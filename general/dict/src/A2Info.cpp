#ifndef __A2INFO_CPP__
#define __A2INFO_CPP__

#include "A2Info.h"

#if !defined(__CINT__)
ClassImp(A2Info);
#endif

int A2Info::clear(){
  run = 0;
  runmode = -1;
  isrunning = false;
  start_time = 0;
  end_time = 0;
  nev_trg = 0;
  nev_scl = 0;
  
  return OK;
}

#endif
