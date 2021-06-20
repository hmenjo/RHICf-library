#include <McPedestal.h>

#include <iostream>
using namespace std;

#include <TFile.h>
#include <TRandom3.h>

McPedestal::McPedestal(){;}

Int_t McPedestal::ReadFile(TString filename){
  
  fEv   = new LHCfEvent();
  fTree = new TChain("LHCfEvents");
  fTree->Add(filename);
  fTree->SetBranchAddress("ev.", &fEv);

  fNentries = fTree->GetEntries();

  TRandom3 rand;
  rand.SetSeed();
  fIev = rand.Integer(fNentries);

  cout << "# Pedestal list: " << fNentries << "    Initial value= " << fIev << endl;

  return 0;
}


Int_t McPedestal::AddPedestal(A1Cal2M* cal){

  // Get One Pedestal events
  fTree->GetEntry(fIev);
  if(! fEv->Check("a1cal2")) {
	 cerr << "Error : No cal2 in the file" << endl;
	 return -1;
  } 
  A1Cal2M* pede = (A1Cal2M*)fEv->Get("a1cal2");

  // Add pedestal values to MC data
  cal->add(pede);

  // Increment the pedestal event number
  fEv->Delete();
  fIev++;
  if(fIev == fNentries) fIev = 0;
  return 0;
  
}
