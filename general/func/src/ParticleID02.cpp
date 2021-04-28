#ifndef __PARTICLEID02_CPP__
#define __PARTICLEID02_CPP__ 

#include "ParticleID02.h"

//----------------------------------------------------------------------
//
// This class is to calculate L20% and L90% values by slightly different
// method to ParticleID01. 
// 
// In ParticleID01,
//    Linear spline interpolation is done  
//    for "integral of dE between first layer and x layer".  
//         
// In ParticleID02,
//    Linear spline interpolation is done
//    for dE transition itself. Then calculate integral of interporated  
//    transition.  
//                
//  The difference between these methods might make a different in the results,
//  especially in case that two continuous layers have big different dE.
//
//  Because this class inherites ParticleID02 with several virtual function.
//  you can select ParticleID01 or ParticleID02 when you allocate it into memory.
//     ParticleID01*  pid;
//       pid = new  ParticleID01() // for ParticleID01 
//       pid = new  ParticleID02() // for ParticleID02
//     .....
// 
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  27 Jan. 11:  First edited by Menjo
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ParticleID02);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

ParticleID02::ParticleID02() : ParticleID01() {;}

ParticleID02::~ParticleID02() {;}

double ParticleID02::Cal2SumLayer(double de0, double de1, double step){
  // Calculate SumdE by linear spline interpolation 
  return (de0+de1)*step/2.;
}

double ParticleID02::Cal2PosdE(double de0, double de1, double step, double val){
  
  // equation of a*x^2 + b*x + c = 0
  double a = (de1-de0)/step;
  double b =  2.*de0;
  double c = -2.*val;
  
  // Case : No solution to the equation  
  if(b*b-4.*a*c < 0){
    return -1;
  }
  
  // Case : 2 solutions 
  double ret[2] = {0.};
  ret[0] = (-1.*b-sqrt(b*b-4.*a*c))/(2.*a);
  ret[1] = (-1.*b+sqrt(b*b-4.*a*c))/(2.*a);

  // Check the answers in the search reagion. (0 < x < step)  
  if(ret[0] >= 0. && ret[0] <= step){ return ret[0]; }
  if(ret[1] >= 0. && ret[1] <= step){ return ret[1]; }

  return -1.;
}

double ParticleID02::CalPosition(double *d, double sum, double ratio){
  double tmpsum = sum*ratio;  
  double tmppos = 0.;
  double pos = 2.;  // start point 
  double step;
  tmpsum -= d[0]*2./2.;
  if(tmpsum < 0){
    return 1. + (sum*ratio)/(d[0]/2./2.);
  }
  
  for(int i=0;i<15;i++){
    if(i<=10){ step = 2.;} 
    else     { step = 4.;}
    
    // Cal2PosdE gives -1 if no solusion between 0 and step
    tmppos = Cal2PosdE(d[i],d[i+1],step,tmpsum);
    
    if(tmppos>=0){
      pos += tmppos;
      return pos ;
    }
    else{
      pos += step;
      tmpsum -= Cal2SumLayer(d[i],d[i+1],step);
    }
  }

  if(tmpsum > 0 && d[15]){
    pos += tmpsum/(d[15]/4./2.);
  }
  return pos;  
}

double ParticleID02::Calculate(double *d,int it){
 
  // Calculate sum dE with linear interpolation of transition shape 
  double step = 2.;
  double sum  = 0.;
  for(int i=0;i<15;i++){  // <- must be 15, not 16
    if(i<=10){ step = 2.;} 
    else     { step = 4.;}
 
    sum += Cal2SumLayer(d[i],d[i+1],step);
  }
  // Correction for first and 16th layers
  sum += d[0]*2./2.;
  sum += d[15]*4./2.;
  calsum[it] = sum;

  // Search L20%
  L[it][0] = CalPosition(d, sum,l0_th);

  // Search L90%
  L[it][1] = CalPosition(d, sum,l1_th);


  return  L[it][1] - L[it][0];
}

#endif
