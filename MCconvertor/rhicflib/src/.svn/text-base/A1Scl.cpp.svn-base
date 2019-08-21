#ifndef __A1SCL_CPP__
#define __A1SCL_CPP__

#include "A1Scl.h"

//----------------------------------------------------------------------
//
// This class stores a scaler event of Frontend1
//
// DATA FORMAT:  (11 Feb. 2010 by H.MENJO)
//  - int    run            (Run Number)
//  - int    number         (Arm#1 Event Number)
//  - unsigned int time[1]  (CPU time)
//  - unsigned int scl0[16] (Scaler value[channel])
//     Channel List (for configuration in 2009)
//      [0] :  40MHz Clock
//      [1] :  Cascade from [0]
//      [2] :  BPTX1
//      [3] :  Cascade from [2]
//      [4] :  BPTX2
//      [5] :  Cascade from [4]
//      [6] :  L3T
//      [7] :  L2TA
//      [8] :  Arm1 FC1
//      [9] :  Arm1 FC2
//      [10]:  Arm1 FC3
//      [11]:  Arm1 FC4
//      [12]:  LHCFCOUNTER:MLEMO(10) Arm1 FC Trigger
//      [13]:  LHCFCOUNTER:MLEMO(11) Arm2 FC Trigger
//      [14]:  LHCFCOUNTER:MLEMO(9)  Coincident of Arm1 FC and Arm2 FC
//      [15]:  no input
//
//     Channel List (for configuration in 2015)     
//      [0] :  Cascade from [0]
//      [1] :  40MHz Clock
//      [2] :  BPTX1
//      [3] :  BPTX2
//      [4] :  L3T
//      [5] :  FC Coincidence
//      [6] :  FC1 TRG
//      [7] :  FC2 TRG
//      [8] :  Arm1 FC1
//      [9] :  Arm1 FC2
//      [10]:  Arm1 FC3
//      [11]:  Arm1 FC4
//      [12]:  -
//      [13]:  -
//      [14]:  - 
//      [15]:  -
//     
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ?? ???. 08: First edited by H.MENJO
//   30 Apr. 15: Y.Makino add channel list for pp2015
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1Scl);
#endif

int A1Scl::clear(){
  run = 0;
  number = 0;
  
  for(int i=0;i<N_A1_PTIM;i++){time[i]=0;}
  for(int i=0;i<N_A1_PSCL;i++){scl0[i]=0;}
  //   for(int i=0;i<N_PGP0;i++){gpio0[i]=0;}
  //   for(int i=0;i<N_PGP1;i++){gpio1[i]=0;}

  return OK;
}

int  A1Scl::copy(A1Scl* d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int  A1Scl::copydata(A1Scl* d){
  this->run     = d->run;
  this->number  = d->number;
  
  for(int i=0;i<N_A1_PTIM;i++){this->time[i]=d->time[i];}
  for(int i=0;i<N_A1_PSCL;i++){this->scl0[i]=d->scl0[i];}
  
  return OK;
}

#endif
