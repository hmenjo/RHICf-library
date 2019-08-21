#ifndef __TLHCFDIPDATAH_CPP__
#define __TLHCFDIPDATAH_CPP__

#include "TLHCFDIPDATAH.h"

#if !defined(__CINT__)
ClassImp(TLHCFDIPDATAH);  
#endif

// *****************************************************************
// ***   TLHCFDIPDATAH::clear   ***************************************
// *****************************************************************
void TLHCFDIPDATAH::clear(){
  run    = 0;
  number = 0;
  DataClear();
}


// *****************************************************************
// ***   TLHCFDIPDATAH::DataClear   ***********************************
// *****************************************************************
void TLHCFDIPDATAH::DataClear(){

  data.time    =  0;
  data.number  =  0;
  data.status  =  0;

  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAH::Add  ******************************************
// *****************************************************************
void TLHCFDIPDATAH::Add(TLHCFDIPDATAH* d){
  LHCFDIPDATAH* add = d->GetData();
  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAH::Divide  ***************************************
// *****************************************************************
void TLHCFDIPDATAH::Divide(double div){

  data.time    =  (int)((double)data.time/div);
  data.number  =  (int)((double)data.number/div);
  
  return ;
}



#endif
