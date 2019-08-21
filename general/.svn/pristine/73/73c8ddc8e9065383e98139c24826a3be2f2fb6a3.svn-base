#ifndef __PARTICLEID02_H__
#define __PARTICLEID02_H__ 

//-----------------------------------------------------------------
//                         ParticleID02
//-----------------------------------------------------------------

#include <TObject.h>
#include "ParticleID01.h"

class ParticleID02 : public ParticleID01 {
  
 public:  
  ParticleID02();
  virtual ~ParticleID02();

  virtual double Calculate(double *d,int it);
  virtual double GetL20(int it){return L[it][0];}
  virtual double GetL95(int it){return GetL90(it);}
  virtual double GetL90(int it){return L[it][1];}
  
  double Cal2SumLayer(double de0, double de1, double step);
  double Cal2PosdE(double de0, double de1, double step, double val);
  double CalPosition(double *d, double sum, double ratio);

  ClassDef(ParticleID02,1);   // Calculate L20 and L90 for PID
};


#endif
