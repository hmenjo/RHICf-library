#ifndef __TRANSITIONFIT_CPP__
#define __TRANSITIONFIT_CPP__

#include "TransitionFit.h"

//----------------------------------------------------------------------
//
//  For fitting transition shapes by a function.
//
//  Fit Function:
//   2.*[0]*(pow([2]*(x-[3]),[1]-1.)*[2]*exp(-1.*[2]*(x-[3])))/TMath::Gamma([1])
//  Parameters:
//   [0] : scale factor, ~ sum of dE
//   [1] : alpha parameter, mainly affect the shape on rising part
//   [2] : beta parameter, mainly affect the shape on falling part
//   [3] : offset of the shower starting point[r.l.]
//  Comments:
//   (alpha-1)/beta equal to the position of shower max[rl].
//   alpha/beta equal to the center of dE
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically 
//              by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(TransitionFit);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstring>
#include <TMath.h>
using namespace std;

int TransitionFit::ncall=0;

TransitionFit::TransitionFit(){
  sprintf(name,"TrainsitionFit_%d",ncall);
  sprintf(title,"TransitionFit %d",ncall);
  Initialize();
  ncall++;
}

TransitionFit::TransitionFit(char tname[],char ttitle[]){
  strcpy(name,tname);
  strcpy(title,ttitle);
  Initialize();
  ncall++;
}

double TransitionFit::FittingFunction(double* v, double* p){
  double x = v[0];
  if(x-p[3]<0.){
    return 0;
  }
  else{
    return 2.*p[0]*(pow(p[2]*(x-p[3]),p[1]-1.)*p[2]*exp(-1.*p[2]*(x-p[3])))/TMath::Gamma(p[1]);
  }
}

void TransitionFit::Initialize(){
  char dirname[256];
  char dirtitle[256];
  char function[256];
  sprintf(dirname,"dir_%s",name);
  strcpy(dirtitle,title);
  strcpy(function,
	 "2.*[0]*(pow([2]*(x-[3]),[1]-1.)*[2]*exp(-1.*[2]*(x-[3])))/TMath::Gamma([1])");
  
  TDirectory *org_dir = gDirectory;
  dir = new TDirectory(name,title);
  dir->cd();
  g[0] = new TGraphErrors();
  g[1] = new TGraphErrors();
  g[0]->Set(16);
  g[1]->Set(16);
  
  //f[0] = new TF1("f0",function,0,45);
  //f[1] = new TF1("f1",function,0,45);
  f[0] = new TF1("f0",this,&TransitionFit::FittingFunction,0,45,4,"TransitionFit","FittingFunction");
  f[1] = new TF1("f1",this,&TransitionFit::FittingFunction,0,45,4,"TransitionFit","FittingFunction");
  
  org_dir->cd();
  
  for(int i=0;i<16;i++){
    if(i<11){ depth[i] = 1.+2.*(i+1);}
    else    { depth[i] = 1.+2.*(i+1)+2.*(i-10);}
    g[0]->SetPoint(i,depth[i],0.);
    g[1]->SetPoint(i,depth[i],0.); 
  }  

  pede[0] = 0.;
  pede[1] = 0.; 

  return ;
}

void TransitionFit::FillToGraph(int tower,A1Cal2* cal){
  int ndata=0;
  double dE,error;
  for(int i=0;i<16;i++){
    dE = cal->cal[tower][i];
    if(dE>1){error = sqrt(dE+pede[tower]*pede[tower]);}
    else{error = sqrt(1+pede[tower]*pede[tower]);}
    g[tower]->SetPoint(ndata,depth[i],dE);
    g[tower]->SetPointError(i,0,error);
    ndata++;
  }
  return ;
}

void TransitionFit::FillToGraph(int tower,A2Cal2* cal){ 
  int ndata=0;
  double dE,error;
  for(int i=0;i<16;i++){
    dE = cal->cal[tower][i];  
    if(dE>1){error = sqrt(dE+pede[tower]*pede[tower]);}
    else{error = sqrt(1+pede[tower]*pede[tower]);} 
    g[tower]->SetPoint(ndata,depth[i],dE);
    g[tower]->SetPointError(i,0,error);
    ndata++;
  }
  return ;
}

void TransitionFit::FillToGraphMod(int tower,A2Cal2* cal){ 
  int ndata=0;
  double dE,error;
  for(int i=0;i<16;i++){
    dE = cal->cal[tower][i];  
    if(dE>1){error = sqrt(dE+pede[tower]*pede[tower]);}
    else{error = sqrt(1+pede[tower]*pede[tower]);}    
    if(i==5) {continue;} 
    // dE(layer=5) is not taken into account 
    // because it doesn't lie on the smooth curve due to the gap of silicon layer. 
    g[tower]->SetPoint(ndata,depth[i],dE);
    g[tower]->SetPointError(i,0,error);
    ndata++;
  }
  return ;
}

int TransitionFit::Fit(int tower){
  double a,b,center;
  double sum,tmp,x,y;
  sum = 0.;
  tmp = 0.;
  for(int i=0;i<g[tower]->GetN();i++){
    g[tower]->GetPoint(i,x,y);
    tmp += x*y;
    sum += y;
  }
  center = tmp/sum;
  a = 8.;
  b = a/center;
  
  if(sum>pede[tower]*16.){
    SetParameter(tower,0,sum);
    SetParameter(tower,1,a);
    SetParameter(tower,2,b);
    SetParameter(tower,3,0.1);
    f[tower]->SetParLimits(0,sum*0.5,sum*1.5);
    f[tower]->SetParLimits(1,1,20);
    f[tower]->SetParLimits(2,0.05,1.0);
    f[tower]->SetParLimits(3,0.00,2.0); 
  }
  else{
    SetParameter(tower,0,pede[tower]*8.);
    SetParameter(tower,1,6.0);
    SetParameter(tower,2,0.5);
    SetParameter(tower,3,0.1);
    f[tower]->SetParLimits(0,0,pede[tower]*16.*2.);
    f[tower]->SetParLimits(1,1,20);
    f[tower]->SetParLimits(2,0.05,1.0);
    f[tower]->SetParLimits(3,0.00,2.0); 
  }

  g[tower]->Fit(f[tower],"QNR"); 
  return OK;
}

int  TransitionFit::Fit(int tower,A1Cal2 *cal){
  FillToGraph(tower,cal);
  return Fit(tower);
}

int  TransitionFit::Fit(int tower,A2Cal2 *cal){
  FillToGraph(tower,cal);
  return Fit(tower);
}

double TransitionFit::GetParameter(int tower,int iparam){
  return f[tower]->GetParameter(iparam);
}

int TransitionFit::SetParameter(int tower,int iparam,double value){
  f[tower]->SetParameter(iparam,value);
  return OK;
}

int TransitionFit::GetParameters(int tower, double *val){
  // Get all(4) parameters and fill to the array
  f[tower]->GetParameters(val);
  return OK;
}

int TransitionFit::SetParameters(int tower, double *val){
  // Get all(4) parameters from the array.
  f[tower]->SetParameters(val);
  return OK;
}

double TransitionFit::GetParError(int tower,int iparam){
  return f[tower]->GetParError(iparam);
}

void TransitionFit::GetFitRange(int tower,double &min,double &max){
  f[tower]->GetRange(min,max);
}

double TransitionFit::GetFitRangeMax(int tower){
  double min,max;
  GetFitRange(tower,min,max);
  return max;
}

double TransitionFit::GetFitRangeMin(int tower){
  double min,max;
  GetFitRange(tower,min,max);
  return min;
}

int TransitionFit::SetFitRange(int tower,double min,double max){
  f[tower]->SetRange(min,max);
  return OK;
}

int TransitionFit::SetFitRangeLayer(int tower,int min,int max){
  if(min<0 || min>=16 || max<0 || max>=16){return ERROR;}
  return SetFitRange(tower,depth[min]-1,depth[max]+1);
}

int TransitionFit::Subtract(int tower, A1Cal2* cal){
  for(int i=0;i<16;i++){
    cal->cal[tower][i] -= EvalAtLayer(tower,i);
  }
  return OK;
}

int TransitionFit::Subtract(int tower, A2Cal2* cal){
  for(int i=0;i<16;i++){
    cal->cal[tower][i] -= EvalAtLayer(tower,i);
  }
  return OK;
}

#endif
