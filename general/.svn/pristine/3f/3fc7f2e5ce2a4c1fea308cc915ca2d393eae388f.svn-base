#ifndef __PMTSATU_H__
#define __PMTSATU_H__

// -------------------------------------------------------------------------
//                                  PMTSatu
//             For detail, refer PMTSatu.cpp or Online Manual 
// -------------------------------------------------------------------------

#include "TNamed.h"

class PMTSatu {
 public:
  // -- DEFINITIONS and PARAMETERS --
  static const int NPMTMAX = 80;
  static const int NHV = 11;
  static const int HV[NHV];
  static const double NAGOYACABLE;   //+++ To be studied !! +++
  static const double AMPFACTOR;
  static const double SPSCABLE ;
  static const double SPS2LHCCABLE;
  static const double GATE200TO500;  //+++ To be studied !! +++
  static const double ADCCONV;  

 protected:
  struct PMTTable {
    int npmt;
    char pmtname[NPMTMAX][10];
    int arm[NPMTMAX];    //+++ 0 (arm1)  or 1 (arm2) 
    int tower[NPMTMAX];  //+++ 0 (small) or 1 (large)
    int size[NPMTMAX];   //+++ 20, 25, 32, 40 +++
    int ch[NPMTMAX];     //+++ 0-15 (and 16, 17 for spare)
    int flag[NPMTMAX];   //+++ 0 (not use) or 1 (in use)
  } pmttable;
 
  double spoint[2][2][16][NHV];   //+++ saturation point           +++
  double slope[2][2][16][NHV];    //+++ linear slope               +++
  double coef2nd[2][2][16][NHV];  //+++ parabolic term coefficient +++

  char tablepath[100];
  char pmttablename[40];

 public:
  PMTSatu();
  PMTSatu( char* tpath, char* fname);
  virtual ~PMTSatu();
  void Init(char* tpath, char* fname);
  int FillPMTTable();
  int FillParamTable();
  int FindPMT( int arm, int tower, int ch);
  int GetParam( int setpmt, int arm, int tower, int ch);
  int GetIHV( int hv);
  double ADC2ADC( int arm, int tower, int ch, int hv, double adc);
  double InvADC2ADC(int arm, int tower, int ch, int hv, double adc);

  double GetParamSpoint(int arm, int tower, int ch, int hv);
  double GetParamSlope(int arm, int tower, int ch, int hv);
  double GetParamCoef2nd(int arm, int tower, int ch, int hv);

  ClassDef(PMTSatu,1);   // Correction of PMT saturation.
};

#endif
