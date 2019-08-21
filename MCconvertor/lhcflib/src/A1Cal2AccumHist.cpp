#ifndef __A1CAL2ACCUMHIST_CPP__
#define __A1CAL2ACCUMHIST_CPP__

#include "A1Cal2AccumHist.h"
#include <iostream>
#include <iomanip>
using namespace std;

#if !defined(__CINT__)
ClassImp(A1Cal2AccumHist);
#endif

int A1Cal2AccumHist::icall = 0;
const int A1Cal2AccumHist::hist_nbin;
const int A1Cal2AccumHist::hist_binmin;
const int A1Cal2AccumHist::hist_binmax;

A1Cal2AccumHist::A1Cal2AccumHist(){
  char name[256];
  char title[256];
  sprintf(name,"a1c2hist%d",icall);
  sprintf(title,"A1Cal2 Histograms %d",icall);
  this->SetName(name);
  this->SetTitle(title);
  Initialize();
  icall++;
}

A1Cal2AccumHist::A1Cal2AccumHist(char* name, char *title) : 
  TNamed(name,title)
{
  Initialize();
}

A1Cal2AccumHist::~A1Cal2AccumHist(){
  //DeleteHist();
}

int  A1Cal2AccumHist::Initialize(){
  char name[256];
  char title[256];
  // for calorimter
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

  // for scifi accumulation
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
        sprintf(name,"%s_hacumscifi_%d_%d_%d",
                this->GetName(),it,il,ixy);
        sprintf(title,"%s Tower:%d Layer:%d XY:%d",
                this->GetTitle(),it,il,ixy);
        if(it==0){
          haccum_scifi[it][il][ixy] = new TH1F(name,title,
                                               20,0,20);
        }
        if(it==1){
          haccum_scifi[it][il][ixy] = new TH1F(name,title,
                                               40,0,40);
        }
      }
    }
  }

  return OK;
}

int A1Cal2AccumHist::DeleteHist(){

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){    
      delete hist_cal[it][il];
      hist_cal[it][il] = NULL;
    }
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	delete haccum_scifi[it][il][ixy];	
	haccum_scifi[it][il][ixy] = NULL;
      }
    }
  }

  return OK; 
}

int  A1Cal2AccumHist::Fill(A1Cal2 *d){
  
  // for calorimter
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hist_cal[it][il]->Fill(d->cal[it][il]);
    }
  }
  
  // scifi
  int nbin;
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      // accum
      nbin = haccum_scifi[0][il][ixy]->GetNbinsX();
      for(int ibin=1;ibin<=nbin;ibin++){
	haccum_scifi[0][il][ixy]->Fill(ibin+0.5,
				       d->scifi0[il][ixy][ibin]);
      }
      nbin = haccum_scifi[1][il][ixy]->GetNbinsX();
      for(int ibin=1;ibin<=nbin;ibin++){
	haccum_scifi[1][il][ixy]->Fill(ibin+0.5,
				       d->scifi1[il][ixy][ibin]);
      }
    }
  }


  return OK;
}

int  A1Cal2AccumHist::Reset(){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
	hist_cal[it][il]->Reset();
    }
  }

  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->Reset();
      }
    }
  }  

  return OK;
}

int  A1Cal2AccumHist::CopyData(A1Cal2AccumHist* d){
  int nbin;
  double nentry;
  double tmp;
  // Calorimter
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
  
  // Scifi
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
        nbin = d->haccum_scifi[it][il][ixy]->GetNbinsX();
        nentry = d->haccum_scifi[it][il][ixy]->GetEntries();
        for(int ibin=1;ibin<=nbin;ibin++){
          tmp = d->haccum_scifi[it][il][ixy]->GetBinContent(ibin);
          this->haccum_scifi[it][il][ixy]->SetBinContent(ibin,tmp);
        }
        this->haccum_scifi[it][il][ixy]->SetEntries(nentry);
      }
    }
  }

  return OK;
}

#endif
