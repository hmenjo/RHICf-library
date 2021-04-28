#ifndef __DARMTOSIMINCIDENTS_H__
#define __DARMTOSIMINCIDENTS_H__

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

class DarmToSimIncidents {
 public:
  static const int MAXP = 100;
  ifstream *fin;
  int      ievent;

  int      np_a1;
  int      np_a2;
  SimP     p_a1[MAXP];
  SimP     p_a2[MAXP];
  string   s_a1[MAXP];
  string   s_a2[MAXP];
  double   cut_posx;
  double   cut_posy;
  double   cut_ke;
  bool     beampipecut;
  bool     tanwallcut;
  double   offset_a1x; 
  double   offset_a1y;
  double   offset_a2x;
  double   offset_a2y;
  
 public:
  DarmToSimIncidents(){Initialize();}
  ~DarmToSimIncidents(){;}
  
  void Initialize();
  void SetCutPosX(double c){cut_posx=c;}
  void SetCutPosY(double c){cut_posy=c;}
  void SetCutKE(double c){cut_ke=c;}
  void SetOffset_A1x(double c){offset_a1x = c;}
  void SetOffset_A1y(double c){offset_a1y = c;}
  void SetOffset_A2x(double c){offset_a2x = c;}
  void SetOffset_A2y(double c){offset_a2y = c;}
  void SetCutBeampipe(bool b=true){beampipecut=b;}
  void SetCutTANWall(bool b=true){tanwallcut=b;}
  int  FileOpen(char *file);
  int  FileClose();
  int  Next(SimIncidents* in1, SimIncidents* in2);
  int  String2SimP(string s, SimP *p);
  int  Cut_beampipe(double x,double y);
  int  Cut_tanwall(double x,double y);
  int  Sort();
  int  PClear();
};

void DarmToSimIncidents::Initialize(){
  ievent = 0;
  cut_posx = 50.;    // 50.mm
  cut_posy = 50.;    // 50.mm
  cut_ke   = 1.00;   // 1 GeV
  beampipecut = true;
  tanwallcut = true;
  offset_a1x = -1.6; // mm
  offset_a1y =  0.0; // mm
  offset_a2x = -0.6; // mm
  offset_a2y =  0.0; // mm
  PClear();
}

int DarmToSimIncidents::FileOpen(char *file){
  fin = new ifstream();
  
  fin->clear();
  fin->open(file);
  if(!fin->good()){
    cerr << "[DarmToSimIncidents::FileOpen] Error: Cannot open " 
	 << file << endl;
    return -1;
  }
  ievent=0;
  return 0;
}

int DarmToSimIncidents::FileClose(){
  fin->close();
  fin->clear();
  return 0;
}

int DarmToSimIncidents::Next(SimIncidents* din1, SimIncidents* din2){
  string s;
  istringstream sin;
  int  detector=0;
  SimP ptmp;
  bool evend_check = false;
  double posx=0.,posy=0.;  // position on the DoubleArm system.

  din1->clear();
  din2->clear();
  PClear();

  while(getline(*fin,s)){
    // identify the header lines
    if(s.length() > 5 && s.length() < 40){
      continue;
    }
    // identify a line feed 
    if(s.length() < 5){
      evend_check = true; 
      break;
    }
    
    detector=String2SimP(s,&ptmp);
    
    // ***** Cut ******
    if(detector==1){
      posx = ptmp.pos[0]-offset_a1x;
      posy = ptmp.pos[1]-offset_a1y;
    }
    else if(detector==2){
      posx = ptmp.pos[0]-offset_a2x;
      posy = ptmp.pos[1]-offset_a2y;
    }
    
    if(tanwallcut && Cut_tanwall(ptmp.pos[0],ptmp.pos[1])==0){continue;}
    if(beampipecut && Cut_beampipe(posx,posy)==0) {continue;}
    if(fabs(ptmp.pos[0]) > cut_posx){continue;}
    if(fabs(ptmp.pos[1]) > cut_posy){continue;}
    if(ptmp.KineticEnergy() < cut_ke){continue;}
    
    // ***** Fill *****
    if(detector==1){
      if(np_a1>=MAXP){
	cerr << "[DarmToSimIncidents::Next] Over " <<MAXP << endl;
      }
      else{
	p_a1[np_a1].copydata(&ptmp);
	s_a1[np_a1] = s;
	np_a1++;
      }
    }
    else if(detector==2){
      if(np_a2>=MAXP){
	cerr << "[DarmToSimIncidents::Next] Over " <<MAXP << endl;
      }
      else{
	p_a2[np_a2].copydata(&ptmp);
	s_a2[np_a2] = s;
	np_a2++;
      }
    }
  }

  if(evend_check==true){
    Sort();
    SimP *pp;
    for(int i=0;i<np_a1;i++){
      pp = new SimP();
      pp->copydata(&(p_a1[i]));
      din1->Add(pp);
    }
    for(int i=0;i<np_a2;i++){
      pp = new SimP();
      pp->copydata(&(p_a2[i]));
      din2->Add(pp);
    }
    
    ievent ++;
    return 0; 
  }
  
  return -1;
}

int DarmToSimIncidents::String2SimP(string s, SimP *p){
  int detector=0;
  istringstream sin;
  sin.str(s);
  int    tmpevent;
  double ke,r,t,pos[3],w[3],momentum;
  
  sin >> tmpevent >> p->user >> p->code >> p->subcode >> p->charge 
      >> ke >> r >> pos[0] >> pos[1] >> pos[2] >> t 
      >> w[0] >> w[1] >> w[2];
  
  p->energy = ke + p->Mass();
  pos[0] *= 10.; // cm->mm
  pos[1] *= 10.; // cm->mm
  pos[2] *= 10.; // cm->mm

  // For Arm1
  if(pos[2]>0){ 
    detector=1;
    pos[0] += offset_a1x;
    pos[1] += offset_a1y;
    pos[2] = 0.;
    momentum = sqrt(p->energy*p->energy - p->Mass()*p->Mass());
    w[0] *= momentum;
    w[1] *= momentum;
    w[2] *= momentum;
  }
  // For Arm2
  if(pos[2]<0){ 
    detector=2;
    pos[0] = -1.*pos[0];
    w[0]   = -1.*w[0];
    pos[2] = -1.*pos[2];
    w[2]   = -1.*w[2];

    pos[0] += offset_a2x;
    pos[1] += offset_a2y;
    pos[2] = 0.;
    momentum = sqrt(p->energy*p->energy - p->Mass()*p->Mass());
    w[0] *= momentum;
    w[1] *= momentum;
    w[2] *= momentum;
  }
  
  p->pos[0] = pos[0];   
  p->pos[1] = pos[1];  
  p->pos[2] = pos[2];   
  p->mom[0] = w[0];
  p->mom[1] = w[1];
  p->mom[2] = w[2];
  
  return detector;
}

int DarmToSimIncidents::Cut_beampipe(double x,double y){
  double r2;
  r2 = (x/106.2)*(x/106.2) + (y/43.97)*(y/43.97);
  if(r2>1.0) return 0;
  else       return 1;
}

int DarmToSimIncidents::Cut_tanwall(double x,double y){
  if(fabs(x)>46.) return 0;
  return 1;
}

int DarmToSimIncidents::PClear(){
  np_a1 = 0;
  for(int i=0;i<MAXP;i++){
    if(p_a1[i].code==0) { break; }
    p_a1[i].clear();
  }

  np_a2 = 0;
  for(int i=0;i<MAXP;i++){
    if(p_a2[i].code==0) { break; }
    p_a2[i].clear();
  }
  return 0;
}

int DarmToSimIncidents::Sort(){
  int i,j;
  SimP tmp;
  
  // Arm1
  if(np_a1>0){
    for(j=1;j<np_a1;j++){
      tmp.copydata(&p_a1[j]);
      i=j-1;
      while(i>=0 && p_a1[i].KineticEnergy() < tmp.KineticEnergy()){
	p_a1[i+1].copydata(&p_a1[i]);
	i--;
      } 
      p_a1[i+1].copydata(&tmp);
    }
  }
  
  // Arm2
  if(np_a2>1){
    for(j=1;j<np_a2;j++){
      tmp.copydata(&p_a2[j]);
      i=j-1;
      while(i>=0 && p_a2[i].KineticEnergy() < tmp.KineticEnergy()){
	p_a2[i+1].copydata(&p_a2[i]);
	i--;
      } 
      p_a2[i+1].copydata(&tmp);
    }
  }
  
  return 0;
}
#endif
