#ifndef __RHICFRoman_CPP__
#define __RHICFRoman_CPP__

#include "RHICfRoman.h"

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(RHICfRoman);
#endif

#include <cmath>

RHICfRoman::RHICfRoman(){
  clear();
}

RHICfRoman::RHICfRoman(const char* name, const char* title) : TNamed(name,title){
  clear();
}

RHICfRoman::~RHICfRoman(){
  ;
}

int RHICfRoman::clear(){
  run = 0;
  number = 0;
  for(int i=0;i<N_CHANNEL;i++){
	 dE[i] = 0.;
  }
  return 0;
}

int RHICfRoman::copy(RHICfRoman* d){
  this->run = d->run;
  this->number = d->number;
  for(int i=0;i<N_CHANNEL;i++){
	 this->dE[i] = d->dE[i];
  }
  return 0;
}




#endif
