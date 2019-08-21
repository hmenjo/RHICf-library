#ifndef __A2REC2_CPP__
#define __A2REC2_CPP__

#include "A2Rec2.h"

//----------------------------------------------------------------------
//   Arm2 Reconstruction parameters with format 2
//   This is an extention of A2Rec1 for Multi-Hits 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Rec2);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#include "globaldef.h"

// -------------------------------------------------------------------
// -----                     DEFINITIONS                         -----
// -------------------------------------------------------------------

#define  REC_FORMAT     2002
#define  SIZE_POS_INIT           112
#define   SIZE_POS_A2REC1         86
#define   POS_MH_NLAYER            4
#define   POS_MH_NVIEW             2
#define   POS_MH_NPARPERHIT        5
#define   POS_MH_NHIT_TOWER(a)     ( SIZE_POS_A2REC1+0+a )         // a:tower
#define   POS_MH_BKGPAR(a,b,c)     ( SIZE_POS_A2REC1+2+a*4+b*2+c)  // a:layer.b:xy, c:ipar 
#define   POS_MH_NHITS(a,b)        ( SIZE_POS_A2REC1+18+a*2+b)
#define   POS_MH_PAR_FIRST         ( SIZE_POS_A2REC1+26)


// -------------------------------------------------------------------
// -----             CONSTRUCTOR/DESTORACTOR                     -----
// -------------------------------------------------------------------
A2Rec2::A2Rec2() : A2Rec1() {
  A2Rec2::resize();
}

A2Rec2::A2Rec2(char* name, char *title) : A2Rec1(name,title){
  A2Rec2::resize();
}

A2Rec2::~A2Rec2(){;}

int  A2Rec2::resize(){
  format = REC_FORMAT;
  Rec0::resize(pos,  SIZE_POS_INIT);
  clear();
  return OK;
}

void A2Rec2::Show(){
  A2Rec1::Show();
  cout << " Multi-Hit:" << endl 
       << "   Small  " << setw(3) <<  this->GetMHNumberOfHits(0) << "      "
       << "   Large  " << setw(3) <<  this->GetMHNumberOfHits(1) << endl;
}

// -------------------------------------------------------------------
// -----                INTERFACE FUNCTIONS                      -----
// -------------------------------------------------------------------
// GetMHBkgPar ---------------------------------------------
double A2Rec2::GetMHBkgPar(int layer, int xy, int ipar){ 
  // Get base line fitting results with a linear function.
  // ipar = 0 : constant
  // ipar = 1 : gradiant
  return pos[POS_MH_BKGPAR(layer,xy,ipar)];
 }

// SetMHBkgPar ---------------------------------------------
void   A2Rec2::SetMHBkgPar(int layer, int xy, int ipar, double val){
  // Set base line fitting results with a linear function.
  // ipar = 0 : constant
  // ipar = 1 : gradient 
  pos[POS_MH_BKGPAR(layer,xy,ipar)] = val;
}

// GetMHNhits ------------------------------------------------
int    A2Rec2::GetMHNhits(int layer, int xy){
  // Return Number of hits in the layer
  return (int)pos[POS_MH_NHITS(layer,xy)];
}

// GetMHNhits ------------------------------------------------
void   A2Rec2::SetMHNhits(int layer, int xy, int nhits){
  // Set Number of Hits in the plane. 
  // It is better not to use this function.
  // To increase/decrease the number of hits, use AddMHHit or EraseMHHit
  pos[POS_MH_NHITS(layer,xy)]=nhits+1.E-9;
}

// GetMHParPos ------------------------------------------------
int    A2Rec2::GetMHParPos(int layer,int xy, int ihits, int ipar){
  // Internal Function : return position of the parameter in the array
  int pos=POS_MH_PAR_FIRST;
  for(int il=0;il<POS_MH_NLAYER;il++){
    for(int iv=0;iv<POS_MH_NVIEW;iv++){
      if(il==layer && iv==xy){
	return pos+POS_MH_NPARPERHIT*ihits+ipar;
      }
      else{
	pos += POS_MH_NPARPERHIT*GetMHNhits(il,iv);
      }
    }
  }
  // Error;
  return POS_MH_PAR_FIRST+ipar;
}

// GetMHPar --------------------------------------------------
double A2Rec2::GetMHPar(int layer,int xy, int ihit, int ipar){
  // Get Multi-Hit parameter
  //  ipar = 0 :  Scale
  //  ipar = 1 :  Position by strip number
  //  ipar = 2 :  Width Parameter 1
  //  ipar = 3 :  Width Parameter 2  
  //  ipar = 4 :  Discared Flag 
  return pos[GetMHParPos(layer,xy,ihit,ipar)];
}

void   A2Rec2::SetMHPar(int layer,int xy, int ihit, int ipar,double val){
  // For modification of Multi-Hit parameter.
  //  ipar = 0 :  Scale
  //  ipar = 1 :  Position by strip number
  //  ipar = 2 :  Width Parameter 1
  //  ipar = 3 :  Width Parameter 2  
  //  ipar = 4 :  Discared Flag 
  pos[GetMHParPos(layer,xy,ihit,ipar)]=val;
}

// GetMHDiscardedFlag ---------------------------------------
bool   A2Rec2::GetMHDiscardedFlag(int layer,int xy, int ihit){
  // Get Discarded Flag of this Hit
  // If return true, this hit results is meaningless.
  // Actually this is contained as the 5th parameter in the hit.
  // This function gives just return value converted to the "bool" format.
  return GetMHPar(layer,xy,ihit,4) > 0.999 ? true : false; 
}

// AddMHHit ------------------------------------------------
int    A2Rec2::AddMHHit(int layer, int xy, double *par){
  // Add hit parmeters in the array
  // size of par must be equal to POS_MH_NPARPERHIT
  
  int nhits = GetMHNhits(layer,xy);

  // Insert parameters
  for(int ipar=0;ipar<POS_MH_NPARPERHIT;ipar++){
    pos.insert( pos.begin()+GetMHParPos(layer,xy,nhits,ipar), 
		par[ipar] );
  }
  // Increment number of hits in the layer
  SetMHNhits(layer,xy, nhits+1);
  return OK;
}

// EraseMHHit ---------------------------------------------
int    A2Rec2::EraseMHHit(int layer, int xy, int ihit){
  // Erase the hit from the array 
  int nhits = GetMHNhits(layer,xy);
  pos.erase( pos.begin()+GetMHParPos(layer,xy,ihit,0), 
	     pos.begin()+GetMHParPos(layer,xy,ihit,0)+POS_MH_NPARPERHIT);
  SetMHNhits(layer,xy, nhits-1);
  return OK;
}


int     A2Rec2::GetMHNumberOfHits(int tower){
  // Number of hits in the tower (except discarded peaks)
  return pos[POS_MH_NHIT_TOWER(tower)];
}
void    A2Rec2::SetMHNumberOfHits(int tower, int val){
  pos[POS_MH_NHIT_TOWER(tower)] = val;
}

#endif
