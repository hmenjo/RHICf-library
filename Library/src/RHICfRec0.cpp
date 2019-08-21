#ifndef __RHICfREC0_CPP__
#define __RHICfREC0_CPP__

#include "RHICfRec0.h"

//----------------------------------------------------------------------
// Base class for reconstruction parameters.
// 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(RHICfRec0);
#endif

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// -------------------------------------------------------------------
// -----                     DEFINITIONS                         -----
// -------------------------------------------------------------------

#define  REC_FORMAT     0
#define  SIZE_EVINFO    0
#define  SIZE_FLAGS     0
#define  SIZE_REC       0
#define  SIZE_CAL       0
#define  SIZE_POS       0
#define  SIZE_PID       0
#define  SIZE_TDC       0
#define  SIZE_COUNTER   0

// -------------------------------------------------------------------
// -----             CONSTRUCTOR/DESTORACTOR                     -----
// -------------------------------------------------------------------
RHICfRec0::RHICfRec0(){
	clear();
};

RHICfRec0::RHICfRec0(char* name, char *title) : TNamed(name,title){
	clear();
}

RHICfRec0::~RHICfRec0(){;}

int  RHICfRec0::resize(){
	format = REC_FORMAT;
	resize(evinfo,  SIZE_EVINFO);
	resize(flags,   SIZE_FLAGS);
	resize(rec,     SIZE_REC);
	resize(cal,     SIZE_CAL);
	resize(pos,     SIZE_POS);
	resize(pid,     SIZE_PID);
	resize(tdc,     SIZE_TDC);
	resize(counter, SIZE_COUNTER);
	clear();
	return 0;
}

int  RHICfRec0::clear(){
	// Clear all data
	run     = 0;
	number  = 0;
	gnumber = 0;
	time[0] = 0;
	time[1] = 0;

	clear(evinfo,   0);
	clear(flags,    0);
	clear(rec,      0.);
	clear(cal,      0.);
	clear(pos,      0.);
	clear(pid,      0.);
	clear(tdc,      0.);
	clear(counter,  0.);
	return 0;
}

int RHICfRec0::copy(RHICfRec0* d){
	// Copy data, name and title of "d" to "this"

	this->SetName(d->GetName());
	this->SetTitle(d->GetTitle());
	return copydata(d);
}

int RHICfRec0::copydata(RHICfRec0* d){
	// Copy only data of "d" to "this"

	this->run     = d->run;
	this->number  = d->number;
	this->gnumber = d->gnumber;
	this->time[0] = d->time[0];
	this->time[1] = d->time[1];

	copy(this->evinfo, d->evinfo);
	copy(this->flags,  d->flags);
	copy(this->rec,    d->rec);
	copy(this->cal,    d->cal);
	copy(this->pos,    d->pos);
	copy(this->pid,    d->pid);
	copy(this->tdc,    d->tdc);
	copy(this->counter,d->counter);

	return 0;
}

int RHICfRec0::FillToPhys(RHICfPhys* phys){
	// Fill recommended results to phys

	// Clear the "phys" buffer
	phys->clear();

	phys->run     = this->run;
	phys->gnumber = this->gnumber;
	phys->number  = this->number;
	phys->time[0] = this->time[0];
	phys->time[1] = this->time[1];

	// Fill Flag
	phys->flag[0] = GetFlags(0);
	phys->flag[1] = GetFlags(1);
	phys->flag[2] = GetFlags(2);

	// Fill Hit Position
	for(int it=0;it<2;it++){
		phys->hits[it] = GetResultNumberOfHits(it);

		if(phys->hits[it]>0){
			for(int ixy=0;ixy<2;ixy++){
				phys->pos[it][ixy] = GetResultHitPosition(it,ixy);
			}
		}
	}

	// Fill PID Result
	for(int it=0;it<2;it++){
		phys->pid[it] = GetResultPID(it);
	}

	// Fill Reconstructed Energy 
	for(int it=0;it<2;it++){
		//if( phys->hits[it] ){
		phys->energy[it] = GetResultEnergy(it,phys->pid[it]);
		//}
	}

	return 0;
}

void RHICfRec0::Show(){
	cout << " ===========      RECONSTRUCTION     ============" << endl;
	//cout << " NAME: " << setw(10) << GetName() << "     "
	//     << " TITLE: " << GetTitle() << endl;
	cout << " RUN: " << setw(6) << run << "    "
		<< "GNUMBER: " << setw(7) << gnumber << "  "
		<< "NUMBER: " << setw(7) << number << "   "
		<< endl;

	return ;
}

// -------------------------------------------------------------------
// -----                 INTERNAL FUNCTIONS                      -----
// -------------------------------------------------------------------

void RHICfRec0::resize(vector<int> &v, int size){
	v.clear();
	v.resize(size);
}

void RHICfRec0::resize(vector<unsigned int> &v, int size){
	v.clear();
	v.resize(size);
}

void RHICfRec0::resize(vector<double> &v, int size){
	v.clear();
	v.resize(size);
}

void RHICfRec0::clear(vector<int> &v, int value){
	for(int i=0;i<(int)v.size();i++){  v[i] = value; }
}

void RHICfRec0::clear(vector<unsigned int> &v, unsigned int value){
	for(int i=0;i<(int)v.size();i++){  v[i] = value; }
}

void RHICfRec0::clear(vector<double> &v, double value){
	for(int i=0;i<(int)v.size();i++){  v[i] = value; }
}

void RHICfRec0::copy(vector<int> &v, vector<int> &d){
	if(v.size() < d.size()){
		resize(v, d.size());
	}
	for(int i=0;i<(int)d.size();i++){
		v[i] = d[i];
	}
}

void RHICfRec0::copy(vector<unsigned int> &v, vector<unsigned int> &d){
	if(v.size() < d.size()){
		resize(v, d.size());
	}
	for(int i=0;i<(int)d.size();i++){
		v[i] = d[i];
	}
}

void RHICfRec0::copy(vector<double> &v, vector<double> &d){
	if(v.size() < d.size()){
		resize(v, d.size());
	}
	for(int i=0;i<(int)d.size();i++){
		v[i] = d[i];
	}
}

// -------------------------------------------------------------------
// -----                INTERFACE FUNCTIONS                      -----
// -------------------------------------------------------------------
// ================== Event Information =================  
// From evinfo  
// Event Quality flag 
int    RHICfRec0::GetEventQuality(){return 0;}
void   RHICfRec0::SetEventQuality(int d){;}
// Beam Colliding flag
int    RHICfRec0::GetBeamColConf(){ return 0;}
void   RHICfRec0::SetBeamColConf(int d){;}
// Bunch Number (RHICf or STAR)
int    RHICfRec0::GetBunchNumber(int ib){ return 0;}
void   RHICfRec0::SetBunchNumber(int ib,int d){;}
// =====================  Flags =========================
// From flags
// Flag from GPIO's (i-th)
unsigned int RHICfRec0::GetFlags(int i){ return 0;}
void         RHICfRec0::SetFlags(int i, unsigned int d){;}
// Analysis Flags 
// Analysis flag (i-th)
unsigned int RHICfRec0::GetAnalysisFlags(int i){return 0;}
void         RHICfRec0::SetAnalysisFlags(int i, unsigned int d){;}

// *** Newly developed for RHICf *** //

bool RHICfRec0::IsShowerTrig() { return true; }
bool RHICfRec0::IsPi0Trig() { return true; }
bool RHICfRec0::IsHighEMTrig() { return true; }

// =============== Reconstruction ======================
// From rec
// Recommended reconstructed energy (tower)
double RHICfRec0::GetResultEnergy(int it){
	if(GetResultPID(it)==RHICfPhys::HADRON){
		return GetResultEnergy(it,RHICfPhys::HADRON);
	}
	else{
		return GetResultEnergy(it,RHICfPhys::ELEMAG);
	}
}
// Recommended reconstructed energy (tower, pid)
double RHICfRec0::GetResultEnergy(int it,int pid){return 0.;}
void   RHICfRec0::SetResultEnergy(int it,int pid,double d){;}
// Sum dE(layer=0-15) (tower)
double RHICfRec0::GetSumdE(int it){ return 0;}
void   RHICfRec0::SetSumdE(int it,double d){;}
// Sum dE(layer=1-12) (tower)
double RHICfRec0::GetSumdE2(int it){ return 0;}
void   RHICfRec0::SetSumdE2(int it,double d){;}
// Shower Leakage parameter (tower)
double RHICfRec0::GetLeakageOut(int it){ return 0;}
void   RHICfRec0::SetLeakageOut(int it,double d){;}
// Correction factor of light yield (tower, layer)
double RHICfRec0::GetLightYield(int it, int il){ return 0;}
void   RHICfRec0::SetLightYield(int it, int il, double d){;}
// Correction factor of energy scale (tower)
double RHICfRec0::GetEnergyScaleFactor(int it){return 0.;}
void   RHICfRec0::SetEnergyScaleFactor(int it,double d){;}
double RHICfRec0::GetType2Energy(int it, int hit){return 0.;}
void   RHICfRec0::SetType2Energy(int it, int hit, double d){;}
double RHICfRec0::GetTyep2Position(int it, int ixy, int hit){return 0;}
void   RHICfRec0::SetTyep2Position(int it, int ixy, int hit, double d){;}
// ================= Calorimer =========================
// From cal 
// Calorimeter dE (tower, layer)
double RHICfRec0::GetCal(int it, int il){ return 0;}
void   RHICfRec0::SetCal(int it, int il, double d){;}
// FC dE (arm, channel)
double RHICfRec0::GetFC(int iarm,int ich){ return 0;}
void   RHICfRec0::SetFC(int iarm,int ich,double d){;}
// Transition fit results
double RHICfRec0::GetTFitParam(int tower, int ipar){return 0.;}
void   RHICfRec0::SetTFitParam(int tower, int ipar, double val){;}
double RHICfRec0::GetTFitParamCorr(int tower, int ipar){return 0.;}
void   RHICfRec0::SetTFitParamCorr(int tower, int ipar, double val){;}
double RHICfRec0::GetTFitParamLeakin(int tower, int ipar){return 0.;}
void   RHICfRec0::SetTFitParamLeakin(int tower, int ipar, double val){;}
double RHICfRec0::GetTScale(int tower){return 0.;}
double RHICfRec0::GetTScaleCorr(int tower){return 0.;}
double RHICfRec0::GetTScaleLeakin(int tower){return 0.;}
double RHICfRec0::GetTMax(int tower){return 0.;}
double RHICfRec0::GetTMaxCorr(int tower){return 0.;}
double RHICfRec0::GetTMaxLeakin(int tower){return 0.;}
// ================== Position ========================
// From pos
// Recommended hit position results 
double RHICfRec0::GetResultHitPosition(int it, int ixy){return -1.;}
void   RHICfRec0::SetResultHitPosition(int it, int ixy,double d){;}
// Recommended number of hit results (tower)
int    RHICfRec0::GetResultNumberOfHits(int it){return 0;}
void   RHICfRec0::SetResultNumberOfHits(int it, int d){;}
// Number of Hits in the tower (tower,layer,xy)
int    RHICfRec0::GetNumberOfHits(int it,int il,int ixy){ return 0;}
void   RHICfRec0::SetNumberOfHits(int it,int il,int ixy, int d){;}
// Hit Position in each layer (tower,layer,xy)
double RHICfRec0::GetHitPosition(int it,int il,int ixy){ return 0.;}
void   RHICfRec0::SetHitPosition(int it,int il,int ixy, double d){;}
// Strip number with maximum dE (tower,layer,xy)
double RHICfRec0::GetPeakStrip(int it,int il,int ixy){ return 0;}
void   RHICfRec0::SetPeakStrip(int it,int il,int ixy, double d){;}
// dE at peak (tower,layer,xy)
double RHICfRec0::GetdEAtPeak(int it,int il,int ixy){ return 0;}
void   RHICfRec0::SetdEAtPeak(int it,int il,int ixy,double d){;}
// Saturation flag of silicon middle sample
int    RHICfRec0::GetSiSatuFlag(int it,int il,int ixy){ return 0;}
void   RHICfRec0::SetSiSatuFlag(int it,int il,int ixy,int d){;}
// Results of Background Fitting by a linear function
double RHICfRec0::GetMHBkgPar(int layer, int xy, int ipar){return 0.;}
void   RHICfRec0::SetMHBkgPar(int layer, int xy, int ipar, double val){;}
// Number of Hits in the layer (layer, xy)
int    RHICfRec0::GetMHNhits(int layer, int xy){return 0;}
void   RHICfRec0::SetMHNhits(int layer, int xy, int nhits){;}

// *** Newly developed for RHICf *** //

// Get maximum energy deposit GSO bar layer
int    RHICfRec0::GetMaxBarLayer(int it) { return 0; }
void    RHICfRec0::SetMaxBarLayer(int it, int d) {;}
// Get second maximum energy deposit GSO bar layer
int    RHICfRec0::GetMaxBarLayer2(int it) { return 0; }
void   RHICfRec0::SetMaxBarLayer2(int it, int d) {;}

// Return the position of parameter in the array.         
int    RHICfRec0::GetMHParPos(int layer,int xy, int ihits, int ipar){return 0;}
// Parameter of Multi-hit fitting (layer, xy, ihit, ipar);
double RHICfRec0::GetMHPar(int layer,int xy, int ihit, int ipar){return 0;}
// To modify the parameter value.
void   RHICfRec0::SetMHPar(int layer,int xy, int ihit, int ipar,double val){;}
bool   RHICfRec0::GetMHDiscardedFlag(int layer,int xy, int ihit){return true;}
// Add new the hit parameters
int    RHICfRec0::AddMHHit(int layer, int xy, double *par){return 0;}
// Erase the hit in the array.
int    RHICfRec0::EraseMHHit(int layer, int xy, int ihit){return 0;}
// Number of hits in the tower (except discarded peaks)
int    RHICfRec0::GetMHNumberOfHits(int tower){return 0;}
void   RHICfRec0::SetMHNumberOfHits(int tower, int val){;}
// Each position of MH
double RHICfRec0::GetMHPosition(int it,int il,int ixy,int imu) {return -1.;}
void RHICfRec0::SetMHPosition(int it,int il,int ixy, int imu, double d) {;}
// Each raw peak height by MH
double RHICfRec0::GetMHPeakRaw(int it,int il,int ixy,int imu) {return -1.;}
void RHICfRec0::SetMHPeakRaw(int it,int il,int ixy,int imu, double d) {;}
// Each estimated peak height by MH (using fitting function -> Eval(position))
double RHICfRec0::GetMHPeakEstimated(int it,int il,int ixy,int imu) {return -1.;}
void RHICfRec0::SetMHPeakEstimated(int it,int il,int ixy,int imu, double d) {;}
// Each dE esimated by integration of each contribution to MH function
double RHICfRec0::GetMHIntegral(int it,int il,int ixy,int imu) {return -1.;}
void RHICfRec0::SetMHIntegral(int it,int il,int ixy,int imu, double d) {;}

// ===================== PID =========================
// From pid 
// PID result (tower) 
int    RHICfRec0::GetResultPID(int it){return -1;}
void   RHICfRec0::SetResultPID(int it,int d){;}
// L20% (tower)
double RHICfRec0::GetL20(int it){ return 0;}
void   RHICfRec0::SetL20(int it,double d){;}
// L90% (tower)
double RHICfRec0::GetL90(int it){ return 0;}
void   RHICfRec0::SetL90(int it,double d){;}
// L2D  (tower) 
double RHICfRec0::GetL2D(int it){ return 0;}
void   RHICfRec0::SetL2D(int it,double d){;}
// Results of transition fiting (tower, parameter) -> Moved to "cal" for A1Rec3
double RHICfRec0::GetTransitionFit(int it,int ip){ return 0;}
void   RHICfRec0::SetTransitionFit(int it,int ip,double d){;}
double RHICfRec0::GetL20wocorr(int tower){return 0.;}
void   RHICfRec0::SetL20wocorr(int tower, double val){;}
double RHICfRec0::GetL90wocorr(int tower){return 0.;}
void   RHICfRec0::SetL90wocorr(int tower, double val){;}
// ===================== TDC ========================
// From tdc 
// TDC value of BPTX (beam 1 or 2)
double RHICfRec0::GetTDC_BPTX(int ib){ return 0;}
void   RHICfRec0::SetTDC_BPTX(int ib, double d){;}
// ================== COUNTER =======================
// From counter
// Counter Value (i-th)
double RHICfRec0::GetCounter(int i){ return 0;}
void   RHICfRec0::SetCounter(int i,double d){;}

#endif
