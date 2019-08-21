#ifndef __RAWL1T_CPP__
#define __RAWL1T_CPP__

#include "RawL1T.h"

//----------------------------------------------------------
// RawL1T
// 
// Data structure for counter values of LHCFL1T.
// This new counters have been implemented at LHCFL1T v1.3. 
// This data is taken at same time as A1Raw. 
// But to avoid to modify the data structure of A1Raw, 
// this new class was prepared.  
// 
// DATA FORMAT:  (16 Jun. 2010 by H.MENJO)
//  - int    run             (Run Number)
//  - int    gnumber         (General Event Number)
//  - int    number          (Event Number)
//
//  - unsigned int time[2]
//     CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned int gpio2     (Counter values in LHCFL1T)
//     Channel List:
//      [0]  :   BPTX1
//      [1]  :   BPTX2
//      [2]  :   BPTX1 "AND" BPTX2
//      [3]  :   BPTX1 "AND" BPTX2 (displaced crossing bunches are also counted)
//      [4]  :   A1_L1T       (Arm1 L1T)
//      [5]  :   A2_L1T       (Arm2 L1T)
//      [6]  :   A1_L1T_ENB   (Arm1 L1T "AND" ENABLE)
//      [7]  :   A2_L1T_ENB   (Arm2 L1T "AND" ENABLE)
//      [8]  :   A1_LASER     (Arm1 Laser)
//      [9]  :   A2_LASER     (Arm2 Laser)
//      [10] :   A1_L2TEXT3   (Arm1 L2TEXT)
//      [11] :   A2_L2TEXT3   (Arm2 L2TEXT)
//      [12] :   A1_L2TEXT    (Arm1 L2TEXT "AND" ENABLE)
//      [13] :   A2_L2TEXT    (Arm2 L2TEXT "AND" ENABLE)
//    *) ENABLE signel is selected by a register in LHCFL1T. 
//       In case of common trigger of Arm1 and Arm2, 
//       ENABLE is  A1_ENABLE  "AND"  A2_ENABLE.
// 
//----------------------------------------------------------

#if !defined(__CINT__)
ClassImp(RawL1T);
#endif

const int RawL1T::NCOUNTERS;

// ***********************************************************
// ***  RawL1T::clear     ************************************
// ***********************************************************
int  RawL1T::clear(){
  // clear all data
  
  run = 0;
  number = 0;
  gnumber = 0;
  
  time[0] = 0;
  time[1] = 0;
 
  for(int i=0;i<NCOUNTERS;i++){
    gpio2[i] = 0;
  }
  
  return OK;
}

// ***********************************************************
// ***  RawL1T::copy      ************************************
// ***********************************************************
int  RawL1T::copy(RawL1T* d){
  // Copy data, name and title of "d" to "this"
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}


// ***********************************************************
// ***  RawL1T::copydata  ************************************
// ***********************************************************
int  RawL1T::copydata(RawL1T* d){
  // Copy only data of "d" to "this"

  run      = d->run;
  number   = d->number;
  gnumber  = d->gnumber;
  
  time[0] = d->time[0];
  time[1] = d->time[1];
  
  for(int i=0;i<NCOUNTERS;i++){
    gpio2[i] = d->gpio2[i];
  }

  return OK;
}

#endif
