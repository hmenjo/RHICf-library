#ifndef __LHCFROOTFUNCTIONS_CPP__
#define __LHCFROOTFUNCTIONS_CPP__

#include "LHCfrootFunctions.h"

#include <iostream>
#include <iomanip>

#include "LHCfEvent.h"


/////////////////////////////////////////////////////////////////////////////////

// ====              LHCfEvents_Show             ====

int LHCfEvents_Show(TTree *tree, int iev){
  // LHCfEvents_Show(TTree *tree, int iev)
  // Show the content list of LHCfEvent in EventID:iev of tree.

  tree->Draw("ev.Show()","","goff",1,iev);
  return 0;
}

int LHCfEvents_Show(TFile *file, int iev){
  // LHCfEvents_Show(TFile *file, int iev)
  // Show the content list of LHCfEvent in EventID:iev of file.

  if(file->Get("LHCfEvents")){
    return LHCfEvents_Show((TTree*)file->Get("LHCfEvents"),iev);
  }
  return -1; 
}

int LHCfEvents_Show(int iev){ 
  // LHCfEvents_Show(int iev) 
  // Search LHCfEvents in gDirectory and Show the contents in EventID:iev
 
  if(gDirectory->FindObject("LHCfEvents")){
    return LHCfEvents_Show((TTree*)gDirectory->FindObject("LHCfEvents"),iev);
  }
  if(gFile->Get("LHCfEvents")){
    return LHCfEvents_Show((TTree*)gFile->Get("LHCfEvents"),iev);
  }
  return -1; 
}

/////////////////////////////////////////////////////////////////////////////////

// ====              LHCfEvents_Get              ====
// These classes are for getting the object from the LHCfEvents. 
// The arguments are basically EventID:iev and the object name:objname. 
// The classes with the specific object name are also available.

TObject* LHCfEvents_Get(TTree *tree, const int iev, const TString objname){
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

TObject* LHCfEvents_Get(const int iev, const TString objname){
  if(gDirectory->FindObject("LHCfEvents")){
    return LHCfEvents_Get((TTree*)gDirectory->FindObject("LHCfEvents"),iev,objname);
  }
  if(gFile->Get("LHCfEvents")){
    return LHCfEvents_Get((TTree*)gFile->Get("LHCfEvents"),iev,objname);
  }  
}

A1Raw* LHCfEvents_GetA1Raw(const int iev){
  return (A1Raw*)LHCfEvents_Get(iev, "a1raw");
}

A1Raw_pp2015* LHCfEvents_GetA1Raw_pp2015(const int iev){
  return (A1Raw_pp2015*)LHCfEvents_Get(iev, "a1raw");
}

A1Cal1* LHCfEvents_GetA1Cal1(const int iev){
  return (A1Cal1*)LHCfEvents_Get(iev, "a1cal1");
}

A1Cal2M* LHCfEvents_GetA1Cal2(const int iev){
  return (A1Cal2M*)LHCfEvents_Get(iev, "a1cal2");
}

A1Phys* LHCfEvents_GetA1Phys(const int iev){
  return (A1Phys*)LHCfEvents_Get(iev, "a1phys");
}

Rec0* LHCfEvents_GetA1Rec(const int iev){
  return (Rec0*)LHCfEvents_Get(iev, "a1rec");
}

SimIncidents* LHCfEvents_GetA1Simin(const int iev){
  return (SimIncidents*)LHCfEvents_Get(iev, "a1simin");
}

A2Raw* LHCfEvents_GetA2Raw(const int iev){
  return (A2Raw*)LHCfEvents_Get(iev, "a2raw");
}

A2Raw_pPb2013* LHCfEvents_GetA2Raw_pPb2013(const int iev){
  return (A2Raw_pPb2013*)LHCfEvents_Get(iev, "a2raw");
}

A2Raw_pp2015* LHCfEvents_GetA2Raw_pp2015(const int iev){
  return (A2Raw_pp2015*)LHCfEvents_Get(iev, "a2raw");
}

A2Raw_pPb2016* LHCfEvents_GetA2Raw_pPb2016(const int iev){
  return (A2Raw_pPb2016*)LHCfEvents_Get(iev, "a2raw");
}

A2Cal1* LHCfEvents_GetA2Cal1(const int iev){
  return (A2Cal1*)LHCfEvents_Get(iev, "a2cal1");
}

A2Cal2M* LHCfEvents_GetA2Cal2(const int iev){
  return (A2Cal2M*)LHCfEvents_Get(iev, "a2cal2");
}

A2Phys* LHCfEvents_GetA2Phys(const int iev){
  return (A2Phys*)LHCfEvents_Get(iev, "a2phys");
}

Rec0* LHCfEvents_GetA2Rec(const int iev){
  return (Rec0*)LHCfEvents_Get(iev, "a2rec");
}

SimIncidents* LHCfEvents_GetA2Simin(const int iev){
  return (SimIncidents*)LHCfEvents_Get(iev, "a2simin");
}

SPSAdamo* LHCfEvents_GetAdamo(const int iev){
  return (SPSAdamo*)LHCfEvents_Get(iev, "adamo");
}

// For more details =========================

void LHCfEvents_GetA1Rec_Show(const int iev){
  LHCfEvents_GetA1Rec(iev)->Show();
  return ;
}

void LHCfEvents_GetA2Rec_Show(const int iev){
  LHCfEvents_GetA2Rec(iev)->Show();
  return ;
}

// For RHICf ============================

RHICfRaw_Op2017* LHCfEvents_GetRHICfRaw_Op2017(const int iev){
  return (RHICfRaw_Op2017*)LHCfEvents_Get(iev, "a1raw");
}

RHICfScl_Op2017* LHCfEvents_GetRHICfScl_Op2017(const int iev){
  return (RHICfScl_Op2017*)LHCfEvents_Get(iev, "a1scl");
}

#endif

