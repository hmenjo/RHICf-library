#ifndef __RAWL1T_H__
#define __RAWL1T_H__

// --------------------------------------------------------------------
//                             RawL1T  
//             For detail, see RawL1T.cpp or Online Manual
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class RawL1T : public TNamed {
 public:
  static const int NCOUNTERS = 14;
  
  int   run;                       // Run Number
  int   number;                    // Event Number
  int   gnumber;                   // Glocal Event Number
  
  unsigned int  time[2];           // Time [0]:sec, [1]:usec
  unsigned int  gpio2[NCOUNTERS];  // Counter valses in LHCFL1T
 
 public:
  RawL1T(){clear();}
  RawL1T(char* name, char *title) : TNamed(name,title){clear();}
  ~RawL1T(){;}
  
  int  clear();
  int  copy(RawL1T* d);
  int  copydata(RawL1T* d);
  
  ClassDef(RawL1T,1);
};

#endif
