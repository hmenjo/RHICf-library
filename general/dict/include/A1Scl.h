#ifndef __A1SCL_H__
#define __A1SCL_H__

// --------------------------------------------------------------------
//                                 A1Scl
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"
#include "feparam_arm1.h"

class A1Scl : public TNamed {
 public:
  int   run;                           // RUN Number
  int   number;                        // Event Number
  unsigned int   time[N_A1_PTIM];      // CPU TIME
  unsigned int   scl0[N_A1_PSCL];      // Scaler values of CAEN V260
  // unsigned int   gpio0[N_A1_PGP0];
  // unsigned int   gpio1[N_A1_PGP1];

 public:
  A1Scl(){clear();}
  A1Scl(const char* name, const char *title) : TNamed(name,title){clear();}
  ~A1Scl(){;}
    
  int       clear();
  int       copy(A1Scl* );
  int       copydata(A1Scl* );

  ClassDef(A1Scl,1);    //  Data structure for Arm1 Scaler Event
};

#endif
