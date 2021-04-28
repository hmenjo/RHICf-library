#ifndef __SCLL1T_H__
#define __SCLL1T_H__

// --------------------------------------------------------------------
//                             SclL1T  
//             For detail, see SclL1T.cpp or Online Manual
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class SclL1T : public TNamed {
 public:
  static const int NCOUNTERS = 20;
  
  int   run;                       // Run Number
  int   number;                    // Event Number
  
  unsigned int  time[1];              // Time [0]:sec
  unsigned int  bcounters[NCOUNTERS]; // BCounter valses in LHCFL1T
 
 public:
  SclL1T(){clear();}
  SclL1T(char* name, char *title) : TNamed(name,title){clear();}
  ~SclL1T(){;}
  
  int  clear();
  int  copy(SclL1T* d);
  int  copydata(SclL1T* d);
  
  ClassDef(SclL1T,1);
};

#endif
