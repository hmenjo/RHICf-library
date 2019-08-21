#ifndef __CALFLAGS1__
#define __CALFLAGS1__

#include <iostream>
#include <iomanip>
using namespace std;

#include "Cal01.hh"

#define  CALFLAGS1_IDATAFORMAT      41
#define  CALFLAGS1_DATAFORMAT  "CALFLAGS1"

#define N_SCL0  8
#define N_INP0  8
#define N_SADC 16
#define N_CAD0  5
#define N_CAD1  5
#define N_CAD2  5

class CalFlags1
{
public:
  int       idataformat;
  char      dataformat[20];

public:
  int       Run;
  int       Number;
  int       Time;

  int       scaler[N_SCL0];
  int       inp0[N_INP0];
  int       sadc[N_SADC];
  
  int       cadc0[N_CAD0];
  int       cadc1[N_CAD1];
  int       cadc2[N_CAD2];

public:
  CalFlags1();
  int Init();
  int Clear();
  int Copy(CalFlags1 *obj);
  int PrintStatus();

  int   GetIDataFormat(){return idataformat;}
  char* GetDataFormat(){return dataformat;}
};

CalFlags1::CalFlags1(){
  Init();
}

int CalFlags1::Init(){
  idataformat = CALFLAGS1_IDATAFORMAT;
  strcpy(dataformat,CALFLAGS1_DATAFORMAT);
  Clear();
  return CAL01_OK;
}

int CalFlags1::Clear(){
  Run=0;
  Number=0;
  Time=0;
  for(int i=0;i<N_INP0;i++){
    inp0[i] = 0;
  }
  for(int i=0;i<N_SCL0;i++){
    scaler[i]=0;
  }
  for(int i=0;i<N_SADC;i++){
    sadc[i]=0;
  }
  for(int i=0;i<N_CAD0;i++){
    cadc0[i] = 0;
    cadc1[i] = 0;
    cadc2[i] = 0;
  }
  return CAL01_OK;
}

int CalFlags1::Copy(CalFlags1 *obj){
  idataformat = obj->idataformat;
  strcpy(dataformat,obj->dataformat);
  Run=obj->Run;
  Number=obj->Number;
  Time=obj->Time;
  for(int i=0;i<N_SCL0;i++){
    scaler[i]=obj->scaler[i];
  }
  for(int i=0;i<N_INP0;i++){
    inp0[i] = obj->inp0[i];
  }
  for(int i=0;i<N_SADC;i++){
    sadc[i]=obj->sadc[i];
  } 
  for(int i=0;i<N_CAD0;i++){
    cadc0[i] = obj->cadc0[i];
    cadc1[i] = obj->cadc1[i];
    cadc2[i] = obj->cadc2[i];
  }
  return CAL01_OK;


}

#endif
