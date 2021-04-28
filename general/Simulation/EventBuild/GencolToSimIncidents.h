#ifndef __GENCOLTOSIMINCIDENTS_H__
#define __GENCOLTOSIMINCIDENTS_H__

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

class GencolToSimIncidents {
 public:
  static const int MAXP = 2000;
  ifstream *fin;
  int      ievent;

  int      np;
  SimP     p[MAXP];
  
  int      npmax;
  double   cut_wz;      // cut of wz
  double   cut_ke;      // [GeV]
  int      inputformat; // 0: for genecol output 
                        // 1: for doublearm +primary
  
 public:
  GencolToSimIncidents(){Initialize();}
  ~GencolToSimIncidents(){;}
  
  void Initialize();
  void SetMaxParticles(int n){npmax = n<MAXP ? n : MAXP;}
  void SetCutWz(double wz){cut_wz=wz;}
  void SetCutKE(double ke){cut_ke=ke;}
  void SetInputFormat(int iformat){inputformat=iformat;}
  int  FileOpen(char *file);
  int  FileClose();
  int  Next(SimIncidents* in);
  int  String2SimP(string s, SimP *p,int iformat=0);
  int  PClear();
};

void GencolToSimIncidents::Initialize(){
  ievent = 0;
  npmax = 20;
  cut_wz = 0.0;
  cut_ke = 100.;
}

int GencolToSimIncidents::FileOpen(char *file){
  fin = new ifstream();

  fin->clear();
  fin->open(file);
  if(!fin->good()){
    cerr << "[GencolToSimIncidents::FileOpen] Error: Cannot open "
         << file << endl;
    return -1;
  }

  string s;
  while(getline(*fin,s)){
    if(s[0]=='#'){break;}
  }
  getline(*fin,s);

  ievent=0;
  return 0;
}

int GencolToSimIncidents::FileClose(){
  fin->close();
  fin->clear();
  return 0;
}

int GencolToSimIncidents::Next(SimIncidents* in){
  string s;
  istringstream sin;
  SimP ptmp;
  bool evend_check = false;
  
  in->clear();
  PClear();
  
  unsigned long pos;
  while(getline(*fin,s)){
    // identify the header lines 
    if(s.length() < 10){evend_check=true;break;}
    if(s.length() < 75){continue;}
    if(np>=npmax) continue;

    pos = s.find("****");
    if(pos!=string::npos){
      s.replace(pos,4,"   0");
    }
    pos = s.find("***");
    if(pos!=string::npos){
      s.replace(pos,3,"  0");
    }
    
    String2SimP(s,&ptmp,inputformat);
    // ***** Cut ****** 
    if(fabs(ptmp.MomZ()/ptmp.Momentum()) < cut_wz){continue;}
    if(ptmp.KineticEnergy() < cut_ke){continue;}
    
    // ***** Fill *****
    if(np>=MAXP){
      cerr << "[GencolToSimIncidents::Next] Over " <<MAXP << endl;
    }
    else{
      if(np<npmax){
	p[np].copydata(&ptmp);
	np++;
      }
    }    
  }

  if(evend_check==true){
    SimP *pp;
    for(int i=0;i<np;i++){
      pp = new SimP();
      pp->copydata(&(p[i]));
      in->Add(pp);
    }
    ievent ++;
    return 0;
  }   

  return -1;
}

int GencolToSimIncidents::String2SimP(string s, SimP *p,int iformat){
  istringstream sin;
  sin.str(s);

  double ke,w[3],pos[3],momentum;
  if(iformat==0){
    sin >> p->code >> p->subcode >> p->charge >> ke 
	>> w[0] >> w[1] >> w[2] >> p->user;
    pos[0] = 0.;
    pos[1] = 0.;
    pos[2] = 0.;
  }  
  else if(iformat==1){
    sin >> p->code >> p->subcode >> p->charge >> ke 
	>> pos[0] >> pos[1] >> pos[2]
	>> w[0] >> w[1] >> w[2] >> p->user;
  }

  p->energy = ke + p->Mass();
  p->pos[0] = pos[0];
  p->pos[1] = pos[1]; 
  p->pos[2] = pos[2];
  momentum = sqrt(p->energy*p->energy - p->Mass()*p->Mass());
  p->mom[0] = momentum*w[0];
  p->mom[1] = momentum*w[1];
  p->mom[2] = momentum*w[2];
  
  return  0;
}

int GencolToSimIncidents::PClear(){
  np = 0;
  for(int i=0;i<MAXP;i++){
    if(p[i].code==0) { break; }
    p[i].clear();
  }
  return 0;
}

#endif
