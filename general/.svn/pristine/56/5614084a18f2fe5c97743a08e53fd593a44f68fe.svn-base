#ifndef __ADAMOFRAME_CPP__
#define __ADAMOFRAME_CPP__

#include "AdamoFrame.h"
#include "MkAdamoPedestalFrame.h"
#include <TGFileDialog.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

AdamoFrame *gAdamoFrame = NULL;

AdamoFrame::AdamoFrame(const TGMainFrame *m){
  fParent = m;

  chk_pedesub  = false;
  chk_allstrip = false;
  
  data         = new SPSAdamo();
  hist         = new SPSAdamoHist();
  pedesubtract = new SPSAdamoPedeSubtract();

  // Make Frame
  MakeFrame();
  
  gAdamoFrame = this;
  
  return ;
}

AdamoFrame::~AdamoFrame(){

  fMain->CloseWindow();

  hist->SetCanvas(NULL); // to avoid calling "delete canvas"
  delete data; 
  delete hist;
  delete pedesubtract;

  gAdamoFrame = NULL;
}

void AdamoFrame::MakeFrame(){
  const int size_h = 750;
  const int size_w = 800; 
  
  ULong_t lhints;
  fMain = new TGMainFrame(gClient->GetRoot(),
			  size_h,size_w);
  
//   fMain = new TGTransientFrame(gClient->GetRoot(),
// 			       fParent,
// 			       size_h,size_w);
  // If I used TGTransitionFrame instead of TGMainFrame, the frame(window)
  // was always in the front of the main window. It is impossible to change 
  // it even if I clicked the main window. 
  
  fMain->Connect("CloseWindow()","AdamoFrame",this,"Close()");
  fMain->SetWindowName("ADAMO Event");
  //fMain->DontCallClose();
  fMain->SetCleanup(kDeepCleanup);
  
  // ---------------------------------------------------------------

  lhints = kLHintsLeft | kLHintsTop;
  fCanvas = new TRootEmbeddedCanvas("fCanvas",fMain,700,800);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY ;
  fMain->AddFrame(fCanvas,new TGLayoutHints(lhints,0,0,0,0));
  canvas = fCanvas->GetCanvas();
  
  // ---------------------------------------------------------------
  TGCompositeFrame *fFbottons
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);
  
  // Save the figure
  fSave = new TGTextButton(fFbottons," Save as ");
  fSave->ChangeOptions(fSave->GetOptions() | kFixedSize);
  fSave->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fSave,
                      new TGLayoutHints(lhints ,2,2,0,0));
  fSave->Connect("Pressed()","AdamoFrame",this,"SaveAs()"); 

  // Strip selection 
  fSelection = new TGCheckButton(fFbottons,"Draw all strips");
  fSelection->ChangeOptions(fSelection->GetOptions() | kFixedSize);
  fSelection->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fSelection,
                      new TGLayoutHints(lhints ,2,2,0,0));
  fSelection->Connect("Pressed()","AdamoFrame",this,"SetFillAllStrip()"); 


  //   Pedestal subtraction button
  fPede = new TGTextButtonMod(fFbottons," Pedestal Subtraction ");
  fPede->ChangeOptions(fPede->GetOptions() | kFixedSize);
  fPede->SetWidth(130);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fPede,
                      new TGLayoutHints(lhints ,2,2,0,0));
  fPede->ChangeOff();
  fPede->Connect("Modified()","AdamoFrame",this,"SetPedeSubtraction()");
  
  //  Open Pedestal Table
  fOpenPede = new TGTextButton(fFbottons," Open Pedestal Table ");
  fOpenPede->ChangeOptions(fOpenPede->GetOptions() | kFixedSize);
  fOpenPede->SetWidth(130);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fOpenPede,
                      new TGLayoutHints(lhints ,2,2,0,0));
  fOpenPede->Connect("Pressed()","AdamoFrame",this,"OpenPedestal()");

  //   Make Pedestal Table 
  fMkPede = new TGTextButton(fFbottons," Make Pedestal Table ");
  fMkPede->ChangeOptions(fMkPede->GetOptions() | kFixedSize);
  fMkPede->SetWidth(130);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fMkPede,
                      new TGLayoutHints(lhints ,2,2,0,0));
  fMkPede->Connect("Pressed()","AdamoFrame",this,"MakePedestal()");

  // Close button
  fClose = new TGTextButton(fFbottons,"&CLOSE");
  fClose->ChangeOptions(fClose->GetOptions() | kFixedSize);
  fClose->SetWidth(100);
  lhints = kLHintsRight | kLHintsTop ;
  fFbottons->AddFrame(fClose,
                  new TGLayoutHints(lhints ,2,2,0,0));
  fClose->Connect("Pressed()","AdamoFrame",this,"Close()");
  
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX;
  fMain->AddFrame(fFbottons,
                  new TGLayoutHints(lhints ,5,5,0,0));
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // For SPSAdamoHist
  canvas->Divide(2,5,0.001,0.001);
  hist->SetCanvas(canvas);
  hist->Fill(data);
  hist->DrawCanvas();

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //fMain->CenterOnParent();
  fMain->SetMWMHints(kMWMDecorAll,
                     kMWMFuncAll,
                     kMWMInputModeless);
  fMain->MapSubwindows();
  fMain->Resize(fMain->GetDefaultSize());
  fMain->MapWindow();

  return ;
}

void AdamoFrame::Close(){
  fClose->Disconnect("Pressed()");
  delete this;
}

void AdamoFrame::FillEvent(SPSAdamo *d){
  data->copydata(d);
  Update();
}

void AdamoFrame::Update(){
  SPSAdamo datatmp;
  datatmp.copydata(data);

  if(chk_pedesub){
    pedesubtract->SubtractPedeAverage(&datatmp);
    pedesubtract->SubtractCommonNoise(&datatmp);
  }  
  char fill_option[10]="S";
  if(chk_allstrip){
    strcpy(fill_option,"");
  }
  
  hist->Reset();
  hist->Fill(&datatmp,fill_option);
  hist->UpdateCanvas();

  hist->UpdateCanvas();
}

void AdamoFrame::SaveAs(){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)this,
			    kFDSave,
			    &fileinfo);
  if(fileinfo.fFilename==NULL){
  }
  else{
    canvas->Print(fileinfo.fFilename);
  }  
}

void AdamoFrame::SetPedeSubtraction(){
  chk_pedesub = fPede->GetStat(); 
  Update();
}

void AdamoFrame::SetFillAllStrip(){
  chk_allstrip = fSelection->GetState();
  Update();
}

void AdamoFrame::MakePedestal(){
  new MkAdamoPedestalFrame(fMain);
}

void AdamoFrame::OpenPedestal(){
  TGFileInfo   fileinfo;
  TGFileDialog *dialog;
  dialog = new TGFileDialog(gClient->GetRoot(),
			    (TGMainFrame*)fMain,
			    kFDOpen,
			    &fileinfo); 
  if(fileinfo.fFilename==NULL){
  }
  else{
    cout << " Read pedestal file : " << endl
	 << "  " << fileinfo.fFilename << endl;
    pedesubtract->ReadFile(fileinfo.fFilename);
  }  
  return ; 
}

#endif
