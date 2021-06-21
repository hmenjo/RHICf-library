#ifndef __MCPEDESTAL_H__
#define __MCPEDESTAL_H__

#include <TChain.h>
#include <TString.h>
#include <LHCfEvent.h>
#include <A1Cal2M.h>

class McPedestal {
 public:
  LHCfEvent  *fEv;
  TChain     *fTree;
  Int_t      fNentries;
  Int_t      fIev;
  
  

 public:
  McPedestal();
  Int_t   ReadFile(TString filename);
  Int_t   AddPedestal(A1Cal2M* cal); 
};


#endif 
