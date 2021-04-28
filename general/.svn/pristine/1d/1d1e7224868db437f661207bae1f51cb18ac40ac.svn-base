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
  tree->AddFile("simulation.root"); 
  // TChain is for a chain of TTree. Therefore this part can be made 
  // replacement to following 2 line
  //   TFile* f = new TFile("");
  //   TTree* tree = (TTree*) f->Get("LHCfEvents")
  // For the detail, see the ROOT manual.

  // Connect the LHCfEvents in TTree to a memory 
  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);

  int nevent = tree->GetEntries();
  for(int ie=0;ie<nevent;ie++){
    // Delete the old objects on the memory.
    ev->Delete();   // !! Important !! Don't foget to call this
    
    // Get the data of #Event ie.
    tree->GetEntry(ie);

    // Show the information of the event.
    ev->Show();
    
    // Check the presence of the object with name of "a1sim".
    // If there is the object in this event, return non-zero value  
    if(ev->Check("a1sim")==0){continue;}

    // Get the object with casting into class of the object.
    // The type of return value of LHCfEvent::Get function is (TObject*)  
    a1sim = (A1Cal2*) ev->Get("a1sim");
    
    // Print, Analyze etc... as you want 
    cout << endl;
    cout << "RUN: " << ev->run << "   "
	 << "#EVENT: " << a1sim->number << "  "  
	 << "dE(20mm-05):  " << a1sim->cal[0][5] << endl;
    cout << endl;
    
    if(ie>10) break;
  }
}

