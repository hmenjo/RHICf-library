#ifndef __A1CAL1TOCAL2_CPP__
#define __A1CAL1TOCAL2_CPP__

#include "A1Cal1ToCal2.h"

//----------------------------------------------------------------------
//
//  This class is for convertion of the data type from
//  A1Cal1 to A1Cal2. In this convertion, the adc value
//  of A1Cal2::cal are calcurated from "high range" adc value of
//  each channnel, if the "low range" adc value is over the
//  threshold (default 3700). if you want to use this adc
//  calculation in the convertion, you should set
//  use_adcrange parameter to 0 by UseADCRange().
//  easy way:
//   UseADCRange(true);
//   (Pedestal subtraction)
//   Convert(cal1,cal2,pede);
//  In this way, the low range adc values of "cal1+pede"
//  are used as the discrimination parameters for the adc
//  calculations. The pede argument don't affect without this
//  adc calculation.
//
//  exact way:
//   UseADCRange(false);
//   CalculateADC(cal1);
//   (Pedestal subtraction)
//   Convert(cal1,cal2);
//  if you don't mind the pedestal fluctuation of adc
//  this way give more exact result of adc calculation.
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  15 Oct. 08: Added use_adcrange parameter and                 
//              CalculateADC(A1Cal1* cal1) by H.MENJO  
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically.
//-----------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(A1Cal1ToCal2);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstring>
using namespace std;

#include "A1Cal2M.h"

const double  A1Cal1ToCal2::DEFAULT_THRESHOLD = 3700.;
const char*   A1Cal1ToCal2::DEFAULT_ADCRANGE_FILE = "./config/adcrange.dat";
const int     A1Cal1ToCal2::ADC_OVERRANGE;
const int     A1Cal1ToCal2::SCIFI_OVERRANGE;

// *******   A1Cal1ToCal2::Init  ****************************
int A1Cal1ToCal2::Init(){
  Initialize();
  adcrange.ReadFile((char*)DEFAULT_ADCRANGE_FILE);
  return OK;
}

// *******   A1Cal1ToCal2::Initialize  **********************
int A1Cal1ToCal2::Initialize(){
  defult_pede.clear();
  use_adcrange = true;
  SetADCRangeThreshold(DEFAULT_THRESHOLD);
  return OK;
}

// *******   A1Cal1ToCal2::ReadADCRangeTable  ***************
int A1Cal1ToCal2::ReadADCRangeTable(char* file){
  adcrange.ReadFile(file);
  return OK;
}

// *******    A1Cal1ToCal2::SetADCRangeThreshold ************
int  A1Cal1ToCal2::SetADCRangeThreshold(double th){
  threshold = th;
  adcrange.SetThresold(threshold);
  return OK;
}

// *******   A1Cal1ToCal2::Convert  *************************
int A1Cal1ToCal2::Convert(A1Cal1* cal1, A1Cal2* cal2, A1Cal1* pede){
  if(pede==0){
    pede =  &defult_pede;
  }
  
  // for event informations
  cal2->run = cal1->run;
  cal2->number = cal1->number;
  cal2->gnumber = cal1->gnumber;
  cal2->time[0] = cal1->time[0];
  cal2->time[1] = cal1->time[1];
  
  // for Calorimeters
  double lowrange=0.;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(use_adcrange==true){
	lowrange = cal1->cal[it][il][0]+pede->cal[it][il][0];
	if(lowrange < threshold){
	  cal2->cal[it][il] = cal1->cal[it][il][0];
	}
	else{
	  cal2->cal[it][il] 
	    = adcrange.GetParameter(it,il,1)*cal1->cal[it][il][1];
	}
      }
      else{
	cal2->cal[it][il] = cal1->cal[it][il][0];
      }
    }
  }

  // Scifi 
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<20;ich++){
	cal2->scifi0[il][ixy][ich] = cal1->scifi0[il][ixy][ich];
      }
      
      for(int ich=0;ich<40;ich++){
	cal2->scifi1[il][ixy][ich] = cal1->scifi1[il][ixy][ich];
      }
      
    }
  }

  // for flags
  for(int i=0;i<3;i++){ cal2->flag[i] = cal1->flag[i]; }

  
  // ++++++++++++++++++++++++++++++++++++++++++++++
  // +++++       IF cal2 is "A1Cal2M"         +++++
  // ++++++++++++++++++++++++++++++++++++++++++++++
  if(strcmp(cal2->ClassName(),"A1Cal2M")==0){
    A1Cal2M* cal2m = (A1Cal2M*) cal2;
    // for TDC
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	cal2m->tdc0[ich][ihit]     = cal1->tdc0[ich][ihit];
	cal2m->tdc0flag[ich][ihit] = cal1->tdc0flag[ich][ihit];
      }
    }
    // for Scaler
    for(int i=0;i<16;i++){ cal2m->scl0[i] = cal1->scl0[i];}
    
    // for Counter 
    for(int i=0;i<35;i++){ cal2m->counter[i] = cal1->counter[i];}
  
    // for  FIFO Counter 
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	cal2m->fifocounter[ich][ib]=cal1->fifocounter[ich][ib];
      }
    } 
  }

  return OK;
} 

// *******   A1Cal1ToCal2::InverseConvert  ******************
int A1Cal1ToCal2::InverseConvert(A1Cal2* cal2, A1Cal1* cal1, A1Cal1* pede){
  if(pede==0){
    pede = &defult_pede;
  }
  
  // initialize cal1
  cal1->clear();

  // for event informations
  cal1->run = cal2->run;
  cal1->number = cal2->number;
  cal1->gnumber = cal2->gnumber;
  cal1->time[0] = cal2->time[0];
  cal1->time[1] = cal2->time[1];
  
  // for Calorimeters
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal1->cal[it][il][0] = cal2->cal[it][il]; 
      cal1->cal[it][il][1] 
	= cal2->cal[it][il]/adcrange.GetParameter(it,il,1);
      if(use_adcrange==true){
	if(cal1->cal[it][il][0]+pede->cal[it][il][0]>threshold){
	  cal1->cal[it][il][0] = 8000.-pede->cal[it][il][0];
	}
	if(cal1->cal[it][il][1]+pede->cal[it][il][1]>threshold){
	  cal1->cal[it][il][1] = 8000.-pede->cal[it][il][1];
	}
      }
    }
  }

  // Scifi 
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<20;ich++){
	cal1->scifi0[il][ixy][ich] = cal2->scifi0[il][ixy][ich];
      }
      
      for(int ich=0;ich<40;ich++){
	cal1->scifi1[il][ixy][ich] = cal2->scifi1[il][ixy][ich];
      }
      
    }
  }

  // for flags
  for(int i=0;i<3;i++){ cal1->flag[i] = cal2->flag[i]; }

  
  // ++++++++++++++++++++++++++++++++++++++++++++++
  // +++++       IF cal2 is "A1Cal2M"         +++++
  // ++++++++++++++++++++++++++++++++++++++++++++++
  if(strcmp(cal2->ClassName(),"A1Cal2M")==0){
    A1Cal2M* cal2m = (A1Cal2M*) cal2;
    // for TDC
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	cal1->tdc0[ich][ihit]     = cal2m->tdc0[ich][ihit];
	cal1->tdc0flag[ich][ihit] = cal2m->tdc0flag[ich][ihit];
      }
    }
    // for Scaler
    for(int i=0;i<16;i++){ cal1->scl0[i] = cal2m->scl0[i];}
    
    // for Counter 
    for(int i=0;i<35;i++){ cal1->counter[i] = cal2m->counter[i];}
  
    // for  FIFO Counter 
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	cal1->fifocounter[ich][ib] = cal2m->fifocounter[ich][ib];
      }
    } 
  }


  return OK;
} 

int A1Cal1ToCal2::CalculateADC(A1Cal1* cal1){
  // for Calorimeters
  int iadc=0;
  for(int it=0;it<2;it++){
    if(it==0) iadc=0;
    if(it==1) iadc=1;
    for(int il=0;il<16;il++){
      if( cal1->cal[it][il][0] > threshold){
	cal1->cal[it][il][0] 
	  = adcrange.Get(iadc,il,
			 cal1->cal[it][il][0],
			 cal1->cal[it][il][1]);
      }
    }
  }
  return OK;
}

int A1Cal1ToCal2::CheckADCOverRange(A1Cal1* cal1){
  int nch=0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(cal1->cal[it][il][1] > 4096){nch++;}
    }
  }
  return nch;
}

#endif
