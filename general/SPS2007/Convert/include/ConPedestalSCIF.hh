#ifndef __CONPEDESTALSCIF__
#define __CONPEDESTALSCIF__

#include <iostream>
#include <iomanip>
#include <fstream>

#define CONPEDESTALSCIF_OK      0
#define CONPEDESTALSCIF_ERROR  -1

class ConPedestalSCIF{
public:
  char       file[256];
  char       format[256];
  int        type;
  int        version;
  int        run;
  int        nevent;
  
  double     peSCIF[512];
  double     peSCIFrms[512];

public:
  ConPedestalSCIF();
  ConPedestalSCIF(char* file);
 
  int        Initialize();
  int        ReadFile(char* file);
  int        WriteFile(int type,char* file,char comment[]="");
  double     GetPedestal(int ch){return peSCIF[ch];}
  int        SetPedestal(int ch, double tmp){peSCIF[ch]=tmp;return CONPEDESTALSCIF_OK;}
  double     GetPedestalRMS(int ch){return peSCIFrms[ch];}
  int        SetPedestalRMS(int ch, double tmp){peSCIFrms[ch]=tmp;return CONPEDESTALSCIF_OK;}
  void       SetRunNumber(int r){run = r;}
  void       SetNEvents(int n){nevent = n;}
};

ConPedestalSCIF::ConPedestalSCIF(){
  Initialize();
}

ConPedestalSCIF::ConPedestalSCIF(char* file){
  Initialize();
  ReadFile(file);
}

int ConPedestalSCIF::Initialize(){
  strcpy(file,"");
  strcpy(format,"");
  type   = 0;
  version = 0;
  run    = 0;
  nevent = 0;
  for(int ich=0;ich<512;ich++){
    peSCIF[ich] = 0.;
  }
  return CONPEDESTALSCIF_OK;
}
  
int ConPedestalSCIF::ReadFile(char *file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ConPedestalSCIF::ReadFile] Cannot Open " 
	 << file << endl;
    return CONPEDESTALSCIF_ERROR;
  }
  
  char a[256];
  int     channel;
  double  pede,pederms;
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
	if(strcmp(format,"SCIF_PEDESTAL_TABLE")!=0){
	  cerr << "[ConPedestalSCIF::ReadFile] this is not SCIF_PEDESTAL_TABLE."
	       << endl;
	  return CONPEDESTALSCIF_ERROR;
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
	if(strcmp(a,"SCIF")==0){
	  fin >> channel >> pede ;
	  if(channel>=0 && channel <512){
// 	    cout << tower << " " << channel << " " << pede<< endl;
	    peSCIF[channel] = pede;
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
	if(strcmp(a,"SCIF")==0){
	  fin >> channel >> pede >> pederms;
	  if(channel>=0 && channel <512){
	    peSCIF[channel] = pede;
	    peSCIFrms[channel] = pederms;
	  }
	}
      }
    }
  }

  fin.close();
  return CONPEDESTALSCIF_OK;
}

int ConPedestalSCIF::WriteFile(int t,char* file,char comment[]){
  ofstream fout;
  if(t==1 || t==2){
    type = t;
    fout.open(file);
    fout << "PARAM_START" << endl;
    fout << "FORMAT:  SCIF_PEDESTAL_TABLE" << endl
	 << "TYPE:     " << type << endl
	 << "VERSION:  " << version <<  endl
	 << "RUN:   " << run << endl
	 << "NEVENT: " << nevent << endl
	 << "COMMENT: SCIF   #ch #data " 
	 << "       : " << comment << endl;
    fout << "PARAM_END" << endl;
    fout << endl;
  }

  // ---------------------------------------------
  if(t==1){
    fout << "DATA_START" << endl;
    fout.setf(ios::fixed);
    for(int i=0;i<512;i++){
      fout << "SCIF  " << setw(3) << i << " "
	   << setw(9) << setprecision(2) 
	   << peSCIF[i] << endl;
    }
    fout << "DATA_END" << endl;
    fout.close();
    return CONPEDESTALSCIF_OK;
  }
  if(t==2){
    fout << "DATA_START" << endl;
    fout.setf(ios::fixed);
    for(int i=0;i<512;i++){
      fout << "SCIF  " << setw(3) << i << " "
	   << setw(9) << setprecision(2) << peSCIF[i] << " " 
	   << setw(6) << setprecision(2) << peSCIFrms[i] 
	   << endl;
    }
    fout << "DATA_END" << endl;
    fout.close();
    return CONPEDESTALSCIF_OK;
  }
  
  return CONPEDESTALSCIF_ERROR;
}

// double ConPedestalSCIF::GetPedestal(int ch){
//   if( (ch>=0 && ch <512)){
//     return peSCIF[ch];
//   }
//   return 0.;
// }

#endif


// int test(){
//   ConPedestalSCIF pede("pede_scifi_run00790.dat");
//   cout << "0 " << pede.GetPedestal(0) << endl; 
//   cout << "511 " << pede.GetPedestal(511) << endl; 

// }
