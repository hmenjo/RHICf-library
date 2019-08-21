#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <TROOT.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TRandom3.h>
using namespace std;

#include "LHCfEvent.h"
#include "A1RawToCal1.h"
#include "A1PedeSubtract.h"
#include "A2RawToCal1.h"
#include "A2RawToCal1Silicon.h"
#include "A2PedeSubtract.h"



// --------------------------------------------------------------
void printhelp(){

  return ;
}


int SetFiles(TChain* tree){
  const TString datadir = "/mnt/lhcfs3/data1/DATA/Op2015/root_files/";
  const int run_start = 44299;
  const int run_end   = 44472;
  
  cout << "READ INPUT FILES ============================" << endl; 
  for(int run=run_start;run<=run_end;run++){
    if(run==44356 || run==44413) {continue;} // LASER RUNS
    cout << datadir+Form("run%04d.root",run) << endl;
    tree->AddFile(datadir+Form("run%04d.root",run));
  }
  cout << "=============================================" << endl;
  
  return 0;
}


///////////////////////////////////////////////////////////////////
//                            MAIN                               //
///////////////////////////////////////////////////////////////////
int main(int argc, char** argv){

  // +++++ PARAMETERS ++++++
  TString  outputpedefilename      =   "pedestal_arm1.root";
  TString  outputpedeevfilename    =   "pedeevents_arm1.root";
  TString  dirLibrary        = LIBDIR;       // LIBDIR is defined in Makefile
  TString  paramMAPMTtable   = dirLibrary+"/tables/GSObar_map9.tab";

  // ++++++ INITIALIZATIONS ++++++++++++++++++++
  TRint theApp("App",&argc,argv,0,0,kTRUE);

  A1RawToCal1        *rawtocal1    = new A1RawToCal1();
  rawtocal1->ReadScifiPosTable((char*)paramMAPMTtable.Data());

  A1PedeSubtract     *pedesubtract = new A1PedeSubtract();
  //pedesubtract->ReadFile((char*).Data());
  pedesubtract->SetAccumNEvent(-1);

  // ++++++ OPEN DATA FILE ++++++++++++++++++++++
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  SetFiles(tree); // 
  tree->SetBranchAddress("ev.",&ev);

  // +++++ OPEN OUTPUT FILE +++++++++++++++++++++++++
  TFile     *ofile = new TFile(outputpedeevfilename,"RECREATE");
  LHCfEvent *oev   = new LHCfEvent();
  TTree     *otree = new TTree("LHCfEvents","Collision Events");
  otree->Branch("ev.","LHCfEvent",&oev);
  otree->SetMaxTreeSize(4000000000);
  gROOT->cd();

  // ****************** LOOP *******************************************
  Int_t  ievent = 0;
  Int_t  nevent_fill = 0;
  Int_t  nevent = tree->GetEntries();

  A1Cal1       *cal1 = new A1Cal1("a1cal1","Arm1");
  if(nevent==0) {cerr << "NO EVENT " << endl; exit(-1);}
  cout << "NEVENT: " << nevent << endl;
  for(int ie=0;ie<nevent;ie++){
    if(ie && ie%5000==0) { cerr << '*' ; }
    if(ie && ie%100000==0){ cerr << ie << endl; }
    ev->Delete();
    tree->GetEntry(ie);
    
    if(!ev->Check("a1raw")){continue;}
    ievent++;

    // Convert from Raw to Cal1 
    rawtocal1->Convert(ev->Get("a1raw"),cal1);

    if(! cal1->flag_pede) {continue;}
    
    pedesubtract->FillPedeEvent(cal1); 
    
    // Fill 
    oev->HeaderCopy(ev);
    oev->Add(cal1); 
    otree->Fill();
    oev->Clear();
    nevent_fill++;   
 
  }
  cerr << endl;

  // +++++++++++++++++ Write ++++++++++++++++++++
  ofile->cd();
  otree->Write("",TObject::kOverwrite);
  ofile->Close();
  

  // ++++++++++++++++ Save the pedestal values +++++++
  pedesubtract->CalPedestal();
  pedesubtract->WriteFile((char*)outputpedefilename.Data());  

  // ++++++++++++++++ Print information +++++++++
  cout << endl
       << "NEVENT:           "  << nevent << endl
       << "NLOOP :           "  << ievent << endl
       << "PEDESTAL EVENTS:  "  << nevent_fill << endl;

  return 0;
}

