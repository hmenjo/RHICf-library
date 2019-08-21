#ifndef __SILICONGAIN_H__
#define __SILICONGAIN_H__

// ----------------------------------------------------------------
// SiliconGain 
// 
// Not coded yet
// 
// ---------------------------------------------------------------

#include "globaldef.h"
#include "TNamed.h"

class SiliconGain{

 public:
  char   tablefile[256];
  char   format[100];
  int    version;
  int    type;
  
 public:
  SiliconGain();
  virtual ~SiliconGain();
  int    Initialize();
  int    GetType(){return type;}
  void   SetType(int t){type = t;}
  int    GetVersion(){return version;}
  void   SetVersion(int v){version = v;}
  int    ReadTable(char* file){return OK;;}
  int    ReadTableType1(){return OK;;}
  int    WriteTable(int t,char* file){return OK;}
  int    WriteTableType1(){return OK;;}
  
  double GetGain(int il,int ixy,int istrip,int ihv=0) { return 1.;}

 public:
  static const char* SILICONGAIN_FORMAT;
  static const int   SILICON_NODATA = 0;
  static const int   SILICON_DATA   = 1;

  ClassDef(SiliconGain,1);   // Control the gain table of silicon (Dummy)
};


#endif
