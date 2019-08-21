#ifndef Delaypede_H
#define Delaypede_H

#include "RHICfRec1.h"
#include "A1Reconstruction.h"
using namespace std;
typedef RHICfRec1 RHICfRec;

class RHICfRaw_Op2017;
class Delaypede{ 
  //private:

  /* double fmean[2][16]; */
  /* double fsigma[2][16]; */
  
 public:
  static const int ntower = 2;
  static const int nlayer = 16;
  RHICfRec *fRec;
 public:
  RHICfRec *GetRec(){ return fRec;}
  /* double fmean[ntower][nlayer](int run, int tower, int layer, int a); */
  /* double fsigma[ntower][nlayer](int run, int tower, int layer, int a); */
  Delaypede();
  ~Delaypede();
  /* double fmean[ntower][nlayer];  */
  /* double fsigma[ntower][nlayer];  */
  
  
  int GetRun(int run, double fmean[2][16]);
  double GetParam(int run, double fmean[2][16], double fsigma[2][16]);
  void CheckDelaypede(RHICfRaw_Op2017 *raw, double fmean[2][16], double fsigma[2][16], int delay_flag[2]);
  void SetDelayPedeFlag(int delay_flag[2], A1Reconstruction *reconstruction);
};

#endif
