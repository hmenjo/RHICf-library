#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

#include <TROOT.h>
#include <TRint.h>
#include <TFile.h>
#include <TStyle.h>
#include <TChain.h>
#include <TString.h>

#include <LHCfEvent.h>
#include <A1CalEventHist.h>
#include <A2CalEventHist.h>

class PrintEventView {
protected:
  LHCfEvent*      fEv;
  TChain*         fTree;
  A1CalEventHist* fA1EventHist;
  A2CalEventHist* fA2EventHist;
  Int_t           fNevents;

public:
  PrintEventView(); 
  void Initialize();
  int  OpenFile(const char* filename);
  int  SearchEvent(int gnumber);
  int  Print(const char* type, const char* filename);
  int  Dump(const char* filename);
};

PrintEventView::PrintEventView(){
  Initialize();
}

void PrintEventView::Initialize(){
  fEv   = new LHCfEvent();
  fTree = new TChain("LHCfEvents","");
  fA1EventHist = new A1CalEventHist();
  fA1EventHist->Initialize();
  fA2EventHist = new A2CalEventHist(); 
  fA2EventHist->Initialize();
  fNevents = 0;
  return ;
}

int PrintEventView::OpenFile(const char* filename){
  fTree->AddFile(filename);
  fTree->SetBranchAddress("ev.",&fEv);
  fNevents = fTree->GetEntries();
  return 0;
}

int PrintEventView::SearchEvent(int gnumber){
  int ie_first = gnumber;
  int ie_end   = ( gnumber+500 < fNevents ? gnumber+500 : fNevents);
  bool check = false;
  cout << "Searching the event of gnumber:" << gnumber << "  ....." << endl;
 
  for(int i=0;i<10;i++){
    if(ie_first >= fNevents){ ie_first /= 2; continue;}
    
    fEv->Delete();
    fTree->GetEntry(ie_first); 
    if( fEv->gnumber > gnumber ){
      ie_first = ie_first * (gnumber / fEv->gnumber) - 100; 
    }
    else {
      check = true;
      break;
    }
  }
  if(check==false){ie_first = 0;}

  check = false;
  for(int ie=ie_first;ie<ie_end;ie++){
    fEv->Delete();
    fTree->GetEntry(ie);
    if( fEv->gnumber == gnumber ){
      check = true;
      break;
    }
  }

  if(check){
    return 0;
  }
  else{
    cerr << "Cannot find the event : gnumber of " << gnumber << endl;
    return -1;
  }
}

int  PrintEventView::Print(const char* type, const char* filename){
  string ss = type;
  if( ss != "a1cal1" && ss != "a1cal2" && ss != "a1sim" &&
      ss != "a2cal1" && ss != "a2cal2" && ss != "a2sim" ){
    cerr << "The data type cannt be treated in this function." << endl;
    return -1;
  }
  
  if( ! fEv->Check(type) ) {
    cerr << "Cannot find the data type [" << type << "] in the event."
	 << endl;
    return -1;
  }

  if( ss == "a1cal1" ) {
    fA1EventHist->DrawCanvas1("low high delay scifiall");
    fA1EventHist->Fill((A1Cal1*)fEv->Get(type));
    fA1EventHist->UpdateCanvas1();
    fA1EventHist->c1->Print(filename);
  }
  else if(ss == "a1cal2" || ss == "a1sim" ){
    fA1EventHist->DrawCanvas1("low scifiall");
    fA1EventHist->Fill((A1Cal2*)fEv->Get(type)); 
    fA1EventHist->UpdateCanvas1();
    fA1EventHist->c1->Print(filename);
  }
  else if ( ss == "a2cal1" ) {
    fA2EventHist->DrawCanvas1("lowsiliconallsilicont1");
    fA2EventHist->Fill((A2Cal1*)fEv->Get(type));
    fA2EventHist->UpdateCanvas1();
    fA2EventHist->c1->Print(filename);
  }
  else if(ss == "a2cal2" || ss == "a2sim" ){
    fA2EventHist->DrawCanvas1("lowhighdelaysiliconallsilicontall");
    fA2EventHist->Fill((A2Cal2*)fEv->Get(type)); 
    fA2EventHist->UpdateCanvas1();
    fA2EventHist->c1->Print(filename);    
  }
  
  return 0;
}

int  PrintEventView::Dump(const char* filename){
  LHCfEvent *oev = new LHCfEvent();
  TTree *otree;
  TFile *ofile = new TFile(filename,"UPDATE");
  
  // If the tree exists in the file, 
  if(ofile->Get("LHCfEvents")!=NULL){
    otree = (TTree*) ofile->Get("LHCfEvents");
    otree->SetBranchAddress("ev.",&oev);
  }
  // Create new Tree
  else {
    otree = new TTree("LHCfEvents","Events After Event Selections");
    otree->Branch("ev.","LHCfEvent",&oev); 
    otree->SetMaxTreeSize(4000000000); 
  }
  
  oev->HeaderCopy(fEv);
  if(fEv->Check("a1cal2")) {oev->Add(fEv->Get("a1cal2")); } 
  if(fEv->Check("a1sim"))  {oev->Add(fEv->Get("a1sim")); }  
  if(fEv->Check("a1rec"))  {oev->Add(fEv->Get("a1rec")); }
  if(fEv->Check("a1simin")){oev->Add(fEv->Get("a1simin")); }  
  if(fEv->Check("a2cal2")) {oev->Add(fEv->Get("a2cal2")); } 
  if(fEv->Check("a2sim"))  {oev->Add(fEv->Get("a2sim")); }  
  if(fEv->Check("a2rec"))  {oev->Add(fEv->Get("a2rec")); }
  if(fEv->Check("a2simin")){oev->Add(fEv->Get("a2simin")); }  
  otree->Fill();
  ofile->Write("",TObject::kOverwrite);
  ofile->Close();
  return 0;
}

//////////////////////////////////////////////////////////

void printhelp(){
  cout << "printeventview -i input_filename -g gnumber -t data_type \n"
       << "  -o output_filename \n"
       << "option) \n"
       << "   -r/--run   run_number : Set Run Number \n"
       << "   -f/--form  form of imput filename like /data/run%5_gc.root \n"
       << "   -d/--draw  Draw the event view on the screen \n"
       << endl;
  return ;
}


int main(int argc, char** argv){
  
  int     run      = -1;
  int     gnumber  = -1;
  TString filename = "";
  TString form     = "";
  TString datatype = "a1cal2"; 
  TString output   = "";
  bool    op_draw  = false;
  TString dumpfile = "";
  
  for(int i=1;i<argc;i++){
    string ss = argv[i];
    if(ss=="-r"||ss=="--run")     {run = atoi(argv[++i]); }
    if(ss=="-g"||ss=="--gnumber") {gnumber = atoi(argv[++i]); }
    if(ss=="-t"||ss=="--type")    {datatype = argv[++i];}
    if(ss=="-i"||ss=="--input")   {filename = argv[++i]; strcpy(argv[i],"");} 
    if(ss=="-o"||ss=="--output")  {output = argv[++i]; strcpy(argv[i],"");} 
    if(ss=="-f"||ss=="--form")    {form = argv[++i]; strcpy(argv[i],"");}
    if(ss=="-d"||ss=="--draw")    {op_draw = true;}
    if(ss=="-D"||ss=="--dump")    {dumpfile = argv[++i]; strcpy(argv[i],"");}
    if(ss=="-h"||ss=="--help")    {printhelp(); exit(0);}
  }

  if(filename=="" && run > 0 && form !=""){
    filename = Form(form.Data(),run);
  }

  if(gnumber <0 || filename=="" || datatype==""){
    printhelp();
    exit(-1);
  }

  if(output==""){
    if(run<0)  output = Form("event_%06d.gif",gnumber);
    else       output = Form("event_run%06d_%06d.gif",run,gnumber);
  }

  if(!op_draw) strcpy(argv[1],"-b");
 
  TApplication theApp("printeventview",&argc,argv);
  gStyle->SetOptStat(0);

  PrintEventView print;
  print.OpenFile(filename);
  if(print.SearchEvent(gnumber) <0){
    exit(-1);
  }
  if(print.Print(datatype,output) == 0){
    cout << "Saved as " << output << endl;
  }

  if(dumpfile!=""){
    print.Dump(dumpfile);
  }

  if(op_draw) theApp.Run();
  return 0;
}
