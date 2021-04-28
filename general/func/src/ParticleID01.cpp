#ifndef __PARTICLEID01_CPP__
#define __PARTICLEID01_CPP__ 

#include "ParticleID01.h"

//----------------------------------------------------------------------
//
//  This is a temporal class for particle identification. 
//  Take care very much to use this.                       
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 09: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ParticleID01);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

const double ParticleID01::l0_th = 0.2;
const double ParticleID01::l1_th = 0.9;

void ParticleID01::Clear(){
  for(int it=0;it<2;it++){
    calsum[it] = 0.;
    L[it][0] = 0.;
    L[it][1] = 0.;
  }
}

double ParticleID01::Calculate(A1Cal2 *d,int it){
  return Calculate(d->cal[it],it);
}

double ParticleID01::Calculate(A2Cal2 *d,int it){
   return Calculate(d->cal[it],it);
}

double ParticleID01::Calculate(double *d,int it){
 
  double sum=0.;
  for(int i=0;i<16;i++){
    if(i<11){
      sum += d[i];
    }
    else{
      sum += 2.*d[i];
    }
  }
  calsum[it] = sum;

  double tmp=0.;
  double a,b;
  double lp[2]={0.}; 
  double lsum[2]={0.};
  bool   check[2];
  check[0] = false;
  check[1] = false;
  // search L20
  for(int i=0;i<16;i++){

    if(i<11){
      tmp += d[i]; 
    }
    else{
      tmp += 2.*d[i];
    }
    lp[1] = i;
    lsum[1] = tmp; 
    
    // search L20
    if(tmp>sum*l0_th && check[0]==false){
      if(i==0){
	L[it][0] = lp[1];
      }else{
	a = (lsum[1]-lsum[0])/(lp[1]-lp[0]);
	b = lsum[1]-a*lp[1];
	L[it][0] = (sum*l0_th - b)/a;
      }
      check[0] = true; 
    }
    // search L95
    if(tmp>sum*l1_th && check[1]==false){
      if(i==0){
	L[it][1] = lp[1];
      }else{
	a = (lsum[1]-lsum[0])/(lp[1]-lp[0]);
	b = lsum[1]-a*lp[1];
	L[it][1] = (sum*l1_th - b)/a;
      }     
      check[1] = true; 
    }
    
    lp[0] = lp[1];
    lsum[0] = lsum[1]; 
  }
  
  return GetShowerLength(it);
}

double ParticleID01::LayerToX(double lp){
  if(lp<10){
    return (lp+1.)*2.;
  }
  else {
    return 22. + (lp-10.)*4.;
  }
}

#endif
