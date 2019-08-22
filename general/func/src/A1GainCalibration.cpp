#ifndef __A1GAINCALIBRATION_CPP__
#define __A1GAINCALIBRATION_CPP__

#include "A1GainCalibration.h"

//---------------------------------------------------------------------- 
//
//  this is for gain calibration of Arm#1 data.
//  for online analysis,
//   Bor: try to get H.V. value from slow control server through TCP/IP
//        protcol. If the connection is failed, it read config/hvtable.txt
//   Loop: Data of only PMT and FC are calibrated in this function
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  19 Aug. 08: First Edited by H.MENJO
//  22 Aug. 08: Added Socket connection to get H.V. and L.V. value from
//              Slow control server in online analysis
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO.
//  26 Apr. 15: Set new conversion-factor table (Y.Makino)
//---------------------------------------------------------------------- 

#if !defined(__CINT__)
ClassImp(A1GainCalibration);
#endif


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const double A1GainCalibration::DEFAULT_PDEFFACTOR_PMT = 0.896;
const double A1GainCalibration::DEFAULT_PDEFFACTOR_SCIFI = 1.0;
const double A1GainCalibration::DEFAULT_PDEFFACTOR_FC = 0.896;
//const char*  A1GainCalibration::DEFAULT_PDEFTABLE="./config/pdef_MUON_HV1000_01_070908.out";
const char*  A1GainCalibration::DEFAULT_PDEFTABLE="./config/20150523_conversion_factors.tab";//op2015 Makino
const char*  A1GainCalibration::DEFAULT_PMTGAINTABLE="./config/GainsheetforCERN060812_1609.txt";
//const char*  A1GainCalibration::DEFAULT_SCIFIGAINTABLE="./config/scifigaintable_071219.out";  
const char*  A1GainCalibration::DEFAULT_SCIFIGAINTABLE="./config/scifigaintable_150526.out";  
const char*  A1GainCalibration::DEFAULT_FCGAINTABLE="./config/fcgaintable_dummy.txt";  
const char*  A1GainCalibration::DEFAULT_HVTABLE="./config/hvtable.txt";

int A1GainCalibration::Initialize(){
	detector = 1;

	for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
			hv[it][il] = 1000.;
		}
	}
	scifihv = 950;
	fchv[0] = 4.0;
	fchv[1] = 4.0;

	pdeffactor_pmt   = DEFAULT_PDEFFACTOR_PMT;
	pdeffactor_scifi = DEFAULT_PDEFFACTOR_SCIFI;
	pdeffactor_fc    = DEFAULT_PDEFFACTOR_FC;

	return OK;
}

int A1GainCalibration::ReadParticleDefineTable(char *file,char *option){
	if(pdeftable.ReadFile(file,option)==ConParticleDefine::CONPARTICLEDEFINE_OK){
		if(pdeftable.GetDetector()!=detector){
			cerr << "[A1GainCalibration::ReadParticleDefineTable] Error: "
				<< "Particle define taable is not for Arm#1." << endl;
			return ERROR;
		}
		return OK;
	}
	else{
		return ERROR;
	}
}

int A1GainCalibration::ReadPMTGainTable(char *file){
	if(pmtgaintable.ReadTable(file)==PMTGain::PMTGAIN_OK){
		return OK;
	}
	else{
		return ERROR;
	}
}

int A1GainCalibration::ReadScifiGainTable(char *file){
	if(scifigaintable.ReadTable(file)==ScifiGain::SCIFIGAIN_OK){
		return OK;
	}
	else{
		return ERROR;
	}
}

int A1GainCalibration::ReadFCGainTable(char *file){
	if(fcgaintable.ReadTable(file)==FCGain::FCGAIN_OK){
		return OK;
	}
	else{
		return ERROR;
	}
}

int A1GainCalibration::SetHV(int it,int il, double value){
	hv[it][il] = value;
	return OK;
}

int A1GainCalibration::SetScifiHV(double value){ 
	scifihv = value;
	return OK;
}

int A1GainCalibration::SetFCHV(int id,double value){
	if(id!=1 && id!=2){
		cerr <<  "[A1GainCalibration::SetFCHV] incorrect value" << endl;
		return ERROR;
	}
	fchv[id-1] = value;
	return OK;
}

int A1GainCalibration::SetPdefFactorPMT(double value){
	pdeffactor_pmt = value;
	return OK;
}

int A1GainCalibration::SetPdefFactorScifi(double value){
	pdeffactor_scifi = value;
	return OK;
}

int A1GainCalibration::SetPdefFactorFC(double value){
	pdeffactor_fc = value;
	return OK;
}

int A1GainCalibration::ReadHVTable(char* file,char* option){
	ifstream fin(file);
	if(!fin){
		cerr << "[A1GainCalibration::ReadHVTable] Cannot Open " << file << endl;
		return ERROR;
	}
	char a[256];
	bool check_param = false;
	char format[256];
	int  type=0;
	int  version=0;
	while(1){
		fin >> a;
		if(fin.eof()){break;}
		if(strcmp(a,"PARAM_START")==0){check_param=true;continue;}
		if(strcmp(a,"PARAM_END")==0){check_param=false;break;}
		if(check_param!=true){continue;}

		if(strcmp(a,"FORMAT:")==0){fin >> format;}
		if(strcmp(a,"TYPE:")==0){fin >> type;}
		if(strcmp(a,"VERSION:")==0){fin >> version;}
	}

	if(strcmp(format,"HVTABLE")!=0){
		cerr << "[A1GainCalibration::ReadHVTable] ERROR: "
			<< file  << " is not \"HVTABLE\"." << endl;
		cerr << format << endl;
		return ERROR;
	}

	if(type==1){ 
		bool check_data = false;
		while(1){
			fin >> a;
			if(fin.eof()){break;}
			if(strcmp(a,"DATA_END")==0){break;}
			if(strcmp(a,"DATA_START")==0){check_data=true;continue;}

			if(strcmp(a,"HV0")==0 &&
					(strstr(option,"ADC")!=NULL || strstr(option,"PMT")!=NULL)){
				for(int i=0;i<16;i++){
					fin >> hv[0][i];
				}
			}
			if(strcmp(a,"HV1")==0 && 
					(strstr(option,"ADC")!=NULL || strstr(option,"PMT")!=NULL)){
				for(int i=0;i<16;i++){
					fin >> hv[1][i];
				}
			}
			if(strcmp(a,"SCIFIHV")==0 && 
					(strstr(option,"SCIFI")!=NULL || strstr(option,"SCIF")!=NULL)){
				fin >> scifihv;
			}
			if(strcmp(a,"FCHV1")==0 && strstr(option,"FC")!=NULL ){
				fin >> fchv[0];
			}
			if(strcmp(a,"FCHV2")==0 && strstr(option,"FC")!=NULL ){
				fin >> fchv[1];
			}
		}
		fin.close();
		return OK;
	}
	else{
		cerr << "[A1GainCalibration::ReadHVTable] ERROR: "
			<< "TYPE: " << type << " is wrong number. 1 should be used" << endl;
		return ERROR;
	}

	return ERROR;
}

int A1GainCalibration::ShowHVTable(){
	string s;
	ShowHVTable(s);
	cout << s ;
	return OK;
}

int A1GainCalibration::ShowHVTable(string &s){
	ostringstream sout;
	sout.setf(ios::fixed);
	sout << "  HV0 " ;
	for(int i=0;i<16;i++){
		if(i==8) sout << endl << "      " ;
		sout << setw(7) << setprecision(1) << hv[0][i] << " "; 
	}
	sout << endl;
	sout << "  HV1 " ;
	for(int i=0;i<16;i++){
		if(i==8) sout << endl << "      " ;
		sout << setw(7) << setprecision(1) << hv[1][i] << " "; 
	}
	sout << endl;
	sout << "  SCIFIHV " << setw(7) << setprecision(1) << scifihv << endl;
	sout << "  FCHV1   " << setw(6) << setprecision(3) << fchv[0] << endl;
	sout << "  FCHV2   " << setw(6) << setprecision(3) << fchv[1] << endl; 
	s = sout.str();
	return OK;
}

// ****************************************************************************
//                                 Calculate   
// ****************************************************************************

	double A1GainCalibration::GetParticleADC(int it,int il){
		return   ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt) 
			*( pmtgaintable.GetGain(detector,it,il,hv[it][il])
					/ pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it)));
	}

int A1GainCalibration::Calculate(A1Cal2* data){
	if( CalculatePMT(data)==ERROR){return ERROR;}
	if( CalculateScifi(data)==ERROR){return ERROR;}
	if( CalculateFC(data)==ERROR){return ERROR;}
	return OK;
}

int A1GainCalibration::CalculatePMT(A1Cal2* data){

	//FILE* fplategain;
	//fplategain = fopen("/ccj/u/mhkim/RHICf/analysis/Reconstruction/STARdb/plategain.txt", "w");

	for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
			//printf("tower:%d, plate:%d, adcH2-adcHD=%1.0f\n", it, il, data->cal[it][il]);
			double C = 1
				/ pmtgaintable.GetGain(detector,it,il,hv[it][il])
				* pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it))
				/ ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt);
			//fprintf(fplategain, "%f\n", 100000*C);
			data->cal[it][il] = data->cal[it][il]
				/ pmtgaintable.GetGain(detector,it,il,hv[it][il])
				* pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it))
				/ ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt);
			//printf("tower:%d, plate:%d, E=%f\n", it, il, data->cal[it][il]);
		}
	}
	//fclose(fplategain);
	return OK;
}

int A1GainCalibration::CalculateScifi(A1Cal2* data){

	//FILE* fTSbargain = fopen("/ccj/u/mhkim/RHICf/analysis/Reconstruction/STARdb/TSbargain.txt", "w");
	//FILE* fTLbargain = fopen("/ccj/u/mhkim/RHICf/analysis/Reconstruction/STARdb/TLbargain.txt", "w");

	for(int il=0;il<4;il++){
		for(int ixy=0;ixy<2;ixy++){
			// For Small Tower 
			for(int ip=0;ip<20;ip++){
				if(pdeftable.GetSCIFParticle(0,il,ixy,ip)<0){
					data->scifi0[il][ixy][ip] = -20000.;
				}
				else if(data->scifi0[il][ixy][ip]<-9000){
					data->scifi0[il][ixy][ip] = -10000.;
				}
				else{
					data->scifi0[il][ixy][ip] = data->scifi0[il][ixy][ip]
						/ scifigaintable.GetGain(0,il,ixy,ip,scifihv)
						* scifigaintable.GetGain(0,il,ixy,ip,(double)pdeftable.GetScifiHV())
						/ ( pdeftable.GetSCIFParticle(0,il,ixy,ip) * pdeffactor_scifi);
					/*double gain = 1.
					  / scifigaintable.GetGain(0,il,ixy,ip,scifihv)
					 * scifigaintable.GetGain(0,il,ixy,ip,(double)pdeftable.GetScifiHV())
					 / ( pdeftable.GetSCIFParticle(0,il,ixy,ip) * pdeffactor_scifi);
					 fprintf(fTSbargain, "%f\n", gain);*/
				}
			}
			// For Large Tower 
			for(int ip=0;ip<40;ip++){
				if(pdeftable.GetSCIFParticle(1,il,ixy,ip)<0){
					data->scifi1[il][ixy][ip] = -20000.;
				}
				else if(data->scifi1[il][ixy][ip]<-9000){
					data->scifi1[il][ixy][ip] = -10000.;
				}	  
				else{ 
					data->scifi1[il][ixy][ip] = data->scifi1[il][ixy][ip]
						/ scifigaintable.GetGain(1,il,ixy,ip,scifihv)
						* scifigaintable.GetGain(1,il,ixy,ip,(double)pdeftable.GetScifiHV())
						/ ( pdeftable.GetSCIFParticle(1,il,ixy,ip) * pdeffactor_scifi);
					/*double gain = 1.
					  / scifigaintable.GetGain(1,il,ixy,ip,scifihv)
					 * scifigaintable.GetGain(1,il,ixy,ip,(double)pdeftable.GetScifiHV())
					 / ( pdeftable.GetSCIFParticle(1,il,ixy,ip) * pdeffactor_scifi);
					 fprintf(fTLbargain, "%f\n", gain);*/
				}
			}
		}
	}
	//fclose(fTSbargain);
	//fclose(fTLbargain);

	/*int nbar;
	for(int it=0;it<2;it++){
		for(int il=0;il<4;il++){
			for(int ixy=0;ixy<2;ixy++){
				if(it==0) nbar = 20;
				if(it==1) nbar = 40;
				for(int ibar=0;ibar<nbar;ibar++){
					if(it==0)printf("tower:%d, layer:%d, xy:%d, bar:%d, E = %f\n", it, il, ixy, ibar, data->scifi0[il][ixy][ibar]);
					if(it==1)printf("tower:%d, layer:%d, xy:%d, bar:%d, E = %f\n", it, il, ixy, ibar, data->scifi1[il][ixy][ibar]);
				}
			}

		}
	}*/

	return OK;
}

int A1GainCalibration::CalculateFC(A1Cal2* data){
	for(int id=0;id<2;id++){
		for(int ich=0;ich<4;ich++){
			data->fc[id][ich] = data->fc[id][ich]
				/ fcgaintable.GetGain(id+1,ich,fchv[id])
				* fcgaintable.GetGain(id+1,ich,pdeftable.GetFCHV(id+1))
				/ ( pdeftable.GetFCParticle(id+1,ich) * pdeffactor_fc);
		} 
	} 
	return OK;
}

int A1GainCalibration::InverseCalculate(A1Cal2* data){
	if( InverseCalculatePMT(data)==ERROR){return ERROR;}
	if( InverseCalculateScifi(data)==ERROR){return ERROR;}
	if( InverseCalculateFC(data)==ERROR){return ERROR;}
	return OK;
}

int A1GainCalibration::InverseCalculate_pp2015(A1Cal2* data){
	if( InverseCalculatePMT_pp2015(data)==ERROR){return ERROR;}
	if( InverseCalculateScifi(data)==ERROR){return ERROR;}
	if( InverseCalculateFC(data)==ERROR){return ERROR;}
	return OK;
}

int A1GainCalibration::InverseCalculatePMT(A1Cal2* data){
	for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
			data->cal[it][il] = data->cal[it][il]
				* ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt)
				* pmtgaintable.GetGain(detector,it,il,hv[it][il])
				/ pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it));
		}
	}
	return OK;
}

int A1GainCalibration::InverseCalculatePMT_pp2015(A1Cal2* data){

	for(int it=0;it<2;it++){
		for(int il=0;il<16;il++){
			// org : MIP*(ADC/MIP)*pdeffactor_pmt?*( HV_now / HV_table )       
			// this: GeV*1000*(ADC/MeV)*pdeffactor_pmt?*( HV_now / HV_table )       
			data->cal[it][il] = data->cal[it][il]*1000
				* ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt)
				* pmtgaintable.GetGain(detector,it,il,hv[it][il])
				/ pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it));
		}
	}
	return OK;
}

int A1GainCalibration::InverseCalculateScifi(A1Cal2* data){
	for(int il=0;il<4;il++){
		for(int ixy=0;ixy<2;ixy++){
			for(int ip=0;ip<20;ip++){
				if(pdeftable.GetSCIFParticle(0,il,ixy,ip)>0){
					// data->scifi0[il][ixy][ip] = data->scifi0[il][ixy][ip] 
					//   * ( pdeftable.GetSCIFParticle(0,il,ixy,ip) * pdeffactor_scifi)
					//   * scifigaintable.GetGain(0,il,ixy,ip,scifihv)
					//   / scifigaintable.GetGain(0,il,ixy,ip,(double)pdeftable.GetScifiHV());	  

					// --- for the moment following is more correct---
					data->scifi0[il][ixy][ip] = data->scifi0[il][ixy][ip] 
						* ( pdeftable.GetSCIFParticle(0,il,ixy,ip) * pdeffactor_scifi) 
						* scifigaintable.GetGain(0,il,ixy,ip,scifihv)
						/ scifigaintable.GetGain(0,il,ixy,ip,(double)pdeftable.GetScifiHV());
				}
				else{
					data->scifi0[il][ixy][ip] = 0.;
				}
			}
			for(int ip=0;ip<40;ip++){
				if(pdeftable.GetSCIFParticle(1,il,ixy,ip)>0){
					// data->scifi1[il][ixy][ip] = data->scifi1[il][ixy][ip]	 
					//   * ( pdeftable.GetSCIFParticle(1,il,ixy,ip) * pdeffactor_scifi)
					//   * scifigaintable.GetGain(1,il,ixy,ip,scifihv)
					//   / scifigaintable.GetGain(1,il,ixy,ip,(double)pdeftable.GetScifiHV());

					// --- for the moment following is more correct---
					data->scifi1[il][ixy][ip] = data->scifi1[il][ixy][ip]	 
						* ( pdeftable.GetSCIFParticle(1,il,ixy,ip) * pdeffactor_scifi)
						* scifigaintable.GetGain(1,il,ixy,ip,scifihv)
						/ scifigaintable.GetGain(1,il,ixy,ip,(double)pdeftable.GetScifiHV());
				}
				else{
					data->scifi1[il][ixy][ip] = 0.;
				}
			}
		}
	}
	return OK;
}

int A1GainCalibration::InverseCalculateFC(A1Cal2* data){
	for(int id=0;id<2;id++){
		for(int ich=0;ich<4;ich++){
			data->fc[id][ich] = data->fc[id][ich]
				* ( pdeftable.GetFCParticle(id+1,ich) * pdeffactor_fc)
				* fcgaintable.GetGain(id+1,ich,fchv[id])
				/ fcgaintable.GetGain(id+1,ich,pdeftable.GetFCHV(id+1));
		} 
	} 
	return OK;
}

// ****************************************************************************
//                         FOR ONLINE ANALYSIS    
// ****************************************************************************
int A1GainCalibration::Init(){
	if( ReadParticleDefineTable((char*)DEFAULT_PDEFTABLE) == OK){
		cout << "[A1GainCalibration] Particle Table: Read " << DEFAULT_PDEFTABLE << endl;
	}
	if( ReadPMTGainTable((char*) DEFAULT_PMTGAINTABLE) == OK){
		cout << "[A1GainCalibration] PMT Gain Table: Read " << DEFAULT_PMTGAINTABLE << endl;
	}
	if( ReadFCGainTable((char*) DEFAULT_FCGAINTABLE) == OK){
		cout << "[A1GainCalibration] FC Gain Table:  Read " << DEFAULT_FCGAINTABLE << endl;
	}

	return OK;
}

int A1GainCalibration::Exit(){
	return OK;
}

int A1GainCalibration::Bor(){
	if( ReadHVTable((char*) DEFAULT_HVTABLE) == OK){
		cout << "[A1GainCalibration] Red H.V. Table [" <<  DEFAULT_HVTABLE << "]" << endl;
	}
	return OK;
}

int A1GainCalibration::Loop(A1Cal2* data){
	CalculatePMT(data);
	CalculateFC(data);
	CalculateScifi(data);
	return OK;
}

#endif
