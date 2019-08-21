#ifndef __GParamD64_CPP__
#define __GParamD64_CPP__

#include "GParamD64.h"

#if !defined(__CINT__)
ClassImp(GParamD64);
#endif

int GParamD64::clear(){
  run = 0;
  number = 0;
  gnumber = 0;
  
  for(int i=0;i<64;i++){
    paramd[i] = 0.;
  }
  return OK;
}

int GParamD64::copy(GParamD64 *d){
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int GParamD64::copydata(GParamD64 *d){
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;
  
  for(int i=0;i<64;i++){
    this->paramd[i] = d->paramd[i];
  }
  return OK;
}

#endif
