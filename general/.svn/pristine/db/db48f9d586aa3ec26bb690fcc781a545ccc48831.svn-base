{  
#include <TH1F.h>
  gInterpreter->AddIncludePath("../../include");
  gInterpreter->AddIncludePath("../../src");
  gSystem->Load("../../lib/libLHCfEvent.so");
  
  TFile *file = new TFile("../../erun00477.root");
  gROOT->cd();  

  TTree* tree = (TTree*)file->Get("LHCfEvents");
  
//   tree->Draw("ev.GetA1Raw(\"a1raw\")->adc0[1]",
// 	     "ev.CheckA1Trg()","",
// 	     1000,0);
  
  tree->Draw("ev.GetA1Raw(\"a1raw\")->adc0[1]:ev.GetA1Raw(\"a1raw\")->adc0[33]",
	     "ev.CheckA1Trg()","",
	     1000,0);
}
