#ifndef __A2CAL2ACCUMHIST_H__
#define __A2CAL2ACCUMHIST_H__

// --------------------------------------------------------------------
//                           A2Cal2AccumHist
//         For detail, see A2Cal1AccumHist.cpp or Online Manual
// --------------------------------------------------------------------

#include <TObject.h>
#include <TNamed.h>
#include <TH1F.h>

#include "globaldef.h"
#include "A2Cal2.h"

class A2Cal2AccumHist : public TNamed {
  
 public:
  TH1F *hist_cal[2][16];   //->   Tower:Layer

 private:
  static int icall;

 public:
  A2Cal2AccumHist();
  A2Cal2AccumHist(char* name, char *title);
  ~A2Cal2AccumHist();

  int  Initialize();
  int  DeleteHist();
  int  DeleteHists(){return DeleteHist();}
  int  Fill(A2Cal2 *d);
  int  Reset();
  int  CopyData(A2Cal2AccumHist* );

  // =====   FOR ONLINE ANALYSIS =====
  int  Init(){return OK;}
  int  Bor(){return OK;}
  int  Eor(){return OK;}
  int  Loop(A2Cal2 *d){return OK;}


 private:
  // DEFINITION FOR ONLINE ANALISYS 
  // FOR 900GeV COLLISIONS
  static const int hist_nbin   =    51;
  static const int hist_binmin =  -100;
  static const int hist_binmax =  5000;
  
  // // FOR 14TeV COLLISIONS
  // static const int hist_nbin   =    101; 
  // static const int hist_binmin =   -700; 
  // static const int hist_binmax =  70000; 
  
  
  ClassDef(A2Cal2AccumHist,1);  //  Histograms for A2Cal2
};


#endif
