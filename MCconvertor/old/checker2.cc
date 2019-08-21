#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TH1F.h>
#include <TFile.h>
#include "RHICfBBC.h"
#include "RHICfZDC.h"
#if defined(__CINT__)
#include "libLHCfEvent.so"
#else
#include "LHCfEvent.h"
#include "RHICfSimIncidents.h"
#include "ParticlesInfo.h"
#endif
#include "LHCfEvent.h"
#include "RHICfSimIncidents.h"
#include "A1Cal2.h"
#include "A1Cal2M.h"
#include "RHICfFC.h"

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
  A1Cal2* a1cal;
  RHICfBBC* fBBC = new RHICfBBC("bbcsim","RHICf Trigger Event"); 
  RHICfZDC* fZDC = new RHICfZDC("zdcsim","RHICf Trigger Event"); 
  RHICfFC   *fFC = new RHICfFC("fcsim", "fc");
  ParticlesInfo *fParticles = new ParticlesInfo("particles", "Simulation particle info");

  // Open the data file.
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile(tmp); 

  LHCfEvent *ev = new LHCfEvent();
  tree->SetBranchAddress("Events",&ev);

  int nevent = tree->GetEntries();
  tree->Print();
  cout << "Entries: " << nevent << endl;
  for(int ie=0;ie<nevent;ie++){
    tree->GetEntry(ie);


        //Junsang****ev->Show();

    //Junsang****if(ev->Check("zdc")!=0) {
      //Junsang****fZDC =((RHICfZDC*)ev->Get("zdc"));
        //Junsang****for (int iZDC = 0; iZDC < 3; iZDC++) 
        //Junsang****{
            //Junsang****cout <<"ZDC[" << iZDC << "]" << (fZDC->ZDCNOP)[iZDC] << endl;
        //Junsang****}
        //Junsang****// Conversion SMD response
        //Junsang****for (int iXY = 0; iXY < 2; iXY++) 
        //Junsang****{
            //Junsang****if (iXY==0) 
            //Junsang****{
                //Junsang****for (int j = 0; j < 7; j++) 
                //Junsang****{
                    //Junsang****cout <<"SMDH[" << j << "]" << (fZDC->SMDHdE)[j]<< endl;
                //Junsang****}
            //Junsang****}
            //Junsang****for (int j = 0; j < 8; j++) 
            //Junsang****{
                //Junsang****cout <<"SMDV[" << j << "]" << (fZDC->SMDVdE)[j] << endl;
            //Junsang****}
        //Junsang****}
    //Junsang****}
    //Junsang****// Conversion BBC response
    //Junsang****for (int iEW = 0; iEW < 2; iEW++) 
    //Junsang****{
        //Junsang****for (int iBBC = 0; iBBC < 32; iBBC++) 
        //Junsang****{
            //Junsang****cout <<"BBC[" << iEW << "][" << iBBC << "]" << (fBBC->dE)[iEW][iBBC] << endl;
        //Junsang****}
    //Junsang****}
    //
    if(ev->Check("particles")!=0) 
    {
        Int_t tmpi;
        fParticles = ((ParticlesInfo*)ev->Get("particles"));
        cout << (fParticles -> GetRunNumber()) << " : " <<(fParticles -> GetEventNumber()) << endl;
        cout << "WPlate:" << (fParticles -> GetWPlate())->GetEntries() << endl;
        if(tmpi = (fParticles -> GetWPlate())->GetEntries()) 
        {
            
            for (int i = 0; i < tmpi; i++) 
            {
                
                cout << fParticles->GetPFromWPlate(i)->GetName() << endl;;
                fParticles->GetPFromWPlate(i)->Get4Momentum().Print();
                
            }
        }
        //Junsang****fParticles->GetPFromIP(0)->Get4Momentum().Print();
        cout << "ZDCGhost:" << (fParticles -> GetZDCGhost())->GetEntries() << endl;
        if(tmpi = (fParticles -> GetZDCGhost())->GetEntries()) 
        {
            
            for (int i = 0; i < tmpi; i++) 
            {
                
                cout << fParticles->GetPFromZDCGhost(i)->GetName() << endl;;
                fParticles->GetPFromZDCGhost(i)->Get4Momentum().Print();
                
            }
        }
        cout << "IP:" << (fParticles -> GetIP())->GetEntries() << endl;
        cout << "Circle:" << (fParticles -> GetCircle())->GetEntries() << endl;
        cout << "Ghost:" << (fParticles -> GetGhost())->GetEntries() << endl;
        cout << "NGhost:" << (fParticles -> GetNGhost())->GetEntries() << endl;
        cout << "P0Ghost:" << (fParticles -> GetP0Ghost())->GetEntries() << endl;
        cout << "NSignal:" << (fParticles -> GetNSignal())->GetEntries() << endl;
        cout << "P0Signal:" << (fParticles -> GetP0Signal())->GetEntries() << endl;

  }
        //Junsang****//Junsang****if((fParticles->GetPFromWPlate(0)))
        //Junsang****//Junsang****{
        //Junsang****//Junsang****cout << "WPlate: " << (fParticles -> GetPFromWPlate(0))->GetName() << endl;
        //Junsang****//Junsang****cout << (fParticles -> GetPFromWPlate(0))->GetName() << endl;
        //Junsang****//Junsang****((fParticles -> GetPFromWPlate(0))->Get4Momentum()).Print();
        //Junsang****//Junsang****}
//Junsang****
//Junsang****
      //Junsang****//Junsang****for (int i = 0; i < 2; i++) 
      //Junsang****//Junsang****{
          //Junsang****//Junsang****for (int j = 0; j < 16; j++) 
          //Junsang****//Junsang****{
              //Junsang****//Junsang****cout << (a1cal->cal)[i][j] << endl;
              //Junsang****//Junsang****
          //Junsang****//Junsang****}
      //Junsang****//Junsang****}
    //Junsang****}

    if(ev->Check("a1cal2")!=0) {
      a1cal=((A1Cal2*)ev->Get("a1cal2"));

      //Junsang****for (int i = 0; i < 2; i++) 
      //Junsang****{
          //Junsang****for (int j = 0; j < 16; j++) 
          //Junsang****{
              //Junsang****cout << (a1cal->cal)[i][j] << endl;
              //Junsang****
          //Junsang****}
      //Junsang****}
      cout << "CalSum 0: " << a1cal->calsum2(0)
	   << " 1: "  << a1cal->calsum2(1)
	   << endl;
    }

    if(ev->Check("fc")!=0) {
      fFC=((RHICfFC*)ev->Get("fc"));

      //Junsang****for (int i = 0; i < 2; i++) 
      //Junsang****{
          //Junsang****for (int j = 0; j < 16; j++) 
          //Junsang****{
              //Junsang****cout << (a1cal->cal)[i][j] << endl;
              //Junsang****
          //Junsang****}
      //Junsang****}
      cout << "FC: " << fFC-> FCdE[0] << ":" << fFC->FCdE[1] << endl;
    }
    if(ev->Check("zdc")!=0) {
      fZDC=((RHICfZDC*)ev->Get("zdc"));

      //Junsang****for (int i = 0; i < 2; i++) 
      //Junsang****{
          //Junsang****for (int j = 0; j < 16; j++) 
          //Junsang****{
              //Junsang****cout << (a1cal->cal)[i][j] << endl;
              //Junsang****
          //Junsang****}
      //Junsang****}
      cout << "ZDC: " << fZDC-> ZDCdE[0] << ":" << fZDC->ZDCdE[1] << endl;
    }
    
    //Junsang****if(ie>40) break;


    ev->Delete();   
}
}

