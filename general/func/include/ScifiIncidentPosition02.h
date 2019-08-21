#ifndef __SCIFIINCIDENTPOSITION02_H__
#define __SCIFIINCIDENTPOSITION02_H__

//-----------------------------------------------------------------
//                    ScifiIncidentPosition02 
//-----------------------------------------------------------------

#include <TObject.h>

#include <TF1.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include "MyFunction.h"
#include "A1Cal2.h"
#include "ConScifiPosition.h"

class ScifiIncidentPosition02{
public:

  double pos[2][4][2];
  double qparam[2][4][2][6];
  double pede[2][4][2];
  ConScifiPosition*  scifipos;

  TF1          *f[2][4][2];       //!
  TGraphErrors *ge[2][4][2];      //!
  
public:
  ScifiIncidentPosition02();
  ScifiIncidentPosition02(char *file);
  virtual ~ScifiIncidentPosition02(){;}

  int    Initialize();
  int    Clear();
  int    ReadScifiPisition(char *file);
  int    SetConScifiPosition(ConScifiPosition* c){scifipos = c; return 0;}
  int    Calculate(A1Cal2* c2data,int it,int il,int ixy); 
  int    Calculate(A1Cal2* c2data,int it);
  double GetPos(int it=0,int il=0,int ixy=0){return pos[it][il][ixy];}
  double GetPosX(int it,int il=-1);
  double GetPosY(int it,int il=-1);
  double GetQParam(int it=0,int il=0,int ixy=0,int ip=0)
            {return qparam[it][il][ixy][ip];} 
  void   SetQParam(int it,int il,int ixy,int ip,double value);
  double GetBaseFluctuation(int it=-1,int il=-1,int ixy=-1);
  void   SetBaseFluctuation(int it,int il,int ixy,double value);
  void   SetBaseFluctuation(double value); 
  TF1*   GetFunction(int it,int il,int ixy){return f[it][il][ixy];}
 
  int    SetGraph(A1Cal2* c2data,int it,int il,int ixy);
  int    Draw(A1Cal2* c2data,int it,int il,int ixy);
  
  static const int SCIFIINCIDENTPOSITION02_OK    =  0;
  static const int SCIFIINCIDENTPOSITION02_ERROR = -10; 
  
  ClassDef(ScifiIncidentPosition02,1);   // Hit position search of SciFi (ver. MENJO)
};

#endif
