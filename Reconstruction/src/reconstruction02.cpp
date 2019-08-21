/**********************************************************************\
  Quick Reconstruction for RHICf Operation 2017

  \**********************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TDatime.h>
#include <TVector3.h>

#include "LHCfEvent.h"
#include "RHICfRaw_Op2017.h"
#include "A1Cal1.h"
#include "A1Cal2M.h"

#include "RHICfRec0.h"
#include "RHICfRec1.h"
#include "RHICfPhys.h"
#include "../include/Delaypede.h"
typedef RHICfRaw_Op2017  RHICfRaw;

#include "A1Calibration.h"
#include "A1Reconstruction.h"

void printhelp() {
	cout << "Quick Reconstruction for RHICf 2017 \n"
	     << "./bin/quickreconstruction -i inputfile -o outputfile -p pedestalfile \n"
	     << "Options)\n"
	     << "  --all   : Select all triggered events \n"
	     << "  --shower   : Select only shower triggered events \n"
	     << "  --special1 : Select only special1 triggered events \n"
	     << "  --special2 : Select only special2 triggered events \n"
	     << endl;
	return;
}

// ---------------------------------------------------------------------
//                                  MAIN 
// ---------------------------------------------------------------------
int main(int argc, char **argv) {
	
	enum EVENTCUT {
			EVENTCUT_SHOWER,
			EVENTCUT_SPECIAL1,
			EVENTCUT_SPECIAL2,
			EVENTCUT_PEDESTAL,
			EVENTCUT_ALL
	};
	
	enum SIMMODE {
			SIM_CAL1,     // Cal1 format (output of sim2exp)
			SIM_SIM,       // Simulation true
			SIM_OFF
	};
	
	TString  arg_inputfilename  = "";
	TString  arg_outputfilename = "";
	TString  arg_pedefile       = "";
	TString  arg_avepedefile       = "";
	TString  arg_startiev       = "";
	TString  arg_endiev         = "";
	EVENTCUT arg_eventcut       = EVENTCUT_ALL;
	bool     arg_debugmode      = false;
	SIMMODE  arg_simulationmode = SIM_OFF;
	int run =0;
	for (int i = 1; i < argc; i++) {
		TString ss = argv[i];
		
		if (ss == "-i" || ss == "--input") {
			arg_inputfilename = argv[++i];
			strcpy(argv[i], "");
		}
		if (ss == "-o" || ss == "--output") {
			arg_outputfilename = argv[++i];
			strcpy(argv[i], "");
		}
		if (ss == "-p" || ss == "--pedestal") {
			arg_pedefile = argv[++i];
			strcpy(argv[i], "");
		}
		if (ss == "-avep" || ss == "--avepedestal") {
                  arg_avepedefile = argv[++i];
                  strcpy(argv[i], "");
                }

		if (ss == "-f") {
			arg_startiev = argv[++i];
			strcpy(argv[i], "");
		}
		if (ss == "-t") {
			arg_endiev = argv[++i];
			strcpy(argv[i], "");
		}
		if(ss=="-run"){
		  run = atoi(argv[++i]);
		  cout    << "RUN NUMBER" << " " << run << endl;
		}
		if (ss == "--shower") { arg_eventcut = EVENTCUT_SHOWER; }
		if (ss == "--special1") { arg_eventcut = EVENTCUT_SPECIAL1; }
		if (ss == "--special2") { arg_eventcut = EVENTCUT_SPECIAL2; }
		if (ss == "--pedestal") { arg_eventcut = EVENTCUT_PEDESTAL; }
		if (ss == "--all") { arg_eventcut = EVENTCUT_ALL; }
		if (ss == "--debug") { arg_debugmode = true; }
		if (ss == "--sim") { arg_simulationmode = SIM_CAL1; }
		if (ss == "--simtrue") { arg_simulationmode = SIM_SIM; }
        
		if (ss == "-h" || ss == "--help") {
			printhelp();
			return 0;
		}
	}
	
	// ++++++ PARAMETERS  +++++++++++++++++++++++++++
	TString  inputfilename  = arg_inputfilename;
	TString  outputfilename = arg_outputfilename;
	TString  pedefile       = arg_pedefile;
	TString  avepedefile       = arg_avepedefile;
	EVENTCUT paramEventCut  = arg_eventcut;
	bool     debugmoe       = arg_debugmode;
	SIMMODE  simulationmode = arg_simulationmode;
	int      startiev       = atoi(arg_startiev);
	int      endiev         = atoi(arg_endiev);
	
	// ++++++ INITIALIZATIONS +++++++++++++++++++
	TRint theApp("App", &argc, argv, 0, 0, kTRUE);
	A1Calibration *calibration = new A1Calibration();
	calibration->SetupDefault_RHICfOp2017();
	calibration->SetPedestalFile(pedefile.Data());
	calibration->SetAvePedestalFile(avepedefile.Data());
	calibration->Initalize();
	
	//return 0;
	
	gROOT->SetBatch(kTRUE);
	A1Reconstruction *reconstruction = new A1Reconstruction();
	
	reconstruction->Initialize();
	
	// ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
	LHCfEvent *ev   = new LHCfEvent();
	TChain    *tree = new TChain("LHCfEvents");
	tree->AddFile(inputfilename.Data());
	tree->SetBranchAddress("ev.", &ev);
	
	// +++++ OPEN OUTPUT FILE +++++++++++++++++++++++++
	TFile     *ofile = new TFile(outputfilename, "RECREATE");
	LHCfEvent *oev   = new LHCfEvent();
	TTree     *otree = new TTree("LHCfEvents", "Collision Events");
	otree->Branch("ev.", "LHCfEvent", &oev);
	otree->SetMaxTreeSize(4000000000);
	
	// Histograms for checks
	TH1D     *h1cal[2][2];
	for (int tower   = 0; tower < 2; ++tower) {
		for (int pid = 0; pid < 2; ++pid) {
			h1cal[tower][pid] = new TH1D(Form("h1cal_%d_%d", tower, pid), "Acuum", 16, 0, 16);
		}
	}
	
	gROOT->cd();
	
	// +++++ EVENT LOOP ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
	int nevmax         = tree->GetEntriesFast();
	int nevupto        = 10000;
	
	int     startHour;
	int     startMin;
	TDatime *startTime = new TDatime();
	startHour = startTime->GetHour();
	startMin  = startTime->GetMinute();
	
	int nevent = 0, nevent_sel1 = 0, nevent_sel2 = 0, nevent_fill = 0;
	
	RHICfPhys *phys = new RHICfPhys();
	A1Cal2M   *cal2 = new A1Cal2M();
	//RHICfRec  *fRec = new RHICfRec();
	
	

	
	bool NoEvent = false;
	double gsobar = 0;
	double before, after;
	int delay_flag[2] = {0};
	int ndelay_flag = 0;
	//  == START OF EVENT LOOP ==
	//for (int iev = 0; iev < nevmax; iev++) {
	for (int iev = startiev; iev < endiev; iev++) {
	  //cerr << "1" << endl;
		Int_t ievlocal = tree->LoadTree(iev);
		if (ievlocal < 0) {
			
			if (iev == startiev) NoEvent = true;
			//cout << iev << endl;
			break;
		}
		

		//continue;
		//cout << iev << endl;
		//cerr << "2" << endl;
		if (iev && iev % 10 == 0) { cerr << '*'; }
		if (iev && iev % 100000 == 0) { cerr << iev << endl; }
		
		ev->Delete();
		tree->GetEntry(iev);
		nevent++;
				
		// === EVENT SELECTION 1 ===
		// Cut SlowControl, Scaler Events
		if (simulationmode == SIM_OFF && !ev->Check("a1raw")) { continue; }
		if (simulationmode == SIM_CAL1 && !ev->Check("a1cal1")) { continue; }
		if (simulationmode == SIM_SIM && !ev->Check("a1sim")) { continue; }
		nevent_sel1++;
		
		//cerr << "3" << endl;
		// === EVENT SELECTION 2 ===
		Bool_t checkselection = kFALSE;
		switch (paramEventCut) {
			case EVENTCUT_SHOWER:
				if (ev->a1flag[0] & 0x010) { checkselection = kTRUE; } // L2T_SHOWER FLAG
				break;
			case EVENTCUT_SPECIAL1:
				if (ev->a1flag[0] & 0x080) { checkselection = kTRUE; } // L2T_SPECIAL1
				break;
			case EVENTCUT_SPECIAL2:
				if (ev->a1flag[0] & 0x200) { checkselection = kTRUE; } // L2T_SHOWER2
				break;
			case EVENTCUT_PEDESTAL:
				if (ev->a1flag[0] & 0x020) { checkselection = kTRUE; } // L2T_PEDESTAL
				break;
			case EVENTCUT_ALL:
				checkselection = kTRUE;
				break;
			default:
				break;
		}
		
		if (!checkselection) { continue; }
		nevent_sel2++;
		
		//=== CALIBRATION ===
		//For Experimental data
		if (simulationmode == SIM_OFF) {
		  calibration->Calculate(ev->Get("a1raw"));
		  //calibration->Calculate(ev->Get(raw));
		  reconstruction->SetData(calibration->GetCal2());
		  //cal2 = calibration->GetCal2();
		  //cout << "raw " << endl; 
		}
		// For MC data converted to Cal1
		else if (simulationmode == SIM_CAL1) {			
		  reconstruction->SetData((A1Cal2M *) ev->Get("a1cal1"));
		  cout << "sim cal " << endl; 
		}
		
		// For MC true
		else if (simulationmode == SIM_SIM) {
		  reconstruction->SetData((A1Cal2M *) ev->Get("a1sim"));
		  cout << "sim" << endl;
		}
		
			
		// === Event Reconstruction ===
		reconstruction->Reconstruct();
		
		//   reconstruction->fRec->SetAnalysisFlags(Flags);
		//Flags = reconstruction->fRec->GetAnalysisFlags();
		// if(Flags>0){
		//    cout << "Flags " << bitset<8>(reconstruction->fRec->GetAnalysisFlags()) << endl;
		// }
        
		//reconstruction->GetRec()->Show(); // For debug
		
		// === FILL TO OUTPUT FILE ===
		oev->HeaderCopy(ev);
		oev->Add(reconstruction->GetRec());
	        
		if (ev->Check("a1simin")) oev->Add(ev->Get("a1simin"));
		if (debugmoe) oev->Add(calibration->GetCal2());
		if (ev->Check("star")) oev->Add(ev->Get("star"));
		otree->Fill();
		oev->Clear();
		nevent_fill++;
		
		// === For Check ==
		if (ev->a1flag[0] & 0x010) {
			reconstruction->GetRec()->FillToPhys(phys);
			for (int tower = 0; tower < 2; ++tower) {
				if (phys->Hits(tower) > 0 && phys->InFiducial(tower)) {
					int pid = 0;
					if (phys->IsElemag(tower)) pid = 0;
					if (phys->IsHadron(tower)) pid = 1;
					for (int layer = 0; layer < 16; ++layer) {
						h1cal[tower][pid]->Fill(layer + 0.5, calibration->GetCal2()->cal[tower][layer]);
					}
				}
			}
		}
		
	} // ==  END OF EVENT LOOP ==
	cerr << endl;
	
	int     endHour;
	int     endMin;
	TDatime *endTime = new TDatime();
	endHour = endTime->GetHour();
	endMin  = endTime->GetMinute();
	double elapsedHour = (double) (endHour * 60 + endMin - startHour * 60 - startMin) / 60;
	
	cout << "Total entries: " << startiev << " ~ " << nevmax << endl;
	printf("This work took %0.2f Hour = %d Minute.\n", elapsedHour, (int) (elapsedHour * 60));
	
	// ++++++++++++++++ WRITE OUTPUT TREE ++++++++++++++++++++
	ofile->cd();
	ofile->Write("", TObject::kOverwrite);
	ofile->Close();
	
	char rmname[256];
	//sprintf(rmname, "%s", outputfilename);
	if (NoEvent) system(Form("rm %s", outputfilename.Data()));
	
	// ++++++++++++ PRINT INFORMATION +++++++++++++
	cout << "INPUT FILE    : " << inputfilename << endl
	     << "OUTPUT FILE   : " << outputfilename << endl
	     << "PEDESTAL FILE : " << pedefile << endl
	     << "NUMBER OF EVENTS " << endl
	     << "  ALL  : " << nevent << endl
	     << "  CUT1 : " << nevent_sel1 << endl
	     << "  CUT2 : " << nevent_sel2 << endl
	     << "  FILL : " << nevent_fill << endl
             << endl;
	
	theApp.Run();
	return 0;
}
