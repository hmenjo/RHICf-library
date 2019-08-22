#ifndef RHICFPHOTONPAIR_H
#define RHICFPHOTONPAIR_H

#include <iostream>

#include <TNamed.h>
#include <TLorentzVector.h>

#include "globaldef.h"

using namespace std;

class RHICfPhotonPair : public TNamed{

	public: 
		RHICfPhotonPair();
		~RHICfPhotonPair();
	
		void Initialize();

		void setPi0Type(int type);
		void setEnergy(double E);
		void setFourMomentum(TLorentzVector mom);
		void setPhotonId(unsigned int id1, unsigned int id2);

		int pi0type();
		double energy();
		TLorentzVector fourmomentum();
		double invarmass();
		double pT();
		double eta();
		double phi();
		unsigned id1();
		unsigned id2();

		void clear();

		Bool_t            fIsBeamCenter;

	private:
		Int_t             fPi0Type;
		Double_t          fEnergy;
		TLorentzVector    fFourMomentum;
	 	Double_t          fInvarMass;
		UInt_t            fNumOfPars;
		UInt_t            fPhotonId[2];

		ClassDef(RHICfPhotonPair, 1)
};
#endif
