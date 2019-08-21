{
  #include "TH1F.h"
  #include "TPad.h"
  #include "TGraph.h"
  gSystem->SetIncludePath(" -I../../dict/include ");
  gSystem->SetIncludePath(" -I../../dict/src ");
  gSystem->SetIncludePath(" -I../../func/include ");
  gSystem->SetIncludePath(" -I../../func/src ");  
  gSystem->Load("../../dict/lib/libLHCfEvent.so");
  
  
  TFile *file = new TFile("tmp.root");
  TTree* tree = (TTree*) file->Get("LHCfEvents");
  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);
  
  A1Cal2* a1sim;
  SimIncidents *a1simin;

  tree->GetEntry(2);  
  a1sim = (A1Cal2*)ev->Get("a1sim");
  a1simin =  (SimIncidents*)ev->Get("a1simin");
  cout << ev->gnumber << endl;
  cout << ev->Get("a1sim") << endl;
  cout << ev->Get("a1simin") << endl;  
//   cout << (A1Cal2*)(ev->Get("a1sim"))->cal[0][0] << endl;
  
  for(int ie=0;ie<100;ie++){
    tree->GetEntry(ie);  
//     a1simin = (SimIncidents*)ev->Get("a1simin");
//     cout << "N=" << a1simin->GetN() << endl;
//     for(int i=0;i<a1simin->GetN();i++){
//       cout << i << "   " << a1simin->Get(i)->KineticEnergy() << endl;
//     }
    cout<<  ev->GetA1Cal2("a1sim")->scifi0[0][0][10] << endl;
  }
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
