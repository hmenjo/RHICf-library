#ifndef __A2REC3_H__
#define __A2REC3_H__

// ---------------------------------------------------------------------------
//
//                                 A2Rec3
//                Extention of A2Rec2 for Transition Fitting
// 
// ---------------------------------------------------------------------------

#include "A2Rec2.h"

class A2Rec3 : public A2Rec2 {
  
 public:
  A2Rec3();
  A2Rec3(char* name, char *title);
  virtual ~A2Rec3(); 
  
  int            resize();  

  virtual void   Show();
  
 public:
  // Interface functions
  // From 
  virtual double GetTFitParam(int tower, int ipar);                // shape w/o correction tower:0,1 ipar:0-3
  virtual void   SetTFitParam(int tower, int ipar, double val);
  virtual double GetTFitParamCorr(int tower, int ipar);            // shape w/ correction tower:0,1 ipar:0-3
  virtual void   SetTFitParamCorr(int tower, int ipar, double val);
  virtual double GetTFitParamLeakin(int tower, int ipar);          // Estimated shape of leakage-in tower:0,1 ipar:0-3
  virtual void   SetTFitParamLeakin(int tower, int ipar, double val);
  virtual double GetTScale(int tower);                             // Scale of Transition fit
  virtual double GetTScaleCorr(int tower);                         // Scale of Transition fit
  virtual double GetTScaleLeakin(int tower);                       // Scale of estimated shape of shower leakage-in
  virtual double GetTMax(int tower);                               // Get depth of Shower Maximum
  virtual double GetTMaxCorr(int tower);                           // Get depth of Shower Maximum 
  virtual double GetTMaxLeakin(int tower);                         // Get depth of Shower Maximum 
  
  // For PID 
  virtual double GetL20wocorr(int tower);                          // Get L20% which was calculated before shower leakin corr.
  virtual void   SetL20wocorr(int tower, double val);     
  virtual double GetL90wocorr(int tower);                          // Get L90% which was calculated before shower leakin corr.
  virtual void   SetL90wocorr(int tower, double val);          

  ClassDef(A2Rec3,1);    // Data for Reconstruction : Arm2 Format 3 (with transition fit results)
};


#endif 
