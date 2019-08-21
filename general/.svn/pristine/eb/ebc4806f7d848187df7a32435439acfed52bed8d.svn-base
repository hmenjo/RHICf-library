#ifndef __A2REC2_H__
#define __A2REC2_H__

// ---------------------------------------------------------------------------
//
//                                 A2Rec2
//                     Extention of A2Rec1 for Multi-Hit
// 
// ---------------------------------------------------------------------------

#include "A2Rec1.h"

class A2Rec2 : public A2Rec1 {
  
 public:
  vector<double>       posmh;              // For Multi-Hit

 public:
  A2Rec2();
  A2Rec2(char* name, char *title);
  virtual ~A2Rec2(); 
  
  int            resize();  

  virtual void   Show();

 public:
  // Interface functions
  // From pos    == Multi-Hit ==
  virtual double GetMHBkgPar(int layer, int xy, int ipar);             // Results of Background Fitting by a linear function 
  virtual void   SetMHBkgPar(int layer, int xy, int ipar, double val); 
  virtual int    GetMHNhits(int layer, int xy);                        // Number of Hits in the layer (layer, xy) includeing discarded peaks
  virtual void   SetMHNhits(int layer, int xy, int nhits);   
  virtual int    GetMHParPos(int layer,int xy, int ihits, int ipar);   // Return the position of parameter in the array.        
  virtual double GetMHPar(int layer,int xy, int ihit, int ipar);       // Parameter of Multi-hit fitting (layer, xy, ihit, ipar);
  virtual void   SetMHPar(int layer,int xy, int ihit, int ipar,double val);  // To modify the parameter value. 
  virtual bool   GetMHDiscardedFlag(int layer,int xy, int ihit);
  virtual int    AddMHHit(int layer, int xy, double *par);             // Add new the hit parameters  
  virtual int    EraseMHHit(int layer, int xy, int ihit);              // Erase the hit in the array. 

  virtual int    GetMHNumberOfHits(int tower);                         // Number of hits in the tower (except discarded peaks)
  virtual void   SetMHNumberOfHits(int tower, int val);                

  ClassDef(A2Rec2,1);    // Data for Reconstruction : Arm2 Format 2
};


#endif 
