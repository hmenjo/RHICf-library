#ifndef  __CONPARTICLEDEFINE_CPP__
#define  __CONPARTICLEDEFINE_CPP__

#include "ConParticleDefine.h"

//----------------------------------------------------------------------
// this class is for controling particle table
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  17 Aug. 08: Copied SPS2007/ConParticleDefine.hh
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ConParticleDefine);
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

const int    ConParticleDefine::CONPARTICLEDEFINE_OK;
const int    ConParticleDefine::CONPARTICLEDEFINE_ERROR;
const char  *ConParticleDefine::CONPARTICLEDEFINE_FORMAT= "PARTICLE_DEFINE";
const double ConParticleDefine::DEFALUT_DEF_SILICON = 1.0;

ConParticleDefine::ConParticleDefine(){
  Initialize();
}

ConParticleDefine::ConParticleDefine(char* file,char option[]){
  Initialize();
  ReadFile(file,option); 
}

ConParticleDefine::~ConParticleDefine(){;}

int ConParticleDefine::Initialize(){
  strcpy(tablefile,"");
  strcpy(format,CONPARTICLEDEFINE_FORMAT);
  type = 0;
  version = 0;
 
  detector = 0;
  hv0 = 1000;
  hv1 = 1000;
  scifihv = 950;

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      def_cal[it][il] = 1.0;
    }
  }

  for(int il=0;il<4;il++){
    for(int xy=0;xy<2;xy++){
      for(int pos=0;pos<20;pos++){
	def_scifi0[il][xy][pos] = 1.0;
      }
      for(int pos=0;pos<40;pos++){
	def_scifi1[il][xy][pos] = 1.0;
      }
    }
  }

  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      def_fc[id][ich]=1.0;
    }
  }
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	def_silicon[il][ixy][istrip] = DEFALUT_DEF_SILICON;
      }
    }
  }

  return CONPARTICLEDEFINE_OK;
}

int ConParticleDefine::SetHV(int it,int hv){
  if(it==0){
    hv0 = hv;
    return CONPARTICLEDEFINE_OK;
  }
  else if(it==1){
    hv1 = hv;
    return CONPARTICLEDEFINE_OK;
  }
  return CONPARTICLEDEFINE_ERROR;
} 

double ConParticleDefine::GetHV(int it){
  if(it==0){
    return (double)hv0;
  }
  else if(it==1){
    return (double)hv1;
  }
  return (double) CONPARTICLEDEFINE_ERROR;
}

int ConParticleDefine::SetFCHV(int id,double hv){
  if(id==1){
    fchv1 = hv;
    return CONPARTICLEDEFINE_OK;
  }
  else if(id==2){
    fchv2 = hv;
    return CONPARTICLEDEFINE_OK;
  }
  return CONPARTICLEDEFINE_ERROR;
}

double ConParticleDefine::GetFCHV(int id){
  if(id==1){
    return fchv1;
  }
  else if(id==2){
    return fchv2;
  }
  return CONPARTICLEDEFINE_ERROR;
}

double ConParticleDefine::GetADCParticle(int t,int l){
  if((t==0 || t==1) && (l>=0 && l<16)){
    return def_cal[t][l]; 
  }
  else{
    cerr << "[ConParticleDefine::GetADCParticle] incorrect value" << endl; 
    return CONPARTICLEDEFINE_ERROR;
  }
}

int ConParticleDefine::SetADCParticle(int t,int l,double value){
  if((t==0 || t==1) && (l>=0 && l<16)){
    def_cal[t][l] = value;
    return CONPARTICLEDEFINE_OK;
  }
  else{
    cerr << "[ConParticleDefine::GetADCParticle] incorrect value" << endl; 
    return CONPARTICLEDEFINE_ERROR;
  }
}

double ConParticleDefine::GetSCIFParticle(int it,int il,int xy,int pos){
  if( il< 0 || il>=4 || (xy!=0 && xy!=1)){
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
    return (double)CONPARTICLEDEFINE_ERROR;
  }

  if(it==0 && pos >=0 && pos<20){
    return  def_scifi0[il][xy][pos];
  }
  else if(it==1 && pos >=0 && pos<40){
    return  def_scifi1[il][xy][pos];
  } 
  else {
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
    return (double)CONPARTICLEDEFINE_ERROR;
  }
}

int ConParticleDefine::SetSCIFParticle(int it,int il,int xy,int pos,double value){
  if( il< 0 || il>=4 || (xy!=0 && xy!=1)){
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
      return CONPARTICLEDEFINE_ERROR;
  }

  if(it==0 && pos >=0 && pos<20){
    def_scifi0[il][xy][pos] = value;
    return CONPARTICLEDEFINE_OK;
  }
  else if(it==1 && pos >=0 && pos<40){
    def_scifi1[il][xy][pos] = value;
    return CONPARTICLEDEFINE_OK;
  } 
  else {
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
    return CONPARTICLEDEFINE_ERROR;
  }
}

double ConParticleDefine::GetFCParticle(int id,int ich){
  if( (id==1 || id==2) && (ich>=0 && ich<4)){
    return def_fc[id-1][ich];
  }
  else{
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
    return (double)CONPARTICLEDEFINE_ERROR; 
  }
}

int ConParticleDefine::SetFCParticle(int id,int ich, double value){
  if( (id==1 || id==2) && (ich>=0 && ich<4)){
    def_fc[id-1][ich] = value;
    return CONPARTICLEDEFINE_OK;
  }
  else{
    cerr << "[ConParticleDefine::GetSCIFParticle] incorrect value"  << endl;
    return CONPARTICLEDEFINE_ERROR; 
  }
}

double ConParticleDefine::GetSiliconParticle(int il,int ixy,int istrip){
  // Not error 
  return def_silicon[il][ixy][istrip];
}

int ConParticleDefine::SetSiliconParticle(int il,int ixy,int istrip,double value){
  def_silicon[il][ixy][istrip] = value;
  return CONPARTICLEDEFINE_OK;
}

int ConParticleDefine::SetSiliconParticle(double value){
  int check = CONPARTICLEDEFINE_OK;
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	if(SetSiliconParticle(il,ixy,istrip,value)!= CONPARTICLEDEFINE_OK){
	  check = CONPARTICLEDEFINE_ERROR; 
	}
      }
    }
  }
  return check;
}


int ConParticleDefine::ReadFile(char* file, char option[]){
  ifstream fin(file);
  if(!fin){
    cerr << "[ConParticleDefine::ReadFile] Cannot Open " << file << endl;
    return CONPARTICLEDEFINE_ERROR;
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
  if(strcmp(format,CONPARTICLEDEFINE_FORMAT)==0){
    if(type==1){strcpy(tablefile,file);return ReadType1(option);}
  }
  type=0;
  version=0;
  cerr << "[ConParticleDefine::ReadFile] "
       <<  file << "is not " <<  CONPARTICLEDEFINE_FORMAT << endl;
  return CONPARTICLEDEFINE_ERROR;
}

int ConParticleDefine::ReadType1(char* option){
  ifstream fin(tablefile);
  if(!fin){  return CONPARTICLEDEFINE_ERROR; }
  
  char   a[256];
  bool   check_data = false;
  int    it,il,ixy,ipos,id,ich;
  double value;

  while(1){
    fin >> a; 
    if(fin.eof()){break;}
    if(strcmp(a,"DATA_END")==0){break;}
    if(strcmp(a,"DATA_START")==0){check_data=true;continue;}
    
    if(check_data!=true){continue;}
    if(strcmp(a,"DETECTOR")==0){fin >> detector;}
    if(strstr(option,"ADC")!=NULL){
      if(strcmp(a,"HV0")==0){ fin >> hv0;} 
      if(strcmp(a,"HV1")==0){ fin >> hv1; } 
      if(strcmp(a,"ADC")==0){
	fin >> it >> il >> value;
	SetADCParticle(it,il,value);
      }
    }
    if(strstr(option,"SCIF")!=NULL || strstr(option,"SCIFI")!=NULL){
      if(strcmp(a,"SCIFIHV")==0){
	fin >> scifihv;
      }  
      if(strcmp(a,"SCIF")==0){
	fin >> it >> il >> ixy >> ipos >> value;
	SetSCIFParticle(it,il,ixy,ipos,value);
      }
    }
    if(strstr(option,"FC")!=NULL){
      if(strcmp(a,"FCHV1")==0){
	fin >> fchv1;
      }
      if(strcmp(a,"FCHV2")==0){
	fin >> fchv2;
      }
      if(strcmp(a,"FC")==0){
	fin >> id >> ich >> value;
	SetFCParticle(id,ich,value);
      }
    }
  }

  fin.close();
  return CONPARTICLEDEFINE_OK;
}

int ConParticleDefine::WriteFile(int t,char* file, char option[]){
  strcpy(tablefile,file);
  ofstream fout(file);
  
  if(t!=1){
    cerr << "[ConParticleDefine::WriteFile] " 
	 << t << " is wrong type" << endl;
    return CONPARTICLEDEFINE_ERROR;
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
  if(type==1){return WriteType1(option);}
  return CONPARTICLEDEFINE_ERROR;
}

int ConParticleDefine::WriteType1(char* option){
  ofstream fout;
  fout.open(tablefile,ios::app);
  fout << "DATA_START" << endl;
  fout.setf(ios::fixed);
  if(strstr(option,"ADC")!=NULL){
    fout << "DETECTOR   " << detector << endl; 
    fout << "HV0  " << setw(5) << hv0 << endl;
    for(int i=0;i<16;i++){
      fout << "ADC   0 " << setw(2) << i << " "
	   << setw(8) << setprecision(3) << def_cal[0][i] << endl;
    }
    fout << endl;
    fout << "HV1  " << setw(5) << hv1 << endl;
    for(int i=0;i<16;i++){
      fout << "ADC   1 " << setw(2) << i << " "
	   << setw(8) << setprecision(3) << def_cal[1][i] << endl;
    }
  }
  fout << endl;

  if(strstr(option,"SCIF")!=NULL || strstr(option,"SCIFI")!=NULL){
  fout << "SCIFIHV  " << setw(5) << scifihv << endl;
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ipos=0;ipos<20;ipos++){
	  fout << "SCIF  0 " 
	       << setw(1) << il << " "
	       << setw(1) << ixy << " "
	       << setw(2) << ipos << " "
	       << setw(8) << setprecision(3) << def_scifi0[il][ixy][ipos]
	       << endl;
	}
      }
    }
    
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ipos=0;ipos<40;ipos++){
	  fout << "SCIF  1 " 
	       << setw(1) << il << " "
	       << setw(1) << ixy << " "
	       << setw(2) << ipos << " "
	       << setw(8) << setprecision(3) << def_scifi1[il][ixy][ipos]
	       << endl;
	} 
      }
    }
  }
  
  if(strstr(option,"FC")!=NULL){ 
    fout << "FCHV1  " << setw(5) << fchv1 << endl;
    fout << "FCHV2  " << setw(5) << fchv2 << endl; 
    for(int id=0;id<2;id++){
      for(int ich=0;ich<4;ich++){
	fout << "FC   " 
	     << setw(1) << id+1 << "  " 
	     << setw(1) << ich << "    "
	     << setw(8) << setprecision(3) << def_fc[id][ich];
      }
    }
  }  
  
  fout << "DATA_END" <<endl;
  fout.close();
  return CONPARTICLEDEFINE_OK;
}

int ConParticleDefine::PrintStatus(){
  cout << "FORMAT: " << format << endl
       << " TABLEFILE: " << tablefile << endl;  
  return CONPARTICLEDEFINE_OK;
}

int ConParticleDefine::Copy(ConParticleDefine* obj){
  strcpy(tablefile,obj->tablefile);
  strcpy(format,obj->format);
  type = obj->type;
  version = obj->version;
  
  return CONPARTICLEDEFINE_OK;
}

#endif


// void test(){
//   Cal01* cdata;
//   ConParticleDefine* cond = new ConParticleDefine();
  
//   RunParam* run;
//   RunTable *rtable = new RunTable("../tables/runtable.txt");
//   run = rtable->GetRunParam(402);
//   cond->SetRunParam(run);
  
//   // write
//   cdata = cond->GetData();
//   cdata->cADC0L[0] = 1;
//   cdata->cADC1L[1] = 2;
//   cond->WriteFile(1,"test.out");
// //   // read
// //   cond->ReadFile("test.out");
// //   cout << cond->GetADCParticle(0,0) << endl;
// //   cout << cond->GetADCParticle(1,1) << endl;
// }
