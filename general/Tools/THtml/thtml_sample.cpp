{
  gROOT->Reset();

#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TText.h"

  string basedir="../../";
  string inputdir;
  inputdir  =  basedir+"/dict/:";
  inputdir  += basedir+"/dict/include:";
  inputdir  += basedir+"/dict/src:";
  inputdir  += basedir+"/func/:";
  inputdir  += basedir+"/func/include:";
  inputdir  += basedir+"/func/src:"; 
  inputdir  += basedir+"/sc/:";
  inputdir  += basedir+"/sc/include:";
  inputdir  += basedir+"/sc/src:"; 

  THtml* html = new THtml();
  html->SetProductName("LHCf Library");
  html->SetOutputDir("./htmldoc");  
  html->SetSourceDir(inputdir.c_str());
  html->SetInputDir(inputdir.c_str());
  html->MakeAll();

}
