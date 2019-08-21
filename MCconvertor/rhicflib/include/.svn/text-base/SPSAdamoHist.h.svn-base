#ifndef __SPSADAMOHIST_H__
#define __SPSADAMOHIST_H__

#include <TObject.h>
#include <TNamed.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>

#include "SPSAdamo.h"

class SPSAdamoHist :  public TNamed {
 public:
  TH1F* hist[SPSAdamo::NLAYER][SPSAdamo::NXY];   //->  [Layer][XY]
  
  TCanvas *c;                                    //!
  
 private:
  char   cname[256];
  char   ctitle[256];
  static int icall;

 public:
  SPSAdamoHist();
  SPSAdamoHist(char* name, char *title);
  ~SPSAdamoHist();
  
  int  Initialize();
  int  DeleteHist();
  int  DeleteHists(){return DeleteHist();}
  int  DeleteCanvas();

  int  Reset();
  int  Fill(SPSAdamo* d,char *op="");   // op:"S" only the valid channels are filled     
  
  void SetCanvas(TCanvas* ctmp){c = ctmp;}  
  int  DrawCanvas();
  int  UpdateCanvas();
  void SetMaximum(double max,char op[]="X,Y");
  void SetMinimum(double min,char op[]="X,Y");
  
  ClassDef(SPSAdamoHist,1);  // Histograms for SPSAdamo
};

#endif
