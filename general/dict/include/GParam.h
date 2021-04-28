// *********************************************************************
// ***    GParam                                                     ***
// *** Data Stock for General Parameters                             ***
// *** ------------------------------------------------------------- *** 
// *** 19 Sep. 08: First Edited by H.MENJO                           ***
// *********************************************************************

#ifndef __GParam_H__
#define __GParam_H__

#include <TNamed.h>
#include "globaldef.h"

class GParam : public TNamed {
 public:
  int    run;          // Run Number
  int    number;       // Event number
  int    gnumber;      // Grobal event number
  
  int    parami[32];   //
  double paramd[32];   //
  
 public:
  GParam(){clear();}
  GParam(char* name, char *title) : TNamed(name,title){clear();}
  ~GParam(){;}
  
  int    clear();
  int    copy(GParam* d);
  int    copydata(GParam* d); 
  
  void   SetI(int i,int value){parami[i]=value;} 
  int    GetI(int i){return parami[i];}
  void   SetD(int i,double value){paramd[i]=value;} 
  double GetD(int i){return paramd[i];}
  
  ClassDef(GParam,1);
};

#endif

