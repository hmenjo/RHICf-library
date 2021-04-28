#ifndef __RHICFRAW_OP2017_CPP__
#define __RHICFRAW_OP2017_CPP__

#include "RHICfRaw_Op2017.h"

//----------------------------------------------------------------------
// RHICfRaw_Op2017
//
// Data Format for the RHICf operation in 2017 
//
// DATA FORMAT:  (Updated 29 Sep 2016 by H.MENJO)
//  - unsigned int time[2]
//     CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned int trgm[1]
//     Token + flag
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 20mm Cal.
//      This array contain 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[32] (CAEN V965)
//      ADC values for the PMTs of 40mm Cal.
//      This array contain 16ch*2ranges
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      Laser Monitor installed inside detector (1ch),
//      Monitoring noize (1ch)
//      This array contains 16ch*2ranges*2 buffers
//      ch.0  Laser Monitor    ch.1  -
//      ch.2  -                ch.3  -
//      ch.4  Noise            ch.5  -
//      ch.6  -                ch.7  -
//      ch.8-15 -
//
//  - unsigned short adc3[0] 
//      not used 
//
//  - unsigned short adc4[0] 
//      not used
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short scifi[512] (SciFi readout board)
//      ADC values of SciFi.
//      The arrangement of data is complicated.
//      Please refer "xxxxx.dat"
//
//  - unsigned int   tdc0[256] (LeCroy1171)
//      Data have the format of the buffer of CAEN V1290
//      The array size should be more than N_A1_TDC0.
//        0-20 bit: TDC value
//       25-21 bit: Channel
//       26 bit   : falling/rising flag 
//      For detail, refer the manual of V1290
//
//  - unsigned int   gpio0[17]
//      Flags and Counter valuse of the trigger module
//      [0] : Event Flag
//      [1] : Discriminator Flag 
//      [2-16] : Counter values
//      Please refer the manual of the trigger module
//
//  - unsigned int   gpio1[15]
//      Flags, Counter values, Fifo counter of the GPIO( RHICF_GPIO )
//      [0] : Event Flag
//      [1-6] : Counter values
//      [7-14]: Fifo counter values
//
//=====================================================================
// ++Logs
//  12 Mar 2016 : Copied  Arm1_pp2015 to RHICfRaw_Op2017 and modified
//                by Menjo
//  14 Feb 2017 : added trgm and change array size of gpi0 from 17 -> 19
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(RHICfRaw_Op2017);
#endif

// *****************************************************************
// ***  RHICfRaw_Op2017  memory allocation of constant values.
// *****************************************************************
const int RHICfRaw_Op2017::c_N_TIME ;
const int RHICfRaw_Op2017::c_N_TRGM ;
const int RHICfRaw_Op2017::c_N_ADC0 ;
const int RHICfRaw_Op2017::c_N_ADC1 ;
const int RHICfRaw_Op2017::c_N_ADC2 ;
const int RHICfRaw_Op2017::c_N_ADC3 ;
const int RHICfRaw_Op2017::c_N_ADC4 ;
const int RHICfRaw_Op2017::c_N_CAD0 ;
const int RHICfRaw_Op2017::c_N_CAD1 ;
const int RHICfRaw_Op2017::c_N_TDC0 ;
const int RHICfRaw_Op2017::c_N_SCL0 ;
const int RHICfRaw_Op2017::c_N_GPI0 ;
const int RHICfRaw_Op2017::c_N_GPI1 ;
const int RHICfRaw_Op2017::c_N_SCIF ;

// ***********************************************************
// ***  RHICfRaw_Op2017::clear     *************************************
// ***********************************************************
int RHICfRaw_Op2017::clear(bankio option){ 
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  TIME,ADC0,ADC1,ADC2,ADC3,ADC4,CADC0,CADC1
  //  SCIFI,TDC0,SCL0,GPIO0,GPIO1,TRGM
  // 
  // exp.  clear(RHICfRaw_Op2017::ADC0 & RHICfRaw_Op2017::SCIFI);
  
  run = 0;
  number = 0;
  gnumber = 0;

  if(option & TIME) for(int i=0;i<c_N_TIME;i++){ time[i] = 0;}
  if(option & TRGM) for(int i=0;i<c_N_TRGM;i++){ trgm[i] = 0;}
  if(option & ADC0) for(int i=0;i<c_N_ADC0;i++){ adc0[i] = 0;}
  if(option & ADC1) for(int i=0;i<c_N_ADC1;i++){ adc1[i] = 0;}
  if(option & ADC2) for(int i=0;i<c_N_ADC2;i++){ adc2[i] = 0;}
  //if(option & ADC3) for(int i=0;i<c_N_ADC3;i++){ adc3[i] = 0;}
  //if(option & ADC4) for(int i=0;i<c_N_ADC4;i++){ adc4[i] = 0;}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ cadc0[i] = 0;}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ cadc1[i] = 0;}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ scifi[i] = 0;}
  if(option & TDC0) for(int i=0;i<c_N_TDC0;i++){ tdc0[i] = 0xFFFFFFFF;}
  //if(option & SCL0) for(int i=0;i<c_N_SCL0;i++){ scl0[i] = 0;}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ gpio0[i] = 0;}
  if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ gpio1[i] = 0;}
  
  return OK;
}


// ***********************************************************
// ***  RHICfRaw_Op2017::copy      *************************************
// ***********************************************************
int RHICfRaw_Op2017::copy(RHICfRaw_Op2017* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  RHICfRaw_Op2017::copydata      *********************************
// ***********************************************************
int RHICfRaw_Op2017::copydata(RHICfRaw_Op2017* d,bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;

  if(option & TIME)  for(int i=0;i<c_N_TIME;i++){ this->time[i] = time[i];}
  if(option & TRGM)  for(int i=0;i<c_N_TRGM;i++){ this->trgm[i] = trgm[i];}
  if(option & ADC0)  for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] = d->adc0[i];}
  if(option & ADC1)  for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] = d->adc1[i];}
  if(option & ADC2)  for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] = d->adc2[i];}
  //if(option & ADC3)  for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] = d->adc3[i];}
  //if(option & ADC4)  for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] = d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] = d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] = d->cadc1[i];}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ this->scifi[i] = d->scifi[i];}
  if(option & TDC0)  for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] = d->tdc0[i];}
  //if(option & SCL0)  for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] = d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ this->gpio0[i] = d->gpio0[i];}
  if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ this->gpio1[i] = d->gpio1[i];}

  return OK;
}

// ***********************************************************
// ***  RHICfRaw_Op2017::add       *************************************
// ***********************************************************
int RHICfRaw_Op2017::add(RHICfRaw_Op2017* d,bankio option){
  // Add data of "d" to this
  // (default option:ALL)

  if(option & TIME)  for(int i=0;i<c_N_TIME;i++){ this->time[i] += time[i];}
  if(option & TRGM)  for(int i=0;i<c_N_TRGM;i++){ this->trgm[i] += trgm[i];}
  if(option & ADC0)  for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] += d->adc0[i];}
  if(option & ADC1)  for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] += d->adc1[i];}
  if(option & ADC2)  for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] += d->adc2[i];}
  //if(option & ADC3)  for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] += d->adc3[i];}
  //if(option & ADC4)  for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] += d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] += d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] += d->cadc1[i];}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ this->scifi[i] += d->scifi[i];}
  if(option & TDC0)  for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] += d->tdc0[i];}
  //if(option & SCL0)  for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] += d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ this->gpio0[i] += d->gpio0[i];}
  if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ this->gpio1[i] += d->gpio1[i];}

  return OK;
}

#endif
