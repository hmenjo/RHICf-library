#ifndef __SCINTIPOSDEPGSO_CPP__
#define __SCINTIPOSDEPGSO_CPP__

//-----------------------------------------------------------------
//                       ScintiPosDepGSO
//          24 Feb. 2015: First edited by Makino
//  For fast calculation  of efficiency, TGraph2D -> TH2D
//  by Menjo 26 May 2017.
//-----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <TMath.h>
#include <TFile.h>
#include <TROOT.h>
#include <TH2D.h>
#include "ScintiPosDepGSO.h"

using namespace std;

const int ScintiPosDepGSO::NLAYER;

// ++++++++++++++++ ScintiPosDepGSO ++++++++++++++++++++
ScintiPosDepGSO::ScintiPosDepGSO(){
	Init();
}

// +++++++++++++++++ ~ScintiPosDepGSO ++++++++++++++++++
ScintiPosDepGSO::~ScintiPosDepGSO(){;}

// ++++++++++++++++ Init ++++++++++++++++++++
int ScintiPosDepGSO::Init(){

	return 0;
}

// ++++++++++++++++ SetdEMapArm1 ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMapArm1(char* map20mm, char* map40mm, char* map20mmhadron, char* map40mmhadron){

	SetdEMap20mm(map20mm, map20mmhadron);
	SetdEMap40mm(map40mm, map40mmhadron);

	return 0;
}

// ++++++++++++++++ SetdEMapArm2 ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMapArm2(char* map25mm, char* map32mm){

	SetdEMap25mm(map25mm);
	SetdEMap32mm(map32mm);

	return 0;
}

// ++++++++++++++++ SetdEMap20mm ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMap20mm(char* map20mm, char* map20mmhadron){

	TFile* fin = new TFile(map20mm,"read");
	if(!fin) cerr<<"File not found in ScintiPosDepGSO::SetdEMap20mm(char* map20mm)"<<endl;

	char hname[256];
	for(int ilay=0; ilay<NLAYER; ++ilay){
		//    sprintf(hname,"h2_demap_ts_lay%d",ilay);
		//    sprintf(hname,"h1_%02d",ilay);
		//    sprintf(hname,"map_tg0_%02d",ilay);
		//    demap_20mm[ilay] = (TGraph2D*)fin->Get(hname);
		demap_20mm[ilay] = (TH2D*) fin->Get(Form("h2map_tg0_%02d",ilay));
	}

	map20mm_ok = true;

	TFile* fin2 = new TFile(map20mmhadron, "read");
        if(!fin2) cerr<<"File not found in ScintiPosDepGSO::SetdEMap20mm(char* map20mmhadron)"<<endl;

        demap_20mmhadron = (TH2D*) fin2->Get("h2map_tg0");
        map20mmhadron_ok = true;	

	return 0;
}

// ++++++++++++++++ SetdEMap40mm ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMap40mm(char* map40mm, char* map40mmhadron){

	TFile* fin = new TFile(map40mm,"read");
	if(!fin) cerr<<"File not found in ScintiPosDepGSO::SetdEMap40mm(char* map40mm)"<<endl;

	char hname[256];
	for(int ilay=0; ilay<NLAYER; ++ilay){
		//    sprintf(hname,"h2_demap_tl_lay%d",ilay);
		//    sprintf(hname,"h1_%02d",ilay);
		//    sprintf(hname,"map_tg1_%02d",ilay);
		//    demap_40mm[ilay] = (TGraph2D*)fin->Get(hname);
		demap_40mm[ilay] = (TH2D*) fin->Get(Form("h2map_tg1_%02d",ilay));
	}

	map40mm_ok = true;

	TFile* fin2 = new TFile(map40mmhadron, "read");
        if(!fin2) cerr<<"File not found in ScintiPosDepGSO::SetdEMap40mm(char* map40mmhadron)"<<endl;
                
        demap_40mmhadron = (TH2D*) fin2->Get("h2map_tg1");
        map40mmhadron_ok = true;

	return 0;
}

// ++++++++++++++++ SetdEMap25mm ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMap25mm(char* map25mm){
	map25mm_ok = true;
	return 0;
}

// ++++++++++++++++ SetdEMap32mm ++++++++++++++++++++
int ScintiPosDepGSO::SetdEMap32mm(char* map32mm){
	map32mm_ok = true;
	return 0;
}

// ++++++++++++++++ GetEfficiency ++++++++++++++++++++
double ScintiPosDepGSO::GetEfficiency(int detector, int tower, int layer, double x, double y){
	// detector (1/2) <-> (Arm1/Arm2)
	// tower    (0/1) <-> (TS/TL)

	double eff=0;

	if( detector==1 && tower==0 ){
		eff = demap_20mm[ layer ]->Interpolate(x, y);
		//eff = demap_20mm[layer]->GetBinContent(demap_20mm[layer]->FindBin(x,y));
	}else if(detector==1 && tower==1 ){
		eff = demap_40mm[ layer ]->Interpolate(x, y);
		//eff = demap_40mm[layer]->GetBinContent(demap_40mm[layer]->FindBin(x,y));
	}else if(detector==2 && tower==0 ){
		eff = demap_25mm[ layer ]->Interpolate(x, y);
	}else if(detector==2 && tower==1 ){
		eff = demap_32mm[ layer ]->Interpolate(x, y);
	}

	// Use following fuction when you really understand the situation. Otherwise never use!
	// if( detector==1 && tower==0 ){
	//   eff = demap_20mm[ layer ]->Interpolate(y, x);
	// }else if(detector==1 && tower==1 ){
	//   eff = demap_40mm[ layer ]->Interpolate(y, x);
	// }else if(detector==2 && tower==0 ){
	//   eff = demap_25mm[ layer ]->Interpolate(y, x);
	// }else if(detector==2 && tower==1 ){
	//   eff = demap_32mm[ layer ]->Interpolate(y, x);
	// }

	return eff;
}

double ScintiPosDepGSO::GetEfficiencyHadron(int detector, int tower, double x, double y){
        // detector (1/2) <-> (Arm1/Arm2)
        // tower    (0/1) <-> (TS/TL)

        double eff=0;

        if( detector==1 && tower==0 ){
                eff = demap_20mmhadron -> Interpolate(x, y);
        }else if(detector==1 && tower==1 ){
                eff = demap_40mmhadron -> Interpolate(x, y);
        }/*else if(detector==2 && tower==0 ){
                eff = demap_25mm[ layer ]->Interpolate(x, y);
        }else if(detector==2 && tower==1 ){
                eff = demap_32mm[ layer ]->Interpolate(x, y);
        }*/

        return eff;
}

// ++++++++++++++++ Calibration ++++++++++++++++++++
int ScintiPosDepGSO::Calibration(A1Cal2* a1cal2, int tower, double x, double y){

	for(int ilay=0; ilay<NLAYER; ++ilay){
		// Modified by Menjo on 2016/6/7
		// Sometimes the efficiency value given by GetEfficiency is unphysical value.
		double eff=1.;
		eff = GetEfficiency(1, tower, ilay, x, y);
		if(eff < 0.1 || eff > 2.){
			double towersize = (tower==0?20.0:40.0);
			double edgesize  = (ilay<12?1.0:2.0);
			if( x < edgesize )          x = edgesize;
			if( x > towersize-edgesize) x = towersize-edgesize;
			if( y < edgesize )          y = edgesize;
			if( y > towersize-edgesize) y = towersize-edgesize;
			eff = GetEfficiency(1, tower, ilay, x, y);
		}

		//if(tower==1 && ilay==1) printf("%0.1f\n", a1cal2->cal[tower][ilay]);
		double Etmp = a1cal2->cal[tower][ilay];
		a1cal2->cal[tower][ilay] /= eff;
		//printf("layer:%d, %0.2f / %0.2f = %0.2f\n", ilay, Etmp, eff, a1cal2->cal[tower][ilay]);
		//a1cal2->cal[tower][ilay] *= (1./0.903);

		//if(tower==1 && ilay==1) printf("%0.1f\n", a1cal2->cal[tower][ilay]);
		//if(tower==1 && ilay==1) printf("   \n");
	}

	return 0;
}

int ScintiPosDepGSO::Calibration(A1Cal2* a1cal2, int tower, double p, double q, double x1, double y1, double x2, double y2){

	//if(tower==1) printf("a1 = %0.1f, b1 = %0.1f, a2 = %0.1f, b2 = %0.1f, p = %0.1f, q = %0.1f\n", x1, y1, x2, y2, p, q);

	for(int ilay=0; ilay<NLAYER; ++ilay){
		// Modified by Menjo on 2016/6/7
		// Sometimes the eff1iciency value given by GetEfficiency is unphysical value.
		double eff1=1.;
		eff1 = GetEfficiency(1, tower, ilay, x1, y1);
		if(eff1 < 0.1 || eff1 > 2.){
			double towersize = (tower==0?20.0:40.0);
			double edgesize  = (ilay<12?1.0:2.0);
			if( x1 < edgesize )          x1 = edgesize;
			if( x1 > towersize-edgesize) x1 = towersize-edgesize;
			if( y1 < edgesize )          y1 = edgesize;
			if( y1 > towersize-edgesize) y1 = towersize-edgesize;
			eff1 = GetEfficiency(1, tower, ilay, x1, y1);
		}

		double eff2=1;
		eff2 = GetEfficiency(1, tower, ilay, x2, y2);
                if(eff2 < 0.1 || eff2 > 2.){
                        double towersize = (tower==0?20.0:40.0);
                        double edgesize  = (ilay<12?1.0:2.0);
                        if( x2 < edgesize )          x2 = edgesize;
                        if( x2 > towersize-edgesize) x2 = towersize-edgesize;
                        if( y2 < edgesize )          y2 = edgesize;
                        if( y2 > towersize-edgesize) y2 = towersize-edgesize;
                        eff2 = GetEfficiency(1, tower, ilay, x2, y2);
                }

		//if(tower==1 && ilay==1) printf("%0.1f\n", a1cal2->cal[tower][ilay]);

		//printf("%f -->", a1cal2->cal[tower][ilay]);
		double Etmp = a1cal2->cal[tower][ilay];
		a1cal2->cal[tower][ilay] /= eff1*p+eff2*q;
		//printf("layer:%d, %0.2f --> %0.2f\n", ilay, Etmp, a1cal2->cal[tower][ilay]);
		//a1cal2->cal[tower][ilay] *= (1./0.903);

		//printf(" %f\n", a1cal2->cal[tower][ilay]);
		//if(tower==1 && ilay==1) printf("%0.1f\n", a1cal2->cal[tower][ilay]);
		//if(tower==1 && ilay==1) printf("   \n");
	}

	return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ Methods for MC with swapped map +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++ GetEfficiency_forBugMC ++++++++++++++++++++
double ScintiPosDepGSO::GetEfficiency_forBugMC(int detector, int tower, int layer, double x, double y){
	// detector (1/2) <-> (Arm1/Arm2)
	// tower    (0/1) <-> (TS/TL)

	double eff=0;

	//  Use following fuction when you really understand the situation. Otherwise never use!
	if( detector==1 && tower==0 ){
		eff = demap_20mm[ layer ]->Interpolate(y, x);
	}else if(detector==1 && tower==1 ){
		eff = demap_40mm[ layer ]->Interpolate(y, x);
	}

	return eff;

}


// ++++++++++++++++ Calibration_forBugMC ++++++++++++++++++++
int ScintiPosDepGSO::Calibration_forBugMC(A1Cal2* a1cal2, int tower, double x, double y){

	for(int ilay=0; ilay<NLAYER; ++ilay)
		a1cal2->cal[tower][ilay] /= GetEfficiency_forBugMC(1, tower, ilay, x, y);

	return 0;
}

#endif
