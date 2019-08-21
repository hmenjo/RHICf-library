#ifndef __TGTEXTBUTTONMOD_CPP__
#define __TGTEXTBUTTONMOD_CPP__

#include <iostream>
#include <iomanip>
#include "TGTextButtonMod.h"
using namespace std;

#if !defined(__CINT__)
  ClassImp(TGTextButtonMod); 
#endif

TGTextButtonMod::TGTextButtonMod(const TGWindow* p,
				 const char* s,
				 Int_t id , 
				 GContext_t norm, 
				 FontStruct_t font,
				 UInt_t option)
  : TGTextButton(p,s,id,norm,font,option)
{
  stat = false;
  SetOn(stat);
  Connect("Clicked()","TGTextButtonMod",this,"Change()");
}

void TGTextButtonMod::Change(){
  if(stat){
    SetOn(false);
    stat = false;
    ChangedOff();
  }
  else{
    SetOn(true);
    stat = true;
    ChangedOn();
  }
}

void TGTextButtonMod::ChangedOn(){Emit("ChangedOn()");Modified();}

void TGTextButtonMod::ChangedOff(){Emit("ChangedOff()");Modified();}

void TGTextButtonMod::Modified(){Emit("Modified()");}

void TGTextButtonMod::SetStat(bool k){
  if(stat!=k){
    stat = k;
    SetOn(stat);
    if(k==true) ChangedOn();
    else        ChangedOff();
  }
}

#endif

