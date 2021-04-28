#ifndef __GSOBARPOSCALC_H__
#define __GSOBARPOSCALC_H__

//================================================================//
//                                                                //
//                       GSObarPosCalc                            //
//          13 Sep. 2014: First edited by Y.Makino                //
//          21 Aug. 2016: Major updates!                          //
//                                                                //
//================================================================//

#include <string>
#include <vector>
#include <TF1.h>
#include <TH1D.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TROOT.h>

#include "A1Cal1.h"
#include "A1Cal2.h"
#include "A1Phys.h"
#include "A1Rec1.h"

typedef A1Rec1 A1Rec;

using namespace std;

class GSObarPosCalc{

	public:
		static const int NTOWER = 2;       // Number of calorimeter towers
		static const int NLAYER = 4;       // Number of GSObar hodoscope XY layer
		static const int NXY    = 2;       // Number of GSObar bundles in 1 layer (X and Y)
		static const int NCH20  = 20;      // Number of GSObars in a bundle (Small tower)
		static const int NCH40  = 40;      // Number of GSObars in a bundle (Large tower)
		static const int NMULTI = 2;       // For MH

		TH1D* h_gsobar[NTOWER][NLAYER][NXY];
		TH1D* h_gsobar2[NTOWER][NLAYER][NXY];
		TGraphErrors* g_gsobar[NTOWER][NLAYER][NXY];

		TF1* f_single[NTOWER][NLAYER][NXY];
		TF1* f_multi[NTOWER][NLAYER][NXY];
		TF1* f_multi_draw[NTOWER][NLAYER][NXY];
		TF1* f_each[NTOWER][NLAYER][NXY][NMULTI];
		TF1* f_each_draw[NTOWER][NLAYER][NXY][NMULTI];

		TSpectrum* sh[NTOWER][NLAYER][NXY];  

		bool xoverlap;
		bool yoverlap;

	private:
		int worthy[2];// worthy[itower] = 1 means "itower" is worhty to analyze.

		int nhit[NTOWER][NLAYER][NXY];// Number of peaks by TSpectrum
		double x_prime[NTOWER][NLAYER][NXY];
		double y_prime[NTOWER][NLAYER][NXY];
		double x_sub[NTOWER][NLAYER][NXY];
		double y_sub[NTOWER][NLAYER][NXY];
		double gsobar_ts_tmp[NLAYER][NXY][NCH20]; 
		double gsobar_tl_tmp[NLAYER][NXY][NCH40];
		static int position_table_ok; 
		static double position_ts[NLAYER][NXY][NCH20];// position of each GSO-bar 
		static double position_tl[NLAYER][NXY][NCH40]; 

		// Initial parameter for fitting.
		double init_param_single[6];
		double init_param_multi[11];

		int nhit_each[NTOWER][NLAYER][NXY];
		int nhit_result[NTOWER];

		static const double tsp_sigma;// used in TSpectrum::Search()
		static const double ratio_threshold;// peak ratio
		static const double distance_threshold;// distance btw two peaks
		double noise_cut;// A peak bellow this value [GeV] is not regarded as a peak. deflaut is 30 MeV
		double ave_cut;

		int maxlay[2];
		int maxlay2[2];

	public:
		GSObarPosCalc();
		virtual ~GSObarPosCalc();

		int Initialize();
		void SetData(A1Cal1* data);
		void SetData(A1Cal2* data);
		void ReadPositionTable(const char table[]); 

		void Reset(); 
		void Fill2Hist(); 
		void MaskInvalidChannels(); 

		void IsWorthy();
		int GetWorthy(int itower) { return worthy[itower]; };

		int InitialParamSet(int tower, int layer, int xy, double* param_single, double* param_multi); 
		int InitialParamEstimate();
		int ParLimits();
		void ParamCheck();

		int CalcPos(char* option);

		void FittingAll();  
		int SingleFit(int tower, int layer, int xy);
		int MultiFit(int tower, int layer, int xy);
		double GetChi2Single(int tower, int layer, int xy, const char* option);
		double GetChi2Multi(int tower, int layer, int xy, const char* option);
		double GetFitParamSingle(int tower, int layer, int xy, int param);
		double GetFitParamMulti(int tower, int layer, int xy, int param);
		double GetPeakHeightSingle(int tower, int layer, int xy);
                double GetPeakHeightMulti(int tower, int layer, int xy, int peak);
                double GetPeakPos(int tower, int layer, int xy);
                double GetPeakPosMH(int tower, int layer, int xy, int peak);
		void FillMH4Rec(A1Rec* rec, int tower);	

		int GetNumOfPeaksAboveThrehsold(int tower, int layer, int xy, char* mode, double threshold);
		int EvalNumOfHits(int tower, int layer, int xy);
		int EvalNumOfHits(int tower);

		double GetdE(int tower, int layer, int xy);
		int GetMaximumBin(int tower, int layer, int xy);
		void GetScan(TCanvas* c, int TSlayer, int TLlyaer, int iev, int TShit, int TLhit);

		void GetEachContribution(int tower);
		double GetEachPeakRaw(int it, int il, int ixy, int imu);
		double GetEachPeakEstimated(int it, int il, int ixy, int imu);
		double GetEachIntegral(int it, int il, int ixy, int imu);

		//  ClassDef(foo,1);  
};
#endif
