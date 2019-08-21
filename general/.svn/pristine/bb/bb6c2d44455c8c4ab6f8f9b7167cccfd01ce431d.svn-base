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

void sample_eventdraw(){

  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile("simulation.root"); 

  char command[256];
  char cut[256];
  TCanvas* c0 = new TCanvas();
  c0->SetLogy();
  tree->SetLineWidth(2);
  tree->SetLineColor(4);
  strcpy(cut,"ev.Check(\"a1sim\")");
  
  // Please add "+ev.Delete()" at the last of command string.
  // ev.Delete() return always 0, so it not affect the histogram.
  // If you don't use "ev.Delete()", the memory size of this process
  // will keep on increasing.
 
  strcpy(command,"ev.GetA1Cal2(\"a1sim\")->calsum(0)+ev.Delete()");
  tree->SetLineStyle(1);
  tree->Draw(command,cut);
  strcpy(command,"ev.GetA1Cal2(\"a1sim\")->calsum(1)+ev.Delete()");
  tree->SetLineStyle(2);
  tree->Draw(command,cut,"same");
  
  tree->SetLineColor(2);
  strcpy(cut,"ev.Check(\"a2sim\")");
  strcpy(command,"ev.GetA2Cal2(\"a2sim\")->calsum(0)+ev.Delete()");
  tree->SetLineStyle(1);
  tree->Draw(command,cut,"same");
  strcpy(command,"ev.GetA2Cal2(\"a2sim\")->calsum(1)+ev.Delete()");
  tree->SetLineStyle(2);
  tree->Draw(command,cut,"same");
  
  c0->Update();

}
