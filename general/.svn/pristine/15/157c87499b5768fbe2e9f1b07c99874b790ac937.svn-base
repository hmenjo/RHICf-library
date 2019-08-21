#ifndef __SILICONGAIN_CPP__
#define __SILICONGAIN_CPP__

#include "SiliconGain.h"

#if !defined(__CINT__)
ClassImp(SiliconGain);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const char* SiliconGain::SILICONGAIN_FORMAT = "SILICON_GAIN";
const int   SiliconGain::SILICON_NODATA;
const int   SiliconGain::SILICON_DATA;

SiliconGain::SiliconGain(){
  Initialize();
}

SiliconGain::~SiliconGain(){;}

int SiliconGain::Initialize(){
  strcpy(tablefile,"");
  strcpy(format,"SILICONGAIN_FORMAT");
  version = SILICON_NODATA;
  type    = SILICON_NODATA;
  return OK;
}



#endif 
