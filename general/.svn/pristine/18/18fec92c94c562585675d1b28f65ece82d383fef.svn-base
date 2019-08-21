#ifndef __FUNCFORLHC_CPP__

#include "FuncForLHC.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstring>
using namespace std;

// Calculate Pi0 Invariant Mass from Gamma Pair.
// energy:[GeV], x,y:[mm], return [MeV]
double CalPi0Mass(double energy1,double x1,double y1,
		  double energy2,double x2,double y2){
  double r2;
  double mass;
  r2 = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
  mass = sqrt(energy1*energy2*r2)/141050.*1000.;
  return mass;
}

#endif
