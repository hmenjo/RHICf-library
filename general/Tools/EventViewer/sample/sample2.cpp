{  
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraph.h>
  gInterpreter->AddIncludePath("../../include");
  gInterpreter->AddIncludePath("../../src");
  
  gSystem->Load("../../lib/libLHCfEvent.so");
  
#include "gsetup.h"
#include "A2RawToCal1.h"

  gsetup();

  TFile *file = new TFile("../../erun00446.root");
  gROOT->cd();  
  
  LHCfEvent *ev = new LHCfEvent();
  TTree* tree = (TTree*)file->Get("LHCfEvents");
  tree->SetBranchAddress("ev.",&ev);
  
  A2Cal1 *a2cal1 = new A2Cal1();
  A2RawToCal1 *a2conv = new A2RawToCal1();
  int iev = 0;

  for(int i=0;i<20;i++){
    ev->Delete();
    tree->GetEntry(i);
    if(ev->CheckA1Trg()){
      a2conv->Convert(ev->GetA2Raw("a2raw"),a2cal1);
      cout << a2cal1->cal[0][0][0] << endl;
      iev ++;
      if(iev==2) break;
    }
  }
  
  A2CalEventHist* hist = new A2CalEventHist();
  hist->Initialize();
  hist->Fill(a2cal1);
  
  hist->DrawCanvas1("Low High Delay siliconall silicontall");
  hist->DrawCanvas2();
}
