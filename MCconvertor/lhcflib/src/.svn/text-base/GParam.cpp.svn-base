#ifndef __GParam_CPP__
#define __GParam_CPP__

#include "GParam.h"

#if !defined(__CINT__)
ClassImp(GParam);
#endif

int GParam::clear(){
  run = 0;
  number = 0;
  gnumber = 0;
  
  for(int i=0;i<32;i++){
    parami[i] = 0;
    paramd[i] = 0.;
  }
  return OK;
}

int GParam::copy(GParam *d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int GParam::copydata(GParam *d){
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;
  
  for(int i=0;i<32;i++){
    this->parami[i] = d->parami[i];
    this->paramd[i] = d->paramd[i];
  }
  return OK;
}

#endif
