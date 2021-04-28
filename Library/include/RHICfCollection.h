#ifndef RHICFCOLLECTION_H
#define RHICFCOLLECTION_H

#include <TNamed.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "globaldef.h"
#include "RHICfSinglePar.h"
#include "RHICfPhotonPair.h"
#include "A1Rec1.h"

class RHICfSinglePar;
class RHICfPhotonPair;
class A1Rec1;

typedef A1Rec1 RHICfEventInfo;

class RHICfCollection : public TNamed{

	public: 
		RHICfCollection();
		RHICfCollection(char* name, char* title);
		~RHICfCollection();

		void Initialize();

		void addSinglePars(TClonesArray pars);
		void addPhotonPairs(TClonesArray pairs);
		void addEventInfo(RHICfEventInfo* info);

		void setBeamCenter(double x0, double y0);
		void setInfo(int runnumber, int evtnumber, TString trgtype, int bunchid, TString runtype, TString quality);

		TClonesArray singlepars();
		TClonesArray photonpairs();
		RHICfEventInfo* eventinfo();

		unsigned int npars();
		unsigned int npairs();
		int          runnumber();
		int          evtnumber();
		TString      trigger();
		int          bunchid();
		TString      runtype();
		TString      quality();

		void clear();

		Bool_t fIsPhotonPair;

	private:
		TClonesArray    fSinglePars;
		TClonesArray    fPhotonPairs;
		RHICfEventInfo* fEventInfo;

		UInt_t     fNumOfPars;
		UInt_t     fNumOfPairs;

		Int_t      fRunNumber;
		Int_t      fEventNumber;
		TString    fTriggerType;
		Double_t   fBunchId;
		TString    fRunType;
		TString    fEventQuality;

		ClassDef(RHICfCollection, 1)
};

#endif
