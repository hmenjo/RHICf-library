#ifndef __RHICFREC1_H__
#define __RHICFREC1_H__

#include "RHICfRec0.h"

class RHICfRec1 : public RHICfRec0 {

	public:
		RHICfRec1();
		RHICfRec1(char* name, char *title);
		virtual ~RHICfRec1(); 

		int            resize();  
		virtual void   Show();

	public:
		// Interface functions
		// From evinfo == Event Information == 
		virtual int    GetEventQuality();             // Event Quality flag 
		virtual void   SetEventQuality(int d);
		virtual int    GetBeamColConf();              // Beam Colliding flag
		virtual void   SetBeamColConf(int d);
		virtual int    GetBunchNumber(int ib);        // Bunch Number (beam 1 or 2)
		virtual void   SetBunchNumber(int ib,int d);
		// From flags  == Flag ==
		virtual unsigned int GetFlags(int i);         // Flag from GPIO's (i-th)
		virtual void         SetFlags(int i, unsigned int d);
		
		// *** Newly developed for RHICf *** //
		virtual bool IsShowerTrig();
                virtual bool IsPi0Trig();
                virtual bool IsHighEMTrig();

		// From rec    == Reconstruction ==
		virtual double GetResultEnergy(int it);         // Recommended reconstructed energy (tower)
		virtual double GetResultEnergy(int it,int pid); // Recommended reconstructed energy (tower, pid)
		virtual void   SetResultEnergy(int it,int pid,double d); 
		virtual double GetSumdE(int it);              // Sum dE(layer=0-15) (tower)
		virtual void   SetSumdE(int it,double d);
		virtual double GetSumdE2(int it);             // Sum dE(layer=1-12) (tower)
		virtual void   SetSumdE2(int it,double d);  
		virtual double GetLeakageOut(int it);         // Shower Leakage parameter (tower)
		virtual void   SetLeakageOut(int it,double d);
		virtual double GetEnergyScaleFactor(int it);  // Correction factor of energy scale (tower)
		virtual void   SetEnergyScaleFactor(int it,double d);
		// From pos    == Position ==
		virtual double GetResultHitPosition(int it, int ixy);      // Recommended hit position results (tower, xy)
		virtual void   SetResultHitPosition(int it, int ixy,double d); 
		virtual int    GetResultNumberOfHits(int it);              // Recommended number of hit results (tower)
		virtual void   SetResultNumberOfHits(int it, int d); 
		virtual int    GetNumberOfHits(int it,int il,int ixy);     // Number of Hits in the tower (tower,layer,xy)
		virtual void   SetNumberOfHits(int it,int il,int ixy, int d);
		virtual double GetHitPosition(int it,int il, int ixy);     // Hit Position in each layer (tower,layer,xy)
		virtual void   SetHitPosition(int it,int il, int ixy, double d); 
		virtual double GetPeakPosition(int it,int il,int ixy);     // Fiber number with maximum dE (tower,layer,xy)
		virtual void   SetPeakPosition(int it,int il,int ixy, double d);
		virtual double GetdEAtPeak(int it,int il,int ixy);         // dE at peak (tower,layer,xy)
		virtual void   SetdEAtPeak(int it,int il,int ixy,double d);
		//virtual int    GetSatuFlag(int it,int il,int ixy);         // Saturation flag for Arm2 
		//virtual void   SetSatuFlag(int it,int il,int ixy,int d); 
		
		// *** Newly developed for RHICf *** //
		virtual int GetMaxBarLayer(int it);
		virtual void SetMaxBarLayer(int it, int d);
		virtual int GetMaxBarLayer2(int it);
		virtual void SetMaxBarLayer2(int it, int d);

		virtual double GetMHPosition(int it, int il, int ixy, int imu);
		virtual void   SetMHPosition(int it, int il, int ixy, int imu, double d);
		virtual double GetMHPeakRaw(int it, int il, int ixy, int imu);
                virtual void   SetMHPeakRaw(int it, int il, int ixy, int imu, double d);
		virtual double GetMHPeakEstimated(int it, int il, int ixy, int imu);
                virtual void   SetMHPeakEstimated(int it, int il, int ixy, int imu, double d);
		virtual double GetMHIntegral(int it, int il, int ixy, int imu);
                virtual void   SetMHIntegral(int it, int il, int ixy, int imu, double d);

		virtual double GetChiSquare(int it, int il, int ixy, int imu);
                virtual void   SetChiSquare(int it, int il, int ixy, int imu, double d);

		// From pid    == PID ==
		virtual int    GetResultPID(int it);             // Recommended PID result (tower)
		virtual void   SetResultPID(int it,int d);        
		virtual double GetL20(int it);                   // L20% (tower)
		virtual void   SetL20(int it,double d);
		virtual double GetL90(int it);                   // L90% (tower) 
		virtual void   SetL90(int it,double d);
		// From pos    == Multi-Hit ==
		virtual double GetMHBkgPar(int tower, int layer, int xy, int ipar);             // Results of Background Fitting by a linear function 
		virtual void   SetMHBkgPar(int tower, int layer, int xy, int ipar, double val); 
		virtual int    GetMHNhits(int tower, int layer, int xy);                        // Number of Hits in the layer (layer, xy) includeing discarded peaks
		virtual void   SetMHNhits(int tower, int layer, int xy, int nhits);   
		virtual int    GetMHParPos(int tower, int layer,int xy, int ihits, int ipar);   // Return the position of parameter in the array.        
		virtual double GetMHPar(int tower, int layer,int xy, int ihit, int ipar);       // Parameter of Multi-hit fitting (layer, xy, ihit, ipar);
		virtual void   SetMHPar(int tower, int layer,int xy, int ihit, int ipar,double val);  // To modify the parameter value. 
		virtual bool   GetMHDiscardedFlag(int tower, int layer,int xy, int ihit);
		virtual int    AddMHHit(int tower, int layer, int xy, double *par);             // Add new the hit parameters  
		virtual int    EraseMHHit(int tower, int layer, int xy, int ihit);              // Erase the hit in the array. 
		virtual int    GetMHNumberOfHits(int tower);                                    // Number of hits in the tower (except discarded peaks)
		virtual void   SetMHNumberOfHits(int tower, int val);                


		ClassDef(RHICfRec1,1);    // Data for Reconstruction : Arm1 Format 1
};


#endif 
