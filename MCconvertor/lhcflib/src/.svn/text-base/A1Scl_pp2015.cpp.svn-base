#ifndef __A1SCL_PP2015_CPP__
#define __A1SCL_PP2015_CPP__

#include "A1Scl_pp2015.h"

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
//   23 Apr 2015: Copied A1Scl by Menjo
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1Scl_pp2015);
#endif

// *****************************************************************
// ***  A1Scl_pp2015  memory allocation of constant values.
// *****************************************************************
const int  A1Scl_pp2015::c_N_A1_PTIM ;
const int  A1Scl_pp2015::c_N_A1_PSCL ;
const int  A1Scl_pp2015::c_N_A1_RAMC ;

int A1Scl_pp2015::clear(){
  run = 0;
  number = 0;
  
  for(int i=0;i<c_N_A1_PTIM;i++){time[i]=0;}
  for(int i=0;i<c_N_A1_PSCL;i++){scl0[i]=0;}
  for(int i=0;i<c_N_A1_RAMC;i++){ramc[i]=0;}
  //   for(int i=0;i<N_PGP0;i++){gpio0[i]=0;}
  //   for(int i=0;i<N_PGP1;i++){gpio1[i]=0;}

  return OK;
}

int  A1Scl_pp2015::copy(A1Scl_pp2015* d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int  A1Scl_pp2015::copydata(A1Scl_pp2015* d){
  this->run     = d->run;
  this->number  = d->number;
  
  for(int i=0;i<c_N_A1_PTIM;i++){this->time[i]=d->time[i];}
  for(int i=0;i<c_N_A1_PSCL;i++){this->scl0[i]=d->scl0[i];}
  for(int i=0;i<c_N_A1_RAMC;i++){this->ramc[i]=d->ramc[i];}
  return OK;
}

#endif
