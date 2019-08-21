#ifndef __A1GAINCALIBRATION_H__
#define __A1GAINCALIBRATION_H__

//-----------------------------------------------------------------------
//                            A1GainCalibration  
//            For detail, see A1GainCalibration.cpp or Online Manual 
//-----------------------------------------------------------------------

#include <TObject.h>

#include "globaldef.h"
#include "ConParticleDefine.h"
#include "PMTGain.h"
#include "ScifiGain.h"
#include "FCGain.h"
#include "A1Cal2.h"

#include <string>
using namespace std;

class A1GainCalibration {
 private:
  int      detector;
  double   hv[2][16];
  double   scifihv;
  double   fchv[2];
  double   pdeffactor_pmt;   // constant factor for partice definition of calorimters.
                             // it is used to calibrate the pdef factor
                             // from SPS2007 to LHC.
  double   pdeffactor_scifi; // constant factor for pdef of SciFi.
  double   pdeffactor_fc;    // constant factor for pdef of Front Counter.
  ConParticleDefine pdeftable;  
  PMTGain           pmtgaintable; 
  ScifiGain         scifigaintable;
  FCGain            fcgaintable;

 public:
  A1GainCalibration(){Initialize();}
  virtual ~A1GainCalibration(){;}
  
  int                Initialize();
  int                SetPdefFactorPMT(double value);
  int                SetPdefFactorScifi(double value);
  int                SetPdefFactorFC(double value);
  double             GetPdefFactorPMT(){return pdeffactor_pmt;}
  double             GetPdefFactorScifi(){return pdeffactor_scifi;}
  double             GetPdefFactorFC(){return pdeffactor_fc;}
  int                ReadParticleDefineTable(char *file,char* option="ADC SCIFI FC");
  int                ReadPMTGainTable(char *file);
  int                ReadScifiGainTable(char *file);
  int                ReadFCGainTable(char *file);
  ConParticleDefine* GetParticleDefineTable(){return &pdeftable;}
  PMTGain*           GetPMTGainTable(){return &pmtgaintable;}
  ScifiGain*         GetScifiGainTable(){return &scifigaintable;}
  FCGain*            GetFCGainTable(){return &fcgaintable;}
  int                SetHV(int it,int il, double value);
  int                SetScifiHV(double value);
  int                SetFCHV(int id,double value);
  double             GetHV(int it,int il){return hv[it][il];}
  double             GetScifiHV(){return scifihv;}
  double             GetFCHV(int id){return fchv[id-1];}

  double             GetParticleADC(int it,int il);

  int                ReadHVTable(char* file,char* option="ADC SCIFI FC");
  int                ShowHVTable();
  int                ShowHVTable(string &s);

  int                Calculate(A1Cal2* data);     // Execute CalculatePMT,Scifi and FC.
  int                CalculatePMT(A1Cal2* data);
  int                CalculateScifi(A1Cal2* data);
  int                CalculateFC(A1Cal2* data);
  int                InverseCalculate(A1Cal2* data);  
  int                InverseCalculate_pp2015(A1Cal2* data);  // Makino
  int                InverseCalculatePMT(A1Cal2* data);
  int                InverseCalculatePMT_pp2015(A1Cal2* data); // Makino
  int                InverseCalculateScifi(A1Cal2* data);
  int                InverseCalculateFC(A1Cal2* data);

 public:  
  // for online analysis
  int Init();
  int Exit();
  int Bor();
  int Eor(){return OK;}
  int Loop(A1Cal2* data);

  
  static const double DEFAULT_PDEFFACTOR_PMT; // SPS2007 pdef -> LHC pdef
  static const double DEFAULT_PDEFFACTOR_SCIFI;
  static const double DEFAULT_PDEFFACTOR_FC;  
  static const char*  DEFAULT_PDEFTABLE;
  static const char*  DEFAULT_PMTGAINTABLE;
  static const char*  DEFAULT_SCIFIGAINTABLE;  
  static const char*  DEFAULT_FCGAINTABLE;
  static const char*  DEFAULT_HVTABLE;

  ClassDef(A1GainCalibration,1);   // Gain Calibration of Arm1.

};

#endif

