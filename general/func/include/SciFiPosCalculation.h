#ifndef __SCIFIPOSCALCULATION_H__
#define __SCIFIPOSCALCULATION_H__

//-----------------------------------------------------------------
//                       SciFiPosCalculation    
// mod ver. for op2015 by Y.Makino
//-----------------------------------------------------------------

#include <TObject.h>

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "globaldef.h"
#include "A1Cal2.h"
#include "A1Phys.h"

using namespace std;

class SciFiPosCalculation{
public:
  double hosei0[4][2][20]; // alignment
  double hosei1[4][2][40];
  double hosei_1MIP0[4][2][20]; // gain 
  double hosei_1MIP1[4][2][40];
  double scifikai0[4][2][20]; // 
  double scifikai1[4][2][40];
  double sumscifi0[4][2]; //
  double sumscifi1[4][2];
  double max0[4][2]; // 
  double max1[4][2]; 
  int saidai0[4][2]; //
  int saidai1[4][2];
  double goukei0[4][2]; //
  double goukei1[4][2];
  double goukei0_1[4][2]; //
  double goukei1_1[4][2];
  double zyuusinn0[4][2]; //
  double zyuusinn1[4][2];
  
public:
  SciFiPosCalculation(){;}
  virtual ~SciFiPosCalculation(){;}
  
  // for online analysis
  int Init();
  int CalPosition(A1Cal2 *a1cal2, A1Phys *a1phys);
  //int ReadGSObarGainTable();
  int ReadGSObarPosTable();
  int Initialize_op2015();

  //offline
  int Initialize();
  void scifi_gaincalibration(A1Cal2 *a1cal2);
  void scifipos_read(A1Cal2 *a1cal2);
  void scifipos_fill(A1Phys *a1phys);

  ClassDef(SciFiPosCalculation,1);   // Hit position search by SciFi (ver. Mizuishi)
};

#endif
