#ifndef __FCGAIN_CPP__
#define __FCGAIN_CPP__

#include "FCGain.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(FCGain);
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

const char* FCGain::FCGAIN_FORMAT = "FC_GAIN";
const int FCGain::FCGAIN_NHV;
const int FCGain::FCGAIN_OK;
const int FCGain::FCGAIN_ERROR;
const int FCGain::FCGAIN_NODATA;
const int FCGain::FCGAIN_DATA;

FCGain::FCGain(){
  Initialize();
}

FCGain::FCGain(char *file){
  Initialize();
  ReadTable(file);
}

FCGain::~FCGain(){;}

int FCGain::Initialize(){
  strcpy(format,FCGAIN_FORMAT);
  type = FCGAIN_NODATA;
  version = FCGAIN_NODATA;
  
  nhv = 0;
  for(int ihv=0;ihv<FCGAIN_NHV;ihv++){
    checkhv[ihv]=0;
    for(int id=0;id<2;id++){
      for(int ich=0;ich<4;ich++){
	gain[id][ich][ihv] = 1.;
      }
    }
  }
  return FCGAIN_OK;
}

int FCGain::ReadTable(char* file){
  ifstream fin(file);
  if(!fin){
    cerr << "[FCGain::ReadFile] Cannot Open " << file << endl;
    return FCGAIN_ERROR;
  }
  char a[256];
  bool check_param = false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    if(strcmp(a,"PARAM_END")==0){check_param=false;break;}

    if(strcmp(a,"FORMAT:")==0){fin >> format;}
    if(strcmp(a,"TYPE:")==0){fin >> type;}
    if(strcmp(a,"VERSION:")==0){fin >> version;}
  }
  fin.close();
  if(strcmp(format,FCGAIN_FORMAT)==0){
    if(type==1){strcpy(tablefile,file);return ReadTableType1();}
  }
  type=0;
  version=0;
  cerr << "[ConParticleDefine::ReadFile] "
       <<  file << "is not " <<  FCGAIN_FORMAT << endl;
  return FCGAIN_ERROR;
}

int  FCGain::ReadTableType1(){
  ifstream fin(tablefile);
  if(!fin){  return FCGAIN_ERROR; }
  
  char   a[256];
  bool   check_data = false;
  int    id,ich;
  double value,hvv;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"DATA_END")==0){break;}
    if(strcmp(a,"DATA_START")==0){check_data=true;continue;}
    
    if(check_data!=true){continue;}
    if(strcmp(a,"D")==0){
      fin >> id >> ich >> hvv >> value;
      if(SetGain(id,ich,HV2nHV(hvv),value)==FCGAIN_OK){
	checkhv[HV2nHV(hvv)]++;
      }
    }
  }
  fin.close();
  for(int ihv=0;ihv<FCGAIN_NHV;ihv++){
    if(checkhv[ihv]!=0){nhv++;}
  }
  return FCGAIN_OK;
}

int FCGain::WriteTable(int t,char* file){
  strcpy(tablefile,file);
  ofstream fout(file);
  if(t!=1){
    cerr << "[FCGain::WriteFile] " 
         << t << " is wrong type" << endl;
    return FCGAIN_ERROR;
  }
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
       << "COMMENT: "   << endl
       << "PARAM_END" << endl << endl;
  fout.close();
  if(type==1){return WriteTableType1();}
  return FCGAIN_ERROR;
}

int FCGain::WriteTableType1(){
  ofstream fout;
  fout.open(tablefile,ios::app);
  fout << "DATA_START" << endl;
  fout.setf(ios::fixed);
  for(int ihv=0;ihv<FCGAIN_NHV;ihv++){
    for(int id=0;id<2;id++){
      for(int ich=0;ich<4;ich++){
	fout << "D "
	     << setw(2) << id+1 << " "
	     << setw(2) << ich << " ";
	fout.setf(ios::fixed);
	fout << setw(6) << setprecision(1) << nHV2HV(ihv) << " "
	     << setw(8) << setprecision(4) << gain[id][ich][ihv] 
	     << endl; 
	fout.unsetf(ios::fixed);
      }
    }
  }
  fout << "DATA_END" <<endl;
  fout.close();
  return FCGAIN_OK;
}

double FCGain::GetGain(int id,int ich,int ihv){
  if(errorchech(id,ich,ihv)==FCGAIN_OK &&
     checkhv[ihv]!=0){
    return gain[id-1][ich][ihv];
  }
  else{
    return (double)FCGAIN_ERROR;
  }
}

double FCGain::GetGain(int id,int ich,double hvv){
  return GetGain(id,ich,HV2nHV(hvv));
}

int  FCGain::SetGain(int id,int ich,int ihv,double value){
  if(errorchech(id,ich,ihv)==FCGAIN_OK){
    gain[id-1][ich][ihv] = value;
    return FCGAIN_OK;
  } 
  return FCGAIN_ERROR;
}

double  FCGain::nHV2HV(int ihv){
  if(ihv==0){return 3.5;}
  if(ihv==1){return 4.0;}
  return FCGAIN_ERROR;
}

int  FCGain::HV2nHV(double tmp){
  int itmp = (int) (tmp*10);
  if     (itmp==35){return 0;}
  else if(itmp==40){return 1;}
  return FCGAIN_ERROR;
}

int FCGain::errorchech(int id,int ich,int ihv){
  if(id!=1 && id!=2){return FCGAIN_ERROR;}
  if(ihv<0 || ihv>=FCGAIN_NHV){return FCGAIN_ERROR;}
  return  FCGAIN_OK;
}

int  FCGain::PrintStatus(){
  cout << "FORMAT: " << format << endl
       << " TABLEFILE: " << tablefile << endl;
  return FCGAIN_OK;
}
#endif

// FCGain* scifig ;
// void test(){

//   scifig = new FCGain();
//   // write
//   scifig->WriteTable(1,"test.out");
//   // read
//   cout << scifig->ReadTable("test.out" ) << endl;
//   cout << scifig->GetGain(1,3,1,39,600.) << endl;

// }
