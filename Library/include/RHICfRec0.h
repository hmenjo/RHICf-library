#ifndef __RHICFREC0_H__
#define __RHICFREC0_H__

#include <vector>

using namespace std;

#include <TNamed.h>
#include <RHICfPhys.h>

class RHICfRec0 : public TNamed {
public:
		// event infomation
		int                  run;                // Run Number
		int                  number;             // Arm#2 Event Number
		int                  gnumber;            // Grobal Event Number
		double               time[2];            // [0]:sec,[1]:usec
		// ++++ DATA +++++
		int                  format;
		vector<int>          evinfo;
		vector<unsigned int> flags;
		vector<double>       rec;
		vector<double>       cal;
		vector<double>       pos;
		vector<double>       pid;
		vector<double>       tdc;
		vector<double>       counter;

public:
		RHICfRec0();
		RHICfRec0(char *name, char *title);
		virtual ~RHICfRec0();
		
		int resize();
		int clear();
		int copy(RHICfRec0 *d);
		int copydata(RHICfRec0 *d);
		
		int GetFormatNumber() { return format; }
		
		int FillToPhys(RHICfPhys *phys);
		
		virtual void Show();

protected:
		// Internal functions 
		void resize(vector<int> &v, int size);
		void resize(vector<unsigned int> &v, int size);
		void resize(vector<double> &v, int size);
		void clear(vector<int> &v, int value);
		void clear(vector<unsigned int> &v, unsigned int value);
		void clear(vector<double> &v, double value);
		void copy(vector<int> &v, vector<int> &d);
		void copy(vector<unsigned int> &v, vector<unsigned int> &d);
		void copy(vector<double> &v, vector<double> &d);

public:
		// Interface functions
		// From evinfo == Event Information == 
		virtual int GetEventQuality();             // Event Quality flag
		virtual void SetEventQuality(int d);
		virtual int GetBeamColConf();              // Beam Colliding flag
		virtual void SetBeamColConf(int d);
		virtual int GetBunchNumber(int ib);        // Bunch Number (beam 1 or 2)
		virtual void SetBunchNumber(int ib, int d);
		// From flags  == Flag ==
		virtual unsigned int GetFlags(int i);         // Flag from GPIO's (i-th)
		virtual void SetFlags(int i, unsigned int d);
		virtual unsigned int GetAnalysisFlags(int i);  // Analysis flag (i-th)
		virtual void SetAnalysisFlags(int i, unsigned int d);
		
		// *** Newly developed for RHICf *** //
		virtual bool IsShowerTrig();
		virtual bool IsPi0Trig();
		virtual bool IsHighEMTrig();
		
		// From cal    == Calorimeter ==
		virtual double GetCal(int it, int il);        // Calorimeter dE (tower, layer)
		virtual void SetCal(int it, int il, double d);
		virtual double GetFC(int iarm, int ich);       // FC dE (arm, channel)
		virtual void SetFC(int iarm, int ich, double d);
		virtual double GetTFitParam(int tower, int ipar);                // shape w/o correction tower:0,1 ipar:0-3
		virtual void SetTFitParam(int tower, int ipar, double val);
		virtual double GetTFitParamCorr(int tower, int ipar);            // shape w/ correction tower:0,1 ipar:0-3
		virtual void SetTFitParamCorr(int tower, int ipar, double val);
		virtual double GetTFitParamLeakin(int tower, int ipar);          // Estimated shape of leakage-in tower:0,1 ipar:0-3
		virtual void SetTFitParamLeakin(int tower, int ipar, double val);
		virtual double GetTScale(int tower);                             // Scale of Transition fit
		virtual double GetTScaleCorr(int tower);                         // Scale of Transition fit
		virtual double GetTScaleLeakin(int tower);                       // Scale of estimated shape of shower leakage-in
		virtual double GetTMax(int tower);                               // Get depth of Shower Maximum
		virtual double GetTMaxCorr(int tower);                           // Get depth of Shower Maximum 
		virtual double GetTMaxLeakin(int tower);                         // Get depth of Shower Maximum 
		// From rec    == Energy Reconstruction ==
		virtual double GetResultEnergy(int it);         // Recommended reconstructed energy (tower)
		virtual double GetResultEnergy(int it, int pid); // Recommended reconstructed energy (tower, pid)
		virtual void SetResultEnergy(int it, int pid, double d);
		virtual double GetSumdE(int it);                // Sum dE(layer=0-15) (tower)
		virtual void SetSumdE(int it, double d);
		virtual double GetSumdE2(int it);               // Sum dE(layer=1-12) (tower)
		virtual void SetSumdE2(int it, double d);
		virtual double GetLeakageOut(int it);           // Shower Leakage parameter (tower)
		virtual void SetLeakageOut(int it, double d);
		virtual double GetLightYield(int it, int il);   // Correction factor of light yield (tower, layer)
		virtual void SetLightYield(int it, int il, double d);
		virtual double GetEnergyScaleFactor(int it);    // Correction factor of energy scale (tower)
		virtual void SetEnergyScaleFactor(int it, double d);
		// *** Newly developed for RHICf *** //
		virtual double GetType2Energy(int it, int hit);
		virtual void SetType2Energy(int it, int hit, double d);
		virtual double GetTyep2Position(int it, int ixy, int hit);
		virtual void SetTyep2Position(int it, int ixy, int hit, double d);
		
		// From pos    == Position ==
		virtual double GetResultHitPosition(int it, int ixy);      // Recommended hit position results (tower, xy)
		virtual void SetResultHitPosition(int it, int ixy, double d);
		virtual int GetResultNumberOfHits(int it);              // Recommended number of hit results (tower)
		virtual void SetResultNumberOfHits(int it, int d);
		virtual int GetNumberOfHits(int it, int il, int ixy);     // Number of Hits in the tower (tower,layer,xy)
		virtual void SetNumberOfHits(int it, int il, int ixy, int d);
		virtual double GetHitPosition(int it, int il, int ixy);     // Hit Position in each layer (tower,layer,xy)
		virtual void SetHitPosition(int it, int il, int ixy, double d);
		virtual double GetPeakStrip(int it, int il, int ixy);        // Strip number with maximum dE (tower,layer,xy)
		virtual void SetPeakStrip(int it, int il, int ixy, double d);
		virtual double GetdEAtPeak(int it, int il, int ixy);         // dE at peak (tower,layer,xy)
		virtual void SetdEAtPeak(int it, int il, int ixy, double d);
		virtual int GetSiSatuFlag(int it, int il, int ixy);       // Saturation flag of silicon middle sample
		virtual void SetSiSatuFlag(int it, int il, int ixy, int d);
		virtual double GetMHBkgPar(int layer, int xy, int ipar);   // Results of Background Fitting by a linear function 
		virtual void SetMHBkgPar(int layer, int xy, int ipar, double val);
		virtual int GetMHNhits(int layer, int xy);              // Number of Hits in the layer (layer, xy)
		virtual void SetMHNhits(int layer, int xy, int nhits);
		virtual int
		GetMHParPos(int layer, int xy, int ihits, int ipar);  // Return the position of parameter in the array.
		virtual double
		GetMHPar(int layer, int xy, int ihit, int ipar);  // Parameter of Multi-hit fitting (layer, xy, ihit, ipar);
		virtual void SetMHPar(int layer, int xy, int ihit, int ipar, double val);  // To modify the parameter value.
		virtual bool GetMHDiscardedFlag(int layer, int xy, int ihit);
		virtual int AddMHHit(int layer, int xy, double *par);   // Add new the hit parameters
		virtual int EraseMHHit(int layer, int xy, int ihit);    // Erase the hit in the array.
		virtual int GetMHNumberOfHits(int tower);               // Number of hits in the tower (except discarded peaks)
		virtual void SetMHNumberOfHits(int tower, int val);
		
		// *** Newly developed for RHICf *** //
		
		virtual int GetMaxBarLayer(int it);
		virtual void SetMaxBarLayer(int it, int d);
		virtual int GetMaxBarLayer2(int it);
		virtual void SetMaxBarLayer2(int it, int d);
		
		virtual double GetMHPosition(int it, int il, int ixy, int imu);
		virtual void SetMHPosition(int it, int il, int ixy, int imu, double d);
		virtual double GetMHPeakRaw(int it, int il, int ixy, int imu);
		virtual void SetMHPeakRaw(int it, int il, int ixy, int imu, double d);
		virtual double GetMHPeakEstimated(int it, int il, int ixy, int imu);
		virtual void SetMHPeakEstimated(int it, int il, int ixy, int imu, double d);
		virtual double GetMHIntegral(int it, int il, int ixy, int imu);
		virtual void SetMHIntegral(int it, int il, int ixy, int imu, double d);
		
		// From pid    == PID == 
		virtual int GetResultPID(int it);             // Recommended PID result (tower)
		virtual void SetResultPID(int it, int d);
		virtual double GetL20(int it);                   // L20% (tower)
		virtual void SetL20(int it, double d);
		virtual double GetL90(int it);                   // L90% (tower) 
		virtual void SetL90(int it, double d);
		virtual double GetL2D(int it);                   // L2D(tower)
		virtual void SetL2D(int it, double d);
		virtual double
		GetL20wocorr(int tower);                          // Get L20% which was calculated before shower leakin corr.
		virtual void SetL20wocorr(int tower, double val);
		virtual double
		GetL90wocorr(int tower);                          // Get L90% which was calculated before shower leakin corr.
		virtual void SetL90wocorr(int tower, double val);
		virtual double GetTransitionFit(int it, int ip);  // Results of transition fiting (tower, parameter)
		virtual void SetTransitionFit(int it, int ip, double d);
		// From tdc    == TDC ==
		virtual double GetTDC_BPTX(int ib);              // TDC value of BPTX (beam 1 or 2)
		virtual void SetTDC_BPTX(int ib, double d);
		// From counter == Counter ==
		virtual double GetCounter(int i);                // Counter Value (i-th)
		virtual void SetCounter(int i, double d);
		
		//  ============= DEFINITION ================= 
		enum DEF_EVQUALITY {
				GOOD = 1,
				BAD  = 0
		};
		
		enum DEF_BEAMTAG {
				CROSSING     = 0x1,
				DISPLACED    = 0x3,
				NONCROSSING  = 0x2,   // Single of Beam1
				NONCROSSING2 = 0x4,   // Single of Beam2
				UNKNOWN      = 0x0
		};

ClassDef(RHICfRec0, 1);    // Data for Reconstruction
};


#endif 

