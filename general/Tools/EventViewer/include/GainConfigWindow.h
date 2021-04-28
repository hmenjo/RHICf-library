#ifndef __GAINCONFIGWINDOW_H__
#define __GAINCONFIGWINDOW_H__

#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <TGTextButtonMod.h>
#include <RQ_OBJECT.h>

#include <string>

class GainConfigWindow{
  RQ_OBJECT("GainConfigWindow");
  
 private:
  const TGWindow      *fParent;
  TGTransientFrame    *fMain;

  TGTextButton        *fBdefault_Op2010;
  TGTextButton        *fBdefault_Op2013;
  TGTextButton        *fBdefault_Op2015;
  TGTextButton        *fBdefault_RHICf2017;  

  TGTextEntry         *fA1Text_hv;
  TGTextEntry         *fA1Text_pdefs;
  TGTextEntry         *fA1Text_pdefscifi;
  TGTextEntry         *fA1Text_pdeffc;
  TGPictureButton     *fA1Holder_hv;
  TGPictureButton     *fA1Holder_pdefs;
  TGPictureButton     *fA1Holder_pdefscifi;
  TGPictureButton     *fA1Holder_pdeffc;

  TGTextEntry         *fA2Text_hv;
  TGTextEntry         *fA2Text_pdefs;
  TGTextEntry         *fA2Text_pdefsi;
  TGTextEntry         *fA2Text_pdeffc;
  TGPictureButton     *fA2Holder_hv;
  TGPictureButton     *fA2Holder_pdefs;
  TGPictureButton     *fA2Holder_pdefsi;
  TGPictureButton     *fA2Holder_pdeffc;

  TGTextButton        *fCancel; 
  TGTextButton        *fOK;
  
 public:
  GainConfigWindow(const TGMainFrame *m);
  ~GainConfigWindow();

  void MakeFrame();  
  void Close();
  void Ok();
  void Cancel(); 
  
  int  FileOpen(std::string &ss);
  void FileArm1HVTable();
  void FileArm1Pdefs();
  void FileArm1PdefSciFi();
  void FileArm1PdefFC();
  void FileArm2HVTable(); 
  void FileArm2Pdefs();
  void FileArm2PdefSi();
  void FileArm2PdefFC();

  void SetToDefault_Op2010();
  void SetToDefault_Op2013();
  void SetToDefault_Op2015();
  void SetToDefault_RHICf2017();
  void ParameterUpdate();
};

#endif 
