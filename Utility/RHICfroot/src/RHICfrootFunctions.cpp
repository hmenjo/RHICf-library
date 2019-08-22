#ifndef __RHICFROOTFUNCTIONS_CPP__
#define __RHICFROOTFUNCTIONS_CPP__

#include "RHICfrootFunctions.h"

#include <iostream>
#include <iomanip>

#include "LHCfEvent.h"


/////////////////////////////////////////////////////////////////////////////////

// ====              RHICfEvents_Show             ====

int RHICfEvents_Show(TTree *tree, int iev){
  // RHICfEvents_Show(TTree *tree, int iev)
  // Show the content list of LHCfEvent in EventID:iev of tree.

  tree->Draw("ev.Show()","","goff",1,iev);
  return 0;
}

int RHICfEvents_Show(TFile *file, int iev){
  // RHICfEvents_Show(TFile *file, int iev)
  // Show the content list of LHCfEvent in EventID:iev of file.

  if(file->Get("LHCfEvents")){
    return RHICfEvents_Show((TTree*)file->Get("LHCfEvents"),iev);
  }
  return -1; 
}

int RHICfEvents_Show(int iev){ 
  // RHICfEvents_Show(int iev) 
  // Search LHCfEvents in gDirectory and Show the contents in EventID:iev
 
  if(gDirectory->FindObject("LHCfEvents")){
    return RHICfEvents_Show((TTree*)gDirectory->FindObject("LHCfEvents"),iev);
  }
  if(gFile->Get("LHCfEvents")){
    return RHICfEvents_Show((TTree*)gFile->Get("LHCfEvents"),iev);
  }
  return -1; 
}

/////////////////////////////////////////////////////////////////////////////////

// ====              LHCfEvents_Get              ====
// These classes are for getting the object from the LHCfEvents. 
// The arguments are basically EventID:iev and the object name:objname. 
// The classes with the specific object name are also available.

TObject* RHICfEvents_Get(TTree *tree, const int iev, const TString objname){
  static LHCfEvent* ev = NULL;
  if(ev == NULL) {
    ev = new LHCfEvent();
  }
  else {
    ev->Delete();
  }
  tree->SetBranchAddress("ev.",&ev);
  tree->GetEntry(iev);
  TObject *obj = NULL;
  if(ev->Check((char*)objname.Data())){
    obj = ev->Get((char*)objname.Data());
  }
  else{
    std::cerr << "No object(name:" << objname << ")" << std::endl;
  }
  tree->ResetBranchAddresses();
  return obj;
}

TObject* RHICfEvents_Get(const int iev, const TString objname){
  if(gDirectory->FindObject("LHCfEvents")){
    return RHICfEvents_Get((TTree*)gDirectory->FindObject("LHCfEvents"),iev,objname);
  }
  if(gFile->Get("LHCfEvents")){
    return RHICfEvents_Get((TTree*)gFile->Get("LHCfEvents"),iev,objname);
  }  
}

RHICfRaw_Op2017* RHICfEvents_GetRaw(const int iev){
  return (RHICfRaw_Op2017*)RHICfEvents_Get(iev, "a1raw");
}

A1Cal1* RHICfEvents_GetCal1(const int iev){
  return (A1Cal1*)RHICfEvents_Get(iev, "a1cal1");
}

A1Cal2M* RHICfEvents_GetCal2(const int iev){
  return (A1Cal2M*)RHICfEvents_Get(iev, "a1cal2");
}

RHICfPhys* RHICfEvents_GetPhys(const int iev){
  return (RHICfPhys*)RHICfEvents_Get(iev, "a1phys");
}

RHICfRec0* RHICfEvents_GetRec(const int iev){
  return (RHICfRec0*)RHICfEvents_Get(iev, "a1rec");
}

RHICfSimIncidents* RHICfEvents_GetSimin(const int iev){
  return (RHICfSimIncidents*)RHICfEvents_Get(iev, "a1simin");
}

// For more details =========================

void RHICfEvents_GetRec_Show(const int iev){
  RHICfEvents_GetRec(iev)->Show();
  return ;
}


#endif

