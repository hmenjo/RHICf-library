#ifndef __GAINCONFIGWINDOW_CPP__
#define __GAINCONFIGWINDOW_CPP__

#include "GainConfigWindow.h"

#include <TVirtualX.h>
#include <TSystem.h>
#include <TGFileDialog.h>

#include "FrameEventView.h"
#include "LHCfParamFiles.h"

#include <iostream>
#include <iomanip>
using namespace std;


GainConfigWindow::GainConfigWindow(const TGMainFrame *m){
  fParent = m;

  // Make Frame
  MakeFrame();
}

GainConfigWindow::~GainConfigWindow(){
  fMain->CloseWindow();
}

void GainConfigWindow::MakeFrame(){
  ULong_t lhints;
  ULong_t lhintsx = kLHintsLeft  | kLHintsTop | kLHintsExpandX ;
  ULong_t lhintsxy = kLHintsLeft  | kLHintsTop | kLHintsExpandX | kLHintsExpandY ; 
  TGCompositeFrame *fLine;
 
  int textsize = 700;

  fMain = new TGTransientFrame(gClient->GetRoot(),
                               fParent,
                               100,100);

  fMain->Connect("CloseWindow()","GainConfigWindow",this,"Close()");
  fMain->SetWindowName("Configuration of Gain Calibration");
  fMain->DontCallClose();
  fMain->SetCleanup(kDeepCleanup);

  // ---------------------------------------------------------
  // --------------------- DEFAULT SET -----------------------
  // ---------------------------------------------------------

  TGCompositeFrame *fFdefaults
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);
  
  fBdefault_Op2010 = new TGTextButton(fFdefaults,"Set To Default in 2010");
  fFdefaults->AddFrame(fBdefault_Op2010,new TGLayoutHints(lhintsx ,0,0,0,0));
  fBdefault_Op2010->Connect("Pressed()","GainConfigWindow",this,"SetToDefault_Op2010()");
  
  fBdefault_Op2013 = new TGTextButton(fFdefaults,"Set To Default in 2013");
  fFdefaults->AddFrame(fBdefault_Op2013,new TGLayoutHints(lhintsx ,0,0,0,0));
  fBdefault_Op2013->Connect("Pressed()","GainConfigWindow",this,"SetToDefault_Op2013()");

  fBdefault_Op2015 = new TGTextButton(fFdefaults,"Set To Default in 2015");
  fFdefaults->AddFrame(fBdefault_Op2015,new TGLayoutHints(lhintsx ,0,0,0,0));
  fBdefault_Op2015->Connect("Pressed()","GainConfigWindow",this,"SetToDefault_Op2015()");
  
  fBdefault_RHICf2017 = new TGTextButton(fFdefaults,"Set To Default For RHICf2017");
  fFdefaults->AddFrame(fBdefault_RHICf2017,new TGLayoutHints(lhintsx ,0,0,0,0));
  fBdefault_RHICf2017->Connect("Pressed()","GainConfigWindow",this,"SetToDefault_RHICf2017()");

  fMain->AddFrame(fFdefaults,new TGLayoutHints(lhintsx,0,0,0,0));

  // ---------------------------------------------------------
  // -------------------------- Arm1 -------------------------
  // ---------------------------------------------------------

  TGGroupFrame* fArm1 = new TGGroupFrame(fMain,"  Arm1  ",
					 kVerticalFrame);
  fArm1->SetTextFont("-*-courier-bold-r-*-*-17-*-*-*-*-*-*-*");
  fArm1->SetTextColor(gFrameEventView->color_blue);
 
  lhints = kLHintsLeft  | kLHintsTop;

  // --- HV Table ---
  TGLabel *fA1Label_hv = new TGLabel(fArm1,"H.V. Table");
  //fA1Label_hv->SetTextFont("-*-courier-bold-r-*-*-14-*-*-*-*-*-*-*");
  fArm1->AddFrame(fA1Label_hv, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm1, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA1Text_hv = new TGTextEntry(fLine,gLHCfParamFiles->file_a1hvtable);
  fLine->AddFrame( fA1Text_hv, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA1Holder_hv = new TGPictureButton(fLine,
  				     gClient->GetPicture("bld_open.xpm"));
  fA1Holder_hv->Connect("Pressed()","GainConfigWindow",this,"FileArm1HVTable()");
  fLine->AddFrame(fA1Holder_hv, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm1->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));
 
  // --- Particle Table for Scintillator ---
  TGLabel *fA1Label_pdefs = new TGLabel(fArm1,"Particle Table For Scintillator");
  fArm1->AddFrame(fA1Label_pdefs, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm1, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA1Text_pdefs = new TGTextEntry(fLine,gLHCfParamFiles->file_a1particledefine);
  fLine->AddFrame( fA1Text_pdefs, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA1Holder_pdefs = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA1Holder_pdefs->Connect("Pressed()","GainConfigWindow",this,"FileArm1Pdefs()");
  fLine->AddFrame(fA1Holder_pdefs, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm1->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));

  // --- Particle Table for SciFi ---
  TGLabel *fA1Label_pdefscifi = new TGLabel(fArm1,"Particle Table For SciFi");
  fArm1->AddFrame(fA1Label_pdefscifi, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm1, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA1Text_pdefscifi = new TGTextEntry(fLine,gLHCfParamFiles->file_a1scifiparticledefine);
  fLine->AddFrame( fA1Text_pdefscifi, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA1Holder_pdefscifi = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA1Holder_pdefscifi->Connect("Pressed()","GainConfigWindow",this,"FileArm1PdefSciFi()");
  fLine->AddFrame(fA1Holder_pdefscifi, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm1->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));

  // --- Particle Table for FC ---
  TGLabel *fA1Label_pdeffc = new TGLabel(fArm1,"Particle Table For FC");
  fArm1->AddFrame(fA1Label_pdeffc, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm1, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA1Text_pdeffc = new TGTextEntry(fLine,gLHCfParamFiles->file_a1fcparticledefine);
  fLine->AddFrame( fA1Text_pdeffc, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA1Holder_pdeffc = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA1Holder_pdeffc->Connect("Pressed()","GainConfigWindow",this,"FileArm1PdefFC()");
  fLine->AddFrame(fA1Holder_pdeffc, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm1->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));
  
  // -----------
  fMain->AddFrame(fArm1,new TGLayoutHints(lhintsx,5,5,5,0));

  // ---------------------------------------------------------
  // -------------------------- Arm2 -------------------------
  // ---------------------------------------------------------

  TGGroupFrame* fArm2 = new TGGroupFrame(fMain,"  Arm2  ",
					 kVerticalFrame);
  fArm2->SetTextFont("-*-courier-bold-r-*-*-17-*-*-*-*-*-*-*");
  fArm2->SetTextColor(gFrameEventView->color_red);
 
  lhints = kLHintsLeft  | kLHintsTop;

  // --- HV Table ---
  TGLabel *fA2Label_hv = new TGLabel(fArm2,"H.V. Table");
  fArm2->AddFrame(fA2Label_hv, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm2, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA2Text_hv = new TGTextEntry(fLine,gLHCfParamFiles->file_a2hvtable);
  fLine->AddFrame( fA2Text_hv, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA2Holder_hv = new TGPictureButton(fLine,
  				     gClient->GetPicture("bld_open.xpm"));
  fA2Holder_hv->Connect("Pressed()","GainConfigWindow",this,"FileArm2HVTable()");
  fLine->AddFrame(fA2Holder_hv, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm2->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));
 
  // --- Particle Table for Scintillator ---
  TGLabel *fA2Label_pdefs = new TGLabel(fArm2,"Particle Table For Scintillator");
  fArm2->AddFrame(fA2Label_pdefs, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm2, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA2Text_pdefs = new TGTextEntry(fLine,gLHCfParamFiles->file_a2particledefine);
  fLine->AddFrame( fA2Text_pdefs, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA2Holder_pdefs = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA2Holder_pdefs->Connect("Pressed()","GainConfigWindow",this,"FileArm2Pdefs()");
  fLine->AddFrame(fA2Holder_pdefs, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm2->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));

  // --- Particle Table for Si ---
  TGLabel *fA2Label_pdefsi = new TGLabel(fArm2,"Particle Table For Si");
  fArm2->AddFrame(fA2Label_pdefsi, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm2, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA2Text_pdefsi = new TGTextEntry(fLine,gLHCfParamFiles->file_a2siparticledefine);
  fLine->AddFrame( fA2Text_pdefsi, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA2Holder_pdefsi = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA2Holder_pdefsi->Connect("Pressed()","GainConfigWindow",this,"FileArm2PdefSi()");
  fLine->AddFrame(fA2Holder_pdefsi, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm2->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));

  // --- Particle Table for FC ---
  TGLabel *fA2Label_pdeffc = new TGLabel(fArm2,"Particle Table For FC");
  fArm2->AddFrame(fA2Label_pdeffc, new TGLayoutHints(lhints, 10,2,8,2));

  fLine = new TGCompositeFrame(fArm2, textsize, 8, kHorizontalFrame|kFixedWidth);

  fA2Text_pdeffc = new TGTextEntry(fLine,gLHCfParamFiles->file_a2fcparticledefine);
  fLine->AddFrame( fA2Text_pdeffc, new TGLayoutHints(lhintsxy, 0,2,0,0));
 
  fA2Holder_pdeffc = new TGPictureButton(fLine,
					gClient->GetPicture("bld_open.xpm"));
  fA2Holder_pdeffc->Connect("Pressed()","GainConfigWindow",this,"FileArm2PdefFC()");
  fLine->AddFrame(fA2Holder_pdeffc, new TGLayoutHints(lhints, 0,0,0,0));
  
  fArm2->AddFrame(fLine , new TGLayoutHints(lhintsx,0,0,0,0));
  
  // -----------
  fMain->AddFrame(fArm2,new TGLayoutHints(lhintsx,5,5,5,0));

  // Buttons --------------------------------------------------
  
  TGCompositeFrame *fFbuttons
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);

  fCancel = new TGTextButton(fFbuttons,"&Cancel");

  fFbuttons ->AddFrame(fCancel,new TGLayoutHints(lhintsx ,0,0,0,0));
  fCancel->Connect("Pressed()","GainConfigWindow",this,"Cancel()");

  fOK = new TGTextButton(fFbuttons,"&OK");

  fFbuttons ->AddFrame(fOK,new TGLayoutHints(lhintsx ,0,0,0,0));
  fOK->Connect("Pressed()","GainConfigWindow",this,"Ok()");

  fMain->AddFrame(fFbuttons,new TGLayoutHints(lhintsx,0,0,0,0));
  // ------------------------------------------------------------
  fMain->CenterOnParent();
  fMain->SetMWMHints(kMWMDecorAll,
                     kMWMFuncAll,
                     kMWMInputModeless);
  fMain->MapSubwindows();
  fMain->Resize(fMain->GetDefaultSize());
  fMain->MapWindow();
  return ;
}

void GainConfigWindow::Ok(){
  fOK->Disconnect("Pressed()");
  fCancel->Disconnect("Pressed()"); 
  
  strcpy(gLHCfParamFiles->file_a1hvtable,             fA1Text_hv->GetText());
  strcpy(gLHCfParamFiles->file_a1particledefine,      fA1Text_pdefs->GetText());
  strcpy(gLHCfParamFiles->file_a1scifiparticledefine, fA1Text_pdefscifi->GetText());
  strcpy(gLHCfParamFiles->file_a1fcparticledefine,    fA1Text_pdeffc->GetText());
  strcpy(gLHCfParamFiles->file_a2hvtable,             fA2Text_hv->GetText());
  strcpy(gLHCfParamFiles->file_a2particledefine,      fA2Text_pdefs->GetText());
  strcpy(gLHCfParamFiles->file_a2siparticledefine,    fA2Text_pdefsi->GetText());
  strcpy(gLHCfParamFiles->file_a2fcparticledefine,    fA2Text_pdeffc->GetText());

  gFrameEventView->SetGainParamters();
  gFrameEventView->Update();

  gLHCfParamFiles->Write();

  delete this;
}

void GainConfigWindow::Cancel(){ 
  fOK->Disconnect("Pressed()"); 
  fCancel->Disconnect("Pressed()"); 

  delete this;
}

void GainConfigWindow::Close(){
 
  fOK->Disconnect("Pressed()"); 
  fCancel->Disconnect("Pressed()"); 

  delete this;
}


int GainConfigWindow::FileOpen(string &ss){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)this,
			    kFDOpen,
			    &fileinfo); 
  if(fileinfo.fFilename==NULL){
    ss = "";
    return 0;
  }
  else{
    ss = fileinfo.fFilename;
    return 1;
  }  
}

void GainConfigWindow::FileArm1HVTable(){
  string ss;
  if(FileOpen(ss)){
    fA1Text_hv->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm1Pdefs(){
  string ss;
  if(FileOpen(ss)){
    fA1Text_pdefs->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm1PdefSciFi(){
  string ss;
  if(FileOpen(ss)){
    fA1Text_pdefscifi->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm1PdefFC(){
  string ss;
  if(FileOpen(ss)){
    fA1Text_pdeffc->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm2HVTable(){
  string ss;
  if(FileOpen(ss)){
    fA2Text_hv->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm2Pdefs(){
  string ss;
  if(FileOpen(ss)){
    fA2Text_pdefs->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm2PdefSi(){
  string ss;
  if(FileOpen(ss)){
    fA2Text_pdefsi->SetText(ss.c_str());
  }  
  return ; 
}

void GainConfigWindow::FileArm2PdefFC(){
  string ss;
  if(FileOpen(ss)){
    fA2Text_pdeffc->SetText(ss.c_str());
  }  
  return ; 
}

void  GainConfigWindow::SetToDefault_Op2010(){
  gLHCfParamFiles->SetToDefault_Op2010();
  ParameterUpdate();
}

void  GainConfigWindow::SetToDefault_Op2013(){
  gLHCfParamFiles->SetToDefault_Op2013();
  ParameterUpdate();
}

void  GainConfigWindow::SetToDefault_Op2015(){
  gLHCfParamFiles->SetToDefault_Op2015();
  ParameterUpdate();
}

void  GainConfigWindow::SetToDefault_RHICf2017(){
  gLHCfParamFiles->SetToDefault_RHICf2017();
  ParameterUpdate();
}


void  GainConfigWindow::ParameterUpdate(){
  fA1Text_hv->SetText(gLHCfParamFiles->file_a1hvtable);
  fA1Text_pdefs->SetText(gLHCfParamFiles->file_a1particledefine);
  fA1Text_pdefscifi->SetText(gLHCfParamFiles->file_a1scifiparticledefine);
  fA1Text_pdeffc->SetText(gLHCfParamFiles->file_a1fcparticledefine);
  
  fA2Text_hv->SetText(gLHCfParamFiles->file_a2hvtable);
  fA2Text_pdefs->SetText(gLHCfParamFiles->file_a2particledefine);
  fA2Text_pdefsi->SetText(gLHCfParamFiles->file_a2siparticledefine);
  fA2Text_pdeffc->SetText(gLHCfParamFiles->file_a2fcparticledefine);
}

#endif
