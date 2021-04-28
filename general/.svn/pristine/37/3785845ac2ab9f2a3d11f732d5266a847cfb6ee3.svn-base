#ifndef __TGTEXTBUTTONMOD__
#define __TGTEXTBUTTONMOD__

#include <iostream>
#include <iomanip>
#include <RQ_OBJECT.h>
#include <TGButton.h>
using namespace std;

class TGTextButtonMod : public TGTextButton {
public:
  TGTextButtonMod(const TGWindow* p,
		  const char* s,
		  Int_t id = -1, 
		  GContext_t norm = GetDefaultGC()(), 
		  FontStruct_t font = GetDefaultFontStruct(),
		  UInt_t option = kRaisedFrame|kDoubleBorder);
  TGTextButtonMod(){;}
  ~TGTextButtonMod(){;}
  
  bool     stat;
  void     Change();
  void     ChangeOn(){SetStat(true);}
  void     ChangeOff(){SetStat(false);} 
  void     ChangedOn();    //*SIGNAL*
  void     ChangedOff();   //*SIGNAL*
  void     Modified();     //*SIGNAL*
  void     SetStat(bool k);
  bool     GetStat(){return stat;}
  
  ClassDef(TGTextButtonMod,1);
};

#endif

