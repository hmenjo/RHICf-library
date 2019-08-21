#ifndef __A2INFO_H__
#define __A2INFO_H__

#include <TNamed.h>
#include "globaldef.h"

class A2Info : public TNamed {
 public:
  int      run;         // Run Number
  int      runmode;     // Rum Mode
  bool     isrunning;   // 1: running , 0: not running
  int      start_time;  // Start Time [UTC]
  int      end_time;    // End Time [UTC]
  int      nev_trg;     // Number of Trigger2 events  
  int      nev_scl;     // Number of Sclar2 events
  
 public:
  A2Info(){clear();}
  A2Info(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Info(){;}
    
  int    clear();
  
  ClassDef(A2Info,1);
};

#endif
