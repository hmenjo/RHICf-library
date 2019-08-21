{
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include "../../dict/lib/libLHCfEvent.so"

TChain* tree = new TChain("LHCfEvents");
tree->AddFile("a.root"); 
LHCfEvent *ev = new LHCfEvent();
tree->SetBranchAddress("ev.",&ev);

cout << tree->GetEntries() << endl;
tree->GetEntry(0);
ev->Show();


for(int ie=0;ie<10;ie++){
  ev->Show();
  ev->Get("a2cal1")->Dump();
  ev->Get("adamo")->Dump();
}

}
