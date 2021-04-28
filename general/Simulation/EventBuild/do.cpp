{
  #include "TH1F.h"
  #include "TPad.h"
  #include "TGraph.h"
  gSystem->SetIncludePath(" -I../../dict/include ");
  gSystem->SetIncludePath(" -I../../dict/src ");
  gSystem->SetIncludePath(" -I../../func/include ");
  gSystem->SetIncludePath(" -I../../func/src ");  
  gSystem->Load("../../dict/lib/libLHCfEvent.so");
  
  gROOT->ProcessLine(".x eventview.cpp");
  
}
