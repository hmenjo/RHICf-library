#ifndef __A1REC2_H__
#define __A1REC2_H__

#include "Rec0.h"

class A1Rec2 : public Rec0 {

 public:
  A1Rec2();
  A1Rec2(char* name, char *title);
  virtual ~A1Rec2(); 
  
  int            resize();  
  virtual void   Show();

  enum BITMAP_FLAGANALYSIS {
    HARDWARETRIGGER = 0x1,
    SOFTWARETRIGGER = 0x2,
    CRITERIA1       = 0x4,
    CRITERIA2       = 0x8
  };

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
  virtual unsigned int GetAnalysisFlags(int i);  // Analysis flag (i-th)
  virtual void         SetAnalysisFlags(int i, unsigned int d);
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
  virtual double GetPeakPosition(int it,int il,int ixy);     // Fiber number with maximum dE (tower,layer,xy)
  virtual void   SetPeakPosition(int it,int il,int ixy, double d);
  virtual double GetdEAtPeak(int it,int il,int ixy);         // dE at peak (tower,layer,xy)
  virtual void   SetdEAtPeak(int it,int il,int ixy,double d);
  //virtual int    GetSatuFlag(int it,int il,int ixy);         // Saturation flag for Arm2 
  //virtual void   SetSatuFlag(int it,int il,int ixy,int d);  
  // From pid    == PID ==
  virtual int    GetResultPID(int it);             // Recommended PID result (tower)
  virtual void   SetResultPID(int it,int d);        
  virtual double GetL20(int it);                   // L20% (tower)
  virtual void   SetL20(int it,double d);
  virtual double GetL90(int it);                   // L90% (tower) 
  virtual void   SetL90(int it,double d);
  virtual double GetL2D(int it);                   // L2D(tower)
  virtual void   SetL2D(int it,double d);          
  // From pos    == Multi-Hit ==
  virtual double GetMHBkgPar(int tower, int layer, int xy, int ipar);             // Results of Background Fitting by a linear function 
  virtual void   SetMHBkgPar(int tower, int layer, int xy, int ipar, double val); 
  virtual int    GetMHNhits(int tower, int layer, int xy);                        // Number of Hits in the layer (layer, xy) includeing discarded peaks
  virtual void   SetMHNhits(int tower, int layer, int xy, int nhits);   
  virtual int    GetMHParPos(int tower, int layer,int xy, int ihits, int ipar);   // Return the position of parameter in the array.        
  virtual double GetMHPar(int tower, int layer,int xy, int ihit, int ipar);       // Parameter of Multi-hit fitting (layer, xy, ihit, ipar);
  virtual void   SetMHPar(int tower, int layer,int xy, int ihit, int ipar,double val);  // To modify the parameter value. 
  virtual bool   GetMHDiscardedFlag(int tower, int layer,int xy, int ihit);
  virtual int    AddMHHit(int tower, int layer, int xy, double *par);             // Add new the hit parameters  
  virtual int    EraseMHHit(int tower, int layer, int xy, int ihit);              // Erase the hit in the array. 
  virtual int    GetMHNumberOfHits(int tower);                                    // Number of hits in the tower (except discarded peaks)
  virtual void   SetMHNumberOfHits(int tower, int val);                


  ClassDef(A1Rec2,1);    // Data for Reconstruction : Arm1 Format 2 (Hadron analysis)
};


#endif 
