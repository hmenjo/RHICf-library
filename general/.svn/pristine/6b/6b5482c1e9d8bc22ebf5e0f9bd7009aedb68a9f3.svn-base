#ifndef __STRIP2COORD_CPP__
#define __STRIP2COORD_CPP__

#include "Arm2Alignment.h"

//--------------------------------------------------------------------------------
//
//   This class is for the alignment of Arm2 silicon detector. 
//   It can convert the strip number to the position on sereral coordinates. 
//   The original is under 
//   svn+ssh://cvslhcf@gr1farm1.ct.infn.it/usr/local/svn/lhcfrepository/trunk/SW/alignment
//
//--------------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(Arm2Alignment);
#endif


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
using namespace std;


const int    Arm2Alignment::SILINMOD;                               //Number of silicon modules
const double Arm2Alignment::ZPOS_XSIL_IN_MODULE =11.107;            //position if x sili inside module (in mm) 
const double Arm2Alignment::ZPOS_YSIL_IN_MODULE =12.942;            //position of y sili inside module (in mm) (ZPOS_XSIL_IN_MODULE+1.835)
const double Arm2Alignment::ZPOS_1ST_W_MODULE_FROM_FRONT_FACE=16.0; //position offace of 1st W module from front face (in mm)
const double Arm2Alignment::THICKNESS_BEFORE_1ST_SILI_MOD = 17.700; //tot thickness of two modules before 1st sili module (in mm)
const double Arm2Alignment::STRIPPITCH =0.080;                      //silicon strip pitch in mm (=80 micron)
const int    Arm2Alignment::FIRST_STRIP_READ_XSIDE = 5;             //1st physical strip (1-768) on sili x-side that is read-out
const int    Arm2Alignment::FIRST_STRIP_READ_YSIDE = 5;             //1st physical strip (1-768) on sili y-side that is read-out
const int    Arm2Alignment::FIRST_STRIP_XPCB = 3;                   //Strip pf PCB connected to 1st readout strip on sili x-side
const int    Arm2Alignment::FIRST_STRIP_YPCB = 2;                   //Strip pf PCB connected to 1st readout strip on sili y-side
//Coordinates of centers of reference frames expressed in the left G10 bar reference frame
const double Arm2Alignment::beamcentercoords[2]={25.780,24.580};               //Coords of beam center in the frame centered on the left G10 bar (in mm)
const double Arm2Alignment::calo25lowrightcornercoords[2]={42.000,12.080};     //Coords of right lower corner of small (25mm) Arm2 tower (in mm)
const double Arm2Alignment::calo32lowrightcornercoords[2]={15.200,38.880};     //Coords of right lower corner of  big  (32mm) Arm2 tower (in mm)
//Rotation angles around the z-azis of each silicon frame (4x and 4y) with respect to design, in the left G10 bar frame
const double Arm2Alignment::theta_x[Arm2Alignment::SILINMOD]={.000118, -.003811,  .003286,  .002346}; //Rotation angle for x layers in left G10 bar frame (rad)
const double Arm2Alignment::theta_y[Arm2Alignment::SILINMOD]={.000355, -.007339, -.000807, -.002319}; //Rotation angle for y layers in left G10 bar frame (rad)
//Position of beginning of strip 1 in the left G10 bar frame (in mm)
const double Arm2Alignment::p1x[Arm2Alignment::SILINMOD]={-17.700, -18.180, -17.770, -17.833};   //x coord of P1 (beginning of strip 1) for x layers (in mm)
const double Arm2Alignment::p1y[Arm2Alignment::SILINMOD]={ 10.472,  10.276,  10.221,  10.426};   //y coord of P1 (beginning of strip 1) for x layers (in mm)
const double Arm2Alignment::q1x[Arm2Alignment::SILINMOD]={ 43.679,  43.988,  44.089,  43.987};   //x coord of Q1 (beginning of strip 1) for y layers (in mm)
const double Arm2Alignment::q1y[Arm2Alignment::SILINMOD]={ 72.152,  72.091,  72.195,  72.240};   //y coord of Q1 (beginning of strip 1) for y layers (in mm)
//Vectors from points O1 (center of left bar ref) to point A and 1, expressed in the general LHCf frame (in mm, from design)
const double Arm2Alignment::PA_O1_general_design[3]={20.,762.,8.};
const double Arm2Alignment::P1_O1_general_design[3]={20.,762.,270.};
//Coordinates of points A and 1 measured by the Survey Team in their reference frame (LHC frame)
const double Arm2Alignment::PA_LHC_meas[3]={45.280,829.380, 38.790};
const double Arm2Alignment::P1_LHC_meas[3]={46.070,829.690,300.690};
//Distances of silicon modules with respect to the first silicon module, along the z-axis (in mm)
const double Arm2Alignment::sil_dist[Arm2Alignment::SILINMOD]={0.000, 35.830, 127.160, 184.130};
//Rotation matrix determined for the movable part of Arm2, expressed in the LHC Survey Team reference frame
const double Arm2Alignment::R[3][3]={ {1.000000,  -0.003364,  0.002045},{0.003364,   1.000000,  0.000859},{-0.002045,  -0.000859,  1.000000} };
//Inverse matrix
const double Arm2Alignment::Rinv[3][3]={ {1.000000,   0.003364, -0.002045},{-0.003364,   1.000000, -0.000859},{0.002045,   0.000859,  1.000000} };
//Rotation matrix determined for the fixed part of Arm2 (manipulator), in the LHC Survey Team reference frame
const double Arm2Alignment::S[3][3]={ {1.000000,  -0.001495,  0.002045},{0.001495,   1.000000,  0.000859},{-0.002045,  -0.000859,  1.000000} };
//Inverse rotation matrix
const double Arm2Alignment::Sinv[3][3]={ {1.000000, 0.001495, -0.002045},{-0.001495,   1.000000, -0.000859},{0.002045,   0.000859,  1.000000} };



//--- Implementation of methods for class strip2coord ------------------------------

//--- Constructor ------------------------------------------------------------------
Arm2Alignment::Arm2Alignment(double position){
  Init();
  //Set info for manipulator position
  Hit.ManipPosition=position;
}
Arm2Alignment::Arm2Alignment(){
  Init();
}
//--- Destructor -------------------------------------------------------------------
Arm2Alignment::~Arm2Alignment(){}


//--- Init -------------------------------------------------------------------------
int Arm2Alignment::Init(){
  //Find vector from points A and 1 to beam center on front face of Arm2
  vec_PA_to_beamcenter_on_front_face[0]=-beamcentercoords[0]-PA_O1_general_design[0];
  vec_PA_to_beamcenter_on_front_face[1]=beamcentercoords[1]-PA_O1_general_design[1];
  vec_PA_to_beamcenter_on_front_face[2]=0-PA_O1_general_design[2];
  vec_P1_to_beamcenter_on_front_face[0]=-beamcentercoords[0]-P1_O1_general_design[0];
  vec_P1_to_beamcenter_on_front_face[1]=beamcentercoords[1]-P1_O1_general_design[1];
  vec_P1_to_beamcenter_on_front_face[2]=0-P1_O1_general_design[2];
  //Initialize variables to store raw hit information
  Hit.Strips[0]=Hit.Strips[1]=-100;
  Hit.Module=-1;
  return 0;
}
//--- ClearHit ---------------------------------------------------------------------
int Arm2Alignment::ClearHit(void){
  int i;
  Hit.Strips[0]=Hit.Strips[1]=0;
  Hit.Module=0;
  for(i=0;i<3;i++){
    Hit.LeftbarCoord[i]=0;
    Hit.GeneralCoord[i]=0;
    Hit.CalorimCoord[i]=0;
    Hit.CalorimCoord[i+3]=0;
    Hit.LHC_Coord[i]=0;
  }
  return 0;
}

//--- GetPos -----------------------------------------------------------------------
double Arm2Alignment::GetPos(void){
  return Hit.ManipPosition;
}
//--- GetHit -----------------------------------------------------------------------
struct Arm2Hit Arm2Alignment::GetHit(void){
  return Hit;
}
//--- SetMod -----------------------------------------------------------------------
int Arm2Alignment::SetRawHit(int mod,double x[2]){
  ClearHit();
  Hit.Module=mod;
  Hit.Strips[0]=x[0];
  Hit.Strips[1]=x[1];
  return 0;
}
//--- SetMod -----------------------------------------------------------------------
int Arm2Alignment::SetRawHit(int mod,double x,double y){
  double strip[2];
  strip[0] = x;
  strip[1] = y;
  return SetRawHit(mod,strip);
} 
//--- SetPos -----------------------------------------------------------------------
int Arm2Alignment::SetPos(double position){
  Hit.ManipPosition=position;  
  return 0;
}

//------------------------------------------------------------------------------------------------------------------
//-------- strip2coord ---------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//-------- Description of input/output parameters (see also ../include/strip2coord_CL.h) ---------------------------
//------------------------------------------------------------------------------------------------------------------
// frame flag: 0 to go from strip num to coords in the frame centered on the left G10 bar 
//               and with center on the Arm2 front face without the external 1mm thick aluminum layer
//             1 to go from strip num to coords in the general LHCf Arm2 frame centered on the beam center
//             2 to go from strip num to coords in the calo Arm2 frame centered on right lower corner of 
//               both towers in this case cartesian_coord is an array of six vars: x1,y1,z1,x2,y2,z2
//               (1=small tower, 2=big tower)
// mod            : index of module where the hit has been found (0...3)
// raw_strip_coord: is the array of 2 numbers (u,v) containing the raw hit coords in strip number
// cartesian_coord: is the output array of 3 or 6 numbers (depending on frame_flag parameter)
struct Arm2Hit Arm2Alignment::Strip2Coord(){
  // int err=0; //commented out by H.MENJO because it is not used in this function

  //z coord for point on selected silicon module; I assume that best point estimate is
  //in the middle between the corresponding x and y layers
  double z_Hit=0;

  int mod;         //Hit module
  double pu[2],qv[2];
  // double ptemp[3]; // commented out by H.MENJO because it is not used in this function
  double uu,vv;    //Coordinated of hits on x and y view (expressed in strip number)
  double mm,qq;    //Parameters for hit line on x side layer (ang. coeff, and known term)
  double rr,ss;    //Parameters for hit line on y side layer (ang. coeff, and known term)

  //Now definition of some variables used in the last part of routine in case we require
  //coordinated in the LHC frame
  int i,j;
  double temp_coord[3]; //Temporary coordinates (they consider GARAGE position and not account for different positions)
  double tv[3]={0,-1,0};//Ideal direction of manip translation
  double tv_rot[3];     //Real direction of manipulator translation
  double tv_rot_mod=0;  //Module of tv_rot before normalization
  double trasl[3];      //Real vector of manipulator translation (its lenght is the amount of translation, and direction is tv_rot)

  //******** START MAIN ROUTINE **********
  mod=Hit.Module;

  //Read x and y strips of hit as passed (0...383) and convert to real strip (1...768)
  uu=(2*(Hit.Strips[0]-FIRST_STRIP_XPCB)+FIRST_STRIP_READ_XSIDE); 
  vv=(2*(Hit.Strips[1]-FIRST_STRIP_YPCB)+FIRST_STRIP_READ_YSIDE);

  //Find x,y coord for beginning of the line that pass trough the hit point and parallel
  //to strips (in mm, in left G10 bar frame)
  pu[0]=p1x[mod]+(uu-1)*STRIPPITCH*cos(theta_x[mod]);
  pu[1]=p1y[mod]+(uu-1)*STRIPPITCH*sin(theta_x[mod]);

  //Find angular coefficient and known term for hit-line on x side (in delrin frame)
  mm=tan(theta_x[mod]-M_PI/2);
  qq=pu[1]-pu[0]*mm;

  //Find x,y coord for beginning of the line that pass trough the hit point and parallel to
  //strips (in mm, in left G10 bar frame)
  qv[0]=q1x[mod]+(vv-1)*STRIPPITCH*sin(theta_y[mod]);
  qv[1]=q1y[mod]-(vv-1)*STRIPPITCH*cos(theta_y[mod]);

  //Find angular coefficient and known term for hit-line on y side (in left G10 bar frame)
  rr=tan(theta_y[mod]);
  ss=qv[1]-qv[0]*rr;

  //Find the z value of point as the mean z-coord of x/y layer of module where the hit is found, in the
  //general LHCf frame. This z coordinate is found in the following way: from design the front face of
  //Arm2 is at z=0mm in this frame; then consider that we have a Al block 15mm thick plus 1mm Al layer
  //before beginning of 1st detector (W) layer; therefore 1st layer begins at z=+15+1=+16mm; then we
  //consider the measured thickness of modules before the 1st silicon module: 7.33mm+10.37mm=17.70mm;
  //1st silicon module starts at x=16mm+17.70mm=33.70mm; finally the 1st x silicon is at 11.107mm and
  //1st y silicon is at 1.835mm from x silicon
  //--> zx=33.700+11.107=44.807mm, zy=44.807mm+1.835mm=46.642mm --> z_Hit=(zx+zy)/2=45.725mm
  //Then we must add the position of considered module with respect to the first one
  z_Hit=(ZPOS_1ST_W_MODULE_FROM_FRONT_FACE+THICKNESS_BEFORE_1ST_SILI_MOD+0.5*(ZPOS_XSIL_IN_MODULE+ZPOS_YSIL_IN_MODULE)+sil_dist[mod]); 

  //Find final reconstructed point in the LHCf reference frames
  Hit.LeftbarCoord[0]=(ss-qq)/(mm-rr);
  Hit.LeftbarCoord[1]=(mm*ss-rr*qq)/(mm-rr);
  Hit.LeftbarCoord[2]=-z_Hit; //(<0 because of z-axis)

  Hit.GeneralCoord[0]=-(Hit.LeftbarCoord[0]-beamcentercoords[0]);
  Hit.GeneralCoord[1]= (Hit.LeftbarCoord[1]-beamcentercoords[1]);
  Hit.GeneralCoord[2]=z_Hit;

  Hit.CalorimCoord[0]=-(Hit.LeftbarCoord[0]-calo25lowrightcornercoords[0]);
  Hit.CalorimCoord[1]= (Hit.LeftbarCoord[1]-calo25lowrightcornercoords[1]);
  Hit.CalorimCoord[2]=z_Hit;
  Hit.CalorimCoord[3]=-(Hit.LeftbarCoord[0]-calo32lowrightcornercoords[0]);
  Hit.CalorimCoord[4]= (Hit.LeftbarCoord[1]-calo32lowrightcornercoords[1]);
  Hit.CalorimCoord[5]=z_Hit;

 //Find vector from points A and 1 to hit point P (P-A) expressed in the general frame of Arm2
  vec_PA_to_hit_point[0]=vec_PA_to_beamcenter_on_front_face[0]+Hit.GeneralCoord[0];
  vec_PA_to_hit_point[1]=vec_PA_to_beamcenter_on_front_face[1]+Hit.GeneralCoord[1];
  vec_PA_to_hit_point[2]=vec_PA_to_beamcenter_on_front_face[2]+Hit.GeneralCoord[2];
  vec_P1_to_hit_point[0]=vec_P1_to_beamcenter_on_front_face[0]+Hit.GeneralCoord[0];
  vec_P1_to_hit_point[1]=vec_P1_to_beamcenter_on_front_face[1]+Hit.GeneralCoord[1];
  vec_P1_to_hit_point[2]=vec_P1_to_beamcenter_on_front_face[2]+Hit.GeneralCoord[2];

  //Now find the coordinates in the LHC Survey Team reference frame:
  //rotate the vector (P-A) and (P-1) to express them in the LHC frame and sum the A and 1 coordinates
  //as measured by the Survey Team
  LHC_coord_PA[0]=R[0][0]*vec_PA_to_hit_point[0]+R[0][1]*vec_PA_to_hit_point[1]+R[0][2]*vec_PA_to_hit_point[2]+PA_LHC_meas[0];
  LHC_coord_PA[1]=R[1][0]*vec_PA_to_hit_point[0]+R[1][1]*vec_PA_to_hit_point[1]+R[1][2]*vec_PA_to_hit_point[2]+PA_LHC_meas[1];
  LHC_coord_PA[2]=R[2][0]*vec_PA_to_hit_point[0]+R[2][1]*vec_PA_to_hit_point[1]+R[2][2]*vec_PA_to_hit_point[2]+PA_LHC_meas[2];
  LHC_coord_P1[0]=R[0][0]*vec_P1_to_hit_point[0]+R[0][1]*vec_P1_to_hit_point[1]+R[0][2]*vec_P1_to_hit_point[2]+P1_LHC_meas[0];
  LHC_coord_P1[1]=R[1][0]*vec_P1_to_hit_point[0]+R[1][1]*vec_P1_to_hit_point[1]+R[1][2]*vec_P1_to_hit_point[2]+P1_LHC_meas[1];
  LHC_coord_P1[2]=R[2][0]*vec_P1_to_hit_point[0]+R[2][1]*vec_P1_to_hit_point[1]+R[2][2]*vec_P1_to_hit_point[2]+P1_LHC_meas[2];
  temp_coord[0]=(LHC_coord_PA[0]+LHC_coord_P1[0])/2;
  temp_coord[1]=(LHC_coord_PA[1]+LHC_coord_P1[1])/2;
  temp_coord[2]=(LHC_coord_PA[2]+LHC_coord_P1[2])/2;

  //Now finding coords in LHC frame
  //In this case we must go from LHCf frame to LHC frame taking into account the 
  //manipulator position.
  //I assume that the movement is done not exactly along the vertical direction of the
  //LHC frame, bu at an angle given by the rotation of the normal to the top plate of
  //the manipulator itself. This rotation has been found by means of the Survey Team
  //measurements of points C,D,3,4. Results is matrix S written before.
  //First I find the translation versor: tv = S * tv = S*(0,-1,0). This measn that I
  //consider the vertical direction, along which the manipulator should move according
  //to design, and apply a rotation S to find the direction along which it moves in the
  //LHC frame. Then I multiply by the amount of translation (Arm2_position)
  tv_rot_mod=0;
  for (i=0;i<=2;i++) {
    tv_rot[i]=0;
    for(j=0;j<=2;j++) tv_rot[i]+=S[i][j]*tv[j];
    tv_rot_mod+=(tv_rot[i]*tv_rot[i]);
  }
  tv_rot_mod=sqrt(tv_rot_mod);
  for (i=0;i<=2;i++) {
    tv_rot[i]/=tv_rot_mod;
    trasl[i]=tv_rot[i]*fabs(Hit.ManipPosition);
    //Finally find final coordinates in the LHC ref frame by adding the traslation vector (trasl) to the coordinates
    //found assuming to be in the GARAGE position (temp_coord)
    Hit.LHC_Coord[i]=temp_coord[i]+trasl[i];
  }


  return Hit;
}


#endif
