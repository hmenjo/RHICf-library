#ifndef __RHICFREC1_CPP__
#define __RHICFREC1_CPP__

#include "RHICfRec1.h"

//----------------------------------------------------------------------
//   Arm2 Reconstruction parameters with format 1 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(RHICfRec1);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

// -------------------------------------------------------------------
// -----                     DEFINITIONS                         -----
// -------------------------------------------------------------------

#define  REC_FORMAT     1001
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
//#define  SIZE_POS_INIT           136
#define   SIZE_POS_INIT           396
#define   POS_RES_HITPOS(i,j)     ( 0+i*2+j)                      // i:tower, j:view
#define   POS_RES_NHITS(i)        ( 4+i)                          // i:tower
#define   POS_NHITS(a,b,c)        ( 6+8*a+2*b+c)                  // a:tower, b:layer,c:xy 
#define   POS_HITPOS(a,b,c)       (22+8*a+2*b+c)                  // a:tower, b:layer,c:xy
#define   POS_PEAKPOS(a,b,c)      (38+8*a+2*b+c)                  // a:tower, b:layer,c:xy
#define   POS_DEATPEAK(a,b,c)     (54+8*a+2*b+c)                  // a:tower, b:layer,c:xy
//#define   POS_SISATUFLAG(a,b,c)   (70+8*a+2*b+c)                // no use from 70-85
// For MH
#define   SIZE_POS_BASE           86
#define   POS_MH_NTOWER            2 
#define   POS_MH_NLAYER            4
#define   POS_MH_NVIEW             2
#define   POS_MH_NPARPERHIT        5
#define   POS_MH_NHIT_TOWER(a)     ( SIZE_POS_BASE+0+a )              // a:tower
#define   POS_MH_BKGPAR(a,b,c,d)   ( SIZE_POS_BASE+2+a*16+b*4+c*2+d)  // a:tower,b:layer,c:xy,d:ipar 
#define   POS_MH_NHITS(a,b,c)      ( SIZE_POS_BASE+34+a*8+b*2+c)      // a:tower,b:layer,c:xy 
#define   POS_MH_PAR_FIRST         ( SIZE_POS_BASE+50)
#define  SIZE_PID                 6
#define   PID_RES(i)              (0+i)
#define   PID_L20(i)              (2+i)
#define   PID_L90(i)              (4+i)
#define  SIZE_TDC                 0
#define  SIZE_COUNTER             0 

// *** Newly developed for RHICf *** //

#define   POS_MAXLAY(a)           (232+2*a)
#define   POS_MAXLAY2(b)           (234+2*b)
#define   POS_MHPOS(a,b,c,d)      (236+16*a+4*b+2*c+d)                  // a:tower, b:layer, c:xy, d:multi
#define   POS_MHYHIS(a,b,c,d)     (268+16*a+4*b+2*c+d)
#define   POS_MHYFUNC(a,b,c,d)    (300+16*a+4*b+2*c+d)
#define   POS_MHINTEGRAL(a,b,c,d) (332+16*a+4*b+2*c+d)
#define   POS_CHISQUARE(a,b,c,d)  (364+16*a+4*b+2*c+d)

// -------------------------------------------------------------------
// -----             CONSTRUCTOR/DESTORACTOR                     -----
// -------------------------------------------------------------------
RHICfRec1::RHICfRec1() : RHICfRec0() {
  resize();
}

RHICfRec1::RHICfRec1(char* name, char *title) : RHICfRec0(name,title){
  resize();
}

RHICfRec1::~RHICfRec1(){;}

int  RHICfRec1::resize(){
  format = REC_FORMAT;
  RHICfRec0::resize(evinfo,  SIZE_EVINFO);
  RHICfRec0::resize(flags,   SIZE_FLAGS);
  RHICfRec0::resize(rec,     SIZE_REC);
  RHICfRec0::resize(cal,     SIZE_CAL);
  RHICfRec0::resize(pos,     SIZE_POS_INIT);
  RHICfRec0::resize(pid,     SIZE_PID);
  RHICfRec0::resize(tdc,     SIZE_TDC);
  RHICfRec0::resize(counter, SIZE_COUNTER);  
  clear();
  return OK;
}

void RHICfRec1::Show(){
  // -----  Print Header ------
  RHICfRec0::Show();
  
  // ----- Print Recommended result -----
  RHICfPhys phys;
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
       << setw(11) << "  --- 20mm ---"
       << setw(11) << "  --- 40mm ---" 
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
  cout << "HITS      -- 20mm-X --   -- 20mm-Y --   -- 40mm-X  --  -- 40mm-Y --" << endl;
  for(int il=0;il<4;il++){
    cout << "Layer" << il << "   ";
    for(int it=0;it<2;it++){
      for(int ixy=0;ixy<2;ixy++){
	cout << setw(2) << GetNumberOfHits(it,il,ixy) 
	     << setw(5) << setprecision(1) << GetHitPosition(it,il,ixy)
	     << setw(6) << setprecision(1) << GetPeakPosition(it,il,ixy) ;
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
int    RHICfRec1::GetEventQuality(){return evinfo[EVINFO_EVENTQUALITY];}
void   RHICfRec1::SetEventQuality(int d){evinfo[EVINFO_EVENTQUALITY] = d;}
// Beam Colliding flag
int    RHICfRec1::GetBeamColConf(){ return evinfo[EVINFO_BEAMCOLCONF];}             
void   RHICfRec1::SetBeamColConf(int d){evinfo[EVINFO_BEAMCOLCONF] = d;}
// Bunch Number (beam 1 or 2)
int    RHICfRec1::GetBunchNumber(int ib){ return evinfo[EVINFO_BUNCHNUMBER(ib)];}
void   RHICfRec1::SetBunchNumber(int ib,int d){evinfo[EVINFO_BUNCHNUMBER(ib)] = d;}
// =====================  Flags =========================
// From flags    
// Flag from GPIO's (i-th)
unsigned int RHICfRec1::GetFlags(int i){ return flags[FLAGS_FLAGS(i)];}     
void         RHICfRec1::SetFlags(int i, unsigned int d){flags[FLAGS_FLAGS(i)] =d;}

// *** Newly developed for RHICf *** //
bool RHICfRec1::IsShowerTrig(){ 

	if((flags[FLAGS_FLAGS(0)] & 0x010)) return true;  
	else return false;
}
bool RHICfRec1::IsPi0Trig(){ 

	if((flags[FLAGS_FLAGS(0)] & 0x080)) return true;
	else return false;
}
bool RHICfRec1::IsHighEMTrig(){ 
	if((flags[FLAGS_FLAGS(0)] & 0x200)) return true;
	else return false;  
}

// =============== Reconstruction ======================
// From rec
// Recommended reconstructed energy (tower)
double RHICfRec1::GetResultEnergy(int it){
  if(GetResultPID(it)==RHICfPhys::HADRON){
    return GetResultEnergy(it,RHICfPhys::HADRON);
  }
  else{
    return GetResultEnergy(it,RHICfPhys::ELEMAG);
  }
}
double RHICfRec1::GetResultEnergy(int it,int pid){return rec[REC_ENERGY(it,pid)];}
void   RHICfRec1::SetResultEnergy(int it,int pid,double d){rec[REC_ENERGY(it,pid)]=d;}
// Sum dE(layer=0-15) (tower)
double RHICfRec1::GetSumdE(int it){ return rec[REC_SUMDE(it)];}             
void   RHICfRec1::SetSumdE(int it,double d){rec[REC_SUMDE(it)] = d;}
// Sum dE(layer=1-12) (tower)
double RHICfRec1::GetSumdE2(int it){ return rec[REC_SUMDE2(it)];}             
void   RHICfRec1::SetSumdE2(int it,double d){rec[REC_SUMDE2(it)] = d;} 
// Shower Leakage parameter (tower)
double RHICfRec1::GetLeakageOut(int it){ return rec[REC_LEAKAGEOUT(it)];}        
void   RHICfRec1::SetLeakageOut(int it,double d){rec[REC_LEAKAGEOUT(it)] = d;}
double RHICfRec1::GetEnergyScaleFactor(int it){return rec[REC_ESCALEFACTOR(it)];}
void   RHICfRec1::SetEnergyScaleFactor(int it,double d){rec[REC_ESCALEFACTOR(it)] = d;}
// ================= Calorimer =========================
// From cal 
// ================== Position ========================
// From pos
// Recommended hit position results 
double RHICfRec1::GetResultHitPosition(int it, int ixy){return pos[POS_RES_HITPOS(it,ixy)];}    
void   RHICfRec1::SetResultHitPosition(int it, int ixy,double d){pos[POS_RES_HITPOS(it,ixy)]=d;}
// Recommended number of hit results (tower)
int    RHICfRec1::GetResultNumberOfHits(int it){return (int)pos[POS_RES_NHITS(it)];}   
void   RHICfRec1::SetResultNumberOfHits(int it, int d){pos[POS_RES_NHITS(it)]=1.E-10+d;} 
// Number of Hits in the tower (tower,xy,layer)
int    RHICfRec1::GetNumberOfHits(int it,int il,int ixy){ return (int)pos[POS_NHITS(it,il,ixy)];}
void   RHICfRec1::SetNumberOfHits(int it,int il,int ixy, int d){pos[POS_NHITS(it,il,ixy)] = 0.00001+d;} 
// Hit Position in each layer (tower,layer,xy)
double RHICfRec1::GetHitPosition(int it,int il, int ixy){ return pos[POS_HITPOS(it,il,ixy)];}    
void   RHICfRec1::SetHitPosition(int it,int il, int ixy, double d){pos[POS_HITPOS(it,il,ixy)] = d;} 
// Strip number with maximum dE (tower,xy,layer)
double RHICfRec1::GetPeakPosition(int it,int il,int ixy){ return pos[POS_PEAKPOS(it,il,ixy)];}   
void   RHICfRec1::SetPeakPosition(int it,int il,int ixy, double d){pos[POS_PEAKPOS(it,il,ixy)] = d;} 
// dE at peak (tower,xy,layer)
double RHICfRec1::GetdEAtPeak(int it,int il,int ixy){ return pos[POS_DEATPEAK(it,il,ixy)];}   
void   RHICfRec1::SetdEAtPeak(int it,int il,int ixy,double d){pos[POS_DEATPEAK(it,il,ixy)]=d;}
 // Saturation flag of silicon middle sample (Only for Arm2)
//int    RHICfRec1::GetSiSatuFlag(int it,int il,int ixy){ return (int)pos[POS_SISATUFLAG(it,il,ixy)];}   
//void   RHICfRec1::SetSiSatuFlag(int it,int il,int ixy,int d){pos[POS_SISATUFLAG(it,il,ixy)]=0.000001+d;}
// ===================== PID =========================
// From pid
// PID result (tower) 
int    RHICfRec1::GetResultPID(int it){return (int)pid[PID_RES(it)];}
void   RHICfRec1::SetResultPID(int it,int d){pid[PID_RES(it)]=1.E-10+d;}   
// L20% (tower)
double RHICfRec1::GetL20(int it){ return pid[PID_L20(it)];}                  
void   RHICfRec1::SetL20(int it,double d){pid[PID_L20(it)]=d;}
// L90% (tower) 
double RHICfRec1::GetL90(int it){ return pid[PID_L90(it)];}                   
void   RHICfRec1::SetL90(int it,double d){pid[PID_L90(it)]=d;} 
// ===================== Multi Hit ====================
// GetMHBkgPar ---------------------------------------------
double RHICfRec1::GetMHBkgPar(int tower, int layer, int xy, int ipar){ 
  // Get base line fitting results with a linear function.
  // ipar = 0 : constant
  // ipar = 1 : gradiant
  return pos[POS_MH_BKGPAR(tower,layer,xy,ipar)];
 }

// SetMHBkgPar ---------------------------------------------
void   RHICfRec1::SetMHBkgPar(int tower, int layer, int xy, int ipar, double val){
  // Set base line fitting results with a linear function.
  // ipar = 0 : constant
  // ipar = 1 : gradient 
  pos[POS_MH_BKGPAR(tower,layer,xy,ipar)] = val;
}

// GetMHNhits ------------------------------------------------
int    RHICfRec1::GetMHNhits(int tower, int layer, int xy){
  // Return Number of hits in the layer
  return (int)pos[POS_MH_NHITS(tower,layer,xy)];
}

// GetMHNhits ------------------------------------------------
void   RHICfRec1::SetMHNhits(int tower, int layer, int xy, int nhits){
  // Set Number of Hits in the plane. 
  // It is better not to use this function.
  // To increase/decrease the number of hits, use AddMHHit or EraseMHHit
  pos[POS_MH_NHITS(tower, layer,xy)]=nhits+1.E-9;
}

// GetMHParPos ------------------------------------------------
int    RHICfRec1::GetMHParPos(int tower, int layer,int xy, int ihits, int ipar){
  // Internal Function : return position of the parameter in the array
  int pos=POS_MH_PAR_FIRST;
  for(int it=0;it<POS_MH_NTOWER;it++){
    for(int il=0;il<POS_MH_NLAYER;il++){
      for(int iv=0;iv<POS_MH_NVIEW;iv++){
	if(it==tower && il==layer && iv==xy){
	  return pos+POS_MH_NPARPERHIT*ihits+ipar;
	}
	else{
	  pos += POS_MH_NPARPERHIT*GetMHNhits(it,il,iv);
	}
      }
    }
  }
  // Error;
  return POS_MH_PAR_FIRST+ipar;
}

// GetMHPar --------------------------------------------------
double RHICfRec1::GetMHPar(int tower, int layer,int xy, int ihit, int ipar){
  // Get Multi-Hit parameter
  //  ipar = 0 :  Scale
  //  ipar = 1 :  Position by strip number
  //  ipar = 2 :  Width Parameter 1
  //  ipar = 3 :  Width Parameter 2  
  //  ipar = 4 :  Discared Flag 
  return pos[GetMHParPos(tower,layer,xy,ihit,ipar)];
}

void   RHICfRec1::SetMHPar(int tower, int layer,int xy, int ihit, int ipar,double val){
  // For modification of Multi-Hit parameter.
  //  ipar = 0 :  Scale
  //  ipar = 1 :  Position by strip number
  //  ipar = 2 :  Width Parameter 1
  //  ipar = 3 :  Width Parameter 2  
  //  ipar = 4 :  Discared Flag 
  pos[GetMHParPos(tower,layer,xy,ihit,ipar)]=val;
}

// GetMHDiscardedFlag ---------------------------------------
bool   RHICfRec1::GetMHDiscardedFlag(int tower, int layer,int xy, int ihit){
  // Get Discarded Flag of this Hit
  // If return true, this hit results is meaningless.
  // Actually this is contained as the 5th parameter in the hit.
  // This function gives just return value converted to the "bool" format.
  return GetMHPar(tower,layer,xy,ihit,4) > 0.999 ? true : false; 
}

// AddMHHit ------------------------------------------------
int    RHICfRec1::AddMHHit(int tower, int layer, int xy, double *par){
  // Add hit parmeters in the array
  // size of par must be equal to POS_MH_NPARPERHIT
  
  int nhits = GetMHNhits(tower, layer,xy);

  // Insert parameters
  for(int ipar=0;ipar<POS_MH_NPARPERHIT;ipar++){
    pos.insert( pos.begin()+GetMHParPos(tower,layer,xy,nhits,ipar), 
		par[ipar] );
  }
  // Increment number of hits in the layer
  SetMHNhits(tower,layer,xy, nhits+1);
  return OK;
}

// EraseMHHit ---------------------------------------------
int    RHICfRec1::EraseMHHit(int tower,int layer, int xy, int ihit){
  // Erase the hit from the array 
  int nhits = GetMHNhits(tower,layer,xy);
  pos.erase( pos.begin()+GetMHParPos(tower,layer,xy,ihit,0), 
	     pos.begin()+GetMHParPos(tower,layer,xy,ihit,0)+POS_MH_NPARPERHIT);
  SetMHNhits(tower,layer,xy, nhits-1);
  return OK;
}


int     RHICfRec1::GetMHNumberOfHits(int tower){
  // Number of hits in the tower (except discarded peaks)
  return pos[POS_MH_NHIT_TOWER(tower)];
}
void    RHICfRec1::SetMHNumberOfHits(int tower, int val){
  pos[POS_MH_NHIT_TOWER(tower)] = val;
}

// *** Newly developed for RHICf *** //

int RHICfRec1::GetMaxBarLayer(int it) { return pos[POS_MAXLAY(it)]; }
void RHICfRec1::SetMaxBarLayer(int it, int d) { pos[POS_MAXLAY(it)] = d; }
int RHICfRec1::GetMaxBarLayer2(int it) { return pos[POS_MAXLAY2(it)]; }
void RHICfRec1::SetMaxBarLayer2(int it, int d) { pos[POS_MAXLAY2(it)] = d; }

double RHICfRec1::GetMHPosition(int it, int il, int ixy, int imu) { return pos[POS_MHPOS(it,il,ixy,imu)]; }
void RHICfRec1::SetMHPosition(int it, int il, int ixy, int imu, double d) { pos[POS_MHPOS(it,il,ixy,imu)] = d; }
double RHICfRec1::GetMHPeakRaw(int it, int il, int ixy, int imu) { return pos[POS_MHYHIS(it,il,ixy,imu)]; }
void RHICfRec1::SetMHPeakRaw(int it, int il, int ixy, int imu, double d) { pos[POS_MHYHIS(it,il,ixy,imu)] = d; }
double RHICfRec1::GetMHPeakEstimated(int it, int il, int ixy, int imu) { return pos[POS_MHYFUNC(it,il,ixy,imu)]; }
void RHICfRec1::SetMHPeakEstimated(int it, int il, int ixy, int imu, double d) { pos[POS_MHYFUNC(it,il,ixy,imu)] = d; }
double RHICfRec1::GetMHIntegral(int it, int il, int ixy, int imu) { return pos[POS_MHINTEGRAL(it,il,ixy,imu)]; }
void RHICfRec1::SetMHIntegral(int it, int il, int ixy, int imu, double d) { pos[POS_MHINTEGRAL(it,il,ixy,imu)] = d; }

double RHICfRec1::GetChiSquare(int it, int il, int ixy, int imu) { 

	//cout << "dict" << pos[POS_CHISQUARE(it,il,ixy,imu)] << endl;
	return pos[POS_CHISQUARE(it,il,ixy,imu)]; 
}
void RHICfRec1::SetChiSquare(int it, int il, int ixy, int imu, double d){ pos[POS_CHISQUARE(it,il,ixy,imu)] = d; }

#endif
