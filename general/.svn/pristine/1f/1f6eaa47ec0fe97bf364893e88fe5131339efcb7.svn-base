#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#if defined(__CINT__)
#include "../../dict/lib/libLHCfEvent.so"
#else
#include "../../dict/include/LHCfEvent.h"
#include "../../dict/include/SimIncidents.h"
#endif
using namespace std;

int main(int argc, char** argv){
  int  srun=0,erun=0;
  char type[256]="";
  char ifilepath[256]=".";
  char ifilename[256]="";
  char ofilename[256]="";
  
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-s")==0 || strcmp(argv[i],"--start")==0){
      srun = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-e")==0 || strcmp(argv[i],"--end")==0){
      erun = atoi(argv[++i]); 
    }
    if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"--output")==0){
      strcpy(ofilename,argv[++i]);
    }
    if(strcmp(argv[i],"-p")==0 || strcmp(argv[i],"--path")==0){
      strcpy(ifilepath,argv[++i]);
    }
    if(strcmp(argv[i],"-t")==0 || strcmp(argv[i],"--type")==0){
      strcpy(type,argv[++i]);
    }
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0 ||
       argc==1){
      cout << endl;
      cout << "combine ------------------------------------------------------\n"
	   << "  Combine ROOT Files.\n"
	   << "  Input files are defined as (path)/(type)_run%05d.out.\n"
	   << "  Ver1.0: 14,Nov.,2008. Created by H.MENJO\n"
	   << "Command)\n"
	   << "  ./combine -s 10001 -e 10100 -t type [-o file] [-p path]\n"
	   << "Options)\n"
	   << "  -s/--start  : First run number.\n"
	   << "  -e/--end    : Last run number.\n" 
	   << "  -t/--type   : Data type. gencol,darm,end2end.\n"
	   << "  -p/--path   : Path for input file.[default: ./]\n"
	   << "  -o/--output : Output filename.[default:(type)_run(fisrt)_(last).root]\n";
      cout << endl;
      return 0;
    }
  }
  
  if(strcmp(type,"")==0){
    cerr << "" << endl;
    return -1;
  }
  
  if(strcmp(ofilename,"")==0){
    sprintf(ofilename,"%s_run%05d_%05d.root",type,srun,erun);
  }   
  
  int nevent=0;
  int cnevent=0;
  TFile     *ifile;
  TTree     *itree;
  LHCfEvent *iev = new LHCfEvent();
  
  int tevent=0;
  int ctevent=0;
  TFile     *ofile = new TFile(ofilename,"RECREATE");
  TTree     *otree = new TTree("LHCfEvents","Simulation");
  LHCfEvent *oev = new LHCfEvent();
  otree->Branch("ev.","LHCfEvent",&oev);

  for(int run=srun;run<=erun;run++){
    sprintf(ifilename,"%s/%s_run%05d.root",ifilepath,type,run);
    cout << "File: " << ifilename << "    "  << endl;
    nevent = 0;
    cnevent = 0;
    ifile = new TFile(ifilename);
    if(ifile->IsZombie()){
      cerr << "Cannot Find " << ifilename << endl;
      continue;
    }
    
    itree = (TTree*) ifile->Get("LHCfEvents");
    if(itree==0){
      ifile->Close();
      delete ifile;
      continue;
    }
    nevent = itree->GetEntries();
    if(nevent==0){
      cerr << "Nevent = 0" << endl;    
      ifile->Close();
      delete ifile;
      continue;
    }
    itree->SetBranchAddress("ev.",&iev);
    
    for(int i=0;i<nevent;i++){
      iev->Delete();
      itree->GetEntry(i);
      tevent++;

      // *****  CUT ******
      //if(a1simin->GetN()==0){continue;}
      //if((a1simin->GetNHit(1,20,20.0)+a1simin->GetNHit(1,40,20.0))==0){continue;}

      // ***** COPY TO OUTPUT TREE *****
      oev->HeaderCopy(iev);
      if(iev->Check("a1sim")){oev->Add(iev->Get("a1sim"));}
      if(iev->Check("a2sim")){oev->Add(iev->Get("a2sim"));}
      if(iev->Check("a1simin")){oev->Add(iev->Get("a1simin"));}
      if(iev->Check("a2simin")){oev->Add(iev->Get("a2simin"));}
      if(iev->Check("gencol")){oev->Add(iev->Get("gencol"));}
      otree->Fill();
      oev->Clear();
      cnevent++;
      ctevent++;
    }
    itree->ResetBranchAddresses();
    ifile->Close();
    delete ifile;
    
    cout << "Events:  " <<  cnevent << "  /  " << nevent << endl
	 << "TEvents: " <<  ctevent << "  /  " << tevent << endl;
  }
  
  cout << "-------------------------------------------------" << endl;
  cout << "OUTPUT: " << ofilename << endl;
  cout << "TOTAL:  " << tevent << endl;
  
  ofile->cd();
  otree->Write("",TObject::kOverwrite);
  ofile->Close();
  
}
