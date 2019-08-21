#ifndef __PARTICLEID01_H__
#define __PARTICLEID01_H__ 

//-----------------------------------------------------------------
//                         ParticleID01
//-----------------------------------------------------------------

#include <TObject.h>
#include "A1Cal2.h"
#include "A2Cal2.h"

class ParticleID01 {
 public:
  double calsum[2]; // sum of 16 layers
  double L[2][2];   // [Layer] Position on the threshold tower:param 
  
 public:  
  ParticleID01(){Clear();}
  virtual ~ParticleID01(){;}

  void           Clear();  
  virtual double Calculate(double *d,int it);
  double         Calculate(A1Cal2 *d,int it);
  double         Calculate(A2Cal2 *d,int it);
  virtual double GetL20(int it){return LayerToX(L[it][0]);}
  virtual double GetL95(int it){return GetL90(it);}
  virtual double GetL90(int it){return LayerToX(L[it][1]);}
  double         GetShowerLength(int it){return GetL95(it)-GetL20(it);}
  double         LayerToX(double lp);
  double         GetSum(int it){return calsum[it];}
  
  static const double l0_th;    // L20
  static const double l1_th;   // L95

  ClassDef(ParticleID01,1);   // Calculate L20 and L90 for PID
};


#endif
