#ifndef __A1PHYSACCUMHIST_CPP__
#define __A1PHYSACCUMHIST_CPP__

#include "A1PhysAccumHist.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#if !defined(__CINT__)
ClassImp(A1PhysAccumHist);
#endif

int A1PhysAccumHist::icall = 0;
const int A1PhysAccumHist::henergy_nbin;
const int A1PhysAccumHist::henergy_binmin;
const int A1PhysAccumHist::henergy_binmax;
const int A1PhysAccumHist::hpid_nbin;
const int A1PhysAccumHist::hpid_binmin;
const int A1PhysAccumHist::hpid_binmax;
const int A1PhysAccumHist::hhits_nbin;
const int A1PhysAccumHist::hhits_binmin;
const int A1PhysAccumHist::hhits_binmax;

A1PhysAccumHist::A1PhysAccumHist(){
  char name[256];
  char title[256];
  sprintf(name,"a2phist%d",icall);
  sprintf(title,"A1Phys Histograms %d",icall);
  this->SetName(name);
  this->SetTitle(title);
  Initialize();
  icall++;
}

A1PhysAccumHist::A1PhysAccumHist(char* name, char *title) : TNamed(name,title){
  Initialize();
}

A1PhysAccumHist::~A1PhysAccumHist(){
  //DeleteHist();
}

int  A1PhysAccumHist::Init(){
  return OK;
}

int A1PhysAccumHist::Initialize(){
  char name[256];
  char title[256];
  
  for(int it=0;it<2;it++){
    // for henergy 
    sprintf(name,"%s_henergy_%d",
	    this->GetName(),it);
    sprintf(title,"%s Energy Tower:%d",
	    this->GetTitle(),it);
    henergy[it] = new TH1F(name,title,
			   henergy_nbin,
			   henergy_binmin,
			   henergy_binmax);
    // for hpid
    sprintf(name,"%s_hpid_%d",
	    this->GetName(),it);
    sprintf(title,"%s ParticleID Tower:%d",
	    this->GetTitle(),it);
    hpid[it] = new TH1F(name,title,
			hpid_nbin,
			hpid_binmin,
			hpid_binmax); 

    // for hhits
    sprintf(name,"%s_hhits_%d",
	    this->GetName(),it);
    sprintf(title,"%s Number of Hits Tower:%d",
	    this->GetTitle(),it);
    hhits[it] = new TH1F(name,title,
			 hhits_nbin,
			 hhits_binmin,
			 hhits_binmax);
    
  }    

  // for h2pos
  sprintf(name,"%s_h2pos_0",this->GetName());
  sprintf(title,"%s Position Tower:0",this->GetTitle());
  h2pos[0] = new TH2F(name,title,
		      hpos0_nbin,
		      hpos0_binmin,
		      hpos0_binmax,
		      hpos0_nbin,
		      hpos0_binmin,
		      hpos0_binmax);
  sprintf(name,"%s_h2pos_1",this->GetName());
  sprintf(title,"%s Position Tower:1",this->GetTitle());
  h2pos[1] = new TH2F(name,title,
		      hpos1_nbin,
		      hpos1_binmin,
		      hpos1_binmax,
		      hpos1_nbin,
		      hpos1_binmin,
		      hpos1_binmax); 

  // for h2flux
  sprintf(name,"%s_h2flux_0",this->GetName());
  sprintf(title,"%s Flux Tower:0",this->GetTitle());
  h2flux[0] = new TH2F(name,title,
		       hpos0_nbin,
		       hpos0_binmin,
		       hpos0_binmax,
		       hpos0_nbin,
		       hpos0_binmin,
		       hpos0_binmax);
  sprintf(name,"%s_h2flux_1",this->GetName());
  sprintf(title,"%s Flux Tower:1",this->GetTitle());
  h2flux[1] = new TH2F(name,title,
		       hpos1_nbin,
		       hpos1_binmin,
		       hpos1_binmax,
		       hpos1_nbin,
		       hpos1_binmin,
		       hpos1_binmax); 

  return OK;
}

int A1PhysAccumHist::DeleteHist(){
  for(int it=0;it<2;it++){
    if( henergy[it]){delete henergy[it]; henergy[it]=NULL;}
    if( h2pos[it])  {delete h2pos[it]; h2pos[it]=NULL;}
    if( h2flux[it]) {delete h2flux[it]; h2flux[it]=NULL;}
    if( hpid[it] )  {delete hpid[it]; hpid[it]=NULL;}
    if( hhits[it] ) {delete hhits[it]; hhits[it]=NULL;}
  }
  return OK;
}

int A1PhysAccumHist::Fill(A1Phys *d,int pid0, int pid1){
  int n=0;
  
  // Check Hits
  if(d->hits[0]==1 && d->energy[0] > 0.){
    // Select particle
    if(pid0==-10 || pid0==d->pid[0]){
      henergy[0]->Fill(d->energy[0]);
      h2pos[0]->Fill(d->pos[0][0],d->pos[0][1]);
      h2flux[0]->Fill(d->pos[0][0],d->pos[0][1],d->energy[0]);
      hpid[0]->Fill(d->pid[0]);
      hhits[0]->Fill(d->hits[0]);
      n++;
    } 
  }
  
  // Check Hits
  if(d->hits[1]==1 && d->energy[1] > 0.){ 
    // Select particle
    if(pid1==-10 || pid1==d->pid[1]){
      henergy[1]->Fill(d->energy[1]);
      h2pos[1]->Fill(d->pos[1][0],d->pos[1][1]);
      h2flux[1]->Fill(d->pos[1][0],d->pos[1][1],d->energy[1]);
      hpid[1]->Fill(d->pid[1]);
      hhits[1]->Fill(d->hits[1]);
      n++;
    }
  }

  return n;
}

int A1PhysAccumHist::Reset(){
  for(int it=0;it<2;it++){
    henergy[it]->Reset();
    h2pos[it]->Reset();
    h2flux[it]->Reset();
    hpid[it]->Reset();
    hhits[it]->Reset();
  } 
  return OK;
}  

int A1PhysAccumHist::CopyData(A1PhysAccumHist* d){
  double tmp;
  for(int it=0;it<2;it++){
    // for energy
    for(int ibin=1;ibin<=henergy[it]->GetNbinsX();ibin++){
      tmp = d->henergy[it]->GetBinContent(ibin);
      this->henergy[it]->SetBinContent(ibin,tmp);
    }
    tmp = d->henergy[it]->GetEntries();
    this->henergy[it]->SetEntries(tmp);

    // for pos
    for(int ix=1;ix<=h2pos[it]->GetNbinsX();ix++){
      for(int iy=1;iy<=h2pos[it]->GetNbinsY();iy++){
	tmp = d->h2pos[it]->GetBinContent(ix,iy);
	this->h2pos[it]->SetBinContent(ix,iy,tmp);
      }
    }
    tmp = d->h2pos[it]->GetEntries();
    this->h2pos[it]->SetEntries(tmp);

    // for flux
    for(int ix=1;ix<=h2flux[it]->GetNbinsX();ix++){
      for(int iy=1;iy<=h2flux[it]->GetNbinsY();iy++){
	tmp = d->h2flux[it]->GetBinContent(ix,iy);
	this->h2flux[it]->SetBinContent(ix,iy,tmp);
      }
    }
    tmp = d->h2flux[it]->GetEntries();
    this->h2flux[it]->SetEntries(tmp); 
    
    // for pid
    for(int ibin=1;ibin<=hpid[it]->GetNbinsX();ibin++){
      tmp = d->hpid[it]->GetBinContent(ibin);
      this->hpid[it]->SetBinContent(ibin,tmp);
    }
    tmp = d->hpid[it]->GetEntries();
    this->hpid[it]->SetEntries(tmp);
    
    // for hits
    for(int ibin=1;ibin<=hhits[it]->GetNbinsX();ibin++){
      tmp = d->hhits[it]->GetBinContent(ibin);
      this->hhits[it]->SetBinContent(ibin,tmp);
    }
    tmp = d->hhits[it]->GetEntries();
    this->hhits[it]->SetEntries(tmp);
  }
  return OK;
}

int A1PhysAccumHist::AddData(A1PhysAccumHist* d){
  double tmp;
  double nentry;
  for(int it=0;it<2;it++){
    // for energy
    nentry = this->henergy[it]->GetEntries() 
      + d->henergy[it]->GetEntries();
    for(int ibin=1;ibin<=henergy[it]->GetNbinsX();ibin++){
      tmp = this->henergy[it]->GetBinContent(ibin)
	+ d->henergy[it]->GetBinContent(ibin);
      this->henergy[it]->SetBinContent(ibin,tmp);
    }
    this->henergy[it]->SetEntries(nentry);
    
    // for pos
    nentry = this->h2pos[it]->GetEntries()
      + d->h2pos[it]->GetEntries();
    for(int ix=1;ix<=h2pos[it]->GetNbinsX();ix++){
      for(int iy=1;iy<=h2pos[it]->GetNbinsY();iy++){
	tmp = this->h2pos[it]->GetBinContent(ix,iy)
	  + d->h2pos[it]->GetBinContent(ix,iy);
	this->h2pos[it]->SetBinContent(ix,iy,tmp);
      }
    }
    this->h2pos[it]->SetEntries(nentry);

    // for flux
    nentry = this->h2flux[it]->GetEntries()
      + d->h2flux[it]->GetEntries();
    for(int ix=1;ix<=h2flux[it]->GetNbinsX();ix++){
      for(int iy=1;iy<=h2flux[it]->GetNbinsY();iy++){
	tmp = this->h2flux[it]->GetBinContent(ix,iy)
	  + d->h2flux[it]->GetBinContent(ix,iy);
	this->h2flux[it]->SetBinContent(ix,iy,tmp);
      }
    }
    this->h2flux[it]->SetEntries(nentry); 
    
    // for pid
    nentry = this->hpid[it]->GetEntries()
      + d->hpid[it]->GetEntries();
    for(int ibin=1;ibin<=hpid[it]->GetNbinsX();ibin++){
      tmp = this->hpid[it]->GetBinContent(ibin)
	+ d->hpid[it]->GetBinContent(ibin);
      this->hpid[it]->SetBinContent(ibin,tmp);
    }
    this->hpid[it]->SetEntries(nentry);
    
    // for hits
    nentry = this->hhits[it]->GetEntries()
      + d->hhits[it]->GetEntries();
    for(int ibin=1;ibin<=hhits[it]->GetNbinsX();ibin++){
      tmp = this->hhits[it]->GetBinContent(ibin)
	+ d->hhits[it]->GetBinContent(ibin);
      this->hhits[it]->SetBinContent(ibin,tmp);
    }
    this->hhits[it]->SetEntries(nentry);
  }
  return OK;
}

#endif
