#ifndef __PMTSATUCORRECTION_CPP__
#define __PMTSATUCORRECTION_CPP__

#include "PMTSatuCorrection.h"

//----------------------------------------------------------------------------
//                   
//  For PMT saturation correction.
//  The main correction function is implemented in PMTSatu coded by T.Sako.
//  This is just an interface as the LHCf general format.
//   
//  Usage:
//    - Initialization 
//     PMTSatuCorrection *pmtsatu = new PMTSatuCorrection();
//     (default table path and table file are set. See PMTSatu::PMTSatu() )
//     pmtsatu->ReadHVTable("hvtable_arm2_ALL600.txt",2);
//     
//    - Correction in your event loop.
//     a2cal1tocal2->CalculateADC(a2cal1);    (convertion H.R.ADC -> L.R.ADC)
//     a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
//     pmtsatu->Calculate(a2cal1)              <---
//     a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion)
//     a2gaincalibration->Calculate(a2cal2);  (gain calibration)
//                    OR
//     a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
//     a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion) 
//     pmtsatu->Calculate(a2cal2)              <---
//     a2gaincalibration->Calculate(a2cal2);  (gain calibration)
//       (The both ways give same result.)
// 
// +++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  12 Aug. 10: First edited by H.MENJO
//----------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(PMTSatuCorrection);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

PMTSatuCorrection::PMTSatuCorrection() : PMTSatu()
{
  Initialize();
}

PMTSatuCorrection::PMTSatuCorrection(char* tpath, char* fname) : 
  PMTSatu(tpath,fname)
{
  Initialize();
}

PMTSatuCorrection::~PMTSatuCorrection(){;}

int PMTSatuCorrection::Initialize(char *tpath, char* fname){
  for(int iarm=0;iarm<2;iarm++){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){ 
	hvtable[iarm][it][il] = -1;
      }
    }
  }
  if(strcmp(tpath,"") && strcmp(fname,"")){
    PMTSatu::Init(tpath,fname);
  }
  return OK;
}

int PMTSatuCorrection::ReadHVTable(A1GainCalibration* gain){
  // Read the HT table of PMTs from A1GainCalibration
  const int arm = 0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hvtable[arm][it][il] = (int)(gain->GetHV(it,il)+0.00000001);
    }
  }
  return OK;
}

int PMTSatuCorrection::ReadHVTable(A2GainCalibration* gain){
  // Read the HT table of PMTs from A2GainCalibration
  const int arm = 1;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hvtable[arm][it][il] = (int)(gain->GetHV(it,il)+0.00000001);
    }
  }
  return OK;
}

int PMTSatuCorrection::ReadHVTable(char filename[],int arm){
  // Read the HV table. 
  // filename : the file path of hv table. 
  //    It is same as the table for A1GainCalibration and A2GainCalibration
  // arm      : 1 (Arm1) or 2 (Arm2) 
  // if you don't give the "arm" argument, the hv table is set for the both arms.  
  if(arm==1 || arm<0){
    A1GainCalibration a1gain;
    a1gain.ReadHVTable(filename,"ADC");
    ReadHVTable(&a1gain);
  }
  if(arm==2 || arm<0){
    A2GainCalibration a2gain;
    a2gain.ReadHVTable(filename,"ADC");
    ReadHVTable(&a2gain);
  }
  return OK;
}

int PMTSatuCorrection::Calculate(A1Cal1* cal){
  // Correct saturation effect of all ADC values in A1Cal1
  // Take account only the values of A1Cal1::cal[*][*][0].
  // It must be called just before the format conversion if you call A*Cal1ToCal2::CalculateADC 
  // before the pedestal subtraction  
  // exp. 
  //   a2cal1tocal2->CalculateADC(a2cal1);    (convertion H.R.ADC -> L.R.ADC)
  //   a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
  //   pmtsatu->Calculate(a2cal1)              <---
  //   a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion)
  //   a2gaincalibration->Calculate(a2cal2);  (gain calibration)

  const int arm = 0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il][0] 
	= PMTSatu::ADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il][0]);
    }
  }
  return OK;
}

int PMTSatuCorrection::Calculate(A2Cal1* cal){
  // Correct saturation effect of all ADC values in A1Cal1
  // Take account only the values of A1Cal1::cal[*][*][0].
  // It must be called just before the format conversion if you call A*Cal1ToCal2::CalculateADC 
  // before the pedestal subtraction  
  // exp. 
  //   a2cal1tocal2->CalculateADC(a2cal1);    (convertion H.R.ADC -> L.R.ADC)
  //   a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
  //   pmtsatu->Calculate(a2cal1)              <---
  //   a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion)
  //   a2gaincalibration->Calculate(a2cal2);  (gain calibration)
  const int arm = 1;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il][0] 
	= PMTSatu::ADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il][0]);
    }
  }
  return OK;
}


int PMTSatuCorrection::Calculate(A1Cal2* cal){
  // Correct saturation effect of all ADC values in A1Cal1
  // Take account only the values of A1Cal1::cal[*][*][0].
  // It must be called just before gain calibration (just after format conversion Cal1->Cal2)
  // exp. 
  //   a2cal1tocal2->CalculateADC(a2cal1);    (convertion H.R.ADC -> L.R.ADC)
  //   a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
  //   a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion) 
  //   pmtsatu->Calculate(a2cal2)              <---
  //   a2gaincalibration->Calculate(a2cal2);  (gain calibration)
  const int arm = 0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il] 
	= PMTSatu::ADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il]);
    }
  }
  return OK;
}

int PMTSatuCorrection::Calculate(A2Cal2* cal){  
  // Correct saturation effect of all ADC values in A1Cal1
  // Take account only the values of A1Cal1::cal[*][*][0].
  // It must be called just before gain calibration (just after format conversion Cal1->Cal2)
  // exp. 
  //   a2cal1tocal2->CalculateADC(a2cal1);    (convertion H.R.ADC -> L.R.ADC)
  //   a2pedesubtract->Subtract(a2cal1);      (pedestal subtraction)
  //   a2cal1tocal2->Convert(a2cal1,a2cal2);  (format conversion) 
  //   pmtsatu->Calculate(a2cal2)              <---
  //   a2gaincalibration->Calculate(a2cal2);  (gain calibration)
  const int arm = 1;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il] 
	= PMTSatu::ADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il]);
    }
  }
  return OK;
}

int PMTSatuCorrection::InvCalculate(A1Cal1* cal){
  // Add saturation effect to all ADC values 
  const int arm = 0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il][0] 
	= PMTSatu::InvADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il][0]);
    }
  }
  return OK;
}

int PMTSatuCorrection::InvCalculate(A2Cal1* cal){
  // Add saturation effect to all ADC values 
  const int arm = 1;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il][0] 
	= PMTSatu::InvADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il][0]);
    }
  }
  return OK;
}

int PMTSatuCorrection::InvCalculate(A1Cal2* cal){
  // Add saturation effect to all ADC values 
  const int arm = 0;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il]
	= PMTSatu::InvADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il]);
    }
  }
  return OK;
}

int PMTSatuCorrection::InvCalculate(A2Cal2* cal){
  // Add saturation effect to all ADC values 
  const int arm = 1;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il]
	= PMTSatu::InvADC2ADC(arm,it,il,hvtable[arm][it][il],cal->cal[it][il]);
    }
  }
  return OK;
}

#endif
