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

void sample_eventloop();

#if !defined(__CINT__)
int main(int argc, char** argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  sample_eventloop();
  //theApp.Run();
  return 0;
}
#endif

void sample_eventloop(){
  A1Cal2* a1sim;
  A2Cal2* a2sim;
  SimIncidents* a1simin;
  SimIncidents* a2simin;

  // Open the data file.
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile("darm_run13551.root"); 

  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);

  int nevent = tree->GetEntries();
  for(int ie=0;ie<nevent;ie++){
    ev->Delete();   
    tree->GetEntry(ie);

    ev->Show();
    if(ev->Check("a1simin")!=0){((SimIncidents*)ev->Get("a1simin"))->Show();}
    if(ev->Check("a2simin")!=0){((SimIncidents*)ev->Get("a2simin"))->Show();}
    
    cout << endl;
    cout << "RUN: " << ev->run << "   ";
    cout << endl;
    
    if(ie>40) break;
  }
}

