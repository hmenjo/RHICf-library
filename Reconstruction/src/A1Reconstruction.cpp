//
// Created by MENJO Hiroaki on 2017/05/24.
//

#include "../include/A1Reconstruction.h"

#include <iostream>
#include <iomanip>

using namespace std;

#include <TMath.h>
#include <TStyle.h>

A1Reconstruction::A1Reconstruction() : Isruntype(false), Isbunchoffset(false){}
A1Reconstruction::~A1Reconstruction(){}

void A1Reconstruction::Initialize() {
	
	fCal    = new A1Cal2M();
	fCalOrg = new A1Cal2M();
	fRec    = new RHICfRec("a1rec", "");
	fPos    = new GSObarPosCalc();
	//fPos->Initialize();

	// Parameters
	TString dirLibrary = LIBDIR;          // LIBDIR is defined in Makefile
	TString dirWork    = WORKDIR;

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

	return;
}

void A1Reconstruction::SetRunType(TString run){

        runtype = run;
        Isruntype = true;
}

int A1Reconstruction::SetData(A1Cal2M *cal){

        fCal->copy(cal);
        fCalOrg->copy(cal);

        // Bunch offset.
        ifstream fbunch("/ccj/w/r01/mhkim/RHICf/analysis/tables/bunchoffset.dat");
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
        fCol -> clear();

        FillEventInfo();

        ReconstructPID();
        ReconstructHitPosition();
        if(fPos->GetWorthy(0)>0 || fPos->GetWorthy(1)>0) ReconstructEnergy();

        return 0;
}

int A1Reconstruction::FillEventInfo() {

	fRec->run     = fCal->run;
        fRec->number  = fCal->number;
        fRec->gnumber = fCal->gnumber;
        fRec->time[0] = fCal->time[0];
        fRec->time[1] = fCal->time[1];
        //printf("NUMBER: %d\n", fRec->number);
        for (int i=0;i<3;i++) fRec->SetFlags(i, fCal->flag[i]);
        fRec->SetEventQuality(A1Rec::GOOD);// For the moment, all events are set to GOOD.

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

int A1Reconstruction::ReconstructPID() {
	// calculate L20 and L90, even no hit in the tower

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
                if(8<fRec->GetL90(itower) && fRec->GetL90(itower)<18) fRec->SetResultPID(itower, A1Phys::ELEMAG);
                else fRec->SetResultPID(itower, A1Phys::HADRON);
        }

        return 0;	
}

// IsMHPosition
int A1Reconstruction::ReconstructHitPosition() {
 
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

int A1Reconstruction::ReconstructEnergy() {
	// Hit decision by using sum dE
	for (int tower = 0; tower < 2; ++tower) {
		double sumdE = fCal->calsum2(tower, 0, 15);
		fRec->SetSumdE(tower, sumdE);
		fRec->SetSumdE2(tower, fCal->calsum2(tower, 1, 12));
		if (fRec->GetResultNumberOfHits(tower) > 0 && sumdE < paramSumdEThreshold)
			fRec->SetResultNumberOfHits(tower, -3);
	}
	
	// For Photons ============================================================
	
	// Light Yield & Shower Leakage-out corrections is included in following ReconstructEnergy(); method
	CorrectionLightYieldPhoton();
	
	// Energy Reconstruction for Double Tower Event
	if (fRec->GetResultNumberOfHits(0) == 1 && fRec->GetResultNumberOfHits(1) == 1)
		ReconstructEnergyPhotonDouble();
	
	// Energy Reconstruction for Single Tower Event in Small Tower
	if (fRec->GetResultNumberOfHits(0) == 1 && fRec->GetResultNumberOfHits(1) == 0)
		ReconstructEnergyPhotonSingle(0);
	
	// Energy Reconstruction for Sinelge Tower Event in Large Tower
	if (fRec->GetResultNumberOfHits(0) == 0 && fRec->GetResultNumberOfHits(1) == 1)
		ReconstructEnergyPhotonSingle(1);
	
	// For Type 2 pi0 event in TS
	if (fRec->GetResultNumberOfHits(0) == 2)
		ReconstructType2Pi0Photon(0);
	
	// For Type 2 pi0 event in TL
	if (fRec->GetResultNumberOfHits(1) == 2)
		ReconstructType2Pi0Photon(1);
	
	// For Hadrons ============================================================
	fCal->copydata(fCalOrg, A1Cal2::CAL); // Reset the LY correction
	
	for (int tower = 0; tower < 2; ++tower) {
		if (fRec->GetResultNumberOfHits(tower) == 0) continue;
		ReconstructEnergyHadron(tower);
	}
	
	return 0;
}

int A1Reconstruction::CorrectionLightYieldPhoton() {
	
	double x, y;
	double x1, y1;
	double x2, y2;
	double p, q;
	
	for (int tower = 0; tower < 2; tower++) {
		// Only for towers with #hits>0, the correction is applyed.
		if (fRec->GetResultNumberOfHits(tower) == 1) {
			
			x = fRec->GetResultHitPosition(tower, 0);
			y = fRec->GetResultHitPosition(tower, 1);
			//cout << x << " " << y << endl;
			/*
			if(tower ==0){
                          if(x < 0.) x = 0.1; 
                          if(20. < x) x = 19.9;
                          if(y < 0.) y = 0.1;
                          if(20. < y) y = 19.9;
                        }
                        if(tower ==1){
                          if(x < 0.) x = 0.1; 
                          if(40. < x) x = 39.9;
                          if(y < 0.) y = 0.1;
                          if(40. < y) y = 39.9; 
                        }
			*/
			fPosdep->Calibration(fCal, tower, x, y);
		}
		
		if (fRec->GetResultNumberOfHits(tower) > 1) {
			
			x1 = fRec->GetMHPosition(tower, t_layer[tower], 0, 0);
			y1 = fRec->GetMHPosition(tower, t_layer[tower], 1, 0);
			x2 = fRec->GetMHPosition(tower, t_layer[tower], 0, 1);
			y2 = fRec->GetMHPosition(tower, t_layer[tower], 1, 1);
			
			//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			/*
			if(tower ==0){
                          if(x1 < 0) x1 = 0.1; 
                          if(20 < x1) x1 = 19.9;
                          if(x2 < 0) x2 = 0.1; 
                          if(20 < x2) x2 = 19.9;
                          if(y1 < 0) y1 = 0.1;
                          if(20 < y1) y1 = 19.9;
                          if(y2 < 0) y2 = 0.1;
                          if(20 < y2) y2 = 19.9;
                        }
                        if(tower ==1){
                          if(x1 < 0) x1 = 0.1; 
                          if(40 < x1) x1 = 39.9;
                           if(x2 < 0) x2 = 0.1; 
                           if(40 < x2) x2 = 39,9;
                          if(y1 < 0) y1 = 0.1;
                          if(40 < y1) y1 = 39.9;
                          if(y2 < 0) y2 = 0.1;
                          if(40 < y2) y2 = 39.9;
                        }
			*/
			
			//if(fPos->GetHitNum(0)==0) printf("a1 = %0.1f, b1 = %0.1f, a2 = %0.1f, b2 = %0.1f\n", x1, y1, x2, y2);
			
			double pRep = 0;
			double qRep = 0;
			
			pRep += fRec->GetMHIntegral(tower, t_layer[tower], 0, 0);
			pRep += fRec->GetMHIntegral(tower, t_layer[tower], 1, 0);
			pRep += fRec->GetMHIntegral(tower, t_layer2[tower], 0, 0);
			pRep += fRec->GetMHIntegral(tower, t_layer2[tower], 1, 0);
			qRep += fRec->GetMHIntegral(tower, t_layer[tower], 0, 1);
			qRep += fRec->GetMHIntegral(tower, t_layer[tower], 1, 1);
			qRep += fRec->GetMHIntegral(tower, t_layer2[tower], 0, 1);
			qRep += fRec->GetMHIntegral(tower, t_layer2[tower], 1, 1);
			
			p             = pRep / (pRep + qRep);
			type2fraction = p;
			q             = 1 - p;
			
			fPosdep->Calibration(fCal, tower, p, q, x1, y1, x2, y2);
		}
	}
	
	return 0;
}

double A1Reconstruction::CalculateEnergyPhotonSimple(int tower) {
	// Simple energy Reconstruction for hit decision
	// Only shower leakage-out correction is applied
	
	if (fRec->GetResultNumberOfHits(tower) == 0) {
		return -1.;
	}
	
	double sum, sumc, x, y;
	x    = fRec->GetResultHitPosition(tower, 0);
	y    = fRec->GetResultHitPosition(tower, 1);
	sum  = fCal->calsum2(tower, 1, 12);
	sumc = sum;
	
	return EnergyConversionPhoton(tower, sumc);
}

int A1Reconstruction::ReconstructEnergyPhotonSingle(int tower) {
	
	// Energy Reconstruction for Single Tower Hit Events
	const int tower_nohit = (tower + 1) % 2;// Tower which has no hit.
	double    x, y;
	x = fRec->GetResultHitPosition(tower, 0);
	y = fRec->GetResultHitPosition(tower, 1);
	
	// Copy cal for non hit tower
	for (int il = 0; il < 16; il++) {
		fCal->cal[tower_nohit][il] = fCalOrg->cal[tower_nohit][il];
	}
	
	
	// Shower leakage in/out correction from only the hit tower.
	double sum[2], sumc[2];
	sum[tower]        = fCal->calsum2(tower, 1, 12);
	sumc[tower]       = sum[tower];
	sum[tower_nohit]  = fCal->calsum2(tower_nohit, 1, 12);
	sumc[tower_nohit] = sum[tower_nohit] - sumc[tower] * fLeakPhoton->GetLeakinFactor(1, tower, x, y);
	
	//cout << sumc[1] << endl;
	
	// Fill Results in A1Rec
	for (int tower = 0; tower < 2; tower++) {
		fRec->SetSumdE(tower, fCal->calsum2(tower, 0, 15));
		fRec->SetSumdE2(tower, sumc[tower]);
		fRec->SetResultEnergy(tower, A1Phys::ELEMAG, EnergyConversionPhoton(tower, sumc[tower]));
		// For the moment, even in hadron events the same conversion function is applied.
		// rec->SetResultEnergy(tower,A1Phys::HADRON, EnergyConversion(tower,sumc[tower]));
	}
	return 0;
}

int A1Reconstruction::ReconstructType2Pi0Photon(int tower) {
	
	// Reconstruct the energy as a single EM shower (shower leakage is already corrected as 2 hits)
	// The result is filled in Rec
	ReconstructEnergyPhotonSingle(tower);
	
	double Etotal, E1, E2, x1, x2, y1, y2;
	Etotal = fRec->GetResultEnergy(tower, 0);
	E1     = Etotal * type2fraction;
	E2     = Etotal * (1. - type2fraction);
	x1     = fRec->GetMHPosition(tower, t_layer[tower], 0, 0);
	y1     = fRec->GetMHPosition(tower, t_layer[tower], 1, 0);
	x2     = fRec->GetMHPosition(tower, t_layer[tower], 0, 1);
	y2     = fRec->GetMHPosition(tower, t_layer[tower], 1, 1);
	
	// Fill to rec
	fRec->SetType2Energy(tower, 0, E1);
	fRec->SetType2Energy(tower, 1, E2);
        
	fRec->SetTyep2Position(tower, 0, 0, x1);
	fRec->SetTyep2Position(tower, 1, 0, y1);
	fRec->SetTyep2Position(tower, 0, 1, x2);
	fRec->SetTyep2Position(tower, 1, 1, y2);
	
	return 0;
}

int A1Reconstruction::ReconstructEnergyPhotonDouble() {
	
	// Energy Reconstruction for Double Tower Hit Events
	double   x[2], y[2];
	double   sum[2], sumc[2];
	double   lo[2], li[2], det;
	for (int tower = 0; tower < 2; tower++) {
		x[tower] = fRec->GetResultHitPosition(tower, 0);
		y[tower] = fRec->GetResultHitPosition(tower, 1);
		
		sum[tower] = fCal->calsum2(tower, 1, 12);
		//    lo[tower]  = fLeakPhoton->GetFactor(1,tower,x[tower],y[tower]);
		lo[tower]  = 1.0; // makino 10.10.2015
		li[tower]  = fLeakPhoton->GetLeakinFactor(1, tower, x[tower], y[tower]);
	}
	
	// Shower leakage in/out correction for the both towers
	det = 1. / (lo[0] * lo[1] - li[0] * li[1]);
	sumc[0] = det * (sum[0] * lo[1] - sum[1] * li[0]);
	sumc[1] = det * (-1. * sum[0] * li[1] + sum[1] * lo[0]);
	
	// Fill Results in A1Rec
	for (int tower = 0; tower < 2; tower++) {
		fRec->SetSumdE(tower, fCal->calsum2(tower, 0, 15));
		fRec->SetSumdE2(tower, sumc[tower]);
		fRec->SetResultEnergy(tower, A1Phys::ELEMAG, EnergyConversionPhoton(tower, sumc[tower]));
	}
	
	return 0;
}

//int A1Reconstruction::ReconstructEnergyType2(int tower) {
//
//	// Light Yield & Shower Leakage-out corrections
//	CorrectionLightYieldType2();
//
//	// Energy Reconstruction for Single Tower Hit Events
//	const int tower_nohit = (tower + 1) % 2;// Tower which has no hit.
//	double    x, y;
//	x = fRec->GetResultHitPosition(tower, 0);
//	y = fRec->GetResultHitPosition(tower, 1);
//
//	// Copy cal for non hit tower
//	for (int il = 0; il < 16; il++) {
//		fCal->cal[tower_nohit][il] = fCalOrg->cal[tower_nohit][il];
//	}
//
//
//	// Shower leakage in/out correction from only the hit tower.
//	double sum[2], sumc[2];
//	sum[tower]        = fCal->calsum2(tower, 1, 12);
//	sumc[tower]       = sum[tower];
//	sum[tower_nohit]  = fCal->calsum2(tower_nohit, 1, 12);
//	sumc[tower_nohit] = sum[tower_nohit] - sumc[tower] * fLeakPhoton->GetLeakinFactor(1, tower, x, y);
//
//	//cout << sumc[1] << endl;
//
//	// Fill Results in A1Rec
//	for (int tower = 0; tower < 2; tower++) {
//		fRec->SetSumdE(tower, fCal->calsum2(tower, 0, 15));
//		fRec->SetSumdE2(tower, sumc[tower]);
//		fRec->SetResultEnergy(tower, A1Phys::ELEMAG, EnergyConversionPhoton(tower, sumc[tower]));
//		// For the moment, even in hadron events the same conversion function is applied.
//		// rec->SetResultEnergy(tower,A1Phys::HADRON, EnergyConversion(tower,sumc[tower]));
//	}
//	return 0;
//}

int A1Reconstruction::ReconstructEnergyHadron(int tower) {
	
	double sum, sumc, x, y;
	x    = fRec->GetResultHitPosition(tower, 0);
	y    = fRec->GetResultHitPosition(tower, 1);
	sum  = fCal->calsum2(tower, 2, 15);
	sumc = sum; // Shower leakage correction must be implemented here
	
	fRec->SetResultEnergy(tower, A1Phys::HADRON, EnergyConversionHadron(tower, sumc));
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
////                      FUNCTIONS GIVING PARAMETERS                         ////
//////////////////////////////////////////////////////////////////////////////////
double A1Reconstruction::EnergyConversionPhoton(int tower, double sumdE) {
	// [NOT FINALIZED YET]
	// From Suzuki's old study with old simulation by EPICS library.
	
	if (tower == 0)
	  return 1.1527 + 0.023877 / 0.744E-3 * sumdE;
	  //return 30.7494 * sumdE;
	if (tower == 1)
	  return 0.9585 + 0.020527 / 0.744E-3 * sumdE;
	  //return 27.4756 * sumdE;
	// Function used in LHCf analysis
	//    if (tower == 0)
	//        return 5.55112e-15 * sumdE * sumdE + 30.0259 * sumdE + 7.53553;
	//    if (tower == 1)
	//        return 5.55112e-14 * sumdE * sumdE + 26.3253 * sumdE + 5.0172;
	
	return 0.;
}

double A1Reconstruction::EnergyConversionHadron(int tower, double sumdE) {
	// [NOT FINALIZED YET]
	// Taken from Ueno's Master thesis.
	// Copy the one for TS to for TL
	
	if (tower == 0)
		return 88.9 * sumdE + 10.7;
	if (tower == 1)
		return 88.9 * sumdE + 10.7;
	
	return 0.;
}

double A1Reconstruction::PIDThresholdPhoton(int tower, double energy) {
	// [NOT OPTIMIZED YET]
	return 20.;
}

double A1Reconstruction::PIDThresholdHadron(int tower, double energy) {
	// [NOT OPTIMIZED YET]
	return 20.;
}


