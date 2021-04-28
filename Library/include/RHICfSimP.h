#ifndef __RHICFSIMP_H__
#define __RHICFSIMP_H__

#include <TNamed.h>
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TVector3.h"

class RHICfSimP : public TNamed {

 public:
  static const double cDistancefromIP;

 public:
/*   int     pdgcode;       // PDG code */
/*   TString name;          // particle name */

/*   int     user;          //  */
/*   double  pos[3];        // Incident Position [mm] */
/*   double  energy;        // Total Energy [GeV] */
/*   double  mom[3];        // Momentum [GeV/c] */

  protected:
  //public:
  // Parameters for conversion of coodinate system. 
  static double  sPositionBeamCenter[2];   //! offset parameters: beam position in the global_detector coodinate 
  static double  sPositionBeamPipe[2];     //! offset parameters: beam pipe position in the global detector coodinate. 

 public:
  RHICfSimP(){clear();}
  RHICfSimP(char* name, char *title) : TNamed(name,title){clear();};
  ~RHICfSimP(){;}

  int   clear();
  int   copy(RHICfSimP* d);     // copy name,title and data. 
  int   copydata(RHICfSimP* d); // copy only data.

  int    PDGcode(){return fPdgcode;}
  int    User(){return fTrackID;}
  int    Tag(){return User();}
  double Energy(){return fFMomentum.Energy();}

  double PosX();
  double PosY();
  double PosZ();
  double MomX(){return fFMomentum.Px();}
  double MomY(){return fFMomentum.Py();}
  double MomZ(){return fFMomentum.Pz();}
  double KineticEnergy();
  double Momentum();
  double Mass();

  bool   IsPhoton()    { return fPdgcode==22 ? true : false;}
  bool   IsGammaray()  { return IsPhoton();}
  bool   IsElectron()  { return fPdgcode==+11  ? true : false;}
  bool   IsPositron()  { return fPdgcode==-11  ? true : false;}
  bool   IsMup()       { return fPdgcode==-13  ? true : false;}
  bool   IsMun()       { return fPdgcode==-13  ? true : false;}
  bool   IsPi0()       { return fPdgcode==111  ? true : false;}
  bool   IsPip()       { return fPdgcode==+211 ? true : false;}
  bool   IsPin()       { return fPdgcode==-211 ? true : false;}
  bool   IsK0()        { return fPdgcode==130 || fPdgcode==310 || fPdgcode==11  ? true : false;}
  bool   IsKp()        { return fPdgcode==+321  ? true : false;}
  bool   IsKn()        { return fPdgcode==-321  ? true : false;}
  bool   IsProton()    { return fPdgcode==+2212 ? true : false;}
  bool   IsAntiProton(){ return fPdgcode==-2212 ? true : false;}
  bool   IsNeutron()   { return fPdgcode==+2112  ? true : false;}
  bool   IsAntiNeutron(){ return fPdgcode==-2112  ? true : false;}
  bool   IsEta()       { return fPdgcode==221 ? true : false;}
  bool   IsElemag()    { return (IsGammaray() | IsElectron() | IsPositron());}

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

 public:

  Int_t          fPdgcode;
  //TString        fName;     // Particle name
  TLorentzVector fFMomentum;// Particle momentum
  TVector3       fPosition; // Particle postion

  //TString        fOriginalPName;      // Original particle name
  //TLorentzVector fOriginalP4Momentum; // Original particle momentum
  //TVector3       fOriginalPPosition;  // Original particle postion

  Int_t          fTrackID; // TrackID
  //Int_t          fTower; // SmallOrLarge

 public:

  RHICfSimP(const RHICfSimP& rhs);
  RHICfSimP& operator=(const RHICfSimP& rhs);

  virtual void    Clear(Option_t* option = "");
  virtual void    Copy(RHICfSimP& obj);
  //void            SetName(TString);
  //TString         GetName(){ return fName;};
  void            Set4Momentum(TLorentzVector);
  TLorentzVector  Get4Momentum(){ return fFMomentum;};
  void            SetPosition(TVector3);
  TVector3        GetPosition(){return fPosition;};

  //void            SetOriginalPName(TString);
  //TString         GetOriginalPName(){ return fOriginalPName;};
  //void            SetOriginalP4Momentum(TLorentzVector);
  //TLorentzVector  GetOriginalP4Momentum(){ return fOriginalP4Momentum;};
  //void            SetOriginalPPosition(TVector3);
  //TVector3        GetOriginalPPosition(){return fOriginalPPosition;};

  //TVector3        GetFramePosition(const Double_t&);

  void            SetTrackID(Int_t);
  Int_t           GetTrackID(){return fTrackID;};
  //void            SetTower(Int_t);
  //Int_t           GetTower(){return fTower;};

  ClassDef(RHICfSimP,1);   // Data class for information of one incident particle in simulation.
};

#endif
