#ifndef __RAWA1_PP2015_CPP__
#define __RAWA1_PP2015_CPP__

#include "A1Raw_pp2015.h"

//----------------------------------------------------------------------
// A1Raw_pp2015
//
// Data Format for the operation at p-p collisions in 2015
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - unsigned int time[2]
//      CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 25mm Cal.
//      This array contains 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[64] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contains 16ch*2ranges*2events 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      ADC values of FC2 (4ch), Laser Monitor installed in detector (1ch),
//      Monitoring noize (1ch)
//      This array contains 16ch*2ranges*2 buffers
//      [0]: FC(0),High  [1]: FC(0), Low
//      [2]: FC(1),High  [3]: FC(1), Low
//      ....
//      ch.0  FC2(0)    ch.1  FC2(1)
//      ch.2  FC2(2)    ch.3  FC2(3)
//      ch.4  -         ch.5  -
//      ch.6  Noise     ch.7  Laser Monitor
//      ch.8-15 -
//
//  - unsigned short adc3[0] 
//      no use.
//
//  - unsigned short adc4[0] 
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
//      The array size should be more than N_A2_TDC
//        0-20 bit: TDC value
//       25-21 bit: Channel
//       26 bit   : falling/rising flag 
//      For detail, refer the manual of V1290
//
//  - unsigned int   gpio0[50]
//      Flags and Counter valuse of the trigger module
//      [0] : Event Flag
//      [1] : Discriminator Flag (This detector)
//      [2] : Discriminator Flag (The other detector)
//      [3-34] : Counter values 
//      the others : no use
//      Please refer the manual of the trigger module
//
//  - unsigned int   gpio1[0]
//      no use
//
//=====================================================================
// ++Logs
//  12 Mar 2015: Copied A2Raw_pPb2013 to A2Raw_pp2015 and modified 
//               for pPb by H.MENJO  
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(A1Raw_pp2015);
#endif

// *****************************************************************
// ***  A1Raw_pp2015  memory allocation of constant values.
// *****************************************************************
const int A1Raw_pp2015::c_N_TIME ;
const int A1Raw_pp2015::c_N_ADC0 ;
const int A1Raw_pp2015::c_N_ADC1 ;
const int A1Raw_pp2015::c_N_ADC2 ;
const int A1Raw_pp2015::c_N_ADC3 ;
const int A1Raw_pp2015::c_N_ADC4 ;
const int A1Raw_pp2015::c_N_CAD0 ;
const int A1Raw_pp2015::c_N_CAD1 ;
const int A1Raw_pp2015::c_N_TDC0 ;
const int A1Raw_pp2015::c_N_SCL0 ;
const int A1Raw_pp2015::c_N_GPI0 ;
const int A1Raw_pp2015::c_N_GPI1 ;
const int A1Raw_pp2015::c_N_SCIF ;

// ***********************************************************
// ***  A1Raw_pp2015::clear     *************************************
// ***********************************************************
int A1Raw_pp2015::clear(bankio option){ 
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  TIME,ADC0,ADC1,ADC2,ADC3,ADC4,CADC0,CADC1
  //  SCIFI,TDC0,SCL0,GPIO0,GPIO1
  // 
  // exp.  clear(A1Raw_pp2015::ADC0 & A1Raw_pp2015::SCIFI);
  
  run = 0;
  number = 0;
  gnumber = 0;

  if(option & TIME) for(int i=0;i<c_N_TIME;i++){ time[i] = 0;}
  if(option & ADC0) for(int i=0;i<c_N_ADC0;i++){ adc0[i] = 0;}
  if(option & ADC1) for(int i=0;i<c_N_ADC1;i++){ adc1[i] = 0;}
  if(option & ADC2) for(int i=0;i<c_N_ADC2;i++){ adc2[i] = 0;}
  if(option & ADC3) for(int i=0;i<c_N_ADC3;i++){ adc3[i] = 0;}
  //if(option & ADC4) for(int i=0;i<c_N_ADC4;i++){ adc4[i] = 0;}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ cadc0[i] = 0;}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ cadc1[i] = 0;}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ scifi[i] = 0;}
  if(option & TDC0) for(int i=0;i<c_N_TDC0;i++){ tdc0[i] = 0xFFFFFFFF;}
  if(option & SCL0) for(int i=0;i<c_N_SCL0;i++){ scl0[i] = 0;}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ gpio0[i] = 0;}
  //if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ gpio1[i] = 0;}
  
  return OK;
}


// ***********************************************************
// ***  A1Raw_pp2015::copy      *************************************
// ***********************************************************
int A1Raw_pp2015::copy(A1Raw_pp2015* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A1Raw_pp2015::copydata      *********************************
// ***********************************************************
int A1Raw_pp2015::copydata(A1Raw_pp2015* d,bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;

  if(option & TIME)  for(int i=0;i<c_N_TIME;i++){ this->time[i] = time[i];}
  if(option & ADC0)  for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] = d->adc0[i];}
  if(option & ADC1)  for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] = d->adc1[i];}
  if(option & ADC2)  for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] = d->adc2[i];}
  if(option & ADC3)  for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] = d->adc3[i];}
  //if(option & ADC4)  for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] = d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] = d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] = d->cadc1[i];}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ this->scifi[i] = d->scifi[i];}
  if(option & TDC0)  for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] = d->tdc0[i];}
  if(option & SCL0)  for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] = d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ this->gpio0[i] = d->gpio0[i];}
  //if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ this->gpio1[i] = d->gpio1[i];}

  return OK;
}

// ***********************************************************
// ***  A1Raw_pp2015::add       *************************************
// ***********************************************************
int A1Raw_pp2015::add(A1Raw_pp2015* d,bankio option){
  // Add data of "d" to this
  // (default option:ALL)

  if(option & TIME)  for(int i=0;i<c_N_TIME;i++){ this->time[i] += time[i];}
  if(option & ADC0)  for(int i=0;i<c_N_ADC0;i++){ this->adc0[i] += d->adc0[i];}
  if(option & ADC1)  for(int i=0;i<c_N_ADC1;i++){ this->adc1[i] += d->adc1[i];}
  if(option & ADC2)  for(int i=0;i<c_N_ADC2;i++){ this->adc2[i] += d->adc2[i];}
  if(option & ADC3)  for(int i=0;i<c_N_ADC3;i++){ this->adc3[i] += d->adc3[i];}
  //if(option & ADC4)  for(int i=0;i<c_N_ADC4;i++){ this->adc4[i] += d->adc4[i];}
  if(option & CADC0) for(int i=0;i<c_N_CAD0;i++){ this->cadc0[i] += d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<c_N_CAD1;i++){ this->cadc1[i] += d->cadc1[i];}
  if(option & SCIFI) for(int i=0;i<c_N_SCIF;i++){ this->scifi[i] += d->scifi[i];}
  if(option & TDC0)  for(int i=0;i<c_N_TDC0;i++){ this->tdc0[i] += d->tdc0[i];}
  if(option & SCL0)  for(int i=0;i<c_N_SCL0;i++){ this->scl0[i] += d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<c_N_GPI0;i++){ this->gpio0[i] += d->gpio0[i];}
  //if(option & GPIO1) for(int i=0;i<c_N_GPI1;i++){ this->gpio1[i] += d->gpio1[i];}

  return OK;
}

#endif
