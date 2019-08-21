#ifndef __SPSADAMOREC0_CPP__
#define __SPSADAMOREC0_CPP__

#include "SPSAdamoRec0.h"

//----------------------------------------------------------------------
// SPSAdamoRec0
//
//   This is data contaner for the ADAMO reconstructed result.
//   This is for old analysis result (SPS2007)  
//
// 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(SPSAdamoRec0);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#include <globaldef.h>

const int SPSAdamoRec0::NLAYER;
const int SPSAdamoRec0::NXY;

SPSAdamoRec0::SPSAdamoRec0(){
  clear();
}

SPSAdamoRec0::~SPSAdamoRec0(){;}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ SPSAdamoRec0::clear()            +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int SPSAdamoRec0::clear(){
  // Clear all data
  run = 0;
  number = 0;
  gnumber = 0;
  
  for(int ixy=0;ixy<NXY;ixy++){
    pos[ixy] = 0.;
    direction[ixy] = 0.;
    clevel[ixy]  = 0;
    clevel1[ixy] = 0;
    ndata[ixy]   = 0;
    for(int ilayer=0;ilayer<NLAYER;ilayer++){
      ndiscri[ixy][ilayer] = 0;
      data[ixy][ilayer]    = 0.;
      dataz[ixy][ilayer]   = 0.;
    }
    chi2[ixy] = 0;
  }
  pad = 0;

  return OK;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ SPSAdamoRec0::copy()             +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int SPSAdamoRec0::copy(SPSAdamoRec0* d){
  // Copy data, name and title of "d" to "this"
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ SPSAdamoRec0::copydata()         +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int SPSAdamoRec0::copydata(SPSAdamoRec0* d){
  // Copy only data of "d" to "this"
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber = d->gnumber;
  
  for(int ixy=0;ixy<NXY;ixy++){
    this->pos[ixy]       = d->pos[ixy];
    this->direction[ixy] = d->direction[ixy];
    this->clevel[ixy]    = d->clevel[ixy];
    this->clevel1[ixy]   = d->clevel1[ixy];
    this->ndata[ixy]     = d->ndata[ixy];
    for(int ilayer=0;ilayer<NLAYER;ilayer++){
      this->ndiscri[ixy][ilayer] = d->ndiscri[ixy][ilayer];
      this->data[ixy][ilayer]    = d->data[ixy][ilayer];
      this->dataz[ixy][ilayer]   = d->dataz[ixy][ilayer];
    }
    this->chi2[ixy] = d->chi2[ixy];
  }
  this->pad = d->pad;

  return OK;  
}


double SPSAdamoRec0::GetPosition(int ixy){return 0;}
double SPSAdamoRec0::GetDirection(int ixy){return 0;}


#endif
