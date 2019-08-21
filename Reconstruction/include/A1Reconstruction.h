//
// Created by MENJO Hiroaki on 2017/05/24.
//

#ifndef A1RECONSTRUCTION_H
#define A1RECONSTRUCTION_H

#include <TString.h>
#include <TCanvas.h>

#include <A1Cal2M.h>
#include <RHICfPhys.h>
#include <RHICfRec1.h>
#include <ParticleID01.h>
#include <ConShowerLeakage.h>
#include <ScintiPosDepGSO.h>
#include <GSObarPosCalc.h>

typedef RHICfRec1 RHICfRec;
class A1Reconstruction {

public:
		A1Cal2M  *fCal;
		A1Cal2M  *fCalOrg;
		RHICfRec *fRec;
		GSObarPosCalc *fPos;
		
		ParticleID01     *fPid;            // calculation of L20, L90
		ConShowerLeakage *fLeakPhoton;     // table of shower leakage
		ConShowerLeakage *fLeakHadron;     // table of shower leakage
		ScintiPosDepGSO  *fPosdep;         // table of light yield correction
		
		double  paramHitPeakThreshold;
		double  paramHitdEThreshold;
		double  paramSumdEThreshold;
		TString paramGSOLY20mm;
		TString paramGSOLY40mm;
		TString paramShowerLeakagePhoton;
		TString paramShowerLeakageHadron;
		TString paramGSObarPosition;


public:
		A1Reconstruction();
		~A1Reconstruction();
		
		void Initialize();

		void SetRunType(TString run);
                int SetData(A1Cal2M *cal);
		
		RHICfRec *GetRec() { return fRec; }

		int FillEventInfo();

		int Reconstruct();
		int ReconstructHitPosition();
		int ReconstructPID();
		int ReconstructEnergy();
		int CorrectionLightYieldPhoton();
		int ReconstructEnergyPhotonSingle(int tower);
		int ReconstructEnergyPhotonDouble();
		int ReconstructType2Pi0Photon(int tower);
		int ReconstructEnergyHadron(int tower);

		void GetScan(TCanvas* c, int TSlayer, int TLlyaer, int iev);
                int  GetScanNum(int TShit, int TLhit) { return scanNum[TShit][TLhit]; };

private:
		int bunchoffset;

                int scanNum[3][3];
                int t_layer[2];// Maximum energy deposit layer
                int t_layer2[2];// Second maximum energy deposit layer
                double L20[2];
                double L90[2];

                bool Isruntype;
                TString runtype;
                bool Isbunchoffset;

		double EnergyConversionPhoton(int tower, double sumdE);
		double EnergyConversionHadron(int tower, double sumdE);
		
		double PIDThresholdPhoton(int tower, double energy);
		double PIDThresholdHadron(int tower, double energy);
};


#endif //A1RECONSTRUCTION_H
