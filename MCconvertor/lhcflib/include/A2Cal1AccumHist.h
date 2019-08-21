#ifndef __A2CAL1ACCUMHIST_H__
#define __A2CAL1ACCUMHIST_H__

// --------------------------------------------------------------------
//                           A2Cal1AccumHist
//         For detail, see A2Cal1AccumHist.cpp or Online Manual
// --------------------------------------------------------------------

#include <TObject.h>
#include <TNamed.h>
#include <TH1F.h>
#include <TCanvas.h>

#include "globaldef.h"
#include "feparam_arm2.h"
#include "A2Cal1.h"

class A2Cal1AccumHist : public TNamed {
  
 public:
  
  TH1F *hist_cal[2][16][2];      //-> Histograms for Scin. [Tower:Layer:Range]
  TH1F *hist_noise[8];           //-> Histograms for Noise. [Channel]
  TH1F *hist_fc[2][4];           //-> Histograms for F.C.'s [Arm(arm1-0,arm2-1):Channel]
  TH1F *hist_laser[2];           //-> Histograms for Laser Monitor PMT. [Channel]
  TH1F *haccum_silicon[4][2][3]; //-> Histograms for Accumulate [Layer:XY:Sample] 
  TH1F *hist_silicon[4][2][3];   //-> Histograms for a typical silicon strip in each layer. 
  TH1F *hist_flag[3];            //-> Accumulate of Flag values 

  // Added at 11 Jan. 2010
  TH1F *hist_tdc[7];             //-> Histograms for TDC
  TH1F *hist_scl[3];             //-> Histograms for Scaler

  int hist_nbin;                 // number of bins of histgrams for ADC values. [210]
  int hist_binmin;               // minimum value of histogram bin for ADC values [-104]
  int hist_binmax;               // maximum value of histogram bin for ADC values [4096]
  int hsilicon_nbin;             // number of bins of histograms for typical silicon channel [500]
  int hsilicon_binmin;           // minimum value of histogram bin for typical silicon channel [-4500]
  int hsilicon_binmax;           // minimum value of histogram bin for typical silicon channel [-4500]
  int hsilicon_channel;          // channel filled value to histogram [10]


  TCanvas*       c_cal0;         //! Canvas for the scintillators in 25mm cal. 
  TCanvas*       c_cal1;         //! Canvas for the scintillators in 32mm cal. 
  TCanvas*       c_adcs;         //! Canvsa for the other ADCs. Noise,Laser,FCs
  TCanvas*       c_flag;         //! Canvas for the flags.
  TCanvas*       c_tdc;          //! Canvas for TDC.
  TCanvas*       c_si;           //! Canvas for Accum Silicon
  
 private:
  static int icall;

 public:
  A2Cal1AccumHist();
  A2Cal1AccumHist(char* name, char *title);
  ~A2Cal1AccumHist();
  
  //   
  int  InitializeMembers();
  int  Initialize(){return InitializeHists();}
  int  InitializeHists(); 
  int  InitializeCanvases();
  int  InitializeCanvasCal0();
  int  InitializeCanvasCal1();
  int  InitializeCanvasADCs();
  int  InitializeCanvasFlag(); 
  int  InitializeCanvasTDC();
  int  InitializeCanvasSilicon();
  int  DeleteHists();
  int  DeleteHist(){return DeleteHists();}  
  int  DeleteCanvases();
  int  Fill(A2Cal1 *d,
	    bool beam=true,      // if true, the beam event is filled. 
	    bool pede=true,      // if true, the pede event is filled. 
	    bool laser=true);    // if true, the laser event is filled. 
  int  Reset();
  int  CopyData(A2Cal1AccumHist* );


  void SetCanvasCal0(TCanvas* c){c_cal0 = c;}
  void SetCanvasCal1(TCanvas* c){c_cal1 = c;}
  void SetCanvasADCs(TCanvas* c){c_adcs = c;}
  void SetCanvasFlag(TCanvas* c){c_flag = c;} 
  void SetCanvasTDC(TCanvas* c){c_tdc = c;}
  void SetCanvasSilicon(TCanvas* c){c_si = c;}
  TCanvas* GetCanvasCal0(){return c_cal0;}
  TCanvas* GetCanvasCal1(){return c_cal1;}
  TCanvas* GetCanvasADCs(){return c_adcs;}
  TCanvas* GetCanvasFlag(){return c_flag;} 
  TCanvas* GetCanvasTDC(){return c_tdc;}
  TCanvas* GetCanvasSilicon(){return c_si;}  
  int  SetHistNbin(int nbin);
  int  SetHistBinMinimum(int binmin);
  int  SetHistBinMaximum(int binmax); 
  int  SetHSiliconNbin(int nbin);
  int  SetHSiliconBinMinimum(int binmin);
  int  SetHSiliconBinMaximum(int binmax);
  int  SetHSiliconChannel(int ch);
  int  GetHistNbin(){return hist_nbin;}
  int  GetHistBinMinimum(){return hist_binmin;}
  int  GetHistBinMaximum(){return hist_binmax;}
  int  GetHSiliconNbin(){return hsilicon_nbin;}
  int  GetHSiliconBinMinimum(){return hsilicon_binmin;}
  int  GetHSiliconBinMaximum(){return hsilicon_channel;} 
  int  GetHSiliconChannel(){return hsilicon_channel;}
  int  SetTDCHistogram(int ich,int nbin,double binmin,double binmax);
  int  SetTDCHistogram(int ich,TH1F* h);
  void SetLineColor(Color_t c);
  void SetFillColor(Color_t c);
  void SetFillStyle(int c);
  void Scale(double s);
  int  Draw(int adcrange=0, const char* option = "");
  int  DrawCal0(int adcrange=0, const char* option = "");
  int  DrawCal1(int adcrange=0, const char* option = "");
  int  DrawADCs(const char* option = "");
  int  DrawFlag(const char* option = "");
  int  DrawTDC(const char* option = ""); 
  int  DrawSilicon(const char* option = "");
  int  OptimizeYRange(TPad* pad);
  int  SetLogy(TCanvas* c, int op=1);
  int  SetLogy(int op=1);
  int  SetLogyCal0(int op=1){return SetLogy(c_cal0,op);} 
  int  SetLogyCal1(int op=1){return SetLogy(c_cal1,op);} 
  int  SetLogyADCs(int op=1){return SetLogy(c_adcs,op);}
  int  SetLogyFlag(int op=1){return SetLogy(c_flag,op);}
  int  SetLogyTDC(int op=1){ return SetLogy(c_tdc,op);}
  int  SetLogySilicon(int op=1){return SetLogy(c_si,op);} 

  // For online analysis 
  int  Init();
  int  Bor();
  int  Eor();
  int  Loop(A2Cal1 *d);

  // Definitions of default values
 private:
  static const int DEFAULT_hist_nbin       =  210;
  static const int DEFAULT_hist_binmin     = -104;
  static const int DEFAULT_hist_binmax     = 4096;
  static const int DEFAULT_hsilicon_nbin   =  110;
  static const int DEFAULT_hsilicon_binmin = -200;
  static const int DEFAULT_hsilicon_binmax = 2000;
  static const int DEFAULT_hsilicon_channel=   10;

  ClassDef(A2Cal1AccumHist,2);   // Histograms for A2Cal1
  
};

#endif