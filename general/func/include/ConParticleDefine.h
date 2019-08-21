#ifndef __CONPARTICLEDEFINE_H__
#define __CONPARTICLEDEFINE_H__

//-----------------------------------------------------------------
//                          ConParticleDefine 
//-----------------------------------------------------------------

#include <TObject.h>

class ConParticleDefine{
protected:
  char       tablefile[256];
  char       format[256];
  int        type;
  int        version;
  
  int        detector;
  int        hv0;
  int        hv1;
  int        scifihv;
  double     fchv1;
  double     fchv2;
  
  double     def_cal[2][16];         // Calorimeter   Tower:Layer
  double     def_scifi0[4][2][20];   // Scifi 20mm    Layer:XY:Ch
  double     def_scifi1[4][2][40];   // Scifi 40mm    Layer:XY:Ch
  double     def_fc[2][4];           // Front Counter Arm:Ch
  double     def_silicon[4][2][384]; // Silicon Layer:XY:Strip

public:
  ConParticleDefine();
  ConParticleDefine(char* file,char option[] = "ADC SCIF FC");
  virtual ~ConParticleDefine();
  
  int        Initialize();
  int        GetType(){return type;}
  void       SetType(int t){type = t;}
  int        GetVersion(){return version;}
  void       SetVersion(int v){version = v;}

  int        SetDetector(int d){detector = d;return CONPARTICLEDEFINE_OK;}
  short int  GetDetector(){return detector;}
  int        SetHV(int it,int hv);
  double     GetHV(int it);
  int        SetHV0(int hv){return SetHV(0,hv);}
  double     GetHV0(){return GetHV(0);}
  int        SetHV1(int hv){return SetHV(1,hv);}
  double     GetHV1(){return GetHV(1);}
  int        SetScifiHV(int hv){scifihv = hv;return CONPARTICLEDEFINE_OK;}
  double     GetScifiHV(){return (double)scifihv;}
  int        SetFCHV(int id,double hv);
  double     GetFCHV(int id);
  int        SetFCHV1(double hv){return SetFCHV(1,hv);}
  double     GetFCHV1(){return GetFCHV(1);}
  int        SetFCHV2(double hv){return SetFCHV(2,hv);}
  double     GetFCHV2(){return GetFCHV(2);}
  double     GetADCParticle(int t,int l);
  int        SetADCParticle(int t,int l,double value);
  double     GetSCIFParticle(int t,int l,int xy,int pos);
  int        SetSCIFParticle(int t,int l,int xy,int pos,double value);
  double     GetFCParticle(int detector,int ch);   // detector: 1 or 2
  int        SetFCParticle(int detector,int ch, double value);
  double     GetCalParticle(int t, int l){return GetADCParticle(t,l);}
  int        SetCalParticle(int t, int l, double value){return SetADCParticle(t,l,value);} 
  double     GetScifiParticle(int t,int l,int xy,int pos){return GetSCIFParticle(t,l,xy,pos);}
  int        SetScifiParticle(int t,int l,int xy,int pos,double value){return SetSCIFParticle(t,l,xy,pos,value);}
  double     GetSiliconParticle(int il,int ixy,int istrip);
  int        SetSiliconParticle(int il,int ixy,int istrip,double value);
  int        SetSiliconParticle(double value); // Set a value to all strip.
  
  int        ReadFile(char* file, char option[] = "ADC SCIF FC");
  int        ReadType1(char* option);
  int        WriteFile(int t,char* file, char option[] = "ADC SCIF FC");
  int        WriteType1(char* option);

  int        Copy(ConParticleDefine* obj);
  int        PrintStatus();

 public:
  //constants
  static const int    CONPARTICLEDEFINE_OK  = 0;
  static const int    CONPARTICLEDEFINE_ERROR = -1;
  static const char*  CONPARTICLEDEFINE_FORMAT; 
  static const double DEFALUT_DEF_SILICON;

  ClassDef(ConParticleDefine,1);   // Control the table of partcile definitions for Arm1 and Arm2 
};


#endif
