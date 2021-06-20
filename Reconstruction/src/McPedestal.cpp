#include <McPedestal.h>

#include <TFile.h>
#include <TRandom3.h>

McPedestal::McPedestal(){
  new TRandom3();
}

Int_t McPedestal::ReadFile(TString filename){
  
  LHCfEvent *fEv   = new LHCfEvent();
  fTree = new TChain("LHCfEvents");
  fTree->Add(filename);
  fTree->SetBranchAddress("ev.", &fEv);

  fNentries = fTree->GetEntries();
  fIev = gRamdom->Integer(fNentries);

  return 0;
}


Int_t McPedestal::AddPedestal(A2Cal2M* cal){

  // Get One Pedestal events

  fTree->GetEntry(fIev);
  if(! fEv->Check("a1cal2")) {
	 cerr << "Error : No cal2 in the file" << endl;
	 return -1;
  } 
  A2Cal2M* pede = fEv->Get("a1cal2");

  // Add pedestal values to MC data
  cal->Add(pede);

  // Increment the pedestal event number
  fEv->Delete();
  fIev++;
  if(fIev == fNentries) fIev = 0;
  return 0;
  
}
