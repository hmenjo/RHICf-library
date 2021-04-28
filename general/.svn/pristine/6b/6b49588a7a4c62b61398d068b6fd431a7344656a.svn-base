#ifndef  __ADCRANGE_HH__
#define  __ADCRANGE_HH__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

#define ADCRANGE_FORMAT   "ADCRANGE"

#define ADCRANGE_NADC     4
#define ADCRANGE_NPARAM   2
#define ADCRANGE_OK       0
#define ADCRANGE_ERROR    1


class ADCRange{
public:
  char   tablefile[256];
  char   format[256];
  int    type;
  int    version;

  // 4 adc+16 ch+2 parameters
  double param[ADCRANGE_NADC][16][ADCRANGE_NPARAM]; 
  static const  double threshold = 3700.;

public:
  ADCRange();
  ADCRange(char* file);
  ~ADCRange(){;}
  
  int    Initialize();
  int    ReadFile(char* file);
  int    WriteFile(int t,char* file,char comment[] = "");

  int    SetParameters(int iadc,int ich, double p[]);
  int    SetParameter(int iadc,int ich, int ip, double p);
  double GetParameter(int iadc,int ich, int ip);
  double Get(int iadc,int ich, double adcr, double adch);
};

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
      }
    } 
    fin.close();
    return ADCRANGE_OK;
  }
  else {
    fin.close();
    return ADCRANGE_ERROR;
  }
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
  if(adcr<threshold){
    return adcr;
  }
  else{
    return param[iadc][ich][0] + param[iadc][ich][1]*adch;
  }
}

#endif
