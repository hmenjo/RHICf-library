#ifndef __SIMINCIDENTS_CPP__
#define __SIMINCIDENTS_CPP__

#include "SimIncidents.h"

//--------------------------------------------------------------------
// This class contains an array of SimP to store informations of all 
// incident particls in one simulation events. 
// 
// To convert the format of the simulation data from ASCII to ROOT 
// with this class, the following programs are available.  
//       general/Simulation/EventBuild/simbuild     for End2End
//                                     darmbuild    for DoubleArm
//                                     gencolbuild  for Gencol
// in these cases, this class with the name of "a1simin" or "a2simin" 
// are stored in LHCfEvent. 
// 
// An example to extract information of incident particles from SimIncidents.
//
//   int    nhit;
//   SinP*  pp;
//   SimIncidents* simin;
//   simin = (SimIncidents*) ev->Get("a2simin");
//   nhit = simin->GetN();   
//   for(int i=0;i<nhit;i++){
//     pp = simin->Get(i);
//     
//     cout << "Particle Code    : " << pp->Code() 
//          << "Particle Charge  : " << pp->Charge() << endl;
//   }     
// 
//  in case you want only the particles hitting a calorimeter,
//  use GetNHit() and GetHit() instead of GetN() and Get();
//  
//   int   nhit;
//   SinP* pp;
//   SimIncidents* simin;
//   simin = (SimIncidents*) ev->Get("a2simin");
//   nhit = simin->GetNHit(2,25,10.,2.0,0.0,0.0);
//     // GetNHit(detector, tower, energy_threshold, detector offsetx,y)   
//   for(int i=0;i<nhit;i++){
//     pp = simin->Get(2,25,i,2.0,0.0,0.0);
//     // must give the same parameters as GetNHit(); 
//   }  
//
//  
// 
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//-------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(SimIncidents);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int SimIncidents::clear(){
  // Clear the array of SimP. It don't delete SimP. 
  run = 0;
  number = 0;
  gnumber = 0;
  
  np = 0;
  particles.Clear();
  
  return OK;
}

int SimIncidents::copy(SimIncidents* d){
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int SimIncidents::copydata(SimIncidents* d){
  // Not implemented yet 
  // It copies only the header data as run, gnumber and etc.
  // Don't use this function.
 
  this->run = d->run;
  this->number = d->number;
  this->gnumber = d->gnumber;
  
  this->np = d->np;
  return OK;
}

void SimIncidents::Add(SimP* d){
  // Add SimP in the array. 
 
  particles.AddAtAndExpand(d,np);
  np++;
}

int SimIncidents::GetNHit(int id, int it,
			  double ke_threshold,double edgecut,
			  double offsetx,double offsety){
  // Return the nubmer of hit particles to the calorimeter.
  //  id      :  detector 1:Old Arm1, 2:Old Arm2, 10:New Arm1, 20: New Arm2
  //  it      :  calorimeter tower (0 (20mm or 25mm) or 1 (40mm or 32mm))
  //             also just the size of cal. 20, 40, 25, 32 are acceptable.
  //  ke_threshold : energy threshold in kinetic energy [GeV]
  //  edgecut :  Distance from edge of your acceptable area. [default: 0]   
  //             in case of 2mm inside, give 2.0 .   
  //  offsetx :  x offset of the detector position [default: 0.0]
  //  offsety :  y offset of the detector position [default: 0.0]
  // 
  // Actually, it just counts resutls of SimP::CheckHit in loop.
  // For detail see SimP::CheckHit
  
  
  int nhit=0;
  SimP* pp;
  for(int ih=0;ih<np;ih++){
    pp = Get(ih);
    if(pp->CheckHit(id,it,edgecut,offsetx,offsety) &&
       pp->KineticEnergy() > ke_threshold){
      if(nhit<10){ref[nhit] = ih;}
      nhit++;
    }
  }
  return nhit;
}

SimP* SimIncidents::GetHit(int id, int it, int ik,
			   double edgecut,
			   double offsetx,double offsety){
  // return SimP with hiting calorimeter and ik'th energy in hit particles.  
  //  id      :  detector 1:Old Arm1, 2:Old Arm2, 10:New Arm1, 20: New Arm2
  //  it      :  calorimeter tower (0 (20mm or 25mm) or 1 (40mm or 32mm))
  //             also just the size of cal. 20, 40, 25, 32 are acceptable. 
  //  ik      :  number in energetic order.
  //  edgecut :  same as GetNHit()
  //  offsetx, offsetx : same as GetNHit()
  // 
  
  int nhit=0;
  SimP* pp;
  for(int ih=0;ih<np;ih++){
    pp = Get(ih);
    if(pp->CheckHit(id,it,edgecut,offsetx,offsety)){
      if(nhit==ik){return pp;}   
      nhit++;
    }
  }
  return (SimP*)0;
}

void SimIncidents::Show(int id,int it,
			double ke_threshold,double edgecut,
			double offsetx,double offsety){
  // Show the list of particles contained in this.
  // This function calls SimP::Show();
  bool check=false;
  cout << " =================== SimIncidents =======================\n";
  cout << " NAME: " << setw(10) << GetName() << "     "
       << " TITLE: " << GetTitle() << endl;
  cout << " RUN: " << setw(6) << run << "    "
       << "GNUMBER: " << setw(7) << gnumber << "  "
       << "NUMBER: " << setw(7) << number << "   " 
       << "NP: " << np << endl;
  cout << " -IP-  -PARTICLE-  USER -KE[GeV]-  -POS_XY[mm] " ;
  if(id==1 && (it==0 || it==20)){cout << "on 20mm-";}
  else if(id==1 && (it==1 || it==40)){cout << "on 40mm-";}
  else if(id==2 && (it==0 || it==25)){cout << "on 25mm-";}
  else if(id==2 && (it==1 || it==32)){cout << "on 32mm-";}
  else if(id==1){cout << "global     20mm           40mm ";check=true;}
  else if(id==2){cout << "global     25mm           32mm ";check=true;}
  else {cout << "global-";}
  cout << endl;
  
  int nhit=0;
  SimP *pp;
  for(int ih=0;ih<np;ih++){
    pp = Get(ih);
    if((id==0 || check || pp->CheckHit(id,it,edgecut,offsetx,offsety)) &&
       pp->KineticEnergy() > ke_threshold){
      cout << setw(4) << nhit << "   " ;
      pp->Show(id,it,offsetx,offsety); 
      nhit++;
    }
  }  
}

double SimIncidents::CalPi0Mass(SimP* p1, SimP* p2){
  // Reconstruction of invariant mass from two partciles.
  // Be careful to use it. some parameters are fixed in this function.
  // 
  double r2;
  double mass;
  r2 = (p1->pos[0]-p2->pos[0])*(p1->pos[0]-p2->pos[0])
    +(p1->pos[1]-p2->pos[1])*(p1->pos[1]-p2->pos[1]);
  mass = sqrt(p1->energy*p2->energy*r2)/139800.*1000.;
  return mass;
}

double SimIncidents::CalPi0Distance(SimP* p1, SimP* p2){
  // Calculate the distance between two hit positions.
  double r2;
  r2 = (p1->pos[0]-p2->pos[0])*(p1->pos[0]-p2->pos[0])
    +(p1->pos[1]-p2->pos[1])*(p1->pos[1]-p2->pos[1]);
  return sqrt(r2);
}

double SimIncidents::CalPi0Energy(SimP* p1, SimP* p2){
  //  return p1->energy + p2->energy;
  return p1->energy + p2->energy;
}

double SimIncidents::CalPi0Momentum(SimP* p1, SimP* p2,
				    int dir,double offsetx,double offsety){
  // Reconstruct the Pi0 momentum from two SimP.
  // Be careful to use this function
  //  dir   :  0 , 1, 2 for x, y, z
  double mon1,mon2,hitpoint;
  if(dir==0){
    hitpoint = p1->pos[0] + offsetx;
    mon1 = p1->energy*(hitpoint/139800.);
    hitpoint = p2->pos[0] + offsetx;
    mon2 = p2->energy*(hitpoint/139800.);
    return mon1 + mon2;
  }
  else if(dir==1){
    hitpoint = p1->pos[1] + offsety;
    mon1 = p1->energy*(hitpoint/139800.);
    hitpoint = p2->pos[1] + offsety;
    mon2 = p2->energy*(hitpoint/139800.);
    return mon1 + mon2;
  }
  else if(dir==2){
    hitpoint = (p1->pos[0] + offsetx)*(p1->pos[0] + offsetx)
      +  (p1->pos[1] + offsety)*(p1->pos[1] + offsety);
    mon1 = p1->energy*sqrt(1-hitpoint/(139800.*139800.)); 
    hitpoint = (p2->pos[0] + offsetx)*(p2->pos[0] + offsetx)
      +  (p2->pos[1] + offsety)*(p2->pos[1] + offsety);
    mon2 = p2->energy*sqrt(1-hitpoint/(139800.*139800.)); 
    return mon1 + mon2;
  }
  return 0.;
}

double SimIncidents::CalPi0Pt(SimP* p1, SimP* p2,
			      double offsetx,double offsety){ 
  // Reconstruct the Pi0 Pt from two SimP.
  // Be careful to use this function
  double px,py;
  px = CalPi0Momentum(p1,p2,0,offsetx,offsety);
  py = CalPi0Momentum(p1,p2,1,offsetx,offsety);
  return sqrt(px*px+py*py);
}

#endif
