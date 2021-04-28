#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include "RHICfBBC.h"
#include "RHICfZDC.h"
#if defined(__CINT__)
#include "libLHCfEvent.so"
#else
#include "LHCfEvent.h"
#include "RHICfSimIncidents.h"
#endif
#include "LHCfEvent.h"
#include "RHICfSimIncidents.h"
#include "A1Cal2.h"
#include "A1Cal2M.h"

using namespace std;

void sample_eventloop(TString);

#if !defined(__CINT__)
int main(int argc, char** argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  TString tmpstring = Form("%s", argv[1]);
  sample_eventloop(tmpstring);
  //theApp.Run();
  return 0;
}
#endif

void sample_eventloop(TString tmp){
  A1Cal2M* a1sim;
  RHICfSimIncidents* a1simin;
  RHICfBBC* fBBC = new RHICfBBC("bbcsim","RHICf Trigger Event"); 
  RHICfZDC* fZDC = new RHICfZDC("zdcsim","RHICf Trigger Event"); 

  // Open the data file.
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile(tmp); 

  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("Events",&ev);

  int nevent = tree->GetEntries();
  for(int ie=0;ie<nevent;ie++){
    ev->Delete();   
    tree->GetEntry(ie);

    //    ev->Show();
    if(ev->Check("a1cal2m")!=0) {
      a1simin=((RHICfSimIncidents*)ev->Get("a1simin"));
      for(int i=0; i<a1simin->GetN(); i++) {
	cout << i << " "
	     << a1simin->Get(i)->PosX() << " "
	     << a1simin->Get(i)->PosY() << " "
	     << a1simin->Get(i)->PosZ() << " "
	     << a1simin->Get(i)->Momentum() << " "
	     << endl;
      }
    }

    if(ev->Check("zdc")!=0) {
      fZDC =((RHICfZDC*)ev->Get("zdc"));
        for (int iZDC = 0; iZDC < 3; iZDC++) 
        {
            cout <<"ZDC[" << iZDC << "]" << (fZDC->ZDCNOP)[iZDC] << endl;
        }
        // Conversion SMD response
        for (int iXY = 0; iXY < 2; iXY++) 
        {
            if (iXY==0) 
            {
                for (int j = 0; j < 7; j++) 
                {
                    cout <<"SMDH[" << j << "]" << (fZDC->SMDHdE)[j]<< endl;
                }
            }
            for (int j = 0; j < 8; j++) 
            {
                cout <<"SMDV[" << j << "]" << (fZDC->SMDVdE)[j] << endl;
            }
        }
    }
    // Conversion BBC response
    for (int iEW = 0; iEW < 2; iEW++) 
    {
        for (int iBBC = 0; iBBC < 32; iBBC++) 
        {
            cout <<"BBC[" << iEW << "][" << iBBC << "]" << (fBBC->dE)[iEW][iBBC] << endl;
        }
    }
    if(ev->Check("a1cal2")!=0) {
      a1sim=((A1Cal2M*)ev->Get("a1cal2"));
      cout << "CalSum 0: " << a1sim->calsum(0)
	   << " 1: "  << a1sim->calsum(1)
	   << endl;
    }


    cout << endl;
    cout << "RUN: " << ev->run << "   ";
    cout << endl;
    
    if(ie>40) break;
  }
}

