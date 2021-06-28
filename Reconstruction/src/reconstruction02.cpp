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

#include <LHCfEvent.h>
#include <RHICfRaw_Op2017.h>
#include <A1Cal1.h>
#include <A1Cal2M.h>

#include <RHICfRec0.h>
#include <RHICfRec1.h>
#include <RHICfPhys.h>
typedef RHICfRaw_Op2017  RHICfRaw;
#include <RHICfSimIncidents.h>

#include <A1Calibration.h>
#include <A1Reconstruction.h>
#include <McPedestal.h>

void printhelp() {
	cout << "Reconstruction for RHICf 2017 \n"
	     << "./bin/reconstruction02 -r [run type] -i [input file] -o [output file] -p [pedestal file] -avep [average pedestal]"
	     << "-f [start iev] -t [end iev]\n"
	     << "Options)\n"
	     << "  --all   : Select all triggered events \n"
	     << "  --shower   : Select only shower triggered events \n"
	     << "  --special1 : Select only special1 triggered events \n"
	     << "  --special2 : Select only special2 triggered events \n"
	     << "  --pedestal_forsim : for production of pedestal list for simulation  \n"	  
	     << endl;
	return;
}


void CalorimeterRescale(A1Cal2M* cal, double scale_ts, double scale_tl){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      cal->cal[it][il] *= (it==0?scale_ts:scale_tl);
    }
  }

  return ;
}

//  This is still temporal. A study about PID (dE comp btw data and MC) by Menjo 
void CalorimeterRescaleLayer(A1Cal2M* cal){
  // Airtificial rescaling the dE in A1Cal2 according to dE comparison result.
  static const double scale[2][16] =  {
    { 0.9687, 1.006, 0.9749, 1.06, 1.01, 0.9476, 1.069, 0.9761, 1.046, 1.055, 1.178, 1.349, 1.996, 2.593, 4.576, 4.966},
    { 0.8955, 0.8995, 1.032, 1.032, 1.082, 0.9758, 0.9511, 1.008, 0.999, 1.023, 1.011, 1.2, 2.4, 2.946, 5.13, 10.94}};

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      // apply only <= layer 8
      if(il <=8)
        cal->cal[it][il] /= scale[it][il];
    }
  }

  return ;
}

// ======================================= MAIN ======================================= //
int main(int argc, char **argv) {
	
	enum EVENTCUT {
			EVENTCUT_SHOWER,
			EVENTCUT_SPECIAL1,
			EVENTCUT_SPECIAL2,
			EVENTCUT_PEDESTAL,
			EVENTCUT_PEDESTAL_FORSIM,    // For pedestal event list for simulation
			EVENTCUT_SIMTRUE,
			EVENTCUT_ALL
	};
	
	enum SIMMODE {
			SIM_CAL1,      // Cal1 format (output of sim2exp)
			SIM_SIM,       // Simulation true
			SIM_PED,       // Simulation true + Pedestal 
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
	TString  arg_pedelistfile   = ""; // for simulation of SIM_PED mode
	

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
		if (ss == "--pedestal_forsim") {arg_eventcut = EVENTCUT_PEDESTAL_FORSIM;}
                if (ss == "--simcut") {arg_eventcut = EVENTCUT_SIMTRUE;}
		if (ss == "--all") { arg_eventcut = EVENTCUT_ALL; }
		if (ss == "--debug") { arg_debugmode = true; }
		if (ss == "--sim") { arg_simulationmode = SIM_CAL1; }
		if (ss == "--simtrue") { arg_simulationmode = SIM_SIM; }
		if (ss == "--simped") { arg_simulationmode = SIM_PED; }
		if (ss == "--pedelist") {
		  arg_pedelistfile = argv[++i];
                  strcpy(argv[i], "");
		}
        
		if (ss == "-h" || ss == "--help") {
			printhelp();
			return 0;
		}
	}


	if(arg_simulationmode == SIM_OFF || arg_simulationmode == SIM_CAL1){
		if(arg_runtype=="" || arg_inputfilename=="" || arg_outputfilename=="" || arg_pedefile=="" || 
		   arg_startiev=="" || arg_endiev=="" || arg_avepedefile=="" || 
		   (arg_runtype!="TS" && arg_runtype!="TL" && arg_runtype!="TOP")){

			printf("simulation mode is SIM_OFF or SIM_CAL1\n");		
			printhelp();
        		return 0;

        	}	
	}
	else if(arg_simulationmode == SIM_SIM){
		if(arg_runtype=="" || arg_inputfilename=="" || arg_outputfilename=="" || arg_startiev=="" || arg_endiev=="" || 
		   (arg_runtype!="TS" && arg_runtype!="TL" && arg_runtype!="TOP")){

			printf("simulation mode is SIM_SIM\n");
                        printhelp();
                        return 0;

		}	
	}
	else if(arg_simulationmode == SIM_PED){
		if(arg_runtype=="" || arg_inputfilename=="" || arg_outputfilename=="" ||
		   (arg_runtype!="TS" && arg_runtype!="TL" && arg_runtype!="TOP") || arg_pedelistfile=="" ){

			printf("simulation mode is SIM_PED\n");
                        printhelp();
                        return 0;

		}	
	}

	

	// Parameters
	TString  inputfilename  = arg_inputfilename;
	TString  outputfilename = arg_outputfilename;
	TString  pedefile       = arg_pedefile;
	TString  avepedefile    = arg_avepedefile;
	EVENTCUT paramEventCut  = arg_eventcut;
	bool     debugmode      = arg_debugmode;
	SIMMODE  simulationmode = arg_simulationmode;
	TString  pedelistfile   = arg_pedelistfile;
	int      startiev       = atoi(arg_startiev);
	int      endiev         = atoi(arg_endiev);

	double   energyrescale[2] = {1.}; // [tower]
	double   beamcenter_mc[2] = {0.}; // for MC;
	// From the study of Minho 
	if(arg_runtype == "TS"){
	  // Middle position 
	  energyrescale[0] = 1.042;
	  energyrescale[1] = 1.061;
	  beamcenter_mc[0] = 0.;
	  beamcenter_mc[1] = 0.;
	}
	else if(arg_runtype == "TL"){
	  // Bottom position 
	  energyrescale[0] = 1.043;
	  energyrescale[1] = 1.042;
	  beamcenter_mc[0] = 0.;
	  beamcenter_mc[1] = 47.4;
	}
	else if(arg_runtype == "TOP"){
	  // Bottom position 
	  energyrescale[0] = 1.055;
	  energyrescale[1] = 1.067;
	  beamcenter_mc[0] = 0.;
	  beamcenter_mc[1] = -24.;
	}

	cout << "Run type: " << arg_runtype << endl
	     << "Event cut: " << paramEventCut << endl; 	

	TRint theApp("App", &argc, argv, 0, 0, kTRUE);
	gROOT->SetBatch(kTRUE);

	// A1Calibration.
	A1Calibration *calibration = new A1Calibration();
	if(simulationmode==SIM_OFF || simulationmode==SIM_CAL1){
		calibration->SetupDefault_RHICfOp2017();
		calibration->SetPedestalFile(pedefile.Data());
		calibration->SetAvePedestalFile(avepedefile.Data());
		calibration->Initalize();
	}
	
	// A1Reconstruction.	
	A1Reconstruction *reconstruction = new A1Reconstruction();
	reconstruction ->SetRunType(arg_runtype);
	reconstruction->Initialize();
	if(arg_simulationmode!=SIM_OFF){
		reconstruction->SetMc();
	}

	// Pedestal for MC
	McPedestal *mcpede;
	if(simulationmode==SIM_PED){
	  mcpede = new McPedestal();
	  mcpede->ReadFile(pedelistfile);
	}

	// Set Beam Center in MC
	RHICfSimP::SetPositionBeamCenter(beamcenter_mc[0], beamcenter_mc[1]);
	RHICfSimP::SetPositionBeamPipeCenter(-1.*beamcenter_mc[0], -1.*beamcenter_mc[1]);
	
	
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
  
	// Event numbers; 1st bin; all, 2nd bin 1st sel, ... 
        TH1D *h1nevent = new TH1D("h1nevent","Number of Events", 5,0.,5.);	


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
	A1Cal2M   *sim  = new A1Cal2M("a1sim","Simulation");
	RHICfRec  *rec = new RHICfRec();
	RHICfSimIncidents *simin;
	
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
		h1nevent->Fill(0.5);
				
		// === EVENT SELECTION 1 ===
		// Cut SlowControl, Scaler Events
		if (simulationmode == SIM_OFF && !ev->Check("a1raw")) { continue; }
		if (simulationmode == SIM_CAL1 && !ev->Check("a1cal1")) { continue; }
		//if (simulationmode == SIM_SIM && !ev->Check("a1sim")) { continue; }
		if (simulationmode == SIM_SIM && !ev->Check("a1cal2")) { continue; }
		nevent_sel1++;
		h1nevent->Fill(1.5);
		
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
		  if (ev->a1flag[0] & 0x2000) { checkselection = kTRUE; } // L2T_PEDESTAL
		  break;
		case EVENTCUT_PEDESTAL_FORSIM:
		  if (ev->a1flag[0] & 0x2000) { checkselection = kTRUE; } // L2T_PEDESTAL	
		  break;
		case EVENTCUT_SIMTRUE:
		  if (! ev->Check("a1simin")) {break;}
		  simin = (RHICfSimIncidents*) ev->Get("a1simin");
		  if ( simin->GetNHit(10,0,0.0,-1.) != 0 || simin->GetNHit(10,1,0.0,-1.) != 0 ) {
			 checkselection = kTRUE;
		  }
		  break;
		case EVENTCUT_ALL:
		  checkselection = kTRUE;
		  break;
		default:
		  break;
		}
		
		if (!checkselection) { continue; }
		nevent_sel2++;
		h1nevent->Fill(2.5);
	
		// Calibration.

		//For experimental data
		if (simulationmode == SIM_OFF){

			calibration->Calculate(ev->Get("a1raw"));
			cal2 = calibration->GetCal2();
			CalorimeterRescale(cal2, energyrescale[0],energyrescale[1]);
			CalorimeterRescaleLayer(cal2);
			
			reconstruction->SetData(cal2);
		}
		// // For MC data converted to Cal1 (Not Yet)
		// else if (simulationmode == SIM_CAL1){
	
		// 	reconstruction->SetData((A1Cal2M *) ev->Get("a1cal1"));
		// }
		// For MC true
		else if (simulationmode == SIM_SIM){

			//reconstruction->SetData((A1Cal2M *) ev->Get("a1sim"));
			reconstruction->SetData((A1Cal2M *) ev->Get("a1cal2"));
			cal2 = (A1Cal2M *) ev->Get("a1cal2");
		}
		// For MC + Pedestal 
		else if (simulationmode == SIM_PED){
		 	cal2 =  (A1Cal2M *) ev->Get("a1cal2");
			sim->copydata(cal2);
			mcpede->AddPedestal(cal2);
			reconstruction->SetData(cal2);
		}

		// Event selection in case of EVENTCUT_PEDESTAL_FORSIM
		if (paramEventCut == EVENTCUT_PEDESTAL_FORSIM){
		  oev -> Add(cal2);
		  oev -> Add(calibration->GetCal1tmp());
		}
		else {
		  // Reconstruction.
		  reconstruction -> Reconstruct();
		  rec = reconstruction -> GetRec();
		  oev -> Add(rec);		  
		  oev -> Add(cal2);
		}

		oev -> HeaderCopy(ev);

		//   reconstruction->fRec->SetAnalysisFlags(Flags);
		//Flags = reconstruction->fRec->GetAnalysisFlags();
		// if(Flags>0){
		//    cout << "Flags " << bitset<8>(reconstruction->fRec->GetAnalysisFlags()) << endl;
		// }

		//reconstruction->GetRec()->Show(); // For debug
		
		if (ev->Check("a1simin")) oev->Add(ev->Get("a1simin"));
		//if (debugmode) oev->Add(calibration->GetCal2());
		if (ev->Check("star")) oev->Add(ev->Get("star"));

		if (simulationmode == SIM_PED) oev->Add(sim);

		otree->Fill();
		oev->Clear();
		nevent_fill++;
		h1nevent->Fill(3.5);

		// For check.
		int TShit = rec -> GetResultNumberOfHits(0);
		int TLhit = rec -> GetResultNumberOfHits(1);
		if(TShit==1 && TLhit==1) ntype1++;
		if((TShit==0 && TLhit==2) || (TShit==2 && TLhit==0)) ntype2++;
		
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
