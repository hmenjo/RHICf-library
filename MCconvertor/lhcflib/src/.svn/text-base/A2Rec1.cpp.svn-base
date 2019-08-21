#ifndef __A2REC1_CPP__
#define __A2REC1_CPP__

#include "A2Rec1.h"

//----------------------------------------------------------------------
//   Arm2 Reconstruction parameters with format 1 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Rec1);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

// -------------------------------------------------------------------
// -----                     DEFINITIONS                         -----
// -------------------------------------------------------------------

#define  REC_FORMAT     2001
#define  SIZE_EVINFO              4
#define   EVINFO_EVENTQUALITY     0
#define   EVINFO_BEAMCOLCONF      1
#define   EVINFO_BUNCHNUMBER(i)   (2+i) 
#define  SIZE_FLAGS               3
#define   FLAGS_FLAGS(i)          (0+i)
#define  SIZE_REC                 12
#define   REC_ENERGY(i,j)         (0+2*i+j)
#define   REC_SUMDE(i)            (4 +i)
#define   REC_SUMDE2(i)           (6 +i)
#define   REC_LEAKAGEOUT(i)       (8 +i)
#define   REC_ESCALEFACTOR(i)     (10+i)
#define  SIZE_CAL                 0
//#define   CAL_CAL(i,l)            (16*i+l)
#define  SIZE_POS                 86
#define   POS_RES_HITPOS(i,j)     ( 0+i*2+j)
#define   POS_RES_NHITS(i)        ( 4+i)
#define   POS_NHITS(a,b,c)        ( 6+8*a+2*b+c)
#define   POS_HITPOS(a,b,c)       (22+8*a+2*b+c)
#define   POS_PEAKSTRIP(a,b,c)    (38+8*a+2*b+c)
#define   POS_DEATPEAK(a,b,c)     (54+8*a+2*b+c)
#define   POS_SISATUFLAG(a,b,c)   (70+8*a+2*b+c)
#define  SIZE_PID                 6
#define   PID_RES(i)              (0+i)
#define   PID_L20(i)              (2+i)
#define   PID_L90(i)              (4+i)
#define  SIZE_TDC                 0
#define  SIZE_COUNTER             0 

// -------------------------------------------------------------------
// -----             CONSTRUCTOR/DESTORACTOR                     -----
// -------------------------------------------------------------------
A2Rec1::A2Rec1() : Rec0() {
  resize();
}

A2Rec1::A2Rec1(char* name, char *title) : Rec0(name,title){
  resize();
}

A2Rec1::~A2Rec1(){;}

int  A2Rec1::resize(){
  format = REC_FORMAT;
  Rec0::resize(evinfo,  SIZE_EVINFO);
  Rec0::resize(flags,   SIZE_FLAGS);
  Rec0::resize(rec,     SIZE_REC);
  Rec0::resize(cal,     SIZE_CAL);
  Rec0::resize(pos,     SIZE_POS);
  Rec0::resize(pid,     SIZE_PID);
  Rec0::resize(tdc,     SIZE_TDC);
  Rec0::resize(counter, SIZE_COUNTER);
  clear();
  return OK;
}

void A2Rec1::Show(){
  // -----  Print Header  ------
  Rec0::Show();

  // ----- Print Recommended result ----- 
  A2Phys phys;
  cout << "--------------- RECOMMEDED RESULTS --------------" << endl;
  FillToPhys(&phys);
  phys.Show();
  
  // --------- Print Additional Informations ---------
  cout << "----------- RECONSTRUCTED PARAMTERS -------------"  << endl;
  // Beam info
  cout << " Beam Config : " << setw(3) << GetBeamColConf() << "      "
       << "BunchNumber : " 
       << setw(6) << GetBunchNumber(0) << setw(6) << GetBunchNumber(0) 
       << endl;
  // Sum dE's
  cout.setf(ios::fixed); 
  cout << "              "
       << setw(11) << "  --- 25mm ---"
       << setw(11) << "  --- 32mm ---" 
       << endl;
  cout << " SumdE(0-15)  : " 
       << setw(11) << setprecision(1) <<  GetSumdE(0) 
       << setw(11) << setprecision(1) <<  GetSumdE(1)
       << endl;
  cout << " SumdE(1-12)  : " 
       << setw(11) << setprecision(1) <<  GetSumdE2(0) 
       << setw(11) << setprecision(1) <<  GetSumdE2(1)
       << endl;
  // Pid
  cout << "  L20          : "
       << setw(11) << setprecision(1) << GetL20(0) 
       << setw(11) << setprecision(1) << GetL20(1) << endl;
  cout << "  L90          : "
       << setw(11) << setprecision(1) << GetL90(0)
       << setw(11) << setprecision(1) << GetL90(1) << endl;  
  // Hits
  cout << "HITS      -- 25mm-X --   -- 25mm-Y --   -- 32mm-X  --  -- 32mm-Y --" << endl;
  for(int il=0;il<4;il++){
    cout << "Layer" << il << "   ";
    for(int it=0;it<2;it++){
      for(int ixy=0;ixy<2;ixy++){
	cout << setw(2) << GetNumberOfHits(it,il,ixy) 
	     << setw(5) << setprecision(1) << GetHitPosition(it,il,ixy)
	     << setw(6) << setprecision(1) << GetPeakStrip(it,il,ixy) ;
	cout << "  " ;
      }
      cout << " ";
    }
    cout << endl;
  }
}

// -------------------------------------------------------------------
// -----                INTERFACE FUNCTIONS                      -----
// -------------------------------------------------------------------
// ================== Event Information =================  
// From evinfo
// Event Quality flag 
int    A2Rec1::GetEventQuality(){return evinfo[EVINFO_EVENTQUALITY];}
void   A2Rec1::SetEventQuality(int d){evinfo[EVINFO_EVENTQUALITY] = d;}
// Beam Colliding flag
int    A2Rec1::GetBeamColConf(){ return evinfo[EVINFO_BEAMCOLCONF];}             
void   A2Rec1::SetBeamColConf(int d){evinfo[EVINFO_BEAMCOLCONF] = d;}
// Bunch Number (beam 1 or 2)
int    A2Rec1::GetBunchNumber(int ib){ return evinfo[EVINFO_BUNCHNUMBER(ib)];}
void   A2Rec1::SetBunchNumber(int ib,int d){evinfo[EVINFO_BUNCHNUMBER(ib)] = d;}
// =====================  Flags =========================
// From flags    
// Flag from GPIO's (i-th)
unsigned int A2Rec1::GetFlags(int i){ return flags[FLAGS_FLAGS(i)];}     
void         A2Rec1::SetFlags(int i, unsigned int d){flags[FLAGS_FLAGS(i)] =d;} 
// =============== Reconstruction ======================
// From rec
// Recommended reconstructed energy (tower)
double A2Rec1::GetResultEnergy(int it){
  if(GetResultPID(it)==A2Phys::HADRON){
    return GetResultEnergy(it,A2Phys::HADRON);
  }
  else{
    return GetResultEnergy(it,A2Phys::ELEMAG);
  }
}
double A2Rec1::GetResultEnergy(int it,int pid){return rec[REC_ENERGY(it,pid)];}
void   A2Rec1::SetResultEnergy(int it,int pid,double d){rec[REC_ENERGY(it,pid)]=d;}
// Sum dE(layer=0-15) (tower)
double A2Rec1::GetSumdE(int it){ return rec[REC_SUMDE(it)];}             
void   A2Rec1::SetSumdE(int it,double d){rec[REC_SUMDE(it)] = d;}
// Sum dE(layer=1-12) (tower)
double A2Rec1::GetSumdE2(int it){ return rec[REC_SUMDE2(it)];}             
void   A2Rec1::SetSumdE2(int it,double d){rec[REC_SUMDE2(it)] = d;} 
// Shower Leakage parameter (tower)
double A2Rec1::GetLeakageOut(int it){ return rec[REC_LEAKAGEOUT(it)];}        
void   A2Rec1::SetLeakageOut(int it,double d){rec[REC_LEAKAGEOUT(it)] = d;}
double A2Rec1::GetEnergyScaleFactor(int it){return rec[REC_ESCALEFACTOR(it)];}
void   A2Rec1::SetEnergyScaleFactor(int it,double d){rec[REC_ESCALEFACTOR(it)] = d;}
// ================= Calorimer =========================
// From cal 
// ================== Position ========================
// From pos
// Recommended hit position results 
double A2Rec1::GetResultHitPosition(int it, int ixy){return pos[POS_RES_HITPOS(it,ixy)];}    
void   A2Rec1::SetResultHitPosition(int it, int ixy,double d){pos[POS_RES_HITPOS(it,ixy)]=d;}
// Recommended number of hit results (tower)
int    A2Rec1::GetResultNumberOfHits(int it){return (int)pos[POS_RES_NHITS(it)];}   
void   A2Rec1::SetResultNumberOfHits(int it, int d){pos[POS_RES_NHITS(it)]=1.E-10+d;} 
// Number of Hits in the tower (tower,xy,layer)
int    A2Rec1::GetNumberOfHits(int it,int il,int ixy){ return (int)pos[POS_NHITS(it,il,ixy)];}
void   A2Rec1::SetNumberOfHits(int it,int il,int ixy, int d){pos[POS_NHITS(it,il,ixy)] = 0.00001+d;} 
// Hit Position in each layer (tower,layer,xy)
double A2Rec1::GetHitPosition(int it,int il, int ixy){ return pos[POS_HITPOS(it,il,ixy)];}    
void   A2Rec1::SetHitPosition(int it,int il, int ixy, double d){pos[POS_HITPOS(it,il,ixy)] = d;} 
// Strip number with maximum dE (tower,xy,layer)
double A2Rec1::GetPeakStrip(int it,int il,int ixy){ return pos[POS_PEAKSTRIP(it,il,ixy)];}   
void   A2Rec1::SetPeakStrip(int it,int il,int ixy, double d){pos[POS_PEAKSTRIP(it,il,ixy)] = d;} 
// dE at peak (tower,xy,layer)
double A2Rec1::GetdEAtPeak(int it,int il,int ixy){ return pos[POS_DEATPEAK(it,il,ixy)];}   
void   A2Rec1::SetdEAtPeak(int it,int il,int ixy,double d){pos[POS_DEATPEAK(it,il,ixy)]=d;}
 // Saturation flag of silicon middle sample 
int    A2Rec1::GetSiSatuFlag(int it,int il,int ixy){ return (int)pos[POS_SISATUFLAG(it,il,ixy)];}   
void   A2Rec1::SetSiSatuFlag(int it,int il,int ixy,int d){pos[POS_SISATUFLAG(it,il,ixy)]=0.000001+d;}
// ===================== PID =========================
// From pid
// PID result (tower) 
int    A2Rec1::GetResultPID(int it){return (int)pid[PID_RES(it)];}
void   A2Rec1::SetResultPID(int it,int d){pid[PID_RES(it)]=1.E-10+d;}   
// L20% (tower)
double A2Rec1::GetL20(int it){ return pid[PID_L20(it)];}                  
void   A2Rec1::SetL20(int it,double d){pid[PID_L20(it)]=d;}
// L90% (tower) 
double A2Rec1::GetL90(int it){ return pid[PID_L90(it)];}                   
void   A2Rec1::SetL90(int it,double d){pid[PID_L90(it)]=d;} 

#endif
