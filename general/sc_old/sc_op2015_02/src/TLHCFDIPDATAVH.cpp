#ifndef __TLHCFDIPDATAVH_CPP__
#define __TLHCFDIPDATAVH_CPP__

#include "TLHCFDIPDATAVH.h"

#if !defined(__CINT__)
ClassImp(TLHCFDIPDATAVH);  
#endif

// *****************************************************************
// ***   TLHCFDIPDATAVH::clear   ***************************************
// *****************************************************************
void TLHCFDIPDATAVH::clear(){
  run    = 0;
  number = 0;
  DataClear();
}


// *****************************************************************
// ***   TLHCFDIPDATAVH::DataClear   ***********************************
// *****************************************************************
void TLHCFDIPDATAVH::DataClear(){

  data.time    =  0;
  data.number  =  0;
  data.status  =  0;

  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAVH::Add  ******************************************
// *****************************************************************
void TLHCFDIPDATAVH::Add(TLHCFDIPDATAVH* d){
  LHCFDIPDATAVH* add = d->GetData();
  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAVH::Divide  ***************************************
// *****************************************************************
void TLHCFDIPDATAVH::Divide(double div){

  data.time    =  (int)((double)data.time/div);
  data.number  =  (int)((double)data.number/div);
  
  return ;
}



#endif
