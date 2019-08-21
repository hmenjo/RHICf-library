#ifndef __SCINTIPOSDEPENDENCE_H__
#define __SCINTIPOSDEPENDENCE_H__

//-----------------------------------------------------------------
//                        ScintiPosDependence   
//-----------------------------------------------------------------

#include <TObject.h>

#include "A1Cal2.h"
#include "A2Cal2.h"

class ScintiPosDependence{
protected:
  char       file[256];
  char       format_type[256];
  int        format;
  int        version;
  char       date[256];
  char       person[256];

  double     C[4][16][10];

public:
  ScintiPosDependence();
  ScintiPosDependence(char* file);
  virtual ~ScintiPosDependence(){;}
  
  int        Initialize();
  int        ReadFile(char* file);
  double     GetFunctionFactor(int ssn,int sn,int i);
  double     GetFunctionFactor(int ideterctor,int itower,int sn,int i);
  int        SetFunctionFactor(int ssn,int sn,int i, double value);
  int        SetFunctionFactor(int ideterctor,int itower,int sn,int i,double value);
  double     GetEfficiency(int ssn,int sn,double x, double y);
  double     GetEfficiency(int ideterctor,int itower,int sn,double x, double y);

  int        Calibration(A1Cal2* d,int it,double x,double y);
  int        Calibration(A2Cal2* d,int it,double x,double y);
  
  static const int SCINTIPOSDEPENDENCE_OK    =  0;
  static const int SCINTIPOSDEPENDENCE_ERROR = -1; 

  ClassDef(ScintiPosDependence,1);   // Control the parameter table of position dependence of light yield on each scintillator.
};

#endif
