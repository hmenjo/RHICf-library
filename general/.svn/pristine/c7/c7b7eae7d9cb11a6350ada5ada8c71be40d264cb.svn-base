#include "../include/A1LHCCrossTalk.h"

//-------------------------------------------------------------------------
// A1LHCCrossTalk                                
// This class is for crosstalk offset of SciFi detectors.
// "A1CrossTalk" is its parent class.
// 
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
// 31.Jan.2010   Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//-------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1LHCCrossTalk);
#endif

using namespace std;

A1LHCCrossTalk::A1LHCCrossTalk(){
  return;
}

A1LHCCrossTalk::~A1LHCCrossTalk(){  
  return;
}

int A1LHCCrossTalk::CTReadFile(char *filename_x, char *filename_y){
  // Reading tabls files selected in arguments for crosstalk offset.
  ReadFile(filename_x,filename_y);
  flag_op2015=false; // 2015 Makino
  return 0;
}

int A1LHCCrossTalk::CTReadFile(char *filename){
  // Reading crosstalk rootfile
  ReadFile(filename);
  flag_op2015=true;
  return 0;
}

int A1LHCCrossTalk::CalibLHCCrossTalk(A1Cal2 * a1cal2){

  // By Y.Makino for op2015
  if(flag_op2015==true){
    CalibCrossTalk_wM(a1cal2);
    return 0;
  }

  // Calibrate crosstalk effects in the A1Cal2 class.
  for(int layer=0;layer<4;layer++){
    for(int pos=0;pos<20;pos++){
      scifi20x[layer][pos]=a1cal2->scifi0[layer][0][pos];
      scifi20y[layer][pos]=a1cal2->scifi0[layer][1][pos];
    }
    for(int pos=0;pos<40;pos++){
      scifi40x[layer][pos]=a1cal2->scifi1[layer][0][pos];
      scifi40y[layer][pos]=a1cal2->scifi1[layer][1][pos];
    }
  }

  CalibCrossTalk(scifi20x,scifi20y,scifi40x,scifi40y);

  for(int layer=0;layer<4;layer++){
    for(int pos=0;pos<20;pos++){
      a1cal2->scifi0[layer][0][pos]=scifi20x[layer][pos];
      a1cal2->scifi0[layer][1][pos]=scifi20y[layer][pos];
    }
    for(int pos=0;pos<40;pos++){
      a1cal2->scifi1[layer][0][pos]=scifi40x[layer][pos];
      a1cal2->scifi1[layer][1][pos]=scifi40y[layer][pos];
    }
  }

  return 0;
}
