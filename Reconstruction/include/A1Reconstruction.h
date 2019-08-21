//==================================================//
//                                                  //
//  - Created by MENJO Hiroaki on 2017/05/24.       //
//                                                  //
//  - First edition by Minho Kim on                 //
//                                                  //
//==================================================//

#ifndef A1RECONSTRUCTION_H
#define A1RECONSTRUCTION_H

#include "A1Cal2M.h"
//#include "A1Rec1.h"
#include <RHICfPhys.h>
#include <RHICfRec1.h>
#include "ParticleID01.h"
#include "ConShowerLeakage.h"
#include "ScintiPosDepGSO.h"
#include "GSObarPosCalc.h"

#include <TString.h>
#include <TCanvas.h>

//typedef A1Rec1 A1Rec;
typedef RHICfRec1 RHICfRec;

class A1Reconstruction{

	public:
		A1Cal2M *fCal;
		A1Cal2M *fCalOrg;
		//A1Rec *fRec;
		RHICfRec* fRec;
		GSObarPosCalc* fPos;

		ParticleID01 *fPid;// Calculation of L20, L90.
		ConShowerLeakage *fLeakPhoton;// Shower leakage-in correction.
		ConShowerLeakage *fLeakHadron;//
		ScintiPosDepGSO *fPosdep;// Shower leakage-out correction.

		TString paramGSOLY20mm;
		TString paramGSOLY40mm;
		TString paramGSOLY20mmHadron;
		TString paramGSOLY40mmHadron;
		TString paramShowerLeakagePhoton;
		TString paramShowerLeakageHadron;
		TString paramGSObarPosition;

	public:
		A1Reconstruction();
		~A1Reconstruction();

		int Initialize();

		void SetRunType(TString run);
		int SetData(A1Cal2M *cal);

		RHICfRec* GetRec(){ return fRec; }

		int FillEventInfo();

		int Reconstruct();
		int ReconstructHitPosition();
		int ReconstructPID();
		int ReconstructEnergy();
		int CorrectionLightYieldPhoton();
		int ReconstructEnergyPhotonSingle(int tower);
		int ReconstructEnergyPhotonDouble();
		int ReconstructEnergyHadron(int tower);

		void GetScan(TCanvas* c, int TSlayer, int TLlyaer, int iev);
		int  GetScanNum(int TShit, int TLhit) { return scanNum[TShit][TLhit]; };

		double GetGPosX_Detector(int tower, double a, double b);
		double GetGPosY_Detector(int tower, double a, double b);

		bool IsInFiducial(int tower, double a, double b);

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
};
#endif //A1RECONSTRUCTION_H
