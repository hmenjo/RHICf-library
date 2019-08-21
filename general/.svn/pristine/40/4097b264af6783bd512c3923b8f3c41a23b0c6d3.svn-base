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

void sample_simincidents();

#if !defined(__CINT__)
int main(int argc, char** argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  sample_simincidents();
  //theApp.Run();
  return 0;
}
#endif

void sample_simincidents(){
  SimP *pp;
  SimIncidents* a1simin;

  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile("simulation.root"); 
  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);
  
  int nevent = tree->GetEntries();
  int np=0;
  for(int ie=0;ie<nevent;ie++){
    ev->Delete();
    tree->GetEntry(ie);
    
    if(ev->Check("a1simin")==0){continue;}

    a1simin = (SimIncidents*)ev->Get("a1simin");
    a1simin->Show();
    
    np = a1simin->GetN();
    for(int ip=0;ip<np;ip++){
      pp = a1simin->Get(ip); 
      cout << "IP: " << setw(4) << ip << "   " 
	   << "KE: " << setw(6) << setprecision(5)
	   << pp->KineticEnergy() << "   " 
	   << "POS on 20mm coordinate:  " 
	   << setw(6) << setprecision(2) << pp->CalPosX(1,0) << "  " 
	   << setw(6) << setprecision(2) << pp->CalPosY(1,0) << "  " 
	   << endl;
    }
    
    if(ie>10) break;
  }
  
}
