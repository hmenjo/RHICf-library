#ifndef __PMTGAIN_CPP__
#define __PMTGAIN_CPP__

#include "PMTGain.h"

//----------------------------------------------------------------------
//
// This class control the PMT Gain table.
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  17 Aug. 08: copied SPS2007/PMTGain.hh to this and modified somethigs
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//  27 Apr. 17: Implemented a new readout type "3" for RHICf operation by Menjo
//                  PMTGAIN_NHV 11 -> 100
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(PMTGain);
#endif


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <math.h>
using namespace std;

const int PMTGain::PMTGAIN_OK;
const int PMTGain::PMTGAIN_ERROR;
const int PMTGain::PMTGAIN_NODATA;

const int PMTGain::PMTGAIN_ND; 
const int PMTGain::PMTGAIN_NT; 
const int PMTGain::PMTGAIN_NP;
const int PMTGain::PMTGAIN_NHV;

//______________________________________________________________________________
// This class control the gain table for the PMTs of the two calorimeters. 


//______________________________________________________________________________
PMTGain::PMTGain(){
  Initalize();
}

//______________________________________________________________________________
PMTGain::PMTGain(char* file){
  Initalize();
  ReadTable(file);
}

int PMTGain::Initalize(){
  strcpy(format,"NO_FORMAT");
  version = PMTGAIN_NODATA;
  type   =  PMTGAIN_NODATA;
  date   =  PMTGAIN_NODATA;

  nhv = 0;
  for(int ihv=0;ihv<PMTGAIN_NHV;ihv++){
    hv[ihv] = 0.;
  }
  
  for(int id=0;id<PMTGAIN_ND;id++){
    for(int it=0;it<PMTGAIN_NT;it++){
      for(int ip=0;ip<PMTGAIN_NP;ip++){
	strcpy( sn[id][it][ip] , "NODATA");
	caln[id][it][ip] = PMTGAIN_NODATA;
	for(int ihv=0;ihv<PMTGAIN_NHV;ihv++){
	  gain[id][it][ip][ihv] = 0.;
	}
      }
    }
  }
  return PMTGAIN_OK;
}


int PMTGain::ReadTable(char* file){
  ifstream fin(file);
  if(!fin){
    cerr << "[PMTGain::ReadTable] Cannot Open " << file << endl;
    return PMTGAIN_ERROR;
  }

  char a[256];
  bool check_param = false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    if(strcmp(a,"PARAM_END")==0){check_param=false;break;}
    
    if(check_param!=true){continue;}
    if(strcmp(a,"FORMAT_TYPE:")==0){
      fin >> a;
      if(strcmp(a,"PMT_GAIN")==0){
	strcpy(format,a);
      }
      else {
	cerr << "[ReadTable] " << file << " is not PMT_GAIN format file."
	     << endl;
	return PMTGAIN_ERROR;
      }
    }
    if(strcmp(a,"FORMAT:")==0){fin >> type;}
    if(strcmp(a,"VERSION:")==0){fin >> version;}
    if(strcmp(a,"DATE:")==0){fin >> date;}
  }
  fin.close();
  strcpy(tablefile,file);
  if(type==2) {
    return ReadTableType2();
  }
  else if(type==3) {
    return ReadTableType3();
  } 
  else{
    cerr << "[ReadTable] Type is not correct." << endl;
    return PMTGAIN_ERROR;
  }
}

int PMTGain::ReadTableType2(){
  ifstream fin(tablefile);
  if(!fin){  return PMTGAIN_ERROR; }
  
  char a[256];
  bool check_data = false;
  int    id,itower,it,il,icaln;
  char   isn[10];
  double ig[PMTGAIN_NHV];
  
  while(1){
    fin >> a; 
    if(fin.eof()){break;}
    if(strcmp(a,"DATA_START")==0){check_data=true;}
    if(strcmp(a,"DATA_END")==0){check_data=false;break;}
    
    if(check_data!=true){continue;}
    if(strcmp(a,"D")==0){
      fin >> id >> itower >> it >> il >> isn >> icaln;
      if((id != 1 && id !=2) ||
	 (itower!=20 && itower!=40 && itower!=25 && itower!=32) ||
	 (il <0 && il >=4)){
	continue;
      }
      id = id -1;
      strcpy(sn[id][TSize2iT(itower)][il],isn);
      caln[id][TSize2iT(itower)][il] = icaln;
      for(int ihv=0;ihv<11;ihv++){
	fin >> ig[ihv];
	gain[id][TSize2iT(itower)][il][ihv] = ig[ihv];
      }
    }  
  }
  
  nhv = 11;
  hv[0] = 1100.;
  hv[1] = 1000.;
  hv[2] = 800.;
  hv[3] = 600.;
  hv[4] = 550.;
  hv[5] = 500.;
  hv[6] = 475.;
  hv[7] = 450.;
  hv[8] = 425.;
  hv[9] = 400.;
  hv[10] = 375.;
  
  return PMTGAIN_OK;
}

int PMTGain::ReadTableType3(){
  ifstream fin(tablefile);
  if(!fin){  return PMTGAIN_ERROR; }
  
  char a[256];
  bool check_data = false;
  int    id,itower,il;
  double ig[PMTGAIN_NHV];
  
  while(1){
    fin >> a; 
    if(fin.eof()){break;}
    if(strcmp(a,"DATA_START")==0){check_data=true;}
    if(strcmp(a,"DATA_END")==0){check_data=false;break;}
    
    if(check_data!=true){continue;}
    if(strcmp(a,"D")==0){
      fin >> id >> itower >> il;
      if((id != 1 && id !=2) ||
	 (itower!=20 && itower!=40 && itower!=25 && itower!=32) ||
	 (il <0 && il >=16)){
	continue;
      }
      id = id -1;
      for(int ihv=0;ihv<101;ihv++){
	fin >> ig[ihv];
	gain[id][TSize2iT(itower)][il][ihv] = ig[ihv];
      }
    }  
  }
  
  nhv = 101;
  for(int i=0;i<nhv;i++){
    hv[i] = 1000. - 5.*i;
  }
  
  return PMTGAIN_OK;
}

double  PMTGain::GetGain(int id,int it,int il,int ihv){
  id = id-1;
  if((id<0  || id  >=PMTGAIN_ND) ||
     (it<0  || it  >=PMTGAIN_NT) ||
     (il<0  || il  >=PMTGAIN_NP) ||
     (ihv<0 || ihv >= nhv)){ return PMTGAIN_NODATA ;}
 
  return gain[id][it][il][ihv];
}

double  PMTGain::GetGain(int id,int it,int il,double hvv){
  return GetGain(id,it,il,HV2nHV(hvv));
}

double  PMTGain::GetGain(int it,int il,int ihv){
  return GetGain(TSize2D(it),TSize2iT(it),il,ihv);
} 

double PMTGain::GetGain(int it,int il,double hvv){
  return GetGain(TSize2D(it),TSize2iT(it),il,HV2nHV(hvv));
}

int  PMTGain::HV2nHV(double tmp){
  if(type==2){
    double range=1.0;
    if     (fabs(tmp-1100.)<range){return  0;}
    else if(fabs(tmp-1000.)<range){return  1;}
    else if(fabs(tmp- 800.)<range){return  2;}
    else if(fabs(tmp- 600.)<range){return  3;}
    else if(fabs(tmp- 550.)<range){return  4;}
    else if(fabs(tmp- 500.)<range){return  5;}    
    else if(fabs(tmp- 475.)<range){return  6;}
    else if(fabs(tmp- 450.)<range){return  7;}    
    else if(fabs(tmp- 425.)<range){return  8;} 
    else if(fabs(tmp- 400.)<range){return  9;}    
    else if(fabs(tmp- 375.)<range){return 10;}  
  }  
  else if(type==3){
    return (int)((1000.001-tmp)/5.);
  }
  
  return PMTGAIN_ERROR;
}
int  PMTGain::TSize2iD(int size){
  if     (size==20){return 0;}
  else if(size==40){return 0;}
  else if(size==25){return 1;}
  else if(size==32){return 1;}
  else {return PMTGAIN_ERROR;}
}

int  PMTGain::TSize2D(int size){
  if     (size==20){return 1;}
  else if(size==40){return 1;}
  else if(size==25){return 2;}
  else if(size==32){return 2;}
  else {return PMTGAIN_ERROR;}
}

int  PMTGain::TSize2iT(int size){
  if     (size==20){return 0;}
  else if(size==40){return 1;}
  else if(size==25){return 0;}
  else if(size==32){return 1;}
  else {return PMTGAIN_ERROR;}
}

int  PMTGain::iT2TSize(int id ,int it){
  if     (id==0 && it==0) {return 20;}
  else if(id==0 && it==1) {return 40;}
  else if(id==1 && it==0) {return 25;}
  else if(id==1 && it==1) {return 32;}
  else {return PMTGAIN_ERROR;}
}

int  PMTGain::PrintStatus(){
  cout << "FORMAT: " << format << endl
       << " TABLEFILE: " << tablefile << endl 
       << " TYPE: " << setw(3) << type << "  "
       << " VERSION: " << setw(3) << version << endl;
  return PMTGAIN_OK;
}


#endif 


// void test(){ 
//     PMTGain pg; 
//     cout << pg.ReadTable("../tables/GainsheetforCERN060812_1609.txt") << endl; 
//     pg.PrintStatus(); 
  
//     cout << pg.GetGain(20,0,0) << endl; 
  

// } 
