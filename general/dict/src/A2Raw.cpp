#ifndef __A2RAW_CPP__
#define __A2RAW_CPP__

#include "A2Raw.h"

//----------------------------------------------------------------------
// A1Raw2
//
// Data structure for the raw data of Arm2.
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
//  - unsigned short adc1[32] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contain 16ch*2ranges 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[8] (LeCroy 1182)
//      ADC values for monitering event by event noise
//      This array contain 8ch
//      [0-2] 3 empty channels of preamp.
//      [3]   ADC value of no input channel
//      [4-7] no use
//
//  - unsigned short adc3[16] (LeCroy 1182)
//      no use.
//
//  - unsigned short adc4[16] (LeCroy 1182)
//      This array contain 8ch*2events
//      ADC values of laser monitor
//      [0] : Laser monitor-L
//      [1] : Laser monitor-R
//      [4-7] : channel 0-4 of Arm1 FC
//      [8-15]: adc values of a delayed gate.
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short arm2[512] (Silicon readout board)
//      Silicon data
//      The arrangement of data is complicated.
//      Please refer the manual of silicon.
//
//  - unsigned int   tdc0[64] (CAEN V1290)
//      Data have the format of the buffer of CAEN V1290
//      The array size should be more than N_A2_TDC0.
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
//  ?? ???. 08: First edited by H.MENJO             
//  21 Apr. 09: Fuction copy(A2Raw* ), copydata(A2Raw*),      
//              add(A2Raw) was added by H.MENJO.          
//  21 Apr. 09: "enum bank" added by H.MENJO
//  30 Oct. 09: Version 3. 
//              Modified the array size of tdc0 by H.MENJO
//              tdc0[N_A1_TDC0]  ->  tdc0[160]

//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Raw);
#endif

// ***********************************************************
// ***  A2Raw::clear     *************************************
// ***********************************************************
int A2Raw::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  TIME,ADC0,ADC1,ADC2,ADC3,ADC4,CADC0,CADC1
  //  ARM2,TDC0,SCL0,GPIO0,GPIO1
  // 
  // exp.  clear(A2Raw::ADC0 & A2Raw::ARM2);

  run = 0;
  number = 0;
  gnumber = 0;

  if(option & TIME)  for(int i=0;i<N_A2_TIME;i++){ time[i] = 0;}
  if(option & ADC0)  for(int i=0;i<N_A2_ADC0;i++){ adc0[i] = 0;}
  if(option & ADC1)  for(int i=0;i<N_A2_ADC1;i++){ adc1[i] = 0;}
  if(option & ADC2)  for(int i=0;i<N_A2_ADC2;i++){ adc2[i] = 0;} 
  if(option & ADC3)  for(int i=0;i<N_A2_ADC3;i++){ adc3[i] = 0;} 
  if(option & ADC4)  for(int i=0;i<N_A2_ADC4;i++){ adc4[i] = 0;}
  if(option & CADC0) for(int i=0;i<N_A2_CAD0;i++){ cadc0[i] = 0;}
  if(option & CADC1) for(int i=0;i<N_A2_CAD1;i++){ cadc1[i] = 0;}
  if(option & TDC0)  for(int i=0;i<N_A2_TDC0;i++){ tdc0[i] = 0xFFFFFFFF;}
  if(option & SCL0)  for(int i=0;i<N_A2_SCL0;i++){ scl0[i] = 0;}
  if(option & GPIO0) for(int i=0;i<N_A2_GPI0;i++){ gpio0[i] = 0;}
  if(option & GPIO1) for(int i=0;i<N_A2_GPI1;i++){ gpio1[i] = 0;}
  if(option & ARM2)  for(int i=0;i<N_A2_ARM2;i++){ arm2[i] = 0;}

  return OK;
}

// ***********************************************************
// ***  A2Raw::copy      *************************************
// ***********************************************************
int A2Raw::copy(A2Raw* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A2Raw::copydata      *********************************
// ***********************************************************
int A2Raw::copydata(A2Raw* d,bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;
  
  if(option & TIME) for(int i=0;i<N_A2_TIME;i++){ this->time[i] = d->time[i];}
  if(option & ADC0) for(int i=0;i<N_A2_ADC0;i++){ this->adc0[i] = d->adc0[i];}
  if(option & ADC1) for(int i=0;i<N_A2_ADC1;i++){ this->adc1[i] = d->adc1[i];}
  if(option & ADC2) for(int i=0;i<N_A2_ADC2;i++){ this->adc2[i] = d->adc2[i];} 
  if(option & ADC3) for(int i=0;i<N_A2_ADC3;i++){ this->adc3[i] = d->adc3[i];} 
  if(option & ADC4) for(int i=0;i<N_A2_ADC4;i++){ this->adc4[i] = d->adc4[i];}
  if(option & CADC0) for(int i=0;i<N_A2_CAD0;i++){ this->cadc0[i] = d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<N_A2_CAD1;i++){ this->cadc1[i] = d->cadc1[i];}
  if(option & TDC0) for(int i=0;i<N_A2_TDC0;i++){ this->tdc0[i] = d->tdc0[i];}
  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ this->scl0[i] = d->scl0[i];}
  if(option & GPIO0) for(int i=0;i<N_A2_GPI0;i++){ this->gpio0[i] = d->gpio0[i];}
  if(option & GPIO1) for(int i=0;i<N_A2_GPI1;i++){ this->gpio1[i] = d->gpio1[i];}
  if(option & ARM2) for(int i=0;i<N_A2_ARM2;i++){ this->arm2[i] = d->arm2[i];}
  
  return OK;
}

// ***********************************************************
// ***  A2Raw::add       *************************************
// ***********************************************************
int A2Raw::add(A2Raw* d,bankio option){
  // Add data of "d" to this
  // (default option:ALL)
  
  if(option & TIME) for(int i=0;i<N_A2_TIME;i++){ this->time[i] += d->time[i];}
  if(option & ADC0) for(int i=0;i<N_A2_ADC0;i++){ this->adc0[i] += d->adc0[i];}
  if(option & ADC1) for(int i=0;i<N_A2_ADC1;i++){ this->adc1[i] += d->adc1[i];}
  if(option & ADC2) for(int i=0;i<N_A2_ADC2;i++){ this->adc2[i] += d->adc2[i];} 
  if(option & ADC3) for(int i=0;i<N_A2_ADC3;i++){ this->adc3[i] += d->adc3[i];} 
  if(option & ADC4) for(int i=0;i<N_A2_ADC4;i++){ this->adc4[i] += d->adc4[i];}
  if(option & CADC0) for(int i=0;i<N_A2_CAD0;i++){ this->cadc0[i] += d->cadc0[i];}
  if(option & CADC1) for(int i=0;i<N_A2_CAD1;i++){ this->cadc1[i] += d->cadc1[i];}
  if(option & TDC0) for(int i=0;i<N_A2_TDC0;i++){ this->tdc0[i] += d->tdc0[i];}
  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ this->scl0[i] += d->scl0[i];}
  if(option & GPIO0) for(int i=2;i<N_A2_GPI0;i++){ this->gpio0[i] += d->gpio0[i];}
  if(option & GPIO1) for(int i=1;i<N_A2_GPI1;i++){ this->gpio1[i] += d->gpio1[i];}
  if(option & ARM2) for(int i=0;i<N_A2_ARM2;i++){ this->arm2[i] += d->arm2[i];}
 
  return OK;
}
#endif
