#ifndef __A2GAINCALIBRATION_CPP__
#define __A2GAINCALIBRATION_CPP__

#include "A2GainCalibration.h"

//---------------------------------------------------------------------- 
//
//  this is for gain calibration of Arm#2 data.
//  for online analysis,
//   Bor: try to get H.V. value from slow control server through TCP/IP
//        protcol. If the connection is failed, it read config/hvtable.txt
//   Loop: Data of only PMT and FC are calibrated in this function
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  19 Aug. 08: First Edited by H.MENJO
//  22 Aug. 08: Added Socket connection to get H.V. and L.V. value from
//              Slow control server in online analysis
//  27 Mar. 09: Comment-out "#if--#endif" before/after SocketControl
//              to be compiled via rootcint
//  26 Jan. 10: Add a function : GetParticleADC()
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO.
//
//---------------------------------------------------------------------- 


#if !defined(__CINT__)
ClassImp(A2GainCalibration);
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const double A2GainCalibration::DEFAULT_PDEFFACTOR_PMT = 0.896; // SPS2007 pdef -> LHC pdef
const double A2GainCalibration::DEFAULT_PDEFFACTOR_SILICON = 1.0; //
const double A2GainCalibration::DEFAULT_PDEFFACTOR_FC = 0.896; // ???? 
const char*  A2GainCalibration::DEFAULT_PDEFTABLE="./config/pdef_sps07_arm2_081003.out";
const char*  A2GainCalibration::DEFAULT_PMTGAINTABLE="./config/GainsheetforCERN060812_1609.txt";
const char*  A2GainCalibration::DEFAULT_SILICONGAINTABLE="./config/silicongaintable.out";  
const char*  A2GainCalibration::DEFAULT_FCGAINTABLE="./config/fcgaintable_dummy.txt";
const char*  A2GainCalibration::DEFAULT_HVTABLE="./config/hvtable.txt";

int A2GainCalibration::Initialize(){
  detector = 2;
  
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hv[it][il] = 1000.;
    }
  }
  siliconhv = 100;
  fchv[0] = 4.0;
  fchv[1] = 4.0;
  
  pdeffactor_pmt     = DEFAULT_PDEFFACTOR_PMT;
  pdeffactor_silicon = DEFAULT_PDEFFACTOR_SILICON;
  pdeffactor_fc      = DEFAULT_PDEFFACTOR_FC;
  
  return OK;
}

int A2GainCalibration::ReadParticleDefineTable(char *file,char *option){
  if(pdeftable.ReadFile(file,option)==ConParticleDefine::CONPARTICLEDEFINE_OK){
    if(pdeftable.GetDetector()!=detector){
      cerr << "[A2GainCalibration::ReadParticleDefineTable] Error: "
	   << "Particle define table is not for Arm#2." << endl;
      return ERROR;
    }
    return OK;
  }
  else{
    return ERROR;
  }
}

int A2GainCalibration::ReadPMTGainTable(char *file){
  if(pmtgaintable.ReadTable(file)==PMTGain::PMTGAIN_OK){
    return OK;
  }
  else{
    return ERROR;
  }
}

int A2GainCalibration::ReadSiliconGainTable(char *file){
  if(sigaintable.ReadTable(file)==OK){
    return OK;
  }
  else{
    return ERROR;
  }
  return OK;
}

int A2GainCalibration::ReadFCGainTable(char *file){
  if(fcgaintable.ReadTable(file)==FCGain::FCGAIN_OK){
    return OK;
  }
  else{
    return ERROR;
  }
}

int A2GainCalibration::SetHV(int it,int il, double value){
  hv[it][il] = value;
  return OK;
}

int A2GainCalibration::SetSiliconHV(double value){ 
  siliconhv = value;
  return OK;
}

int A2GainCalibration::SetFCHV(int id,double value){
  if(id!=1 && id!=2){
    cerr <<  "[A2GainCalibration::SetFCHV] incorrect value" << endl;
    return ERROR;
  }
  fchv[id-1] = value;
  return OK;
}

int A2GainCalibration::SetPdefFactorPMT(double value){
  pdeffactor_pmt = value;
  return OK;
}

int A2GainCalibration::SetPdefFactorSilicon(double value){
  pdeffactor_silicon = value;
  return OK;
}

int A2GainCalibration::SetPdefFactorFC(double value){
  pdeffactor_fc = value;
  return OK;
}

int A2GainCalibration::ReadHVTable(char* file,char* option){
  ifstream fin(file);
  if(!fin){
    cerr << "[A2GainCalibration::ReadHVTable] Cannot Open " << file << endl;
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
    cerr << "[A2GainCalibration::ReadHVTable] ERROR: "
	 << file  << " is not \"HVTABLE\"." << endl;
    cerr << format << endl;
    return ERROR;
  }

  if(type==2){ 
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
      if(strcmp(a,"SILICONHV")==0 && 
	 (strstr(option,"SILICON")!=NULL || strstr(option,"SILI")!=NULL)){
	fin >> siliconhv;
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
    cerr << "[A2GainCalibration::ReadHVTable] ERROR: "
	 << "TYPE: " << type << " is wrong number. 2 should be used" << endl;
    return ERROR;
  }
  
  return ERROR;
}

int A2GainCalibration::ShowHVTable(){
  string s;
  ShowHVTable(s);
  cout << s ;
  return OK;
}

int A2GainCalibration::ShowHVTable(string &s){
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
  sout << "  SILICONHV " << setw(7) << setprecision(1) << siliconhv << endl;
  sout << "  FCHV1     " << setw(6) << setprecision(3) << fchv[0] << endl;
  sout << "  FCHV2     " << setw(6) << setprecision(3) << fchv[1] << endl; 
  s = sout.str();
  return OK;
}

// ****************************************************************************
//                                 Calculate   
// ****************************************************************************

double A2GainCalibration::GetParticleADC(int it,int il){
  return   ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt) 
          *( pmtgaintable.GetGain(detector,it,il,hv[it][il])
	   / pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it)));
}

int A2GainCalibration::Calculate(A2Cal2* data){
  if( CalculatePMT(data)==ERROR){return ERROR;}
  if( CalculateSilicon(data)==ERROR){return ERROR;}
  if( CalculateFC(data)==ERROR){return ERROR;}
  return OK;
}

int A2GainCalibration::CalculatePMT(A2Cal2* data){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
	data->cal[it][il] = data->cal[it][il]
	/ pmtgaintable.GetGain(detector,it,il,hv[it][il])
	* pmtgaintable.GetGain(detector,it,il,(double)pdeftable.GetHV(it))
	/ ( pdeftable.GetADCParticle(it,il) * pdeffactor_pmt);
    }
  }
  return OK;
}

int A2GainCalibration::CalculateSilicon(A2Cal2* data){
  // Temporal codes
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  data->silicon[il][ixy][istrip][isample] = data->silicon[il][ixy][istrip][isample]
	    *  sigaintable.GetGain(il,ixy,istrip)
	    / ( pdeftable.GetSiliconParticle(il,ixy,istrip) * pdeffactor_silicon);
	}
      }
    }
  }
  return OK;
}

int A2GainCalibration::CalculateFC(A2Cal2* data){
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

int A2GainCalibration::InverseCalculate(A2Cal2* data){
  if( InverseCalculatePMT(data)==ERROR){return ERROR;}
  if( InverseCalculateSilicon(data)==ERROR){return ERROR;}
  if( InverseCalculateFC(data)==ERROR){return ERROR;}
  return OK;
}

int A2GainCalibration::InverseCalculatePMT(A2Cal2* data){
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

int A2GainCalibration::InverseCalculateSilicon(A2Cal2* data){
  // Temporal codes
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  data->silicon[il][ixy][istrip][isample] = data->silicon[il][ixy][istrip][isample] 
	    * ( pdeftable.GetSiliconParticle(il,ixy,istrip) * pdeffactor_silicon)
	    / sigaintable.GetGain(il,ixy,istrip); 
	}
      }
    }
  }
  return OK;
}

int A2GainCalibration::InverseCalculateFC(A2Cal2* data){
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
//#if !defined(__CINT__)
int A2GainCalibration::Init(){
  if( ReadParticleDefineTable((char*)DEFAULT_PDEFTABLE) == OK){
    cout << "[A2GainCalibration] Particle Table: Red " << DEFAULT_PDEFTABLE << endl;
  }
  if( ReadPMTGainTable((char*) DEFAULT_PMTGAINTABLE) == OK){
    cout << "[A2GainCalibration] PMT Gain Table: Red " << DEFAULT_PMTGAINTABLE << endl;
  }
  if( ReadFCGainTable((char*) DEFAULT_FCGAINTABLE) == OK){
    cout << "[A2GainCalibration] FC Gain Table:  Red " << DEFAULT_FCGAINTABLE << endl;
  }
  return OK;
}

int A2GainCalibration::Exit(){
  return OK;
}

int A2GainCalibration::Bor(){
  if( ReadHVTable((char*) DEFAULT_HVTABLE) == OK){
    cout << "[A2GainCalibration] Red H.V. Table [" <<  DEFAULT_HVTABLE << "]" << endl;
  }
  return OK;
}

int A2GainCalibration::Loop(A2Cal2* data){
  CalculatePMT(data);
  CalculateFC(data);
  return OK;
}

#endif
