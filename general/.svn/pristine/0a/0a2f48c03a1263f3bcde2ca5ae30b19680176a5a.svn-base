#ifndef __A2PHYS_CPP__
#define __A2PHYS_CPP__

#include "A2Phys.h"

//----------------------------------------------------------------------
// A2Phys
// 
// Data structure for physics values measured by Arm2.
// Only physics values like energy, hit position, etc. are stored in this class.
//
// DATA FORMAT: (Last update at 07 Oct. 2009 by H.MENJO )
//  - int    run        (Run Number)
//  - int    number     (Arm#2 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//
//  - double energy[2]  [tower]
//     Energy of incident particle.
//      [unit] GeV
//      tower: 0=25mm,1=32mm
//
//  - double pos[2][2]  [tower][xy]
//     Hit position[mm] on the calorimteter system.
//      [unit] mm
//      tower: 0=25mm,1=32mm
//      xy: 0="X",1="Y"
//
//  - int pid[2]  [tower]
//     Particle type of incident particle.
//     0=Electromagnetic, 1=Hadronic, -10=Unknown
//      tower: 0=25mm,1=32mm
//
//  - int hits[2] [tower]
//     Number of detected particles in each calorimeter
//      tower: 0=25mm,1=32mm
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  HOW TO GET THE HIT POSITION IN SEVERAL COORDINATE (3 Dec. 2015 by Menjo)
//   The hit position of the particle can be provided in several coodrinate. 
//    (1) Global Detector  : The origin is located on the center of detctor 
//    (2) Global Beam Pipe : The origin is located on the center of beam pipe 
//                           = the coordinate system of End2End output
//    (3) Global Beam Center : The origin is located on the beam center. 
//    These three coodinate can be converted by a simple shift with the corresponding 
//    parameters while the conversion to/from calorimeter coordinate needs a rotation 
//    also in case of Arm1. 
//    The incident position can be got by the functions 
//    (1) -> GlobalPos_Detector(tower,xy, offsetx, offsety) 
//    (2) -> GlobalPos_BeamPipe(tower, xy)
//    (3) -> GlobalPos_BC(tower, xy,offsetx, offsety)
//    These offsetx,offsety which are shift paramters must be specified. 
//    The offsets are automatticaly calculated if the beam center and the beam pipe 
//    position on the global detector coordinate system are given via a static 
//    function,  SetPositionBeamCenter(x,y) and  SetPositionBeamPipeCenter(x,y).
//    An example 
//         A1Phys::SetPositionBeamCenter(1.0,1.0);
//         A1Phys::SetPositionBeamPipeCenter(0.0,20.0);  
//         then 
//         cout << phys->GlobalPosX_BC() << endl; 
//    About the detail, see SimP also. 
//
// +++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ?? ???. 08: First edited by H.MENJO
//   27 Aug. 08: 2 Constant ELEMAG and HADRON were added by H.MENJO
//   10 Sep. 08: Change deta type: long -> int
//   10 Jan. 10: Added the function of Show() by H.MENJO
//    4 Jan  12: Change the arguments of Momentum()
//               (it, dir, offsetx, offsety) => (it, dir, beamcenter_x, beamcenter_y)
//               It affects GetPi0Momentum(), GetPi0Pt() and etc.
//    2 Dec. 15: Added the functions for coordinate conversion by H.MENJO
//    2 Dec. 15: Added the functions for coordinate conversion by H.MENJO
// ------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Phys);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

const int A2Phys::ALLPARTICLE;
const int A2Phys::ELEMAG;
const int A2Phys::HADRON;
const double A2Phys::cDistance = 141050.;
const double A2Phys::cPi0mass  = 0.1349766;

double A2Phys::sPositionBeamCenter[2] = {0.};
double A2Phys::sPositionBeamPipe[2]   = {0.};

// ***********************************************************
// ***  A2Phys::clear()  *************************************
// ***********************************************************
int A2Phys::clear(){
  // Clear data 
  
  run     = 0;
  number  = 0;
  gnumber = 0;
  time[0] = 0;
  time[1] = 0;
  
  for(int it=0;it<2;it++){
    energy[it] = 0.;
    pos[it][0] = 0.;
    pos[it][1] = 0.;
    pid[it]    = -1;
    hits[it]   = 0;
    
    //_________________________________________________________
    for(int il=0;il<4;il++)
      for(int ixy=0;ixy<2;ixy++)
        for(int isample=0;isample<3;isample++)
  	  sideposit[it][il][ixy][isample] = 0.;	
    for(int isample=0;isample<3;isample++)  
      sidepositsum[it][isample] = 0.;		  
  }
  
  for(int i=0;i<3;i++){
    flag[i] = 0;
  }

  return OK;
}

// ***********************************************************
// ***  A2Phys::copy     *************************************
// ***********************************************************
int A2Phys::copy(A2Phys* d){
  // Copy data, name and title of "d" to "this"
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

// ***********************************************************
// ***  A2Phys::copydata     *********************************
// ***********************************************************
int A2Phys::copydata(A2Phys* d){
  // Copy only data of "d" to "this"
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber;
  this->time[0] = d->time[0];
  this->time[1] = d->time[1];

  for(int it=0;it<2;it++){
    this->energy[it] = d->energy[it];
    this->pos[it][0] = d->pos[it][0];
    this->pos[it][1] = d->pos[it][1];
    this->pid[it]    = d->pid[it];
    this->hits[it]   = d->hits[it];
    
    //_________________________________________________________
    for(int il=0;il<4;il++)
      for(int ixy=0;ixy<2;ixy++)
        for(int isample=0;isample<3;isample++)
  	  this->sideposit[it][il][ixy][isample] = d->sideposit[it][il][ixy][isample];	
    for(int isample=0;isample<3;isample++)  
      this->sidepositsum[it][isample] = d->sidepositsum[it][isample];	    
  }

  for(int i=0;i<3;i++){
    this->flag[i] = d->flag[i];
  }
  
  return OK;
}


// *****************************************************************
// *****                 FOR  ANALYSIS                           ***
// *****************************************************************
bool A2Phys::InFiducial(int it,double edgecut){
  // if hit position is in fiducial area, return true. 
  // 1st argment is ID of tower(0:25mm,1:32mm),
  // 2nd is the distance from the eduge as cut criteria. default is 2.0mm
  
  if(it==0){
    if( fabs(pos[0][0]-12.5)<(12.5-edgecut) && 
	fabs(pos[0][1]-12.5)<(12.5-edgecut)){ 
      return true;
    }
    else{
      return false;
    }
  }
  else if(it==1){
    if( fabs(pos[1][0]-16.)<(16.-edgecut) && 
	fabs(pos[1][1]-16.)<(16.-edgecut)){ 
      return true;
    }
    else{
      return false;
    }
  }
  return false;
}

double A2Phys::GlobalPos(int it,int ixy,double offsetx,double offsety){
  // Return the hit position on the global coordinate system.
  // 1st argment is ID of tower(0:25mm,1:32mm),
  // 2nd is ID for XY.(0:x,1:y)
  // 3rd and 4th is xy-offset value 
  // if offset=0, the detector is in the beam center postion.
  // if offset is non-zero value, return x'+offsetx.
  //
  // Modified by Alessio (26/05/2015): mirrored Arm2 geometry
  //
  double tmp;
  if(it==0){
    if(ixy==0){
      tmp = pos[0][0] - 8.0;
      return tmp+offsetx;
    }
    else if(ixy==1){
      tmp = pos[0][1] - 12.5;
      return tmp+offsety;
    }
    else {
      return -1.;
    }
  }
  if(it==1){
    if(ixy==0){
      tmp = pos[1][0] - 41.8;
      return tmp+offsetx;
    }
    else if(ixy==1){
      tmp = pos[1][1] + 14.3;
      return tmp+offsety;
    }
    else {
      return -1.;
    }  
  }
  return -1.;
}

double A2Phys::GPosR(int it,double offsetx,double offsety){
  double x,y;
  x = GPosX(it,offsetx,offsety);
  y = GPosY(it,offsetx,offsety); 
  return sqrt(x*x+y*y);
}

double A2Phys::GetPi0Distance(bool check){
  // Calculate the distance [mm] between 25mm hit position and 32mm hit position.
  // if the argment is true, check whether the event is the pi0 event or not.
  // but not implement yet.
  if(check==true){
  }
  double r2;
  double gpos[2][2];  // [tower][xy]
  for(int it=0;it<2;it++){
    for(int ixy=0;ixy<2;ixy++){
      gpos[it][ixy] =  GlobalPos(it,ixy,0.,0.);
    }
  }
  r2 = (gpos[0][0]-gpos[1][0])*(gpos[0][0]-gpos[1][0])
    + (gpos[0][1]-gpos[1][1])*(gpos[0][1]-gpos[1][1]);
  return sqrt(r2);
}

double A2Phys::GetPi0Mass(bool check){
  // Calculate the reconstructed mass [MeV] from the gamma-ray pair.
  // The distance from I.P. to Calorimter front is fixed (141.050m)
  // if the argment is true, check whether the event is the pi0 event or not.
  // but not implement yet.
  if(check==true){  
  }
  double r;
  double mass;
  r = GetPi0Distance(false);
  mass = sqrt(energy[0]*energy[1])*r/cDistance*1000.; // [Mev]
  return mass;
}

double A2Phys::GetPi0Energy(bool check){
  // Calculate the reconstructed pi0 energy[GeV]. (return energy[0]+energy[1])
  // if the argment is true, check whether the event is the pi0 event or not.
  // but not implement yet.
  if(check==true){  
  }
  return energy[0]+energy[1];
}

double A2Phys::Momentum(int it,int dir, double beamcenter_x,double beamcenter_y){
  // Return the momentum [GeV/c].
  // This value is reconstructed from energy, hit position, 
  // neutral beam center positon and detector position.
  // 1st argment is ID of tower(0:25mm,1:32mm). 
  // 2nd is ID of axis (0=x,1=y,2=z) on the global coordinate system.
  // 3rd and 4th are for the offset of beam center position.
  // (Modified in 04 Jan 2012)
  //   offsetx and offsety indicate the beam center position.
  //   if the beam center was at (-0.6, 0.0), please set as (-0.6, 0.0)
  //   In the previous version, it was (+0.6, 0.0) for the beam center position

  double offsetx = -1.* beamcenter_x;
  double offsety = -1.* beamcenter_y;
  if(dir==0 || dir==1){
    double hitpoint;
    hitpoint = GlobalPos(it,dir,offsetx,offsety);
    return energy[it]*hitpoint/cDistance;
  }
  // For Z
  else if(dir==2){ 
    double x,y;
    x =  GlobalPos(it,0,offsetx,offsety);
    y =  GlobalPos(it,1,offsetx,offsety);
    return energy[it]*sqrt(1-(x*x+y*y)/(cDistance*cDistance));
  }
  return 0.;
}

double A2Phys::GetPi0Momentum(int dir, double beamcenter_x, double beamcenter_y){
  // Return Pi0 Momentum [GeV/c]. ( Momentum(0,dir) + Momentum(1,dir))
  return Momentum(0,dir,beamcenter_x,beamcenter_y) + Momentum(1,dir,beamcenter_x,beamcenter_y);
}

double A2Phys::GetPi0MomentumX(double beamcenter_x, double beamcenter_y){
  // = GetPi0Momentum(0,beamcenter_x, beamcenter_y);
  return GetPi0Momentum(0,beamcenter_x, beamcenter_y);
}

double A2Phys::GetPi0MomentumY(double beamcenter_x, double beamcenter_y){
  // = GetPi0Momentum(1,beamcenter_x, beamcenter_y);
  return GetPi0Momentum(1,beamcenter_x, beamcenter_y);
}

double A2Phys::GetPi0Pt(double beamcenter_x, double beamcenter_y){
  // Return Pi0 transverse momentum [GeV/c]
  double px,py;
  px = GetPi0Momentum(0,beamcenter_x,beamcenter_y);
  py = GetPi0Momentum(1,beamcenter_x,beamcenter_y);
  return sqrt(px*px+py*py);
}

double A2Phys::GetPi0Pl(double beamcenter_x, double beamcenter_y){
  // = GetPi0Momentum(2,beamcenter_x, beamcenter_y);
  return GetPi0Momentum(2, beamcenter_x, beamcenter_y);
}

double A2Phys::GetPi0Rapidity(double beamcenter_x, double beamcenter_y){
  // Return Pi0 Rapidity, y
  // y = 1/2 ln {(E+Pl)/(E-Pl)}
  double pi0energy = GetPi0Energy();
  double pi0pl     = GetPi0Pl(beamcenter_x, beamcenter_y);
  return 0.5*log((pi0energy+pi0pl)/(pi0energy-pi0pl));
}

void A2Phys::Show(){
  cout.setf(ios::fixed);
  cout.setf(ios::right);
  //  cout << " ARM2 PHYS RUN" << setw(5) << run << "   " 
  cout << " RUN" << setw(5) << run << "   " 
       << "NUMBER: " << setw(7) << number << "   "
       << "GNUMBER: " << setw(7) << gnumber << "   "
       << endl
       << "  TOWER  HIT  PID  ENERGY   POSITION" << endl
       << "   25mm: " 
       << setw(3) << hits[0] << "  "
       << setw(3) << pid[0] << "  "
       << setw(6) << setprecision(1) << energy[0] << "  "
       << setw(5) << setprecision(1) << pos[0][0] << "  "
       << setw(5) << setprecision(1) << pos[0][1] << "  "
       << endl
       << "   32mm: " 
       << setw(3) << hits[1] << "  "
       << setw(3) << pid[1] << "  "
       << setw(6) << setprecision(1) << energy[1] << "  "
       << setw(5) << setprecision(1) << pos[1][0] << "  "
       << setw(5) << setprecision(1) << pos[1][1] << "  "  
       << endl;
}

// *****************************************************************
// *****        FOR CONVERSION OF POSITION COORDINATE          *****
// *****************************************************************
int A2Phys::SetPositionBeamCenter(double x,double y){
  sPositionBeamCenter[0] = x;
  sPositionBeamCenter[1] = y;
  return 0;
}

int A2Phys::SetPositionBeamPipeCenter(double x,double y){
  sPositionBeamPipe[0] = x;
  sPositionBeamPipe[1] = y;
  return 0;
}

double A2Phys::GlobalPos_Detector(int tower, int ixy){
  // Return the incident position in the global detector coordinate (The origin is the ideal detector center.). 
  return GlobalPos(tower, ixy, 0., 0.);
}

double A2Phys::GlobalPos_BC(int tower, int ixy, double offsetx,double offsety){
  // Return the hit position in the global beam center coordinate. 
  // The offset paramters should be the beam center position on the global detector coordinate system 
  // If offsetx, offsety are not given, the defaults value which are calculated from 
  // sPositionBeamCenter, are used. The sPositionBeamCenter can be setted by SetPositionBeamCenter()
  return GlobalPos(tower, ixy, -1.*offsetx, -1.*offsety);
}

double A2Phys::GlobalPos_BeamPipe(int tower, int ixy, double offsetx,double offsety){
  // Return the incident position in the global beam pipe coordinate. 
  // The offset paramters should be the detector center position on the global beam pipe coordinate system 
  // If offsetx, offsety are not given, the defaults value which are calculated from 
  // sPositionBeamPipe, are used. The sPositionBeamPipe can be setted by SetPositionBeamPipeCenter()
  return GlobalPos(tower, ixy, -1.*offsetx, -1.*offsety);
}
	
#endif
