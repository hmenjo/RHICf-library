#ifndef __CONPEDESTALADC__
#define __CONPEDESTALADC__

#define CONPEDESTALADC_OK      0
#define CONPEDESTALADC_ERROR  -1

#include <fstream>
using namespace std;

class ConPedestalADC{
//protected:
public:
  char       file[256];
  char       format[256];
  int        type;
  int        version;
  int        run;
  int        nevent;
  
  double     peADC[3][32];
  double     perms[3][32];

public:
  ConPedestalADC();
  ConPedestalADC(char* file);
 
  int        Initialize();
  int        ReadFile(char* file);
  int        WriteFile(int t, char* file, char comment[256]=" "); 
  int        WriteFile(char* file, char comment[256]=" "); 
  double     GetPedestal(int t,int ch);
  int        SetPedestal(int t,int ch, double tmp);
  double     GetPedestalRMS(int t,int ch);
  int        SetPedestalRMS(int t,int ch, double tmp);
  void       SetRunNumber(int r){run = r;}
  void       SetNEvents(int n){nevent = n;}
};

ConPedestalADC::ConPedestalADC(){
  Initialize();
}

ConPedestalADC::ConPedestalADC(char* file){
  Initialize();
  ReadFile(file);
}

int ConPedestalADC::Initialize(){
  strcpy(file,"");
  strcpy(format,"");
  type   = 0;
  version = 0;
  run    = 0;
  nevent = 0;
  for(int it=0;it<3;it++){
    for(int ich=0;ich<32;ich++){
      peADC[it][ich] = 0.;
    }
  }
  return CONPEDESTALADC_OK;
}
  
int ConPedestalADC::ReadFile(char *file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ConPedestalADC::ReadFile] Cannot Open " 
	 << file << endl;
    return CONPEDESTALADC_ERROR;
  }
  
  char a[256];
  int     tower,channel;
  double  pede,rms;
  bool check_param=false;
  bool check_data=false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_END")==0){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    
    if(check_param==true){
      if(strcmp(a,"FORMAT:")==0){
	fin >> format;
	if(strcmp(format,"ADC_PEDESTAL_TABLE")!=0){
	  cerr << "[ConPedestalADC::ReadFile] this is not ADC_PEDESTAL_TABLE."
	       << endl;
	  return CONPEDESTALADC_ERROR;
	}
      }
      if(strcmp(a,"TYPE:")==0){fin >> type;}
      if(strcmp(a,"VERSION:")==0){fin >> version;}
      if(strcmp(a,"RUN:")==0){fin >> run;}
      if(strcmp(a,"NEVENT:")==0){fin >> nevent;}
    }
  }

  if(type==1){
    while(1){
      fin >> a;
      if(fin.eof()){break;}
      if(strcmp(a,"DATA_END")==0){break;}
      if(strcmp(a,"DATA_START")==0){check_data=true;}
      
      if(check_data==true){
	if(strcmp(a,"ADC")==0){
	  fin >> tower >> channel >> pede;
	  if( (tower==0 || tower==1 || tower==2) &&
	      (channel>=0 && channel <32)){
// 	    cout << tower << " " << channel << " " << pede<< endl;
	    peADC[tower][channel] = pede;
	  }
	}
      }
    }
  }
  
  if(type==2){
    while(1){
      fin >> a;
      if(fin.eof()){break;}
      if(strcmp(a,"DATA_END")==0){break;}
      if(strcmp(a,"DATA_START")==0){check_data=true;}
      
      if(check_data==true){
	if(strcmp(a,"ADC")==0){
	  fin >> tower >> channel >> pede >> rms;
	  if( (tower==0 || tower==1 || tower==2) &&
	      (channel>=0 && channel <32)){
// 	    cout << tower << " " << channel << " " << pede<< endl;
	    peADC[tower][channel] = pede;
	    perms[tower][channel] = rms;
	  }
	}
      }
    }
  }

  fin.close();
  return CONPEDESTALADC_OK;
}

int ConPedestalADC::WriteFile(int t, char* file, char comment[256]){
  type = t;
  if(type!=1 && type!=2){
    cerr << "[ConPedestalADC::WriteFile] TYPE is incorrect." << endl; 
    return CONPEDESTALADC_ERROR;
  }

  ofstream fout(file);
  fout << "PARAM_START" << endl
       << "FORMAT:  ADC_PEDESTAL_TABLE" << endl
       << "TYPE:     "  << type << endl
       << "VERSION:  1" << endl
       << "RUN:   " << run<< endl
       << "NEVENT: " << nevent << endl
       << "COMMENT: ADC #Module  #ch #data" << endl
       << "       : " <<  comment << endl   
       << "PARAM_END" << endl;
 
  if(type==1){
    fout << "DATA_START" << endl;
    fout.setf(ios::fixed);
    for(int it=0;it<3;it++){
      for(int ich=0;ich<32;ich++){
	fout << "ADC  " << setw(1) << it << " " << setw(2) << ich 
	     << setw(10) << setprecision(3) <<  peADC[it][ich] << endl;
      }
    }
    fout << "DATA_END" << endl;
  }
  if(type==2){
    fout << "DATA_START" << endl;
    fout.setf(ios::fixed);
    for(int it=0;it<3;it++){
      for(int ich=0;ich<32;ich++){
	fout << "ADC  " << setw(1) << it << " " << setw(2) << ich 
	     << setw(10) << setprecision(3) <<  peADC[it][ich] << " "
	     << setw(10) << setprecision(3) <<  perms[it][ich] << endl;
      }
    }
    fout << "DATA_END" << endl; 
  }
  fout.close();
  return CONPEDESTALADC_OK;
}

int ConPedestalADC::WriteFile(char* file, char comment[256]){
  ofstream fout(file);
  fout << "PARAM_START" << endl
       << "FORMAT:  ADC_PEDESTAL_TABLE" << endl
       << "TYPE:     1" << endl
       << "VERSION:  1" << endl
       << "RUN:   " << run<< endl
       << "NEVENT: " << nevent << endl
       << "COMMENT: ADC #Module  #ch #data" << endl
       << "       : " <<  comment << endl   
       << "PARAM_END" << endl;
 
  fout << "DATA_START" << endl;
  fout.setf(ios::fixed);
  for(int it=0;it<3;it++){
    for(int ich=0;ich<32;ich++){
      fout << "ADC  " << setw(1) << it << " " << setw(2) << ich 
	   << setw(10) << setprecision(3) <<  peADC[it][ich] << endl;
    }
  }
  fout << "DATA_END" << endl;
  fout.close();
  return CONPEDESTALADC_OK;

}

double ConPedestalADC::GetPedestal(int t,int ch){
  if( (t==0 || t==1 || t==2) &&
      (ch>=0 && ch <32)){
    return peADC[t][ch];
  }
  return 0.;
}

int ConPedestalADC::SetPedestal(int t,int ch, double tmp){
  if( (t==0 || t==1 || t==2) &&
      (ch>=0 && ch <32)){
    peADC[t][ch] = tmp;  
    return 0;
  }
  return -1;
}

double ConPedestalADC::GetPedestalRMS(int t,int ch){
  if( (t==0 || t==1 || t==2) &&
      (ch>=0 && ch <32)){
    return perms[t][ch];
  }
  return 0.;
}

int ConPedestalADC::SetPedestalRMS(int t,int ch, double tmp){
  if( (t==0 || t==1 || t==2) &&
      (ch>=0 && ch <32)){
    perms[t][ch] = tmp;  
    return 0;
  }
  return -1;
}

#endif


// int test(){
//   ConPedestalADC pede("pede_adc_run00790.dat");
//   cout << "1_0 " << pede.GetPedestal(1,0) << endl; 
//   cout << "1_0 " << pede.GetPedestal(1,1) << endl; 

// }

