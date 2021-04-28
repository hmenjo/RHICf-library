#ifndef __A2SCL_PP2015_H__
#define __A2SCL_PP2015_H__

// --------------------------------------------------------------------
//                            A2Scl_pp2015
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A2Scl_pp2015 : public TNamed {
 public:
  static const int c_N_A2_PTIM = 2;
  static const int c_N_A2_PSCL = 16;
  static const int c_N_A2_RAMC = 256;

 public:
  int   run;                            // RUN Number
  int   number;                         // Event Number
  unsigned int   time[c_N_A2_PTIM];       // CPU TIME
  unsigned int   scl0[c_N_A2_PSCL];       // Scaler values of CAEN V260
  unsigned int   ramc[c_N_A2_RAMC];      // RAM Counter values of CAEN V1495 
  
 public:
  A2Scl_pp2015(){clear();}
  A2Scl_pp2015(const char* name, const char *title) : TNamed(name,title){clear();}
  ~A2Scl_pp2015(){;}
    
  int       clear();
  int       copy(A2Scl_pp2015* );
  int       copydata(A2Scl_pp2015* );

  ClassDef(A2Scl_pp2015,1);      //  Data structure for Arm2 Scaler Event
};

#endif
