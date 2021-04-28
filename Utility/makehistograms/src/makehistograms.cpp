/**********************************************************************\
           Making histograms from Quick Reconstruction results
                    for RHICf Operation 2017
\**********************************************************************/

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

#include <LHCfEvent.h>
// #include <A1Rec1.h>
// #include <A1Phys.h>

#include "RHICfRec0.h"
#include "RHICfRec1.h"
#include "RHICfPhys.h"

// typedef A1Rec1 A1Rec;
typedef RHICfRec1 RRec;

void printhelp() {
    cout << "Make Histograms \n"
         << endl;
    return;
}

class MakeHistograms {
public:
  static const int ntrg = 7; 
    TFile *ofile;
    TH1D  *h1_sumdE[ntrg][2][2];    // trigger mode, tower, integral range
    TH1D  *h1_spectrum[ntrg][2][2]; // trigger mode, tower, pid
    TH1D  *h1_spectrum_3sigma[ntrg][2][2]; // trigger mode, tower, pid
    TH1D  *h1_spectrum_4sigma[ntrg][2][2]; // trigger mode, tower, pid
    TH1D  *h1_spectrum_5sigma[ntrg][2][2]; // trigger mode, tower, pid
    TH1D  *h1_pid[ntrg][2][2];      // trigger mode, tower, l90/l20
    TH2D  *h2_hitmap[ntrg][2][2];   // trigger mode, tower, pid
    TH2D  *h2_hitmapall[ntrg][2];   // trigger mode, pid
    TH2D  *h2_hitmapall_photon[ntrg][5];   // trigger mode, energy
    TH2D  *h2_hitmapall_hadron[ntrg][5];   // trigger mode, energy
    TH1D  *h1_mgg[ntrg];
    TH1D  *h1_pi0spectrum[ntrg];

public:
  MakeHistograms(const char *filename);
    
  ~MakeHistograms();
    
  void Write();
  
  // int Fill(A1Phys *phys, A1Rec *rec);
    
  // int Fill(A1Phys *phys, A1Rec *rec, int trg);
    
  // int FillPi0(A1Phys *phys);
    
  // int FillPi0(A1Phys *phys, int trg);
  
  int Fill(RHICfPhys *phys, RRec *rec);
    
  int Fill(RHICfPhys *phys, RRec *rec, int trg);
    
  int FillPi0(RHICfPhys *phys);
    
  int FillPi0(RHICfPhys *phys, int trg);
};

const int MakeHistograms::ntrg;

MakeHistograms::MakeHistograms(const char *filename) {
    // Open File
    ofile = new TFile(filename, "RECREATE");
    
    for (int trg = 0; trg < ntrg; ++trg) {
        for (int pid = 0; pid < 2; ++pid) {
            for (int tower         = 0; tower < 2; ++tower) {
	      //h1_spectrum[trg][tower][pid] = new TH1D(Form("h1_spectrum_%d_%d_%d", trg, tower, pid), "Spectrum",100, 0., 500.);
	      h1_spectrum[trg][tower][pid] = new TH1D(Form("h1_spectrum_%d_%d_%d", trg, tower, pid), "Spectrum",400, 0., 2000.);
                h1_pid[trg][tower][pid]      = new TH1D(Form("h1_pid_%d_%d_%d", trg, tower, pid), "L90%/L20%",
                                                        100, 0., 50.);
                h2_hitmap[trg][tower][pid]   = new TH2D(Form("h2_hitmap_%d_%d_%d", trg, tower, pid), "Hitmap",
                                                        (tower == 0 ? 40 : 80), 0., (tower == 0 ? 20. : 40.),
                                                        (tower == 0 ? 40 : 80), 0., (tower == 0 ? 20. : 40.));
            }
            h2_hitmapall[trg][pid] = new TH2D(Form("h2_hitmapall_%d_%d", trg, pid), "Hitmap all",
                                              100, -50., 50., 100, -20., 80.);
        }
        
        // For sum dE
        for (int tower = 0; tower < 2; ++tower) {
            for (int range = 0; range < 2; ++range) {
                h1_sumdE[trg][tower][range] = new TH1D(Form("h1_sumdE_%d_%d_%d", trg, tower, range), "Sum dE",
                                                       500, -1., 9.);
            }
        }
        
        
        // For type1-pi0
        h1_mgg[trg]         = new TH1D(Form("h1_mgg_%d", trg),
                                       "Mgg", 300, 0, 300);
        h1_pi0spectrum[trg] = new TH1D(Form("h1_pi0spectrum_%d", trg),
                                       "Pi0 Spectrum", 26, 0, 260);
    
	for(int enth=0;enth<5;enth++){
	 h2_hitmapall_photon[trg][enth] = new TH2D(Form("h2_hitmapall_photon_%d_%d", trg, enth), 
						    "Hitmap all",
						   100, -50., 50., 100, -20., 80.);
	 h2_hitmapall_hadron[trg][enth] = new TH2D(Form("h2_hitmapall_hadron_%d_%d", trg, enth), 
						   "Hitmap all",
						    100, -50., 50., 100, -20., 80.);
	}
    }
    gROOT->cd();
    return;
}

MakeHistograms::~MakeHistograms() {
    ofile->Close();
}

void MakeHistograms::Write() {
    ofile->cd();
    ofile->Write();
    gROOT->cd();
}

//int MakeHistograms::Fill(A1Phys *phys, A1Rec *rec) {
int MakeHistograms::Fill(RHICfPhys *phys, RRec *rec) {
  
  Fill(phys, rec, 0); // All
  if ((phys->flag[0] & 0x010)) { Fill(phys, rec, 1); } // Shower Trigger
  if ((phys->flag[0] & 0x080)) { Fill(phys, rec, 2); } // Special1 Trigger
  if ((phys->flag[0] & 0x200)) { Fill(phys, rec, 3); } // Special2 Trigger
  if ((phys->flag[0] & 0x020)) { Fill(phys, rec, 4); } // Pedestal Trigger (Zero bias trigger )
  if ((phys->flag[0] & 0x010) && (phys->flag[0] & 0x080)) { Fill(phys, rec, 5); } // Shower Trigger & Special1 Trigger
  if ((phys->flag[0] & 0x010) && ((phys->flag[1] & 0x8) || (phys->flag[1] & 0x80000))) { Fill(phys, rec, 6); } // Shower Trigger & Special1 Trigger
    return 0;
}

//int MakeHistograms::Fill(A1Phys *phys, A1Rec *rec, int trg) {
int MakeHistograms::Fill(RHICfPhys *phys, RRec *rec, int trg) {
    int      nfill = 0;
    int n_all=0;
    double energy1[2]={0};
    double energy2[2]={0};
    double energy3[2]={0};
    double energy4[2]={0};
    for (int tower = 0; tower < 2; ++tower) {
        // Fill to Sum dE
        h1_sumdE[trg][tower][0]->Fill(rec->GetSumdE(tower));
        h1_sumdE[trg][tower][1]->Fill(rec->GetSumdE2(tower));
        energy1[tower] = phys->Energy(tower);
        // Check Hit Detection
        if (phys->Hits(tower) == 0) continue;
	energy2[tower] = phys->Energy(tower);
        // Check Hit Poistion in Fiducial.
        if (!phys->InFiducial(tower)) continue;
        energy3[tower] = phys->Energy(tower);
        int    pid             = -1;
        double energythreshold = 10.;
        if (phys->IsElemag(tower)) {
            pid             = 0;
            energythreshold = 10.;
        }
        if (phys->IsHadron(tower)) {
            pid             = 1;
            energythreshold = 200.;
        }
        
        h1_pid[trg][tower][0]->Fill(rec->GetL90(tower));
        h1_pid[trg][tower][1]->Fill(rec->GetL20(tower));
        
        if (pid < 0) continue;
	energy4[tower] = phys->Energy(tower);
	//----true energy histogram
	if(trg == 1){
	  if(tower == 0 && phys->flag[0] & 0x0400){ 
	    h1_spectrum[trg][0][pid]->Fill(phys->Energy(0));
	  }
	  if(tower == 1 && phys->flag[0] & 0x0800){ 
	    h1_spectrum[trg][1][pid]->Fill(phys->Energy(1));
	  }
	}	

	else if(trg == 3){
	  if(tower == 0 && phys->flag[1] & 0x08) h1_spectrum[trg][0][pid]->Fill(phys->Energy(0));
	  if(tower == 1 && phys->flag[1] & 0x080000) h1_spectrum[trg][1][pid]->Fill(phys->Energy(1));
	}
	else if(trg == 0 || trg ==2 || trg == 4 || trg == 5 || trg == 6){
	  h1_spectrum[trg][tower][pid]->Fill(phys->Energy(tower));
	}
	
	
        if (phys->Energy(tower) > energythreshold) {
            h2_hitmap[trg][tower][pid]->Fill(phys->X(tower), phys->Y(tower));
            h2_hitmapall[trg][pid]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
        }
	

	if (pid==0){
	  if(phys->Energy(tower) > 10.) 
	    h2_hitmapall_photon[trg][0]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 50.) 
	    h2_hitmapall_photon[trg][1]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 100.) 
	    h2_hitmapall_photon[trg][2]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 150.) 
	    h2_hitmapall_photon[trg][3]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
  	  if(phys->Energy(tower) > 200.) 
	    h2_hitmapall_photon[trg][4]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));  

	}
	if (pid==1){
	  if(phys->Energy(tower) > 10.) 
	    h2_hitmapall_hadron[trg][0]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 50.) 
	    h2_hitmapall_hadron[trg][1]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 100.) 
	    h2_hitmapall_hadron[trg][2]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
	  if(phys->Energy(tower) > 200.) 
	    h2_hitmapall_hadron[trg][3]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));
  	  if(phys->Energy(tower) > 300.) 
	    h2_hitmapall_hadron[trg][4]->Fill(phys->GPosX_Detector(tower), phys->GPosY_Detector(tower));   
	}
	
        ++nfill;
	//if(tower == 0 && trg == 0 && 270 < phys->Energy(tower) ){
	//cout << tower << " " << energy1[tower] << " " << energy2[tower] << " " << energy3[tower] << " " << energy4[tower] << endl;
	//}    
    }
    
    return nfill;
}


//int MakeHistograms::FillPi0(A1Phys *phys) {
int MakeHistograms::FillPi0(RHICfPhys *phys) {
    FillPi0(phys, 0); // All
    if (phys->flag[0] & 0x010) { FillPi0(phys, 1); } // Shower Trigger
    if (phys->flag[0] & 0x080) { FillPi0(phys, 2); } // Special1 Trigger
    if (phys->flag[0] & 0x200) { FillPi0(phys, 3); } // Special2 Trigger
    if (phys->flag[0] & 0x020) { FillPi0(phys, 4); } // Pedestal Trigger (Zero bias trigger )
    if ((phys->flag[0] & 0x010) && (phys->flag[0] & 0x080)) { FillPi0(phys, 5); } // Shower Trigger & Special1 Trigger
    if ((phys->flag[0] & 0x010) && (phys->flag[0] & 0x200)) { FillPi0(phys, 6); } // Shower Trigger & Special1 Trigger
    return 0;
}

//int MakeHistograms::FillPi0(A1Phys *phys, int trg) {
int MakeHistograms::FillPi0(RHICfPhys *phys, int trg) {
    static const double cDistance    = 18000.; // ?? [mm]
    static const double cMassRange[] = {120., 150.};
    
    // Select Photon Pair Events
    if (!(phys->Hits(0) == 1 && phys->IsElemag(0) && phys->InFiducial(0))) return 0;
    if (!(phys->Hits(1) == 1 && phys->IsElemag(1) && phys->InFiducial(1))) return 0;
    
    double r2        = TMath::Power(phys->GPosX_Detector(0) - phys->GPosX_Detector(1), 2)
                       + TMath::Power(phys->GPosY_Detector(0) - phys->GPosY_Detector(1), 2);
    double energy_ts = phys->Energy(0);
    double energy_tl = phys->Energy(1);
    double mass      = TMath::Sqrt(energy_ts * energy_tl * r2) / cDistance * 1000.;
    double pi0energy = energy_ts + energy_tl;
    
    h1_mgg[trg]->Fill(mass);
    if (mass > cMassRange[0] && mass < cMassRange[1]) {
        h1_pi0spectrum[trg]->Fill(pi0energy);
    }
    return 1;
}


// ---------------------------------------------------------------------
//                                  MAIN
// ---------------------------------------------------------------------
int main(int argc, char **argv) {
    
    TString inputfilename  = "";
    TString outputfilename = "";
    
    for (int i = 1; i < argc; i++) {
        string ss = argv[i];
        
        if (ss == "-i" || ss == "--input") {
            inputfilename = argv[++i];
            strcpy(argv[i], "");
        }
        if (ss == "-o" || ss == "--output") {
            outputfilename = argv[++i];
            strcpy(argv[i], "");
        }
    }
    
    if (inputfilename == "" || outputfilename == "") {
        cerr << "give an input file name and/or an output file name." << endl;
        printhelp();
        return -1;
    }
    
    // ++++++ INITIALIZATIONS +++++++++++++++++++
    TRint theApp("App", &argc, argv, 0, 0, kTRUE);
    
    // ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
    LHCfEvent *ev   = new LHCfEvent();
    TChain    *tree = new TChain("LHCfEvents");
    tree->AddFile(inputfilename.Data());
    tree->SetBranchAddress("ev.", &ev);
    
    //+++++ OPEN OUTPUT FILE +++++++++++++++++++++++++
    
    MakeHistograms *hists = new MakeHistograms(outputfilename.Data());
    
    
    // +++++ EVENT LOOP ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    int      nevmax = tree->GetEntriesFast();
    int      nevent = 0;
    //A1Phys   *phys  = new A1Phys();
    RHICfPhys *phys = new RHICfPhys();
    
    //  == START OF EVENT LOOP ==
    for (int iev    = 0; iev < nevmax; iev++) {
      
      Int_t ievlocal = tree->LoadTree(iev);
      if (ievlocal < 0) break;
        
      if (iev && iev % 1000 == 0) { cerr << '*'; } 
      if (iev && iev % 20000 == 0) { cerr << iev << endl; }
      ev->Delete();
      tree->GetEntry(iev);
        
      if (!ev->Check("a1rec")) { continue; }
      nevent++;
      
      //A1Rec *rec = (A1Rec *) ev->Get("a1rec");
      RRec *rec = (RRec *) ev->Get("a1rec");
      rec->FillToPhys(phys);
      
      //for(int trg =0; trg < 7; trg++){
      hists->Fill(phys, rec);
      //}
      hists->FillPi0(phys);
      
    }
    cerr << endl;
    
    hists->Write();
    
    theApp.Run();
    
    return 0;
    
}
