#ifndef __RHICFSCL_OP2017_CPP__
#define __RHICFSCL_OP2017_CPP__

#include "RHICfScl_Op2017.h"

//----------------------------------------------------------------------
//
// This class stores a scaler event of Frontend1
//
// ====================================================================
// DATA FORMAT:
//  - int    run        (Run Number)
//  - int    number     (Scaler Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - unsigned int counter[120]  (BRAM Counter values)
//        counter[i] : Shower Trigger Counts of  bunch ID i
//  - unsigned int   logic_counter[12] (Counters in RHICF_LOGIC)
//              VME Address  Inputs
//        [0] :    0x201C,   SHOWER_TRG1
//        [1] :    0x2040,   SHOWER_TRG_VETOED (2 CLK vetoed)
//        [2] :    0x2020,   L2T_SHOWER
//        [3] :    0x2024,   L2T_SHOWER AND L3T
//        [4] :    0x202C,   SPECIAL1_TRG1
//        [5] :    0x2044,   SPECIAL1_TRG_VETOED  (2 CLK vetoed)
//        [6] :    0x2030,   L2T_SPECIAL1 AND L3T 
//        [7] :    0x2034,   SPECIAL2_TRG1
//        [8] :    0x2048,   SPECIAL2_TRG_VETOED  (2 CLK vetoed)
//        [9] :    0x204C,   L2T_SPECIAL2
//        [10]:    0x2038,   L2T_SPECIAL2 AND L3T 
//        [11]:    0x203C,   L3T
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(RHICfScl_Op2017);
#endif

// *****************************************************************
// ***  RHICfScl_Op2017  memory allocation of constant values.
// *****************************************************************
const int  RHICfScl_Op2017::c_N_A1_PTIM ;
const int  RHICfScl_Op2017::c_N_A1_PGP0 ;
const int  RHICfScl_Op2017::c_N_A1_PGP1 ;

int RHICfScl_Op2017::clear(){
  run = 0;
  number = 0;
  
  for(int i=0;i<c_N_A1_PTIM;i++){time[i]=0;}
  for(int i=0;i<c_N_A1_PGP0;i++){logic_counter[i]=0;}
  for(int i=0;i<c_N_A1_PGP1;i++){counter[i]=0;}

  return OK;
}

int  RHICfScl_Op2017::copy(RHICfScl_Op2017* d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int  RHICfScl_Op2017::copydata(RHICfScl_Op2017* d){
  this->run     = d->run;
  this->number  = d->number;
  
  for(int i=0;i<c_N_A1_PTIM;i++){this->time[i]=d->time[i];}
  for(int i=0;i<c_N_A1_PGP0;i++){this->logic_counter[i]=d->logic_counter[i];}
  for(int i=0;i<c_N_A1_PGP1;i++){this->counter[i]=d->counter[i];}
  return OK;
}

#endif
