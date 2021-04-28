#ifndef  __SCINTIPOSDEPGSO_H__
#define __SCINTIPOSDEPGSO_H__

//------------------------------------------------
//
//               ScintiPosDepGSO
//
//------------------------------------------------
// Correction of position dependence both of non-
// uniforimity and shower-leakage.
// --> Modified. ONLY non-uniformity is corrected in this function
//------------------------------------------------
#include <iostream>
#include <fstream>
#include <TH2D.h>
#include <TH2F.h>
#include <TGraph2D.h>
#include "A1Cal2.h"
#include "A2Cal2.h"

using namespace std;

class ScintiPosDepGSO {

	private:

	public:
		ScintiPosDepGSO();

		virtual ~ScintiPosDepGSO();

		int Init();

		int SetdEMapArm1(char *map20mm, char *map40mm, char *map20mmhadron, char *map40mmhadron);

		int SetdEMapArm2(char *map25mm, char *map32mm);

		int SetdEMap20mm(char *map20mm, char* map20mmhadron);

		int SetdEMap40mm(char *map40mm, char* map40mmhadron);

		int SetdEMap25mm(char *map25mm);

		int SetdEMap32mm(char *map32mm);

		double GetEfficiency(int detector, int tower, int layer, double x, double y);
		double GetEfficiencyHadron(int detector, int tower, double x, double y);

		int Calibration(A1Cal2* a1cal2, int tower, double x, double y);
		int Calibration(A1Cal2* a1cal2, int tower, double p, double q, double x1, double y1, double x2, double y2);

		double GetEfficiency_forBugMC(int detector, int tower, int layer, double x, double y);

		int Calibration_forBugMC(A1Cal2 *a1cal2, int tower, double x, double y);

		bool             map20mm_ok;
		bool             map40mm_ok;
		bool             map20mmhadron_ok;
                bool             map40mmhadron_ok;
		bool             map25mm_ok;
		bool             map32mm_ok;
		static const int NLAYER = 16;       // Number of GSOplate hodoscope XY layer

		TH2D *demap_20mm[NLAYER];
		TH2D *demap_40mm[NLAYER];
		TH2D* demap_20mmhadron;
		TH2D* demap_40mmhadron;
		//TGraph2D* demap_20mm[NLAYER];
		//TGraph2D* demap_40mm[NLAYER];
		TH2F *demap_25mm[NLAYER];
		TH2F *demap_32mm[NLAYER];

};

#endif
