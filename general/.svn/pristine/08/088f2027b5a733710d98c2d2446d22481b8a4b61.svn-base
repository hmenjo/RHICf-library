/************************************************************************\

               The simplest code for touching a1cal data   

                  Class References can be found in 
  http://lhcfs1.stelab.nagoya-u.ac.jp/analysis/ClassIndex/ClassIndex.html

\************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1D.h>

#include <LHCfEvent.h>
#include <RHICfRaw_Op2017.h>
#include <RHICfScl_Op2017.h>
#include <A1Cal1.h>
#include <A1RawToCal1.h>
#include <A1PedeSubtract.h>

// typedef just for simplicity 
typedef LHCfEvent        RHICfEvent;
typedef RHICfRaw_Op2017  RHICfRaw;
typedef RHICfScl_Op2017  RHICfScl;

void printhelp(){
  cout << "./sample_eventloop -i inputfile -p pedestal -o outputfile" << endl;
}

/////////////////////////////////////////////////////////////////////
//                              MAIN 
/////////////////////////////////////////////////////////////////////
int main(int argc,char **argv){

  vector<string> inputfiles;
  string         pedestalfile = "";
  string         outputfile = "";
  for(int i=1;i<argc;i++){
	 string ss = argv[i];
	 if(ss=="-i"){
		inputfiles.push_back(argv[++i]);
	 }
	 if(ss=="-s"){
		pedestalfile = argv[++i];
	 }
	 if(ss=="-o"){
		outputfile = argv[++i];
	 }
	 if(ss=="-h" || ss=="--help"){
		printhelp();
		return -1;
	 }
  }

  TApplication app("sample2",&argc,argv);
  
  // +++++++++++++++++++ OPEN DATA FILES +++++++++++++++++++++++
  RHICfEvent *ev = new RHICfEvent();
  TChain* tree = new TChain("LHCfEvents");  // Must be used "LHCfEvents" 
  for(int i=0;i<inputfiles.size();i++){ 
    tree->Add(inputfiles[i].c_str());
  }
  tree->SetBranchAddress("ev.",&ev);
  int nev = tree->GetEntries();

  // ++++++++++++++++++ FUNCTIONS FOR CONVERSION +++++++++++++++
  // For Format Conversion of RHICfRaw to A1Cal1
  A1RawToCal1    *conv = new A1RawToCal1();
  conv->ReadScifiPosTable("../../tables/GSObar_map9.tab");
  // For Pedestal Subtraction 
  A1PedeSubtract *pedesubtract = new A1PedeSubtract();
  if(pedestalfile!=""){
    pedesubtract->ReadFile((char*)pedestalfile.c_str());
  }

  // ++++++++++++++++ MAKING HISTOGRAMAS ++++++++++++++++++++++++

  TH1D* h_col = new TH1D("h_col","",400,-400,3600);
  TH1D* h_ped = new TH1D("h_ped","",400,-400,3600);

  // ++++++++++++++++++++++ EVENT LOOP ++++++++++++++++++++++++++
  A1Cal1 *cal = new A1Cal1();
  for(int i=0;i<nev;i++){
    ev->Delete();         // Delete must be called every event 
    tree->GetEntry(i);    
	 
 	 // Select only the triggered event(Cut Scaler event)
	 if(!ev->Check("a1raw")){continue;}
	 
	 // Format conversion 
	 conv->Convert(ev->Get("a1raw"),cal);
	 
	 // Pedestal Subtraction
	 pedesubtract->Subtraction(cal);
	 
	 // Fill the adc value of TS 0th, NRADC to a histogram 
	 if(cal->flag_beam)  h_col->Fill(cal->cal[0][0][0]); // Tower:Layer:Range(0,1) 
	 if(cal->flag_pede)  h_ped->Fill(cal->cal[0][0][0]); // Tower:Layer:Range(0,1) 
	 
	 if(i&&i%1000==0)  {cerr << "*";}
	 if(i&&i%500000==0){cerr << i<<endl;}
	 
  } // End of loop
  cerr << endl;

  if(outputfile!=""){
	 TFile *file = new TFile(outputfile.c_str(),"RECREATE");
	 file->cd();
	 h_col->Write();
	 h_ped->Write();
	 file->Close();
  }
 

  //app.Run();
  return 0;
}
