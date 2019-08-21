#ifndef __GSOBARPOSCALC_CPP__
#define __GSOBARPOSCALC_CPP__

//----------------------------------------------------------------------
//                       GSObarPosCalc
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  13 Sep. 2014: First edited by Y.Makino
//  21 Aug. 2016: Major updates!
//----------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <TMath.h>
#include <TROOT.h>
#include <TH1D.h>
#include <TSpectrum.h>
#include <TStyle.h>
#include <TGraph.h>

#include "../include/GSObarPosCalc.h"

using namespace std;

const int GSObarPosCalc::NTOWER;
const int GSObarPosCalc::NLAYER;
const int GSObarPosCalc::NXY;
const int GSObarPosCalc::NCH20;
const int GSObarPosCalc::NCH40;
double GSObarPosCalc::position_ts[GSObarPosCalc::NLAYER][GSObarPosCalc::NXY][GSObarPosCalc::NCH20]={};
double GSObarPosCalc::position_tl[GSObarPosCalc::NLAYER][GSObarPosCalc::NXY][GSObarPosCalc::NCH40]={};
const double GSObarPosCalc::tsp_sigma     = 1.0;
const double GSObarPosCalc::ratio_threshold = 0.2; // ratio
const double GSObarPosCalc::distance_threshold = 3.0;

int GSObarPosCalc::position_table_ok;
char name[256];

GSObarPosCalc::GSObarPosCalc(){
	Initialize();
}

GSObarPosCalc::~GSObarPosCalc(){;}

// +++++++++++++++++++++++ CalcPos ++++++++++++++++++++++++++
int GSObarPosCalc::CalcPos(char* option){

	InitialParamEstimate();
	IsWorthy();
	FittingAll();

	/*int trial = 0;

	  while( trial < 1 ){

	  ReconfigParam();
	  FittingAll();

	  ++trial;
	  }*/

	return 0;
}

TF1* get_Lorenzian(int tower, int npeak){

	TF1* func;

	double xmin = 0.0;
	double xmax = 20.0*(tower+1);

	if( npeak==2 )
		func = new TF1("multi","[2]*([4]*([0]*0.5)/pow(((x-[1])*(x-[1])+[0]), 1.5) + (1- [4])*([3]*0.5)/pow(((x-[1])*(x-[1])+[3]), 1.5)) + [5] + [8]*([10]*([6]*0.5)/pow(((x-[7])*(x-[7])+[6]), 1.5) + (1- [10])*([9]*0.5)/pow(((x-[7])*(x-[7])+[9]), 1.5))",xmin,xmax);
	else 
		func = new TF1("single","[2]*([4]*([0]*0.5)/pow(((x-[1])*(x-[1])+[0]), 1.5) + (1- [4])*([3]*0.5)/pow(((x-[1])*(x-[1])+[3]), 1.5)) +[5]",xmin,xmax);

	//    func = new TF1("lorentzian"," [2]*( [1]/( (x-[0])**2 + [1]**2  ) )/(TMath::Pi()) + [2]*[4]*( [3]/( (x-[0])**2 + [3]**2  ) )/(TMath::Pi())", xmin, xmax);
	//    func = new TF1("single"," [0] * pow( 1 + pow( (x-[1]/([2]/2)), 2), [3] ) ", xmin, xmax);

	return func;
}

// +++++++++++++++++++++++ Initialize +++++++++++++++++++++++
int GSObarPosCalc::Initialize(){
  
	// default threshold value 
	//noise_cut=30.0*0.001;
	noise_cut = 0.05;
	//cout << " GSObarPosCalc::Initialize()" << endl;
	// --- Data container ---
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

			// --- 20mm ---
			sprintf(name,"h_gsobar_ts_lay%d_xy%d", ilay, ixy);
			h_gsobar[0][ilay][ixy] = new TH1D(name, name, GSObarPosCalc::NCH20, 0, GSObarPosCalc::NCH20);    
			// --- 40mm ---
			sprintf(name,"h_gsobar_tl_lay%d_xy%d", ilay, ixy); 
			h_gsobar[1][ilay][ixy] = new TH1D(name, name, GSObarPosCalc::NCH40, 0, GSObarPosCalc::NCH40);   
		}
	}

	// --- TGraph for fit ----
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

			// --- 20mm ---
			sprintf(name,"g_gsobar_ts_lay%d_xy%d", ilay, ixy);
			g_gsobar[0][ilay][ixy] = new TGraphErrors(GSObarPosCalc::NCH20);
			g_gsobar[0][ilay][ixy]->SetName(name);      
			g_gsobar[0][ilay][ixy]->SetLineWidth( 2 );      

			// --- 40mm ---
			sprintf(name,"g_gsobar_tl_lay%d_xy%d", ilay, ixy);
			g_gsobar[1][ilay][ixy] = new TGraphErrors(GSObarPosCalc::NCH40);
			g_gsobar[1][ilay][ixy]->SetName(name);      
			g_gsobar[1][ilay][ixy]->SetLineWidth( 2 );      

		}
	}

	// --- Fitting functions ---
	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){
		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				f_single[it][ilay][ixy] = (TF1*) get_Lorenzian(it, 1);
				f_multi[it][ilay][ixy] = (TF1*) get_Lorenzian(it, 2);
				f_single[it][ilay][ixy]->SetLineColor( kRed );
				f_multi[it][ilay][ixy]->SetLineColor( kBlue );
				f_single[it][ilay][ixy]->SetNpx( 10000 );
				f_multi[it][ilay][ixy]->SetNpx( 10000 );

				for(int imu=0;imu<2;imu++){

					f_each[it][ilay][ixy][imu] = (TF1*) get_Lorenzian(it, 1);
					f_each[it][ilay][ixy][imu] -> SetLineColor(1);
					f_each[it][ilay][ixy][imu] -> SetNpx(10000);
				}
			}
		}
	}

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){
		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){
				sh[it][ilay][ixy] = new TSpectrum();
			}
		}
	}

	return 0;
}

void GSObarPosCalc::GetEachContribution(int tower){

	for(int il=0;il<2;il++){
		for(int ixy=0;ixy<2;ixy++){
			for(int imu=0;imu<2;imu++){

				double par[11];
				f_multi[tower][il][ixy] -> GetParameters(&par[0]);

				if(imu==0) f_each[tower][il][ixy][imu] -> SetParameters(par[0], par[1], par[2], par[3], par[4], par[5]/2);
				if(imu==1) f_each[tower][il][ixy][imu] -> SetParameters(par[6], par[7], par[8], par[9], par[10], par[5]/2);
			}	
		}
	}
}

double GSObarPosCalc::GetEachPeakRaw(int it, int il, int ixy, int imu){

	double pos;
	if(imu==0) pos = GetFitParamMulti(it, il, ixy, 1);
	if(imu==1) pos = GetFitParamMulti(it, il, ixy, 7);

	int posbin = h_gsobar[it][il][ixy] -> FindBin(pos);

	double candidate[3] = {h_gsobar[it][il][ixy]->GetBinContent(posbin-1), 
			       h_gsobar[it][il][ixy]->GetBinContent(posbin),
			       h_gsobar[it][il][ixy]->GetBinContent(posbin+1)};
	int maxarray = TMath::LocMax(3, candidate);

	return candidate[maxarray];
}

double GSObarPosCalc::GetEachPeakEstimated(int it, int il, int ixy, int imu){

	double pos;
	if(imu==0) pos = GetFitParamMulti(it, il, ixy, 1);
        if(imu==1) pos = GetFitParamMulti(it, il, ixy, 7);

	return f_each[it][il][ixy][imu] -> Eval(pos);
}

double GSObarPosCalc::GetEachIntegral(int it, int il, int ixy, int imu){

	if(it==0) return f_each[it][il][ixy][imu] -> Integral(0, 20);
	if(it==1) return f_each[it][il][ixy][imu] -> Integral(0, 40);
}

void GSObarPosCalc::IsWorthy(){

	worthy[0] = 0;
	worthy[1] = 0;

	int xworthy[2] = {0};
	int yworthy[2] = {0};

	for(int itower=0;itower<2;itower++){
		for(int ilayer=0;ilayer<4;ilayer++){
			for(int ixy=0;ixy<2;ixy++){

				int nbar;
				if(itower==0) nbar = 20;
				if(itower==1) nbar = 40;

				for(int ibar=0;ibar<nbar;ibar++){

					double edep = h_gsobar[itower][ilayer][ixy] -> GetBinContent(ibar+1);
					
					if(edep>noise_cut && ixy==0) xworthy[itower]++;
					if(edep>noise_cut && ixy==1) yworthy[itower]++;								
				}
			}
		}
	}

	for(int itower=0;itower<2;itower++){
		if(xworthy[itower]>0 && yworthy[itower]>0) worthy[itower] = 1;
	}
}

// +++++++++++++++++++++++ ParamCheck +++++++++++++++++++++++
void GSObarPosCalc::ParamCheck(){

	cout <<"====== Watch these parameters! ======="<<endl;
	cout<<"tsp_sigma          : "<<tsp_sigma <<"[GSO-bar, mm equivalent ]"<<endl;
	cout<<"ratio_threshold    : "<<ratio_threshold <<"[no unit]"<<endl;
	cout<<"distance_threshold : "<<distance_threshold<<"[mm]"<<endl;
	cout<<"noise_cut          : "<<noise_cut <<"[GeV]"<<endl;
	cout<<"======================================="<<endl;
}


// +++++++++++++++++++++++ SetData +++++++++++++++++++++++
void GSObarPosCalc::SetData(A1Cal1 *data){

	Reset();
       
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){
			for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich)
				gsobar_ts_tmp[ilay][ixy][ich]=data->scifi0[ilay][ixy][ich];
			for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich)
				gsobar_tl_tmp[ilay][ixy][ich]=data->scifi1[ilay][ixy][ich];
		}
	}

	Fill2Hist();
}
void GSObarPosCalc::SetData(A1Cal2 *data){

	Reset();
	
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
	  for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){
	    for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich) {
	      //cout << ilay << " " << ixy << " " << ich << " " << setprecision(15) <<  data->scifi0[ilay][ixy][ich]<< endl;
	      gsobar_ts_tmp[ilay][ixy][ich]=data->scifi0[ilay][ixy][ich];
	    }
	    for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich) 
	      gsobar_tl_tmp[ilay][ixy][ich]=data->scifi1[ilay][ixy][ich];
	  }
	}
	
	// --- Fill to histograms ---
	Fill2Hist();
}

// +++++++++++++++++++++++ ReadPositionTable +++++++++++++++++++++++
void GSObarPosCalc::ReadPositionTable(const char table[]){

	// Reading a file of GSObar-positions 
	ifstream fin(table);
	if(!fin) cerr<<"GSObar alignment table does not exist."<<endl;

	char a[256];
	int tower=0;
	int layer=0;
	int xy=0;
	int ch=0;

	while(1){
		fin >> a;

		if(strcmp(a,"DATA_END")==0) break;
		if(strcmp(a,"GSOBAR")==0){
			fin >> tower;
			fin >> layer;
			fin >> xy;
			fin >> ch;
			if(tower==0)      fin >> position_ts[layer][xy][ch];
			else if(tower==1) fin >> position_tl[layer][xy][ch];
		}
	}

	position_table_ok=1;
}

// +++++++++++++++++++++++ Reset +++++++++++++++++++++++
void GSObarPosCalc::Reset(){

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){
		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){
				h_gsobar[it][ilay][ixy]->Reset();
				g_gsobar[it][ilay][ixy]->Set(0);

				for(int i=0; i<6; ++i){

					f_single[it][ilay][ixy]->SetParameter(i,0);
					for(int imu=0;imu<2;imu++) f_each[it][ilay][ixy][imu] -> SetParameter(i, 0);					
				}

				for(int i=0; i<11; ++i){

					f_multi[it][ilay][ixy]->SetParameter(i,0);
				}

				x_prime[it][ilay][ixy] = -1;
				y_prime[it][ilay][ixy] = -1;
				x_sub[it][ilay][ixy] = -1;
				y_sub[it][ilay][ixy] = -1;
			}
		}
	}

	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

			// --- copied signals ---
			for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich) 
				gsobar_ts_tmp[ilay][ixy][ich]=0;
			for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich) 
				gsobar_tl_tmp[ilay][ixy][ich]=0;

		}

	}

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){
		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){
				nhit_each[it][ilay][ixy]=0;
			}
		}
	}

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){
		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				for(int ip=0; ip<6; ++ip)
					init_param_single[ip]=0;
				for(int ip=0; ip<11; ++ip)
					init_param_multi[ip]=0;

			}
		}
	}
}

void GSObarPosCalc::Fill2Hist(){
  
	//  double pede_rms = 0.000006; // eqivalent to ADC count of 3.
	int ped_rms_adc = 3; //[ADC]
	double ave_conv_factor = 3.5e5; // [ADC/GeV@1000V]
	double f_1000v_to_600v = 0.05; // 
	double special_factor = 0.477; 
	double hv_gain_factor =  f_1000v_to_600v*special_factor; // 1000V->550V
	double mod_ave_conv_factor = hv_gain_factor*ave_conv_factor; // [ADC/GeV@550V]
	double ped_rms_gev = ped_rms_adc/mod_ave_conv_factor; 

	double err=0.15;

	//
	// For the moment, given errors are empirical ones that fitting is performed reasonably  
	// We need a discussion here. 
	//

	// --- HISTOS ---
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

			// --- 20mm ---
			for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich){
				h_gsobar[0][ilay][ixy]->SetBinContent(ich+1, gsobar_ts_tmp[ilay][ixy][ich]);
				//h_gsobar[0][ilay][ixy]->SetBinError(ich+1,  err*gsobar_ts_tmp[ilay][ixy][ich] +  sqrt(ped_rms_gev)  );  
				//if(ilay==1) printf("tower:0, layer:%d, xy:%d; (%d, %f)\n", ilay, ixy, ich, gsobar_ts_tmp[ilay][ixy][ich]); 
			}
			// --- 40mm ---
			for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich){
				h_gsobar[1][ilay][ixy]->SetBinContent(ich+1, gsobar_tl_tmp[ilay][ixy][ich]);
				//h_gsobar[1][ilay][ixy]->SetBinError(ich+1, err*gsobar_tl_tmp[ilay][ixy][ich] + sqrt(ped_rms_gev) );
				//if(ilay==1) printf("tower:1, layer:%d, xy:%d; (%d, %f)\n", ilay, ixy, ich, gsobar_tl_tmp[ilay][ixy][ich]);
			}
		}
	}

	// --- TGraphs ---
	for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
		for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

			// --- 20mm ---
			for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich){
				g_gsobar[0][ilay][ixy]->SetPoint(ich, position_ts[ilay][ixy][ich], gsobar_ts_tmp[ilay][ixy][ich]);
				g_gsobar[0][ilay][ixy]->SetPointError(ich, 0, err*gsobar_ts_tmp[ilay][ixy][ich] + sqrt(ped_rms_gev)  );       
			}
			// --- 40mm ---
			for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich){
				g_gsobar[1][ilay][ixy]->SetPoint(ich, position_tl[ilay][ixy][ich], gsobar_tl_tmp[ilay][ixy][ich]);
				g_gsobar[1][ilay][ixy]->SetPointError(ich, 0, err*gsobar_tl_tmp[ilay][ixy][ich] +  sqrt(ped_rms_gev)  );
			}
		}
	}

	// --- Mask invalid channels ---
	MaskInvalidChannels();
}

// +++++++++++++++++++++++ MaskInvalidChannels  +++++++++++++++++++++++
void GSObarPosCalc::MaskInvalidChannels(){

	//--- dead channel ---
	g_gsobar[0][3][0]->SetPoint(12, position_ts[3][0][12],  0);
	g_gsobar[0][3][0]->RemovePoint(12);

}

int GSObarPosCalc::ParLimits(){

	//  double width1_lim[]={0.1, 1.2}; 
	//  double width2_lim[]={1.2, 20.}; 
	double width1_lim[]={0.5, 5.0}; 
	double width2_lim[]={5.0, 40.}; 
	double hight_lim[]={0, 100};
	double ratio_lim[]={0, 1.0};

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){

		//if(worthy[it]==0) continue;

		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				// // multi
				//printf("%0.1f %0.1f %0.1f\n", hight_lim[0], f_multi[it][ilay][ixy]->GetParameter(2), hight_lim[1]);
				f_multi[it][ilay][ixy]->SetParLimits(0, width1_lim[0], width1_lim[1]);  // w1 
				f_multi[it][ilay][ixy]->SetParLimits(1, -1.0, 1.0+20.*(it+1));          // x
				f_multi[it][ilay][ixy]->SetParLimits(2, hight_lim[0], hight_lim[1]);    // h
				f_multi[it][ilay][ixy]->SetParLimits(3, width2_lim[0], width2_lim[1]);  // w2
				f_multi[it][ilay][ixy]->SetParLimits(4, ratio_lim[0], ratio_lim[1]);    // ratio
				//	f_multi[it][ilay][ixy]->SetParLimits(5, -0.001, 0.001);              // base 
				f_multi[it][ilay][ixy]->SetParLimits(6, width1_lim[0], width1_lim[1]);  // 2w1 
				f_multi[it][ilay][ixy]->SetParLimits(7, -1.0, 1.0+20.*(it+1));          // 2x
				f_multi[it][ilay][ixy]->SetParLimits(8, hight_lim[0], hight_lim[1]);    // 2h
				f_multi[it][ilay][ixy]->SetParLimits(9, width2_lim[0], width2_lim[1]);  // 2w2
				f_multi[it][ilay][ixy]->SetParLimits(10, ratio_lim[0], ratio_lim[1]);   // 2ratio

				// single 
				f_single[it][ilay][ixy]->SetParLimits(0, width1_lim[0], width1_lim[1]);  // w1 
				f_single[it][ilay][ixy]->SetParLimits(1, -1.0, 1.0+20.*(it+1));          // x
				f_single[it][ilay][ixy]->SetParLimits(2, hight_lim[0], hight_lim[1]);    // h
				f_single[it][ilay][ixy]->SetParLimits(3, width2_lim[0], width2_lim[1]);  // w2 
				f_single[it][ilay][ixy]->SetParLimits(4, ratio_lim[0], ratio_lim[1]);    // ratio	
			}
		}
	}

	return 0;
}

int GSObarPosCalc::InitialParamSet(int tower, int layer, int xy, double* param_single, double* param_multi){
  // for(int i =0;i<6;i++){
  //   cout << "param_single"<< " " << *(param_single+i) << endl;
  // }
  //cout << "set parameter" << endl;
  // multi
	f_multi[tower][layer][xy]->SetParameters( param_multi );

	// single 
	f_single[tower][layer][xy]->SetParameters( param_single );

	return 0;
}

int GSObarPosCalc::InitialParamEstimate(){

	//  int giveup_fit[]={1, 1};

	// Get maximum energy deposit layer and second maximum deposit one.
        for(int it=0; it<2; ++it){

		double edepsum[4] = {0};

                for(int ilay=0; ilay<4; ++ilay){
		  //cout << "GetdE(it, ilay, 0)"<< " " << GetdE(it, ilay, 0) << endl;
		  edepsum[ilay] += GetdE(it, ilay, 0) + GetdE(it, ilay, 1);
                }

		maxlay[it] = TMath::LocMax(4, edepsum);
		edepsum[maxlay[it]] = 0;
		maxlay2[it] = TMath::LocMax(4, edepsum);
        }

	//printf("maxlay[0]: %d, maxlay[1]: %d\n", maxlay[0], maxlay[1]);

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){

		//if(worthy[it]==0) continue;

		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				x_prime[it][ilay][ixy] = 0;
				y_prime[it][ilay][ixy] = 0;
				x_sub[it][ilay][ixy] = 0;
				y_sub[it][ilay][ixy] = 0;

				// --- Peak search for init params ---
				sh[it][ilay][ixy]->Search( h_gsobar[it][ilay][ixy], tsp_sigma, "nobackground nodraw goff", ratio_threshold);
				//	sh[it][ilay][ixy]->Search( h_gsobar[it][ilay][ixy], tsp_sigma, "nobackground", ratio_threshold);

				nhit[it][ilay][ixy] = sh[it][ilay][ixy]->GetNPeaks();
				float* found_peak = sh[it][ilay][ixy]->GetPositionX();

				if( nhit[it][ilay][ixy]==0 ){

					// -- maximum bin as prime peak --
					int max_bin = h_gsobar[it][ilay][ixy]->GetMaximumBin();
					x_prime[it][ilay][ixy] = h_gsobar[it][ilay][ixy]->GetBinCenter( max_bin );
					y_prime[it][ilay][ixy] = h_gsobar[it][ilay][ixy]->GetBinContent( max_bin );

					// -- lateral center as sub peak ( super adhoc ) --
					int bin_center = 10*(it+1);
					x_sub[it][ilay][ixy] = (double) bin_center;
					y_sub[it][ilay][ixy] = h_gsobar[it][ilay][ixy]->GetBinContent( bin_center );

				}else if( nhit[it][ilay][ixy]==1 ){

					// -- for prime peak --
					int bin = h_gsobar[it][ilay][ixy]->GetXaxis()->FindBin( found_peak[0] );	
					y_prime[it][ilay][ixy] = h_gsobar[it][ilay][ixy]->GetBinContent( bin );
					x_prime[it][ilay][ixy] = found_peak[0];

					// -- lateral center as sub peak ( super adhoc ) --
					int bin_center = 10*(it+1);
					x_sub[it][ilay][ixy] = (double) bin_center;
					y_sub[it][ilay][ixy] = h_gsobar[it][ilay][ixy]->GetBinContent( bin_center );

				}else if( nhit[it][ilay][ixy] > 1 ){

					// -- for prime peak --
					for(int i=0; i<nhit[it][ilay][ixy]; ++i){

						int bin_tmp = h_gsobar[it][ilay][ixy]->GetXaxis()->FindBin( found_peak[i] );
						double y_tmp = h_gsobar[it][ilay][ixy]->GetBinContent( bin_tmp );

						if( y_tmp > y_prime[it][ilay][ixy] ){

							y_prime[it][ilay][ixy] = y_tmp;
							x_prime[it][ilay][ixy] = found_peak[i];
						}
					}

					// -- for sub peak --
					for(int i=0; i<nhit[it][ilay][ixy]; ++i){

						int bin_tmp = h_gsobar[it][ilay][ixy]->GetXaxis()->FindBin( found_peak[i] );
						double y_tmp = h_gsobar[it][ilay][ixy]->GetBinContent( bin_tmp );

						if( y_tmp > y_sub[it][ilay][ixy] && y_tmp < y_prime[it][ilay][ixy] ){

							y_sub[it][ilay][ixy] = y_tmp;
							x_sub[it][ilay][ixy] = found_peak[i];
						}
					}
				}

				// for in case of minus value of y
				if(y_prime[it][ilay][ixy]<0)  y_prime[it][ilay][ixy] = -y_prime[it][ilay][ixy];
				if(y_sub[it][ilay][ixy]<0)    y_sub[it][ilay][ixy] = -y_sub[it][ilay][ixy];
				
			}
		}
	}

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){

		//if(worthy[it]==0) continue;

                for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
                        for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				// single
                                init_param_single[0] = 1.0;  // prime width1
                                init_param_single[1] = x_prime[it][ilay][ixy];  // prime x
                                init_param_single[2] = y_prime[it][ilay][ixy];  // prime hight
                                init_param_single[3] = 10.0;     // prime width2
                                init_param_single[4] = 0.6;     // prime ratio
                                init_param_single[5] = 0.00001;     // baseline

                                // multi
                                init_param_multi[0] = 1.0;  // prime width1
                                init_param_multi[1] = x_prime[it][maxlay[it]][ixy];
                                init_param_multi[2] = y_prime[it][maxlay[it]][ixy];
                                //init_param_multi[1] = x_prime[it][ilay][ixy];  // prime x
                                //init_param_multi[2] = y_prime[it][ilay][ixy];  // prime hight
                                init_param_multi[3] = 10.0;     // prime width2
                                init_param_multi[4] = 0.6;     // prime ratio

                                init_param_multi[5] = 0.00001;  // baseline

                                init_param_multi[6] = 1.0;  // sub width1
                                init_param_multi[7] = x_sub[it][maxlay[it]][ixy];
                                init_param_multi[8] = y_sub[it][maxlay[it]][ixy];
                                //init_param_multi[7] = x_sub[it][ilay][ixy];  // sub x
                                //init_param_multi[8] = y_sub[it][ilay][ixy];  // sub hight
                                init_param_multi[9] = 10.0;     // sub width2
                                init_param_multi[10] = 0.6;     // sub ratio
				//cout << it << " " << ilay << " " << ixy << endl;
                                InitialParamSet(it, ilay, ixy, init_param_single, init_param_multi);
			}
		}
	}

	ParLimits();

	return 0;
}

void GSObarPosCalc::FittingAll(){

	for(int it=0; it<GSObarPosCalc::NTOWER; ++it){

		if(worthy[it]==1) continue;

		for(int ilay=0; ilay<GSObarPosCalc::NLAYER; ++ilay){
			for(int ixy=0; ixy<GSObarPosCalc::NXY; ++ixy){

				// -- single --
				SingleFit(it, ilay, ixy);

				// -- multi --
				MultiFit(it, ilay, ixy);
			}
		}
	}
}

// +++++++++++++++++++++++ SingleFit +++++++++++++++++++++++v
int GSObarPosCalc::SingleFit(int tower, int layer, int xy){
  //cout << "single fit" << endl;
	return g_gsobar[tower][layer][xy]->Fit( f_single[tower][layer][xy],"QR"); // Q0?
}

// +++++++++++++++++++++++ MultiFit +++++++++++++++++++++++v
int GSObarPosCalc::MultiFit(int tower, int layer, int xy){

	return g_gsobar[tower][layer][xy]->Fit( f_multi[tower][layer][xy],"QR");
}

// +++++++++++++++++++++++ GetChi2Single +++++++++++++++++++++++v
double GSObarPosCalc::GetChi2Single(int tower, int layer, int xy, const char* option=""){

	double chi2 = f_single[tower][layer][xy]->GetChisquare();
	double dof  = (double) f_single[tower][layer][xy]->GetNDF();

	if( strcmp(option,"reduced")==0 )
		return chi2/dof;
	else
		return chi2;
}

// +++++++++++++++++++++++ GetChi2Multi +++++++++++++++++++++++v
double GSObarPosCalc::GetChi2Multi(int tower, int layer, int xy, const char* option=""){

	double chi2 = f_multi[tower][layer][xy]->GetChisquare();
	double dof  = (double) f_multi[tower][layer][xy]->GetNDF();

	if( strcmp(option,"reduced")==0 )
		return chi2/dof;
	else
		return chi2;

}

// +++++++++++++++++++++++ GetFitParamSingle +++++++++++++++++++++++v
double GSObarPosCalc::GetFitParamSingle(int tower, int layer, int xy, int param){

	if( param>5 || param<0 ) return -1234;

	return f_single[tower][layer][xy]->GetParameter( param );
	//return 10;

}

// +++++++++++++++++++++++ GetFitParamMulti +++++++++++++++++++++++v
double GSObarPosCalc::GetFitParamMulti(int tower, int layer, int xy, int param){

	if( param>12 || param<0 ) return -1234;

	return f_multi[tower][layer][xy]->GetParameter( param );

}

// +++++++++++++++++++++++ ReconfigParam +++++++++++++++++++++++v
int GSObarPosCalc::ReconfigParam(){

	//
	//
	// フィッティングのループの中のルーチン。
	// 各１層目と２層目でフィット結果（カイ２乗）を比較する。
	// フィット結果がより良いものから、幅、比と位置のパラメータを抜き出して、次のフィットでもう一方が使えるようにする。
	// 高さは各プレーンの最大値を使う？シングルは良いけども、マルチの場合どうするか？
	//
	//

	// for(int it=0; it<2; ++it){
	//   for(int ixy=0; ixy<2; ++ixy){

	//     // ==== single hit =====
	//     double chi2dof_1st = GetChi2Single(it,0,ixy,"reduced");
	//     double chi2dof_2nd = GetChi2Single(it,1,ixy,"reduced");
	//     double peakh_1st = GetPeakHeightSingle(it, 0, ixy);
	//     double peakh_2nd = GetPeakHeightSingle(it, 0, ixy);

	//     if( chi2dof_1st > chi2dof_2nd && peakh_2nd > noise_cut ){

	// 	// When 2nd layer fitting was better than that of 1st
	// 	double hight = TMath::MaxElement( g_gsobar[it][0][ixy]->GetN(), g_gsobar[it][0][ixy]->GetY());
	// 	if(hight<0) hight=0.000001;
	// 	double* param = f_single[it][1][ixy]->GetParameters();
	// 	f_single[it][0][ixy]->SetParameters( param );
	// 	f_single[it][0][ixy]->SetParameter(2, hight);
	// 	//	cout<<f_single[it][0][ixy]->GetParameter(2)<<endl;

	//     }else if( chi2dof_1st < chi2dof_2nd && peakh_1st > noise_cut ){

	// 	// When 1st layer fitting was better than that of 2nd
	//      	double hight = TMath::MaxElement(g_gsobar[it][1][ixy]->GetN(),g_gsobar[it][1][ixy]->GetY());
	// 	if(hight<0) hight=0.000001;
	// 	double* param = f_single[it][0][ixy]->GetParameters();
	// 	f_single[it][1][ixy]->SetParameters( param );
	// 	f_single[it][1][ixy]->SetParameter(2, hight);
	//     }else{
	// 	// In other case, optimization do not be performed. (No idea)
	//     }

	//     // ==== multi hit ====
	//     chi2dof_1st = GetChi2Multi(it,0,ixy,"reduced");
	//     chi2dof_2nd = GetChi2Multi(it,1,ixy,"reduced");
	//     peakh_1st = GetPeakHeightMulti(it, 0, ixy, 0);
	//     peakh_2nd = GetPeakHeightMulti(it, 1, ixy, 0);
	//     double delta_1st = abs( GetFitParamMulti(it, 0, ixy, 1) - GetFitParamMulti(it, 0, ixy, 7) );
	//     double delta_2nd = abs( GetFitParamMulti(it, 1, ixy, 1) - GetFitParamMulti(it, 1, ixy, 7) );

	//     if( chi2dof_1st > chi2dof_2nd && peakh_2nd > noise_cut && delta_1st > distance_threshold ){
	//     	double* param = f_multi[it][1][ixy]->GetParameters();
	//     	f_multi[it][0][ixy]->SetParameters( param );

	//     }else if( chi2dof_1st < chi2dof_2nd && peakh_1st > noise_cut && delta_2nd > distance_threshold ){
	//     	double* param = f_multi[it][0][ixy]->GetParameters();
	//     	f_multi[it][1][ixy]->SetParameters( param );

	//     }else{
	// 	// do nothing	
	//     }
	//   }
	// }

	return 0;
}

// +++++++++++++++++++++++ GetNumOfPeaksAboveThrehsold  +++++++++++++++++++++++
int GSObarPosCalc::GetNumOfPeaksAboveThrehsold(int tower, int layer, int xy, char* mode, double threshold){

	int nhit2=0;

	if( strcmp(mode,"single") == 0 ){

		// Get the peak height by Eval method from single hit fit function.
		double p_height = GetPeakHeightSingle(tower, layer, xy);

		if( p_height > threshold )
			++nhit2;

	}else if( strcmp(mode,"multi") == 0 ){

		// p_height1 is higher one.
		double p_height1 = GetPeakHeightMulti(tower, layer, xy, 0);
		double p_height2 = GetPeakHeightMulti(tower, layer, xy, 1);

		if( p_height1 > threshold )
			++nhit2;

		if( p_height2 > threshold )
			++nhit2;

		//TSpectrum
		if(nhit[tower][layer][xy] < 2)
			nhit2 = 1;

		double par[11]={};  
		f_multi[tower][layer][xy]->GetParameters( par );

		// distance
		if( abs( par[1]-par[7] ) < distance_threshold )
			nhit2=1;

		// ratio
		if( p_height2 / p_height1 < ratio_threshold )
			nhit2=1;
	}

	return nhit2;
}

// +++++++++++++++++++++++ GetPeakHeightSingle +++++++++++++++++++++++
double GSObarPosCalc::GetPeakHeightSingle(int tower, int layer, int xy){

	double x1 = f_single[tower][layer][xy]->GetParameter( 1 );
	double p_height = f_single[tower][layer][xy]->Eval( x1 );

	return p_height;
}

// +++++++++++++++++++++++ GetPeakHeightMulti +++++++++++++++++++++++
double GSObarPosCalc::GetPeakHeightMulti(int tower, int layer, int xy, int peak){

	// if peak==0 -> return bigger one
	// if peak==1 -> return smaller one

	double h_peak[2]={};

	double par[11]={};  
	f_multi[tower][layer][xy]->GetParameters( par );

	h_peak[0] = par[2]*0.5*( par[4]/pow( par[0], 0.5 ) + (1-par[4])/pow( par[3], 0.5) )   + par[5] ;
	h_peak[1] = par[8]*0.5*( par[10]/pow( par[6], 0.5 ) + (1-par[10])/pow( par[9], 0.5) ) + par[5] ;

	if(peak==0)
		return max( h_peak[0], h_peak[1] );
	else
		return min( h_peak[0], h_peak[1] );
}

// +++++++++++++++++++++++ EvalNumOfHits +++++++++++++++++++++++v
int GSObarPosCalc::EvalNumOfHits(int tower){

	for(int il=0; il<4; ++il){
		for(int ixy=0; ixy<2; ++ixy){
			nhit_each[tower][il][ixy] = EvalNumOfHits(tower, il, ixy);
		}
	}

	// ==== Judge and Return ====

	// --- Null hit case ---- 
	int is_null=1;
	for(int il=0; il<4; ++il){
		for(int ixy=0; ixy<2; ++ixy){
			if( nhit_each[tower][il][ixy]>0 ) is_null=0;
		}
	}
	if( is_null == 1 ){

		nhit_result[tower] = 0;
		return nhit_result[tower];
	}
	// -----------------------

	// --- Multi hit case ----
	// 1st-2nd coincidence  
	for(int ixy=0; ixy<2; ++ixy){
		if( nhit_each[tower][0][ixy] > 1 && nhit_each[tower][1][ixy] > 1 ){

			nhit_result[tower] = 2;
			return nhit_result[tower];
		}
	}

	// x-y coincidence in 1st or 2nd
	for(int il=0; il<2; ++il){
		if( nhit_each[tower][il][0] > 1 && nhit_each[tower][il][1] > 1 ){

			nhit_result[tower] = 2;
			return nhit_result[tower];
		}
	}
	// -----------------------

	// Otherwise this event is regraded as a single event
	nhit_result[tower] = 1;

	return nhit_result[tower];
}

int GSObarPosCalc::EvalNumOfHits(int tower, int layer, int xy){

	int nhit_sh = GetNumOfPeaksAboveThrehsold( tower, layer, xy, "single", noise_cut);
	int nhit_mh = GetNumOfPeaksAboveThrehsold( tower, layer, xy, "multi", noise_cut);

	double fit_comp = GetChi2Single(tower, layer, xy, "reduced") / GetChi2Multi(tower, layer, xy, "reduced"); // >1 -> MH is better

	//if( nhit_mh > 1 && fit_comp > 1.0 ) return 2;
	if(nhit_mh>1) return 2;
	if(nhit_sh>0) return 1;

	// otherwise no peak was found
	return 0;
}

// +++++++++++++++++++++++ GetdE +++++++++++++++++++++++v
double GSObarPosCalc::GetdE(int tower, int layer, int xy){
  
	return h_gsobar[tower][layer][xy]->Integral();
}

// +++++++++++++++++++++++ GetPeakPos +++++++++++++++++++++++v
double GSObarPosCalc::GetPeakPos(int tower, int layer, int xy){

	return GetFitParamSingle(tower, layer, xy, 1);
}

// +++++++++++++++++++++++ GetPeakPosMH +++++++++++++++++++++++v
double GSObarPosCalc::GetPeakPosMH(int tower, int layer, int xy, int peak){

	double pos=0;

	if( peak==0 )
		pos = GetFitParamMulti(tower, layer, xy, 1);
	else
		pos = GetFitParamMulti(tower, layer, xy, 7);

	return pos;
}

// +++++++++++++++++++++++ QuickPos +++++++++++++++++++++++v
double GSObarPosCalc::QuickPos(int tower, int layer, int xy){

	//
	// +++ Calc shower peak by using 'centre of mass' +++
	//

	double pos=0;

	if(tower==0){

		double norm_val = 0;
		double val = 0;

		for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich){
			double pos = (double)ich + 0.5; 
			val       += pos * pow( gsobar_ts_tmp[layer][xy][ich], 3);
			norm_val  += pow( gsobar_ts_tmp[layer][xy][ich],3);
		}

		// --- calc CoM ---
		pos = val/norm_val;	


	}else if(tower==1){

		double norm_val = 0;
		double val = 0;

		for(int ich=0; ich<GSObarPosCalc::NCH40; ++ich){
			double pos = (double)ich + 0.5; 
			val       += pos * pow( gsobar_tl_tmp[layer][xy][ich], 3);
			norm_val  += pow( gsobar_tl_tmp[layer][xy][ich],3);
		}

		// --- calc CoM ---
		pos = val/norm_val;	

	}    

	return pos;

}

// +++++++++++++++++++++++ GetMaximumBin +++++++++++++++++++++++v
int GSObarPosCalc::GetMaximumBin(int tower, int layer, int xy){

	int the_ch = 0;
	double tmp = 0;

	if(tower==0){

		for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich){
			if( gsobar_ts_tmp[layer][xy][ich] > tmp ){
				tmp = gsobar_ts_tmp[layer][xy][ich];
				the_ch = ich;
			}
		}

	}else{

		for(int ich=0; ich<GSObarPosCalc::NCH20; ++ich){
			if( gsobar_ts_tmp[layer][xy][ich] > tmp ){
				tmp = gsobar_ts_tmp[layer][xy][ich];
				the_ch = ich;
			}
		}
	}

	// return the "bin number"
	return the_ch + 1;
}

// +++++++++++++++++++++++ FillMH4Rec +++++++++++++++++++++++
void GSObarPosCalc::FillMH4Rec(RHICfRec* rec, int tower){

	double a1, b1, a2, b2;

	for(int ilay=0; ilay<4; ++ilay){
		for(int ixy=0; ixy<2; ++ixy){

			double param_p1[5]={};
			double param_p2[5]={};

			// filling
			param_p1[0] =  GetFitParamMulti(tower, ilay, ixy, 2); // scale1
			param_p1[1] =  GetFitParamMulti(tower, ilay, ixy, 1); // pos
			param_p1[2] =  GetFitParamMulti(tower, ilay, ixy, 0); // width1
			param_p1[3] =  GetFitParamMulti(tower, ilay, ixy, 3); // width2
			param_p1[4] =  GetFitParamMulti(tower, ilay, ixy, 4); // ratio

			param_p2[0] =  GetFitParamMulti(tower, ilay, ixy, 8); // scale1
			param_p2[1] =  GetFitParamMulti(tower, ilay, ixy, 7); // pos
			param_p2[2] =  GetFitParamMulti(tower, ilay, ixy, 6); // width1
			param_p2[3] =  GetFitParamMulti(tower, ilay, ixy, 9); // width2
			param_p2[4] =  GetFitParamMulti(tower, ilay, ixy, 10); // ratio

			// -- add multi hit --
			rec->AddMHHit(tower, ilay, ixy, param_p1);
			rec->AddMHHit(tower, ilay, ixy, param_p2);
		}
	}
}

#endif
