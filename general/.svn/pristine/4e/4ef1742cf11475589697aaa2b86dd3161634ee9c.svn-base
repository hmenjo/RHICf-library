#ifndef __SCIFIGAIN_CPP__
#define __SCIFIGAIN_CPP__

#include "ScifiGain.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//  19 Aug. 16: Some lines were added for 550V operation (MAKINO)
//   1 May  17: Added 650V (Menjo)
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ScifiGain);
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

const char* ScifiGain::SCIFIGAIN_FORMAT = "SCIFI_GAIN";
const int ScifiGain::SCIFIGAIN_NHV;
const int ScifiGain::SCIFIGAIN_OK;
const int ScifiGain::SCIFIGAIN_ERROR;
const int ScifiGain::SCIFIGAIN_NODATA;
const int ScifiGain::SCIFIGAIN_DATA;

ScifiGain::ScifiGain(){
  Initialize();
}

ScifiGain::ScifiGain(char* file){
  Initialize(); 
  ReadTable(file);
}


ScifiGain::~ScifiGain(){;}

int ScifiGain::Initialize(){
  strcpy(format,SCIFIGAIN_FORMAT);
  type = SCIFIGAIN_NODATA;
  version = SCIFIGAIN_NODATA;
  
  nhv = 0;
  for(int ihv=0;ihv<SCIFIGAIN_NHV;ihv++){
    checkhv[ihv]=0;
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
		  for(int ixy=0;ixy<2;ixy++){
			 for(int ip=0;ip<NPos(it);ip++){
				gain[it][il][ixy][ip][ihv] = 1.;
			 }
		  }
      }
    }
  }
  return SCIFIGAIN_OK;
}

int ScifiGain::ReadTable(char* file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ScifiGain::ReadFile] Cannot Open " << file << endl;
    return SCIFIGAIN_ERROR;
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
  if(strcmp(format,SCIFIGAIN_FORMAT)==0){
    if(type==1){strcpy(tablefile,file);return ReadTableType1();}
  }
  type=0;
  version=0;
  cerr << "[ConParticleDefine::ReadFile] "
       <<  file << "is not " <<  SCIFIGAIN_FORMAT << endl;
  return SCIFIGAIN_ERROR;
}

int  ScifiGain::ReadTableType1(){
  ifstream fin(tablefile);
  if(!fin){  return SCIFIGAIN_ERROR; }
  
  char   a[256];
  bool   check_data = false;
  int    it,il,ixy,ip;
  double value,hvv;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"DATA_END")==0){break;}
    if(strcmp(a,"DATA_START")==0){check_data=true;continue;}
    
    if(check_data!=true){continue;}
    if(strcmp(a,"D")==0){
      fin >> it >> il >> ixy >> ip >> hvv >> value;
      if(errorchech(it,il,ixy,ip,HV2nHV(hvv))==SCIFIGAIN_OK){
		  gain[it][il][ixy][ip][HV2nHV(hvv)] = value;
		  checkhv[HV2nHV(hvv)]++;
      }
    }
  }
  fin.close();
  for(int ihv=0;ihv<SCIFIGAIN_NHV;ihv++){
    if(checkhv[ihv]!=0){nhv++;}
  }
  return SCIFIGAIN_OK;
}

int ScifiGain::WriteTable(int t,char* file){
  strcpy(tablefile,file);
  ofstream fout(file);
  if(t!=1){
    cerr << "[ScifiGain::WriteFile] " 
         << t << " is wrong type" << endl;
    return SCIFIGAIN_ERROR;
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
  return SCIFIGAIN_ERROR;
}

int ScifiGain::WriteTableType1(){
  ofstream fout;
  fout.open(tablefile,ios::app);
  fout << "DATA_START" << endl;
  fout.setf(ios::fixed);
  for(int ihv=0;ihv<SCIFIGAIN_NHV;ihv++){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
		  for(int ixy=0;ixy<2;ixy++){
			 for(int ip=0;ip<NPos(it);ip++){
				fout << "D "
					  << setw(2) << it << " "
					  << setw(2) << il << " "
					  << setw(2) << ixy << " "
					  << setw(3) << ip << " "
					  << setw(4) << (int)nHV2HV(ihv) << " "
					  << setw(8) << gain[it][il][ixy][ip][ihv] << endl; 
			 }
		  }
      }
    }
  }
  fout << "DATA_END" <<endl;
  fout.close();
  return SCIFIGAIN_OK;
}

double ScifiGain::GetGain(int it,int il,int ixy,int ipos,int ihv){
  if(errorchech(it,il,ixy,ipos,ihv)==SCIFIGAIN_OK &&
     checkhv[ihv]!=0){
    return gain[it][il][ixy][ipos][ihv];
  }
  else{
    return SCIFIGAIN_ERROR;
  }
}

double ScifiGain::GetGain(int it,int il,int ixy,int ipos,double hvv){
  return GetGain(it,il,ixy,ipos,HV2nHV(hvv));
}

int  ScifiGain::SetGain(int it,int il,int ixy,int ipos,int ihv,double value){
  if(errorchech(it,il,ixy,ipos,ihv)==SCIFIGAIN_OK){
    gain[it][il][ixy][ipos][ihv] = value;
    return SCIFIGAIN_OK;
  } 
  return SCIFIGAIN_ERROR;
}

int  ScifiGain::nHV2HV(int ihv){
  if(ihv==0){return 950;}
  if(ihv==1){return 600;}
  if(ihv==2){return 480;}
  if(ihv==3){return 550;} // makino
  if(ihv==4){return 650;} 
  return SCIFIGAIN_ERROR;
}

int  ScifiGain::HV2nHV(double tmp){
  int itmp = (int) (tmp+0.000001);
  if     (itmp==950){return 0;}
  else if(itmp==600){return 1;}
  else if(itmp==480){return 2;}
  else if(itmp==550){return 3;} // makino
  else if(itmp==650){return 4;} 
  return SCIFIGAIN_ERROR;
}

int  ScifiGain::NPos(int it){
  if(it==0)     {return 20;}
  else if(it==1){return 40;}
  else { return 0;}
}

int ScifiGain::errorchech(int it,int il,int ixy,int ipos,int ihv){
  if(it!=0 && it!=1)  {return SCIFIGAIN_ERROR;}
  if(il<0 || il>=4)   {return SCIFIGAIN_ERROR;}
  if(ixy!=0 && ixy!=1){return SCIFIGAIN_ERROR;}
  if(ipos<0 || ipos>=NPos(it))   {return SCIFIGAIN_ERROR;}
  if(ihv<0 || ihv>=SCIFIGAIN_NHV){return SCIFIGAIN_ERROR;}
  return  SCIFIGAIN_OK;
}

int  ScifiGain::PrintStatus(){
  cout << "FORMAT: " << format << endl
       << " TABLEFILE: " << tablefile << endl;
  return SCIFIGAIN_OK;
}
#endif

// ScifiGain* scifig ;
// void test(){

//   scifig = new ScifiGain();
//   // write
//   scifig->WriteTable(1,"test.out");
//   // read
//   cout << scifig->ReadTable("test.out" ) << endl;
//   cout << scifig->GetGain(1,3,1,39,600.) << endl;

// }
