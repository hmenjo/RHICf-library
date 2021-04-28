//==================================================//
//                                                  //
//  - Created by MENJO Hiroaki on 2017/05/24.       //
//                                                  //
//  - First edition by Minho Kim on                 //
//                                                  //
//==================================================//

#include "../include/A1Reconstruction.h"

#include <iostream>
#include <iomanip>

#include <TClonesArray.h>
#include <TMath.h>
#include <TStyle.h>

using namespace std;

A1Reconstruction::A1Reconstruction() : Isruntype(false), Isbunchoffset(false){}
A1Reconstruction::~A1Reconstruction(){}

int A1Reconstruction::Initialize(){

	if(!Isruntype){
		cerr << "A1Reconstruction::Initialize - Run type was NOT specified." << endl;
		return -1;
	}

	fCal    = new A1Cal2M();
	fCalOrg = new A1Cal2M();
	//fRec    = new A1Rec("a1rec", "");
	fRec    = new RHICfRec("a1rec", "");
	fPos = new GSObarPosCalc();

	TString dirLibrary = LIBDIR;
	TString dirWork = WORKDIR;

	// Energy threshold criteria for hit detection
	cEnergyThreshold = 10.;

	// Leakage-out correction.
	paramGSOLY20mm = dirWork + "/tables/" + runtype + "/leakageout_verTH2D_photon.root";
	paramGSOLY40mm = dirWork + "/tables/" + runtype + "/leakageout_verTH2D_photon.root";
	paramGSOLY20mmHadron = dirWork + "/tables/" + runtype + "/leakageout_verTH2D_neutron.root";
	paramGSOLY40mmHadron = dirWork + "/tables/" + runtype + "/leakageout_verTH2D_neutron.root";
	fPosdep = new ScintiPosDepGSO();
	fPosdep->SetdEMapArm1((char *) paramGSOLY20mm.Data(), (char *) paramGSOLY40mm.Data(), 
								 (char *) paramGSOLY20mmHadron.Data(), (char *) paramGSOLY40mmHadron.Data());
	// Leakage-in correction.
	paramShowerLeakagePhoton = dirWork + "/tables/" + runtype + "/leakagein_verTH2D_photon.root";
	paramShowerLeakageHadron = dirLibrary + "/tables/leakage_arm1_081118.root";// Not optimized yet.
	fLeakPhoton = new ConShowerLeakage();
	fLeakPhoton->ReadROOTFile((char *) paramShowerLeakagePhoton.Data());
	fLeakHadron = new ConShowerLeakage();
	fLeakHadron->ReadROOTFile((char *) paramShowerLeakageHadron.Data());

	paramGSObarPosition  = dirLibrary+ "/tables/gsobar_postable_160803.tab";
	fPos -> ReadPositionTable((char*)paramGSObarPosition.Data());

	fPid = new ParticleID01();

	for(int tshit=0; tshit<3; tshit++){
                for(int tlhit=0;tlhit<3;tlhit++){
                        scanNum[tshit][tlhit] = 0;
                }
        }
	for(int it=0; it<2; it++){
		L20[it] = 0;
		L90[it] = 0;
	}

	return 0;
}

void A1Reconstruction::SetRunType(TString run){

	runtype = run;
	Isruntype = true;
}

int A1Reconstruction::SetData(A1Cal2M *cal){

	fCal->copy(cal);
	fCalOrg->copy(cal);

	// Bunch offset.
	ifstream fbunch("./tables/bunchoffset.dat");
	int runnum;
	while(!fbunch.eof()){
		fbunch >> runnum;
		if(runnum == fCal->run){
			fbunch >> bunchoffset;
			Isbunchoffset = true;
			break;
		}
	}
	if(!Isbunchoffset){
		cerr << "A1Reconstruction::SetData - No bunch offset information" << endl;
		return -1;
	}

	return 0;
}

// ======================================= Reconstruction. ======================================= //
int A1Reconstruction::Reconstruct(){

	// Reset
	fRec -> clear();
	fRec -> resize();

	FillEventInfo();

	ReconstructPID();
	ReconstructHitPosition();
	
	if(fPos->GetWorthy(0)>0 || fPos->GetWorthy(1)>0) ReconstructEnergy();	

	return 0;
}

int A1Reconstruction::FillEventInfo(){

	fRec->run     = fCal->run;
	fRec->number  = fCal->number;
	fRec->gnumber = fCal->gnumber;
	fRec->time[0] = fCal->time[0];
	fRec->time[1] = fCal->time[1];
	//printf("NUMBER: %d\n", fRec->number);
	for (int i=0;i<3;i++) fRec->SetFlags(i, fCal->flag[i]);
	//fRec->SetEventQuality(A1Rec::GOOD);// For the moment, all events are set to GOOD.
	fRec->SetEventQuality(RHICfRec::GOOD);

	// Bunch information: 0 for RHICf and 1 for STAR
	int bunchrhicf = fCal -> counter[27];
	int bunchstar;
	if(-240<=bunchrhicf+bunchoffset && bunchrhicf+bunchoffset<-120) bunchstar = bunchrhicf + bunchoffset + 240;
	else if(-120<=bunchrhicf+bunchoffset && bunchrhicf+bunchoffset<0) bunchstar = bunchrhicf + bunchoffset + 120;
	else if(0<=bunchrhicf+bunchoffset && bunchrhicf+bunchoffset<120) bunchstar = bunchrhicf + bunchoffset;
	else if(120<=bunchrhicf+bunchoffset && bunchrhicf+bunchoffset<240) bunchstar = bunchrhicf + bunchoffset - 120;
	else if(240<=bunchrhicf+bunchoffset && bunchrhicf+bunchoffset<360) bunchstar = bunchrhicf + bunchoffset - 240; 
	else{
		cerr << "A1Reconstruction::FillEventInfo - Reconstructed bunch number is strange."  << endl;
		return -1;
	}
	//printf("RHICf bunch: %d\n", bunchrhicf);
	//printf("STAR bunch: %d\n\n", bunchstar);
	fRec -> SetBunchNumber(0, bunchrhicf);
	fRec -> SetBunchNumber(1, bunchstar);	

	// Fill Counter values
	for (int i=0;i<35;i++) fRec->SetCounter(i, fCal->counter[i] + 1.E-5);// Add 1.E-5 for double values.

	return 0;
}

int A1Reconstruction::ReconstructPID(){

	fPid->Calculate(fCal, 0);
	L20[0] = fPid->GetL20(0);
	L90[0] = fPid->GetL95(0);// L90
	fPid->Calculate(fCal, 1);
	L20[1] = fPid->GetL20(1);
	L90[1] = fPid->GetL95(1);// L90
	fRec->SetL20(0, L20[0]);
	fRec->SetL20(1, L20[1]);
	fRec->SetL90(0, L90[0]);
	fRec->SetL90(1, L90[1]);

	for(int itower=0; itower<2; itower++){
		if(8<fRec->GetL90(itower) && fRec->GetL90(itower)<18) fRec->SetResultPID(itower, RHICfPhys::ELEMAG);
		else fRec->SetResultPID(itower, RHICfPhys::HADRON);
	}

	return 0;
}

int A1Reconstruction::ReconstructHitPosition(){

	fPos -> SetData(fCal);

	int nhit[2] = {0};

	// Maximum and second maximum energy deposit layer
	double max_sumBar[2][4] = {0};// [tower][layer]

	for(int it=0; it<2; ++it){
		for(int ilay=0; ilay<4; ilay++){

			max_sumBar[it][ilay] = fPos->GetdE(it, ilay, 0) + fPos->GetdE(it, ilay, 1);
		}
		t_layer[it] = TMath::LocMax(4, max_sumBar[it]);
		fRec -> SetMaxBarLayer(it, t_layer[it]);		
		max_sumBar[it][t_layer[it]] = 0;
		t_layer2[it] = TMath::LocMax(4, max_sumBar[it]);
		fRec -> SetMaxBarLayer2(it, t_layer2[it]);
	}

	fPos -> IsWorthy();
	int worthy[2];
	worthy[0] = fPos -> GetWorthy(0);
	worthy[1] = fPos -> GetWorthy(1);	
	if(worthy[0]==0 && worthy[1]==0){
		for(int it=0;it<2;it++) fRec -> SetResultNumberOfHits(it, 0);
	}
	else{
		fPos -> CalcPos("");

		// Single hit.
		for(int it=0;it<2;it++){
			for(int il=0;il<4;il++){
				for(int ixy=0;ixy<2;ixy++){

					// Hit position.
					double pos = fPos->GetPeakPos(it, il, ixy);
					fRec->SetHitPosition(it, il, ixy, pos);

					// Bin position.
					int bin = fPos->GetMaximumBin(it, il, ixy);
					fRec->SetPeakPosition( it, il, ixy, bin);

					// Peak height.
					double peakheight = fPos -> GetPeakHeightSingle(it, il, ixy);
					fRec->SetdEAtPeak( it, il, ixy, peakheight);

					// Number of hits in each layer
					int nhiteach = fPos->EvalNumOfHits(it, il, ixy);
					fRec->SetNumberOfHits(it, il, ixy, nhiteach);

					// Chi2.
					double chi2 = fPos -> GetChi2Single(it, il, ixy, "reduced");
					fRec -> SetChiSquare(it, il, ixy, 0, chi2);
					chi2 = fPos -> GetChi2Multi(it, il, ixy, "reduced");
					fRec -> SetChiSquare(it, il, ixy, 1, chi2);
				}
			}
			// Final hit position.
			double posx = fPos->GetPeakPos(it, t_layer[it], 0);
			double posy = fPos->GetPeakPos(it, t_layer[it], 1);
			fRec->SetResultHitPosition(it, 0, posx);
			fRec->SetResultHitPosition(it, 1, posy);
			
			// Number of hits.
			nhit[it] = fPos->EvalNumOfHits(it);
			fRec->SetResultNumberOfHits(it, nhit[it]);
		}
		
		// Multi hit.
		double a1, b1, a2, b2;
		for(int it=0; it<2; ++it){
			if(nhit[it]>=2){
				fPos -> GetEachContribution(it);
				fRec -> SetMHNumberOfHits(it, 2);

				for(int il=0;il<4;il++){
					for(int ixy=0;ixy<2;ixy++){
						for(int imu=0;imu<2;imu++){

							double pos = fPos -> GetPeakPosMH(it, il, ixy, imu);
							double h_raw = fPos -> GetEachPeakRaw(it, il, ixy, imu);
							double h_estimated = fPos -> GetEachPeakEstimated(it, il, ixy, imu);
							double integral = fPos -> GetEachIntegral(it, il, ixy, imu);

							if(il==t_layer[it] && ixy==0 && imu==0) a1 = pos;
							if(il==t_layer[it] && ixy==1 && imu==0) b1 = pos;
							if(il==t_layer[it] && ixy==0 && imu==1) a2 = pos;
							if(il==t_layer[it] && ixy==1 && imu==1) b2 = pos;

							fRec -> SetMHPosition(it, il, ixy, imu, pos);
							fRec -> SetMHPeakRaw(it, il, ixy, imu, h_raw);
							fRec -> SetMHPeakEstimated(it, il, ixy, imu, h_estimated);
							fRec -> SetMHIntegral(it, il, ixy, imu, integral);

							//if(il==t_layer[it]){
							  //printf("GetPeakPosHM(%d, %d, %d, %d) = %f\n", it, il, ixy, imu, pos);
							  //printf("GetEachPeakRaw(%d, %d, %d, %d) = %f\n", it, il, ixy, imu, h_raw);
							  //printf("GetEachPeakEstimated(%d, %d, %d, %d) = %f\n", it, il, ixy, imu, h_estimated);
							  //printf("GetEachIntegral(%d, %d, %d, %d) = %f\n\n", it, il, ixy, imu, integral);
							  //}
						}
					}
				}
			}
		}
	}

	/*if(fPos->EvalNumOfHits(0)>=2){   
		fRec->SetMHNumberOfHits(0,2);       
		fPos->FillMH4Rec(fRec, 0);     
	} 
	if(fPos->EvalNumOfHits(1)>=2){ 
		fRec->SetMHNumberOfHits(1,2);  
		fPos->FillMH4Rec(fRec, 1); 
	}*/

	return 0;
}

int A1Reconstruction::ReconstructEnergy(){

  //----------------------- Photon and Pi0 -----------------------------------//

	// Hit decision by using sum dE
	for (int tower=0; tower<2; ++tower){
		double sumdE = fCal->calsum2(tower, 0, 15);
		fRec->SetSumdE(tower, sumdE);
		fRec->SetSumdE2(tower, fCal->calsum2(tower, 1, 11));
		/*if (fRec->GetResultNumberOfHits(tower) > 0 && sumdE < paramSumdEThreshold)
			fRec->SetResultNumberOfHits(tower, -3);*/

		// Check the number of hits with the value of simplified energy reconstruction. 
		if( ReconstructEnergyPhotonSimple(tower) < cEnergyThreshold ){
		  fRec->SetResultNumberOfHits(tower,0); //  Kill the hit if E<threshold
		} 
	}

	// Type-I pi0.
	if (fRec->GetResultNumberOfHits(0)>0 && fRec->GetResultNumberOfHits(1)>0) {
	  ReconstructEnergyPhotonDouble();
	  
	  // Check the number of hits again
	  for(int it=0;it<2;it++){
		 double energy = fRec->GetResultEnergy(it, RHICfPhys::ELEMAG);
		 if(energy < cEnergyThreshold){
          fRec->SetResultNumberOfHits(it,0); //  Kill the hit if E<threshold
		 }
	  }
	}

	// Single photon and Type-II pi0.
	// For the small tower 
	if (fRec->GetResultNumberOfHits(0)>0 && fRec->GetResultNumberOfHits(1)==0){

		CorrectionLightYieldPhoton();
		ReconstructEnergyPhotonSingle(0);
	}
	// For the large tower 
	if (fRec->GetResultNumberOfHits(0)==0 && fRec->GetResultNumberOfHits(1)>0){

		CorrectionLightYieldPhoton();
		ReconstructEnergyPhotonSingle(1);
	}

	//------------------------   Hadrons   ---------------------------//
	fCal->copydata(fCalOrg, A1Cal2::CAL);// Reset the LY correction
	for (int tower=0; tower<2; ++tower){
		if (fRec->GetResultNumberOfHits(tower) == 0) continue;
		ReconstructEnergyHadron(tower);
	}

	return 0;
}

int A1Reconstruction::CorrectionLightYieldPhoton(){

	double x, y;
	double x1, y1;
	double x2, y2;
	double p = 0;
	double q = 0;

	for (int tower=0; tower<2; tower++){
		// Single photon.
		if(fRec->GetResultNumberOfHits(tower)==1){
			x = fRec->GetResultHitPosition(tower, 0);
			y = fRec->GetResultHitPosition(tower, 1);
			fPosdep->Calibration(fCal, tower, x, y);
		}
		// Type-II pi0.
		if(fRec->GetResultNumberOfHits(tower)>1){
			x1 = fRec->GetMHPosition(tower, t_layer[tower], 0, 0);
			y1 = fRec->GetMHPosition(tower, t_layer[tower], 1, 0);
			x2 = fRec->GetMHPosition(tower, t_layer[tower], 0, 1);
			y2 = fRec->GetMHPosition(tower, t_layer[tower], 1, 1);

			//if(fPos->GetHitNum(0)==0) printf("a1 = %0.1f, b1 = %0.1f, a2 = %0.1f, b2 = %0.1f\n", x1, y1, x2, y2);
			if(!fPos->xoverlap) p += fRec -> GetMHPeakEstimated(tower, t_layer[tower], 0, 0);
			if(!fPos->yoverlap) p += fRec -> GetMHPeakEstimated(tower, t_layer[tower], 1, 0);
			if(!fPos->xoverlap) p += fRec -> GetMHPeakEstimated(tower, t_layer2[tower], 0, 0);
			if(!fPos->yoverlap) p += fRec -> GetMHPeakEstimated(tower, t_layer2[tower], 1, 0);
			if(!fPos->xoverlap) q += fRec -> GetMHPeakEstimated(tower, t_layer[tower], 0, 1);
			if(!fPos->yoverlap) q += fRec -> GetMHPeakEstimated(tower, t_layer[tower], 1, 1);
			if(!fPos->xoverlap) q += fRec -> GetMHPeakEstimated(tower, t_layer2[tower], 0, 1);
			if(!fPos->yoverlap) q += fRec -> GetMHPeakEstimated(tower, t_layer2[tower], 1, 1);

			p = p/(p+q);
			q = 1-p;
			fPosdep->Calibration(fCal, tower, p, q, x1, y1, x2, y2);
		}
	}

	return 0;
}

double A1Reconstruction::ReconstructEnergyPhotonSimple(int tower){
  // simplifed energy reconstruction only for N_hit calculation with E_threshold 
  double x = fRec->GetResultHitPosition(tower, 0);
  double y = fRec->GetResultHitPosition(tower, 1);

  double sum = 0.;
  double eff = 0.;
  for(int il=1;il<=11;il++){
    eff = fPosdep -> GetEfficiency(1, tower, il, x, y);
    
    if(eff < 0.1 || eff > 2.){
      double towersize = (tower==0?20.0:40.0);
      double edgesize  = (il<12?1.0:2.0);
      if( x < edgesize )          x = edgesize;
      if( x > towersize-edgesize) x = towersize-edgesize;
      if( y < edgesize )          y = edgesize;
      if( y > towersize-edgesize) y = towersize-edgesize;
      eff = fPosdep -> GetEfficiency(1, tower, il, x, y);
    }
    sum += fCal->cal[tower][il]/eff;

    //sum += fCal->cal[tower][il] * fLeakPhoton->GetLeakinFactorll(tower, il, x, y);
  }
  return EnergyConversionPhoton(tower, sum);
}

int A1Reconstruction::ReconstructEnergyPhotonSingle(int tower){

	const int tower_nohit = (tower+1)%2;// Tower which has no hit.
	double x = fRec->GetResultHitPosition(tower, 0);
	double y = fRec->GetResultHitPosition(tower, 1);

	// Copy cal for non hit tower
	for (int il=0; il<16; il++) fCal->cal[tower_nohit][il] = fCalOrg->cal[tower_nohit][il];

	// Shower leakage in/out correction from only the hit tower.
	double sum[2], sumc[2];
	//sum[tower]        = fCal->calsum2(tower, 1, 12);
	sum[tower] = fCal -> calsum2(tower, 1, 11);
	sumc[tower]       = sum[tower];
	sum[tower_nohit]  = fCal->calsum2(tower_nohit, 1, 11);
	//sumc[tower_nohit] = sum[tower_nohit] - sumc[tower] * fLeakPhoton->GetLeakinFactor(1, tower, x, y);
	//cout << sumc[1] << endl;

	// Fill Results in A1Rec
	for (int tower=0; tower<2; tower++){
		fRec->SetSumdE(tower, fCal->calsum2(tower, 0, 15));
		fRec->SetSumdE2(tower, sumc[tower]);
		fRec->SetResultEnergy(tower, RHICfPhys::ELEMAG, EnergyConversionPhoton(tower, sumc[tower]));
		// For the moment, even in hadron events the same conversion function is applied.
		// rec->SetResultEnergy(tower,A1Phys::HADRON, EnergyConversion(tower,sumc[tower]));
	}
	return 0;
}

int A1Reconstruction::ReconstructEnergyPhotonDouble() {

  //cout << "Type-I pi0" << endl;

	double x[2], y[2];
	double sumc[2];
	double lo[2][16], li[2][16];
	double TSedep[16], TLedep[16];
	double TSedepCor[16], TLedepCor[16];

	for (int tower=0; tower<2; tower++){

		x[tower] = fRec->GetResultHitPosition(tower, 0);
		y[tower] = fRec->GetResultHitPosition(tower, 1);

		for(int il=0;il<16;il++){
			lo[tower][il] = fPosdep -> GetEfficiency(1, tower, il, x[tower], y[tower]);
			li[tower][il] = fLeakPhoton -> GetLeakinFactorll(tower, il, x[tower], y[tower]);
			//printf("tower:%d, layer:%d (%0.1f, %0.1f), li:%0.2f, lo:%0.2f\n", tower, il, x[tower], y[tower], li[tower][il], lo[tower][il]);
			if(tower==0) TSedep[il] = fCal -> cal[tower][il];
			if(tower==1) TLedep[il] = fCal -> cal[tower][il];
		}
	}

	for(int il=0;il<16;il++){
		double TSedeptmp = fCal -> cal[0][il];
		double TLedeptmp = fCal -> cal[1][il];

		TSedepCor[il] = ((li[1][il]*TLedep[il]-TSedep[il])/(li[1][il]*li[0][il]-1))/lo[0][il];		
		TLedepCor[il] = ((li[0][il]*TSedep[il]-TLedep[il])/(li[1][il]*li[0][il]-1))/lo[1][il];
		//TSedepCor[il] = TSedep[il]/lo[0][il];
		//TLedepCor[il] = TLedep[il]/lo[1][il];
		fCal -> cal[0][il] = TSedepCor[il]*(1.);
		fCal -> cal[1][il] = TLedepCor[il]*(1.);
		//printf("%d layer TS; before:%f, after:%f,    TL; before:%f, after:%f\n", il, TSedeptmp, fCal -> cal[0][il], TLedeptmp, fCal -> cal[1][il]);
	}

	for(int it=0;it<2;it++){ 
		sumc[it] = fCal->calsum2(it, 1, 11);
		//printf("sumc[%d] = %f\n", it, sumc[it]);

	}

	// Fill Results in A1Rec
	for (int tower = 0; tower < 2; tower++) {
		fRec->SetSumdE(tower, fCal->calsum2(tower, 0, 15));
		fRec->SetSumdE2(tower, sumc[tower]);
		fRec->SetResultEnergy(tower, RHICfPhys::ELEMAG, EnergyConversionPhoton(tower, sumc[tower]));
	}

	return 0;
}

int A1Reconstruction::ReconstructEnergyHadron(int tower) {
	double sum, sumc, x, y;
	x    = fRec->GetResultHitPosition(tower, 0);
	y    = fRec->GetResultHitPosition(tower, 1);
	sum  = fCal->calsum2(tower, 0, 15);

	double eff=1.;
	eff = fPosdep -> GetEfficiencyHadron(1, tower, x, y);
	/*if(eff < 0.1 || eff > 2.){
		double towersize = (tower==0?20.0:40.0);
		double edgesize  = (ilay<12?1.0:2.0);
		if( x < edgesize )          x = edgesize;
		if( x > towersize-edgesize) x = towersize-edgesize;
		if( y < edgesize )          y = edgesize;
		if( y > towersize-edgesize) y = towersize-edgesize;
		eff = fPosdep -> GetEfficiencyHadron(1, tower, x, y);
	}*/

	sumc = sum/eff;
	//printf("(%0.1f, %0.1f): %f --> %f\n", x, y, sum, sumc); 
	fRec->SetResultEnergy(tower, RHICfPhys::HADRON, EnergyConversionHadron(tower, sumc));

	return 0;
}

double A1Reconstruction::EnergyConversionPhoton(int tower, double sumdE){
        
	if(runtype=="TS"){
	  if(tower==0) return 31.1666*sumdE+1.39715; // Reference : latest Minho's analysis note in 2020/02/
	  if(tower==1) return 27.3389*sumdE+1.12892;
	  //if(tower==0) return 31.4127*sumdE+1.99042; // Minho's old study
	  //if(tower==1) return 27.5125*sumdE+1.73390;
	}
	if(runtype=="TL"){
	  if(tower==0) return 31.1323*sumdE+1.42462;
          if(tower==1) return 27.3429*sumdE+1.11522;
	  //if(tower==0) return 31.4127*sumdE;
	  //if(tower==1) return 27.5125*sumdE;
	}
	if(runtype=="TOP"){
	  if(tower==0) return 31.1749*sumdE+1.41172;
          if(tower==1) return 27.3434*sumdE+1.12205;
	  //if(tower==0) return 31.2272*sumdE;
	  //if(tower==1) return 27.3025*sumdE;
	}

	return 0;
}

double A1Reconstruction::EnergyConversionHadron(int tower, double sumdE){
	// [NOT FINALIZED YET]
	// Taken from Ueno's Master thesis.
	// Copy the one for TS to for TL

	if (tower==0) return  88.9*sumdE + 10.7;
	if (tower==1) return  88.9*sumdE + 10.7;

	return 0;
}

void A1Reconstruction::GetScan(TCanvas* c, int TSlayer, int TLlayer, int iev){

	int tshit = fRec -> GetResultNumberOfHits(0);
	int tlhit = fRec -> GetResultNumberOfHits(1);
	gStyle -> SetOptStat(0);
	fPos -> GetScan(c, TSlayer, TLlayer, iev, tshit, tlhit);
	scanNum[tshit][tlhit]++;
}

double A1Reconstruction::GetGPosX_Detector(int tower, double a, double b){

	double offset;
        double barsize;

        if(tower==0){
                offset = 0;
                barsize = 10;
        }
        if(tower==1){
                offset = 47.4;
                barsize = 20;
        }
        return (1./sqrt(2))*(a-b);
}
double A1Reconstruction::GetGPosY_Detector(int tower, double a, double b){

	double offset;
        double barsize;

        if(tower==0){
                offset = 0;
                barsize = 10;
        }
        if(tower==1){
                //offset = 47.4;
                //barsize = 20;
		offset = 5;
		barsize = -10;
        }
        return (1./sqrt(2))*(a+b-2*barsize)+offset;
}
bool A1Reconstruction::IsInFiducial(int tower, double a, double b){

	if(tower==0){
		if(2<a && a<18 && 2<b && b<18) return true;
		else return false;
	}
	if(tower==1){
		if(2<a && a<38 && 2<b && b<38) return true;
                else return false;
	}
}


