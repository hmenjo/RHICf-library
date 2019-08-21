#ifndef __RHICFSCL_OP2017_H__
#define __RHICFSCL_OP2017_H__

// --------------------------------------------------------------------
//                            RHICfScl_Op2017
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class RHICfScl_Op2017 : public TNamed {
 public:
  static const int c_N_A1_PTIM = 2;
  static const int c_N_A1_PGP0 = 12;    // DWORD 
  static const int c_N_A1_PGP1 = 120;   // DWORD 

 public:
  int   run;                                   // RUN Number
  int   number;                                // Event Number
  unsigned int   time[c_N_A1_PTIM];            // CPU TIME
  unsigned int   logic_counter[c_N_A1_PGP0];   // Counters in RHICF_LOGIC
  unsigned int   counter[c_N_A1_PGP1];         // BRAM Counter values 

 public:
  RHICfScl_Op2017(){clear();}
  RHICfScl_Op2017(const char* name, const char *title) : TNamed(name,title){clear();}
  ~RHICfScl_Op2017(){;}
    
  int       clear();
  int       copy(RHICfScl_Op2017* );
  int       copydata(RHICfScl_Op2017* );

  ClassDef(RHICfScl_Op2017,2);    //  Data structure for Scaler Event of RHICf 2017
};

#endif
