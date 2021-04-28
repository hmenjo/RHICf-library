#ifndef __SPSADAMOHIST_CPP__
#define __SPSADAMOHIST_CPP__

#include "SPSAdamoHist.h"

//----------------------------------------------------------
// SPSAdamoHist
//
//+++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++
//  04 Oct. 10: First edited by H.MENJO
//----------------------------------------------------------

#if !defined(__CINT__)
ClassImp(SPSAdamoHist);
#endif

#include <iostream>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <cstdio>
using namespace std;

#include "TStyle.h"

int SPSAdamoHist::icall = 0;

SPSAdamoHist::SPSAdamoHist(){
  char name[256];
  char title[256];
  sprintf(name,"a2hev_%d",icall);
  sprintf(title,"A2EventHist");
  this->SetName(name);
  this->SetTitle(title);
  icall++;

  Initialize();
}

SPSAdamoHist::SPSAdamoHist(char* name, char *title) : TNamed(name,title){
  Initialize();
}

SPSAdamoHist::~SPSAdamoHist(){
  DeleteHist();
  DeleteCanvas();
}

int  SPSAdamoHist::Initialize(){
  char name[256];
  char title[256];
    
  strcpy(cname,this->GetName());
  strcpy(ctitle,this->GetTitle());

  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      sprintf(name,"%s_hist_%d_%d",cname,il,ixy);
      sprintf(title,"Layer:%d %s",il,ixy==0 ? "X" : "Y");
      hist[il][ixy] = new TH1F(name,title,SPSAdamo::NSTRIP,0,SPSAdamo::NSTRIP);
      hist[il][ixy]->SetXTitle("#strip");
      hist[il][ixy]->SetYTitle("ADC counts");
      hist[il][ixy]->GetXaxis()->SetTitleSize(0.07);
      hist[il][ixy]->GetXaxis()->SetTitleOffset(0.75);
      hist[il][ixy]->GetXaxis()->SetLabelSize(0.07);  
      hist[il][ixy]->GetYaxis()->SetTitleSize(0.07);
      hist[il][ixy]->GetYaxis()->SetTitleOffset(0.65);
      hist[il][ixy]->GetYaxis()->SetLabelSize(0.07);
    }
  }
  
  c =  NULL;
  
  return OK;
}

int SPSAdamoHist::DeleteHist(){
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      if(hist[il][ixy]){ delete hist[il][ixy]; hist[il][ixy] = NULL; }
    }
  }
  return OK;
}

int SPSAdamoHist::DeleteCanvas(){
  if(c) delete c;
  return OK;
}

int SPSAdamoHist::Reset(){
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      hist[il][ixy]->Reset();
    }
  }
  return OK;
}

int SPSAdamoHist::Fill(SPSAdamo* d, char *op){\
  // Option "S" : only the valid channels are filled. 
 
  bool op_S = false;
  if(strstr(op,"S")){op_S = true;}

  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	if(op_S && !SPSAdamo::IsValidStrip(il,ixy,is)) {continue;}
	hist[il][ixy]->Fill(is+0.5,d->strip[il][ixy][is]);
      }
    }
  }  
  return OK;
}

int SPSAdamoHist::DrawCanvas(){
  char name[256];
  char title[256];
  if(c==NULL){
    sprintf(name,"%s_c",cname);
    sprintf(title,"%s_canvas",ctitle);
    c = new TCanvas(name,title,1000,800);
    c->Divide(2,5,0.001,0.001);
  }

  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      c->cd(il*2+ixy+1);
      gPad->SetRightMargin(0.03);
      gPad->SetLeftMargin(0.10);
      if(hist[il][ixy]){
	hist[il][ixy]->Draw();
      }
    }
  }
  return OK;
}

int SPSAdamoHist::UpdateCanvas(){
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      c->cd(il*2+ixy+1);
      gPad->Modified();
      gPad->Update();
    }
  } 
  return OK;
}

void SPSAdamoHist::SetMaximum(double max, char op[]){
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      if(hist[il][ixy]){
	if(ixy==0 && strstr(op,"X")) hist[il][ixy]->SetMaximum(max);
	if(ixy==1 && strstr(op,"Y")) hist[il][ixy]->SetMaximum(max);
      }
    } 
  }
}

void SPSAdamoHist::SetMinimum(double min, char op[]){
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      if(hist[il][ixy]){
	if(ixy==0 && strstr(op,"X")) hist[il][ixy]->SetMinimum(min);
	if(ixy==1 && strstr(op,"Y")) hist[il][ixy]->SetMinimum(min);
      }
    } 
  }
}

#endif
