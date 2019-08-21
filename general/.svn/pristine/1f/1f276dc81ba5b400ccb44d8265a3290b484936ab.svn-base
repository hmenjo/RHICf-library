{
  #include "TH1F.h"
  #include "TPad.h"
  #include "TGraph.h"
  gSystem->SetIncludePath(" -I../../dict/include ");
  gSystem->SetIncludePath(" -I../../dict/src ");
  gSystem->SetIncludePath(" -I../../func/include ");
  gSystem->SetIncludePath(" -I../../func/src ");  
  gSystem->Load("../../dict/lib/libLHCfEvent.so");
  
  
  TFile *file = new TFile("../data/srun10001_10100.root");
  TTree* tree = (TTree*) file->Get("LHCfEvents");
  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);
  
  A1Cal2* a1sim;
  SimIncidents *a1simin;

  tree->GetEntry(2);  
  a1sim = (A1Cal2*)ev->Get("a1sim");
  a1simin =  (SimIncidents*)ev->Get("a1simin");
  
  TH1F *h1_ch0 = new TH1F("h1_ch0","Ch0",100,0,10000);
  TH1F *h1_ch1 = new TH1F("h1_ch1","Ch1",100,0,10000); 
  
  for(int ie=0;ie<100;ie++){
    ev->Delete();
    tree->GetEntry(ie);  
    if(ev->Check("a1sim")==0) continue; 
    if(ev->Check("a1sim")==0) continue; 
    a1sim = (A1Cal2*)ev->Get("a1sim");
    a1simin = (SimIncidents*)ev->Get("a1simin");

    cout << a1sim->fc[0][0] << endl;
    h1_ch0->Fill(a1sim->fc[0][0]);
    h1_ch1->Fill(a1sim->fc[0][1]);
    
//     cout << "N=" << a1simin->GetN() << endl;
//     for(int i=0;i<a1simin->GetN();i++){
//       cout << i << "   " << a1simin->Get(i)->KineticEnergy() << endl;
//     }
    
  }
  
  TCanvas *c = new TCanvas("c","",600,600);
  c->Divide(2,2);
  c->cd(1);
  h1_ch0->Draw();
  c->cd(2);
  h1_ch1->Draw();
  
  c->Update();

  char command[256];
  char cut[1000];
//   sprintf(command,
// 	  "(SimIncidents*)(ev->Get(\"a1simin\"))->GetHit(1,0,0)->KineticEnergy()");
//   sprintf(command,
// 	  "(SimIncidents*)(ev->Get(\"a1simin\"))->GetHit(1,0,0)->code");  
//   sprintf(cut,
// 	  "(SimIncidents*)(ev->Get(\"a1simin\"))->GetNHit(1,0)>0 ");
//   strcat(cut,
// 	 " && (SimIncidents*)(ev->Get(\"a1simin\"))->GetHit(1,0,0)->code==1");
//   tree->Draw(command,cut);

//   tree->Draw("0 >> h(4,0,4)",
// 	     "ev->GetA1Cal2(\"a1sim\")->fc[0][0]>0.5&&ev->GetA1Cal2(\"a1sim\")->fc[0][2]>0.5");
//   sprintf(cut,
// 	  "ev->GetA1Cal2(\"a1sim\")->fc[0][0]>0.5&&ev->GetA1Cal2(\"a1sim\")->fc[0][2]>0.5" );
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][1]>0.5&&ev->GetA1Cal2(\"a1sim\")->fc[0][2]>0.5");
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][0]>0.5&&ev->GetA1Cal2(\"a1sim\")->fc[0][3]>0.5");
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][1]>0.5&&ev->GetA1Cal2(\"a1sim\")->fc[0][3]>0.5"); 
//   sprintf(cut,
// 	  "ev->GetA1Cal2(\"a1sim\")->fc[0][0]>0.5" );
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][1]>0.5");
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][2]>0.5");
//   strcat(cut,
// 	 " || ev->GetA1Cal2(\"a1sim\")->fc[0][3]>0.5"); 

//   tree->Draw("0 >> h(4,0,4)",cut);
}
