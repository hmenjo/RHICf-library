#ifndef __PMTGAIN_H__
#define __PMTGAIN_H__

//-----------------------------------------------------------------
//                           PMTGain
//-----------------------------------------------------------------

#include <TObject.h>

class PMTGain
{
public:
  // constants 
  static const int PMTGAIN_OK = 0;
  static const int PMTGAIN_ERROR = -1;
  static const int PMTGAIN_NODATA = -1;

  static const int PMTGAIN_ND  = 2;    // detector
  static const int PMTGAIN_NT  = 2;    // tower
  static const int PMTGAIN_NP  = 18;   // PMT
  static const int PMTGAIN_NHV = 101; // HV

protected:
  char   tablefile[256];
  
  char   format[100];
  int    version;
  int    type;
  int    date;
  
  int    nhv;
  double hv[PMTGAIN_NHV];
  char   sn[PMTGAIN_ND][PMTGAIN_NT][PMTGAIN_NP][10];
  int    caln[PMTGAIN_ND][PMTGAIN_NT][PMTGAIN_NP];
  double gain[PMTGAIN_ND][PMTGAIN_NT][PMTGAIN_NP][PMTGAIN_NHV];

public:
  PMTGain();
  PMTGain(char* file);
  virtual ~PMTGain(){;}

  int    Initalize();
  int    ReadTable(char* file);
  int    ReadTableType2();
  int    ReadTableType3();

  char*  GatTable(){return tablefile;}
  char*  GetFormat(){return format;}
  int    GetVersion(){return version;}
  int    GetType(){return type;}
  int    GetDate(){return date;}
  int    GetNHV(){return nhv;}
  double GetGain(int id,int it,int il,int ihv);
  double GetGain(int id,int it,int il,double hvv);
  double GetGain(int it,int il,int ihv);
  double GetGain(int it,int il,double hvv);

  int    HV2nHV(double tmp);
  double nHV2HV(int ihv){return hv[ihv];}
  int    TSize2iT(int size);
  int    TSize2iD(int size);
  int    TSize2D(int size);
  int    iT2TSize(int id ,int it);

  int    PrintStatus();  

  ClassDef(PMTGain,1);   // Control the gain table of all PMTs.
};

#endif 
