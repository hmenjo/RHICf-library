#ifndef __FILETOSIMINCIDENTS_H__
#define __FILETOSIMINCIDENTS_H__

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include "TFile.h"
#include "SimP.h"
#include "SimIncidents.h"
#include "LHCfEvent.h"

class FileToSimIncidents{
 public:
  static const int MAXP = 1000;
  ifstream *fin;
  int      detector;
  int      ievent;

  int      np;
  SimP     p[MAXP];
  double   cut_posx;
  double   cut_posy;
  double   cut_ke;
  
 public: 
  FileToSimIncidents(){Initialize();}
  FileToSimIncidents(int d, char *file);  
  ~FileToSimIncidents();  
  
  void Initialize();
  void SetCutPosX(double c){cut_posx=c;}
  void SetCutPosY(double c){cut_posy=c;}
  void SetCutKE(double c){cut_ke=c;}
  void SetDetector(int d){detector = d;}
  int  FileOpen(char *file);
  int  FileClose();
  int  Next(A1Cal2* d,SimIncidents* din, A2Cal2* d2=0);   // for Arm#1
  int  Next(A2Cal2* d,SimIncidents* din, A1Cal2* d2=0);   // for Arm#2
  
  int  Sort();
  int  PClear();
};

const int FileToSimIncidents::MAXP;

FileToSimIncidents::FileToSimIncidents(int d, char *file){
  Initialize();
  SetDetector(d);
  FileOpen(file);
}

void FileToSimIncidents::Initialize(){
  ievent = 0;
  detector = 0;
  cut_posx = 5.0;   // 5.0cm
  cut_posy = 5.0;   // 5.0cm
  cut_ke   = 1.00;   // 1000MeV
  PClear();
}

int FileToSimIncidents::FileOpen(char *file){
  fin = new ifstream();
  
  fin->clear();
  fin->open(file);
  if(!fin->good()){
    cerr << "[FileToSimIncidents::FileOpen] Error: Cannot open " 
	 << file << endl;
    return -1;
  }
  
  ievent=0;
  return 0;
}

int FileToSimIncidents::FileClose(){
  fin->close();
  fin->clear();
  return 0;
}

int FileToSimIncidents::Next(A1Cal2* d ,SimIncidents* din, A2Cal2* d2){
  bool check_start=false;
  bool check_end=false;
  string s;
  istringstream sin;
  SimP tmp;
  char ctmp0[20];
  char ctmp1[20];
  int  tower,layer,channel;
  double value;
  
  d->clear();
  din->clear();
  PClear();
 
  while(getline(*fin,s)){
    //cout << s << endl; 
    if(s.compare(0,5,"start")==0){
      check_start = true;
    }
    if(s.compare(0,3,"end")==0){
      check_end = true;
      break;
    }
    
    if(check_start==false){continue;}
    
    sin.clear();
    sin.str(s);

    if(s.compare(0,4," TRG")==0){
      tmp.clear();
      sin >> ctmp0
	  >> tmp.user >> tmp.code >> tmp.subcode >> tmp.charge
	  >> tmp.pos[0] >> tmp.pos[1] >> tmp.pos[2] 
	  >> tmp.energy 
	  >> tmp.mom[0] >> tmp.mom[1] >> tmp.mom[2];
      //cout << tmp.pos[0] << "  " << endl;
      if(fabs(tmp.pos[0]) > cut_posx){continue;}  
      //cout << tmp.pos[1] << "  " << endl;
      if(fabs(tmp.pos[1]) > cut_posy){continue;}
      //cout << tmp.mom[2]<< "  " << endl;
      if(tmp.mom[2] < 0.){continue;}
      //cout <<tmp.Energy() << endl;
      if(tmp.Energy() < cut_ke){continue;} 
      //cout <<tmp.KineticEnergy() << endl;
      if(tmp.KineticEnergy() < cut_ke){continue;}
      if(np>=MAXP){
	cerr << "[FileToSimIncidents::Next] Over " <<MAXP << endl;
      }
      else{
	//cout << "GET" << endl;
	tmp.pos[0] *= 10.;  // cm->mm
	tmp.pos[1] *= 10.;  // cm->mm
	tmp.pos[2] *= 10.;  // cm->mm	
	p[np].copydata(&tmp);
	np++;
      }
    }  
    else if(s.compare(0,5," scin")==0){ 
      sin >> ctmp0 >> ctmp1 >> tower >> layer >> value;
      if(strcmp(ctmp1,"fd")==0 && tower==1){
	if(layer==1){ d->fc[0][2] = value;}
	else if(layer==2){ d->fc[0][3] = value;}
	else if(layer==3){ d->fc[0][0] = value;}
	else if(layer==4){ d->fc[0][1] = value;}
	if(d2!=0){
	  if(layer==1){ d2->fc[0][2] = value;}
	  else if(layer==2){ d2->fc[0][3] = value;}
	  else if(layer==3){ d2->fc[0][0] = value;}
	  else if(layer==4){ d2->fc[0][1] = value;}
	} 
      }
      else if(strcmp(ctmp1,"t2")==0 && tower==2){
	d->cal[0][layer-1] = value;
      }
      else if(strcmp(ctmp1,"t4")==0 && tower==3){
	d->cal[1][layer-1] = value;
      }
    }
    else if(s.compare(0,7," scifix")==0){ 
      sin >> ctmp0 >> ctmp1 >> tower >> layer >> channel >> value;
      if(strcmp(ctmp1,"t2")==0 && tower==2){
	layer--;
	d->scifi0[layer/2][0][channel-1] = value;
      }
      else if(strcmp(ctmp1,"t4")==0 && tower==3){
	layer--;
	d->scifi1[layer/2][0][channel-1] = value;
      }
    }
    else if(s.compare(0,7," scifiy")==0){
      sin >> ctmp0 >> ctmp1 >> tower >> layer >> channel >> value;
      if(strcmp(ctmp1,"t2")==0 && tower==2){
	layer--;
	d->scifi0[layer/2][1][channel-1] = value;
      }
      else if(strcmp(ctmp1,"t4")==0 && tower==3){
	layer--;
	d->scifi1[layer/2][1][channel-1] = value;
      }
    }
  }

  if(check_start && check_end){ 
    Sort();
    SimP *pp;
    for(int i=0;i<np;i++){
      pp = new SimP();
      pp->copydata(&(p[i]));
      din->Add(pp);
    }
    ievent ++;
    return 0; 
  } 
  return -1;
}

int FileToSimIncidents::Next(A2Cal2* d,SimIncidents* din, A1Cal2* d2){
  bool check_start=false;
  bool check_end=false;
  string s;
  istringstream sin;
  SimP tmp;
  char ctmp0[20];
  char ctmp1[20];
  int  tower,layer,channel;
  double value;
  d->clear();
  din->clear();
  PClear();

  while(getline(*fin,s)){
    if(s.compare(0,5,"start")==0){
      check_start = true;
    }
    if(s.compare(0,3,"end")==0){
      check_end = true;
      break;
    }
    
    if(check_start==false){continue;}
    
    sin.clear();
    sin.str(s);

    if(s.compare(0,4," TRG")==0){
      tmp.clear();
      sin >> ctmp0
	  >> tmp.user >> tmp.code >> tmp.subcode >> tmp.charge
	  >> tmp.pos[0] >> tmp.pos[1] >> tmp.pos[2] 
	  >> tmp.energy 
	  >> tmp.mom[0] >> tmp.mom[1] >> tmp.mom[2];
      //cout << tmp.pos[0] << "  " << endl;
      if(fabs(tmp.pos[0]) > cut_posx){continue;}  
      //cout << tmp.pos[1] << "  " << endl;
      if(fabs(tmp.pos[1]) > cut_posy){continue;}
      //cout << tmp.mom[2]<< "  " << endl;
      if(tmp.mom[2] < 0.){continue;}
      //cout <<tmp.Energy() << endl;
      if(tmp.Energy() < cut_ke){continue;} 
      //cout <<tmp.KineticEnergy() << endl;
      if(tmp.KineticEnergy() < cut_ke){continue;}
      if(np>=MAXP){
	cerr << "[FileToSimIncidents::Next] Over " <<MAXP << endl;
      }
      else{
	//cout << "GET" << endl;
	tmp.pos[0] *= 10.;  // cm->mm
	tmp.pos[1] *= 10.;  // cm->mm
	tmp.pos[2] *= 10.;  // cm->mm	
	p[np].copydata(&tmp);
	np++;
      }
    }  
    else if(s.compare(0,5," scin")==0){ 
      sin >> ctmp0 >> ctmp1 >> tower >> layer >> value;
      if(strcmp(ctmp1,"fd")==0 && tower==1){
	if(layer==1){ d->fc[1][3] = value;}
	else if(layer==2){ d->fc[1][2] = value;}
	else if(layer==3){ d->fc[1][1] = value;}
	else if(layer==4){ d->fc[1][0] = value;}
	if(d2!=0){
	  if(layer==1){ d2->fc[1][2] = value;}
	  else if(layer==2){ d2->fc[1][3] = value;}
	  else if(layer==3){ d2->fc[1][0] = value;}
	  else if(layer==4){ d2->fc[1][1] = value;}
	} 
      }
      else if(strcmp(ctmp1,"t25")==0 && tower==2){
	d->cal[0][layer-1] = value;
      }
      else if(strcmp(ctmp1,"t32")==0 && tower==3){
	d->cal[1][layer-1] = value;
      }
    }
    else if(s.compare(0,3," si")==0){ 
      sin >> ctmp0  >> layer >> channel >> value;
      layer--;
      d->silicon[layer/2][layer%2][channel-1][0] = value;
    }
  }

  if(check_start && check_end){ 
    Sort();
    SimP *pp;
    for(int i=0;i<np;i++){
      pp = new SimP();
      pp->copydata(&(p[i]));
      din->Add(pp);
    }
    ievent ++;
    return 0; 
  } 
  return -1;
}


int FileToSimIncidents::PClear(){
  np = 0;
  for(int i=0;i<MAXP;i++){
    if(p[i].code==0) { break; }
    p[i].clear();
  }
  return 0;
}

int FileToSimIncidents::Sort(){
  if(np<=1) {return 0;}
  int i,j;
  SimP tmp;
  for(j=1;j<np;j++){
    tmp.copydata(&p[j]);
    i=j-1;
    while(i>=0 && p[i].KineticEnergy() < tmp.KineticEnergy()){
      p[i+1].copydata(&p[i]);
      i--;
    } 
    p[i+1].copydata(&tmp);
  }
  
  return 0;
}

#endif
