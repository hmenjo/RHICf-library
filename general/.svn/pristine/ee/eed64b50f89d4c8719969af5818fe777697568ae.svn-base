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
#if defined(__CINT__) && !defined(__MAKECINT__)
// load the library for interpreter mode
#include "libLHCfEvent.so"
#include "libLHCfFunction.so"
#else
#include "LHCfEvent.h"
#include "A2RawToCal1.h"
#include "A2RawToCal1Silicon.h"
#include "A2PedeSubtract.h"
#endif
#include "gsetup.h"

void sample();

#if !defined(__CINT__)
int main(int argc, char** argv){
  TRint theApp("sample",&argc,argv,0,0,kTRUE);
  sample();
  theApp.Run();
  return 0;
}
#endif

void sample(){
  
  // +++++++ OPEN DATA FILE ++++++++++++++++++++++++
  const char datafile[] = "run05000.root"; 
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile(datafile);
  tree->SetBranchAddress("ev.",&ev);
  int  nevent = tree->GetEntries();
  if(nevent>0){ cout << "FILE: " << datafile << endl; }
  else        { return ;}

  // ++++++ Initialize functions ++++++++++++++++++++ 
  // Functions for format conversions
  A2RawToCal1        *a2rawtocal1    = new A2RawToCal1();
  A2RawToCal1Silicon *a2rawtocal1si = new A2RawToCal1Silicon();
  // Functions for pedestal subtraction.
  const char pedefile[] = "pede_run05000.root";
  A2PedeSubtract *a2pedesubtract = new A2PedeSubtract();
  a2pedesubtract->ReadFile((char*)pedefile);
  
  // +++++++ EVENT LOOP +++++++++++++++++++++++++++++
  int  ievent = 0;
  A2Raw*  a2raw;
  A2Cal1* a2cal1 = new A2Cal1("a2cal1","Arm2");
  for(ievent=0;ievent<nevent;ievent++){
    if(ievent && ievent%200==0){ cerr << '*' ; }
    if(ievent && ievent%5000==0){ cerr << ievent << endl; }
    ev->Delete();           // Reflesh 
    tree->GetEntry(ievent); // Get ievent-th event.
    
    // ++++++++ EVENT SELECTIONS ++++++++++++++++++
    // search Arm2 event ("a2raw") 
    if(! ev->Check("a2raw")) continue;

    // Cut by event flags.
    //   ev->IsA2L2TAFlag() : Shower Flag
    //   ev->IsA2L2TPFlag() : Pedestal Flag
    // if(! ev->IsA2L2TAFlag() ) continue;
   
    
    // +++++++++ GET DATA OF THIS EVENT +++++++++++
    // Get data pointer for Arm2.
    a2raw = (A2Raw*)ev->Get("a2raw");
    
    // ++++++++++++ Calculate ++++++++++++++++++
    // Format conversion 
    a2rawtocal1->Convert(a2raw,a2cal1);
    a2rawtocal1si->Convert(a2raw,a2cal1);
   
    // Pedestal subtraction.
    a2pedesubtract->Subtract(a2cal1);

    // ++++++++++++++++++++++++++++++++++++
    // ++++++++++++ YOUR CODE +++++++++++++
    // ++++++++++++++++++++++++++++++++++++
    
    // The structure of silicon data is silicon[4][2][384][3].
    // [layer][xy(x:0,y:1)][strip][sample] 
    // you can access like a2cal1->silicon[0][0][100][1] .
    
  }
  cerr << endl;
  
  return ;
} 


