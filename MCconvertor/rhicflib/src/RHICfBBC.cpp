#ifndef __RHICFBBC_CPP__
#define __RHICFBBC_CPP__

#include "RHICfBBC.h"

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(RHICfBBC);
#endif

#include <cmath>

RHICfBBC::RHICfBBC(){
  clear();
}

RHICfBBC::RHICfBBC(const char* name, const char* title) : TNamed(name,title){
  clear();
}

RHICfBBC::RHICfBBC(const RHICfBBC& rhs): run(rhs.run), number(rhs.number)
{
}

RHICfBBC& RHICfBBC::operator=(const RHICfBBC& rhs)
{

    TNamed::operator=(rhs);
    run = rhs.run;
    number = rhs.number;
    return *this;

}

RHICfBBC::~RHICfBBC(){
  ;
}

int RHICfBBC::clear(){
  run = 0;
  number = 0;
  for (int iWE = 0; iWE < 2; iWE++) 
  {
      for(int i=0;i<N_CHANNEL;i++){
          dE[iWE][i] = 0.;
      }
      
  }
  for (int iWE = 0; iWE < 2; iWE++) 
  {
      for(int i=0;i<N_CHANNEL;i++){
          NOP[iWE][i] = 0.;
      }
      
  }
  return 0;
}

int RHICfBBC::copy(RHICfBBC* d){
  this->run = d->run;
  this->number = d->number;
  for (int iWE = 0; iWE < 2; iWE++) 
  {
      for(int i=0;i<N_CHANNEL;i++){
          this->dE[iWE][i] = d->dE[iWE][i];
      }
      
  }
  for (int iWE = 0; iWE < 2; iWE++) 
  {
      for(int i=0;i<N_CHANNEL;i++){
          this->NOP[iWE][i] = d->dE[iWE][i];
      }
      
  }
  return 0;
}




#endif
