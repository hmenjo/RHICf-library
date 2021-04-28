//-------------------------------------------------------------------------
// A1LHCCrossTalk                                
// This class is for crosstalk offset of SciFi detectors with A1Cal2.
// First, you must call "CTReadFile" to select following table files.
// 
// table/CROSSTALK_offset_X.dat : table for X direction.
// table/CROSSTALK_offset_Y.dat : table for Y direction.
// table/CROSSTALK_offset_X_invert.dat : invert table for X direction.
// table/CROSSTALK_offset_Y_invert.dat : invert table for Y direction.
//
// "invert" means invert matrix. When you use this tables, you can add the effect of crosstalk to SciFi data. (MC data etc.)
// After calling "CTReadFile", you can use "CalibLHCCrossTalk" to calibrate crosstalk effect.
//=========================================================================
// 27.Aug.2009   M.NAKAI 
// 26 Apr.2015   Y.Makino
//-------------------------------------------------------------------------

#ifndef INC_A1LHCCROSSTALK
#define INC_A1LHCCROSSTALK

#include <TObject.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "A1CrossTalk.h"
#include "A1Cal2.h"

class A1LHCCrossTalk : public A1CrossTalk
{
 public:
  A1LHCCrossTalk();
  virtual ~A1LHCCrossTalk();
  int CTReadFile(char *filename_x, char *filename_y);
  int CTReadFile(char *filename); // read the rootfile 
  int CalibLHCCrossTalk(A1Cal2 * a1cal2);
  int flag_op2015;

 private:
  double scifi20x[4][20];
  double scifi40x[4][40];
  double scifi20y[4][20];
  double scifi40y[4][40];

  ClassDef(A1LHCCrossTalk,1);   // Cross talk calibration for SciFi in A1Cal2 
};

#endif
