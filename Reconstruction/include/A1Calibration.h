//
// Created by MENJO Hiroaki on 2017/05/24.
//

#ifndef A1CALIBRATION_H
#define A1CALIBRATION_H

#include <TString.h>

#include <A1Cal1.h>
#include <A1Cal2M.h>

#include <A1RawToCal1.h>
#include <A1PedeSubtract.h>
#include <A1Cal1ToCal2.h>
#include <PMTSatuCorrection.h>
#include <A1LHCCrossTalk.h>
#include <A1GainCalibration.h>

class A1Calibration {

public:
		// Parameters
		TString  dirLibrary;
		TString  paramPedestalFile;
		TString  paramAvePedestalFile;
		TString  paramConversionTable;
		TString  paramHVgainTable;
		TString  paramHvtable;
		TString  paramGSObarHVtable;
		TString  paramAdcrange;
		Double_t paramAdcrangeThreshold;
		Double_t paramAttenuation;
		Bool_t   paramPMTsaturationCollection;
		TString  paramPMTSatuPath;
		TString  paramPMTSatuFile;
		TString  paramGSObarCrossTalk;
		TString  paramMAPMTtable;
		
		// Functions
		A1RawToCal1       *fRawToCal1;
		A1PedeSubtract    *fPedeSubtract;
		A1Cal1ToCal2      *fCal1ToCal2;
		A1GainCalibration *fGainCalibration;
		PMTSatuCorrection *fPmtSatu;
		A1LHCCrossTalk    *fCrossTalk;
		
		// Outputs
		A1Cal1  *fCal1;
		A1Cal1  *fCal1tmp;
		A1Cal2M *fCal2;

public:
		A1Calibration();
		~A1Calibration();
		int Initalize();
		int SetPedestalFile(const char *filename);
		int SetAvePedestalFile(const char *filename);
		int SetupDefault_RHICfOp2017();
		int Calculate(TObject *raw);
		
		A1Cal1 *GetCal1() { return fCal1; }
		A1Cal1 *GetCal1tmp() { return fCal1tmp; }
		A1Cal2M *GetCal2() { return fCal2; }
	
	
};


#endif //A1CALIBRATION_H
