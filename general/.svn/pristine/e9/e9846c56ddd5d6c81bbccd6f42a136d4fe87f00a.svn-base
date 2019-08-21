#ifndef __A1SCL_PP2015_H__
#define __A1SCL_PP2015_H__

// --------------------------------------------------------------------
//                            A1Scl_pp2015
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A1Scl_pp2015 : public TNamed {
 public:
  static const int c_N_A1_PTIM = 2;
  static const int c_N_A1_PSCL = 16;
  static const int c_N_A1_RAMC = 256;

 public:
  int   run;                           // RUN Number
  int   number;                        // Event Number
  unsigned int   time[c_N_A1_PTIM];      // CPU TIME
  unsigned int   scl0[c_N_A1_PSCL];      // Scaler values of CAEN V260
  unsigned int   ramc[c_N_A1_RAMC];      // RAM Counter values of CAEN V1495 
  // unsigned int   gpio0[N_A1_PGP0];
  // unsigned int   gpio1[N_A1_PGP1];

 public:
  A1Scl_pp2015(){clear();}
  A1Scl_pp2015(const char* name, const char *title) : TNamed(name,title){clear();}
  ~A1Scl_pp2015(){;}
    
  int       clear();
  int       copy(A1Scl_pp2015* );
  int       copydata(A1Scl_pp2015* );

  ClassDef(A1Scl_pp2015,1);    //  Data structure for Arm1 Scaler Event in 2015
};

#endif
