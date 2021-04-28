// ****************************************************************
// *** FCGain Class                                             ***
// *** now this is dummy                                        ***
// ****************************************************************

#ifndef __FCGAIN_H__
#define __FCGAIN_H__

//-----------------------------------------------------------------
//                          FCGain     
//-----------------------------------------------------------------

#include <TObject.h>

class FCGain{
 public:
  // constants
  static const char* FCGAIN_FORMAT;
  static const int FCGAIN_NHV = 2;
  static const int FCGAIN_OK = 0;
  static const int FCGAIN_ERROR = -1;
  static const int FCGAIN_NODATA = 0;
  static const int FCGAIN_DATA = 1;

 public:
  char   tablefile[256];
  char   format[100];
  int    version;
  int    type;
  
  int    nhv;
  int    checkhv[FCGAIN_NHV];
  double gain[2][4][FCGAIN_NHV]; // detector:channel:ihv

 public:
  FCGain();
  FCGain(char* file);
  virtual ~FCGain(); 

  int    Initialize();
  int    GetType(){return type;}
  void   SetType(int t){type = t;}
  int    GetVersion(){return version;}
  void   SetVersion(int v){version = v;}
  int    ReadTable(char* file);
  int    ReadTableType1();
  int    WriteTable(int t,char* file);
  int    WriteTableType1();

  double GetGain(int id,int ich,int ihv); 
  double GetGain(int id,int ich,double hvv); 
  int    SetGain(int id,int ich,int ihv,double value);
  int    errorchech(int id,int ich,int ihv);
  int    HV2nHV(double tmp);
  double nHV2HV(int ihv);

  int    PrintStatus();
  
  ClassDef(FCGain,1);   // Control the gain table of F.C. 
};

#endif
