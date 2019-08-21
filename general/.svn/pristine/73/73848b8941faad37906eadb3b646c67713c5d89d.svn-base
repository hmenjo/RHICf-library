#ifndef __A2CALEVENTHIST_H__
#define __A2CALEVENTHIST_H__

#include <TObject.h>
#include <TNamed.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TGraph.h>
#include <TText.h>
#include "globaldef.h"
#include "A2Cal1.h"
#include "A2Cal2.h"

class A2CalEventHist :  public TNamed {
 public:
  
  TH1F*   hist_cal[2][2];      //-> tower:range
  TH1F*   hist_cald[2][2];     //-> tower:range
  TH1F*   hist_fc[2];          //-> arm
  TH1F*   hist_laser;          //->
  TH1F*   hist_noise;          //-> 
  
  TH1F*   hist_silicon[4][2][3]; //-> layer:xy:timing
  
  TGraph* g_tdc;               //->
  
  TText*  t_info[7];           //->

  TText*  t_tdc[12][16];       //->
  TText*  t_scl[16];           //->
  TText*  t_flag[3][32];       //->
  TText*  t_flagd[3];          //->
  TText*  t_cnt[35];           //->
  TText*  t_fifo[8];           //->

  TCanvas*  c1;                 //!
  TPad*     c1pad1_1;           //! 
  TPad*     c1pad1_2;           //!
  TPad*     c1pad1_3;           //! 
  TPad*     c1pad1_4;           //! 
  TPad*     c1pad2_1;           //! 
  TPad*     c1pad2_2;           //!
  TPad*     c1pad3_1;           //! 
  TPad*     c1pad3_2;           //!
  TPad*     c1pad4_1;           //! 
  TPad*     c1pad4_2;           //!
  
  TCanvas*  c2;                 //!
  TPad*     c2pad1;             //! 
  TPad*     c2pad2;             //!
  TPad*     c2pad3;             //! 
  TPad*     c2pad4;             //! 
  
  TCanvas*  c3;                 //!

  TText *l_cnt[35];             //!  Labels for counters
  TText *l_tdc[12];             //!  Labels for TDC
  TText *l_scl[16];             //!  Labels for Scalers
  TText *lf_0;                  //!
  TText *lf_1;                  //!
  TText *lf_2;                  //!

  enum GPIOLOGIC {
    GPIOLOGIC_OLD      = 1,
    GPIOLOGIC_V28      = 2,
    GPIOLOGIC_OP2015   = 3,
    GPIOLOGIC_UNKNOWN  = 0
  };

  // For Scaler, TDC, 
  enum DISPLAY_VERSION {
    VERSION_PP2010     = 2010,
    VERSION_PPB2013    = 2013,
    VERSION_PP2015     = 2015, 
    VERSION_PPB2016    = 2016, 
    VERSION_UNKNOW     = 0
  };
  
  GPIOLOGIC          gpioversion;        //!
  DISPLAY_VERSION    f_DisplayVersion;   //!

 private:
  char   cname[256];
  char   ctitle[256];
  static int icall;
  
 public:
  A2CalEventHist();
  A2CalEventHist(char* name, char *title) : TNamed(name,title){;}
  ~A2CalEventHist();
  
  int  Initialize(); 
  int  DeleteHist(); 
  int  DeleteHists(){ return DeleteHist();}
  int  Reset();
  int  Fill(A2Cal1* d); 
  int  Fill(A2Cal2* d);

  void SetCanvas1(TCanvas* c){c1 = c;}
  int  DrawCanvas1(char *option="lowhighdelaysiliconallsilicont0");
  int  UpdateCanvas1(); 
  int  ClearCanvas1();          // Clear Pads
  int  SetHistConfig(int op=0); // op=0 for A1Cal1, op=1 for A1Cal2

  void SetCanvas2(TCanvas* c){c2 = c;}
  int  DrawCanvas2(char *option="");
  int  UpdateCanvas2();

  void SetCanvas3(TCanvas* c){c3 = c;}
  int  DrawCanvas3(char *option="");
  int  UpdateCanvas3();
  int  SetCanvas3YRange(double min,double max);
  
  int  SetHistColor(int op=0);
  int  OptimizeYRange(); 
  int  OptimizeYRange(TPad* pad);
  int  ChangeHistTitleOnPad(TPad* pad, char* title);
  TH1* GetTH1OnPad(TPad* pad);

  GPIOLOGIC SelGPIOLogicFormat(A2Cal1* d);
  int  SetDisplayFormat(DISPLAY_VERSION version); // 
  void SetDisplayVersion_pp2010();                // Display format for 2010
  void SetDisplayVersion_pPb2013();               // Display format for 2013
  void SetDisplayVersion_pp2015();                // Display format for 2015 
  void SetDisplayVersion_pPb2016();               // Display format for 2016
  
  ClassDef(A2CalEventHist,1);
  
};

#endif
