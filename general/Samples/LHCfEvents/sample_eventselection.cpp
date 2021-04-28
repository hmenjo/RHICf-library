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

void sample_eventselection();

#if !defined(__CINT__)
int main(int argc, char** argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  sample_eventselection();
  //theApp.Run();
  return 0;
}
#endif

void sample_eventselection(){
  A1Cal2* a1sim;
  A2Cal2* a2sim;
  
  // Open the data file.
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile("simulation.root"); 
  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);
  
  // Create TTree and LHCfEvent for selected events
  // Please set the name of this TTree to "LHCfEvents" (it's not mandatory)
  TTree* otree = new TTree("LHCfEvents","Title of this TTree");
  LHCfEvent *oev = new LHCfEvent();
  otree->Branch("ev.","LHCfEvent",&oev);
 
  TH1F* hist = new TH1F("hist","Sum dE of all calorimeter",4,0,4);
  
  int nevent = tree->GetEntries();
  int ievent=0;
  int iselected=0;
  for(int ie=0;ie<nevent;ie++){
    ev->Delete(); 
    tree->GetEntry(ie);
    ievent++;
    
    // Event Selection 
    //   In this sample, selection condition is 
    //   that at least sum of one calorimeter dE is > 100 MIPs
    if(ev->Check("a1sim")==0){ continue; }
    if(ev->Check("a2sim")==0){ continue; }
    a1sim = (A1Cal2*) ev->Get("a1sim");
    a2sim = (A2Cal2*) ev->Get("a2sim");
    if( a1sim->calsum(0) < 100. && a1sim->calsum(1) < 100. && 
	a2sim->calsum(0) < 100. && a2sim->calsum(1) < 100.){continue;}
    
    hist->Reset();
    hist->SetBinContent(1,a1sim->calsum(0));
    hist->SetBinContent(2,a1sim->calsum(1));
    hist->SetBinContent(3,a2sim->calsum(0));
    hist->SetBinContent(4,a2sim->calsum(1));

    // Copy the event header to oev
    oev->HeaderCopy(ev);
    
    // Add the objects to oev. you can select the filled object.
    // and fill other object. (exp. the analyzed data, histograms)
    oev->Add(a1sim); 
    oev->Add(a2sim);
    if(ev->Check("a1simin")){ oev->Add(ev->Get("a1simin")); }
    if(ev->Check("a2simin")){ oev->Add(ev->Get("a2simin")); }
    oev->Add(hist);
    
    // Fill the event to TTree
    otree->Fill();

    // Clear the event header and disconnect the filled objects from "oev"
    oev->Clear();
    iselected++;
  }

  cout << "Total Events:    " << ievent << endl
       << "Selected events: " << iselected << endl;

  TFile *f = new TFile("selectedevents.root","RECREATE");
  otree->Write();
  f->Close();
}
