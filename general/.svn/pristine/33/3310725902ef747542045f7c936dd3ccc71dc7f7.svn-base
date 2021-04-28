#ifndef __CALFLAGS1CALCULATION__
#define __CALFLAGS1CALCULATION__

#include "Raw.hh"
#include "CalFlags1.hh"

class CalFlags1Calculation
{
protected:
  Raw*             rdata;
  CalFlags1*       cflags;
  
public:
  CalFlags1Calculation();

  int    SetRawData(Raw* r);
  int    SetCalFlags1Data(CalFlags1 *c);
  Raw*        GetRawData(){ return rdata; }
  CalFlags1*  GetCalFlags1Data(){ return cflags;}
  int    InitCalFlags1Cal();
  int    Calculate();
};

CalFlags1Calculation::CalFlags1Calculation(){
  InitCalFlags1Cal();
}

int CalFlags1Calculation::InitCalFlags1Cal(){
  rdata = 0;
  cflags = 0;
  return CAL01_OK;
}

int CalFlags1Calculation::SetRawData(Raw* r){
  rdata = r;
  return CAL01_OK;
}

int CalFlags1Calculation::SetCalFlags1Data(CalFlags1 *c){
  cflags = c;
  return CAL01_OK;
}

int CalFlags1Calculation::Calculate(){
  cflags->Run = rdata->Number.Run;
  cflags->Number = rdata->Number.Number;
  cflags->Time = rdata->Number.Time;
  
  for(int i=0;i<N_INP0;i++){
    cflags->inp0[i] = rdata->INP0.INP0[i];
  }
  for(int i=0;i<N_SCL0;i++){
    cflags->scaler[i] = rdata->SCL0.SCL0[i];
  }
  for(int i=0;i<N_SADC;i++){
    cflags->sadc[i] = rdata->SADC.SADC[i];
  } 
  for(int i=0;i<N_CAD0;i++){
    cflags->cadc0[i] = rdata->CAD0.CAD0[i];
    cflags->cadc1[i] = rdata->CAD1.CAD1[i];
    cflags->cadc2[i] = rdata->CAD2.CAD2[i];
  }
  return CAL01_OK;
}

#endif
