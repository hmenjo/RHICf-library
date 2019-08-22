#include "RHICfCollection.h"

#include <TLorentzVector.h>
#include <TVector2.h>

#include <iostream>

ClassImp(RHICfCollection)

using namespace std;

RHICfCollection::RHICfCollection(){}
RHICfCollection::RHICfCollection(char* name, char* title) : TNamed(name, title), fIsPhotonPair(false){}
RHICfCollection::~RHICfCollection(){}

void RHICfCollection::Initialize(){

	fEventInfo = new RHICfEventInfo();
	fSinglePars.SetClass("RHICfSinglePar", 0);
	fPhotonPairs.SetClass("RHICfPhotonPair", 0);
}

//================================ SET ================================//
void RHICfCollection::addSinglePars(TClonesArray pars){ fSinglePars = pars; }
void RHICfCollection::addPhotonPairs(TClonesArray pairs){ fPhotonPairs = pairs; }
void RHICfCollection::addEventInfo(RHICfEventInfo* info){ fEventInfo = info; }

void RHICfCollection::setBeamCenter(double x0, double y0){

	for(int ipar=0; ipar<npars(); ipar++){

		RHICfSinglePar* par = (RHICfSinglePar*)fSinglePars.ConstructedAt(ipar);
		par -> setBeamCenter(x0, y0);
	}
	if(fIsPhotonPair){
		for(int ipair=0; ipair<npairs(); ipair++){

			RHICfPhotonPair* pair = (RHICfPhotonPair*)fPhotonPairs.ConstructedAt(ipair);
			RHICfSinglePar* photon1 = (RHICfSinglePar*)fSinglePars.ConstructedAt(pair->id1());
			RHICfSinglePar* photon2 = (RHICfSinglePar*)fSinglePars.ConstructedAt(pair->id2());
			TLorentzVector mom1 = photon1 -> fourmomentum();
			TLorentzVector mom2 = photon2 -> fourmomentum();
			pair -> setFourMomentum(mom1+mom2);
			pair -> fIsBeamCenter = true;
		}
	}
}
void RHICfCollection::setInfo(int runnumber, int evtnumber, TString trgtype, int bunchid, TString runtype, TString quality){

	fRunNumber = runnumber;
	fEventNumber = evtnumber;
	fTriggerType = trgtype;
	fBunchId = bunchid;
	fRunType = runtype;
	fEventQuality = quality;
}

//================================ GET ================================//
TClonesArray RHICfCollection::singlepars(){ return fSinglePars; }
TClonesArray RHICfCollection::photonpairs(){ return fPhotonPairs; }
RHICfEventInfo* RHICfCollection::eventinfo(){ return fEventInfo; }

unsigned int RHICfCollection::npars(){ return fSinglePars.GetEntries(); }
unsigned int RHICfCollection::npairs(){ return fPhotonPairs.GetEntries(); }
int RHICfCollection::runnumber(){ return fRunNumber; }
int RHICfCollection::evtnumber(){ return fEventNumber; }
TString RHICfCollection::trigger(){ return fTriggerType; }
int RHICfCollection::bunchid(){ return fBunchId; }
TString RHICfCollection::runtype(){ return fRunType; }
TString RHICfCollection::quality(){ return fEventQuality; }

void RHICfCollection::clear(){

	fEventInfo -> clear();
	fSinglePars.Clear();
	fPhotonPairs.Clear();

	fIsPhotonPair = false;
}


