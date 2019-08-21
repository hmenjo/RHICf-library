#ifndef __A2SCL_PP2015_CPP__
#define __A2SCL_PP2015_CPP__

#include "A2Scl_pp2015.h"

//----------------------------------------------------------------------
//
// This class stores a scaler event of Frontend1
//
// DATA FORMAT:  (11 Feb. 2010 by H.MENJO)
//  - int    run            (Run Number)
//  - int    number         (Arm#1 Event Number)
//  - unsigned int time[1]  (CPU time)
//  - unsigned int scl0[16] (Scaler value[channel])
//     Channel List
//      [0] :  ?
//      [1] :  ?
//      [2] :  ?
//      [3] :  ?
//      [4] :  ?
//      [5] :  ?
//      [6] :  ?
//      [7] :  ?
//      [8] :  ?
//      [9] :  ?
//      [10]:  ?
//      [11]:  ?
//      [12]:  ?
//      [13]:  ?
//      [14]:  ?
//      [15]:  no input
//     
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ?? ???. 08: First edited by H.MENJO
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Scl_pp2015);
#endif

// *****************************************************************
// ***  A1Scl_pp2015  memory allocation of constant values.
// *****************************************************************
const int  A2Scl_pp2015::c_N_A2_PTIM ;
const int  A2Scl_pp2015::c_N_A2_PSCL ;
const int  A2Scl_pp2015::c_N_A2_RAMC ;

int A2Scl_pp2015::clear(){
  run = 0;
  number = 0;
  
  for(int i=0;i<c_N_A2_PTIM;i++){time[i]=0;}
  for(int i=0;i<c_N_A2_PSCL;i++){scl0[i]=0;}
  for(int i=0;i<c_N_A2_RAMC;i++){ramc[i]=0;}


  return OK;
}

int  A2Scl_pp2015::copy(A2Scl_pp2015* d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int  A2Scl_pp2015::copydata(A2Scl_pp2015* d){
  this->run     = d->run;
  this->number  = d->number;
  
  for(int i=0;i<c_N_A2_PTIM;i++){this->time[i]=d->time[i];}
  for(int i=0;i<c_N_A2_PSCL;i++){this->scl0[i]=d->scl0[i];}
  for(int i=0;i<c_N_A2_RAMC;i++){this->ramc[i]=d->ramc[i];}

  return OK;
}
#endif
