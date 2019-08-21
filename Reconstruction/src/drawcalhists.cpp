//
// Created by MENJO Hiroaki on 2017/05/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TDiamond.h>
#include <TLegend.h>


// ---------------------------------------------------------------------
//                                  MAIN
// ---------------------------------------------------------------------
int main(int argc, char **argv) {
    
    TString inputfilename = "";
    TString outputpath    = "";
    
    for (int i = 1; i < argc; i++) {
        string ss = argv[i];
        
        if (ss == "-i" || ss == "--input") {
            inputfilename = argv[++i];
            strcpy(argv[i], "");
        }
        if (ss == "--path") {
            outputpath = argv[++i];
            strcpy(argv[i], "");
        }
    }
    
    TRint theApp("App", &argc, argv, 0, 0, kTRUE);
    
    TFile *file = new TFile(inputfilename);
    if (file->IsZombie()) {
        cerr << "Could not open " << inputfilename << endl;
        return -1;
    }
    
    file->ls();
    
    // Draw Accumulate Histogram -----------------------------------------------------------------------
    
    TCanvas *c0 = new TCanvas("c0", "Accum", 1000, 1000);
    c0->Divide(2, 2, 0.001, 0.001);
    for (int tower = 0; tower < 2; ++tower) {
        for (int pid = 0; pid < 2; ++pid) {
            c0->cd(tower + pid * 2 + 1);
            
            TH1D *h = (TH1D*) file->Get(Form("h1cal_%d_%d",tower,pid));
            h->SetXTitle("Layer");
            h->SetYTitle("Accum. dE");
            h->Draw("hist");
            if(tower==0 && pid==0) h->SetTitle("TS:Photon");
            if(tower==1 && pid==0) h->SetTitle("TL:Photon");
            if(tower==0 && pid==1) h->SetTitle("TS:Hadron");
            if(tower==1 && pid==1) h->SetTitle("TL:Hadron");
        }
    }
    c0->Update();
    c0->Print(outputpath + Form("/calaccum.gif"));
    
    theApp.Run();
    return 0;
}
