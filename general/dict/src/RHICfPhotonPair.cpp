#include "RHICfPhotonPair.h"

ClassImp(RHICfPhotonPair)

RHICfPhotonPair::RHICfPhotonPair() : fIsBeamCenter(false){}
RHICfPhotonPair::~RHICfPhotonPair(){}

void RHICfPhotonPair::Initialize(){}

//================================ SET ================================//
void RHICfPhotonPair::setPi0Type(int type){ fPi0Type = type; }
void RHICfPhotonPair::setEnergy(double E){ fEnergy = E; }
void RHICfPhotonPair::setFourMomentum(TLorentzVector mom){ 
	
	fFourMomentum = mom; 
	fIsBeamCenter = true;
}
void RHICfPhotonPair::setPhotonId(unsigned int id1, unsigned int id2){

	fPhotonId[0] = id1;
	fPhotonId[1] = id2;
}

//================================ GET ================================//
int RHICfPhotonPair::pi0type(){ return fPi0Type; }
double RHICfPhotonPair::energy(){ return fEnergy; }
TLorentzVector RHICfPhotonPair::fourmomentum(){

        if(fIsBeamCenter) return fFourMomentum;
        else{
                cerr << "RHICfPhotonPair::fourmomentum - Beam center is NOT set" << endl;
                fFourMomentum.SetPxPyPzE(-1, -1, -1, -1);
                return fFourMomentum;
        }
}
double RHICfPhotonPair::pT(){

        if(fIsBeamCenter) return fFourMomentum.Pt();
        else{
                cerr << "RHICfPhotonPair::pT - Beam center is NOT set" << endl;
                return -1;
        }
}
double RHICfPhotonPair::eta(){

        if(fIsBeamCenter) return fFourMomentum.Eta();
        else{
                cerr << "RHICfPhotonPair::eta - Beam center is NOT set" << endl;
                return -1;
        }
}
double RHICfPhotonPair::phi(){

        if(fIsBeamCenter) return fFourMomentum.Phi();
        else{
                cerr << "RHICfPhotonPair::phi - Beam center is NOT set" << endl;
                return -1;
        }
}
double RHICfPhotonPair::invarmass(){

	if(fIsBeamCenter){
		TLorentzVector p = fFourMomentum;
		return sqrt(pow(p.E(),2) - pow(p.Px(),2) - pow(p.Py(),2) - pow(p.Pz(),2));
	}
        else{
                cerr << "RHICfPhotonPair::invarmass - Beam center is NOT set" << endl;
                return -1; 
        } 
}
unsigned int RHICfPhotonPair::id1(){ return fPhotonId[0]; }
unsigned int RHICfPhotonPair::id2(){ return fPhotonId[1]; }

void RHICfPhotonPair::clear(){}
