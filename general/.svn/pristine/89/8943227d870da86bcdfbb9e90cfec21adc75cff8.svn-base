#ifndef __A2CAL2M_CPP__
#define __A2CAL2M_CPP__

#include "A2Cal2M.h"

//----------------------------------------------------------------------
// A2Cal2M  : Modified A2Cal2
//
//  This class has additional variables, TDC scaler and counter of GPIOs, 
//  which are same as "A2Cal1". 
//
// 
// +++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  23 Nov. 10: First editted by H.MENJO
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Cal2M);
#endif

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

// -----------------------------------------------------------
// -----                  A2Cal2M::clear                 -----       
// -----------------------------------------------------------
int A2Cal2M::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option 
  // 
  
  // cerr << "A2Cal2M::clear" << endl;

  // Clear main variables 
  A2Cal2::clear(option);

  // Clear TDC
  if((option & TDC0) || (option & TDC0FLAG)){
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	if(option & TDC0)     tdc0[ich][ihit] = 0.;
	if(option & TDC0FLAG) tdc0flag[ich][ihit] = -1;
      }
    }
  }
  
  // Clear Scaler
  if(option & SCL0) for(int i=0;i<16;i++){ scl0[i] = 0.;}
  
  // Clear Counter
  if(option & COUNTER) for(int i=0;i<35;i++) {counter[i]=0;}
  
  // Clear FIFO Counter
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	fifocounter[ich][ib]=0;
      }
    } 
  }  

  return OK;
}

// -----------------------------------------------------------
// -----       A2Cal2M::copy copydata For A2Cal2         -----       
// -----------------------------------------------------------
int A2Cal2M::copy(A2Cal2* d, bankio option){ 
  // This is a virtual function for A2Cal2*. 
  // if d refers A2Cal2,  call A2Cal2::copy(A2Cal2* ,bankio);
  // if d refers A2Cal2M, call A2Cal2M::copy(A2Cal2M* ,bankio);
  if(strcmp(d->ClassName(),"A2Cal2")==0)  return A2Cal2::copy(d,option);
  if(strcmp(d->ClassName(),"A2Cal2M")==0) return A2Cal2M::copy((A2Cal2M*)d,option);
  return OK;
}

// -----------------------------------------------------------
// -----       A2Cal2M::copy copydata For A2Cal2M        -----       
// -----------------------------------------------------------
int A2Cal2M::copy(A2Cal2M* d, bankio option){ 
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)

  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d, option);
}

// -----------------------------------------------------------
// -----           A2Cal2M::copydata For A2Cal2          -----                      
// -----------------------------------------------------------
int A2Cal2M::copydata(A2Cal2* d, bankio option){ 
  // This is a virtual function for A2Cal2*. 
  // if d refers A2Cal2,  call A2Cal2::copydata(A2Cal2* ,bankio);
  // if d refers A2Cal2M, call A2Cal2M::copyata(A2Cal2M* ,bankio);
  if(strcmp(d->ClassName(),"A2Cal2")==0)  return A2Cal2::copydata(d,option);
  if(strcmp(d->ClassName(),"A2Cal2M")==0) return A2Cal2M::copydata((A2Cal2M*)d,option);
  return OK;
}

// -----------------------------------------------------------
// -----           A2Cal2M::copydata For A2Cal2M         -----                      
// -----------------------------------------------------------
int A2Cal2M::copydata(A2Cal2M* d, bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)

  A2Cal2::copydata(d,option);
  
  // Copy TDC   
  if((option & TDC0) || (option & TDC0FLAG)){
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	if(option & TDC0)     this->tdc0[ich][ihit] = d->tdc0[ich][ihit];
	if(option & TDC0FLAG) this->tdc0flag[ich][ihit] = d->tdc0flag[ich][ihit];
      }
    }
  }

  // Copy Scaler
  if(option & SCL0) for(int i=0;i<16;i++){ this->scl0[i] = d->scl0[i];}

  // Copy Counter 
  if(option & COUNTER) for(int i=0;i<35;i++) {this->counter[i]=d->counter[i];}
  
  // Copy FIFO Counter 
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]=d->fifocounter[ich][ib];
      }
    } 
  }
  
  return OK;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ CONVERSION OF SCL0 VALUE                            +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double A2Cal2M::clk(){
  //  scl0[1]*2^24+scl0[0]

  const int b24 = 16777216;
  return ((double)scl0[1])*b24 + scl0[0];  
}

double A2Cal2M::bptx1(){
  //  scl0[3]*2^24+scl0[2]
  
  const int b24 = 16777216;
  return ((double)scl0[3])*b24 + scl0[2]; 
}

double A2Cal2M::bptx2(){
  //  scl0[5]*2^24+scl0[4]

  const int b24 = 16777216;
  return ((double)scl0[5])*b24 + scl0[4]; 
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  USEFUL FUNCTIONS                                +++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++           Check Bunch Crossing                   +++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int A2Cal2M::CheckBunchCrossing(){
  // Return bunch crossing configuration of this event.
  // Whether the event is with bunch crossing or not can be checked by several ways,
  //   1) BPTX flag, the easiest way but it cannot identify displaced bunch crossing. 
  //   2) Bunch ID,  if you know the filling scheme in this fill,
  //                 you can check whether the bunch crosses or not by bunch ID
  //   3) TDC,       TDC values of BPTX's also help to identify bunch crossing
  //                 event by event. This gives correct results.
  // This function take the mathod "3)"
  // 
  // Return values 
  //   if bunch crossing,                  return 1,
  //   if non-bunch crossing (Beam1),      return 2,
  //   if displaced beam crossing,         return 3,
  //   if non-bunch crossing (Beam2),      return 4,
  //   else (unknow or simulation)         return 0
  
  // Get TDC values
  double bptx1 = GetTDCofBPTX1();
  double bptx2 = GetTDCofBPTX2();
  
  // Check No TDC values or Simulation
  if(bptx1 > 0. && bptx2 > 0.){ return A2Cal2M::UNKNOWN;}
  
  // Check non-bunch crossing
  // Only Beam1 (coming from IP to Arm2 detector)
  if(bptx1 < 0. && bptx2 > 0.){ return A2Cal2M::NONCROSSING;}
  // Only Beam2 (out going from Arm2 detector to IP)
  if(bptx1 > 0. && bptx2 < 0.){ return A2Cal2M::NONCROSSING2;}  
  
  // Check displaced bunch crossing 
  if(fabs( bptx1-bptx2 ) > 50.){ return A2Cal2M::DISPLACED;}
  
  return A2Cal2M::CROSSING;
}

double A2Cal2M::GetTDCofBPTX1(){
  // Get TDC values of BPTX1 in the possible period for this event.
  // For the moment, the period is set to from -1300ns to -800ns.
  // This must be called after pedestal subtraction. 
  // it means that 0 is equal to the timing of L3T trigger.
  // if no hit, return +1. 
  const int ch = 2;
  for(int ih=0;ih<16;ih++){
    if(this->tdc0flag[ch][ih]<0) break;
    if(this->tdc0[ch][ih] > -1300. && this->tdc0[ch][ih] < -800.){
      return this->tdc0[ch][ih];
    }
  }
  return 1.;
}

double A2Cal2M::GetTDCofBPTX2(){
  // Get TDC value of BPTX2 in the possible period for this event.
  // For the moment, the period is set to from -1300ns to -800ns. 
  // This must be called after pedestal subtraction. 
  // it means that 0 is equal to the timing of L3T trigger. 
  // if no hit, return +1. 
  const int ch = 3;
  for(int ih=0;ih<16;ih++){ 
    if(this->tdc0flag[ch][ih]<0) break;
    if(this->tdc0[ch][ih] > -1300. && this->tdc0[ch][ih] < -800.){
      return this->tdc0[ch][ih];
    }
  }
  return  1.;
}



#endif
