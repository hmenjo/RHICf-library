#ifndef __RHICFFC_CPP__
#define __RHICFFC_CPP__

#include "RHICfFC.h"

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(RHICfFC);
#endif

#include <cmath>

RHICfFC::RHICfFC(){
  clear();
}

RHICfFC::RHICfFC(const char* name, const char* title) : TNamed(name,title){
  clear();
}

RHICfFC::~RHICfFC(){
  ;
}

RHICfFC::RHICfFC(const RHICfFC& rhs): run(rhs.run), number(rhs.number)
{
}

RHICfFC& RHICfFC::operator=(const RHICfFC& rhs)
{

    TNamed::operator=(rhs);
    run = rhs.run;
    number = rhs.number;
    return *this;

}

int RHICfFC::clear(){
  run = 0;
  number = 0;
  for(int i=0;i<N_FCCHANNEL;i++){
	 FCdE[i] = 0.;
  }
  return 0;
}

int RHICfFC::copy(RHICfFC* d){
  this->run = d->run;
  this->number = d->number;
  for(int i=0;i<N_FCCHANNEL;i++){
	 this->FCdE[i] = d->FCdE[i];
  }
  return 0;
}

void RHICfFC::Clear(){
  run = 0;
  number = 0;
  for(int i=0;i<N_FCCHANNEL;i++){
	 FCdE[i] = 0.;
  }
}



#endif
