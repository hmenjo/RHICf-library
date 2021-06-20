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
#include <A1PedeSubtract.h>

void printhelp() {
    cout << "Make Histograms \n"
         << endl;
    return;
}

// ----------------------------
class Histogram {
public:
  
  // Plates
  TH1D* h1_adc[2][16];
  TH1D* h1_dE[2][16];
  TH1D* h1_sumdE[2];
  // GSO bars
  TH1D* h1_pos[2][4][2];
public:
  Histogram(const char tag[]);
  void Fill(A1Cal1 *cal1, A1Cal2M *cal2);
  
};

Histogram::Histogram(const char tag[]){
	 for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
		  h1_adc[it][il] = new TH1D(Form("h1_adc_%d_%d_%s",it,il,tag),
											 Form("ADC at t:%d l:%d",it,il),
											 1000,500.-0.5,1500.-0.5);
		  h1_dE[it][il] = new TH1D(Form("h1_dE_%d_%d_%s",it,il,tag),
											Form("dE at t:%d l:%d",it,il),
											600,-0.01,0.05);
		}
		h1_sumdE[it] = new TH1D(Form("h1_sumdE_%d_%s",it,tag),
										Form("sum dE at t:%d",it),
										600, -0.1,0.5);
	 }


	 for(int it=0;it<2;it++){
		for(int il=0;il<4;il++){
		  for(int iv=0;iv<2;iv++){
			 h1_pos[it][il][iv] = new TH1D(Form("h1_pos_%d_%d_%d_%s",it,il,iv,tag),
													 Form("sum pos at t%d,l%d,v%d",it,il,iv),
													 600.,-0.1,0.5);
		  }
		}
	 }
	 
	 return ;
}

void Histogram::Fill(A1Cal1 *cal1, A1Cal2M *cal2){
  
	 // Each plate
	 for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
		  h1_adc[it][il]->Fill(cal1->cal[it][il][0]);
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
	 
	 return ;
}

// -----------------------

bool EventSelection(A1Cal2M* cal2){

  // Selection by Disciminator flag
  if (cal2->flag[1] != 0) return false;

  // Selection by Sum dE
  // Before it, please confirm the mean value is correctly about 0 GeV.
  // The criterion 0.05 corresponds to ~ 4 sigma of Std.dev.  
  if ( TMath::Abs( cal2->calsum(0) ) > 0.05  ) return false;
  if ( TMath::Abs( cal2->calsum(1) ) > 0.05  ) return false;

  // Selection by GSO bar dE
  // There are many events with negative sum especially in layer 0,1
  // These are due to overshoot of MAPMT pulse
  // The criterion will cut some of these events. 
  int check = 0;
  for(int it=0;it<2;it++){
	 for(int il=0;il<4;il++){
		for(int iv=0;iv<2;iv++){
		  double sum = 0.;
		  int size = (it==0?20:40);
		  for(int ip=0;ip<size;ip++){
			 if(it==0) sum += cal2->scifi0[il][iv][ip];
			 else      sum += cal2->scifi1[il][iv][ip];
		  }
		  if(TMath::Abs(sum >= 0.02)) check++;
		}
	 }
  }
  if(check > 0) return false;
	 
  return true;
}


// ---------------------------------------------------------------------
//                                  MAIN
// ---------------------------------------------------------------------
int main(int argc, char **argv) {
    
  TString inputfilename  = "";
  TString outputfilename = "";
  TString pedefilename = "";
  TString pedelistfilename = "";

  
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
	 if (ss == "-l" || ss == "--pedelist") {
		pedelistfilename = argv[++i];
		strcpy(argv[i], "");		
	 }	 
	 if (ss == "-p" || ss == "--avpede") {
		pedefilename = argv[++i];
		strcpy(argv[i], "");		
	 }
	 if (ss == "-h" || ss == "--help") {
		printhelp();
		return -1;
	 }
  }
  
  if (inputfilename == "" || outputfilename == "" || pedelistfilename == "") {
	 cerr << "give an input file name and/or an output file name." << endl;
	 printhelp();
	 return -1;
  }

  cout << "INPUT_FILE_PATH= " << inputfilename << endl;
  cout << "OUTPUT_FILE_PATH= " << outputfilename<< endl;
  cout << "PDEELIST_FILE_PATH= " << pedelistfilename << endl;
    
  // ++++++ INITIALIZATIONS +++++++++++++++++++
  
  TFile *ofile = new TFile(outputfilename, "recreate");
  ofile->cd();
  
  Histogram hist_all("all");
  Histogram hist_sel("sel");

  
  gROOT->cd();
  

  // ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
  LHCfEvent *ev   = new LHCfEvent();
  TChain    *tree = new TChain("LHCfEvents");
  tree->Add(inputfilename.Data());
  tree->SetBranchAddress("ev.", &ev);

  // ++++++ OPEN OUTPUT TREE +++++++++++++++++++++++
  TFile     *ofile2 = new TFile(pedelistfilename, "RECREATE");
  LHCfEvent *oev   = new LHCfEvent();
  TTree     *otree = new TTree("LHCfEvents", "Collision Events");
  otree->Branch("ev.", "LHCfEvent", &oev);
  otree->SetMaxTreeSize(4000000000);
  gROOT->cd();
  
  // +++++ EVENT LOOP +++++++++++++++++++++++++++++++
  int      nevmax = tree->GetEntriesFast();
  int      nevent = 0;
  int      nevent_fill = 0;
  A1Cal1    *cal1 = NULL;
  A1Cal2M   *cal2 = NULL;

  A1PedeSubtract *pede = new A1PedeSubtract();
  pede->SetOffsetSubtraction(false);
  
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
	 if (!ev->Check("a1cal1tmp")) { continue; }
	 nevent++;
         
	 cal1 = (A1Cal1*) ev->Get("a1cal1tmp");
	 cal2 = (A1Cal2M *) ev->Get("a1cal2");




	 hist_all.Fill(cal1,cal2);

	 if( EventSelection( cal2 ) == false){ continue; }
	 
	 hist_sel.Fill(cal1, cal2);

	 // Pedestal calculation
	 pede->FillPedeEvent(cal1);
	 
	 oev -> HeaderCopy(ev);
	 oev -> Add(ev->Get("a1cal1tmp"));
	 oev -> Add(ev->Get("a1cal2"));
	 otree->Fill();
	 oev->Clear();
	 nevent_fill++;
	 
  }
  cerr << endl;
  cout << "NEvent : " << nevent << endl;
  cout << "NFill  : " << nevent_fill << endl;

  pede->CalPedestal();
  if(pedefilename!=""){
	 pede->WriteFile((char*)pedefilename.Data());
  }
  
  ofile->Write();
  ofile->Close();

  ofile2->Write("", TObject::kOverwrite);
  ofile2->Close();
  
  return 0;
    
}
