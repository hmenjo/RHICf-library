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

void eventview();
void Go(int i);
void Next();
void Previous();

#if !defined(__CINT__)
int main(int argc, char** argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  eventview();
  theApp.Run();
  return 0;
}
#endif

int ievent;
TChain* tree;
LHCfEvent *ev;
A1CalEventHist* hist;
A1Cal2* a1sim;
SimIncidents *a1simin;

void eventview(){
  ievent=0;
  
  ev = new LHCfEvent();
  tree = new TChain("LHCfEvents","");
  //tree->Add("/home2/LHCf/Simulation/LHC/end2end_root05/end2end_run19501_19550.root");
  tree->Add("/home2/LHCf/Simulation/LHC/end2end_root90/end2end_run90052.root");
  tree->SetBranchAddress("ev.",&ev);
  
  tree->GetEntry(0);
  a1sim = ev->GetA1Cal2("a1sim");

  hist = new A1CalEventHist();
  hist->Initialize();
  hist->Fill(a1sim);
  hist->DrawCanvas1("Low scifiall");
}

void Go(int i){
  tree->GetEntry(i);
  a1sim = ev->GetA1Cal2("a1sim");
  cout << a1sim->run << "  " << a1sim->number << endl;
  hist->Reset();
  hist->Fill(a1sim);
  hist->UpdateCanvas1();
  
  SimP *pp;
  a1simin = (SimIncidents*)ev->Get("a1simin");
  int nhit=0;
  
  cout.setf(ios::fixed);
  
  nhit = a1simin->GetNHit(1,20,10.);
  for(int i=0;i<nhit;i++){
    pp = a1simin->GetHit(1,20,i);
    cout << "20mm: " << setw(3) << i << " "  
	 << setw(3) << pp->code << " " 
	 << setw(4) << pp->user << " "
	 << setw(5) << setprecision(0) << pp->KineticEnergy() << " "
      	 << setw(5) << setprecision(1) << pp->CalPosX(1,20) << " " 
	 << setw(5) << setprecision(1) << pp->CalPosY(1,20) << " " 
	 << setw(5) << setprecision(1) << pp->PosX() << " "
      	 << setw(5) << setprecision(1) << pp->PosY() << " "
	 << endl;
  }

  nhit = a1simin->GetNHit(1,40,10.);
  for(int i=0;i<nhit;i++){
    pp = a1simin->GetHit(1,40,i);
    cout << "40mm: " << setw(3) << i << " "  
	 << setw(3) << pp->code << " " 
	 << setw(4) << pp->user << " "
	 << setw(5) << setprecision(0) << pp->KineticEnergy() << " "
      	 << setw(5) << setprecision(1) << pp->CalPosX(1,40) << " " 
	 << setw(5) << setprecision(1) << pp->CalPosY(1,40) << " " 
	 << setw(5) << setprecision(1) << pp->PosX() << " "
      	 << setw(5) << setprecision(1) << pp->PosY() << " "
	 << endl;
  }

  nhit = a1simin->GetN();
  for(int i=0;i<nhit;i++){
    pp = a1simin->Get(i);
    if(pp->CheckHit(1,0)==0 && pp->CheckHit(1,1)==0){
      cout << "Other:" << setw(3) << i << " "  
	   << setw(3) << pp->code << " " 
	   << setw(4) << pp->user << " "
	   << setw(5) << setprecision(0) << pp->KineticEnergy() << " "
	   << setw(5) << setprecision(1) << pp->PosX() << " "
	   << setw(5) << setprecision(1) << pp->PosY() << " "
	   << endl;
    }
  }
}

void Next(){
  ievent++;
  Go(ievent);
}

void Previous(){
  ievent--;
  Go(ievent);
}
