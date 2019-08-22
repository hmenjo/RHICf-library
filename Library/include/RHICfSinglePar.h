#ifndef RHICFSINGLEPAR_H
#define RHICFSINGLEPAR_H

#include <TNamed.h>
#include <TVector2.h>
#include <TLorentzVector.h>
#include <TString.h>

#include "globaldef.h"

class RHICfSinglePar : public TNamed{

	public: 
		RHICfSinglePar();
		RHICfSinglePar(char* name, char* title);
		~RHICfSinglePar();

		void setTower(int it);
		void setId(unsigned int id);
		void setPosition(double x, double y);
		void setEnergy(double E);
		void setPid(TString pid);
		void setBeamCenter(double x0, double y0);

		int tower();
		unsigned int id();
		double energy();
		TLorentzVector fourmomentum();
		TVector2 position();
		TString pid();
		double pT();
		double eta();
		double phi();

		Bool_t           fIsInfiducial;

	private:
		Bool_t           fIsBeamCenter;
		Int_t            fTower;
		UInt_t           fId;
		TLorentzVector   fFourMomentum;
		TVector2         fPosition;// Coordinate origin is the center of TS.
		Double_t         fEnergy;
		TString          fPid;

		ClassDef(RHICfSinglePar, 1)	
};
#endif
