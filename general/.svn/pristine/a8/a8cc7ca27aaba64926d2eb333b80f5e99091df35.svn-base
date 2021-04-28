{  
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraph.h>
  gInterpreter->AddIncludePath("../../include");
  gInterpreter->AddIncludePath("../../src");
  
  gSystem->Load("../../lib/libLHCfEvent.so");
  
#include "gsetup.h"
#include "A1RawToCal1.h"

  gsetup();

  TFile *file = new TFile("../../erun00521.root");
  gROOT->cd();  
  
  LHCfEvent *ev = new LHCfEvent();
  TTree* tree = (TTree*)file->Get("LHCfEvents");
  tree->SetBranchAddress("ev.",&ev);
  
  A1Cal1 *a1cal1 = new A1Cal1();
  A1RawToCal1 *a1conv = new A1RawToCal1();
  a1conv->ReadScifiPosTable("config/scifi_pos_table_080408.dat");
  int iev = 0;

  for(int i=0;i<500;i++){
    ev->Delete();
    tree->GetEntry(i);
    if(ev->CheckA1Trg()){
      a1conv->Convert(ev->GetA1Raw("a1raw"),a1cal1);
      cout << a1cal1->cal[0][0][0] << endl;
      iev ++;
      if(iev==4) break;
    }
  }
  
  A1CalEventHist* hist = new A1CalEventHist();
  hist->Initialize();
  hist->Fill(a1cal1);
  
  hist->DrawCanvas1("Low High Delay scifiall");
  hist->DrawCanvas2();
}
