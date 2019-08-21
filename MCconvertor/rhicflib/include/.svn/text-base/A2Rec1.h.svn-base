#ifndef __A2REC1_H__
#define __A2REC1_H__

#include "Rec0.h"

class A2Rec1 : public Rec0 {
 public:
  A2Rec1();
  A2Rec1(char* name, char *title);
  virtual ~A2Rec1(); 
  
  int    resize();  

  virtual void   Show();

 public:
  // Interface functions
  // From evinfo == Event Information == 
  virtual int    GetEventQuality();             // Event Quality flag 
  virtual void   SetEventQuality(int d);
  virtual int    GetBeamColConf();              // Beam Colliding flag
  virtual void   SetBeamColConf(int d);
  virtual int    GetBunchNumber(int ib);        // Bunch Number (beam 1 or 2)
  virtual void   SetBunchNumber(int ib,int d);
  // From flags  == Flag ==
  virtual unsigned int GetFlags(int i);         // Flag from GPIO's (i-th)
  virtual void         SetFlags(int i, unsigned int d); 
  // From rec    == Reconstruction ==
  virtual double GetResultEnergy(int it);         // Recommended reconstructed energy (tower)
  virtual double GetResultEnergy(int it,int pid); // Recommended reconstructed energy (tower, pid)
  virtual void   SetResultEnergy(int it,int pid,double d); 
  virtual double GetSumdE(int it);              // Sum dE(layer=0-15) (tower)
  virtual void   SetSumdE(int it,double d);
  virtual double GetSumdE2(int it);             // Sum dE(layer=1-12) (tower)
  virtual void   SetSumdE2(int it,double d);  
  virtual double GetLeakageOut(int it);         // Shower Leakage parameter (tower)
  virtual void   SetLeakageOut(int it,double d);
  virtual double GetEnergyScaleFactor(int it);  // Correction factor of energy scale (tower)
  virtual void   SetEnergyScaleFactor(int it,double d);
  // From pos    == Position ==
  virtual double GetResultHitPosition(int it, int ixy);      // Recommended hit position results (tower, xy)
  virtual void   SetResultHitPosition(int it, int ixy,double d); 
  virtual int    GetResultNumberOfHits(int it);              // Recommended number of hit results (tower)
  virtual void   SetResultNumberOfHits(int it, int d); 
  virtual int    GetNumberOfHits(int it,int il,int ixy);     // Number of Hits in the tower (tower,layer,xy)
  virtual void   SetNumberOfHits(int it,int il,int ixy, int d);
  virtual double GetHitPosition(int it,int il, int ixy);     // Hit Position in each layer (tower,layer,xy)
  virtual void   SetHitPosition(int it,int il, int ixy, double d); 
  virtual double GetPeakStrip(int it,int il,int ixy);        // Strip number with maximum dE (tower,layer,xy)
  virtual void   SetPeakStrip(int it,int il,int ixy, double d);
  virtual double GetdEAtPeak(int it,int il,int ixy);         // dE at peak (tower,layer,xy)
  virtual void   SetdEAtPeak(int it,int il,int ixy,double d);
  virtual int    GetSiSatuFlag(int it,int il,int ixy);       // Saturation flag of silicon middle sample
  virtual void   SetSiSatuFlag(int it,int il,int ixy,int d);  
  // From pid    == PID ==
  virtual int    GetResultPID(int it);             // Recommended PID result (tower)
  virtual void   SetResultPID(int it,int d);        
  virtual double GetL20(int it);                   // L20% (tower)
  virtual void   SetL20(int it,double d);
  virtual double GetL90(int it);                   // L90% (tower) 
  virtual void   SetL90(int it,double d);

  ClassDef(A2Rec1,1);    // Data for Reconstruction : Arm2 Format 1
};


#endif 
