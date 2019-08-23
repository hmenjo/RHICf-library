#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TInterpreter.h>
#include "LHCfEvent.h"
#include "gsetup.h"

int main(int argc, char** argv){

  TRint theApp("LHCfroot",&argc,argv,0,0,kTRUE); 
  
  // Include Path ----------------------------------------------------
  string libbasedir;
  
  libbasedir = PATHBASE;
  gInterpreter->AddIncludePath((libbasedir+"/general/dict/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/general/dict/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/general/dict/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/general/func/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/general/func/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/general/func/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/Library/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/Library/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/Library/lib").c_str());
  
  // Generic Configuration of Art works ------------------------------
  gsetup();

  // Start ROOT Interpreter ------------------------------------------ 
  theApp.Run();
} 
