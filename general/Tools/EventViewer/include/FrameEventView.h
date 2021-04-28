#ifndef __FRAMEEVENTVIEW_H__
#define __FRAMEEVENTVIEW_H__

#include <iostream>
#include <iomanip>
using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TGWindow.h>
#include <TGClient.h>
#include <TGFrame.h>
#include <TGButton.h>
#include <RQ_OBJECT.h>
#include <TG3DLine.h>
#include <TGTab.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TRootEmbeddedCanvas.h>
#include <TStyle.h>
#include <TGTextEntry.h>
#include <TGMenu.h>
#include "TGTextButtonMod.h"

#include "LHCfEvent.h"
#include "A1RawToCal1.h"
#include "A1CalEventHist.h"
#include "A1PedeSubtract.h"
#include "A2RawToCal1.h"
#include "A2RawToCal1Silicon.h"
#include "A2CalEventHist.h"
#include "A2PedeSubtract.h"
#include "A1LHCCrossTalk.h"
#include "A1Cal1ToCal2.h"
#include "A2Cal1ToCal2.h"
#include "A1GainCalibration.h"
#include "A2GainCalibration.h"
#include "RawL1TDraw.h"
using namespace std;

class FrameEventView { 
  RQ_OBJECT("FrameEventView")

 public:
  const TGWindow  *window;
  UInt_t           wsize;
  UInt_t           hsize;

  TGMainFrame      *fMain;
  TGTab            *tab;
  TGCompositeFrame *ftab0;
  TGCompositeFrame *ftab1;
  TGCompositeFrame *ftab2;
  TGCompositeFrame *ftab3;
  TRootEmbeddedCanvas *fCanvas_0;
  TCanvas             *canvas_0;
  TRootEmbeddedCanvas *fCanvas_1;
  TCanvas             *canvas_1; 
  TRootEmbeddedCanvas *fCanvas_2;
  TCanvas             *canvas_2;
  TRootEmbeddedCanvas *fCanvas_3;
  TCanvas             *canvas_3; 
  TGTextButton        *fNext;
  TGTextButton        *fPrevious;
  TGTextButton        *fGo;
  TGTextButton        *fPrint;
  TGTextButton        *fTool;
  TGTextButton        *fExit;
  TGTextButtonMod     *fSearchArm1;
  TGTextButtonMod     *fSearchArm2; 
  TGTextButtonMod     *fSearchBeam;
  TGTextButtonMod     *fSearchPede;
  TGTextButtonMod     *fSearchLaser;  
  TGTextButtonMod     *fPede;
  TGTextButtonMod     *fGain;  
  TGTextEntry         *fText;       

  TGPopupMenu         *fMenuFilter;
  TGPopupMenu         *fMenuDatatype;  
  TGPopupMenu         *fMenuShow;

  TFile               *ifile;
  TTree               *tree;
  int                 ievent;
  int                 nevent;
  LHCfEvent           *ev;
  A1Cal1              *a1cal1;
  A1Cal2              *a1cal2;  
  A1RawToCal1         *a1conv;
  A1CalEventHist      *a1hist;
  A1PedeSubtract      *a1pedesub;
  A2Cal1              *a2cal1;
  A2Cal2              *a2cal2;
  A2RawToCal1         *a2conv; 
  A2RawToCal1Silicon  *a2convsi;
  A2CalEventHist      *a2hist;
  A2PedeSubtract      *a2pedesub;
  
  RawL1TDraw          *a1rawl1tdraw;
  RawL1TDraw          *a2rawl1tdraw; 
  // for gain calibration
  A1Cal1ToCal2        *a1cal1tocal2;
  A1GainCalibration   *a1gaincalibration;
  A1LHCCrossTalk      *a1crosstalk;
  A2Cal1ToCal2        *a2cal1tocal2;
  A2GainCalibration   *a2gaincalibration;
  
  bool                 docrosstalk;

 public:
  char   configdir[256];    // ./.eventview
  int    run1stev;

  Pixel_t         color_blue;
  Pixel_t         color_red;
  Pixel_t         color_gray;
  Pixel_t         color_green;
  Pixel_t         color_nodata;

 public:
  FrameEventView(){;}
  FrameEventView(const TGWindow *p, UInt_t w, UInt_t h);
  ~FrameEventView(){;}
  
  void  MakeFrame(); 
  int   Initialize();
  int   SetGainParamters();
  int   OpenFile(char *filename);
  int   ReadPedeFile(char *filename);
  int   SetConfigDir(char *dir);
  char* GetConfigDir(){return configdir;} 
  int   GetRun1stev(){return run1stev;}

  void  Exit();
  int   GetData(int i); 
  int   Show(int i);
  int   Go();
  int   Next();
  int   Previous(); 
  int   Update();
  int   Print();
  int   Tool();
  int   MenuOpenData(); 
  int   MenuOpenPedestal();
  int   SaveAs();
  int   ClearMenuFilter(int arm); 
  int   ClearMenuDatatype(int arm); 
  
  int   GainCalibOn();
  int   GainCalibOff();

  int   GetNEvent(){return nevent;}
  int   GetIEvent(){return ievent;}
  void  SetIEvent(int i){ievent = i;}

  int   HandleMenu(Int_t id);

  enum HandleMenuID {
    M_FILE_DATA,
    M_FILE_PEDESTAL,
    M_FILE_SAVE,
    M_FILE_SAVEAS,
    M_FILE_EXIT,

    M_DATATYPE_A1RAW,
    M_DATATYPE_A1CAL1,   
    M_DATATYPE_A1CAL2,
    M_DATATYPE_A1SIM,
    M_DATATYPE_A2RAW,
    M_DATATYPE_A2CAL1,   
    M_DATATYPE_A2CAL2,
    M_DATATYPE_A2SIM,
    M_DATATYPE_A2RAW_PPB2013,
    M_DATATYPE_A1RAW_PP2015,
    M_DATATYPE_A2RAW_PP2015,
    M_DATATYPE_A2RAW_PPB2016,
    M_DATATYPE_RHICFRAW_OP2017,

    M_FILTER_A1ALL,
    M_FILTER_A1L2TA,
    M_FILTER_A1STRG,
    M_FILTER_A1LTRG,
    M_FILTER_A1SLTRG, 
    M_FILTER_A1L2TA_MB,
    M_FILTER_A1L2TA_SP,
    M_FILTER_A2ALL,
    M_FILTER_A2L2TA,
    M_FILTER_A2STRG,
    M_FILTER_A2LTRG,
    M_FILTER_A2SLTRG, 
    M_FILTER_A2L2TA_MB,
    M_FILTER_A2L2TA_SP,
	 
	 M_FILTER_RHICF_ALL,
	 M_FILTER_RHICF_SHOWER,
	 M_FILTER_RHICF_SHOWER_TS,
	 M_FILTER_RHICF_SHOWER_TL,
	 M_FILTER_RHICF_SPE1,
	 M_FILTER_RHICF_SPE2,
	 M_FILTER_RHICF_STAR,
    
    M_FILE_SAVE_ARM1HIST,
    M_FILE_SAVE_ARM1VALUE,
    M_FILE_SAVE_ARM2HIST,
    M_FILE_SAVE_ARM2VALUE,

    M_TOOL_EDITER,
    M_TOOL_EVENTTAG,
    M_TOOL_MKPEDESTAL,
    M_TOOL_GAINFCONFIG,
    M_TOOL_ADAMOEVENTVIEW,

    M_SHOW_ALL, 
    M_SHOW_CLEAR,
    M_SHOW_LHCFEVENT,
    M_SHOW_A1CAL2, 
    M_SHOW_A1REC,
    M_SHOW_A1PHYS,
    M_SHOW_A1SIM,
    M_SHOW_A1SIMIN,
    M_SHOW_A2CAL2, 
    M_SHOW_A2REC,
    M_SHOW_A2PHYS,
    M_SHOW_A2SIM,
    M_SHOW_A2SIMIN,

    M_NON
  };
};

extern FrameEventView* gFrameEventView;

#endif
