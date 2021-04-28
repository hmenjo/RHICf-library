{  
#include <TH1F.h>
  gInterpreter->AddIncludePath("../../include");
  gInterpreter->AddIncludePath("../../src");
  gSystem->Load("../../lib/libLHCfEvent.so");
  
  TFile *file = new TFile("../../erun00477.root");
  gROOT->cd();  
  
  LHCfEvent *ev = new LHCfEvent();
  TTree* tree = (TTree*)file->Get("LHCfEvents");
  tree->SetBranchAddress("ev.",&ev);
  
  A1Raw* a1raw;
  TH1F* h = new TH1F("h","ADC",4000,0,4000);

  for(int i=0;i<10000;i++){
    ev->Delete();
    tree->GetEntry(i);
    if(ev->CheckA1Trg()){
      a1raw = ev->GetA1Raw("a1raw");
      h->Fill(a1raw->adc0[1]);
    }
  }
  
  h->Draw();
  
}
