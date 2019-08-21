#ifndef __A2SCL_H__
#define __A2SCL_H__

// --------------------------------------------------------------------
//                                 A2Scl
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"
#include "feparam_arm2.h"

class A2Scl : public TNamed {
 public:
  int   run;                            // RUN Number
  int   number;                         // Event Number
  unsigned int   time[N_A2_PTIM];       // CPU TIME
  unsigned int   scl0[N_A2_PSCL];       // Scaler values of CAEN V260
  // unsigned int   gpio0[N_A2_PGP0];
  // unsigned int   gpio1[N_A2_PGP1];
  
 public:
  A2Scl(){clear();}
  A2Scl(const char* name, const char *title) : TNamed(name,title){clear();}
  ~A2Scl(){;}
    
  int       clear();
  int       copy(A2Scl* );
  int       copydata(A2Scl* );

  ClassDef(A2Scl,1);      //  Data structure for Arm2 Scaler Event
};

#endif
