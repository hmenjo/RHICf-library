#ifndef __A2GAINCALIBRATION_H__
#define __A2GAINCALIBRATION_H__

//-----------------------------------------------------------------------
//                            A2GainCalibration  
//            For detail, see A2GainCalibration.cpp or Online Manual 
//-----------------------------------------------------------------------

#include "globaldef.h"
#include "A2Cal2.h"
#include "ConParticleDefine.h"
#include "PMTGain.h"
#include "FCGain.h"
#include "SiliconGain.h"

#include <string>
using namespace std;

class A2GainCalibration {
 private:
  int      detector;
  double   hv[2][16];
  double   siliconhv;
  double   fchv[2];
  double   pdeffactor_pmt;     // constant factor for partice definition of calorimters.
                               // it is used to calibrate the pdef factor
                               // from SPS2007 system to LHC system.
  double   pdeffactor_silicon; // constant factor for pdef of Silicon.
  double   pdeffactor_fc;      // constant factor for pdef of Front Counter.
  ConParticleDefine pdeftable;  
  PMTGain           pmtgaintable; 
  FCGain            fcgaintable;
  SiliconGain       sigaintable;
    
 public:
  A2GainCalibration(){Initialize();}
  virtual ~A2GainCalibration(){;}
  
  int                Initialize();
  int                SetPdefFactorPMT(double value);
  int                SetPdefFactorSilicon(double value);
  int                SetPdefFactorFC(double value);
  double             GetPdefFactorPMT(){return pdeffactor_pmt;}
  double             GetPdefFactorSilicon(){return pdeffactor_silicon;}
  double             GetPdefFactorFC(){return pdeffactor_fc;}
  int                ReadParticleDefineTable(char *file,char* option="ADC SILICON FC");
  int                ReadPMTGainTable(char *file);
  int                ReadSiliconGainTable(char *file); // not yet
  int                ReadFCGainTable(char *file);
  ConParticleDefine* GetParticleDefineTable(){return &pdeftable;}
  PMTGain*           GetPMTGainTable(){return &pmtgaintable;}
  SiliconGain*       GetSiliconGainTable(){return &sigaintable;}
  FCGain*            GetFCGainTable(){return &fcgaintable;}  
  int                SetHV(int it,int il, double value);
  int                SetSiliconHV(double value);
  int                SetFCHV(int id,double value);
  double             GetHV(int it,int il){return hv[it][il];}
  double             GetSiliconHV(){return siliconhv;}
  double             GetFCHV(int id){return fchv[id-1];}

  double             GetParticleADC(int it,int il);
  
  int                ReadHVTable(char* file,char* option="ADC SILICON FC");
  int                ShowHVTable();
  int                ShowHVTable(string &s);

  int                Calculate(A2Cal2* data);     // Execute CalculatePMT,Silicon and FC.
  int                CalculatePMT(A2Cal2* data);
  int                CalculateSilicon(A2Cal2* data);   // not yet
  int                CalculateFC(A2Cal2* data);
  int                InverseCalculate(A2Cal2* data);  
  int                InverseCalculatePMT(A2Cal2* data);
  int                InverseCalculateSilicon(A2Cal2* data); // not yet
  int                InverseCalculateFC(A2Cal2* data);

 public:  
  // for online analysis
  int Init();
  int Exit();
  int Bor();
  int Eor(){return OK;}
  int Loop(A2Cal2* data);
  
  static const double DEFAULT_PDEFFACTOR_PMT;
  static const double DEFAULT_PDEFFACTOR_SILICON;
  static const double DEFAULT_PDEFFACTOR_FC; 
  static const char*  DEFAULT_PDEFTABLE;
  static const char*  DEFAULT_PMTGAINTABLE;
  static const char*  DEFAULT_SILICONGAINTABLE;  
  static const char*  DEFAULT_FCGAINTABLE;
  static const char*  DEFAULT_HVTABLE;
  
  ClassDef(A2GainCalibration,1);   // Gain Calibration of Arm2.

};

#endif

