#ifndef __CONPEDESTALFSIL__
#define __CONPEDESTALFSIL__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "CalFSIL1.hh"
using namespace std;

#define CONPEDESTALFSIL_OK      0
#define CONPEDESTALFSIL_ERROR  -1
#define CONPEDESTALFSIL_FORMAT  "CONPEDESTALFSIL" 

class ConPedestalFSIL{
protected:
  char       tablefile[256];
  char       format[256];
  int        type;
  int        version;
  int        run;
  int        nevent;
  
  CalFSIL1   *cfsil1;

public:  
  ConPedestalFSIL();
  ConPedestalFSIL(char* file);

  int        Initialize();
  int        ReadFile(char* file);  
  int        WriteFile(int t,char* file,char comment[] = "");
  double     GetPedestal(int il,int ixy,int ch);
  CalFSIL1*  GetPedestal(){return cfsil1;}
  int        SetPedestal(CalFSIL1* c); 
};

ConPedestalFSIL::ConPedestalFSIL(){
  Initialize();
}

ConPedestalFSIL::ConPedestalFSIL(char* file){
  Initialize();
  ReadFile(file);
}

int ConPedestalFSIL::Initialize(){
  strcpy(tablefile,"");
  strcpy(format,"");
  type   = 0;
  version = 0;
  run    = 0;
  nevent = 0;
  cfsil1 = new CalFSIL1();
  return CONPEDESTALFSIL_OK;
}

int ConPedestalFSIL::ReadFile(char *file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ConPedestalFSIL::ReadFile] Cannot Open "
         << file << endl;
    return CONPEDESTALFSIL_ERROR;
  }
  strcpy(tablefile,file);

  char a[256];
  int     il,ixy,ich;
  double  pede;
  bool check_param=false;
  bool check_data=false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_END")==0){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    if(check_param==true){
      if(strcmp(a,"FORMAT:")==0){ fin >> format;}
      if(strcmp(a,"TYPE:")==0){fin >> type;}
      if(strcmp(a,"VERSION:")==0){fin >> version;}
      if(strcmp(a,"RUN:")==0){fin >> run;}
      if(strcmp(a,"NEVENT:")==0){fin >> nevent;}
    }
  }
  
  if(strcmp(format,CONPEDESTALFSIL_FORMAT)!=0){ 
    cerr << "[ConPedestalFSIL::ReadFile] this is not " 
	 << CONPEDESTALFSIL_FORMAT
	 << endl;
    return CONPEDESTALFSIL_ERROR;
  }
  
  if(strcmp(format,CONPEDESTALFSIL_FORMAT)!=0){ }
  
  if(type==1){
    while(1){
      fin >> a;
      if(fin.eof()){break;}
      if(strcmp(a,"DATA_END")==0){break;}
      if(strcmp(a,"DATA_START")==0){check_data=true;}

      if(check_data==true){
        if(strcmp(a,"FSIL")==0){
          fin >> il >> ixy >> ich >> pede;
          if( (il>=0 && il<5 ) &&
	      (ixy ==1 || ixy==0) &&
              (ich>=0 && ich <1024)){
	    //          cout << tower << " " << channel << " " << pede<< endl;
            cfsil1->cFSIL[il][ixy][ich] = pede;
          }
        }
      }
    }
  }
  fin.close();
  return CONPEDESTALFSIL_OK;
}

int ConPedestalFSIL::WriteFile(int t,char* file,char comment[]){
  strcpy(tablefile,file);
  ofstream fout(file);
  
  if(t!=1){
    cerr << "[ConPedestalFSIL::WriteFile] "
         << t << " is wrong type" << endl;
    return CONPEDESTALFSIL_ERROR;
  }
  strcpy(format,CONPEDESTALFSIL_FORMAT);
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
    for(int il=0;il<5;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ich=0;ich<1024;ich++){
	  fout << "FSIL   "
	       << setw(1) << il << " "
	       << setw(1) << ixy << " "
	       << setw(4) << ich << " "
	       << setw(10) << setprecision(2) << cfsil1->cFSIL[il][ixy][ich]
	       << endl;
	}
      }
    }
    fout << "DATA_END" <<endl; 
    fout.close();
    return CONPEDESTALFSIL_OK; 
  } 
  return CONPEDESTALFSIL_ERROR;
}

double ConPedestalFSIL::GetPedestal(int il,int ixy,int ich){
  if( (il>=0 && il<5 ) &&
      (ixy ==1 || ixy==0) &&
      (ich>=0 && ich <1024)){
    return cfsil1->cFSIL[il][ixy][ich];
  }
  return 0.;
}

int  ConPedestalFSIL::SetPedestal(CalFSIL1* c){
  cfsil1 = c;
  return CONPEDESTALFSIL_OK; 
}
#endif
