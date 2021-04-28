#ifndef __EVENTTAGFRAME_H__
#define __EVENTTAGFRAME_H__

#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TCanvas.h>
#include <TRootEmbeddedCanvas.h>
#include <TGTextEntry.h>
#include <TGStatusBar.h>
#include <RQ_OBJECT.h>
#include <TGaxis.h>
#include <TH1F.h>
#include "EventMarker.h"

class EventTagFrame {
  RQ_OBJECT("EventTagFrame");
  
 private:
  const TGWindow      *fParent;
  TGTransientFrame    *fMain;
  
  TRootEmbeddedCanvas *fCanvas;
  TCanvas             *canvas;
  TH1F                *axis;       

  TGTextButton        *fCreate;
  TGRadioButton       *fRColor[3];
  TGTextEntry         *fTextEntry;
  TGTextButton        *fUnzoom;
  TGTextButton        *fClear;  
  TGTextButton        *fClose;
  TGStatusBar         *fStatusBar;
  
  static const int     NMARKER=200;
  int                  nmarker;
  EventMarker         *marker[NMARKER];
  int                  mcolor;

  char                 configdir[256];
  
 public:
  EventTagFrame(const TGMainFrame *m);
  ~EventTagFrame();

  void MakeFrame();
  void DrawTag(int ie, int ge, int a1, int a2, 
	       int color,char* text);
  void CreateTag();
  void DoRadio();
  void Unzoom();
  void Close();
  void Clear(); 
  void EventInfo(Int_t , Int_t , Int_t , TObject* );

  int  ReadTag(char* filename);
  int  WriteTag(char* filename);

  enum EventTagWedgetID{
    M_COLOR_RED,
    M_COLOR_BLUE,
    M_COLOR_GREEN,
    NON,
  };

};

#endif
