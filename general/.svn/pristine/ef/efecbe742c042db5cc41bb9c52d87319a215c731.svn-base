#ifndef __MKADAMOPEDESTALFRAME_H__
#define __MKADAMOPEDESTALFRAME_H__

#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include <TGProgressBar.h>
#include <RQ_OBJECT.h>

class MkAdamoPedestalFrame {
  RQ_OBJECT("MkAdamoPedestalFrame");
 
 private:
  const TGWindow      *fParent;
  TGTransientFrame    *fMain;
  
  TGLabel             *fLabel;
  TGNumberEntry       *fNumber;
  TGHProgressBar      *fProgress1;

  TGTextButton        *fCalculate;
  TGTextButton        *fSave;
  TGTextButton        *fClose;
  
 public:
  MkAdamoPedestalFrame(const TGMainFrame *m);
  ~MkAdamoPedestalFrame();
  
  void MakeFrame();
  void Calculate();
  void Save();
  void Close();
};

#endif 
