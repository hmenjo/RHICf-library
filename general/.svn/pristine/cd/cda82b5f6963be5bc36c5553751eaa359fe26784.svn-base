// *********************************************************************
// ***  A1PhysAccumHist                                              ***
// *** This class control the histogrames for the Arm#1 Phys Data    ***
// *** 20 Jul. 08: First Editted by H.MENJO                          ***
// *********************************************************************

#ifndef __A1PHYSACCUMHIST_H__
#define __A1PHYSACCUMHIST_H__

#include <TNamed.h>
#include <TH1F.h>
#include <TH2F.h>

#include "globaldef.h"
#include "A1Phys.h"

class A1PhysAccumHist : public TNamed {
 public:
  TH1F*   henergy[2];   //->
  TH2F*   h2pos[2];     //->
  TH2F*   h2flux[2];    //->
  TH1F*   hpid[2];      //->
  TH1F*   hhits[2];     //->
  
 public:
  A1PhysAccumHist();
  A1PhysAccumHist(char* name, char *title);
  ~A1PhysAccumHist();
  
  int  Initialize();
  int  DeleteHist();
  int  DeleteHists(){ return DeleteHist(); }
  int  Fill(A1Phys *d,int pid0=-10, int pid1=-10);
  int  Reset();
  int  CopyData(A1PhysAccumHist* );
  int  AddData(A1PhysAccumHist* ); 

  // for online analysis
  int  Init();
  int  Bor(){return OK;}
  int  Eor(){return OK;}
  int  Loop(A1Phys *d){return OK;}

 private: 
  static int icall;  

  // DEFINITIONS 
  static const int henergy_nbin   =  1000;
  static const int henergy_binmin =     0;
  static const int henergy_binmax = 10000;
  static const int hpos0_nbin   = 22;
  static const int hpos0_binmin = -1;
  static const int hpos0_binmax = 21;
  static const int hpos1_nbin   = 42;
  static const int hpos1_binmin = -1;
  static const int hpos1_binmax = 41;
 
  static const int hpid_nbin    =  3;
  static const int hpid_binmin  = -1;
  static const int hpid_binmax  =  2;
  static const int hhits_nbin   =  3;
  static const int hhits_binmin = -1;
  static const int hhits_binmax =  2;

  ClassDef(A1PhysAccumHist,1);   //  Histograms for A1Phys
};

#endif

