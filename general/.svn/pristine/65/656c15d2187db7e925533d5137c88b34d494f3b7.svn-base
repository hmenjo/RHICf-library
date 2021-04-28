#ifndef __A2CAL2ACCUMHIST_CPP__
#define __A2CAL2ACCUMHIST_CPP__

#include "A2Cal2AccumHist.h"
#include <iostream>
#include <iomanip>
using namespace std;

#if !defined(__CINT__)
ClassImp(A2Cal2AccumHist);
#endif

int A2Cal2AccumHist::icall = 0;
const int A2Cal2AccumHist::hist_nbin;
const int A2Cal2AccumHist::hist_binmin;
const int A2Cal2AccumHist::hist_binmax;

A2Cal2AccumHist::A2Cal2AccumHist(){
  char name[256];
  char title[256];
  sprintf(name,"a2c2hist%d",icall);
  sprintf(title,"A2Cal2 Histograms %d",icall);
  this->SetName(name);
  this->SetTitle(title); 
  Initialize();
  icall++;
}

A2Cal2AccumHist::A2Cal2AccumHist(char* name, char *title) : 
  TNamed(name,title)
{
  Initialize();
}

A2Cal2AccumHist::~A2Cal2AccumHist(){
  //DeleteHist();
}

int  A2Cal2AccumHist::Initialize(){
  char name[256];
  char title[256];
  
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      sprintf(name,"%s_hcal_%d_%02d",
	      this->GetName(),it,il);
      sprintf(title,"%s Tower:%d Layer:%02d",
	      this->GetTitle(),it,il);
      hist_cal[it][il] = new TH1F(name,title,
				  hist_nbin,
				  hist_binmin,
				  hist_binmax); 
    }
  }

  return OK;
}

int A2Cal2AccumHist::DeleteHist(){

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){    
      delete hist_cal[it][il];
      hist_cal[it][il] = NULL;
    }
  }

  return OK; 
}

int  A2Cal2AccumHist::Fill(A2Cal2 *d){
    
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hist_cal[it][il]->Fill(d->cal[it][il]);
    }
  }

  return OK;
}

int  A2Cal2AccumHist::Reset(){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
	hist_cal[it][il]->Reset();
    }
  }
  return OK;
}

int  A2Cal2AccumHist::CopyData(A2Cal2AccumHist* d){
  double tmp;
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
	// Copy the values
      for(int ibin=1;ibin<=hist_nbin;ibin++){
	tmp = d->hist_cal[it][il]->GetBinContent(ibin);
	hist_cal[it][il]->SetBinContent(ibin,tmp);
      }
      // Copy entries
      tmp = d->hist_cal[it][il]->GetEntries();
      hist_cal[it][il]->SetEntries(tmp);
    }
  }
  return OK;
}

#endif
