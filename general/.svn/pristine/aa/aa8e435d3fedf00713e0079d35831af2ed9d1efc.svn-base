#ifndef __A2CAL1TOCAL2_CPP__
#define __A2CAL1TOCAL2_CPP__

#include "A2Cal1ToCal2.h"

//----------------------------------------------------------------------
//  This class is for convertion of the data type from
//  A2Cal1 to A2Cal2. In this convertion, the adc value
//  of A2Cal2::cal are calcurated from "high range" adc value of
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
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  15 Oct. 08: Added use_adcrange parameter and
//              CalculateADC(A2Cal1* cal1) by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO.
//  23 Nov. 10: Modified Convert() and InverseConvert for A2Cal2M
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Cal1ToCal2);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstring>
using namespace std;

#include "A2Cal2M.h"

const double  A2Cal1ToCal2::DEFAULT_THRESHOLD = 3700.;
const char*   A2Cal1ToCal2::DEFAULT_ADCRANGE_FILE = "./config/adcrange.dat";
const int     A2Cal1ToCal2::ADC_OVERRANGE;
const int     A2Cal1ToCal2::SCIFI_OVERRANGE;

// *******   A2Cal1ToCal2::Init  ****************************
int A2Cal1ToCal2::Init(){
  Initialize();
  adcrange.ReadFile((char*)DEFAULT_ADCRANGE_FILE);
  return OK;
}

// *******   A2Cal1ToCal2::Initialize  **********************
int A2Cal1ToCal2::Initialize(){
  defult_pede.clear();
  use_adcrange = true;
  SetADCRangeThreshold(DEFAULT_THRESHOLD);
  return OK;
}

// *******   A2Cal1ToCal2::ReadADCRangeTable  ***************
int A2Cal1ToCal2::ReadADCRangeTable(char* file){
  adcrange.ReadFile(file);
  return OK;
}

// *******    A2Cal1ToCal2::SetADCRangeThreshold ************
int  A2Cal1ToCal2::SetADCRangeThreshold(double th){
  threshold = th;
  adcrange.SetThresold(threshold);
  return OK;
}

// *******   A2Cal1ToCal2::Convert  *************************
int A2Cal1ToCal2::Convert(A2Cal1* cal1, A2Cal2* cal2, A2Cal1* pede){
  if(pede==0){
    pede =  &defult_pede;
  }
  
  // for event informations
  cal2->run = cal1->run;
  cal2->number = cal1->number;
  cal2->gnumber = cal1->gnumber;
  cal2->time[0] = cal1->time[0];
  cal2->time[1] = cal1->time[1];
  
  // +++++ for Calorimeters +++++
  double lowrange=0.;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      lowrange = cal1->cal[it][il][0]+pede->cal[it][il][0];
      if(use_adcrange==true){
	if(lowrange < threshold){
	  cal2->cal[it][il] = cal1->cal[it][il][0];
	}
	else{
	  cal2->cal[it][il] 
	    = adcrange.GetParameter(2+it,il,1)*cal1->cal[it][il][1];
	}
      }
      else{
	cal2->cal[it][il] = cal1->cal[it][il][0];
      }
    }
  }
  
  // +++++ for flags +++++
  for(int i=0;i<3;i++){ cal2->flag[i] = cal1->flag[i]; }

  // +++++ for silicon +++++
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  cal2->silicon[il][ixy][istrip][isample]
	    =  cal1->silicon[il][ixy][istrip][isample];
	}
      }
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++
  // +++++       IF cal2 is "A2Cal2M"         +++++
  // ++++++++++++++++++++++++++++++++++++++++++++++
  if(strcmp(cal2->ClassName(),"A2Cal2M")==0){
    A2Cal2M* cal2m = (A2Cal2M*) cal2;
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

// *******   A2Cal1ToCal2::InverseConvert  ******************
int A2Cal1ToCal2::InverseConvert(A2Cal2* cal2, A2Cal1* cal1, A2Cal1* pede){
  if(pede==0){
    pede = &defult_pede;
  }
  // initalize cal1
  cal1->clear();

  // for event informations
  cal1->run = cal2->run;
  cal1->number = cal2->number;
  cal1->gnumber = cal2->gnumber;
  cal1->time[0] = cal2->time[0];
  cal1->time[1] = cal2->time[1];
  
  // +++++ for Calorimeters +++++
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

  // +++++ for flags +++++
  for(int i=0;i<3;i++){ cal1->flag[i] = cal2->flag[i]; }

  // +++++ for silicon +++++
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  cal1->silicon[il][ixy][istrip][isample]
	    =  cal2->silicon[il][ixy][istrip][isample];
	}
      }
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++
  // +++++       IF cal2 is "A2Cal2M"         +++++
  // ++++++++++++++++++++++++++++++++++++++++++++++
  if(strcmp(cal2->ClassName(),"A2Cal2M")==0){
    A2Cal2M* cal2m = (A2Cal2M*) cal2;
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

int A2Cal1ToCal2::CalculateADC(A2Cal1* cal1){
  int iadc=0;
  for(int it=0;it<2;it++){
    if(it==0) iadc=2;
    if(it==1) iadc=3;
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

int A2Cal1ToCal2::CheckADCOverRange(A2Cal1* cal1){
  int nch=0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(cal1->cal[it][il][1] > 4096){nch++;}
    }
  }
  return nch;
}

#endif
