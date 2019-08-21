#ifndef __MKPEDESTALFRAME_CPP__
#define __MKPEDESTALFRAME_CPP__

#include "MkPedestalFrame.h"
#include "FrameEventView.h"
#include "LHCfEvent.h"

#include <TVirtualX.h>
#include <TSystem.h>
#include <TGFileDialog.h>

#include <iostream>
#include <iomanip>
using namespace std;

MkPedestalFrame::MkPedestalFrame(const TGMainFrame *m){
  fParent = m;

  // Make Frame
  MakeFrame();
}

MkPedestalFrame::~MkPedestalFrame(){
  fMain->CloseWindow();
}

void MkPedestalFrame::MakeFrame(){
  ULong_t lhints;

  fMain = new TGTransientFrame(gClient->GetRoot(),
                               fParent,
                               100,100);
  fMain->Connect("CloseWindow()","MkPedestalFrame",this,"Close()");
  fMain->SetWindowName("Calculate Pedestal Table");
  fMain->DontCallClose();
  fMain->SetCleanup(kDeepCleanup);
  
  // ------------------------------------------------------------
  fLabel = new TGLabel(fMain,"Calculate Pedestal Table");
  fLabel->SetTextFont("-adobe-courier-bold-r-*-*-14-*-*-*-*-*-iso8859-1");
  fLabel->SetTextJustify(36);
  fLabel->ChangeOptions(fLabel->GetOptions() | kFixedSize);
  fLabel->SetWidth(250);
  lhints =  kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fMain->AddFrame(fLabel,new TGLayoutHints(lhints, 2,2,2,2));

  
  TGLabel* fLabel2 = new TGLabel(fMain,"Number of Accumulate Pedestal Events");
  lhints =  kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fMain->AddFrame(fLabel2,new TGLayoutHints(lhints, 2,2,2,2));
   
  // default_val,degitwidth,id, 
  fNumber = new TGNumberEntry(fMain, 100, 9,-1,
			      TGNumberFormat::kNESInteger,
			      TGNumberFormat::kNEANonNegative,
			      TGNumberFormat::kNELLimitMinMax,
			      100, 5000);
  fNumber->SetLogStep(kTRUE);
  lhints = kLHintsCenterX | kLHintsTop ;
  fMain->AddFrame(fNumber,new TGLayoutHints(lhints, 2,2,5,5));
  
  fProgress1 = new TGHProgressBar(fMain, TGProgressBar::kFancy, 300);
  fProgress2 = new TGHProgressBar(fMain, TGProgressBar::kFancy, 300);
  fProgress1->SetBarColor("blue");
  fProgress2->SetBarColor("red");
  fProgress1->SetFillType(TGProgressBar::kBlockFill);
  fProgress2->SetFillType(TGProgressBar::kBlockFill);
  fProgress1->ShowPosition(kTRUE, kFALSE, "Arm1 %.0f events");
  fProgress2->ShowPosition(kTRUE, kFALSE, "Arm2 %.0f events");
  lhints = kLHintsCenterX | kLHintsTop ;
  fMain->AddFrame(fProgress1,new TGLayoutHints(lhints, 2,2,5,0)); 
  fMain->AddFrame(fProgress2,new TGLayoutHints(lhints, 2,2,0,5));

  fCalculate = new TGTextButton(fMain,"Calculate");
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fMain->AddFrame(fCalculate,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fCalculate->Connect("Pressed()","MkPedestalFrame",this,"Calculate()");

  TGCompositeFrame *fFbuttons
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);
  
  fSave = new TGTextButton(fFbuttons,"Save");
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fFbuttons->AddFrame(fSave,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fSave->Connect("Pressed()","MkPedestalFrame",this,"Save()");
  
  fClose = new TGTextButton(fFbuttons,"Close");
  lhints = kLHintsLeft  | kLHintsTop | kLHintsExpandX ;
  fFbuttons->AddFrame(fClose,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fClose->Connect("Pressed()","MkPedestalFrame",this,"Close()");

  lhints = kLHintsLeft  | kLHintsTop | kLHintsExpandX ;
  fMain->AddFrame(fFbuttons,
		  new TGLayoutHints(lhints ,0,0,0,0));

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

void MkPedestalFrame::Calculate(){
  int npede  = fNumber->GetIntNumber();
  int cevent = gFrameEventView->GetIEvent();
  
  fProgress1->SetMin(0);
  fProgress1->SetMax(npede);
  fProgress2->SetMin(0);
  fProgress2->SetMax(npede); 

  // ++++++ LOOP ++++++
  int  a1npede = 0;
  int  a2npede = 0;
  TTree     *tree = gFrameEventView->tree;
  LHCfEvent *ev   = gFrameEventView->ev;
  A1PedeSubtract *a1pedesub = gFrameEventView->a1pedesub;
  A2PedeSubtract *a2pedesub = gFrameEventView->a2pedesub; 
  A1RawToCal1    *a1conv    =  gFrameEventView->a1conv;
  A2RawToCal1    *a2conv    =  gFrameEventView->a2conv;
  A2RawToCal1Silicon *a2convsi = gFrameEventView->a2convsi;
  A1Cal1* a1cal1 = gFrameEventView->a1cal1;
  A2Cal1* a2cal1 = gFrameEventView->a2cal1;
  int nevent = gFrameEventView->GetNEvent();
  for(int i=0;i<nevent;i++){
    ev->Delete();
    tree->GetEntry(i); 
    
    // For Arm1
    if(a1npede < npede && ev->Check("a1raw") || ev->Check("a1cal1")){
      if(ev->Check("a1raw")){
	a1conv->Convert(ev->Get("a1raw"),a1cal1);
      }
      else if(ev->Check("a1cal1")){
	a1cal1 = (A1Cal1*) ev->Get("a1cal1");
      }
      if(a1cal1->flag_pede){
	a1pedesub->FillPedeEvent(a1cal1);
	a1npede++;
	fProgress1->Increment(1);
      }  
    }
    
    // For Arm2
    if(a2npede < npede && ev->Check("a2raw") || ev->Check("a2cal1")){
      if(ev->Check("a2raw")){
	a2conv->Convert(ev->Get("a2raw"),a2cal1);
	a2convsi->Convert(ev->Get("a2raw"),a2cal1);
      }
      else if(ev->Check("a2cal1")){
	a2cal1 = (A2Cal1*) ev->Get("a2cal1");
      }
      if(a2cal1->flag_pede){
	a2pedesub->FillPedeEvent(a2cal1);
	a2npede++;
	fProgress2->Increment(1);
      }  
      gSystem->ProcessEvents();
    }
    
    if(a1npede >= npede && a2npede >= npede){
      break;
    }
  }
  
  a1pedesub->CalPedestal();
  a2pedesub->CalPedestal();

  if(a1npede >= npede && a2npede >= npede){
    fLabel->SetText("!! DONE !!");
  }
  else {
    fLabel->SetText("Not eought pedestal event");
  }
  //gClient->NeedRedraw(fLabel,kTRUE);
  //gVirtualX->Update();
  
  gFrameEventView->SetIEvent(cevent);
}

void MkPedestalFrame::Save(){
  char *default_filename = new char[256];
  strcpy(default_filename,"pedestal.root");
  TGFileInfo   fileinfo;
  fileinfo.fFilename = default_filename; 
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
                            (TGMainFrame*)this,
                            kFDSave,
                            &fileinfo);
  if(fileinfo.fFilename==NULL){
  }
  else{
    gFrameEventView->a1pedesub->WriteFile(fileinfo.fFilename);
    gFrameEventView->a2pedesub->WriteFile(fileinfo.fFilename);
  }
  return ;
}

void MkPedestalFrame::Close(){
  fClose->Disconnect("Pressed()");
  delete this;
}



#endif
