#ifndef __SCIFIINCIDENTPOSITION02_CPP__
#define __SCIFIINCIDENTPOSITION02_CPP__

#include "ScifiIncidentPosition02.h"

//----------------------------------------------------------------------
//
// Be careful to use.
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 09: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ScifiIncidentPosition02);
#endif


#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

const int ScifiIncidentPosition02::SCIFIINCIDENTPOSITION02_OK;
const int ScifiIncidentPosition02::SCIFIINCIDENTPOSITION02_ERROR;

ScifiIncidentPosition02::ScifiIncidentPosition02(){
  Initialize();
}

ScifiIncidentPosition02::ScifiIncidentPosition02(char *file){
  Initialize();
  ReadScifiPisition(file);
}

int ScifiIncidentPosition02::Initialize(){
  Clear();
  scifipos = NULL;
  char name[256];
  char func[]="[2]*([4]*([0]/2.)/pow(((x-[1])**2+[0]),3./2.)+(1-[4])*([3]/2.)/pow(((x-[1])**2+[3]),3./2.))";
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	sprintf(name,"f_scifi_%d_%d_%d",it,il,ixy);
	f[it][il][ixy] = new TF1(name,func);
	f[it][il][ixy]->SetParameter(0,2.);
	f[it][il][ixy]->SetParameter(1,10.6);
	f[it][il][ixy]->SetParameter(2,300.*2);
	f[it][il][ixy]->SetParameter(3,10.);
	f[it][il][ixy]->SetParameter(4,0.8);
	f[it][il][ixy]->SetParLimits(0,0.4,5.);      // width
	f[it][il][ixy]->SetParLimits(1,0.,40.);      // center
	f[it][il][ixy]->SetParLimits(2,100.,1200.);  // Scale
	f[it][il][ixy]->SetParLimits(3,5,40);        // width
	f[it][il][ixy]->SetParLimits(4,0.15,1.0);    // ratio 
	f[it][il][ixy]->SetLineStyle(2);
	f[it][il][ixy]->SetLineColor(4);
	if(it==0){
	  f[it][il][ixy]->SetRange(-1,21);
	}
	else{
	  f[it][il][ixy]->SetRange(-1,41);
	}
	pede[it][il][ixy] = 0.0;

	ge[it][il][ixy] = new TGraphErrors(40);
	ge[it][il][ixy]->SetLineStyle(1);
	ge[it][il][ixy]->SetMarkerStyle(7);	
      }
    }
  }
 
  return SCIFIINCIDENTPOSITION02_OK;
}

int ScifiIncidentPosition02::Clear(){
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
        pos[it][il][ixy]    = -10.0;
	for(int ip=0;ip<6;ip++){
	  qparam[it][il][ixy][ip] = -10;
	}
      }
    }
  }
  return SCIFIINCIDENTPOSITION02_OK;
}

int ScifiIncidentPosition02::ReadScifiPisition(char *file){
  if(scifipos==0){
    scifipos = new ConScifiPosition();
  }
  return scifipos->ReadFile(file);
}

int ScifiIncidentPosition02::Calculate(A1Cal2* c2data,int it){
  if(it==0){
    return Calculate(c2data,it,0,0) + Calculate(c2data,it,0,1);
  }
  else if(it==1){
    return Calculate(c2data,it,1,0) + Calculate(c2data,it,1,1);
  }
  return SCIFIINCIDENTPOSITION02_ERROR;
}

double ScifiIncidentPosition02::GetPosX(int it,int il){
  if(il<0){
    if(it==0) return GetPos(0,0,0);
    if(it==1) return GetPos(1,1,0);
  }
  return GetPos(it,il,0);
}

double ScifiIncidentPosition02::GetPosY(int it,int il){
  if(il<0){
    if(it==0) return GetPos(0,0,1);
    if(it==1) return GetPos(1,1,1);
  }
  return GetPos(it,il,1);
}

void  ScifiIncidentPosition02::SetQParam(int it,int il,
					 int ixy,int ip,
					 double value){
  qparam[it][il][ixy][ip] = value;
  f[it][il][ixy]->SetParameter(ip,value);
} 
  
double ScifiIncidentPosition02::GetBaseFluctuation(int it,int il,int ixy){
  if(it==-1){
    return pede[0][0][0];
  }
  else{
    return pede[it][il][ixy];
  }
}

void   ScifiIncidentPosition02::SetBaseFluctuation(int it,int il,int ixy,double value){
  pede[it][il][ixy] = value;
  return ;
}

void   ScifiIncidentPosition02::SetBaseFluctuation(double value){
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	SetBaseFluctuation(it,il,ixy,value);
      }
    }
  }
  return ;
}

int ScifiIncidentPosition02::SetGraph(A1Cal2* c2data,int it,int il,int ixy){
  double pmax;
  int nfiber,ndata;
  double apos;
  double *adc;
  double *tadc;
  if(it==0){
    nfiber = 20;
    adc =  &(c2data->scifi0[il][ixy][0]);
    tadc = &(c2data->scifi0[il][(ixy+1)%2][0]); 
  }
  else if(it==1){
    nfiber = 40;
    adc =  &(c2data->scifi1[il][ixy][0]);
    tadc = &(c2data->scifi1[il][(ixy+1)%2][0]); 
  }
  else{
    cerr << "[ScifiIncidentPosition02::SetGraph] Error " << endl;
    return SCIFIINCIDENTPOSITION02_ERROR; 
  }

  ndata = 0;
  ge[it][il][ixy]->Set(nfiber);
  pmax = MyMax(nfiber,tadc);
  for(int ic=0;ic<nfiber;ic++){
    if(adc[ic]<-9000.){continue;}
    // Dead channels
    if(it==0 && il==1 && ixy==0 && ic==9) {continue;}   // Found at beam tests 
    if(it==1 && il==0 && ixy==0 && ic==0) {continue;}   // Found at beam tests 
    if(it==1 && il==0 && ixy==1 && ic==18){continue;}   // Found at beam tests 
    if(it==0 && il==0 && ixy==1 && ic==14){continue;}   // Found at LHC operations
    apos = scifipos->GetCenterPosition(it,il,ixy,ic,pmax);
    ge[it][il][ixy]->SetPoint(ndata,apos,adc[ic]);
    ge[it][il][ixy]->SetPointError(ndata,0.,sqrt(fabs(adc[ic])+pede[it][il][ixy]));
    ndata ++;
  }   
  ge[it][il][ixy]->Set(ndata);
  return SCIFIINCIDENTPOSITION02_OK;
}  

int ScifiIncidentPosition02::Calculate(A1Cal2* c2data,int it,int il,int ixy){
  SetGraph(c2data,it,il,ixy);
  
  int    imax;
  double dpos,dscl;
  double pmax,pmin;
  int nfiber;
  double *adc;
  if(it==0){
    nfiber = 20;
    adc = &(c2data->scifi0[il][ixy][0]);
  }
  else if(it==1){
    nfiber = 40;
    adc = &(c2data->scifi1[il][ixy][0]);
  }
  else{
    cerr << "[ScifiIncidentPosition02::Calculate] Error " << endl;
    return SCIFIINCIDENTPOSITION02_ERROR; 
  }

  imax = MyMax(nfiber,adc);
  dpos = (double)imax;
  dscl = adc[imax];
  pmin = dpos -1.5;
  pmax = dpos +1.5;
  if(pmin<0.){ pmin = 0.;}
  if(pmax>nfiber) {pmax = nfiber;}
  
  f[it][il][ixy]->SetParameter(1,dpos);
  f[it][il][ixy]->SetParLimits(1,pmin,pmax);
  pmin = 2.*dscl*0.7;
  pmax = 2.*dscl*3.0;
  f[it][il][ixy]->SetParameter(2,dscl);
  f[it][il][ixy]->SetParLimits(2,pmin,pmax);
  ge[it][il][ixy]->Fit(f[it][il][ixy],"IQN","");
  
  pos[it][il][ixy] = f[it][il][ixy]->GetParameter(1);
  
  for(int ip=0;ip<5;ip++){
    qparam[it][il][ixy][ip] = f[it][il][ixy]->GetParameter(ip);
  }
  qparam[it][il][ixy][5] = f[it][il][ixy]->GetChisquare();
  
  return SCIFIINCIDENTPOSITION02_OK; 
}

int ScifiIncidentPosition02::Draw(A1Cal2* c2data,int it,int il,int ixy){
  static TCanvas *c = NULL;
  if(c==NULL){
    c = new TCanvas();
  }
  
  c->cd();
  c->Clear();
  SetGraph(c2data,it,il,ixy);
  
  for(int ip=0;ip<5;ip++){
    f[it][il][ixy]->SetParameter(ip,qparam[it][il][ixy][ip]);
  }
 
  char title[100];
  int  tower=20,layer=0;
  char xy='X';
  if(it==0){tower = 20;}
  if(it==1){tower = 40;}
  if(ixy==0){xy = 'X';}
  if(ixy==1){xy = 'Y';}
  layer = il;
  sprintf(title,"%dmm Layer:%d %c",tower,layer,xy);
  ge[it][il][ixy]->SetTitle(title);
  ge[it][il][ixy]->Draw("ALP");
  f[it][il][ixy]->Draw("same");
  c->Update();
  
  return SCIFIINCIDENTPOSITION02_OK; 
}

#endif
