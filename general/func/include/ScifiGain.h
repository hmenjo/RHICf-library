#ifndef __SCIFIGAIN_H__
#define __SCIFIGAIN_H__

#include <TObject.h>

class ScifiGain{
 public:
  // constants
  static const char* SCIFIGAIN_FORMAT;
  static const int SCIFIGAIN_NHV = 5;
  static const int SCIFIGAIN_OK = 0;
  static const int SCIFIGAIN_ERROR = -1;
  static const int SCIFIGAIN_NODATA = 0;
  static const int SCIFIGAIN_DATA = 1;

 public:
  char   tablefile[256];
  char   format[100];
  int    version;
  int    type;
  
  int    nhv;
  int    checkhv[SCIFIGAIN_NHV];
  double gain[2][4][2][40][SCIFIGAIN_NHV];

 public:
  ScifiGain();
  ScifiGain(char* file);
  virtual ~ScifiGain(); 
 
  int    Initialize();
  int    GetType(){return type;}
  void   SetType(int t){type = t;}
  int    GetVersion(){return version;}
  void   SetVersion(int v){version = v;}
  int    ReadTable(char* file);
  int    ReadTableType1();
  int    WriteTable(int t,char* file);
  int    WriteTableType1();

  double GetGain(int it,int il,int ixy,int ipos,int ihv); 
  double GetGain(int it,int il,int ixy,int ipos,double hvv); 
  int    SetGain(int it,int il,int ixy,int ipos,int ihv,double value);
  int    errorchech(int it,int il,int ixy,int ipos,int ihv);
  int    HV2nHV(double tmp);
  int    nHV2HV(int ihv);
  int    NPos(int it);

  int    PrintStatus();

  ClassDef(ScifiGain,1);   // Control the gain table of SciFi
};

#endif
