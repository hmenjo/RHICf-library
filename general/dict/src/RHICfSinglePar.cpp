#include "RHICfSinglePar.h"

#include <iostream>

using namespace std;

ClassImp(RHICfSinglePar)

RHICfSinglePar::RHICfSinglePar(){}
RHICfSinglePar::RHICfSinglePar(char* name, char* title) : TNamed(name, title), fIsBeamCenter(false){}
RHICfSinglePar::~RHICfSinglePar(){}

//================================ SET ================================//
void RHICfSinglePar::setTower(int it){ fTower = it; }
void RHICfSinglePar::setId(unsigned int id) { fId = id; }
void RHICfSinglePar::setPosition(double x, double y){ fPosition.Set(x, y); }
void RHICfSinglePar::setEnergy(double E) { fEnergy = E; }
void RHICfSinglePar::setPid(TString pid){ fPid = pid; }
void RHICfSinglePar::setBeamCenter(double x0, double y0){

	double z = 18000;
	double x = fPosition.X() - x0;
	double y = fPosition.Y() - y0;
	double E = fEnergy;
	double r = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	fFourMomentum.SetPxPyPzE((x/r)*E, (y/r)*E, (z/r)*E, E);

	fIsBeamCenter = true;
}

//================================ GET ================================//
double RHICfSinglePar::energy(){ return fEnergy; }
TLorentzVector RHICfSinglePar::fourmomentum(){

	if(fIsBeamCenter) return fFourMomentum;
	else{
		cerr << "RHICfSinglePar::fourmomentum - Beam center is NOT set" << endl;
                fFourMomentum.SetPxPyPzE(-1, -1, -1, -1);
		return fFourMomentum;
	}
}
double RHICfSinglePar::pT(){

	if(fIsBeamCenter) return fFourMomentum.Pt();
	else{
		cerr << "RHICfSinglePar::pT - Beam center is NOT set" << endl;
		return -1;
	} 
}
double RHICfSinglePar::eta(){

        if(fIsBeamCenter) return fFourMomentum.Eta();
        else{
                cerr << "RHICfSinglePar::eta - Beam center is NOT set" << endl;
                return -1;
        }
}
double RHICfSinglePar::phi(){

        if(fIsBeamCenter) return fFourMomentum.Phi();
        else{
                cerr << "RHICfSinglePar::phi - Beam center is NOT set" << endl;
                return -1;
        }
}
int RHICfSinglePar::tower(){ return fTower; }
unsigned RHICfSinglePar::id() { return fId; }
TVector2 RHICfSinglePar::position(){ return fPosition; }
TString RHICfSinglePar::pid(){ return fPid; }
