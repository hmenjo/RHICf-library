#ifndef __STRIP2COORD__
#define __STRIP2COORD__

#include <TObject.h>

//*************************************************************************************************
//***************  struct Arm2 hit  ***************************************************************
//*************************************************************************************************
//*************************************************************************************************
struct Arm2Hit{
  //Distance of Arm2 from the GARAGE position (amount of displacement due to manipulator, in mm)
  double ManipPosition;
  //Coordinates of hit point expressed in strip number and id of hit module
  double Strips[2]; //
  int    Module;
  //Arrays for coordinate results in the three different reference frame of Arm2
  double LeftbarCoord[3]; //Final coords expressed in the "leftbar" reference frame
  double GeneralCoord[3]; //Final coords expressed in the "general" reference frame
  double CalorimCoord[6]; //Final coords expressed in the "calorim" reference frame
  //Arrays for coordinate results in the LHC reference frame
  double LHC_Coord[3];
};



//*************************************************************************************************
//***************  class Arm2Alignment ************************************************************
//***************                      ************************************************************
//*************************************************************************************************
class Arm2Alignment {
 public:
  static const int    SILINMOD = 4;                       //Number of silicon modules
  
 private:

  //Structure to hold all results from Strip2Coord conversion
  struct Arm2Hit Hit;
                      
  static const double ZPOS_XSIL_IN_MODULE;                //position if x sili inside module (in mm) 
  static const double ZPOS_YSIL_IN_MODULE;                //position of y sili inside module (in mm)
  static const double ZPOS_1ST_W_MODULE_FROM_FRONT_FACE;  //position offace of 1st W module from front face (in mm)
  static const double THICKNESS_BEFORE_1ST_SILI_MOD;      //tot thickness of two modules before 1st sili module (in mm)
  static const double STRIPPITCH;                         //silicon strip pitch in mm (=80 micron)
  static const int    FIRST_STRIP_READ_XSIDE;             //1st physical strip (1-768) on sili x-side that is read-out
  static const int    FIRST_STRIP_READ_YSIDE;             //1st physical strip (1-768) on sili y-side that is read-out
  static const int    FIRST_STRIP_XPCB;                   //Strip pf PCB connected to 1st readout strip on sili x-side
  static const int    FIRST_STRIP_YPCB;                   //Strip pf PCB connected to 1st readout strip on sili y-side
  //Coordinates of centers of reference frames expressed in the left G10 bar reference frame
  static const double beamcentercoords[2];            //Coords of beam center in the frame centered on the left G10 bar (in mm)
  static const double calo25lowrightcornercoords[2];  //Coords of right lower corner of small (25mm) Arm2 tower (in mm)
  static const double calo32lowrightcornercoords[2];  //Coords of right lower corner of small (25mm) Arm2 tower (in mm)
  //Rotation angles around the z-azis of each silicon frame (4x and 4y) with respect to design, in the left G10 bar frame
  static const double theta_x[SILINMOD];
  static const double theta_y[SILINMOD];
  //Position of beginning of strip 1 in the left G10 bar frame (in mm)
  static const double p1x[SILINMOD];
  static const double p1y[SILINMOD];
  static const double q1x[SILINMOD];
  static const double q1y[SILINMOD];
  //Vectors from points O1 (center of left bar ref) to point A and 1, expressed in the general LHCf frame (in mm, from design)
  static const double PA_O1_general_design[3];
  static const double P1_O1_general_design[3];
  //Coordinates of points A and 1 measured by the Survey Team in their reference frame (LHC frame)
  static const double PA_LHC_meas[3];
  static const double P1_LHC_meas[3];
  //Distances of silicon modules with respect to the first silicon module, along the z-axis (in mm)
  static const double sil_dist[SILINMOD];
  //Rotation matrix determined for the movable part of Arm2, expressed in the LHC Survey Team reference frame
  static const double R[3][3];
  //Inverse rotation matrix
  static const double Rinv[3][3];
  //Rotation matrix determined for the fixed part of Arm2 (manipulator), in the LHC Survey Team reference frame
  static const double S[3][3];
  //Inverse rotation matrix
  static const double Sinv[3][3];

  //Vector pointing from point A (Survey measurements) to the point defined as intersection of beam line with 
  //the front face plane of Arm2, expressed in the general frame. It must be summed to the coordinates of
  //point of interest (in the general frame) to find the vector pointing from point A to that point. Then we must rotate
  //the final vector (remember that the rotation matrix is given in the general frame) to find its expression in the LHC
  //Survey Team frame.
  double vec_PA_to_beamcenter_on_front_face[3];//In the general LHCf frame --> = {-20.000, -762.000, -8};
  double vec_P1_to_beamcenter_on_front_face[3];//In the general LHCf frame --> = {-20.000, -762.000, -270};
  //Vector pointing from point A and 1 (Survey measurements) to the point hit point
  double vec_PA_to_hit_point[3];               //In the general LHCf frame
  double vec_P1_to_hit_point[3];               //In the general LHCf frame
  //Arrays for coordinate results in the LHC reference frame
  double LHC_coord_PA[3];
  double LHC_coord_P1[3];

  
 public:
  Arm2Alignment(double position);
  Arm2Alignment();
  virtual ~Arm2Alignment();

  int     Init         (void);               //Do some initialization for Arm2 geometric parameter
  int     ClearHit     (void);               //Reset all hit structure apart the manipulator position
  int     SetRawHit    (int mod,double x[2]);//Set the hit expressed in readout strip number (0...383)
  int     SetRawHit    (int mod,double x,double y); // Alias to SetRawHit(int, double[2]);
  int     SetPos       (double position);    //Set manipulator position (distance from GARAGE, in mm)
  double  GetPos       (void);               //Return manipulator position (distance from GARAGE, in mm)

  struct  Arm2Hit GetHit(void);              //Get structure with all stored hit info
  struct  Arm2Hit Strip2Coord(void);         //Convert hit raw data to cartesian coords and return resut structure

  ClassDef(Arm2Alignment,1);   // Alignment of the Arm2 detector
};

#endif
