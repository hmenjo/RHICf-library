#ifndef __EVENTTAGFRAME_CPP__
#define __EVENTTAGFRAME_CPP__

#include "EventTagFrame.h"
#include "FrameEventView.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int EventTagFrame::NMARKER;

EventTagFrame::EventTagFrame(const TGMainFrame *m){
  fParent = m;
  nmarker = 0;
  for(int i=0;i<NMARKER;i++){
    marker[i] = NULL;
  }
  mcolor = kRed;

  // Make Frame
  MakeFrame();

  // Load Tag Log file
  char fpath[256];
  char filename[512];
  sprintf(fpath,
	  "%s/taglog",
	  gFrameEventView->GetConfigDir());
  sprintf(filename,
	  "%s/run%05d.dat",
	  fpath,gFrameEventView->GetRun1stev());
  
  // create taglog dir
  char command[256];
  sprintf(command,"mkdir -p %s",fpath);
  system(command);
  // load the file
  ReadTag(filename);
}

EventTagFrame::~EventTagFrame(){
  // Write log
  char fpath[256];
  char filename[512];
  sprintf(fpath,
	  "%s/taglog",
	  gFrameEventView->GetConfigDir());
  sprintf(filename,
	  "%s/run%05d.dat",
	  fpath,gFrameEventView->GetRun1stev());
  WriteTag(filename);
  
  if(axis) delete axis;
  for(int i=0;i<NMARKER;i++){
    if(marker[i]!=NULL) delete marker[i]; 
  }
  fMain->CloseWindow();
}

void EventTagFrame::MakeFrame(){
  ULong_t lhints;

  fMain = new TGTransientFrame(gClient->GetRoot(),
			       fParent,
                               100,100);
  fMain->Connect("CloseWindow()","EventTagFrame",this,"Close()");
  fMain->SetWindowName("Event Tag");
  fMain->DontCallClose();
  fMain->SetCleanup(kDeepCleanup);
  
  // ---------------------------------------------------------------
   // status bar
   Int_t parts[] = {50, 50};
   fStatusBar = new TGStatusBar(fMain, 50, 10, kVerticalFrame);
   fStatusBar->SetParts(parts, 2);
   fStatusBar->Draw3DCorner(kFALSE);
   fMain->AddFrame(fStatusBar, 
		   new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 3));

  // ---------------------------------------------------------------

  lhints = kLHintsLeft | kLHintsTop;
  fCanvas = new TRootEmbeddedCanvas("fCanvas",fMain,800,50);
  lhints = kLHintsLeft | kLHintsTop | kLHintsExpandX ;;
  fMain->AddFrame(fCanvas,new TGLayoutHints(lhints,0,0,0,0));
  canvas = fCanvas->GetCanvas();

  // ---------------------------------------------------------------
  TGCompositeFrame *fFbottons
    = new TGCompositeFrame(fMain, 200, 8, kHorizontalFrame);

  fCreate = new TGTextButton(fFbottons,"&Create");
  fCreate->ChangeOptions(fCreate->GetOptions() | kFixedSize);
  fCreate->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop;
  fFbottons->AddFrame(fCreate,
		      new TGLayoutHints(lhints ,5,5,0,0));
  fCreate->Connect("Pressed()","EventTagFrame",this,"CreateTag()");

  fRColor[0] = new TGRadioButton(fFbottons,"Red",  M_COLOR_RED);
  fRColor[1] = new TGRadioButton(fFbottons,"Blue", M_COLOR_BLUE);
  fRColor[2] = new TGRadioButton(fFbottons,"Green",M_COLOR_GREEN);
  lhints = kLHintsLeft | kLHintsTop;
  for(int i=0;i<3;i++){
    fRColor[i]->ChangeOptions(fRColor[i]->GetOptions() | kFixedSize);
    fRColor[i]->SetWidth(60);
    if(i==0){fRColor[i]->SetBackgroundColor(gFrameEventView->color_red);}
    if(i==1){fRColor[i]->SetBackgroundColor(gFrameEventView->color_blue);}
    if(i==2){fRColor[i]->SetBackgroundColor(gFrameEventView->color_green);}
    fRColor[i]->SetFont("-adobe-courier-bold-r-*-*-12-*-*-*-*-*-iso8859-1");
    fFbottons->AddFrame(fRColor[i],
			new TGLayoutHints(lhints ,0,0,0,0));
    fRColor[i]->Connect("Pressed()","EventTagFrame",this,"DoRadio()");
  }
  fRColor[0]->SetState(kButtonDown);

  fTextEntry = new TGTextEntry(fFbottons,new TGTextBuffer(100));
  fTextEntry->Resize(200,fTextEntry->GetDefaultHeight());
  fTextEntry->SetFont("-adobe-courier-bold-r-*-*-14-*-*-*-*-*-iso8859-1");
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fTextEntry,
		      new TGLayoutHints(lhints ,2,2,0,0));

  fUnzoom = new TGTextButton(fFbottons,"Unzoom"); 
  fUnzoom->ChangeOptions(fUnzoom->GetOptions() | kFixedSize);
  fUnzoom->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop;
  fFbottons->AddFrame(fUnzoom,
		      new TGLayoutHints(lhints ,2,2,0,0));
  fUnzoom->Connect("Pressed()","EventTagFrame",this,"Unzoom()");

  fClear = new TGTextButton(fFbottons,"Clear");
  fClear->ChangeOptions(fClear->GetOptions() | kFixedSize);
  fClear->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fClear,
		      new TGLayoutHints(lhints ,2,2,0,0));
  fClear->Connect("Pressed()","EventTagFrame",this,"Clear()");

  fClose = new TGTextButton(fFbottons,"&CLOSE");
  fClose->ChangeOptions(fClose->GetOptions() | kFixedSize);
  fClose->SetWidth(100);
  lhints = kLHintsLeft | kLHintsTop ;
  fFbottons->AddFrame(fClose,
                  new TGLayoutHints(lhints ,2,2,0,0));
  fClose->Connect("Pressed()","EventTagFrame",this,"Close()");
  
  fMain->AddFrame(fFbottons,
                  new TGLayoutHints(lhints ,5,5,10,0));
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  canvas->cd();
  canvas->SetBottomMargin(0.4);
  canvas->SetRightMargin(0.05);
  canvas->SetLeftMargin(0.05);  
  canvas->SetFrameLineColor(kWhite);
  canvas->SetFrameLineWidth(0);
  if(gFrameEventView->GetNEvent()){
    axis = new TH1F("axis","",5000,0,gFrameEventView->GetNEvent());
  }
  else{
    axis = new TH1F("axis","",10,0,1);
  }
  axis->GetYaxis()->SetTitleSize(0.);
  axis->GetYaxis()->SetLabelSize(0.); 
  axis->GetYaxis()->SetLabelColor(kWhite);
  axis->GetYaxis()->SetTickLength(0);
  axis->GetYaxis()->SetAxisColor(kWhite);
  axis->GetXaxis()->SetTitleSize(0.2);
  axis->GetXaxis()->SetLabelSize(0.2);
  axis->GetXaxis()->SetTickLength(0.2);
  axis->Draw();
  canvas->Update();

  canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",
		  "EventTagFrame",this,
		  "EventInfo(Int_t,Int_t,Int_t,TObject*)");

  fMain->CenterOnParent();
  fMain->SetMWMHints(kMWMDecorAll,
                     kMWMFuncAll,
                     kMWMInputModeless);
  fMain->MapSubwindows();
  fMain->Resize(fMain->GetDefaultSize());
  fMain->MapWindow();

}

void EventTagFrame::CreateTag(){
  DrawTag(gFrameEventView->GetIEvent(),
	  gFrameEventView->ev->gnumber,
	  gFrameEventView->ev->a1number,
	  gFrameEventView->ev->a2number,
	  mcolor,
	  (char*)fTextEntry->GetText());
  return ;
}

void EventTagFrame::DrawTag(int ie, int ge, int a1, int a2, 
			    int color,char* text){
  marker[nmarker] = new EventMarker();
  marker[nmarker]->SetEventNumber(ie);
  marker[nmarker]->SetGNumber(ge);
  marker[nmarker]->SetA1Number(a1);
  marker[nmarker]->SetA2Number(a2); 
  marker[nmarker]->SetMarkerColor(color);
  marker[nmarker]->SetComment(text);
  marker[nmarker]->SetVal(&marker[nmarker]);
  fTextEntry->SetText("");
  canvas->cd();
  marker[nmarker]->DrawTag();
  if(nmarker<NMARKER) nmarker++;
  canvas->Update();
  return ;
}

void EventTagFrame::DoRadio(){
  TGButton *btn = (TGButton *) gTQSender;
  Int_t id = btn->WidgetId();
  
  if(id == M_COLOR_RED)  {mcolor = kRed;}
  if(id == M_COLOR_BLUE) {mcolor = kBlue;}
  if(id == M_COLOR_GREEN){mcolor = kGreen;}

  for (int i = 0; i < 3; i++){
    if (fRColor[i]->WidgetId() != id){
      fRColor[i]->SetState(kButtonUp);
    }
    else {
      fRColor[i]->SetState(kButtonDown);
    }
  }
}


void EventTagFrame::Unzoom(){

  axis->GetXaxis()->UnZoom();
  canvas->Modified();
  canvas->Update();
//   gClient->NeedRedraw(fCanvas,kTRUE);
//   gVirtualX->Update();
  
  return ;
}

void EventTagFrame::Close(){
  fClose->Disconnect("Pressed()");
  delete this;
}

void EventTagFrame::Clear(){
  for(int i=0;i<nmarker;i++){
    delete marker[i];
    marker[i] = NULL;
  }
  nmarker = 0;
  canvas->Update();
  return ;
}

void EventTagFrame::EventInfo(Int_t event, Int_t px, Int_t py, 
			      TObject *selected){
  char text[100]="";
  EventMarker *m;
  
  if(strcmp(selected->ClassName(),"EventMarker")==0){
    m = (EventMarker*) selected;
    sprintf(text,
	    "  Event:  %6d  ( gnumber=%6d, a1number=%6d, a2number=%6d )",
	    m->GetEventNumber(),
	    m->GetGNumber(),
	    m->GetA1Number(),
	    m->GetA2Number());
    fStatusBar->SetText(text,0);
    fStatusBar->SetText(m->GetComment(),1);  
    // Press
    if(event == 1){ 
      gFrameEventView->Show(m->GetEventNumber());
      gFrameEventView->SetIEvent(m->GetEventNumber());
      //fStatusBar->SetText("Press",1);  
    }
    //cout << event << endl;
  }
  else{
    fStatusBar->SetText(text,0);
    fStatusBar->SetText(text,1);
  }
 
}

int  EventTagFrame::ReadTag(char* filename){
  ifstream fin(filename);
  if(!fin){return -1;}
  string ss;
  istringstream sin;
  int ie,ge,a1,a2,color;
  char comment[256];
  while(getline(fin,ss)){
    if(ss[0]=='#'){ continue; }
    
    sin.str(ss);
    sin >> ie >> ge >> a1 >> a2 >> color;
    ss = ss.substr(50,ss.length()-50);
    strcpy(comment,ss.c_str());
    DrawTag(ie,ge,a1,a2,color,comment);
  }
  fin.close();
  return 0;
}

int  EventTagFrame::WriteTag(char* filename){
  ofstream fout(filename);
  if(!fout){return -1;}
  
  for(int i=0;i<nmarker;i++){
    if(marker[i] == NULL){continue;}
    fout << setw(9) << marker[i]->GetEventNumber() << " "
	 << setw(9) << marker[i]->GetGNumber() << " "
	 << setw(9) << marker[i]->GetA1Number() << " "
	 << setw(9) << marker[i]->GetA2Number() << " "
	 << setw(6)  << marker[i]->GetMarkerColor() << "    ";
    if(strcmp(marker[i]->GetComment(),"")!=0){
      fout << marker[i]->GetComment() ;
    }
    else{
      fout << "-" ;
    }
    fout << endl;
  }
  fout.close(); 
  return 0;
}

#endif
