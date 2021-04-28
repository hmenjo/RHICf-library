#ifndef __A1INFO_H__
#define __A1INFO_H__

#include <TNamed.h>
#include "globaldef.h"

class A1Info : public TNamed {
 public:
  int      run;         // Run Number
  int      runmode;     // Rum Mode
  bool     isrunning;   // 1: running , 0: not running
  int      start_time;  // Start Time [UTC]
  int      end_time;    // End Time [UTC]
  int      nev_trg;     // Number of Trigger1 events  
  int      nev_scl;     // Number of Sclar1 events
  
 public:
  A1Info(){clear();}
  A1Info(char* name, char *title) : TNamed(name,title){clear();}
  ~A1Info(){;}
    
  int    clear();
  
  ClassDef(A1Info,1);
};

#endif
