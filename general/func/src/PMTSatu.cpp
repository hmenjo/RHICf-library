#ifndef __PMTSATU_CPP__
#define __PMTSATU_CPP__

#include "PMTSatu.h"

//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ Class PMTSatu to obtain saturation corrected ADC value                +++
//+++     based on the laser calibration in Nagoya 2006.                    +++
//+++                                                                       +++
//+++ USAGE:                                                                +++
//+++   PMTSatu pmtsatu;                 // call constructor                +++
//+++   pmtsatu.SetPMT( arm, tower, ch)  // specify channel                 +++
//+++   pmtsatu.GetParam();              // find parameters of set cahnnel  +++
//+++                                    // (this can be skipped in future) +++
//+++   double adc_new = pmtsatu.ADC2ADC( hv, adc);                         +++
//+++                                    // return satu-corr ADC value      +++
//+++                                                                       +++
//+++ 20100809: First Edition by T.Sako                                     +++
//+++ 20100811: improve for easier use                                      +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(PMTSatu);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <cstdio>
using namespace std;

// ------- DEFINITION AND PARAMETERS ------
const int    PMTSatu::NPMTMAX;
const int    PMTSatu::NHV;
const int    PMTSatu::HV[NHV] = {375,400,425,450,475,500,550,600,800,1000,1100};
const double PMTSatu::NAGOYACABLE = 0.9;
const double PMTSatu::AMPFACTOR = 4.8;
const double PMTSatu::SPSCABLE = 0.962;
const double PMTSatu::SPS2LHCCABLE = 0.896;
const double PMTSatu::GATE200TO500 = 1.1;
const double PMTSatu::ADCCONV = NAGOYACABLE/(AMPFACTOR*SPSCABLE*SPS2LHCCABLE*GATE200TO500);

PMTSatu::PMTSatu() {
  // Default table path and pmt_table file 
  // "general/tables/pmtsatutables and pmt_table.dat" 
  // are set. 
#ifdef COMPILEDIR
  string comdir = COMPILEDIR;
  if(comdir.rfind("func")!=string::npos){
    comdir = comdir.substr(0,comdir.rfind("func"));
  }
  Init((char*)(comdir+"/tables/pmtsatutables").c_str(),
       "pmt_table.dat");
#else
  Init("./tables", "pmt_table.dat");
#endif

  return;
}

PMTSatu::PMTSatu( char* tpath, char* fname) {
  // Construct with setting up the table path and pmt_table file
  Init( tpath, fname);
  return;
}

PMTSatu::~PMTSatu() {
  return;
}

void PMTSatu::Init( char* tpath, char* fname) {
  pmttable.npmt = 0; 
  strcpy( tablepath, tpath);
  strcpy( pmttablename, fname);
  if( FillPMTTable() > 0){  
    FillParamTable();
  }
  return;
}

int PMTSatu::FillPMTTable() {
  char buf[20];
  char fname[140];
  sprintf(fname, "%s/%s", tablepath, pmttablename);
  ifstream ifile(fname);
  if(!ifile){
    return -1;
  }
  
  pmttable.npmt = 0; 

  while ( !ifile.eof() && pmttable.npmt<NPMTMAX ) {
    ifile >> buf;
    if ( strcmp(buf,"END")==0 ) break;

    strcpy( pmttable.pmtname[pmttable.npmt], buf);
    ifile >> pmttable.size[pmttable.npmt]
          >> pmttable.ch[pmttable.npmt] 
          >> pmttable.flag[pmttable.npmt];

    if ( pmttable.size[pmttable.npmt]==20 ) {
      pmttable.arm[pmttable.npmt] = 0;
      pmttable.tower[pmttable.npmt] = 0;
    } else if ( pmttable.size[pmttable.npmt]==40 ) {
      pmttable.arm[pmttable.npmt] = 0;
      pmttable.tower[pmttable.npmt] = 1;
    } else if ( pmttable.size[pmttable.npmt]==25 ) {
      pmttable.arm[pmttable.npmt] = 1;
      pmttable.tower[pmttable.npmt] = 0;
    } else if ( pmttable.size[pmttable.npmt]==32 ) {
      pmttable.arm[pmttable.npmt] = 1;
      pmttable.tower[pmttable.npmt] = 1;
    } else cerr << "Tower size invalid" << endl;

    pmttable.npmt++;
  }

  ifile.close();
#ifdef DEBUG
  cout << pmttable.npmt << " PMTs detected in the table." << endl;
#endif

  return pmttable.npmt;
}

int PMTSatu::FillParamTable() {
  int setpmt;

  for ( int arm=0; arm<2; arm++) {
    for ( int tower=0; tower<2; tower++) {
      for ( int ch=0; ch<16; ch++) {
	setpmt = FindPMT(arm, tower, ch);
	if ( setpmt != -1) {
  	  GetParam(setpmt, arm, tower, ch);
	} else {
	  for ( int hv=0; hv<NHV; hv++) {
            spoint[arm][tower][ch][hv]  = -99.9;
            slope[arm][tower][ch][hv]   = -99.9;
            coef2nd[arm][tower][ch][hv] = -99.9;
	  }
	}
      }
    }
  }

  return 0;
}

int PMTSatu::FindPMT(int arm, int tower, int ch) {
  int setpmt = -1;

  for ( int ipmt=0; ipmt<pmttable.npmt; ipmt++ ) {
    if ( pmttable.arm[ipmt]==arm && pmttable.tower[ipmt]==tower && 
         pmttable.ch[ipmt]==ch && pmttable.flag[ipmt]==1 ) { setpmt=ipmt;}
  }

  return setpmt;
}

int PMTSatu::GetParam( int setpmt, int arm, int tower, int ch) {
  if ( setpmt<0 ) {
    cerr << "PMT is not set properly" << endl;
    return -1;
  }

  char fname[140];
  sprintf( fname, "%s/param_%s.out", tablepath, pmttable.pmtname[setpmt]);
  ifstream ifile(fname);

  char buf[50];
  int hv, ihv=0;
  double dum;

  while ( !ifile.eof() ) {
    ifile >> buf;

    if ( strcmp( buf, "HV")==0 ) {
      ifile >> hv;
      ihv = GetIHV( hv);
    }
    if ( strcmp( buf, "FIT_PARAM")==0 ) {
      ifile >> dum >> spoint[arm][tower][ch][ihv] 
                   >> slope[arm][tower][ch][ihv]
                   >> coef2nd[arm][tower][ch][ihv];
      //      cout << dum << " " << spoint[arm][tower][ch][ihv] 
      //                  << " " << slope[arm][tower][ch][ihv]
      //                  << " " << coef2nd[arm][tower][ch][ihv] << endl;
    }
  }

  ifile.close();

  return 0;
}

int PMTSatu::GetIHV( int hv) {
  int ihv;
  for ( ihv=0; ihv<NHV; ihv++) if ( hv==HV[ihv] ) break;
  return ihv;
}

double PMTSatu::ADC2ADC( int arm, int tower, int ch, int hv, double adc) {
  // Main function of this correction.
  // this function returns the corrected adc value.
  //  arm   : 0 (Arm1), 1 (Arm2)
  //  tower : 0 (small), 1(large)
  //  ch    : 0-15
  //  hv    : 375, 400,.... (give interger value, this value must be in HV[])
  //  adc   : ADC value (eq. low range adc after pedestal subtraction)
  
  int ihv = GetIHV(hv);
  
  if ( slope[arm][tower][ch][ihv]<0.0 ) {
    cerr << "ERROR : Parameter not filled properly." << endl;
    return adc;
  }

  double x = adc*ADCCONV;
  double y_linear = slope[arm][tower][ch][ihv] * x;
  double y_satu;

  double x0 = spoint[arm][tower][ch][ihv];
  double a = coef2nd[arm][tower][ch][ihv];
  double b = slope[arm][tower][ch][ihv] - 2*a*x0;
  double c = a*x0*x0;

  if ( x<x0 ) y_satu = y_linear;
  else y_satu = a*x*x + b*x + c;

  double ratio;
  if(adc > 0.0001){
    ratio = y_satu/y_linear;
  }
  else{
    ratio = 1.;
  }
  return adc*ratio; 
}

double PMTSatu::InvADC2ADC(int arm, int tower, int ch, int hv, double adc){
  // Add the saturation to simulation results
  // this function returns the calculated adc value.
  //  arm   : 0 (Arm1), 1 (Arm2)
  //  tower : 0 (small), 1(large)
  //  ch    : 0-15
  //  hv    : 375, 400,.... (give interger value, this value must be in HV[])
  //  adc   : ADC value (eq. low range adc after pedestal subtraction)
  
  int ihv = GetIHV(hv);
  
  if ( slope[arm][tower][ch][ihv]<0.0 ) {
    cerr << "ERROR : Parameter not filled properly." << endl;
    return 0.0;
  }

  double x = adc*ADCCONV * slope[arm][tower][ch][ihv];
  double y_linear = adc*ADCCONV;
  double y_satu;

  double x0 = spoint[arm][tower][ch][ihv];
  double a = coef2nd[arm][tower][ch][ihv];
  double b = slope[arm][tower][ch][ihv] - 2*a*x0;
  double c = a*x0*x0;

  if ( x< (x0*slope[arm][tower][ch][ihv]) ) y_satu = y_linear;
  else y_satu = sqrt( (x+b*b/(4.*a)-c)/a ) -b/(2.*a); 
  
  if(y_linear>0.001){
    double ratio = y_satu/y_linear;
    return adc*ratio; 
  }
  else{
    return adc;
  }
}

double PMTSatu::GetParamSpoint(int arm, int tower, int ch, int hv){
  return spoint[arm][tower][ch][GetIHV(hv)];
}

double PMTSatu::GetParamSlope(int arm, int tower, int ch, int hv){
  return slope[arm][tower][ch][GetIHV(hv)];
}

double PMTSatu::GetParamCoef2nd(int arm, int tower, int ch, int hv){
  return coef2nd[arm][tower][ch][GetIHV(hv)];
}
#endif
