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
typedef RHICfRaw_Op2017  RHICfRaw;

#include "A1Calibration.h"
#include "A1Reconstruction.h"

void printhelp() {
	cout << "Reconstruction for RHICf 2017 \n"
	     << "./bin/reconstruction02 -r [run type] -i [input file] -o [output file] -p [pedestal file] -avep [average pedestal]"
	     << "-f [start iev] -t [end iev]\n"
	     << "Options)\n"
	     << "  --all   : Select all triggered events \n"
	     << "  --shower   : Select only shower triggered events \n"
	     << "  --special1 : Select only special1 triggered events \n"
	     << "  --special2 : Select only special2 triggered events \n"
	     << endl;
	return;
}

// ======================================= MAIN ======================================= //
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

	TString  arg_runtype        = "";	
	TString  arg_inputfilename  = "";
	TString  arg_outputfilename = "";
	TString  arg_pedefile       = "";
	TString  arg_avepedefile    = "";
	TString  arg_startiev       = "";
	TString  arg_endiev         = "";
	EVENTCUT arg_eventcut       = EVENTCUT_ALL;
	bool     arg_debugmode      = false;
	SIMMODE  arg_simulationmode = SIM_OFF;

	for (int i=1; i<argc; i++){

		TString ss = argv[i];

		if(ss=="-r" || ss=="--runtype"){
                        arg_runtype = argv[++i];
                        strcpy(argv[i], "");
                }		
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

	if(arg_runtype=="" || arg_inputfilename=="" || arg_outputfilename=="" || arg_pedefile=="" || arg_startiev=="" || arg_endiev=="" ||
	   arg_avepedefile=="" || (arg_runtype!="TS" && arg_runtype!="TL" && arg_runtype!="TOP")){

		printhelp();
                return 0;
        }
	
	// Parameters
	TString  inputfilename  = arg_inputfilename;
	TString  outputfilename = arg_outputfilename;
	TString  pedefile       = arg_pedefile;
	TString  avepedefile       = arg_avepedefile;
	EVENTCUT paramEventCut  = arg_eventcut;
	bool     debugmoe       = arg_debugmode;
	SIMMODE  simulationmode = arg_simulationmode;
	int      startiev       = atoi(arg_startiev);
	int      endiev         = atoi(arg_endiev);
	
	TRint theApp("App", &argc, argv, 0, 0, kTRUE);
	gROOT->SetBatch(kTRUE);

	// A1Calibration.
	A1Calibration *calibration = new A1Calibration();
	calibration->SetupDefault_RHICfOp2017();
	calibration->SetPedestalFile(pedefile.Data());
	calibration->SetAvePedestalFile(avepedefile.Data());
	calibration->Initalize();
	
	// A1Reconstruction.	
	A1Reconstruction *reconstruction = new A1Reconstruction();
	reconstruction -> SetRunType(arg_runtype);
	reconstruction->Initialize();
	
	// Input.
	LHCfEvent *ev   = new LHCfEvent();
	TChain    *tree = new TChain("LHCfEvents");
	tree->AddFile(inputfilename.Data());
	tree->SetBranchAddress("ev.", &ev);
	
	// Output.
	TFile     *ofile = new TFile(outputfilename, "RECREATE");
	LHCfEvent *oev   = new LHCfEvent();
	TTree     *otree = new TTree("LHCfEvents", "Collision Events");
	otree->Branch("ev.", "LHCfEvent", &oev);
	otree->SetMaxTreeSize(4000000000);
	
	// TCanvas and Histograms for checks
	const int nscan = 10;
	TCanvas* scanCanv[3][3][nscan];
        for(int tshit=0;tshit<3;tshit++){
                for(int tlhit=0;tlhit<3;tlhit++){
                        for(int iscan=0;iscan<nscan;iscan++){
                                scanCanv[tshit][tlhit][iscan] = new TCanvas(Form("scanCanv_%d_%d_%d", tshit, tlhit, iscan), "", 800, 800);
                        }
                }
        }

	TH1D* h1_cal[2][2];
	for (int tower=0; tower<2; ++tower){
		for (int pid=0; pid<2; ++pid){
			h1_cal[tower][pid] = new TH1D(Form("h1_cal_%d_%d", tower, pid), "Acuum", 16, 0, 16);
		}
	}
	
	gROOT->cd();
	
	int nevmax = tree->GetEntriesFast();	
	int nevent = 0;
	int nevent_sel1 = 0, nevent_sel2 = 0, nevent_fill = 0;
	int nevent_a1raw = 0, ntype1 = 0, ntype2 = 0;	
	bool NoEvent = false;

	RHICfPhys *phys = new RHICfPhys();
	A1Cal2M   *cal2 = new A1Cal2M();
	RHICfRec  *rec = new RHICfRec();

	// ======================================= Start event loop. ======================================= //
	for (int iev = startiev; iev < endiev; iev++){

		Int_t ievlocal = tree->LoadTree(iev);
		if (ievlocal < 0){
			if (iev == startiev) NoEvent = true;
			//cout << iev << endl;
			break;
		}
		
		//continue;
		//cout << iev << endl;
		//cerr << "2" << endl;
		if (iev && iev % 200 == 0) { cerr << '*'; }
		if (iev && iev % 5000 == 0) { cerr << iev << endl; }
		ev->Delete();
		tree->GetEntry(iev);
		nevent++;
				
		// === EVENT SELECTION 1 ===
		// Cut SlowControl, Scaler Events
		if (simulationmode == SIM_OFF && !ev->Check("a1raw")) { continue; }
		if (simulationmode == SIM_CAL1 && !ev->Check("a1cal1")) { continue; }
		if (simulationmode == SIM_SIM && !ev->Check("a1sim")) { continue; }
		nevent_sel1++;
		
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
	
		// Calibration.

		//For experimental data
		if (simulationmode == SIM_OFF){

			calibration->Calculate(ev->Get("a1raw"));
			reconstruction->SetData(calibration->GetCal2());
			cal2 = calibration->GetCal2();
		}

		// For MC data converted to Cal1
		else if (simulationmode == SIM_CAL1){
	
			reconstruction->SetData((A1Cal2M *) ev->Get("a1cal1"));
		}

		// For MC true
		else if (simulationmode == SIM_SIM){

			reconstruction->SetData((A1Cal2M *) ev->Get("a1sim"));
		}

		// Reconstruction.
		reconstruction -> Reconstruct();
		oev -> HeaderCopy(ev);
		rec = reconstruction -> GetRec();
                oev -> Add(rec);
		oev -> Add(cal2);

		//   reconstruction->fRec->SetAnalysisFlags(Flags);
		//Flags = reconstruction->fRec->GetAnalysisFlags();
		// if(Flags>0){
		//    cout << "Flags " << bitset<8>(reconstruction->fRec->GetAnalysisFlags()) << endl;
		// }

		//reconstruction->GetRec()->Show(); // For debug

		if (ev->Check("a1simin")) oev->Add(ev->Get("a1simin"));
		if (debugmoe) oev->Add(calibration->GetCal2());
		if (ev->Check("star")) oev->Add(ev->Get("star"));

		otree->Fill();
		oev->Clear();
		nevent_fill++;

		// For check.
		int TShit = rec -> GetResultNumberOfHits(0);
                int TLhit = rec -> GetResultNumberOfHits(1);
                if(TShit==1 && TLhit==1) ntype1++;
                if(TShit==0 && TLhit==2) ntype2++;

                int scanNum = reconstruction -> GetScanNum(TShit, TLhit);
                int tsmax = rec -> GetMaxBarLayer(0);
                int tlmax = rec -> GetMaxBarLayer(1);
                if(scanNum < nscan) reconstruction -> GetScan(scanCanv[TShit][TLhit][scanNum], tsmax, tlmax, iev);

		if (ev->a1flag[0] & 0x010) {
			reconstruction->GetRec()->FillToPhys(phys);
			for (int tower = 0; tower < 2; ++tower) {
				if (phys->Hits(tower) > 0 && phys->InFiducial(tower)) {
					int pid = 0;
					if (phys->IsElemag(tower)) pid = 0;
					if (phys->IsHadron(tower)) pid = 1;
					for (int layer = 0; layer < 16; ++layer) {
						h1_cal[tower][pid]->Fill(layer + 0.5, calibration->GetCal2()->cal[tower][layer]);
					}
				}
			}
		}

	}
	// ======================================= End of event loop. ======================================= //

	ofile->cd();

	for(int tshit=0;tshit<3;tshit++){
                for(int tlhit=0;tlhit<3;tlhit++){
                        for(int iscan=0;iscan<reconstruction->GetScanNum(tshit, tlhit);iscan++){

                                scanCanv[tshit][tlhit][iscan] -> Write(Form("scan_%d_%d_%d", tshit, tlhit, iscan));
                        }
                }
        }
	for (int tower=0; tower<2; ++tower){
                for (int pid=0; pid<2; ++pid){

                        h1_cal[tower][pid] -> Write();
                }
        }

	ofile->Write("", TObject::kOverwrite);
	ofile->Close();

	char rmname[256];
	//sprintf(rmname, "%s", outputfilename);
	if (NoEvent) system(Form("rm %s", outputfilename.Data()));

	// Print information.
	printf("ntype1 = %d\n", ntype1);
        printf("ntype2 = %d\n", ntype2);
        printf("nevent = %d\n", nevent);
        printf("nevent_a1raw = %d\n", nevent_a1raw);

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
