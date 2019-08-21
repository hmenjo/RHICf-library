#ifndef __MKADAMOPEDESTALFRAME_CPP__
#define __MKADAMOPEDESTALFRAME_CPP__

#include "MkAdamoPedestalFrame.h"
#include "FrameEventView.h"
#include "LHCfEvent.h"
#include "AdamoFrame.h"

#include <TVirtualX.h>
#include <TSystem.h>
#include <TGFileDialog.h>

#include <iostream>
#include <iomanip>
using namespace std;

MkAdamoPedestalFrame::MkAdamoPedestalFrame(const TGMainFrame *m){
  fParent = m;

  // Make Frame
  MakeFrame();
}

MkAdamoPedestalFrame::~MkAdamoPedestalFrame(){
  fMain->CloseWindow();
}

void MkAdamoPedestalFrame::MakeFrame(){
  ULong_t lhints;

  fMain = new TGTransientFrame(gClient->GetRoot(),
                               fParent,
                               100,100);
  fMain->Connect("CloseWindow()","MkAdamoPedestalFrame",this,"Close()");
  fMain->SetWindowName("Calculate ADAMO Pedestal Table");
  fMain->DontCallClose();
  fMain->SetCleanup(kDeepCleanup);
  
  // ------------------------------------------------------------
  fLabel = new TGLabel(fMain,"Calculate ADAMO Pedestal");
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
  fProgress1->SetBarColor("blue");
  fProgress1->SetFillType(TGProgressBar::kBlockFill);
  fProgress1->ShowPosition(kTRUE, kFALSE, "%.0f events");
  lhints = kLHintsCenterX | kLHintsTop ;
  fMain->AddFrame(fProgress1,new TGLayoutHints(lhints, 2,2,5,0)); 

  fCalculate = new TGTextButton(fMain,"Calculate");
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fMain->AddFrame(fCalculate,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fCalculate->Connect("Pressed()","MkAdamoPedestalFrame",this,"Calculate()");

  TGCompositeFrame *fFbuttons
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);
  
  fSave = new TGTextButton(fFbuttons,"Save");
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX ;
  fFbuttons->AddFrame(fSave,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fSave->Connect("Pressed()","MkAdamoPedestalFrame",this,"Save()");
  
  fClose = new TGTextButton(fFbuttons,"Close");
  lhints = kLHintsLeft  | kLHintsTop | kLHintsExpandX ;
  fFbuttons->AddFrame(fClose,
		  new TGLayoutHints(lhints ,0,0,0,0));
  fClose->Connect("Pressed()","MkAdamoPedestalFrame",this,"Close()");

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

void MkAdamoPedestalFrame::Calculate(){
  int npede  = fNumber->GetIntNumber();
  int cevent = gFrameEventView->GetIEvent();
  
  fProgress1->SetMin(0);
  fProgress1->SetMax(npede);

  // ++++++ LOOP ++++++
  int            ipede = 0; 
  bool           check_pedeflag;
  TTree         *tree   = gFrameEventView->tree;
  LHCfEvent     *ev     = gFrameEventView->ev;
  int            nevent = gFrameEventView->GetNEvent(); 
  A1Cal1        *a1cal1 = gFrameEventView->a1cal1;
  A2Cal1        *a2cal1 = gFrameEventView->a2cal1; 
  SPSAdamo      *adamo  = NULL;
  A1RawToCal1   *a1conv = gFrameEventView->a1conv;
  A2RawToCal1   *a2conv = gFrameEventView->a2conv;
  SPSAdamoPedeSubtract  *pedesub = gAdamoFrame->pedesubtract;
  for(int i=0;i<nevent;i++){
    ev->Delete();
    tree->GetEntry(i); 
   
    //if(!ev->Check("a1raw")){continue;}
    if(!ev->Check("a1raw")  && !ev->Check("a2raw") && 
       !ev->Check("a1cal1") && !ev->Check("a2cal1")){continue;}
    
    check_pedeflag = false;

    // For Arm1
    if(ev->Check("a1raw") || ev->Check("a1cal1")){
      if(ev->Check("a1raw")){
	a1conv->Convert(ev->GetA1Raw("a1raw"),a1cal1);
      }
      else if(ev->Check("a1cal1")){
	a1cal1 = (A1Cal1*) ev->Get("a1cal1");
      }
      if(a1cal1->flag_pede){ check_pedeflag = true; }
    }
    
    // For Arm2
    if(ev->Check("a2raw") || ev->Check("a2cal1")){
      if(ev->Check("a2raw")){
	a2conv->Convert(ev->GetA2Raw("a2raw"),a2cal1);
      }
      else if(ev->Check("a2cal1")){
	a2cal1 = (A2Cal1*) ev->Get("a2cal1");
      }
      if(a2cal1->flag_pede){ check_pedeflag = true; }  
    }

    if(check_pedeflag){
      adamo = (SPSAdamo*) ev->Get("adamo");
      pedesub->FillPedeEvent(adamo);
      ipede++;
      fProgress1->Increment(1);
      gSystem->ProcessEvents();
    } 

    if(ipede >= npede){
      break;
    }
  }

  pedesub->CalPedestal();

  if(ipede >= npede){
    fLabel->SetText("!! DONE !!");
  }
  else {
    fLabel->SetText("Not eought pedestal event");
  }
  gClient->NeedRedraw(fLabel,kTRUE);
  gVirtualX->Update();
  
  gFrameEventView->SetIEvent(cevent);
}

void MkAdamoPedestalFrame::Save(){
  char *default_filename = new char[256];
  strcpy(default_filename,"pedestal_adamo.root");
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
    gAdamoFrame->pedesubtract->WriteFile(fileinfo.fFilename);
  }
  return ;
}

void MkAdamoPedestalFrame::Close(){
  fClose->Disconnect("Pressed()");
  delete this;
}



#endif
