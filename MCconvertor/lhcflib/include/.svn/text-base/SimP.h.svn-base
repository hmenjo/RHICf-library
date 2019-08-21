#ifndef __SIMP_H__
#define __SIMP_H__

#include <TNamed.h>
#include "globaldef.h"

class SimP : public TNamed {
 public:
  int     code;          // code for particle identification on Epics
  int     subcode;       // sub-code 
  int     charge;        // charge 
  int     user;          // 
  double  pos[3];        // Incident Position [mm]
  double  energy;        // Total Energy [GeV]
  double  mom[3];        // Momentum [GeV/c]

  //protected:
 public:
  // Parameters for conversion of coodinate system. 
  static double  sPositionBeamCenter[2];   //! offset parameters: beam position in the global_detector coodinate 
  static double  sPositionBeamPipe[2];     //! offset parameters: beam pipe position in the global detector coodinate. 

 public:
  SimP(){clear();}
  SimP(char* name, char *title) : TNamed(name,title){clear();}
  ~SimP(){;}

  int   clear();
  int   copy(SimP* d);     // copy name,title and data. 
  int   copydata(SimP* d); // copy only data.

  int    Code(){return code;}
  int    SubCode(){return subcode;}
  int    Charge(){return charge;}
  int    User(){return user;}
  int    Tag(){return User();}
  double Energy(){return energy;}
  // Old
  //double PosX(){return pos[0];} 
  //double PosY(){return pos[1];} 
  //double PosZ(){return pos[2];} 
  // New extraporate to the calorimeter surface.  
  double PosX();
  double PosY();
  double PosZ();
  double MomX(){return mom[0];}
  double MomY(){return mom[1];}
  double MomZ(){return mom[2];}
  double KineticEnergy();
  double Momentum();
  double Mass();
  bool   IsPhoton()  { return code==1 ? true : false;}
  bool   IsGammaray(){ return IsPhoton();}
  bool   IsElectron(){ return code==2 && charge==-1 ? true : false;}
  bool   IsPositron(){ return code==2 && charge==1  ? true : false;}
  bool   IsMup()     { return code==3 && charge==1  ? true : false;}
  bool   IsMun()     { return code==3 && charge==-1 ? true : false;}  
  bool   IsPi0()     { return code==4 && charge==0  ? true : false;}
  bool   IsPip()     { return code==4 && charge==1  ? true : false;}
  bool   IsPin()     { return code==4 && charge==-1 ? true : false;} 
  bool   IsK0()      { return code==5 && charge==0  ? true : false;} 
  bool   IsKp()      { return code==5 && charge==1  ? true : false;} 
  bool   IsKn()      { return code==5 && charge==-1 ? true : false;} 
  bool   IsProton()  { return code==6 && charge==1  ? true : false;} 
  bool   IsAntiProton(){ return code==6 && charge==-1  ? true : false;} 
  bool   IsNeutron() { return code==6 && charge==0  ? true : false;}
  bool   IsEta()     { return code==28 ? true : false;}
  bool   IsElemag()  { return (IsGammaray() | IsElectron() | IsPositron());}
  
  // Return position in the coordinate syste on selected calorimeter. 
  // Set the position offset of the detector from normal position. 
  void   CalPos(int id,int it,double &x,double &y,
		double offsetx=GetOffset(0),
		double offsety=GetOffset(1));  // Incident position in the calorimeter coordinate id=1/2/10(NewArm1)/20(NewArm2)
  double CalPosX(int id,int it,
		 double offsetx=GetOffset(0),
		 double offsety=GetOffset(1));  
  double CalPosY(int id,int it,
		 double offsetx=GetOffset(0),
		 double offsety=GetOffset(1));  
  int    CheckHit(int id,int it,double edgecut=0.0,
		  double offsetx=GetOffset(0),
		  double offsety=GetOffset(1)); // Check the hit in the given acceptance of calorimeter. id=1/2/10(NewArm1)/20(NewArm2)
  void   Show(int id=0,int it=0,
	      double offsetx=GetOffset(0),
	      double offsety=GetOffset(1));  

  // Incident Position in several coordinate system. ------------------------  
  double PositionShift(int xy, double offsetx,double offsety);      // Simple shift x'=x+offsetx, y'=y+offsety
  double GlobalPos_Detector(int xy, 
			    double offsetx=GetOffsetDetector(0),
			    double offsety=GetOffsetDetector(1)); // Incidnet Position in the global detector coordinate
  double GlobalPos_BC(int xy,
		      double offsetx=GetOffsetBC(0),
		      double offsety=GetOffsetBC(1));  // Incident Position in the global beam center coordinate 
  double GlobalPos_BeamPipe(int xy);                                                // Incident Position in the global beam pipe coordinate
  
  double GPosX_Detector(){ return GlobalPos_Detector(0);}  // Arias to GlobalPos_Detector(0)
  double GPosY_Detector(){ return GlobalPos_Detector(1);}  // Arias to GlobalPos_Detector(1)
  double GPosX_BC(){ return GlobalPos_BC(0);}              // Arias to GlobalPos_BC(0)
  double GPosY_BC(){ return GlobalPos_BC(1);}              // Arias to GlobalPos_BC(1)
  double GPosX_BeamPipe(){ return GlobalPos_BeamPipe(0);}  // Arias to GlobalPos_BeamPipe(0)
  double GPosY_BeamPipe(){ return GlobalPos_BeamPipe(1);}  // Arias to GlobalPos_BeamPipe(1)
  

  // Static Functions 
  static double GetCalorimeterSize(int id,int it);
  static int    SetPositionBeamCenter(double x,double y);     // Set the Beam Center Position in the Global_Detertor coordinate.
  static int    SetPositionBeamPipeCenter(double x,double y); // Set the Beam Pipe Center in the Global_Detertor coordinate.
  static double GetPositionBeamCenter(int xy){return sPositionBeamPipe[xy];}
  static double GetPositionBeamPipeCenter(int xy){return sPositionBeamPipe[xy];} 
  static double GetOffset(int xy){return -1.*sPositionBeamPipe[xy];}     // = -1.*sPositionBeamPipe[xy]
  static double GetOffsetDetector(int xy){return sPositionBeamPipe[xy];} // = sPositionBeamPipe[xy]
  static double GetOffsetBC(int xy){return sPositionBeamPipe[xy]-sPositionBeamCenter[xy];} // =sPositionBeamPipe[xy]-sPositionBeamCenter[xy] 

  ClassDef(SimP,1);   // Data class for information of one incident particle in simulation.
};

#endif
