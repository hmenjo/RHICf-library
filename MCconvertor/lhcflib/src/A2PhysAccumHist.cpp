#ifndef __A2PHYSACCUMHIST_CPP__
#define __A2PHYSACCUMHIST_CPP__

#include "A2PhysAccumHist.h"
#include <iostream>
#include <iomanip>
using namespace std;

#if !defined(__CINT__)
ClassImp(A2PhysAccumHist);
#endif

int A2PhysAccumHist::icall = 0;
const int A2PhysAccumHist::henergy_nbin;
const int A2PhysAccumHist::henergy_binmin;
const int A2PhysAccumHist::henergy_binmax;
const int A2PhysAccumHist::hpos0_nbin;
const int A2PhysAccumHist::hpos0_binmin;
const int A2PhysAccumHist::hpos0_binmax;
const int A2PhysAccumHist::hpos1_nbin;
const int A2PhysAccumHist::hpos1_binmin;
const int A2PhysAccumHist::hpos1_binmax;
const int A2PhysAccumHist::hpid_nbin;
const int A2PhysAccumHist::hpid_binmin;
const int A2PhysAccumHist::hpid_binmax;
const int A2PhysAccumHist::hhits_nbin;
const int A2PhysAccumHist::hhits_binmin;
const int A2PhysAccumHist::hhits_binmax;
const int A2PhysAccumHist::hsideposit_nbin;
const int A2PhysAccumHist::hsideposit_binmin;
const int A2PhysAccumHist::hsideposit_binmax;
const int A2PhysAccumHist::hsidepositsum_nbin;
const int A2PhysAccumHist::hsidepositsum_binmin;
const int A2PhysAccumHist::hsidepositsum_binmax;

A2PhysAccumHist::A2PhysAccumHist(){
  char name[256];
  char title[256];
  sprintf(name,"a2phist%d",icall);
  sprintf(title,"A2Phys Histograms %d",icall);
  this->SetName(name);
  this->SetTitle(title);
  Initialize();
  icall++;
}

A2PhysAccumHist::A2PhysAccumHist(char* name, char *title) : TNamed(name,title){
  Initialize();
}

A2PhysAccumHist::~A2PhysAccumHist(){
  DeleteHist();
}


int A2PhysAccumHist::Initialize(){
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
		     
  //____________________________________________________________		       
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++)
      for(int ixy=0;ixy<2;ixy++) {
        // for hsideposit 
        if(ixy==0)
        {
          sprintf(name,"%s_hsideposit_%d_%dx",
                  this->GetName(),it, il);
          sprintf(title,"%s SiDeposit Tower:%d Layer:%dx",
	          this->GetTitle(),it, il);
	}
	else if(ixy==1)
	{
          sprintf(name,"%s_hsideposit_%d_%dy",
                  this->GetName(),it, il);
          sprintf(title,"%s SiDeposit Tower:%d Layer:%dy",
	          this->GetTitle(),it, il);	
	}
        hsideposit[it][il][ixy] = new TH1F(name,title,
			   hsideposit_nbin,
			   hsideposit_binmin,
			   hsideposit_binmax);			       
        }
    // for hsideposit 
    sprintf(name,"%s_hsidepositsum_%d",
            this->GetName(),it);
    sprintf(title,"%s SiDepositSum Tower:%d",
	    this->GetTitle(),it);
    hsidepositsum[it] = new TH1F(name,title,
		   hsidepositsum_nbin,
		   hsidepositsum_binmin,
		   hsidepositsum_binmax);
  }	       
        
  return OK;
}

int A2PhysAccumHist::DeleteHist(){
  for(int it=0;it<2;it++){
    if( henergy[it]!=NULL ){delete henergy[it]; henergy[it]=NULL;}
    if( h2pos[it]!=NULL )  {delete h2pos[it]; h2pos[it]=NULL;}
    if( h2flux[it]!=NULL ) {delete h2flux[it]; h2flux[it]=NULL;}
    if( hpid[it]!=NULL )  {delete hpid[it]; hpid[it]=NULL;}
    if( hhits[it]!=NULL ) {delete hhits[it]; hhits[it]=NULL;}
    
    //____________________________________________________________		       
    for(int il=0;il<4;il++)
      for(int ixy=0;ixy<2;ixy++)
         if( hsideposit[it][il][ixy]!=NULL ) {delete hsideposit[it][il][ixy]; hsideposit[it][il][ixy]=NULL;}
         
    if( hsidepositsum[it]!=NULL ) {delete hsidepositsum[it]; hsidepositsum[it]=NULL;}     
  }

  return OK;
}

int A2PhysAccumHist::Fill(A2Phys *d,int pid0, int pid1){
  int n=0;
  
  // Check Hits
  if(d->hits[0]==1 && d->energy[0] > 0.){
    // Select particle
    if( pid0==-10 || pid0==d->pid[0] ){
      henergy[0]->Fill(d->energy[0]);
      h2pos[0]->Fill(d->pos[0][0],d->pos[0][1]);
      h2flux[0]->Fill(d->pos[0][0],d->pos[0][1],d->energy[0]);
      hpid[0]->Fill(d->pid[0]);
      hhits[0]->Fill(d->hits[0]);

/*      
      //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
           hsideposit[0][il][ixy]->Fill(d->sideposit[0][il][ixy][1]);
	           
      hsidepositsum[0]->Fill(d->sidepositsum[0][1]);      
*/
      
      //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
          {
           double bincontent = 0.; 
           for(int isample=0;isample<3;isample++)
            {
             bincontent += d->sideposit[0][il][ixy][isample];
            }
            bincontent/=3.;
            hsideposit[0][il][ixy]->Fill(bincontent);
          }
          
      double bincontent = 0.; 
      for(int isample=0;isample<3;isample++)
        {
	  bincontent += d->sidepositsum[0][isample];
	}
      bincontent/=3.;         
      hsidepositsum[0]->Fill(bincontent);
      
      n++;
    } 
  }

  // Check Hits
  if(d->hits[1]==1 && d->energy[1] > 0.){  
    // Select particle
    if(pid1==-10 || pid1==d->pid[1] ){
      henergy[1]->Fill(d->energy[1]);
      h2pos[1]->Fill(d->pos[1][0],d->pos[1][1]);
      h2flux[1]->Fill(d->pos[1][0],d->pos[1][1],d->energy[1]);
      hpid[1]->Fill(d->pid[1]);
      hhits[1]->Fill(d->hits[1]);
/*      
      //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
           hsideposit[1][il][ixy]->Fill(d->sideposit[1][il][ixy][1]);
	           
      hsidepositsum[1]->Fill(d->sidepositsum[1][1]);      
*/
      //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
          {
           double bincontent = 0.; 
           for(int isample=0;isample<3;isample++)
            {
             bincontent += d->sideposit[1][il][ixy][isample];
            }
            bincontent/=3.;            
            hsideposit[1][il][ixy]->Fill(bincontent);
          }
          
      double bincontent = 0.; 
      for(int isample=0;isample<3;isample++)
        {
         bincontent += d->sidepositsum[1][isample];
         }
      bincontent/=3.;         
      hsidepositsum[1]->Fill(bincontent);
      
      n++;
    }
  }
  
  return n;
}

int A2PhysAccumHist::Reset(){
  for(int it=0;it<2;it++){
    henergy[it]->Reset();
    h2pos[it]->Reset();
    h2flux[it]->Reset();
    hpid[it]->Reset();
    hhits[it]->Reset();
    
    //____________________________________________________________		       
    for(int il=0;il<4;il++)
      for(int ixy=0;ixy<2;ixy++)
         hsideposit[it][il][ixy]->Reset();
         
    hsidepositsum[it]->Reset();      
  } 
  return OK;
}  

int A2PhysAccumHist::CopyData(A2PhysAccumHist* d){
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
          
    //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
          {
            // for hsideposit
            for(int ibin=1;ibin<=hsideposit[it][il][ixy]->GetNbinsX();ibin++){
              tmp = d->hsideposit[it][il][ixy]->GetBinContent(ibin);
              this->hsideposit[it][il][ixy]->SetBinContent(ibin,tmp);
            }
    	    tmp = d->hsideposit[it][il][ixy]->GetEntries();
    	    this->hsideposit[it][il][ixy]->SetEntries(tmp);
    	  }
    	  
    // for hsidepositsum
    for(int ibin=1;ibin<=hsidepositsum[it]->GetNbinsX();ibin++){
      tmp = d->hsidepositsum[it]->GetBinContent(ibin);
      this->hsidepositsum[it]->SetBinContent(ibin,tmp);
    }
    tmp = d->hsidepositsum[it]->GetEntries();
    this->hsidepositsum[it]->SetEntries(tmp);
        	  
  }
  return OK;
}

int A2PhysAccumHist::AddData(A2PhysAccumHist* d){
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
    
    //____________________________________________________________		       
      for(int il=0;il<4;il++)
        for(int ixy=0;ixy<2;ixy++)
          {
            // for hsideposit
            nentry = this->hsideposit[it][il][ixy]->GetEntries()
       	        + d->hhits[it]->GetEntries();
    	    for(int ibin=1;ibin<=hsideposit[it][il][ixy]->GetNbinsX();ibin++){
      	      tmp = this->hsideposit[it][il][ixy]->GetBinContent(ibin)
		+ d->hsideposit[it][il][ixy]->GetBinContent(ibin);
      	      this->hsideposit[it][il][ixy]->SetBinContent(ibin,tmp);
    	    }
    	  this->hsideposit[it][il][ixy]->SetEntries(nentry);
    	  }
    
    // for hsidepositsum
    nentry = this->hsidepositsum[it]->GetEntries()
      + d->hsidepositsum[it]->GetEntries();
    for(int ibin=1;ibin<=hsidepositsum[it]->GetNbinsX();ibin++){
      tmp = this->hsidepositsum[it]->GetBinContent(ibin)
	+ d->hsidepositsum[it]->GetBinContent(ibin);
      this->hsidepositsum[it]->SetBinContent(ibin,tmp);
    }
    this->hsidepositsum[it]->SetEntries(nentry);	      
    
  }
  return OK;
}

#endif
