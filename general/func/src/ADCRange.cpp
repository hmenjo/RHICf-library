#ifndef  __ADCRANGE_CPP__
#define  __ADCRANGE_CPP__

#include "ADCRange.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ADCRange);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string.h>
using namespace std;

const char* ADCRange::ADCRANGE_FORMAT = "ADCRANGE";
const int ADCRange::ADCRANGE_NADC;
const int ADCRange::ADCRANGE_NPARAM;
const int ADCRange::ADCRANGE_OK;
const int ADCRange::ADCRANGE_ERROR;
const double ADCRange::DEFAULT_THRESHOLD = 3700.;

ADCRange::ADCRange(){
	Initialize();
}

ADCRange::ADCRange(char* file){
	Initialize();
	ReadFile(file);
}

int ADCRange::Initialize(){
	strcpy(tablefile,"");
	strcpy(format,"");
	type   = 0;
	version = 0;

	for(int iadc=0;iadc<ADCRANGE_NADC;iadc++){
		for(int ich=0;ich<16;ich++){
			param[iadc][ich][0] = 0.;
			param[iadc][ich][1] = 8.;
		}
	}
	threshold = DEFAULT_THRESHOLD;

	return ADCRANGE_OK; 
}

int ADCRange::ReadFile(char* file){
	ifstream fin(file);
	if(!fin){
		cerr << "[ADCRange::ReadFile] Cannot Open "
			<< file << endl;
		return ADCRANGE_ERROR;
	}
	strcpy(tablefile,file);

	char a[256];
	bool check_param=false;
	bool check_data=false;
	while(1){
		fin >> a;
		if(fin.eof()){break;}
		if(strcmp(a,"PARAM_END")==0){break;}
		if(strcmp(a,"PARAM_START")==0){check_param=true;}
		if(check_param==true){
			if(strcmp(a,"FORMAT:")==0){ fin >> format; }
			if(strcmp(a,"TYPE:")==0){fin >> type;}
			if(strcmp(a,"VERSION:")==0){fin >> version;}
		}
	}

	if(strcmp(format,ADCRANGE_FORMAT)!=0){
		cerr << "[ADCRange::ReadFile] this is not "
			<< ADCRANGE_FORMAT
			<< endl;
		return ADCRANGE_ERROR;
	}

	//FILE* frange;
	//frange = fopen("/ccj/u/mhkim/RHICf/analysis/Reconstruction/STARdb/adcpar.txt", "w");

	int    iadc,ich;
	double p[2];
	if(type==1){
		while(1){
			fin >> a;
			if(fin.eof()){break;}
			if(strcmp(a,"DATA_END")==0){break;}
			if(strcmp(a,"DATA_START")==0){check_data=true;}

			if(strcmp(a,"ADC")==0){
				fin >> iadc >> ich >> p[0] >> p[1];
				SetParameters(iadc,ich,p);
				/*if(iadc<2){ 
					fprintf(frange, "%f\n", p[0]);
					fprintf(frange, "%f\n", p[1]);
				}*/
			}
		} 
		fin.close();
		return ADCRANGE_OK;
	}
	else {
		fin.close();
		return ADCRANGE_ERROR;
	}

	//fclose(frange);
}

int ADCRange::WriteFile(int t,char* file,char comment[]){
	strcpy(tablefile,file);
	ofstream fout(file);
	if(t!=1){
		cerr << "[ADCRange::WriteFile] "
			<< t << " is wrong type" << endl;
		return ADCRANGE_ERROR;
	}

	strcpy(format,ADCRANGE_FORMAT);
	type = t;
	time_t nowtime;
	struct tm *lt;
	char timestamp[10];
	time(&nowtime);
	lt = localtime(&nowtime);

	sprintf(timestamp,"%02d%02d%02d",lt->tm_year%100,lt->tm_mon+1,lt->tm_mday);
	fout << "PARAM_START" << endl
		<< "FORMAT:  " << format << endl
		<< "TYPE:    " << t << endl
		<< "VERSION: " << version << endl
		<< "DATE:    " << timestamp << endl
		<< "COMMENT: " << comment <<  endl
		<< "PARAM_END" << endl << endl;

	if(t==1){
		fout << "DATA_START" << endl;
		fout.setf(ios::fixed);
		for(int iadc=0;iadc<ADCRANGE_NADC;iadc++){
			for(int ich=0;ich<16;ich++){
				fout << "ADC  " 
					<< setw(2) << iadc << " "
					<< setw(2) << ich  << "  "
					<< setw(10) << setprecision(5) << param[iadc][ich][0] << "  "
					<< setw(10) << setprecision(7) << param[iadc][ich][1] << " "
					<< endl;
			} 
		} 
		fout << "DATA_END" <<endl;
		fout.close();
		return ADCRANGE_OK;
	}

	return ADCRANGE_ERROR;
}


int ADCRange::SetParameters(int iadc,int ich, double p[]){
	return SetParameter(iadc,ich,0,p[0]) + SetParameter(iadc,ich,1,p[1]);
}

int ADCRange::SetParameter(int iadc,int ich, int ip, double p){
	if(iadc<0 || iadc>=ADCRANGE_NADC ||
			ich<0  || ich>=16 ||
			ip<0   || ip >=ADCRANGE_NPARAM){
		cerr << "[ADCRange::SetParam] Paremater Error" << endl;
		return ADCRANGE_ERROR;
	}
	param[iadc][ich][ip] = p;
	return ADCRANGE_OK;
}

double ADCRange::GetParameter(int iadc,int ich, int ip){
	return param[iadc][ich][ip];
}

double ADCRange::Get(int iadc,int ich, double adcr, double adch){
	//printf("tower:%d, plate:%d, p0:%f, p1:%f\n", iadc, ich, param[iadc][ich][0], param[iadc][ich][1]);
	if(adcr<threshold){
		return adcr;
	}
	else{
		return param[iadc][ich][0] + param[iadc][ich][1]*adch;
	}
}

#endif
