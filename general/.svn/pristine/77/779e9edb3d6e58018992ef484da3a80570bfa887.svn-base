// ***********************************************************
// ***  RawFSIL Class                                      ***
// ***   this class is for format SPS2006 raw data         ***
// ***  03 Apl. 07 : first edited                          ***
// ***********************************************************

#ifndef __RAWFSIL__
#define __RAWFSIL__

#include <iostream>
#include <iomanip>

#define  RAWFSIL_IDATAFORMAT    31
#define  RAWFSIL_DATAFORMAT   "RAWFSIL"

#include "Raw.hh"

class RawFSIL
{
private:
public:
  int            idataformat;
  char           dataformat[20];
  
public:
  struct{
    Int_t           nFSIL;
    UShort_t        FSIL[15394]; //[nFSIL]
  } FSIL;

  RawFSIL();
  ~RawFSIL();

  int     Init();
  int     Clear();
  int     Copy(const RawFSIL* obj);
  int     GetIDataFormat(){return idataformat;}
  char*   GetDataFormat(){return dataformat;}
  int     PrintStatus();
};

RawFSIL::RawFSIL() {
  Init();
  return ;
}

RawFSIL::~RawFSIL() {
  return ;
}

int RawFSIL::Init(){
  idataformat = RAWFSIL_IDATAFORMAT;
  strcpy(dataformat,RAWFSIL_DATAFORMAT);
  Clear();
  return RAW_OK;
}

int RawFSIL::Clear(){
  FSIL.nFSIL = 0;
  for(int i=0;i<15394;i++){FSIL.FSIL[i]=0;}
  return RAW_OK;
}

int RawFSIL::Copy(const RawFSIL* obj){
  idataformat = obj->idataformat;
  strcpy(dataformat,obj->dataformat);
  FSIL.nFSIL =  obj->FSIL.nFSIL;
  for(int i=0;i<FSIL.nFSIL;i++){
    FSIL.FSIL[i] =  obj->FSIL.FSIL[i];
  }
  return RAW_OK;
}

int RawFSIL::PrintStatus(){
  cout << "Format:  " << dataformat << endl;
  cout << " nFSIL: " << setw(5) << FSIL.nFSIL << endl;
  return RAW_OK;
}

#endif
