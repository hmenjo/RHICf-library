#ifndef __A2PHYS_H__
#define __A2PHYS_H__

// --------------------------------------------------------------------
//                               A2Phys
//             For detail, see A2Phys.cpp or Online Manual
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A2Phys : public TNamed {
 public:
  // event infomation
  int            run;         // Run number
  int            number;      // Arm#2  event number
  int            gnumber;     // Grobal event number
  double         time[2];

  double         energy[2];   // Energy[GeV] of each calorimter. [tower]  0:25mm, 1:32mm 
  double         pos[2][2];   // Hit position[mm] on the calorimteter system. [tower][xy]
  double	 sideposit[2][4][2][3]; // Energy deposit in silicon. [tower][layer][xy][sample] //Added by eugenio
  double	 sidepositsum[2][3];    // Energy deposit in silicon summed over all layers. [tower][sample] //Added by eugenio  
  int            pid[2];      // Particle ID 0:elemag 1:hadronic [tower]
  int            hits[2];     // Number of hits  [tower]

  unsigned int   flag[3];     // GPIO0:2ch  + GPIO:1ch

 protected:
  // Parameters for conversion of coodinate system. 
  static double  sPositionBeamCenter[2];   //! offset parameters: beam position in the global_detector coodinate 
  static double  sPositionBeamPipe[2];     //! offset parameters: beam pipe position in the global detector coodinate. 


 public:
  A2Phys(){clear();}
  A2Phys(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Phys(){;}
  
  int    clear();
  int    copy(A2Phys* );
  int    copydata(A2Phys* );

  double Energy(int it){return energy[it];}
  double Pos(int it,int ixy){return pos[it][ixy];}
  double X(int it){return pos[it][0];}
  double Y(int it){return pos[it][1];}
  int    Hits(int it){return hits[it];}
  int    PID(int it){return pid[it];}
  bool   IsElemag(int it){ return pid[it]==ELEMAG ? true : false;}
  bool   IsHadron(int it){ return pid[it]==HADRON ? true : false;}  

  // ******************** FOR ANALYSIS **********************
  bool   InFiducial(int it,double edgecut=2.0);
  double GlobalPos(int it,int ixy,double offsetx=0.,double offsety=0.);
         // Return the hit position on the global coordinate system.
         // 1st argment is ID of tower(0:25mm,1:32mm), 2nd is ID for XY.(0:x,1:y)
         // 3rd and 4th is xy-offset value 
         // if offset is non-zero, return x'+offsetx. 
  double GPos(int it,int ixy,double offsetx=0.,double offsety=0.) // Note: offsetx, offsety = -1.* beamcenter 
         {return GlobalPos(it,ixy,offsetx,offsety);}
         // Alias of GlobalPos();
  double GPosX(int it,double offsetx=0.,double offsety=0.)  // Note: offsetx, offsety = -1.* beamcenter 
         {return GlobalPos(it,0,offsetx,offsety);}
         // Alias to X-GlobalPos(it,0)
  double GPosY(int it,double offsetx=0.,double offsety=0.)  // Note: offsetx, offsety = -1.* beamcenter 
         {return GlobalPos(it,1,offsetx,offsety);} 
         // Alias to Y-GlobalPos(it,1)
  double GPosR(int it,double offsetx=0.,double offsety=0.);  // Note: offsetx, offsety = -1.* beamcenter 
  double GetPi0Distance(bool check=false);
         // Calculate the distance [mm] between 25mm hit position and 32mm hit position.
         // if the argment is true, check whether the event is the pi0 event.
         // but not implement yet.
  double GetPi0Mass(bool check=false);   
         // Calculate the reconstructed mass [MeV] from the gamma pair. 
         // The distance from I.P. to Calorimter sirface is fixed (141.050m)
         // if the argment is true, check whether the event is the pi0 event.
         // but not implement yet.
  double GetPi0Energy(bool check=false);                               // Pi0 Energy [GeV] (energy[0]+energy[1])
         // Calculate the reconstructed pi0 energy[GeV]. (return energy[0]+energy[1])
         // if the argment is true, check whether the event is the pi0 event.
         // but not implement yet.
  double Momentum(int it,int dir, 
		  double beamcenter_x=GetOffsetBC(0),
		  double beamcenter_y=GetOffsetBC(1)); 
         // Calculate the momentum [GeV/c].
         // This value is reconstructed from energy, hit position, 
         // neutral beam center positon and detector position.
         // 1st argment is ID of tower(0:25mm,1:32mm). 
         // 2nd is ID of axis (0=x,1=y,2=z) on the global coordinate system.
         // 3rd and 4th are for the offset of beam center position. 
         // (Modified in 04 Jan 2012)
         //   offsetx and offsety indicate the beam center position.
         //   if the beam center was at (-0.6, 0.0), please set as (-0.6, 0.0)
         //   In the previous version, it was (+0.6, 0.0) for the beam center position
  double GetPi0Momentum(int dir, 
			double beamcenter_x=GetOffsetBC(0), 
			double beamcenter_y=GetOffsetBC(1));     // Return Pi0 Momentum [GeV/c]. ( Momentum(0,dir) + Momentum(1,dir))
  double GetPi0MomentumX(double beamcenter_x=GetOffsetBC(0), 
			 double beamcenter_y=GetOffsetBC(1));    // Pi0 Momentum_X [GeV/c] (=GetPi0Momentum(0,beamcenter_x,beamcenter_y))
  double GetPi0MomentumY(double beamcenter_x=GetOffsetBC(0), 
			 double beamcenter_y=GetOffsetBC(1));    // Pi0 Momentum_Y [GeV/c] (=GetPi0Momentum(1,beamcenter_x,beamcenter_y))   
  double GetPi0Pt(double beamcenter_x=GetOffsetBC(0), 
		  double beamcenter_y=GetOffsetBC(1));           // Return Pi0 transverse momentum [GeV/c]   
  double GetPi0Pl(double beamcenter_x=GetOffsetBC(0), 
		  double beamcenter_y=GetOffsetBC(1));           // Pi0 longitudinal momentum [GeV/c] (=GetPi0Momentum(2))
  double GetPi0Rapidity(double beamcenter_x=GetOffsetBC(0), 
			double beamcenter_y=GetOffsetBC(1));     // Pi0 Rapidity

  // Hit Position in several coordinate system. ------------------------ 
  double GlobalPos_Detector(int tower, int ixy);                         // Hit Position in the global detector coordinate
  double GlobalPos_BC(int tower, int ixy, 
		      double offsetx=GetOffsetBC(0),
		      double offsety=GetOffsetBC(1));                    // Hit Position in the global beam center coordinate 
  double GlobalPos_BeamPipe(int tower, int ixy,    
			    double offsetx=GetOffsetBeamPipe(0),
			    double offsety=GetOffsetBeamPipe(1));        // Hit Position in the global beam pipe coordinate
  
  double GPosX_Detector(int tower){return GlobalPos_Detector(tower,0);}  // Arias to GlobalPos_Detector(tower,0)
  double GPosY_Detector(int tower){return GlobalPos_Detector(tower,1);}  // Arias to GlobalPos_Detector(tower,1)
  double GPosX_BC(int tower){return GlobalPos_BC(tower,0);}              // Arias to GlobalPos_BC(tower,0)
  double GPosY_BC(int tower){return GlobalPos_BC(tower,1);}              // Arias to GlobalPos_BC(tower,1)
  double GPosX_BeamPipe(int tower){return GlobalPos_BeamPipe(tower,0);}  // Arias to GlobalPos_BeamPipe(tower,0)
  double GPosY_BeamPipe(int tower){return GlobalPos_BeamPipe(tower,1);}  // Arias to GlobalPos_BeamPipe(tower,1)
  

  void   Show();   // Print informations.
  
  // Definition 
  static const int     ALLPARTICLE = -10;       //!
  static const int     ELEMAG = 0;              //!
  static const int     HADRON = 1;              //!
  static const double  cDistance;               //! Distance between I.P. and the front of calorimeter. [mm]
  static const double  cPi0mass;                //! Pi0 invariant mass [MeV]
  
  // Static Functions
  static double CalorimeterSize(int it){return it==0 ? 25.0 : 32.0;}
  static int    SetPositionBeamCenter(double x,double y);                 // Set the Beam Center Position in the Global_Detertor coordinate.[mm]
  static int    SetPositionBeamPipeCenter(double x,double y);             // Set the Beam Pipe Center in the Global_Detertor coordinate.[mm]
  static double GetOffsetBC(int xy){return sPositionBeamCenter[xy];}      // = sPositionBeamCenter[xy]  
  static double GetOffsetBeamPipe(int xy){return sPositionBeamPipe[xy];}  // = sPositionBeamPipe[xy]  
  
  ClassDef(A2Phys,1);
};

#endif
