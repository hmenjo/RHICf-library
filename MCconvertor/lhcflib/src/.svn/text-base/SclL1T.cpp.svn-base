#ifndef __SclL1T_CPP__
#define __SclL1T_CPP__

#include "SclL1T.h"

//----------------------------------------------------------
// SclL1T
// 
// Data structure for bcounter values of LHCFL1T.
// This new counters have been implemented at LHCFL1T v1.3.
// This data is taken at same time as A1Scl and A2Scl.
// But to avoid to modify the data structure of A1Scl and A2Scl,
// this new class was implemented.
//
// DATA FORMAT:  (16 Jun. 2010 by H.MENJO)
//  - int    run                          (Run Number)
//  - int    number                       (Event Number)
//  - unsinged int  time[1]               (Time [0]:sec)
//  - unsigned int  bcounters[NCOUNTERS]  (BCounter values [20])
//      Channel List
//      [0]  :  FC "AND" BPTX in the 1st LHC backet. 
//      [1]  :  FC "AND" BPTX in the 2nd LHC backet. 
//      ...
//      [19] :  FC "AND" BPTX in the 20th LHC backet. 
//
//----------------------------------------------------------

#if !defined(__CINT__)
ClassImp(SclL1T);
#endif

const int SclL1T::NCOUNTERS;

// ***********************************************************
// ***  SclL1T::clear     ************************************
// ***********************************************************
int  SclL1T::clear(){
  // clear all data
  
  run = 0;
  number = 0;

  time[0] = 0;

  for(int i=0;i<NCOUNTERS;i++){
    bcounters[i] = 0;
  }
  
  return OK;
}

// ***********************************************************
// ***  SclL1T::copy      ************************************
// ***********************************************************
int  SclL1T::copy(SclL1T* d){
  // Copy data, name and title of "d" to "this"
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}


// ***********************************************************
// ***  SclL1T::copydata  ************************************
// ***********************************************************
int  SclL1T::copydata(SclL1T* d){
  // Copy only data of "d" to "this"

  run      = d->run;
  number   = d->number;

  time[0] = d->time[0];

  for(int i=0;i<NCOUNTERS;i++){
    bcounters[i] = d->bcounters[i];
  }

  return OK;
}

#endif
