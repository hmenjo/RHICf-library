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
  libbasedir = LHCFLIBBASE;
  gInterpreter->AddIncludePath((libbasedir+"/dict/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/dict/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/dict/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/sc/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/sc/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/sc/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/lib").c_str()); 
  
  // Generic Configuration of Art works ------------------------------
  gsetup();

  // Start ROOT Interpreter ------------------------------------------ 
  theApp.Run();
} 
