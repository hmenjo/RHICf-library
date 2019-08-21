// *********************************************************************
// ***    GParamD064                                                 ***
// *** Data Stock for General Parameters                             ***
// *** This can store 64 double parameters                           ***
// *** ------------------------------------------------------------- *** 
// *** 20 Nov. 08: First Edited by H.MENJO                           ***
// *********************************************************************

#ifndef __GParamD64_H__
#define __GParamD64_H__

#include <TNamed.h>
#include "globaldef.h"

class GParamD64 : public TNamed {
 public:
  int    run;          // Run Number
  int    number;       // Event number
  int    gnumber;      // Grobal event number
  
  double paramd[64];   //
  
 public:
  GParamD64(){clear();}
  GParamD64(char* name, char *title) : TNamed(name,title){clear();}
  ~GParamD64(){;}
  
  int    clear();
  int    copy(GParamD64* d);
  int    copydata(GParamD64* d); 

  void   SetD(int i,double value){paramd[i]=value;} 
  double GetD(int i){return paramd[i];}
  void   Set(int i,double value){SetD(i,value);}
  double Get(int i){return GetD(i);}
  
  ClassDef(GParamD64,1);
};

#endif

