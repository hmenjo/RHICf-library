#ifndef __SCINTIPOSDEPENDENCE_CPP__
#define __SCINTIPOSDEPENDENCE_CPP__

#include "ScintiPosDependence.h"

//----------------------------------------------------------------------
//
// this class control the table of condense efficiency in each scintillator.
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  19 Sep. 08: Copy from SPS2007 Analysis. H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ScintiPosDependence);
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <math.h>
using namespace std;

const int ScintiPosDependence::SCINTIPOSDEPENDENCE_OK;
const int ScintiPosDependence::SCINTIPOSDEPENDENCE_ERROR;

ScintiPosDependence::ScintiPosDependence(){
  Initialize();
}

ScintiPosDependence::ScintiPosDependence(char* file){
  Initialize();
  ReadFile(file);
}

int ScintiPosDependence::Initialize(){
  strcpy(file,"");
  strcpy(format_type,"");
  format  = 0;
  version = 0;
  strcpy(date,"");
  strcpy(person,"");

  for(int j=0;j<4;j++){
    for(int k=0;k<16;k++){
      for(int l=0;l<10;l++){
	C[j][k][l]=0.;
      }
    }
  }

  return SCINTIPOSDEPENDENCE_OK;
}
  
int ScintiPosDependence::ReadFile(char *file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ScintiPosDependence::ReadFile] Cannot Open " 
	 << file << endl;
    return SCINTIPOSDEPENDENCE_ERROR;
  }

  char    a[256];
  double  c[10];
  int     tower,scinti_size,scinti_size_number,scinti_number;
  int     nsize=0;
  bool    check_param=false;
  bool    check_data=false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_END")==0){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}

    if(check_param==true){
      if(strcmp(a,"FORMAT_TYPE:")==0){
	fin >> format_type;
	if(strcmp(format_type,"SCINTI_POSITION")!=0){
	  cerr << "[ScintiPosDependence::ReadFile] this is not SCINTI_POSITION_TABLE."
	       << endl;
	  return SCINTIPOSDEPENDENCE_ERROR;
	}
      }
      if(strcmp(a,"FORMAT:")==0){fin >> format;}
      if(strcmp(a,"VERSION:")==0){fin >> version;}
      if(strcmp(a,"DATE:")==0){fin >> date;}
      if(strcmp(a,"PERSON:")==0){fin >> person;}
    }
  }

  if(format==1){
    while(1){
      fin >> a;
      if(fin.eof()){break;}
      if(strcmp(a,"DATA_END")==0){break;}
      if(strcmp(a,"DATA_START")==0){check_data=true;}

      if(check_data!=true) continue;
      if(strcmp(a,"A")==0){
	fin >> tower >> scinti_size >> scinti_size_number >> scinti_number 
	    >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] 
	    >> c[5] >> c[6] >> c[7] >> c[8] >> c[9];
	if( (tower==0 || tower==1 ) &&
	    (scinti_size_number>=0 && scinti_size_number<4) &&
	    (scinti_number>=0 && scinti_number<16)){
	  for(int i=0;i<10;i++){
	    if(scinti_size==20){nsize = 0;}
	    if(scinti_size==40){nsize = 1;}
	    if(scinti_size==25){nsize = 2;} 
	    if(scinti_size==32){nsize = 3;} 
	    C[nsize][scinti_number][i] = c[i];
	  }
	}
      }
    }
  }

  fin.close();
  return SCINTIPOSDEPENDENCE_OK;
}

double ScintiPosDependence::GetFunctionFactor(int ssn,int sn,int i){
  if( (ssn>=0 && ssn<4) &&
      (sn>=0 && sn<16) &&
      (i>=0 && i<10) ){
    return C[ssn][sn][i];
  }
  return 0.;
}

double ScintiPosDependence::GetFunctionFactor(int idetector,int itower,int sn,int i){
  if((idetector==1 || idetector==2 ) &&
     (itower==0 || itower==1)){
    return GetFunctionFactor((idetector-1)*2+itower ,sn,i);
  }
  return 0.;
}

int ScintiPosDependence::SetFunctionFactor(int ssn,int sn,int i, double value){
  if( (ssn>=0 && ssn<4) &&
      (sn>=0 && sn<16) &&
      (i>=0 && i<10) ){
    C[ssn][sn][i] = value;
    return SCINTIPOSDEPENDENCE_OK;
  } 
  return SCINTIPOSDEPENDENCE_ERROR;
}

int ScintiPosDependence::SetFunctionFactor(int idetector,int itower,int sn,int i,
					   double value){
  if((idetector==1 || idetector==2 ) &&
     (itower==0 || itower==1)){
    return SetFunctionFactor((idetector-1)*2+itower ,sn,i,value);
  }
  return SCINTIPOSDEPENDENCE_ERROR;
}

double ScintiPosDependence::GetEfficiency(int ssn,int sn,double x, double y){
  double mx=0.,my=0.;
  if( (ssn>=0 && ssn<4) &&
      (sn>=0 && sn<16) ){
    if     (ssn==0){mx = y - 10.; my = x -10.;} //20mm
    else if(ssn==1){mx = y - 20.; my = x -20.;} //40mm
    else if(ssn==2){mx = y - 12.5; my = x -12.5;} //25mm
    else if(ssn==3){mx = y - 16.; my = x - 16.;} //32mm   
    return (C[ssn][sn][0]
	    + C[ssn][sn][1]*mx + C[ssn][sn][2]*mx*mx + C[ssn][sn][3]*mx*mx*mx 
	    + C[ssn][sn][4]*my + C[ssn][sn][5]*my*my + C[ssn][sn][6]*my*my*my 
	    + C[ssn][sn][7]*mx*my + C[ssn][sn][8]*mx*mx*my + C[ssn][sn][9]*mx*my*my)
      / C[ssn][sn][0];
  }
  return 0.;
}

double ScintiPosDependence::GetEfficiency(int idetector,int itower,
					  int sn,double x, double y){
  if((idetector==1 || idetector==2 ) &&
     (itower==0 || itower==1)){
    return GetEfficiency((idetector-1)*2+itower ,sn,x,y);
  }
  return 0.;
}

int  ScintiPosDependence::Calibration(A1Cal2* d,int it,double x,double y){
  for(int i=0;i<16;i++){
    d->cal[it][i] /= GetEfficiency(1,it,i,x,y);
  }
  return SCINTIPOSDEPENDENCE_OK;
}

int  ScintiPosDependence::Calibration(A2Cal2* d,int it,double x,double y){
  for(int i=0;i<16;i++){
    d->cal[it][i] /= GetEfficiency(2,it,i,x,y);
  }
  return SCINTIPOSDEPENDENCE_OK;
}



#endif

/*
 int test(){
   ScintiPosDependence factor("all_data_new.txt");
   cout << "Scinti=40mm,0,C0 " << factor.GetFunctionFactor(0,0,0,0) << endl; 
   cout << "Scinti=40mm,0,C1 " << factor.GetFunctionFactor(0,0,0,1) << endl;
   cout << "Scinti=40mm,0,x=0,y=0 " << factor.GetCorrectionFactor(0,0,0,0,0) << endl;
   cout << "Scinti=40mm,0,x=1,y=0 " << factor.GetCorrectionFactor(0,0,0,1,0) << endl; 
 }
*/
