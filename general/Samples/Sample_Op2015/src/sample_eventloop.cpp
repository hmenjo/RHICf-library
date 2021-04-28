#include <iostream>
#include <iomanip>
#include <limits.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <fstream>

using namespace std;

#include <TROOT.h>
#include <TRint.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>

#include "LHCfEvent.h"
#include "RHICfRaw_Op2017.h"
#include "A1Raw_pp2015.h"
#include "A2Raw_pp2015.h"
#include "A1Scl_pp2015.h"
#include "A2Scl_pp2015.h"
#include "A1RawToCal1.h"
#include "A2RawToCal1.h"
#include "A1Cal1AccumHist.h"
#include "A2Cal1AccumHist.h"
#include "A1PedeSubtract.h"
#include "A2PedeSubtract.h"
#include "A2RawToCal1Silicon.h"
#include "LHCfRunInfoTable.h"
#include "TLHCFDIPDATAH.h"
#include "TLHCFDIPDATAL.h"

void printhelp(){
  cout << "sample_eventloop [run number]" << endl;
}

int main(int argc, char** argv){  

  // ++++++++ Manage optioons +++++++++++++++++++++++++++++
  char number[256] = "";
  char filename[256] = "";
  char outname[256] = "";

  strcpy(number, argv[1]);
  int runnum = atoi(number);
  cout << runnum << endl;

  sprintf(filename, "/data1/DATA1/test/root_files/run%08d.root", runnum);
  sprintf(outname, "./result/run%d.root", runnum);

  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      printhelp();
      return 0;
    }
  }
  
  if(argc>2){
    printhelp();
    return -1;
  }

  if(number==""){
    printhelp();
    return -1;
  }
  
  //TApplication app("adchists",&argc,argv);
  TRint app("adchists_arm1",&argc,argv,0,0,kTRUE);  
    
  // ++++++ OPEN INPUT FILES +++++++++++++++++++++++++++++++++++++
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  tree -> Add(filename);
  tree->SetBranchAddress("ev.",&ev);
  int nevent = tree->GetEntries();

  // ++++++ OPEN OUTPUT FILES +++++++++++++++++++++++++++++++++++++
  TFile* outfile = new TFile(outname, "RECREATE");

  // +++++ INITIALIZE VALUABLES AND FUNCTIONS ++++++++++++++++++ 
  RHICfRaw_Op2017* a1raw = new RHICfRaw_Op2017();
  A1Cal1             *a1cal1 = new A1Cal1();
  A1RawToCal1        *a1conv = new A1RawToCal1();
  a1conv->ReadScifiPosTable("../../../tables/GSObar_map9.tab");

  /*A2Cal1             *a2cal1 = new A2Cal1();
  A2RawToCal1        *a2conv = new A2RawToCal1();
  A2RawToCal1Silicon *a2rawtocal1si = new A2RawToCal1Silicon();

  A1Scl_pp2015* a1scllast = new A1Scl_pp2015();
  A2Scl_pp2015* a2scllast = new A2Scl_pp2015();*/  

  const int platescl = 3000;
  const int pdiffscl = 500;
  const int barscl = 100000;
  const int bpedscl = 20000;
  TH1D* Plate[2][16][2];// [tower][plate][range]; [i][j][0]: Large dynamic range
  TH1D* PlateD[2][16][2];
  TH1D* PlateDiff[2][16][2];
  for(int i=0;i<2;i++){
    for(int j=0;j<16;j++){
      for(int k=0;k<2;k++){
	Plate[i][j][k] = new TH1D(Form("Plate_%d_%d_%d", i, j, k), "", 
				  pdiffscl+platescl, -pdiffscl, platescl);
	Plate[i][j][k] -> SetLineColor(1);
	PlateD[i][j][k] = new TH1D(Form("PlateD_%d_%d_%d", i, j, k), "", 
				   pdiffscl+platescl, -pdiffscl, platescl);
	PlateD[i][j][k] -> SetLineColor(1);
	PlateD[i][j][k] -> SetLineStyle(2);
	PlateDiff[i][j][k] = new TH1D(Form("PlateDiff_%d_%d_%d", i, j, k), "", 
				      pdiffscl+platescl, -pdiffscl, platescl);
	PlateDiff[i][j][k] -> SetLineColor(2);
      }
    }
  }
  TH1D* Bar0[4][2][20];
  TH1D* Bar1[4][2][40];
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      for(int k=0;k<20;k++){
	Bar0[i][j][k] = new TH1D(Form("Bar0_%d_%d_%d", i, j, k), "", 
				 barscl-bpedscl, bpedscl, barscl);
      }
      for(int k=0;k<40;k++){
	Bar1[i][j][k] = new TH1D(Form("Bar1_%d_%d_%d", i, j, k), "", 
				 barscl-bpedscl, bpedscl, barscl);
      }
    }
  }
    
  cout << nevent << "entries" << endl;
  int fstep = 0;
  // +++++ EVNET LOOP +++++++++++++++++++++++++++++++++++++++++
  for(int ievent=0;ievent<nevent;ievent++){
    for(int fper=0;fper<100;fper++){
      if((int)(TMath::Nint(((double)ievent/(double)nevent)*100)==fper) && (fstep==fper)){
	cout << fper << " %" << endl;
	fstep++;
      }
    }
    ev->Delete();
    tree->GetEntry(ievent);

    //  == For Arm1 data == 
    if(ev->Check("a1raw")){
      //cout << a1raw->adc0[0] << ", " << a1raw->adc0[1] << ", " << a1raw->adc0[2] << ", " << a1raw->adc0[3] << endl;

      a1raw = (RHICfRaw_Op2017*) ev -> Get("a1raw");
      a1conv -> Convert(a1raw, a1cal1);
      
      //cout << a1cal1->cal[0][0][1] << ", " << a1cal1->cal[0][0][0] << ", " << a1cal1->cal[0][1][1] << ", " << a1cal1->cal[0][1][0] << endl;

      for(int i=0;i<2;i++){
	for(int j=0;j<16;j++){
	  for(int k=0;k<2;k++){
	    Plate[i][j][k] -> Fill(a1cal1->cal[i][j][k]);
	    PlateD[i][j][k] -> Fill(a1cal1->cald[i][j][k]);
	    PlateDiff[i][j][k] -> Fill(a1cal1->cal[i][j][k]-a1cal1->cald[i][j][k]);
	  }
	}
      }
      for(int i=0;i<4;i++){
	for(int j=0;j<2;j++){
	  for(int k=0;k<20;k++){
	    Bar0[i][j][k] -> Fill(a1cal1->scifi0[i][j][k]);
	  }
	  for(int k=0;k<40;k++){
	    Bar1[i][j][k] -> Fill(a1cal1->scifi1[i][j][k]);
	  }
	}
      }
      //a1conv->Convert(ev->Get("a1raw"),a1cal1);
    }

  } // End of event loop ========================

  



  TCanvas* PlateCanv[2][2];
  for(int i=0;i<2;i++){
    for(int k=0;k<2;k++){
      PlateCanv[i][k] = new TCanvas(Form("PlateCanv_%d_%d", i, k), "", 1600, 1000);
      PlateCanv[i][k] -> Divide(4, 4);
      for(int j=0;j<16;j++){
	PlateCanv[i][k] -> cd(j+1);
	gPad -> SetLogy();
	gStyle -> SetStatW(0.3);
	gStyle -> SetStatH(0.3);
	Plate[i][j][k] -> Draw();
	PlateD[i][j][k] -> Write();
	PlateD[i][j][k] -> Draw("same");
	Plate[i][j][k] -> Write();
	PlateDiff[i][j][k] -> Draw("same");
	PlateDiff[i][j][k] -> Write();
      }
      PlateCanv[i][k] -> Write();
    }
  }
  for(int i=0;i<2;i++){
    for(int k=0;k<2;k++){
      cout << Form("Plate_%d_%d", i, k) << setw(8);
      for(int j=0;j<16;j++){
	cout << TMath::Nint(Plate[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(17);
      for(int j=0;j<16;j++){
	cout << setprecision(3) << Plate[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
      cout << setw(8);
    }
  }
  cout<< "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  for(int i=0;i<2;i++){
    for(int k=0;k<2;k++){
      cout << Form("PlateD_%d_%d", i, k) << setw(7);
      for(int j=0;j<16;j++){
        cout << TMath::Nint(PlateD[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(17);
      for(int j=0;j<16;j++){
        cout << setprecision(3) << PlateD[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
      cout << setw(8);
    }
  }
  cout<< "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  for(int i=0;i<2;i++){
    for(int k=0;k<2;k++){
      cout << Form("Diffr_%d_%d", i, k) << setw(8);
      for(int j=0;j<16;j++){
        cout << TMath::Nint(PlateDiff[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(17);
      for(int j=0;j<16;j++){
        cout << setprecision(3) << PlateDiff[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
      cout << setw(8);
    }
  }
  cout<< "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      cout << Form("Bar0_%d_%d", i, j) << setw(8);
      for(int k=0;k<20;k++){
	cout << TMath::Nint(Bar0[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(16);
      for(int k=0;k<20;k++){
	cout << setprecision(3) << Bar0[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
      cout << setw(8);
    }
  }
  cout<< "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      cout << Form("Bar0_%d_%d", i, j) << setw(8);
      for(int k=0;k<20;k++){
        cout << TMath::Nint(Bar1[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(16);
      for(int k=0;k<20;k++){
        cout << setprecision(3) << Bar1[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
      cout << setw(16);
      for(int k=20;k<40;k++){
        cout << TMath::Nint(Bar1[i][j][k]->GetMean()) << setw(8);
      }
      cout << endl;
      cout << setw(16);
      for(int k=20;k<40;k++){
        cout << setprecision(3) << Bar1[i][j][k]->GetRMS() << setw(8);
      }
      cout << endl;
    }
  }

  outfile -> Close();

  cerr << endl;
  
  app.Run();
  return 0;  
}
