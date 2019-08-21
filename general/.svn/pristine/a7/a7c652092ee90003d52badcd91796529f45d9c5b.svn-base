//-------------------------------------------------------------------------
// A1CrossTalk
//=========================================================================
// 27.Aug.2009   M.NAKAI 
// 31.Jan.2010   Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
// 26.Apr.2015   Y.Makino for op2015
//-------------------------------------------------------------------------

#ifndef _INC_A1CROSSTALK_
#define _INC_A1CROSSTALK_

#include <TObject.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TFile.h>
#include "A1Cal1.h"
#include "A1Cal2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class A1CrossTalk{
 public:
  A1CrossTalk();
  virtual  ~A1CrossTalk();
  int ReadFile(char *filename_x, char *filename_y);
  int ReadFile(char *filename); // op2015
  int CalibCrossTalk(double scifi20x[][20], double scifi20y[][20], double scifi40x[][40], double scifi40y[][40]);
  //argument : scifi20x[4:layer][20:pos] scifi40x[4:layer][20:pos]

  // op2015
  int CalibCrossTalk_wM(A1Cal1* data);
  int CalibCrossTalk_wM(A1Cal2* data);
  int CalibCrossTalk_wM(double scifi0[][2][20], double scifi1[][2][40]);
  int CalibCrossTalk_wOrgM(A1Cal1* data);
  int CalibCrossTalk_wOrgM(A1Cal2* data);
  int CalibCrossTalk_wOrgM(double scifi0[][2][20], double scifi1[][2][40]);

 private:

  double calib_cross_20x[4][20][60];
  double calib_cross_40x[4][40][60];
  double calib_cross_20y[4][20][60];
  double calib_cross_40y[4][40][60];
  double temp_40x[4][40];
  double temp_20x[4][20];
  double temp_40y[4][40];
  double temp_20y[4][20];

  string listname;
  double value;
  int layer,pos,cross_pos;

  ifstream fin_x;
  ifstream fin_y;

  TMatrixD *M[8];
  TMatrixD *bM[8];
  TVectorD *V;
  TVectorD *Vx;
  TVectorD *Vy;
  double a4Vx[4][60];
  double a4Vy[4][60];

  ClassDef(A1CrossTalk,1);   // Cross talk calibration for SciFi. GSO-bar!
};

#endif
