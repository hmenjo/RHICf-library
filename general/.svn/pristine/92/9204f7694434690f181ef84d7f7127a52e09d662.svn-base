#ifndef __A2RAW_PPB2013_CPP__
#define __A2RAW_PPB2013_CPP__

#include "A2Raw_pPb2013.h"

//----------------------------------------------------------------------
// A1Raw2_pPb2013
//
// Data Format for the operation at p-Pb collisions in 2013
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - unsigned int time[2]
//      CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 25mm Cal.
//      This array contain 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[64] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contain 16ch*2ranges*2events 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      ADC values of FC (4ch), Laser (2ch), Mornitering noise(3ch)
//      This array contain 16ch*2ranges*2events 
//      [0]: FC(0),High  [1]: FC(0), Low
//      [2]: FC(1),High  [3]: FC(1), Low
//      ....
//      ch.0  FC(0)    ch.1  FC(1)
//      ch.2  FC(2)    ch.3  FC(3)
//      ch.4  -        ch.5  -
//      ch.6  Laser R  ch.7  Laser L
//      ch.8  Noise(0) ch.9  Noise(1)
//      ch.10 Noise(2) ch.11 -
//      ch.12-15 -
//
//  - unsigned short adc3[0] (LeCroy 1182)
//      no use.
//
//  - unsigned short adc4[0] (LeCroy 1182)
//      no use.
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short arm2[14280] (Silicon readout board)
//      Silicon data
//      The arrangement of data is complicated.
//      Please refer the manual of silicon.
//
//  - unsigned int   tdc0[256] (CAEN V1290)
//      Data have the format of the buffer of CAEN V1290
//      The array size should be more than c_N_TDC0
//       0-15bit  :  Value (1count=1nsec)
//       16bit    :  phase
//       17-20bit :  channel
//       21bit    :  valid flag
//       23bit    :  end flag
//      For detail, refer the manual of this module.
//
//  - unsigned int   gpio0[17]
//      Flags and Counter valuse of LHCFLOGIC
//      [0] : Event Flag
//      [1] : Discri Flag
//      the others : counter valuse
//      Please refer the manual of LHCFLOGIC
//
//  - unsigned int   gpio1[27]
//      Flag and Counter valuse of LHCFCOUNTER
//      [0] : Event Flag
//      [1-19]  : counter valuse
//      [20-27] : fifo counter values
//      Please refer the manual of LHCFCOUNTER
//
//=====================================================================
// ++Logs
//  15 Dec 2012: Copied A2Raw to A2Raw_pPb2013 and modified for pPb 
//               by H.MENJO
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Raw_pPb2013);
#endif

// *****************************************************************
// ***  A2Raw_pPb2013  memory allocation of constant values.
// *****************************************************************
const int A2Raw_pPb2013::c_N_TIME ;
const int A2Raw_pPb2013::c_N_ADC0 ;
const int A2Raw_pPb2013::c_N_ADC1 ;
const int A2Raw_pPb2013::c_N_ADC2 ;
const int A2Raw_pPb2013::c_N_ADC3 ;
const int A2Raw_pPb2013::c_N_ADC4 ;
const int A2Raw_pPb2013::c_N_CAD0 ;
const int A2Raw_pPb2013::c_N_CAD1 ;
const int A2Raw_pPb2013::c_N_TDC0 ;
const int A2Raw_pPb2013::c_N_SCL0 ;
const int A2Raw_pPb2013::c_N_GPI0 ;
const int A2Raw_pPb2013::c_N_GPI1 ;
const int A2Raw_pPb2013::c_N_ARM2 ;

// ***********************************************************
// ***  A2Raw_pPb2013::clear     *****************************
// ***********************************************************
int A2Raw_pPb2013::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  TIME,ADC0,ADC1,ADC2,ADC3,ADC4,CADC0,CADC1
  //  ARM2,TDC0,SCL0,GPIO0,GPIO1
  // 
  // exp.  clear(A2Raw_pPb2013::ADC0 & A2Raw_pPb2013::ARM2);

  run = 0;
  number = 0;
  gnumber = 0;

  if(option & TIME)  for(int i=0;i<c_N_TIME;i++){ time[i] = 0;}
  if(option & ADC0)  for(int i=0;i<c_N_ADC0;i++){ adc0[i] = 0;}
  if(option & ADC1)  for(int i=0;i<c_N_ADC1;i++){ adc1[i] = 0;}
  if(option & ADC2)  for(int i=0;i<c_N_ADC2;i++){ adc2[i] = 0;} 
  if(option & ADC3)  for(int i=0;i<c_N_ADC3;i++){ adc3[i] = 0;} 
  if(option & ADC4)  for(int i=0;i<c_N_ADC4;i++){ adc4[i] = 0;}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ cadc0[i] = 0;}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ cadc1[i] = 0;}
  if(option & TDC0)  for(int i=0;i<c_N_TDC0;i++){ tdc0[i] = 0xFFFFFFFF;}
  if(option & SCL0)  for(int i=0;i<c_N_SCL0;i++){ scl0[i] = 0;}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ gpio0[i] = 0;}
  if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ gpio1[i] = 0;}
  if(option & ARM2)  for(int i=0;i<c_N_ARM2;i++){ arm2[i] = 0;}

  return OK;
}

// ***********************************************************
// ***  A2Raw_pPb2013::copy      *****************************
// ***********************************************************
int A2Raw_pPb2013::copy(A2Raw_pPb2013* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A2Raw_pPb2013::copydata      *************************
// ***********************************************************
int A2Raw_pPb2013::copydata(A2Raw_pPb2013* d,bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;
  
  if(option & TIME) for(int i=0;i<c_N_TIME;i++){ this->time[i] = d->time[i];}
  if(option & ADC0) for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] = d->adc0[i];}
  if(option & ADC1) for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] = d->adc1[i];}
  if(option & ADC2) for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] = d->adc2[i];} 
  if(option & ADC3) for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] = d->adc3[i];} 
  if(option & ADC4) for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] = d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] = d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] = d->cadc1[i];}
  if(option & TDC0) for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] = d->tdc0[i];}
  if(option & SCL0) for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] = d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ this->gpio0[i] = d->gpio0[i];}
  if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ this->gpio1[i] = d->gpio1[i];}
  if(option & ARM2) for(int i=0;i<c_N_ARM2;i++){ this->arm2[i] = d->arm2[i];}
  
  return OK;
}

// ***********************************************************
// ***  A2Raw_pPb2013::add       *****************************
// ***********************************************************
int A2Raw_pPb2013::add(A2Raw_pPb2013* d,bankio option){
  // Add data of "d" to this
  // (default option:ALL)
  
  if(option & TIME) for(int i=0;i<c_N_TIME;i++){ this->time[i] += d->time[i];}
  if(option & ADC0) for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] += d->adc0[i];}
  if(option & ADC1) for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] += d->adc1[i];}
  if(option & ADC2) for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] += d->adc2[i];} 
  if(option & ADC3) for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] += d->adc3[i];} 
  if(option & ADC4) for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] += d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] += d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] += d->cadc1[i];}
  if(option & TDC0) for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] += d->tdc0[i];}
  if(option & SCL0) for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] += d->scl0[i];}
  if(option & GPIO0) for(int i=2;i<c_N_GPI0;i++){ this->gpio0[i] += d->gpio0[i];}
  if(option & GPIO1) for(int i=1;i<c_N_GPI1;i++){ this->gpio1[i] += d->gpio1[i];}
  if(option & ARM2) for(int i=0;i<c_N_ARM2;i++){ this->arm2[i] += d->arm2[i];}
 
  return OK;
}
#endif
