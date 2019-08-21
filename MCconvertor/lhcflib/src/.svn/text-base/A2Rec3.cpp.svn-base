#ifndef __A2REC3_CPP__
#define __A2REC3_CPP__

#include "A2Rec3.h"

//----------------------------------------------------------------------
//   Arm3 Reconstruction parameters with format 3
//   This is an extention of A2Rec2 for Transition Fitting
//   These results are filled to the vector "cal".
//   Each fit has four parameters (see TransitionFit class)
//   Three type results are recoreded
//     0: before the leakage-in correcton,
//     1: after the leakage-in correction,
//     2: estimated leakage-in
//     The relation should be as 0 = 1+2 if the fittings are perfect. 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Rec3);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#include "globaldef.h"

// -------------------------------------------------------------------
// -----                     DEFINITIONS                         -----
// -------------------------------------------------------------------

#define  REC_FORMAT     2003
#define  SIZE_CAL                   24             // size of vector::cal
#define   POS_CAL_TFITPARAM(a,b,c)  (0+a*8+b*4+c)  // a:type,b:tower,c:ipar
#define  SIZE_PID                   10             // 6 in A2Rec1 + 4
#define   POS_L20_OLD(i)             (6+i)         // i:tower
#define   POS_L90_OLD(i)             (8+i)         // i:tower



// -------------------------------------------------------------------
// -----             CONSTRUCTOR/DESTORACTOR                     -----
// -------------------------------------------------------------------

A2Rec3::A2Rec3() : A2Rec2() {
  A2Rec3::resize();
}

A2Rec3::A2Rec3(char* name, char *title) : A2Rec2(name,title){
  A2Rec3::resize();
}

A2Rec3::~A2Rec3(){;}

int  A2Rec3::resize(){
  format = REC_FORMAT;
  Rec0::resize(cal,  SIZE_CAL); 
  Rec0::resize(pid,  SIZE_PID);
  clear();
  return OK;
}

void A2Rec3::Show(){
  A2Rec2::Show();
  cout << " Transition Fit : " << endl;
  for(int tower=0;tower<2;tower++){
    cout << (tower==0?"   Small:All    ":"   Large:All    ") ;
    cout << setw(7) << setprecision(0) << GetTFitParam(tower,0) 
	 << setw(7) << setprecision(2) << GetTFitParam(tower,1)
	 << setw(7) << setprecision(2) << GetTFitParam(tower,2)
	 << setw(7) << setprecision(2) << GetTFitParam(tower,3)
	 << "   ( S_max= " << setw(5) << setprecision(1) << GetTMax(tower) <<" )" << endl;
    cout << (tower==0?"   Small:w/corr ":"   Large:w/corr ") ;
    cout << setw(7) << setprecision(0) << GetTFitParamCorr(tower,0) 
	 << setw(7) << setprecision(2) << GetTFitParamCorr(tower,1)
	 << setw(7) << setprecision(2) << GetTFitParamCorr(tower,2)
	 << setw(7) << setprecision(2) << GetTFitParamCorr(tower,3)
	 << "   ( S_max= " << setw(5) << setprecision(1) << GetTMaxCorr(tower) <<" )" << endl;
    cout << (tower==0?"   Small:leakin ":"   Large:leakin ") ;
    cout << setw(7) << setprecision(0) << GetTFitParamLeakin(tower,0) 
	 << setw(7) << setprecision(2) << GetTFitParamLeakin(tower,1)
	 << setw(7) << setprecision(2) << GetTFitParamLeakin(tower,2)
	 << setw(7) << setprecision(2) << GetTFitParamLeakin(tower,3)
	 << "   ( S_max= " << setw(5) << setprecision(1) << GetTMaxLeakin(tower) <<" )" << endl;
  }
  return ;
}

// -------------------------------------------------------------------
// -----                INTERFACE FUNCTIONS                      -----
// -------------------------------------------------------------------
double A2Rec3::GetTFitParam(int tower, int ipar){
  // Get result of transition fit before correction 
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift. 
  return cal[POS_CAL_TFITPARAM(0,tower,ipar)];
}

void   A2Rec3::SetTFitParam(int tower, int ipar, double val){
  // Set result of transition fit before correction
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift.   
  cal[POS_CAL_TFITPARAM(0,tower,ipar)] = val;
}

double A2Rec3::GetTFitParamCorr(int tower, int ipar){
  // Get result of transition fit after shower leakage-in correction 
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift.   
  return cal[POS_CAL_TFITPARAM(1,tower,ipar)];
}

void   A2Rec3::SetTFitParamCorr(int tower, int ipar, double val){
  // Set result of transition fit after shower leakage-in correction 
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift.   
  cal[POS_CAL_TFITPARAM(1,tower,ipar)] = val;  
}

double A2Rec3::GetTFitParamLeakin(int tower, int ipar){
  // Estimated transition shape of leakage-in
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift.   
  return cal[POS_CAL_TFITPARAM(2,tower,ipar)];
}

void   A2Rec3::SetTFitParamLeakin(int tower, int ipar, double val){
  // Set the estimated transition shape of leakage-in
  // tower : 0 (25mm), 1(32mm)
  // ipar  : 0-3, fitting parameters, 0: scale, 1,2: shape params, 3: shift.   
  cal[POS_CAL_TFITPARAM(2,tower,ipar)] = val;
}

double A2Rec3::GetTScale(int tower){
  // Scale of Transition shape 
  return GetTFitParam(tower,0);
}

double A2Rec3::GetTScaleCorr(int tower){ 
  // Scale of Transition shape 
  return GetTFitParamCorr(tower,0);
}

double A2Rec3::GetTScaleLeakin(int tower){
  // Scale of Transition shape 
  return GetTFitParamLeakin(tower,0);
}

double A2Rec3::GetTMax(int tower){
  // Get depth of Shower Maximum
  // (alpha-1)/beta + shift
  return (GetTFitParam(tower,1)-1.)/GetTFitParam(tower,2)+GetTFitParam(tower,3);
}

double A2Rec3::GetTMaxCorr(int tower){
  // Get depth of Shower Maximum
  // (alpha-1)/beta + shift
  return (GetTFitParamCorr(tower,1)-1.)/GetTFitParamCorr(tower,2)+GetTFitParamCorr(tower,3);
}

double A2Rec3::GetTMaxLeakin(int tower){
  // Get depth of Shower Maximum
  // (alpha-1)/beta + shift
  return (GetTFitParamLeakin(tower,1)-1.)/GetTFitParamLeakin(tower,2)+GetTFitParamLeakin(tower,3);
}

// 

// For PID -----------------------------
double A2Rec3::GetL20wocorr(int tower){
  // Get L20% which was calculated before shower leakin corr.
  return pid[POS_L20_OLD(tower)];
}
void   A2Rec3::SetL20wocorr(int tower, double val){
  pid[POS_L20_OLD(tower)] = val;
}
double A2Rec3::GetL90wocorr(int tower){
  // Get L90% which was calculated before shower leakin corr.
  return pid[POS_L90_OLD(tower)];
}
void   A2Rec3::SetL90wocorr(int tower, double val){
  pid[POS_L90_OLD(tower)] = val;
}

#endif
