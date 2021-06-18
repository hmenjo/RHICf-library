/**********************************************************************\
   For checking pedetal event list generated from data, which is used 
   for MC.
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
#include <A1Cal2M.h>

void printhelp() {
    cout << "Make Histograms \n"
         << endl;
    return;
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
	 if (ss == "-h" || ss == "--help") {
		printhelp();
		return -1;
	 }
  }
  
  if (inputfilename == "" || outputfilename == "" ) {
	 cerr << "give an input file name and/or an output file name." << endl;
	 printhelp();
	 return -1;
  }

  cout << "INPUT_FILE_PATH=" << inputfilename << endl;
  cout << "OUTPUT_FILE_PATH=" << outputfilename<< endl;
    
  // ++++++ INITIALIZATIONS +++++++++++++++++++
  
  TFile *ofile = new TFile(outputfilename, "recreate");
  ofile->cd();

  // Plates
  TH1D* h1_dE[2][16];
  TH1D* h1_sumdE[2];
  for(int it=0;it<2;it++){
	 for(int il=0;il<16;il++){
		h1_dE[it][il][ie] = new TH1D(Form("h1_dE_%d_%d",it,il),
											  Form("dE at t:%d l:%d",it,il),
											  100,-0.5,0.5);
	 }
	 h1_sumdE[it] = new TH1D(Form("h1_sumdE_%d",it),
									 Form("sum dE at t:%d",it),
									 100, -2.,2.);
  }

  // GSO bars
  TH1D* h1_pos[2][4][2];
  for(int it=0;it<2;it++){
	 for(int il=0;il<4;il++){
		for(int iv=0;iv<2;iv++){
		  h1_pos[it][il][iv] = new TH1D(Form("h1_pos_%s_%s_%s",it,il,iv),
												  Form("sum pos at t%d,l%d,v%d",it,il,iv),
												  100.,-1.,1.);
		}
	 }
  }
  
  
  gROOT->cd();
  

  // ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
  LHCfEvent *ev   = new LHCfEvent();
  TChain    *tree = new TChain("LHCfEvents");
  tree->Add(inputfilename.Data());
  tree->SetBranchAddress("ev.", &ev);
    
  // +++++ EVENT LOOP +++++++++++++++++++++++++++++++
  int      nevmax = tree->GetEntriesFast();
  int      nevent = 0;
  A1Cal2M   *cal2;

  cout << "Event loop start ...." << endl;
  //  == START OF EVENT LOOP ==
  for (int iev    = 0; iev < nevmax; iev++) {   
	 
	 //if(iev > 1000000) break;
    
	 Int_t ievlocal = tree->LoadTree(iev);
	 if (ievlocal < 0) break;
    
	 if (iev && iev % 10000 == 0) { cerr << '*'; } 
	 if (iev && iev % 100000 == 0) { cerr << iev << endl; }
	 ev->Delete();
	 tree->GetEntry(iev);
    
	 if (!ev->Check("a1cal2")) { continue; }
	 nevent++;
	 cal2 = (A1Cal2M *) ev->Get("a1cal2");

	 // Each plate
	 for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
		  h1_dE[it][il]->Fill(cal2->cal[it][il]);
		}
	 }
	 
	 // sumdE
	 h1_sumdE[0]->Fill(cal2->calsum(0));
	 h1_sumdE[1]->Fill(cal2->calsum(1));

	 // GSO bars
	 for(int it=0;it<2;it++){
		for(int il=0;il<4;il++){
		  for(int iv=0;iv<2;iv++){
			 double sum = 0.;
			 int size = (it==0?20:40);
			 for(int ip=0;ip<size;ip++){
				if(it==0) sum += cal2->scifi0[il][iv][ip];
				else      sum += cal2->scifi1[il][iv][ip];
			 }
			 h1_pos[it][il][iv]->Fill(sum);
		  }
		}
	 }
	 
  }
  cerr << endl;
  cout << "NEvent : " << nevent << endl;
  
  ofile->Write();
  ofile->Close();
  
  return 0;
    
}
