#ifndef __RHICFZDC_CPP__
#define __RHICFZDC_CPP__

#include "RHICfZDC.h"

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(RHICfZDC);
#endif

#include <cmath>

RHICfZDC::RHICfZDC(){
  clear();
}

RHICfZDC::RHICfZDC(const char* name, const char* title) : TNamed(name,title){
  clear();
}

RHICfZDC::~RHICfZDC(){
  ;
}

RHICfZDC::RHICfZDC(const RHICfZDC& rhs): run(rhs.run), number(rhs.number)
{
}

RHICfZDC& RHICfZDC::operator=(const RHICfZDC& rhs)
{

    TNamed::operator=(rhs);
    run = rhs.run;
    number = rhs.number;
    return *this;

}

int RHICfZDC::clear(){
  run = 0;
  number = 0;
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 ZDCdE[i] = 0.;
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 SMDHdE[i] = 0.;
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 SMDVdE[i] = 0.;
  }
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 ZDCNOP[i] = 0.;
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 SMDHNOP[i] = 0.;
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 SMDVNOP[i] = 0.;
  }
  return 0;
}

int RHICfZDC::copy(RHICfZDC* d){
  this->run = d->run;
  this->number = d->number;
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 this->ZDCdE[i] = d->ZDCdE[i];
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 this->SMDHdE[i] = d->SMDHdE[i];
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 this->SMDVdE[i] = d->SMDVdE[i];
  }
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 this->ZDCNOP[i] = d->ZDCNOP[i];
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 this->SMDHNOP[i] = d->SMDHNOP[i];
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 this->SMDVNOP[i] = d->SMDVNOP[i];
  }
  return 0;
}


void RHICfZDC::Clear(){
  run = 0;
  number = 0;
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 ZDCdE[i] = 0.;
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 SMDHdE[i] = 0.;
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 SMDVdE[i] = 0.;
  }
  for(int i=0;i<N_ZDCCHANNEL;i++){
	 ZDCNOP[i] = 0.;
  }
  for(int i=0;i<N_SMDHCHANNEL;i++){
	 SMDHNOP[i] = 0.;
  }
  for(int i=0;i<N_SMDVCHANNEL;i++){
	 SMDVNOP[i] = 0.;
  }
}


#endif
