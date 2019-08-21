// *********************************************************************
// ***  A1Cal1AccumHist                                              ***
// *** This class control the histogrames for the Arm#1 Cal2 Data    ***
// *** 20 Jul. 08: First Editted by H.MENJO                          ***
// ********************************************************************* 

#ifndef __A1CAL2ACCUMHIST_H__
#define __A1CAL2ACCUMHIST_H__

#include <TObject.h>
#include <TNamed.h>
#include <TH1F.h>

#include "globaldef.h"
#include "A1Cal2.h"

class A1Cal2AccumHist : public TNamed {
  
 public:
  TH1F *hist_cal[2][16];        //->  Tower:Layer
  TH1F *haccum_scifi[2][4][2];  //->  Accumulate Tower:Layer:XY
 
 private:
  static int icall;

 public:
  A1Cal2AccumHist();
  A1Cal2AccumHist(char* name, char *title);
  ~A1Cal2AccumHist();

  // 
  int  Initialize(); 
  int  DeleteHist();
  int  DeleteHists(){return DeleteHist();}
  int  Fill(A1Cal2 *d);
  int  Reset();
  int  CopyData(A1Cal2AccumHist* );
  
  // =====   FOR ONLINE ANALYSIS =====
  int  Init(){return OK;}
  int  Bor(){return OK;}
  int  Eor(){return OK;}
  int  Loop(A1Cal2 *d){return OK;}
  
 private:
  // DEFINITION FOR ONLINE ANALISYS
  // FOR 900GeV COLLISIONS
  static const int hist_nbin   =     51;
  static const int hist_binmin =   -100;
  static const int hist_binmax =   5000;

  // // FOR 14TeV COLLISIONS
  // static const int hist_nbin   =    101; 
  // static const int hist_binmin =   -700; 
  // static const int hist_binmax =  70000; 
 
  ClassDef(A1Cal2AccumHist,1);    // Histograms for A1Cal2
};


#endif
