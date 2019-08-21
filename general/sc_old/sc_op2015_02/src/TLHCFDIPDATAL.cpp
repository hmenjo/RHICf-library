#ifndef __TLHCFDIPDATAL_CPP__
#define __TLHCFDIPDATAL_CPP__

#include "TLHCFDIPDATAL.h"

#if !defined(__CINT__)
ClassImp(TLHCFDIPDATAL);  
#endif

// *****************************************************************
// ***   TLHCFDIPDATAL::clear   ***************************************
// *****************************************************************
void TLHCFDIPDATAL::clear(){
  run    = 0;
  number = 0;
  DataClear();
}


// *****************************************************************
// ***   TLHCFDIPDATAL::DataClear   ***********************************
// *****************************************************************
void TLHCFDIPDATAL::DataClear(){

  data.time    =  0;
  data.number  =  0;
  data.status  =  0;

  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAL::Add  ******************************************
// *****************************************************************
void TLHCFDIPDATAL::Add(TLHCFDIPDATAL* d){
  LHCFDIPDATAL* add = d->GetData();
  return ;
}

// *****************************************************************
// ***   TLHCFDIPDATAL::Divide  ***************************************
// *****************************************************************
void TLHCFDIPDATAL::Divide(double div){

  data.time    =  (int)((double)data.time/div);
  data.number  =  (int)((double)data.number/div);
  
  return ;
}



#endif
