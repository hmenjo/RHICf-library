#ifndef __ADAMOFRAME_H__
#define __ADAMOFRAME_H__

#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TGMenu.h>
#include <RQ_OBJECT.h>

#include "TGTextButtonMod.h"
#include "SPSAdamo.h"
#include "SPSAdamoHist.h"
#include "SPSAdamoPedeSubtract.h"

class AdamoFrame {
  RQ_OBJECT("AdamoFrame");
  
 private:
  const TGWindow        *fParent;
  
  TGMainFrame           *fMain;
  //TGCompositionFrame    *fMain;
  
  TRootEmbeddedCanvas   *fCanvas;
  TGTextButton          *fClose;
  TGTextButton          *fSave; 
  TGCheckButton         *fSelection;
  TGTextButtonMod       *fPede;
  TGTextButton          *fOpenPede;    
  TGTextButton          *fMkPede;  

 public:
  TCanvas               *canvas;
  SPSAdamo              *data;
  SPSAdamoHist          *hist;
  SPSAdamoPedeSubtract  *pedesubtract;
  bool                   chk_pedesub;
  bool                   chk_allstrip;
  
 public:
  AdamoFrame(const TGMainFrame *m);
  ~AdamoFrame();
  
  void MakeFrame();
  void Close();          
  void FillEvent(SPSAdamo *d);
  void Update();
  void SaveAs();
  void SetPedeSubtraction();
  void SetFillAllStrip();
  void MakePedestal();
  void OpenPedestal();
};

extern AdamoFrame* gAdamoFrame;     // global pointe

#endif
