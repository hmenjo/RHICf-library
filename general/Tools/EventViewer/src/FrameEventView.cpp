#ifndef __FRAMEEVENTVIEW_CPP__
#define __FRAMEEVENTVIEW_CPP__

#include "FrameEventView.h"
#include <TApplication.h>
#include <TGClient.h>
#include <TVirtualX.h>
#include <TGFileDialog.h>
#include <cctype>
#include "EventTagFrame.h"
#include "MkPedestalFrame.h"
#include "LHCfParamFiles.h"
#include "GainConfigWindow.h"
#include "AdamoFrame.h"
#include <Rec0.h>
#include <A2Phys.h>
#include <SimIncidents.h>

using namespace std;

FrameEventView* gFrameEventView;

FrameEventView::FrameEventView(const TGWindow *p, UInt_t w, UInt_t h){
  window = p;
  wsize = w;
  hsize = h;
  
  ifile = NULL;
  ievent = 0;
  nevent = 0;

  gClient->GetColorByName("#0000ff",color_blue);
  gClient->GetColorByName("#ff0000",color_red);
  gClient->GetColorByName("#00cc00",color_green);
  gClient->GetColorByName("#cecece",color_nodata);
  
  strcpy(configdir,"./.eventview");
  run1stev = 0;

  docrosstalk = false;
  //docrosstalk = true;

  gFrameEventView = this;
}

void FrameEventView::MakeFrame(){
  ULong_t lhints;
  
  fMain = new TGMainFrame(window,wsize,hsize,kFixedWidth);
  fMain->Connect("CloseWindow()","FrameEventView",this,"Exit()");
  fMain->SetWindowName("LHCf Event Viewer v2.0");
  fMain->SetCleanup(kDeepCleanup);
  
  // MENU -------------------------------------------------------
  TGLayoutHints* fMenuBarLayout
    = new TGLayoutHints(kLHintsTop | kLHintsExpandX);
  TGLayoutHints* fMenuBarItemLayout
    = new TGLayoutHints(kLHintsTop | kLHintsLeft, 4, 4, 2, 0);
  
  TGPopupMenu* fMenuFileSave = new TGPopupMenu(gClient->GetRoot());
  fMenuFileSave->AddEntry("./arm1hist.gif" , M_FILE_SAVE_ARM1HIST);
  fMenuFileSave->AddEntry("./arm1value.gif", M_FILE_SAVE_ARM1VALUE);
  fMenuFileSave->AddEntry("./arm2hist.gif" , M_FILE_SAVE_ARM2HIST);
  fMenuFileSave->AddEntry("./arm2value.gif", M_FILE_SAVE_ARM2VALUE); 

  TGPopupMenu* fMenuFile = new TGPopupMenu(gClient->GetRoot());
  fMenuFile->AddEntry("&Open Data File",     M_FILE_DATA);
  fMenuFile->AddEntry("Open &Pedestal File", M_FILE_PEDESTAL);
  fMenuFile->AddSeparator();  
  fMenuFile->AddPopup("&Save",    fMenuFileSave);
  fMenuFile->AddEntry("Save &as", M_FILE_SAVEAS);
  fMenuFile->AddSeparator();
  fMenuFile->AddEntry("&Exit",   M_FILE_EXIT);

  fMenuFilter = new TGPopupMenu(gClient->GetRoot());
  fMenuFilter->AddEntry("Arm1 All ",         M_FILTER_A1ALL);
  fMenuFilter->AddEntry("Arm1 L2TA",         M_FILTER_A1L2TA);
  fMenuFilter->AddEntry("Arm1 20mm Shower",  M_FILTER_A1STRG);
  fMenuFilter->AddEntry("Arm1 40mm Shower",  M_FILTER_A1LTRG);
  fMenuFilter->AddEntry("Arm1 20mm and 40mm",M_FILTER_A1SLTRG); 
  fMenuFilter->AddEntry("Arm1 L2TA_MB(Minimum Bias)", M_FILTER_A1L2TA_MB);
  fMenuFilter->AddEntry("Arm1 L2TA_SP(Pi0)", M_FILTER_A1L2TA_SP);
  
  fMenuFilter->AddSeparator();
  fMenuFilter->AddEntry("Arm2 All ",         M_FILTER_A2ALL);
  fMenuFilter->AddEntry("Arm2 L2TA",         M_FILTER_A2L2TA);
  fMenuFilter->AddEntry("Arm2 25mm Shower",  M_FILTER_A2STRG);
  fMenuFilter->AddEntry("Arm2 32mm Shower",  M_FILTER_A2LTRG);
  fMenuFilter->AddEntry("Arm2 25mm and 32mm",M_FILTER_A2SLTRG);  
  fMenuFilter->AddEntry("Arm2 L2TA_MB(Minimum Bias)", M_FILTER_A2L2TA_MB);
  fMenuFilter->AddEntry("Arm2 L2TA_SP(Pi0)", M_FILTER_A2L2TA_SP);
  fMenuFilter->AddSeparator();
#if FORMAT == 2017
  fMenuFilter->AddEntry("RHICf All",         M_FILTER_RHICF_ALL);
  fMenuFilter->AddEntry("RHICf Shower",      M_FILTER_RHICF_SHOWER);
  fMenuFilter->AddEntry("RHICf Shower(TS)",  M_FILTER_RHICF_SHOWER_TS);
  fMenuFilter->AddEntry("RHICf Shower(TL)",  M_FILTER_RHICF_SHOWER_TL);
  fMenuFilter->AddEntry("RHICf Special1",    M_FILTER_RHICF_SPE1);
  fMenuFilter->AddEntry("RHICf Special2",    M_FILTER_RHICF_SPE2);
  fMenuFilter->AddEntry("RHICf+STAR",        M_FILTER_RHICF_STAR);
#endif 

  ClearMenuFilter(1);
#if   FORMAT == 2015
  fMenuFilter->CheckEntry( M_FILTER_A1ALL);
#elif FORMAT == 2017  
  fMenuFilter->CheckEntry( M_FILTER_RHICF_ALL);
#else
  fMenuFilter->CheckEntry( M_FILTER_A1ALL);
#endif
  
  ClearMenuFilter(2);
  fMenuFilter->CheckEntry( M_FILTER_A2ALL);

  fMenuDatatype = new TGPopupMenu(gClient->GetRoot());
  fMenuDatatype->AddEntry("a1raw", M_DATATYPE_A1RAW);
  fMenuDatatype->AddEntry("a1raw_pp2015",  M_DATATYPE_A1RAW_PP2015); 
  fMenuDatatype->AddEntry("a1cal1",M_DATATYPE_A1CAL1);
  fMenuDatatype->AddEntry("a1cal2",M_DATATYPE_A1CAL2);
  fMenuDatatype->AddEntry("a1sim", M_DATATYPE_A1SIM);
  fMenuDatatype->AddSeparator();
  fMenuDatatype->AddEntry("a2raw", M_DATATYPE_A2RAW); 
  fMenuDatatype->AddEntry("a2raw_pPb2013", M_DATATYPE_A2RAW_PPB2013); 
  fMenuDatatype->AddEntry("a2raw_pp2015",  M_DATATYPE_A2RAW_PP2015); 
  fMenuDatatype->AddEntry("a2raw_pPb2016", M_DATATYPE_A2RAW_PPB2016);
  fMenuDatatype->AddEntry("a2cal1",M_DATATYPE_A2CAL1);
  fMenuDatatype->AddEntry("a2cal2",M_DATATYPE_A2CAL2);
  fMenuDatatype->AddEntry("a2sim", M_DATATYPE_A2SIM); 
  fMenuDatatype->AddSeparator();
  fMenuDatatype->AddEntry("rhicfraw_Op2017", M_DATATYPE_RHICFRAW_OP2017); 
  
  cout << "FORMAT " << FORMAT << endl;
#if FORMAT == 2010
  fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW);
#elif FORMAT == 2013
  fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PPB2013);
#elif FORMAT == 2015
  fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW_PP2015);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PP2015);
#elif FORMAT == 2016
  fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW_PP2015);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PPB2016);
#elif FORMAT == 2017 
  fMenuDatatype->CheckEntry(M_DATATYPE_RHICFRAW_OP2017);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PP2015);
#else
  fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW_PP2015);
  fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PP2015); 
#endif

  TGPopupMenu* fMenuTool = new TGPopupMenu(gClient->GetRoot());
  fMenuTool->AddEntry("&Editer",              M_TOOL_EDITER);
  fMenuTool->AddEntry("Event &Tag",           M_TOOL_EVENTTAG);
  fMenuTool->AddEntry("Calculate &Pedestal",  M_TOOL_MKPEDESTAL);
  fMenuTool->AddEntry("Configure of Gain Calibration",M_TOOL_GAINFCONFIG);
  fMenuTool->AddEntry("ADAMO Event Viewer",   M_TOOL_ADAMOEVENTVIEW);

  fMenuShow = new TGPopupMenu(gClient->GetRoot());
  fMenuShow->AddEntry("&ALL"   ,  M_SHOW_ALL);
  fMenuShow->AddEntry("&CLEARE",  M_SHOW_CLEAR);   
  fMenuShow->AddSeparator(); 
  fMenuShow->AddEntry("Event",  M_SHOW_LHCFEVENT);
  fMenuShow->AddEntry("a1cal2",  M_SHOW_A1CAL2);
  fMenuShow->AddEntry("a1rec",   M_SHOW_A1REC);
  fMenuShow->AddEntry("a1phys",  M_SHOW_A1PHYS);
  fMenuShow->AddEntry("a1sim",   M_SHOW_A1SIM);
  fMenuShow->AddEntry("a1simin", M_SHOW_A1SIMIN);
  fMenuShow->AddEntry("a2cal2",  M_SHOW_A2CAL2);
  fMenuShow->AddEntry("a2rec",   M_SHOW_A2REC);
  fMenuShow->AddEntry("a2phys",  M_SHOW_A2PHYS);
  fMenuShow->AddEntry("a2sim",   M_SHOW_A2SIM);
  fMenuShow->AddEntry("a2simin", M_SHOW_A2SIMIN);
  // Clear all Show flag
  HandleMenu(M_SHOW_CLEAR);

  TGMenuBar* fMenuBar = new TGMenuBar(fMain, 1, 1, kHorizontalFrame);
  // fMenuBar->SetBackgroundColor(color_black);
  fMenuBar->AddPopup("&File",      fMenuFile,    fMenuBarItemLayout);
  fMenuBar->AddPopup("&Filter",    fMenuFilter,  fMenuBarItemLayout); 
  fMenuBar->AddPopup("&Data Type", fMenuDatatype,fMenuBarItemLayout); 
  fMenuBar->AddPopup("&Tool",      fMenuTool,    fMenuBarItemLayout);
  fMenuBar->AddPopup("&Print Info",fMenuShow,    fMenuBarItemLayout);
  fMain->AddFrame(fMenuBar, fMenuBarLayout);

  fMenuFileSave->Connect("Activated(Int_t)", "FrameEventView", this,
		     "HandleMenu(Int_t)");
  fMenuFile->Connect("Activated(Int_t)", "FrameEventView", this,
		     "HandleMenu(Int_t)");
  fMenuFilter->Connect("Activated(Int_t)", "FrameEventView", this,
		     "HandleMenu(Int_t)");
  fMenuDatatype->Connect("Activated(Int_t)", "FrameEventView", this,
			 "HandleMenu(Int_t)");
  fMenuTool->Connect("Activated(Int_t)", "FrameEventView", this,
		     "HandleMenu(Int_t)");
  fMenuShow->Connect("Activated(Int_t)", "FrameEventView", this,
		     "HandleMenu(Int_t)");

  // CANVAS TAG -------------------------------------------------
  tab = new TGTab(fMain,wsize,hsize-50);
  ftab0 = tab->AddTab("  ARM1 HIST  ");
  ftab0->SetLayoutManager(new TGVerticalLayout(ftab0));
  ftab1 = tab->AddTab("  ARM1 VALUE  ");
  ftab1->SetLayoutManager(new TGVerticalLayout(ftab1));
  ftab2 = tab->AddTab("  ARM2 HIST  ");
  ftab2->SetLayoutManager(new TGVerticalLayout(ftab2));
  ftab3 = tab->AddTab("  ARM2 VALUE  ");
  ftab3->SetLayoutManager(new TGVerticalLayout(ftab3));
  
  fCanvas_0 = new TRootEmbeddedCanvas("fCanvas_0",ftab0,400,650);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY;;
  ftab0->AddFrame(fCanvas_0,new TGLayoutHints(lhints,0,0,0,0));
  canvas_0 = fCanvas_0->GetCanvas();
  canvas_0->SetTitle("ARM1 HIST");
  
  fCanvas_1 = new TRootEmbeddedCanvas("fCanvas_1",ftab1,400,650);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY;;
  ftab1->AddFrame(fCanvas_1,new TGLayoutHints(lhints,0,0,0,0));
  canvas_1 = fCanvas_1->GetCanvas();
  canvas_1->SetTitle("ARM1 VALUE");
  
  fCanvas_2 = new TRootEmbeddedCanvas("fCanvas_2",ftab2,400,650);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY;;
  ftab2->AddFrame(fCanvas_2,new TGLayoutHints(lhints,0,0,0,0));
  canvas_2 = fCanvas_2->GetCanvas();
  canvas_2->SetTitle("ARM2 HIST");

  fCanvas_3 = new TRootEmbeddedCanvas("fCanvas_3",ftab3,400,650);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY;;
  ftab3->AddFrame(fCanvas_3,new TGLayoutHints(lhints,0,0,0,0));
  canvas_3 = fCanvas_3->GetCanvas();
  canvas_3->SetTitle("ARM2 VALUE");

#if FORMAT == 2010 || FORMAT == 2015 || FORMAT == 2017
  tab->SetTab(0);
#elif FORMAT == 2013 || FORMAT == 2016
  tab->SetTab(2);
#else 
  tab->SetTab(0);
#endif

  tab->Resize(tab->GetDefaultSize());
  
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY;
  fMain->AddFrame(tab, new TGLayoutHints(lhints,1,1,1,1));
  
  TGCompositeFrame *cBottom
    = new TGCompositeFrame(fMain, 170, 20, kHorizontalFrame);
  
  fExit = new TGTextButton(cBottom,"    Exit    ");
  lhints = kLHintsRight | kLHintsBottom ;
  cBottom->AddFrame(fExit,new TGLayoutHints(lhints ,10,1,1,1));
  fExit->Connect("Pressed()","FrameEventView",this,"Exit()");

  fPrevious = new TGTextButton(cBottom," <<  Previous  ");
  lhints = kLHintsLeft | kLHintsBottom |  kLHintsExpandX ;
  cBottom->AddFrame(fPrevious,new TGLayoutHints(lhints ,2,2,1,1));
  fPrevious->Connect("Pressed()","FrameEventView",this,"Previous()");
  
  fSearchArm1  = new TGTextButtonMod(cBottom,"Arm1"); 
  //fSearchArm1->SetBackgroundColor(color_blue);  
  fSearchArm1->SetTextColor(color_blue);
  //fSearchArm1->SetFont("-*-new century schoolbook-medium-r-*-*-14-*-*-*-*-*-*-*");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fSearchArm1,new TGLayoutHints(lhints ,2,2,1,1));
  fSearchArm1->ChangeOn();
  
  fPede  = new TGTextButtonMod(cBottom,"  Pedestal Sub.  ");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fPede,new TGLayoutHints(lhints ,2,2,1,1));
  fPede->ChangeOff();
  fPede->Connect("Modified()","FrameEventView",this,"Update()");

  fGain  = new TGTextButtonMod(cBottom,"    Gain Cal.    ");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fGain,new TGLayoutHints(lhints ,2,2,1,1));
  fGain->ChangeOff();
  //fGain->Connect("Modified()","FrameEventView",this,"Update()");
  fGain->Connect("ChangedOn()","FrameEventView",this,"GainCalibOn()");
  fGain->Connect("ChangedOff()","FrameEventView",this,"GainCalibOff()");

  fSearchArm2  = new TGTextButtonMod(cBottom,"Arm2");
  //fSearchArm2->SetBackgroundColor(color_red);
  fSearchArm2->SetTextColor(color_red);
  //fSearchArm2->SetFont("-*-new century schoolbook-medium-r-*-*-14-*-*-*-*-*-*-*");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fSearchArm2,new TGLayoutHints(lhints ,2,2,1,1));
  fSearchArm2->ChangeOn();

  fSearchBeam  = new TGTextButtonMod(cBottom,"BEAM");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fSearchBeam,new TGLayoutHints(lhints ,2,2,1,1));
  fSearchBeam->ChangeOn(); 
  
  fSearchPede  = new TGTextButtonMod(cBottom,"PEDE");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fSearchPede,new TGLayoutHints(lhints ,2,2,1,1));
  fSearchPede->ChangeOn(); 

  fSearchLaser  = new TGTextButtonMod(cBottom,"Laser");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fSearchLaser,new TGLayoutHints(lhints ,2,2,1,1));
  fSearchLaser->ChangeOn(); 

  fNext = new TGTextButton(cBottom," Next  >> ");
  lhints = kLHintsLeft | kLHintsBottom |  kLHintsExpandX ;
  cBottom->AddFrame(fNext,new TGLayoutHints(lhints ,2,2,1,1));
  fNext->Connect("Pressed()","FrameEventView",this,"Next()");

  fGo = new TGTextButton(cBottom,"  Go  ");
  lhints = kLHintsLeft | kLHintsBottom ;
  cBottom->AddFrame(fGo,new TGLayoutHints(lhints ,2,2,1,1));
  fGo->Connect("Pressed()","FrameEventView",this,"Go()");

  fText = new TGTextEntry(cBottom,"");
  lhints = kLHintsLeft | kLHintsBottom ;
  fText->SetWidth(150);
  cBottom->AddFrame( fText,new TGLayoutHints(lhints,1,1,2,2));

  //   fPrint = new TGTextButton(cBottom,"Print");
  //   lhints = kLHintsLeft | kLHintsBottom ;
  //   cBottom->AddFrame(fPrint,new TGLayoutHints(lhints ,1,1,1,1));
  //   fPrint->Connect("Pressed()","FrameEventView",this,"Print()");

  //   fTool = new TGTextButton(cBottom,"Tool");
  //   lhints = kLHintsLeft | kLHintsBottom ;
  //   cBottom->AddFrame(fTool,new TGLayoutHints(lhints ,1,1,1,1));
  //   fTool->Connect("Pressed()","FrameEventView",this,"Tool()");

  lhints = kLHintsBottom | kLHintsLeft |  kLHintsExpandX ;
  fMain->AddFrame(cBottom, new TGLayoutHints(lhints,0,0,0,0));
  
  fMain->SetMWMHints(kMWMDecorAll,
                     kMWMFuncAll,
                     kMWMInputModeless);
  fMain->MapSubwindows();
  fMain->Resize(fMain->GetDefaultSize());
  fMain->MapWindow();  
}

void FrameEventView::Exit(){
  gApplication->Terminate(0);
  return ;
}

int FrameEventView::OpenFile(char *filename){
  if(ifile){
    tree->ResetBranchAddresses();  
    ifile->Close();
    ev->Delete();
    delete ev;
    delete ifile;
  }

  ifile = new TFile(filename);
  if(ifile->IsZombie()){
    cerr << "Cannot Open " << filename << endl;
    Exit(); 
    return -1;
  }
  gROOT->cd();
  
  tree = (TTree*)ifile->Get("LHCfEvents");
  if(!tree){
    cerr << "Cannot find [LHCfEvents] in " << filename << endl;
    Exit();    
    return -1;
  }

  if(!tree->FindBranch("ev.")){
    cerr << "Tree don't have a Branch[ev.]" << endl; 
    Exit(); 
    return -1; 
  }

  ievent = 0;
  nevent = tree->GetEntries();
  
  ev = new LHCfEvent();
  tree->SetBranchAddress("ev.",&ev);
  Show(0);
  run1stev = ev->run;
  
  cout << "#Event : " << nevent << endl;

  return 0;
}

int FrameEventView::Initialize(){

  //   if(ifile==NULL){
  //     cerr << "File is not open." << endl;
  //     Exit();
  //     return -1;
  //   }
  
  a1cal1 = new A1Cal1();  
  a1cal2 = new A1Cal2();
  a1conv = new A1RawToCal1();
  a1conv->ReadScifiPosTable(gLHCfParamFiles->file_a1scifipostable);
  a1hist = new A1CalEventHist("a1ev","A1");
  a1hist->Initialize();
  a1hist->SetCanvas1(canvas_0);
  a1hist->SetCanvas2(canvas_1);
  a1pedesub = new A1PedeSubtract();
  a1pedesub->SetAccumNEvent(100000);
    
  a2cal1 = new A2Cal1();
  a2cal2 = new A2Cal2();
  a2conv = new A2RawToCal1();
  a2convsi = new A2RawToCal1Silicon();
  a2hist = new A2CalEventHist("a2ev","A2");
  a2hist->Initialize();
  a2hist->SetCanvas1(canvas_2);
  a2hist->SetCanvas2(canvas_3);
  a2pedesub = new A2PedeSubtract();
  a2pedesub->SetAccumNEvent(100000);

  a1cal1tocal2      = new A1Cal1ToCal2();
  a1gaincalibration = new A1GainCalibration();
  a1crosstalk       = new A1LHCCrossTalk();
  a2cal1tocal2      = new A2Cal1ToCal2();
  a2gaincalibration = new A2GainCalibration(); 
  SetGainParamters();

  a1rawl1tdraw = NULL;
  a2rawl1tdraw = NULL;
   
  ievent = 0;
  Show(ievent);
  
  a1hist->DrawCanvas1("lowhighdelayscifiall");
  a1hist->DrawCanvas2(); 

  a2hist->DrawCanvas1("lowhighdelaysiliconallsilicontall");
  a2hist->DrawCanvas2();
  
  a1rawl1tdraw = new RawL1TDraw();
  a1rawl1tdraw->Initialize();
 

#if FORMAT == 2010
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_PP2010);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PP2010); 
#elif FORMAT == 2013
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_PP2010);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PPB2013);
#elif FORMAT == 2015
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_PP2015);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PP2015);
#elif FORMAT == 2016
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_PP2015);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PPB2016);
#elif FORMAT == 2017
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_RHICF_OP2017);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PP2015);
#else
  a1hist->SetDisplayFormat(A1CalEventHist::VERSION_PP2015);
  a2hist->SetDisplayFormat(A2CalEventHist::VERSION_PP2015);
#endif 
  
#if FORMAT == 2010 || FORMAT == 2013
    a1rawl1tdraw = new RawL1TDraw();
    a1rawl1tdraw->Initialize();
    a1rawl1tdraw->SetCanvas((TCanvas*)a1hist->c2pad4);
    a1rawl1tdraw->DrawCanvas(); 
    a2rawl1tdraw = new RawL1TDraw();
    a2rawl1tdraw->Initialize();
    a2rawl1tdraw->SetCanvas((TCanvas*)a2hist->c2pad4);
    a2rawl1tdraw->DrawCanvas();
#endif 
    
#if FORMAT == 2013
    a2rawl1tdraw->SetDisplayVersion_pPb2013();
#endif 


  return 0;
}

int FrameEventView::SetGainParamters(){

  a1conv->ReadScifiPosTable(gLHCfParamFiles->file_a1scifipostable);
  a1cal1tocal2->ReadADCRangeTable(gLHCfParamFiles->file_a1adcrange);
  a1cal1tocal2->UseADCRange(false);
  a1cal1tocal2->SetADCRangeThreshold(4000.);
  a1gaincalibration->ReadParticleDefineTable(gLHCfParamFiles->file_a1particledefine,"ADC");
  a1gaincalibration->ReadParticleDefineTable(gLHCfParamFiles->file_a1scifiparticledefine,"SCIFI");
  a1gaincalibration->ReadPMTGainTable(gLHCfParamFiles->file_a1pmtgaintable);
  a1gaincalibration->ReadScifiGainTable(gLHCfParamFiles->file_a1scifigaintable);
  a1gaincalibration->ReadFCGainTable(gLHCfParamFiles->file_a1fcgaintable);
  a1gaincalibration->ReadHVTable(gLHCfParamFiles->file_a1hvtable);
  if(strcmp(gLHCfParamFiles->file_a1scificrosstalky,"")!=0){
    a1crosstalk->CTReadFile(gLHCfParamFiles->file_a1scificrosstalkx,
			    gLHCfParamFiles->file_a1scificrosstalky);
  }
  else{
    a1crosstalk->CTReadFile(gLHCfParamFiles->file_a1scificrosstalkx);
  }

  a2cal1tocal2->ReadADCRangeTable(gLHCfParamFiles->file_a2adcrange);
  a2cal1tocal2->UseADCRange(false);
  a2cal1tocal2->SetADCRangeThreshold(4000.);
  a2gaincalibration->ReadParticleDefineTable(gLHCfParamFiles->file_a2particledefine,"ADC");
  //
  a2gaincalibration->ReadPMTGainTable(gLHCfParamFiles->file_a2pmtgaintable);
  //
  a2gaincalibration->ReadFCGainTable(gLHCfParamFiles->file_a2fcgaintable);
  a2gaincalibration->ReadHVTable(gLHCfParamFiles->file_a2hvtable);

  return 0;
}

int FrameEventView::ReadPedeFile(char *filename){
  a1pedesub->ReadFile(filename);
  a2pedesub->ReadFile(filename); 
  return 0;
}

int FrameEventView::SetConfigDir(char *dir){
  strcpy(configdir,dir);
  return 0;
}

int FrameEventView::GetData(int i){
  if(i<0 || i >= nevent){
    return -1;
  } 
  int check=0;
  ev->Delete();
  tree->GetEntry(i);  
  //cout << "Event: " << i << "   " << hex << ev->GetTag() << dec<< endl;

  if(!fSearchArm1->GetStat() && !fSearchArm2->GetStat()){
    check++;
  }
  // Search Arm1 Event ------------------------------------------------- 
  if( fSearchArm1->GetStat() &&  
      (ev->CheckA1Trg() || ev->CheckA1Sim() ||
       ev->Check("a1raw") || ev->Check("a1cal1") || ev->Check("a1cal2") || ev->Check("a1sim")) ){
    // Data Selection 
    if((fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW)  && ev->Check("a1raw")) ||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A1CAL1) && ev->Check("a1cal1"))||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A1CAL2) && ev->Check("a1cal2"))||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A1SIM)  && ev->Check("a1sim")) ||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW_PP2015) && ev->Check("a1raw")) ||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_RHICFRAW_OP2017) && ev->Check("a1raw")) ){
      
      // BEAM EVENT
      if( fSearchBeam->GetStat() && (ev->a1flag[0] & 0x1000) && !(ev->a1flag[0] & 0x2000) ){  
		  // Additional Filter in the popup menu 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1ALL)  ){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1L2TA) && ev->IsA1L2TAFlag())  { check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1STRG) && ev->IsA1STRGFlag()){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1LTRG) && ev->IsA1LTRGFlag()){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1SLTRG)&& (ev->IsA1STRGFlag() && ev->IsA1LTRGFlag())){ check++; }
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1L2TA_MB) && ev->IsA1L2TAMBFlag()){ check++; }
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A1L2TA_SP) && ev->IsA1L2TASPFlag()){ check++; }
		  
#if FORMAT == 2017
		  // For RHICf operation
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_ALL)  ){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_SHOWER)    && (ev->a1flag[0]&0x010)){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_SHOWER_TS) && (ev->a1flag[0]&0x400)){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_SHOWER_TL) && (ev->a1flag[0]&0x800)){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_SPE1)      && (ev->a1flag[0]&0x080)){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_SPE2)      && (ev->a1flag[0]&0x200)){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_RHICF_STAR)      && (ev->a1flag[1]&0x400000)){ check++;} 
 #endif 
		}
      // PEDESTAL EVENT
      if( fSearchPede->GetStat() && (ev->a1flag[0] & 0x2000) ){  
		  check++;
      }  
      // LASER EVENT
      if( fSearchLaser->GetStat() && (ev->a1flag[0] & 0x4000) ){  
		  check++;
      } 
    }
	 
    // For Data selection with data of Operation 2015
    if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW_PP2015) && ev->Check("a1raw")){
      // BEAM EVENT  
      if( fSearchBeam->GetStat() && (ev->a1flag[0] & 0x1000) && !(ev->a1flag[0] & 0x2000)  ){ 
		  check++;
      }
      // PEDESTAL EVENT
      if( fSearchPede->GetStat() && (ev->a1flag[0] & 0x2000) ){  
		  check++;
      }  
    }

  }

  // Search Arm2 Event ------------------------------------------------- 
  if( fSearchArm2->GetStat() && 
      (ev->CheckA2Trg() || ev->CheckA2Sim() ||
       ev->Check("a2raw") || ev->Check("a2cal1") || ev->Check("a2cal2") || ev->Check("a2sim"))){

    // Data Selection 
    if((fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW)  && ev->Check("a2raw")) ||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2CAL1) && ev->Check("a2cal1"))||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2CAL2) && ev->Check("a2cal2"))||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2SIM)  && ev->Check("a2sim")) || 
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2013)  && ev->Check("a2raw")) ||
       (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2016)  && ev->Check("a2raw"))){

      // BEAM EVENT  
      if( fSearchBeam->GetStat() && (ev->a2flag[0] & 0x1000) && !(ev->a2flag[0] & 0x2000)  ){  
		  // Additional Filter in the popup menu 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2ALL) ){ check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2L2TA) && ev->IsA2L2TAFlag())  { check++;} 
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2STRG) && ev->IsA2STRGFlag()){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2LTRG) && ev->IsA2LTRGFlag()){ check++;}
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2SLTRG) && (ev->IsA2STRGFlag() && ev->IsA2LTRGFlag())){ check++; }
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2L2TA_MB) && ev->IsA2L2TAMBFlag()){ check++; }
		  if(fMenuFilter->IsEntryChecked(M_FILTER_A2L2TA_SP) && ev->IsA2L2TASPFlag()){ check++; }
      }
      // PEDESTAL EVENT
      if( fSearchPede->GetStat() && (ev->a2flag[0] & 0x2000) ){  
		  check++;
      }  
      // LASER EVENT
      if( fSearchLaser->GetStat() && (ev->a2flag[0] & 0x4000) ){  
		  check++;
      } 
    }
    
    // For Data selection with data of Operation 2015
    if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PP2015) && ev->Check("a2raw")){
      // BEAM EVENT  
      if( fSearchBeam->GetStat() && (ev->a2flag[0] & 0x1000) && !(ev->a2flag[0] & 0x2000)  ){ 
		  check++;
      }
      // PEDESTAL EVENT
      if( fSearchPede->GetStat() && (ev->a2flag[0] & 0x2000) ){  
	check++;
      }  
    }


  } 
  if(check){
    return 0;
  }
  else{  
    return -1;
  }
}

int FrameEventView::Show(int i){
  a1hist->Reset();
  a2hist->Reset(); 

  if(GetData(i)<0){
    cerr << "Nodata: event " << i << endl;
    return -1;
  }
  A1Cal1 *a1cal1tmp;
  A2Cal1 *a2cal1tmp;
  
  // Fill Arm1 ---------------------------------------------------------------------------------
  if( ( fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW) && ev->Check("a1raw") ) || 
      ( fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW_PP2015) && ev->Check("a1raw") ) || 
      ( fMenuDatatype->IsEntryChecked(M_DATATYPE_RHICFRAW_OP2017) && ev->Check("a1raw") )  ){
    a1cal1->clear();
    // For data in 2010 etc
    if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW)){
      a1conv->Convert((A1Raw*)ev->Get("a1raw"),a1cal1);
    }
    // For data of Opration 2015
    else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1RAW_PP2015)){
      a1conv->Convert((A1Raw_pp2015*)ev->Get("a1raw"),a1cal1);  
    }
    // For data of Opration 2015
    else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_RHICFRAW_OP2017)){
      a1conv->Convert((RHICfRaw_Op2017*)ev->Get("a1raw"),a1cal1);  
    }

    if(!fGain->GetStat()){
      if(fPede->GetStat()){
		  a1pedesub->Subtract(a1cal1); 
      }
      a1hist->Fill(a1cal1); 
    }
    else{
      a1cal2->clear();
      a1cal1tocal2->CalculateADC(a1cal1);
      if(fPede->GetStat()){
		  a1pedesub->Subtract(a1cal1); 
      }
      a1cal1tocal2->Convert(a1cal1,a1cal2);
      a1gaincalibration->Calculate(a1cal2);
      if(docrosstalk) a1crosstalk->CalibLHCCrossTalk(a1cal2);
      a1hist->Fill(a1cal2);
    }
    tab->GetTabTab(0)->ChangeBackground(color_blue);
    tab->GetTabTab(1)->ChangeBackground(color_blue); 
  }
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1CAL1) && ev->Check("a1cal1")){
    a1cal1tmp = (A1Cal1*) ev->Get("a1cal1");
    if(!fGain->GetStat()){
      if(fPede->GetStat()){
		  a1pedesub->Subtract(a1cal1tmp); 
      }
      a1hist->Fill(a1cal1tmp);
    }
    else{
      a1cal2->clear();
      a1cal1tocal2->CalculateADC(a1cal1tmp);
      if(fPede->GetStat()){
		  a1pedesub->Subtract(a1cal1tmp); 
      }
      a1cal1tocal2->Convert(a1cal1tmp,a1cal2);
      a1gaincalibration->Calculate(a1cal2);
      if(docrosstalk) a1crosstalk->CalibLHCCrossTalk(a1cal2);
      a1hist->Fill(a1cal2);
    }
    tab->GetTabTab(0)->ChangeBackground(color_blue);
    tab->GetTabTab(1)->ChangeBackground(color_blue); 
  }
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1CAL2) && ev->Check("a1cal2")){
    a1hist->Fill((A1Cal2*)ev->Get("a1cal2"));  
    tab->GetTabTab(0)->ChangeBackground(color_blue);
    tab->GetTabTab(1)->ChangeBackground(color_blue); 
  }
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A1SIM) && ev->Check("a1sim")){
    a1hist->Fill((A1Cal2*)ev->Get("a1sim"));
    tab->GetTabTab(0)->ChangeBackground(color_blue);
    tab->GetTabTab(1)->ChangeBackground(color_blue);  
  } 
  else{
    tab->GetTabTab(0)->ChangeBackground(color_nodata);
    tab->GetTabTab(1)->ChangeBackground(color_nodata);
  }

  if(ev->Check("a1rawl1t") && a1rawl1tdraw!=NULL){
    a1rawl1tdraw->Fill((RawL1T*)ev->Get("a1rawl1t"));
  }
  if(ev->Check("a2rawl1t") && a2rawl1tdraw!=NULL){
    a2rawl1tdraw->Fill((RawL1T*)ev->Get("a2rawl1t"));
  }

  a1hist->UpdateCanvas1();
  a1hist->UpdateCanvas2();
  
  // Fill Arm2 ---------------------------------------------------------------------------------
  if( (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW) && ev->Check("a2raw")) || 
      (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2013) && ev->Check("a2raw")) || 
      (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PP2015) && ev->Check("a2raw")) ||
      (fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2016) && ev->Check("a2raw")) ){
    a2cal1->clear(); 
    // For data in 2010 etc
    if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW)){
      a2conv->Convert((A2Raw*)ev->Get("a2raw"),a2cal1);  
      a2convsi->Convert((A2Raw*)ev->Get("a2raw"),a2cal1); 
    }
    // For data of p-Pb collisions in 2013 
    else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2013)){
      a2conv->Convert((A2Raw_pPb2013*)ev->Get("a2raw"),a2cal1);  
      a2convsi->Convert((A2Raw_pPb2013*)ev->Get("a2raw"),a2cal1); 
    }
    // For data of Opration 2015
    else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PP2015)){
      a2conv->Convert((A2Raw_pp2015*)ev->Get("a2raw"),a2cal1);  
      a2convsi->Convert((A2Raw_pp2015*)ev->Get("a2raw"),a2cal1);  
    }
    else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2RAW_PPB2016)){
      a2conv->Convert((A2Raw_pPb2016*)ev->Get("a2raw"),a2cal1);  
      a2convsi->Convert((A2Raw_pPb2016*)ev->Get("a2raw"),a2cal1); 
    }

    if(!fGain->GetStat()){
      if(fPede->GetStat()){
	a2pedesub->Subtract(a2cal1); 
      }
      a2hist->Fill(a2cal1);
    }
    else{
      a2cal2->clear();
      a2cal1tocal2->CalculateADC(a2cal1);
      if(fPede->GetStat()){
	a2pedesub->Subtract(a2cal1); 
      }
      a2cal1tocal2->Convert(a2cal1,a2cal2);
      a2gaincalibration->Calculate(a2cal2);
      a2hist->Fill(a2cal2);
    }
    tab->GetTabTab(2)->ChangeBackground(color_red);
    tab->GetTabTab(3)->ChangeBackground(color_red); 
  } 
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2CAL1) && ev->Check("a2cal1")){
    a2cal1tmp = (A2Cal1*) ev->Get("a2cal1");
    if(!fGain->GetStat()){
      if(fPede->GetStat()){
	a2pedesub->Subtract(a2cal1tmp);  
      }
      a2hist->Fill(a2cal1tmp);  
    }
    else{
      a2cal2->clear();
      a2cal1tocal2->CalculateADC(a2cal1tmp);
      if(fPede->GetStat()){
	a2pedesub->Subtract(a2cal1tmp); 
      }
      a2cal1tocal2->Convert(a2cal1tmp,a2cal2);
      a2gaincalibration->Calculate(a2cal2);
      a2hist->Fill(a2cal2);
    }
    tab->GetTabTab(2)->ChangeBackground(color_red);
    tab->GetTabTab(3)->ChangeBackground(color_red); 
  }
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2CAL2) && ev->Check("a2cal2")){
    a2hist->Fill((A2Cal2*)ev->Get("a2cal2"));   
    tab->GetTabTab(2)->ChangeBackground(color_red);
    tab->GetTabTab(3)->ChangeBackground(color_red); 
  }
  else if(fMenuDatatype->IsEntryChecked(M_DATATYPE_A2SIM) && ev->Check("a2sim")){
    a2hist->Fill((A2Cal2*)ev->Get("a2sim"));   
    tab->GetTabTab(2)->ChangeBackground(color_red);
    tab->GetTabTab(3)->ChangeBackground(color_red); 
  } 
  else{
    tab->GetTabTab(2)->ChangeBackground(color_nodata);
    tab->GetTabTab(3)->ChangeBackground(color_nodata);
  }
  a2hist->UpdateCanvas1();
  a2hist->UpdateCanvas2();
  
  // ADAMO for SPS2010 ---------------------------------------------------------------------------
  if(gAdamoFrame && ev->Check("adamo")){
    gAdamoFrame->FillEvent((SPSAdamo*) ev->Get("adamo"));
  }
  // Print Information by Show() function -------------------------------
  if(fMenuShow->IsEntryChecked(M_SHOW_LHCFEVENT)){
    ev->Show();
    cout << endl;
  }   
//   if(fMenuShow->IsEntryChecked(M_SHOW_A1CAL2) && 
//      ev->Check("a1cal2")){  
//     cout << "================" 
// 	 << ev->Get("a1cal2")->ClassName() << " : " 
// 	 << ev->Get("a1cal2")->GetName()
// 	 << "==================" << endl;
//     ((A1Cal2*) ev->Get("a1cal2"))->Show();
//     cout << endl;
//   }
  if(fMenuShow->IsEntryChecked(M_SHOW_A1REC) && 
     ev->Check("a1rec")){
    cout << "================" 
	 << ev->Get("a1rec")->ClassName() << " : " 
	 << ev->Get("a1rec")->GetName()
	 << "==================" << endl;
    ((Rec0*) ev->Get("a1rec"))->Show();
    cout << endl;
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A1PHYS) && 
     ev->Check("a1phys")){
    cout << "================" 
	 << ev->Get("a1phys")->ClassName() << " : " 
	 << ev->Get("a1phys")->GetName()
	 << "==================" << endl;
    ((A1Phys*) ev->Get("a1phys"))->Show();
    cout << endl; 
  }
//   if(Fmenushow->IsEntryChecked(M_SHOW_A1SIM) && 
//      ev->Check("a1sim")){
//     cout << "================" 
// 	 << ev->Get("a1sim")->ClassName() << " : " 
// 	 << ev->Get("a1sim")->GetName()
// 	 << "==================" << endl;
//     ((A1Cal2*) ev->Get("a1sim"))->Show();
//     cout << endl;
//   }
  if(fMenuShow->IsEntryChecked(M_SHOW_A1SIMIN) && 
     ev->Check("a1simin")){   
    cout << "================" 
	 << ev->Get("a1simin")->ClassName() << " : " 
	 << ev->Get("a1simin")->GetName()
	 << "==================" << endl;
    ((SimIncidents*) ev->Get("a1simin"))->Show(1,-1);
    cout << endl;
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A2CAL2) && 
     ev->Check("a2cal2")){  
    cout << "================" 
	 << ev->Get("a2cal2")->ClassName() << " : " 
	 << ev->Get("a2cal2")->GetName()
	 << "==================" << endl;
    ((A2Cal2*) ev->Get("a2cal2"))->Show();
    cout << endl;
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A2REC) && 
     ev->Check("a2rec")){
    cout << "================" 
	 << ev->Get("a2rec")->ClassName() << " : " 
	 << ev->Get("a2rec")->GetName()
	 << "==================" << endl;
    ((Rec0*) ev->Get("a2rec"))->Show();
    cout << endl;
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A2PHYS) && 
     ev->Check("a2phys")){
    cout << "================" 
	 << ev->Get("a2phys")->ClassName() << " : " 
	 << ev->Get("a2phys")->GetName()
	 << "==================" << endl;
    ((A2Phys*) ev->Get("a2phys"))->Show();
    cout << endl; 
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A2SIM) && 
     ev->Check("a2sim")){
    cout << "================" 
	 << ev->Get("a2sim")->ClassName() << " : " 
	 << ev->Get("a2sim")->GetName()
	 << "==================" << endl;
    ((A2Cal2*) ev->Get("a2sim"))->Show();
    cout << endl;
  }
  if(fMenuShow->IsEntryChecked(M_SHOW_A2SIMIN) && 
     ev->Check("a2simin")){   
    cout << "================" 
	 << ev->Get("a2simin")->ClassName() << " : " 
	 << ev->Get("a2simin")->GetName()
	 << "==================" << endl;
    ((SimIncidents*) ev->Get("a2simin"))->Show(2,-1);
    cout << endl;
  }

  // Fill the event number to the bottom line
  char text[256];
  sprintf(text,"%d",i);
  fText->SetText(text);
  
  return 0;
}

int FrameEventView::Update(){
  return Show(ievent);
}

int FrameEventView::Go(){
  int ie = 0; 
  if(strcmp(fText->GetText(),"")==0){
    ie = ievent;
  }else {
    ie = atoi(fText->GetText());
  }
  
  if(ie>=nevent){
    cout << "Over the #event in the file." << endl;
    ie = nevent-1;
  }

//   if(Show(ie)==0){
//     ievent = ie;
//   }
  
  Show(ie);
  ievent = ie;

  return 0;
}

int FrameEventView::Next(){

  for(int i=0;i<5000;i++){
    if(GetData(++ievent)==0) break;
    if(ievent>=nevent){
      cout << "Over #event in the file"<< endl;
      ievent = nevent -1;
      break;
    }
  } 
  Show(ievent);

  return 0;
}

int FrameEventView::Previous(){

  for(int i=0;i<5000;i++){
    if(GetData(--ievent)==0) break;
  } 
  Show(ievent);

  return 0;
}

int FrameEventView::Print(){
  int itab = tab->GetCurrent();
  char text[256];

  strcpy(text,fText->GetText()); 
  if(strcmp(fText->GetText(),"")==0 || isdigit(text[strlen(text)-1])){
    sprintf(text,"%s_%d.gif",fText->GetText(),itab);
  }

  if(itab==0){ canvas_0->Print(text);}
  if(itab==1){ canvas_1->Print(text);}
  if(itab==2){ canvas_2->Print(text);}
  if(itab==3){ canvas_3->Print(text);} 
  
  return 0;
}

int FrameEventView::MenuOpenData(){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)this,
			    kFDOpen,
			    &fileinfo); 
  if(fileinfo.fFilename==NULL){
  }
  else{
    cout << " Opened "
	 << fileinfo.fFilename << endl;
    OpenFile(fileinfo.fFilename);
  }  
  return 0; 
}

int FrameEventView::MenuOpenPedestal(){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)this,
			    kFDOpen,
			    &fileinfo); 
  if(fileinfo.fFilename==NULL){
  }
  else{
    cout << " Read pedestal file : " << endl
	 << "  " << fileinfo.fFilename << endl;
    ReadPedeFile(fileinfo.fFilename);
  }  
  return 0; 
}

int FrameEventView::SaveAs(){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)this,
			    kFDSave,
			    &fileinfo);
  if(fileinfo.fFilename==NULL){
  }
  else{
    int itab = tab->GetCurrent();
    TCanvas *c = NULL;
    if     (itab==0){ c = canvas_0;}
    else if(itab==1){ c = canvas_1;}
    else if(itab==2){ c = canvas_2;}
    else if(itab==3){ c = canvas_3;}
    
    c->Print(fileinfo.fFilename);
    cout << " "  << c->GetTitle() << " was saved as " << endl
	 << "  " << fileinfo.fFilename << endl;
  }  
  return 0;
}

int FrameEventView::Tool(){
  static int inum = 0;
  char name[256];
  sprintf(name,"ctool_%d",inum);

  gROOT->cd();
  TCanvas* c = new TCanvas(name,"Tool",750,28);
  c->ToggleToolBar();
  c->Update();
  inum++;

  return 0;   
}

int FrameEventView::ClearMenuFilter(int arm){
  if(arm==1){
    fMenuFilter->UnCheckEntry(M_FILTER_A1ALL);
    fMenuFilter->UnCheckEntry(M_FILTER_A1L2TA);
    fMenuFilter->UnCheckEntry(M_FILTER_A1STRG);
    fMenuFilter->UnCheckEntry(M_FILTER_A1LTRG); 
    fMenuFilter->UnCheckEntry(M_FILTER_A1SLTRG);
    fMenuFilter->UnCheckEntry(M_FILTER_A1L2TA_MB);
    fMenuFilter->UnCheckEntry(M_FILTER_A1L2TA_SP);
	 
	 // For RHICf
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_ALL);
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_SHOWER); 
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_SHOWER_TS); 
 	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_SHOWER_TL); 
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_SPE1); 
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_SPE2); 	
	 fMenuFilter->UnCheckEntry(M_FILTER_RHICF_STAR); 
	 
    return 0;
  }
  else if(arm==2){
    fMenuFilter->UnCheckEntry(M_FILTER_A2ALL);
    fMenuFilter->UnCheckEntry(M_FILTER_A2L2TA);
    fMenuFilter->UnCheckEntry(M_FILTER_A2STRG);
    fMenuFilter->UnCheckEntry(M_FILTER_A2LTRG); 
    fMenuFilter->UnCheckEntry(M_FILTER_A2SLTRG);  
    fMenuFilter->UnCheckEntry(M_FILTER_A2L2TA_MB);
    fMenuFilter->UnCheckEntry(M_FILTER_A2L2TA_SP);
    return 0;
  }
  else {
    return -1;
  }
}

int FrameEventView::ClearMenuDatatype(int arm){
  if(arm==1){
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A1RAW);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A1CAL1);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A1CAL2);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A1SIM);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A1RAW_PP2015); 
    fMenuDatatype->UnCheckEntry(M_DATATYPE_RHICFRAW_OP2017); 
    return 0;
  }
  else if(arm==2){
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2RAW);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2CAL1);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2CAL2);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2SIM);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2RAW_PPB2013);  
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2RAW_PP2015);
    fMenuDatatype->UnCheckEntry(M_DATATYPE_A2RAW_PPB2016);  
    return 0;
  }
  else {
    return -1;
  }
}

int FrameEventView::GainCalibOn(){
  a1hist->ClearCanvas1();
  a2hist->ClearCanvas1();
  a1hist->SetHistConfig(1);
  a2hist->SetHistConfig(1);  
  a1hist->DrawCanvas1("lowscifiall");
  a2hist->DrawCanvas1("lowsiliconallsilicont1");   
  Update();
  return 0;
}

int FrameEventView::GainCalibOff(){
  a1hist->ClearCanvas1();
  a2hist->ClearCanvas1();  
  a1hist->SetHistConfig(0);
  a2hist->SetHistConfig(0);  
  a1hist->DrawCanvas1("lowhighdelayscifiall"); 
  a2hist->DrawCanvas1("lowhighdelaysiliconallsilicontall");
  Update();
  return 0;
}

int FrameEventView::HandleMenu(Int_t id){
  switch (id) {
  // Open File -------------------------------------
  case M_FILE_DATA:
    {
      MenuOpenData();  
    }
    break;  
    
  case M_FILE_PEDESTAL:
    {
      MenuOpenPedestal();  
    }
    break;  


  // Save Canvas ----------------------------------- 
  case M_FILE_SAVE_ARM1HIST:
    {
      canvas_0->Print("./arm1hist.gif");
    }
    break;
    
  case M_FILE_SAVE_ARM1VALUE:
    {
      canvas_1->Print("./arm1value.gif");
    }
    break;   

  case M_FILE_SAVE_ARM2HIST:
    {
      canvas_2->Print("./arm2hist.gif");
    }
    break;
    
  case M_FILE_SAVE_ARM2VALUE:
    {
      canvas_3->Print("./arm2value.gif");
    }
    break;    

  case M_FILE_SAVEAS:
    {
      SaveAs();
    }
    break;
    
  case M_FILE_EXIT:
    {
      Exit();
    }
    break;
  // Additional Event Filter For Arm1 ---------------
  case M_FILTER_A1ALL:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1ALL);
    }
    break;   
    
  case M_FILTER_A1L2TA:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1L2TA);
    }
    break;     

  case M_FILTER_A1STRG:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1STRG);
    }
    break;       

  case M_FILTER_A1LTRG:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1LTRG);
    }
    break;   
    
  case M_FILTER_A1SLTRG:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1SLTRG);
    }
    break;  
  case M_FILTER_A1L2TA_MB:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1L2TA_MB);
    } 
  case M_FILTER_A1L2TA_SP:
    {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_A1L2TA_SP);
    }
    break;            
  // Additional Event Filter For Arm2 ---------------
  case M_FILTER_A2ALL:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2ALL);
    }
    break;   
    
  case M_FILTER_A2L2TA:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2L2TA);
    }
    break;     

  case M_FILTER_A2STRG:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2STRG);
    }
    break;       

  case M_FILTER_A2LTRG:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2LTRG);
    }
    break;   
    
  case M_FILTER_A2SLTRG:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2SLTRG);
    }
    break; 
  case M_FILTER_A2L2TA_MB:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2L2TA_MB);
    } 
	 break;
  case M_FILTER_A2L2TA_SP:
    {
      ClearMenuFilter(2);
      fMenuFilter->CheckEntry(M_FILTER_A2L2TA_SP);
    }      
	 break;
	 // Event Filter For RHICf ------------------
  case M_FILTER_RHICF_ALL:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_ALL);
    }      
	 break;
  case M_FILTER_RHICF_SHOWER:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_SHOWER);
    }  
	 break;	 
  case M_FILTER_RHICF_SHOWER_TS:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_SHOWER_TS);
    }
	 break;  	 
  case M_FILTER_RHICF_SHOWER_TL:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_SHOWER_TL);
    } 
	 break;	 	 
  case M_FILTER_RHICF_SPE1:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_SPE1);
    }
	 break; 
  case M_FILTER_RHICF_SPE2:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_SPE2);
    }
 	 break;
  case M_FILTER_RHICF_STAR:
	 {
      ClearMenuFilter(1);
      fMenuFilter->CheckEntry(M_FILTER_RHICF_STAR);
    } 
	 break;
  // DATA TYPE ---------------------------------------
  case M_DATATYPE_A1RAW:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW);
      Update();
    }
    break;       
  case M_DATATYPE_A1RAW_PP2015:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry(M_DATATYPE_A1RAW_PP2015);
      Update();
    }
    break; 
  case M_DATATYPE_A1CAL1:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry(M_DATATYPE_A1CAL1);
      Update();
    }
    break; 
  case M_DATATYPE_A1CAL2:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry(M_DATATYPE_A1CAL2);
      Update();
    }
    break; 
  case M_DATATYPE_A1SIM:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry(M_DATATYPE_A1SIM);
      Update();
    }
    break;   
  case M_DATATYPE_A2RAW:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW);
      Update();
    }
    break;       
  case M_DATATYPE_A2CAL1:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2CAL1);
      Update();
    }
    break; 
  case M_DATATYPE_A2CAL2:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2CAL2);
      Update();
    }
    break; 
  case M_DATATYPE_A2SIM:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2SIM);
      Update();
    }
    break;   
  case M_DATATYPE_A2RAW_PPB2013:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PPB2013);
      Update();
    }
    break; 
  case M_DATATYPE_A2RAW_PP2015:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PP2015);
      Update();
    }
    break;   
  case M_DATATYPE_A2RAW_PPB2016:
    {
      ClearMenuDatatype(2);
      fMenuDatatype->CheckEntry(M_DATATYPE_A2RAW_PPB2016);
      Update();
    }
    break;
    //-----
  case M_DATATYPE_RHICFRAW_OP2017:
    {
      ClearMenuDatatype(1);
      fMenuDatatype->CheckEntry( M_DATATYPE_RHICFRAW_OP2017);
      Update();
    }
    break;  
  // TOOL ---------------------------------------------
  case M_TOOL_EDITER:
    {
      Tool();
    }
    break;  

  case M_TOOL_EVENTTAG:
    {
      new EventTagFrame(fMain);
    }
    break;  
    
  case M_TOOL_MKPEDESTAL:
    {
      new MkPedestalFrame(fMain);
    }
    break;  
    
  case M_TOOL_GAINFCONFIG:
    {
      new GainConfigWindow(fMain);
    }
    break;

  case M_TOOL_ADAMOEVENTVIEW:
    {
      new AdamoFrame(fMain);
    }
    break;   

  case M_SHOW_ALL:   
    { 
      fMenuShow->CheckEntry(M_SHOW_LHCFEVENT);
      fMenuShow->CheckEntry(M_SHOW_A1CAL2);
      fMenuShow->CheckEntry(M_SHOW_A1REC);
      fMenuShow->CheckEntry(M_SHOW_A1PHYS);
      fMenuShow->CheckEntry(M_SHOW_A1SIM);
      fMenuShow->CheckEntry(M_SHOW_A1SIMIN); 
      fMenuShow->CheckEntry(M_SHOW_A2CAL2);
      fMenuShow->CheckEntry(M_SHOW_A2REC);
      fMenuShow->CheckEntry(M_SHOW_A2PHYS);
      fMenuShow->CheckEntry(M_SHOW_A2SIM);
      fMenuShow->CheckEntry(M_SHOW_A2SIMIN); 
      Update();
    }
    break;
  case M_SHOW_CLEAR:   
    {
      fMenuShow->UnCheckEntry(M_SHOW_LHCFEVENT);
      fMenuShow->UnCheckEntry(M_SHOW_A1CAL2);
      fMenuShow->UnCheckEntry(M_SHOW_A1REC);
      fMenuShow->UnCheckEntry(M_SHOW_A1PHYS);
      fMenuShow->UnCheckEntry(M_SHOW_A1SIM);
      fMenuShow->UnCheckEntry(M_SHOW_A1SIMIN); 
      fMenuShow->UnCheckEntry(M_SHOW_A2CAL2);
      fMenuShow->UnCheckEntry(M_SHOW_A2REC);
      fMenuShow->UnCheckEntry(M_SHOW_A2PHYS);
      fMenuShow->UnCheckEntry(M_SHOW_A2SIM);
      fMenuShow->UnCheckEntry(M_SHOW_A2SIMIN); 
      //Update();
    }
    break;  
  case M_SHOW_LHCFEVENT:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_LHCFEVENT)){
		  fMenuShow->UnCheckEntry(M_SHOW_LHCFEVENT);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_LHCFEVENT);
      }
    }
    break;
  case M_SHOW_A1CAL2:   
    {
      cout << fMenuShow->IsEntryChecked(M_SHOW_A1CAL2) << endl;
      if(fMenuShow->IsEntryChecked(M_SHOW_A1CAL2)){
		  fMenuShow->UnCheckEntry(M_SHOW_A1CAL2);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A1CAL2);
      }
    }
    break;
  case M_SHOW_A1REC:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A1REC)){
		  fMenuShow->UnCheckEntry(M_SHOW_A1REC);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A1REC);
      }
    }
    break;   
  case M_SHOW_A1PHYS:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A1PHYS)){
		  fMenuShow->UnCheckEntry(M_SHOW_A1PHYS);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A1PHYS);
      } 
    }
    break;   
  case M_SHOW_A1SIM:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A1SIM)){
	fMenuShow->UnCheckEntry(M_SHOW_A1SIM);
      }
      else{
	fMenuShow->CheckEntry(M_SHOW_A1SIM);	
      }
    }
    break;  
  case M_SHOW_A1SIMIN:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A1SIMIN)){
	fMenuShow->CheckEntry(M_SHOW_A1SIMIN);
      }	
      else{
	fMenuShow->UnCheckEntry(M_SHOW_A1SIMIN);
      }
    }
    break;   
  case M_SHOW_A2CAL2:   
    {
      cout << fMenuShow->IsEntryChecked(M_SHOW_A2CAL2) << endl;
      if(fMenuShow->IsEntryChecked(M_SHOW_A2CAL2)){
		  fMenuShow->UnCheckEntry(M_SHOW_A2CAL2);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A2CAL2);
      }
    }
    break;
  case M_SHOW_A2REC:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A2REC)){
		  fMenuShow->UnCheckEntry(M_SHOW_A2REC);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A2REC);
      }
    }
    break;   
  case M_SHOW_A2PHYS:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A2PHYS)){
		  fMenuShow->UnCheckEntry(M_SHOW_A2PHYS);
      }
      else{
		  fMenuShow->CheckEntry(M_SHOW_A2PHYS);
      } 
    }
    break;   
  case M_SHOW_A2SIM:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A2SIM)){
	fMenuShow->UnCheckEntry(M_SHOW_A2SIM);
      }
      else{
	fMenuShow->CheckEntry(M_SHOW_A2SIM);	
      }
    }
    break;  
  case M_SHOW_A2SIMIN:   
    {
      if(fMenuShow->IsEntryChecked(M_SHOW_A2SIMIN)){
	fMenuShow->CheckEntry(M_SHOW_A2SIMIN);
      }	
      else{
	fMenuShow->UnCheckEntry(M_SHOW_A2SIMIN);
      }
    }
    break;   

  default:
    {
      printf("Menu item %d selected\n", id);
    }
    break;
  }
  return 0;
}

#endif
