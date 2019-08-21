#ifndef __MKPEDESTALFRAME_H__
#define __MKPEDESTALFRAME_H__

#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include <TGProgressBar.h>
#include <RQ_OBJECT.h>

class MkPedestalFrame {
  RQ_OBJECT("MkPedestalFrame");
 
 private:
  const TGWindow      *fParent;
  TGTransientFrame    *fMain;
  
  TGLabel             *fLabel;
  TGNumberEntry       *fNumber;
  TGHProgressBar      *fProgress1;
  TGHProgressBar      *fProgress2;

  TGTextButton        *fCalculate;
  TGTextButton        *fSave;
  TGTextButton        *fClose;
  
 public:
  MkPedestalFrame(const TGMainFrame *m);
  ~MkPedestalFrame();
  
  void MakeFrame();
  void Calculate();
  void Save();
  void Close();
};

#endif 
