//
// Created by MENJO Hiroaki on 2017/05/24.
//

#include "A1Calibration.h"
#include "../include/A1Calibration.h"

A1Calibration::A1Calibration() : paramPedestalFile("") {
	return;
}

A1Calibration::~A1Calibration() {
	return;
}

int A1Calibration::Initalize() {
	
	// Outputs
	fCal1 = new A1Cal1("a1cal", "");
	fCal2 = new A1Cal2M("a1cal2", "");
		
	// Functions
	fRawToCal1 = new A1RawToCal1();
	fRawToCal1->ReadScifiPosTable((char *) paramMAPMTtable.Data());
	
	fPedeSubtract = new A1PedeSubtract();
	fPedeSubtract->ReadFile((char *) paramPedestalFile.Data());
	fPedeSubtract->ReadAveFile((char *) paramAvePedestalFile.Data());
	fPedeSubtract->SetAccumNEvent(-1);
	
	fCal1ToCal2 = new A1Cal1ToCal2();
	fCal1ToCal2->ReadADCRangeTable((char *) paramAdcrange.Data());
	fCal1ToCal2->UseADCRange(false);
	fCal1ToCal2->SetADCRangeThreshold(paramAdcrangeThreshold);
	
	fGainCalibration = new A1GainCalibration();
	fGainCalibration->ReadParticleDefineTable((char *) paramConversionTable.Data());
	fGainCalibration->ReadPMTGainTable((char *) paramHVgainTable.Data());
	fGainCalibration->ReadHVTable((char *) paramHvtable.Data());
	fGainCalibration->SetPdefFactorPMT(paramAttenuation);
	fGainCalibration->ReadScifiGainTable((char *) paramGSObarHVtable.Data());
	
	fPmtSatu = new PMTSatuCorrection();
	if (paramPMTsaturationCollection) {
		fPmtSatu->Initialize((char *) paramPMTSatuPath.Data(), (char *) paramPMTSatuFile.Data());
		fPmtSatu->ReadHVTable(fGainCalibration);
	}
	
	fCrossTalk = new A1LHCCrossTalk();
	fCrossTalk->CTReadFile((char *) paramGSObarCrossTalk.Data());
	
	return 0;
}

int A1Calibration::SetPedestalFile(const char *filename) {
	paramPedestalFile = filename;
	return 0;
}
int A1Calibration::SetAvePedestalFile(const char *filename) {
       paramAvePedestalFile = filename;
       return 0;
}

int A1Calibration::SetupDefault_RHICfOp2017() {
	dirLibrary                   = LIBDIR;       // LIBDIR is defined in Makefile
	//paramPedestalFile            = "";           // No default file
	paramConversionTable         = dirLibrary + "/tables/conversion_factor_RHIC_pp_bar_op_plate.tab";
	paramHVgainTable             = dirLibrary + "/tables/GainTable_Fit_20170427.txt";
	paramHvtable                 = dirLibrary + "/config/hvtable_rhicf2017_normal.txt";
	paramGSObarHVtable           = dirLibrary + "/tables/MAPMTgaintable_20170501.txt";
	paramAdcrange                = dirLibrary + "/tables/adcrange_002_100412.dat";
	paramAdcrangeThreshold       = 3600.;
	paramAttenuation             = 0.908;  // [NOT FIXED] 0.908 is for LHC 2015.
	paramPMTsaturationCollection = kFALSE; // For new detectors, kFALSE
	paramPMTSatuPath             = "";
	paramPMTSatuFile             = "";
	paramGSObarCrossTalk         = dirLibrary + "/tables/20141215_XtalkMatrixTemplate.root";
	paramMAPMTtable              = dirLibrary + "/tables/GSObar_map9.tab";
	
	return 0;
}

int A1Calibration::Calculate(TObject *raw) {
	
	TString cname = raw->ClassName();
	// For Experimental data ---
	if (cname == "RHICfRaw_Op2017") {
		// Format conversion from raw to fCal1
		fRawToCal1->Convert(raw, fCal1);
	}
	// For MC -----
	if (cname == "A1Cal1"){
		// Copy
		fCal1->copy((A1Cal1*)raw);
	}
	
	// Combine the values of dual-range ADC [WRADC->LRADC]
	fCal1ToCal2->CalculateADC(fCal1);
	
	// Pedestal Subtruction
	fPedeSubtract->RHICfSubtract(fCal1);
	
	// Conversion from Cal1 to Cal2
	fCal1ToCal2->Convert(fCal1, fCal2);
	
	// Correction of PMT Saturation
	if (paramPMTsaturationCollection)
		fPmtSatu->Calculate(fCal2);
	
	// Gain Calibraion (ADC->dE)
	fGainCalibration->Calculate(fCal2);
	
	// CrossTalk Correction for GSO bars
	fCrossTalk->CalibCrossTalk_wM(fCal2);
	
	return 0;
}

