#ifndef __A2CALEVENTHIST_CPP__
#define __A2CALEVENTHIST_CPP__

#include "A2CalEventHist.h"

#if !defined(__CINT__)
ClassImp(A2CalEventHist);
#endif
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCollection.h>
using namespace std;

#include "A2Cal2M.h"

int A2CalEventHist::icall = 0;

A2CalEventHist::A2CalEventHist(){
  char name[256];
  char title[256];
  sprintf(name,"a2hev_%d",icall);
  sprintf(title,"A2EventHist");
  this->SetName(name);
  this->SetTitle(title);
  icall++;
}

A2CalEventHist::~A2CalEventHist(){
  //DeleteHist();
}

int  A2CalEventHist::Initialize(){
  char name[256];
  char title[256];
  char tname[256];
  char rname[256]; 

  strcpy(cname,this->GetName());
  strcpy(ctitle,this->GetTitle());

  gStyle->SetMarkerStyle(1);
  
  for(int it=0;it<2;it++){
    for(int ir=0;ir<2;ir++){
      if(it==0) strcpy(tname,"25mm");
      if(it==1) strcpy(tname,"32mm");
      if(ir==0) strcpy(rname,"low");
      if(ir==1) strcpy(rname,"high");
      sprintf(name,"%s_cal_%d_%d",cname,it,ir);
      sprintf(title,"%s %s %s",ctitle,tname,rname);
      hist_cal[it][ir] = new TH1F(name,title,16,0,16); 
      hist_cal[it][ir]->SetXTitle("Layer");
      hist_cal[it][ir]->SetYTitle("ADC Counts");
      if(ir==0) hist_cal[it][ir]->SetLineColor(4);
      if(ir==1) hist_cal[it][ir]->SetLineColor(2); 
      sprintf(name,"%s_%d_%d_d",cname,it,ir);
      sprintf(title,"%s %s %s delayed",ctitle,tname,rname);
      hist_cald[it][ir] = new TH1F(name,title,16,0,16);
      hist_cald[it][ir]->SetXTitle("Layer");
      hist_cald[it][ir]->SetYTitle("ADC Counts");  
      if(ir==0) hist_cald[it][ir]->SetLineColor(4);
      if(ir==1) hist_cald[it][ir]->SetLineColor(2);
      hist_cald[it][ir]->SetLineStyle(2);

      hist_cal[it][ir]->GetXaxis()->SetTitleSize(0.07);
      hist_cal[it][ir]->GetXaxis()->SetLabelSize(0.07);
      hist_cal[it][ir]->GetXaxis()->SetTitleOffset(0.8);
      hist_cal[it][ir]->GetYaxis()->SetTitleSize(0.07); 
      hist_cal[it][ir]->GetYaxis()->SetLabelSize(0.07); 
      hist_cal[it][ir]->GetYaxis()->SetTitleOffset(0.7);
      hist_cal[it][ir]->GetYaxis()->SetNdivisions(505);
      hist_cald[it][ir]->GetXaxis()->SetTitleSize(0.07);
      hist_cald[it][ir]->GetXaxis()->SetLabelSize(0.07);
      hist_cald[it][ir]->GetXaxis()->SetTitleOffset(0.8);
      hist_cald[it][ir]->GetYaxis()->SetTitleSize(0.07); 
      hist_cald[it][ir]->GetYaxis()->SetLabelSize(0.07); 
      hist_cald[it][ir]->GetYaxis()->SetTitleOffset(0.7);
      hist_cald[it][ir]->GetYaxis()->SetNdivisions(505);
    }
  }
  
  
  for(int i=0;i<2;i++){
    sprintf(name,"%s_fc_%d",cname,i);
    sprintf(title,"%s Arm%d FC",ctitle,i+1);
    hist_fc[i] = new TH1F(name,title,4,0,4);
    hist_fc[i]->SetXTitle("Channel");
    hist_fc[i]->SetYTitle("ADC counts");
    if(i==0) hist_fc[i]->SetLineColor(4);
    if(i==1) hist_fc[i]->SetLineColor(2);  
    hist_fc[i]->GetXaxis()->SetNdivisions(504);
    hist_fc[i]->GetYaxis()->SetNdivisions(505);
  }
  
  sprintf(name,"%s_laser_1",cname);
  sprintf(title,"%s Laser",ctitle);
  hist_laser = new TH1F(name,title,2,0,2);
  hist_laser->SetXTitle("Channel");
  hist_laser->SetYTitle("ADC counts");
  hist_laser->GetXaxis()->SetNdivisions(502);
  hist_laser->GetYaxis()->SetNdivisions(505);
  
  sprintf(name,"%s_noize_1",cname);
  sprintf(title,"%s noise",ctitle);
  hist_noise = new TH1F(name,title,4,0,4);
  hist_noise->SetXTitle("Channel");
  hist_noise->SetYTitle("ADC counts");
  hist_noise->GetXaxis()->SetNdivisions(502);
  hist_noise->GetYaxis()->SetNdivisions(505);

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int itime=0;itime<3;itime++){
	if(ixy==0) strcpy(rname,"X");
	if(ixy==1) strcpy(rname,"Y");
	sprintf(name,"%s_silicon_%d_%d_%d",cname,il,ixy,itime);
	sprintf(title,"%s %d %s %d",ctitle,il,rname,itime);
	//sprintf(title,"%d %s %d",il,rname,itime);
	hist_silicon[il][ixy][itime] = new TH1F(name,title,384,0,384); 
	hist_silicon[il][ixy][itime]->SetXTitle("#Strip");
	hist_silicon[il][ixy][itime]->SetYTitle("ADC Counts");
	if(il==0) hist_silicon[il][ixy][itime]->SetLineColor(4);
	if(il==1) hist_silicon[il][ixy][itime]->SetLineColor(kGreen+3);
	if(il==2) hist_silicon[il][ixy][itime]->SetLineColor(2);
	if(il==3) hist_silicon[il][ixy][itime]->SetLineColor(6);
	if(itime==0) hist_silicon[il][ixy][itime]->SetLineStyle(2);
	if(itime==1) hist_silicon[il][ixy][itime]->SetLineStyle(1);
	if(itime==2) hist_silicon[il][ixy][itime]->SetLineStyle(4);	
	
	hist_silicon[il][ixy][itime]->GetXaxis()->SetNdivisions(510);
	hist_silicon[il][ixy][itime]->GetYaxis()->SetNdivisions(505);
	hist_silicon[il][ixy][itime]->GetXaxis()->SetTitleSize(0.07);
	hist_silicon[il][ixy][itime]->GetXaxis()->SetLabelSize(0.07);
	hist_silicon[il][ixy][itime]->GetXaxis()->SetTitleOffset(0.8);
	hist_silicon[il][ixy][itime]->GetYaxis()->SetTitleSize(0.07);
	hist_silicon[il][ixy][itime]->GetYaxis()->SetLabelSize(0.07);
	hist_silicon[il][ixy][itime]->GetYaxis()->SetTitleOffset(0.4);
      }
    }
  }
  
  // For GPIO Flags (LHCFLOGIC)
  double x,y;
  char text[256];
  for(int i=0;i<16;i++){
    if(i==0)  {strcpy(text,"BPTX1");}
    if(i==1)  {strcpy(text,"BPTX2");}
    if(i==2)  {strcpy(text,"EXT_L1T");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"L2TA");}
    if(i==5)  {strcpy(text,"L2TP");}
    if(i==6)  {strcpy(text,"L2T_EXT");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"L2T_L1T");}
    if(i==9)  {strcpy(text,"    -");}
    if(i==10) {strcpy(text,"STRG");}
    if(i==11) {strcpy(text,"LTRG");}
    if(i==12) {strcpy(text,"BEAM");}
    if(i==13) {strcpy(text,"PEDE");}
    if(i==14) {strcpy(text,"LASER");}
    if(i==15) {strcpy(text,"ENABLE");}
    x = 0.10+i*0.056;
    y = 0.80;
    t_flag[0][i] = new TText(x,y,text);
    t_flag[0][i]->SetTextSize(0.080);
  }
  // For op2015
  for(int i=0;i<16;i++){  
    x = 0.10+i*0.056;
    y = 0.70;
    strcpy(text,"");
    t_flag[0][i+16] = new TText(x,y,text);
    t_flag[0][i+16]->SetTextSize(0.080);  
  }  

  x = 0.01;
  y = 0.80;
  sprintf(text,"FFFFFFFF  :");  
  t_flagd[0] = new TText(x,y,text);
  t_flagd[0] ->SetTextSize(0.090);
  t_flagd[0] ->SetTextFont(102);

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(it==0){ sprintf(text,"25-%02d",il); }
      if(it==1){ sprintf(text,"32-%02d",il); }
      x = 0.10+il*0.056;
      y = 0.50-0.10*it;
      t_flag[1][il+16*it] = new TText(x,y,text); 
      t_flag[1][il+16*it]->SetTextSize(0.090);
    }
  }
  x = 0.01;
  y = 0.50;
  sprintf(text,"FFFFFFFF  :");  
  t_flagd[1] = new TText(x,y,text);
  t_flagd[1] ->SetTextSize(0.090);
  t_flagd[1]->SetTextFont(102);

  // For GPIO Flags (LHCFCOUNTER)
  for(int i=0;i<32;i++){
    if(i==0)  {strcpy(text,"A1ENA");}
    if(i==1)  {strcpy(text,"A1STR");}
    if(i==2)  {strcpy(text,"A1L3T");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"A2ENA");}
    if(i==5)  {strcpy(text,"A2STR");}
    if(i==6)  {strcpy(text,"A2L3T");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"BPTX1");}
    if(i==9)  {strcpy(text,"BPTX2");}
    if(i==10) {strcpy(text,"L1A");}
    if(i==11) {strcpy(text,"    -");}
    if(i==12) {strcpy(text,"A1_FC");}
    if(i==13) {strcpy(text,"A2_FC");}
    if(i==14) {strcpy(text,"L2TC");}
    if(i==15) {strcpy(text,"    -");}
    if(i==16) {strcpy(text,"A1FC0");}
    if(i==17) {strcpy(text,"A1FC1");}
    if(i==18) {strcpy(text,"A1FC2");}
    if(i==19) {strcpy(text,"A1FC3");}
    if(i==20) {strcpy(text,"A2FC0");}
    if(i==21) {strcpy(text,"A2FC1");}
    if(i==22) {strcpy(text,"A2FC2");}
    if(i==23) {strcpy(text,"A2FC3");}
    if(i>=24) {strcpy(text,"");}
    if(i<16){ 
      x = 0.10+i*0.056;
      y = 0.18;
    }
    else{
      x = 0.10+(i-16)*0.056;
      y = 0.18-0.11 ;
    } 
    t_flag[2][i] = new TText(x,y,text); 
    t_flag[2][i]->SetTextSize(0.078);
  } 
  x = 0.01;
  y = 0.15;
  sprintf(text,"FFFFFFFF  :");  
  t_flagd[2] = new TText(x,y,text);
  t_flagd[2] ->SetTextSize(0.090);
  t_flagd[2]->SetTextFont(102);

  // Scaler
  strcpy(text,"10000000");
  for(int i=0;i<16;i++){
    x = 0.005+0.062*i;
    y = 0.80;
    t_scl[i] = new TText(x,y,text);
    t_scl[i]->SetTextSize(0.075);
    t_scl[i]->SetTextFont(102);
  }

  // GPIO counter
  strcpy(text,"100000000");
  for(int i=0;i<35;i++){
    x = 0.005+0.083*(i%12);
    y = 0.57-0.16*(i/12);
    t_cnt[i] = new TText(x,y,text);
    t_cnt[i]->SetTextSize(0.075);
    t_cnt[i]->SetTextFont(102);
  }

  // FIFO counter
  strcpy(text,"100000000");
  for(int i=0;i<8;i++){
    x = 0.10+0.10*i + (i/4)*0.05;
    y = 0.05;
    t_fifo[i] = new TText(x,y,text);
    t_fifo[i]->SetTextSize(0.075);
    t_fifo[i]->SetTextFont(102);
  }
  
  // TDC 
  strcpy(text,"10000");
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      x = 0.10 + 0.056*ihit;
      y = 0.85 - 0.068*ich - 0.02*(ich/4);
      t_tdc[ich][ihit] =  new TText(x,y,text);
      t_tdc[ich][ihit]->SetTextSize(0.070);
      t_tdc[ich][ihit]->SetTextFont(102);
    }
  }

  // Info
  for(int i=0;i<7;i++){
    x = 0.4;
    y = 0.95 - 0.11*(i+1);
    strcpy(text,"0000");
    t_info[i] =  new TText(x,y,text);
    t_info[i]->SetTextSize(0.120);
    t_info[i]->SetTextFont(102);
  }

  c1=NULL;
  c1pad1_1=NULL;
  c1pad1_2=NULL;
  c1pad1_3=NULL;
  c1pad1_4=NULL;
  c1pad2_1=NULL;
  c1pad2_2=NULL;
  c1pad3_1=NULL;
  c1pad3_2=NULL;
  c1pad4_1=NULL;
  c1pad4_2=NULL;

  c2=NULL;
  c2pad1=NULL;
  c2pad2=NULL;
  c2pad3=NULL;
  c2pad4=NULL;

  c3=NULL;

  for(int i=0;i<35;i++){
    l_cnt[i] = NULL;
  }
  
  return OK;
}

int A2CalEventHist::DeleteHist(){

  for(int it=0;it<2;it++){
    for(int ir=0;ir<2;ir++){
      if(hist_cal[it][ir]){
	delete hist_cal[it][ir];
	hist_cal[it][ir] = NULL;	
      }	
      if(hist_cald[it][ir]){
	delete hist_cald[it][ir]; 
	hist_cald[it][ir] = NULL;  
      }
    } 
  }
    
  for(int i=0;i<2;i++){
    if(hist_fc[i]){
      delete hist_fc[i];
      hist_fc[i] = NULL;
    }
  }  
  
  if(hist_laser){
    delete hist_laser;
    hist_laser = NULL;
  }
  if(hist_noise){
    delete hist_noise;
    hist_noise = NULL;
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<3;ixy++){
	if(hist_silicon[it][il][ixy]){
	  delete hist_silicon[it][il][ixy];
	  hist_silicon[it][il][ixy] = NULL;
	}
      }
    }
  }

 if(g_tdc){ delete g_tdc; g_tdc=NULL;}
  
  for(int i=0;i<7;i++){
    if(t_info[i]){
      delete t_info[i];
      t_info[i] = NULL;
    }
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(t_tdc[ich][ihit]){
	delete t_tdc[ich][ihit];
	t_tdc[ich][ihit] = NULL;
      }
    }
  }

  for(int ich=0;ich<16;ich++){
    if(t_scl[ich]){
      delete t_scl[ich];
      t_scl[ich] = NULL;
    }
  }

  for(int i=0;i<3;i++){
    for(int j=0;j<32;j++){
      if(t_flag[i][j]){
	delete t_flag[i][j];
	t_flag[i][j] = NULL;
      } 
    }
  }

  for(int i=0;i<3;i++){ 
    if(t_flagd[i]){
      delete t_flagd[i];
      t_flagd[i] = NULL;
    } 
  }

  for(int j=0;j<35;j++){
    if(t_cnt[j]){
      delete t_cnt[j];
      t_cnt[j] = NULL;
    }
  }
  for(int j=0;j<8;j++){
    if(t_fifo[j]){
      delete t_fifo[j];
      t_fifo[j] = NULL;
    }
  }

  if(c1){ delete c1; c1=NULL;}
  if(c1pad1_1){ delete c1pad1_1; c1pad1_1 = NULL;}
  if(c1pad1_2){ delete c1pad1_2; c1pad1_2 = NULL;}
  if(c1pad1_3){ delete c1pad1_3; c1pad1_3 = NULL;}
  if(c1pad1_4){ delete c1pad1_4; c1pad1_4 = NULL;}
  if(c1pad2_1){ delete c1pad2_1; c1pad2_1 = NULL;}
  if(c1pad2_2){ delete c1pad2_2; c1pad2_2 = NULL;}
  if(c1pad3_1){ delete c1pad3_1; c1pad3_1 = NULL;}
  if(c1pad3_2){ delete c1pad3_2; c1pad3_2 = NULL;}
  if(c1pad4_1){ delete c1pad4_1; c1pad4_1 = NULL;}
  if(c1pad4_2){ delete c1pad4_2; c1pad4_2 = NULL;}
  
  if(c2){ delete c2; c2=NULL; }
  if(c2pad1){ delete c2pad1; c2pad1=NULL; }
  if(c2pad2){ delete c2pad2; c2pad2=NULL; }  
  if(c2pad3){ delete c2pad3; c2pad3=NULL; }
  if(c2pad4){ delete c2pad4; c2pad4=NULL; }
 
  if(c3){ delete c3; c3=NULL; }
  
  return OK;
}

// ============== A2CalEventHist::Reset ==============
int A2CalEventHist::Reset(){
  for(int it=0;it<2;it++){
    for(int ir=0;ir<2;ir++){
      hist_cal[it][ir]->Reset();
      hist_cald[it][ir]->Reset();
    }
  }
  hist_fc[0]->Reset();
  hist_fc[1]->Reset();
  hist_laser->Reset();
  hist_noise->Reset();
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int itime=0;itime<3;itime++){
	hist_silicon[il][ixy][itime]->Reset();
      }
    }
  } 
  
  for(int i=0;i<7;i++){
    t_info[i]->SetTitle("");
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      t_tdc[ich][ihit]->SetTitle("");
    }
  } 
  
  for(int i=0;i<16;i++){
    t_scl[i]->SetTitle("");
  }
  
  for(int iflag=0;iflag<3;iflag++){
    t_flagd[iflag]->SetTitle("");
    for(int ib=0;ib<32;ib++){
      if(iflag==0 && ib==32){break;}
      if(iflag==1 && ib==32){break;}
      if(iflag==2 && ib==32){break;}
      t_flag[iflag][ib]->SetTextColor(kGray);
    }
  }
  
  for(int i=0;i<35;i++){
    t_cnt[i]->SetTitle("");
  }
  
  for(int i=0;i<8;i++){
    t_fifo[i]->SetTitle("");
  }
  
  return OK;
}

// ============== A2CalEventHist::Fill ==============
int A2CalEventHist::Fill(A2Cal1* d){
  for(int it=0;it<2;it++){
    for(int ir=0;ir<2;ir++){
      for(int il=0;il<16;il++){
	hist_cal[it][ir]->Fill(il+0.5,d->cal[it][il][ir]); 
	hist_cald[it][ir]->Fill(il+0.5,d->cald[it][il][ir]); 
      }
    }
  }
  
  for(int ia=0;ia<2;ia++){
    for(int ich=0;ich<4;ich++){
      hist_fc[ia]->Fill(ich+0.5,d->fc[ia][ich]);
    }
  }

  for(int ich=0;ich<2;ich++){
    hist_laser->Fill(ich+0.5,d->laser[ich]);
  }
  
  for(int ich=0;ich<8;ich++){
    if(ich==hist_noise->GetNbinsX()) break;
    hist_noise->Fill(ich+0.5,d->emptyadc[ich]);
  }
  

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int itime=0;itime<3;itime++){
	for(int is=0;is<384;is++){
	  hist_silicon[il][ixy][itime]
	    ->Fill(is+0.5,d->silicon[il][ixy][is][itime]);
	}
      }
    }
  }
  
  // Flags
  char text[256];
  for(int i=0;i<3;i++){
    sprintf(text,"%08x  :",d->flag[i]);
    t_flagd[i]->SetTitle(text);
    for(int ib=0;ib<32;ib++){  
      if(i==0 && ib==32) break;
      if(i==1 && ib==32) break;
      if(i==2 && ib==32) break;

      if((d->flag[i] >> ib) & 0x1){
	t_flag[i][ib]->SetTextColor(kRed);
      }
      else{
	t_flag[i][ib]->SetTextColor(kGray);
      }
    }
  }
  
  // Scaler
  for(int i=0;i<16;i++){
    sprintf(text,"%8u",(unsigned int)d->scl0[i]);
    t_scl[i]->SetTitle(text);
  }

  // GPIO Counters
  for(int i=0;i<35;i++){
    sprintf(text,"%u",(unsigned int)d->counter[i]);
    t_cnt[i]->SetTitle(text);
  }

  // GPIO Counter FIFO
  for(int i=0;i<8;i++){
    sprintf(text,"%u",(unsigned int)d->fifocounter[i/4][i%4]);
    t_fifo[i]->SetTitle(text);
  }

  // TDC
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(d->tdc0flag[ich][ihit]<0){
	t_tdc[ich][ihit]->SetTitle("");
      }
      else{
	sprintf(text,"%d",(int)d->tdc0[ich][ihit]);
	t_tdc[ich][ihit]->SetTitle(text);
      }
    }
  }

  // INFO
  for(int i=0;i<7;i++){
    if(i==0) sprintf(text,"%d",d->run);
    if(i==1) sprintf(text,"%d",d->number);
    if(i==2) sprintf(text,"%d",d->gnumber);
    if(i==3) sprintf(text,"%d",(int)d->time[0]);  
    if(i==4) sprintf(text,"%08x",d->flag[0]);
    if(i==5) sprintf(text,"%08x",d->flag[1]);
    if(i==6) sprintf(text,"%08x",d->flag[2]);    
    t_info[i]->SetTitle(text);
  }

  // Change label according to GPIO logic version.
  if( f_DisplayVersion == VERSION_PP2010){
    if(gpioversion!=SelGPIOLogicFormat(d)){
      gpioversion = SelGPIOLogicFormat(d);
      if(gpioversion==GPIOLOGIC_OLD){
	t_flag[0][7]->SetTitle("    -");
	t_flag[0][9]->SetTitle("    -");
	if(l_cnt[12]) l_cnt[12]->SetTitle("L2T_L1A_E");
	if(l_cnt[14]) l_cnt[14]->SetTitle("");   
      }
      else if(gpioversion==GPIOLOGIC_V28){
	t_flag[0][7]->SetTitle("L2TA_SP");
	t_flag[0][9]->SetTitle("L2TA_MB");
	if(l_cnt[12]) l_cnt[12]->SetTitle("L2TA_W/OE");
	if(l_cnt[14]) l_cnt[14]->SetTitle("SPE_ENA"); 
      }
    }
  }
  
  return OK;
}

// ============== A2CalEventHist::Fill ==============
int A2CalEventHist::Fill(A2Cal2* d){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      hist_cal[it][0]->Fill(il+0.5,d->cal[it][il]); 
    }
  }
  
  for(int ia=0;ia<2;ia++){
    for(int ich=0;ich<4;ich++){
      hist_fc[ia]->Fill(ich+0.5,d->fc[ia][ich]);
    }
  }

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int itime=0;itime<3;itime++){
	for(int is=0;is<384;is++){
	  hist_silicon[il][ixy][itime]
	    ->Fill(is+0.5,d->silicon[il][ixy][is][itime]);
	}
      }
    }
  }
  
  // Flags
  char text[256];
  for(int i=0;i<3;i++){
    sprintf(text,"%08x  :",d->flag[i]);
    t_flagd[i]->SetTitle(text);
    for(int ib=0;ib<32;ib++){  
      if(i==0 && ib==16) break;
      if(i==1 && ib==32) break;
      if(i==2 && ib==24) break;

      if((d->flag[i] >> ib) & 0x1){
	t_flag[i][ib]->SetTextColor(kRed);
      }
      else{
	t_flag[i][ib]->SetTextColor(kGray);
      }
    }
  }

  // INFO
  for(int i=0;i<7;i++){
    if(i==0) sprintf(text,"%d",d->run);
    if(i==1) sprintf(text,"%d",d->number);
    if(i==2) sprintf(text,"%d",d->gnumber);
    if(i==3) sprintf(text,"%d",(int)d->time[0]);  
    if(i==4) sprintf(text,"%08x",d->flag[0]);
    if(i==5) sprintf(text,"%08x",d->flag[1]);
    if(i==6) sprintf(text,"%08x",d->flag[2]);    
    t_info[i]->SetTitle(text);
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++
  // +++++       If d is "A2Cal2M"         +++++
  // ++++++++++++++++++++++++++++++++++++++++++++++
  if(strcmp(d->ClassName(),"A2Cal2M")==0){
    A2Cal2M* dm = (A2Cal2M*) d;

    // TDC
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	if(dm->tdc0flag[ich][ihit]<0){
	  t_tdc[ich][ihit]->SetTitle("");
	}
	else{
	  sprintf(text,"%d",(int)dm->tdc0[ich][ihit]);
	  t_tdc[ich][ihit]->SetTitle(text);
	}
      }
    }
    
    // Scaler
    for(int i=0;i<16;i++){
      sprintf(text,"%8u",(unsigned int)dm->scl0[i]);
      t_scl[i]->SetTitle(text);
    }
    
    // GPIO Counters
    for(int i=0;i<35;i++){
      sprintf(text,"%u",(unsigned int)dm->counter[i]);
      t_cnt[i]->SetTitle(text);
    }
    
    // GPIO Counter FIFO
    for(int i=0;i<8;i++){
      sprintf(text,"%u",(unsigned int)dm->fifocounter[i/4][i%4]);
      t_fifo[i]->SetTitle(text);
    } 
  }


  return OK;
}

// ============== A2CalEventHist::DrawCanvas1 ==============
int A2CalEventHist::DrawCanvas1(char *option){
  char name[256];
  char title[256];
  char tmp[256];
  if(c1==NULL){
    sprintf(name,"%s_c1",cname);
    sprintf(title,"%s_canvas1",ctitle);
    c1 = new TCanvas(name,title,1000,800);
  }
  if(c1pad1_1==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad1_1",cname);
    c1pad1_1 = new TPad(name,"",0.0,0.77,0.30,1.0);
    c1pad1_1->SetBorderSize(1); 
    c1pad1_1->Draw();
   }
  if(c1pad1_2==NULL){ 
    c1->cd();
    sprintf(name,"%s_c1pad1_2",cname);
    c1pad1_2 = new TPad(name,"",0.3,0.77,0.55,1.0);
    c1pad1_2->SetBorderSize(1);
    c1pad1_2->Draw();
  }  
  if(c1pad1_3==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad1_3",cname);
    c1pad1_3 = new TPad(name,"",0.55,0.77,0.80,1.0);
    c1pad1_3->SetBorderSize(1); 
    c1pad1_3->Draw();
  } 
  if(c1pad1_4==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad1_4",cname);
    c1pad1_4 = new TPad(name,"",0.80,0.77,1.0,1.0); 
    c1pad1_4->SetBorderSize(1);
    c1pad1_4->Draw();
  }
  
  if(c1pad2_1==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad2_1",cname);
    c1pad2_1 = new TPad(name,"",0.0,0.5,0.5,0.77);
    c1pad2_1->SetBorderSize(1); 
    c1pad2_1->Draw();
   }
  if(c1pad2_2==NULL){ 
    c1->cd();
    sprintf(name,"%s_c1pad2_2",cname);
    c1pad2_2 = new TPad(name,"",0.50,0.5,1.0,0.77);
    c1pad2_2->SetBorderSize(1);
    c1pad2_2->Draw();
  }  
  
  if(c1pad3_1==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad3_1",cname);
    c1pad3_1 = new TPad(name,"",0.0,0.25,1.0,0.50);
    c1pad3_1->SetBorderSize(1); 
    c1pad3_1->Draw();
   }
//   if(c1pad3_2==NULL){ 
//     c1->cd();
//     sprintf(name,"%s_c1pad3_2",cname);
//     c1pad3_2 = new TPad(name,"",0.40,0.25,1.0,0.50);
//     c1pad3_2->SetBorderSize(1);
//     c1pad3_2->Draw();
//   }  
   
  if(c1pad4_1==NULL){
    c1->cd();
    sprintf(name,"%s_c1pad4_1",cname);
    c1pad4_1 = new TPad(name,"",0.0,0.0,1.0,0.25);
    c1pad4_1->SetBorderSize(1); 
    c1pad4_1->Draw();
   }
//   if(c1pad4_2==NULL){ 
//     c1->cd();
//     sprintf(name,"%s_c1pad4_2",cname);
//     c1pad4_2 = new TPad(name,"",0.40,0.0,1.0,0.25);
//     c1pad4_2->SetBorderSize(1);
//     c1pad4_2->Draw();
//   }  


  char gop[256] = "hist";
  TLegend *legend;
  
  // Calorimeter 25mm
  c1pad2_1->cd();
  if(strstr(option,"low")!=0 || strstr(option,"Low")!=0){
    hist_cal[0][0]->Draw(gop);
    strcpy(gop,"hist,same");
  
    if(strstr(option,"delay")!=0 || strstr(option,"Delay")!=0 ||
       strstr(option,"delayed")!=0 || strstr(option,"Delayed")!=0 ){
      hist_cald[0][0]->Draw(gop);
      strcpy(gop,"hist,same");
    }
  }
  if(strstr(option,"high")!=0 || strstr(option,"High")!=0){
    hist_cal[0][1]->Draw(gop);   
    strcpy(gop,"hist,same");
    if(strstr(option,"delay")!=0 || strstr(option,"Delay")!=0 ||
       strstr(option,"delayed")!=0 || strstr(option,"Delayed")!=0){
      hist_cald[0][1]->Draw(gop);
      strcpy(gop,"hist,same");
    }
  }
  c1pad2_1->Update();
  legend = c1pad2_1->BuildLegend(0.75,0.77,0.98,1.0);
  legend->SetFillColor(kWhite);
  c1pad2_1->Update();

  // Calorimeter 32mm
  c1pad2_2->cd();
  strcpy(gop,"hist");
  if(strstr(option,"low")!=0 || strstr(option,"Low")!=0){
    hist_cal[1][0]->Draw(gop); 
    strcpy(gop,"hist,same");
    if(strstr(option,"delay")!=0 || strstr(option,"Delay")!=0 ||
       strstr(option,"delayed")!=0 || strstr(option,"Delayed")!=0 ){
      hist_cald[1][0]->Draw(gop); 
      strcpy(gop,"hist,same");
    }
  }
  if(strstr(option,"high")!=0 || strstr(option,"High")!=0){
    hist_cal[1][1]->Draw(gop); 
    strcpy(gop,"hist,same");
    if(strstr(option,"delay")!=0 || strstr(option,"Delay")!=0 ||
       strstr(option,"delayed")!=0 || strstr(option,"Delayed")!=0){
      hist_cald[1][1]->Draw(gop);
      strcpy(gop,"hist,same");
    }
  }
  c1pad2_2->Update();
  legend = c1pad2_2->BuildLegend(0.75,0.77,0.98,1.0);
  legend->SetFillColor(kWhite);
  c1pad2_2->Update();
  
  // Silicon X
  c1pad3_1->cd();
  c1pad3_1->SetRightMargin(0.12);
  c1pad3_1->SetLeftMargin(0.06);
  strcpy(gop,"hist,");
  for(int il=0;il<4;il++){
    sprintf(tmp,"silicon%d",il);
    if(strstr(option,tmp)!=0 || strstr(option,"siliconall")!=0){
      if(strstr(option,"silicont0")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][0][0]->Draw(gop);
	strcpy(gop,"hist,same");
      }
      if(strstr(option,"silicont1")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][0][1]->Draw(gop);
	strcpy(gop,"hist,same");
      }
      if(strstr(option,"silicont2")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][0][2]->Draw(gop);
	strcpy(gop,"hist,same");
      }
    }
  }
  c1pad3_1->Update();
  legend = c1pad3_1->BuildLegend(0.90,0.05,0.99,0.95); 
  legend->SetFillColor(kWhite);
  c1pad3_1->Update();
  ChangeHistTitleOnPad(c1pad3_1,"X-View");

  // Silicon Y
  c1pad4_1->cd(); 
  c1pad4_1->SetRightMargin(0.12);
  c1pad4_1->SetLeftMargin(0.06); 
  strcpy(gop,"hist,");
  for(int il=0;il<4;il++){
    sprintf(tmp,"silicon%d",il);
    if(strstr(option,tmp)!=0 || strstr(option,"siliconall")!=0){
      if(strstr(option,"silicont0")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][1][0]->Draw(gop);
	strcpy(gop,"hist,same");
      }
      if(strstr(option,"silicont1")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][1][1]->Draw(gop);
	strcpy(gop,"hist,same");
      }
      if(strstr(option,"silicont2")!=0 || strstr(option,"silicontall")!=0){
	hist_silicon[il][1][2]->Draw(gop);
	strcpy(gop,"hist,same");
      }
    }
  }
  c1pad4_1->Update();
  legend = c1pad4_1->BuildLegend(0.90,0.05,0.99,0.95); 
  legend->SetFillColor(kWhite);
  c1pad4_1->Update();
  ChangeHistTitleOnPad(c1pad4_1,"X-View");

  // FC
  c1pad1_2->cd();
  strcpy(gop,"hist,");
  hist_fc[0]->Draw();
  hist_fc[1]->Draw("hist,same");
  c1pad1_2->Update();
  legend = c1pad1_2->BuildLegend(0.75,0.85,0.99,0.99); 
  legend->SetFillColor(kWhite);
  c1pad1_2->Update(); 
  
  // Noise
  c1pad1_3->cd();
  strcpy(gop,"hist,");
  hist_noise->Draw();
  c1pad1_3->Update();

  // Laser
  c1pad1_4->cd();
  strcpy(gop,"hist,");
  hist_laser->Draw();
  c1pad1_4->Update();

  // Info
  c1pad1_1->cd();
  // Info
  char text[256];
  double x,y;
  TText* l_info[7];
  for(int i=0;i<7;i++){
    x = 0.05;
    y = 0.95 - 0.11*(i+1);
    if(i==0) strcpy(text,"RUN:");
    if(i==1) strcpy(text,"NUMBER:");
    if(i==2) strcpy(text,"GNUMBER:");
    if(i==3) strcpy(text,"TIME:");
    if(i==4) strcpy(text,"FLAG0:");
    if(i==5) strcpy(text,"FLAG1:");
    if(i==6) strcpy(text,"FLAG2:");
    l_info[i] = new TText(x,y,text);
    l_info[i]->SetTextSize(0.1);
    l_info[i]->Draw();
    t_info[i]->Draw();
  }
  c1pad1_1->Update();

  return OK;
}

int  A2CalEventHist::UpdateCanvas1(){
  OptimizeYRange();

  if(c1pad1_1!=NULL) {c1pad1_1->Modified();c1pad1_1->Update();}
  if(c1pad1_2!=NULL) {c1pad1_2->Modified();c1pad1_2->Update();}
  if(c1pad1_3!=NULL) {c1pad1_3->Modified();c1pad1_3->Update();}
  if(c1pad1_4!=NULL) {c1pad1_4->Modified();c1pad1_4->Update();}
  if(c1pad2_1!=NULL) {c1pad2_1->Modified();c1pad2_1->Update();}
  if(c1pad2_2!=NULL) {c1pad2_2->Modified();c1pad2_2->Update();}
  if(c1pad3_1!=NULL) {c1pad3_1->Modified();c1pad3_1->Update();}
  if(c1pad3_2!=NULL) {c1pad3_2->Modified();c1pad3_2->Update();}
  if(c1pad4_1!=NULL) {c1pad4_1->Modified();c1pad4_1->Update();}
  if(c1pad4_2!=NULL) {c1pad4_2->Modified();c1pad4_2->Update();}
  if(c1!=NULL){c1->Modified();c1->Update();}
  return OK;
}

int  A2CalEventHist::ClearCanvas1(){
  if(c1pad1_1!=NULL) {c1pad1_1->Clear();}
  if(c1pad1_2!=NULL) {c1pad1_2->Clear();}
  if(c1pad1_3!=NULL) {c1pad1_3->Clear();}
  if(c1pad1_4!=NULL) {c1pad1_4->Clear();}
  if(c1pad2_1!=NULL) {c1pad2_1->Clear();}
  if(c1pad2_2!=NULL) {c1pad2_2->Clear();}
  if(c1pad3_1!=NULL) {c1pad3_1->Clear();}
  if(c1pad3_2!=NULL) {c1pad3_2->Clear();}
  if(c1pad4_1!=NULL) {c1pad4_1->Clear();}
  if(c1pad4_2!=NULL) {c1pad4_2->Clear();}
  return OK;
}

int  A2CalEventHist::SetHistConfig(int op){
  // Set Title of Y-axis of histograms
  // op=0 for A1Cal1, op=1 for A1Cal2 
  for(int it=0;it<2;it++){
    for(int ir=0;ir<2;ir++){
      if(op==0)     { hist_cal[it][ir]->SetYTitle("ADC Counts");}
      else if(op==1){ hist_cal[it][ir]->SetYTitle("dE [MIPs]");}
    }
  }
  
  for(int i=0;i<2;i++){
    if(op==0)     { hist_fc[i]->SetYTitle("ADC Counts");}
    else if(op==1){ hist_fc[i]->SetYTitle("dE [MIPs]");}
  }    
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){ 
      for(int is=0;is<3;is++){
	if(op==0)     { hist_silicon[il][ixy][is]->SetYTitle("ADC Counts");}
	else if(op==1){ hist_silicon[il][ixy][is]->SetYTitle("dE [MeV]");}
      }
    }
  }
  return OK;
}

int  A2CalEventHist::OptimizeYRange(){
  
  OptimizeYRange(c1pad1_2);
  OptimizeYRange(c1pad1_3);
  OptimizeYRange(c1pad1_4); 
  OptimizeYRange(c1pad2_1);
  OptimizeYRange(c1pad2_2); 
  OptimizeYRange(c1pad3_1);
  OptimizeYRange(c1pad4_1);

  return OK;
}

//========== A2CalEventHist::DrawCanvas2 =========
int A2CalEventHist::DrawCanvas2(char *option){
  char name[256];
  char title[256];
  char text[256]; 
  double x,y;
  if(c2==NULL){
    sprintf(name,"%s_c2",cname);
    sprintf(title,"%s_canvas2",ctitle);
    c2 = new TCanvas(name,title,1000,800);
  }
  if(c2pad1==NULL){
    c2->cd();
    sprintf(name,"%s_c2pad1",cname);
    c2pad1 = new TPad(name,"",0.0,0.77,1.0,1.0);
    c2pad1->SetBorderSize(1); 
    c2pad1->Draw();
  } 
  if(c2pad2==NULL){
    c2->cd();
    sprintf(name,"%s_c2pad2",cname);
    c2pad2 = new TPad(name,"",0.0,0.50,1.0,0.77);
    c2pad2->SetBorderSize(1); 
    c2pad2->Draw();
  } 
  if(c2pad3==NULL){
    c2->cd();
    sprintf(name,"%s_c2pad3",cname);
    c2pad3 = new TPad(name,"",0.0,0.25,1.0,0.50);
    c2pad3->SetBorderSize(1); 
    c2pad3->Draw();
  }
  if(c2pad4==NULL){
    c2->cd();
    sprintf(name,"%s_c2pad4",cname);
    c2pad4 = new TPad(name,"",0.0,0.00,1.0,0.25);
    c2pad4->SetBorderSize(1); 
    c2pad4->Draw();
  }

  c2pad1->cd();
  lf_0 = new TText(0.01,0.88,"FLAG0 : LHCFLOGIC FLAGS");
  lf_0->SetTextSize(0.090);
  lf_0->Draw();
  lf_1 = new TText(0.01,0.60,"FLAG1 : LHCFLOGIC DISCRIMINATOR");
  lf_1->SetTextSize(0.090);
  lf_1->Draw();
  lf_2 = new TText(0.01,0.25,"FLAG2 : LHCFCOUNTER FLAGS");
  lf_2->SetTextSize(0.090);
  lf_2->Draw();
  
  for(int iflag=0;iflag<3;iflag++){
    t_flagd[iflag]->Draw();
    for(int i=0;i<32;i++){
      if(iflag==0 && i<32) t_flag[iflag][i]->Draw();
      if(iflag==1 && i<32) t_flag[iflag][i]->Draw();
      if(iflag==2 && i<32) t_flag[iflag][i]->Draw();
    }
  }
  c2pad1->Update();
  
  c2pad2->cd();
  // Scaler
  TText *lscl = new TText(0.01,0.92,"Scaler");
  lscl->SetTextSize(0.090);
  lscl->Draw();
  for(int i=0;i<16;i++){
    x = 0.025+0.062*i;
    y = 0.87;
    l_scl[i] = new TText(x,y,"");
    l_scl[i]->SetTextSize(0.075);
    l_scl[i]->SetTextFont(102);
    l_scl[i]->SetTextColor(kGray+2);
    l_scl[i]->Draw();
  } 
  for(int i=0;i<16;i++){
    t_scl[i]->Draw();
  }

  // GPIO Counter 
  TText *l_cntl = new TText(0.01,0.71,"GPIO Counters");
  l_cntl->SetTextSize(0.090);
  l_cntl->Draw();
  for(int i=0;i<35;i++){
    if(i==0){strcpy(text,"CLK");}
    if(i==1){strcpy(text,"L1T");}
    if(i==2){strcpy(text,"BPTX_AND");}
    if(i==3){strcpy(text,"L1T_ENA");}
    if(i==4){strcpy(text,"STRG");}
    if(i==5){strcpy(text,"LTRG");}
    if(i==6){strcpy(text,"SHOWER");}
    if(i==7){strcpy(text,"SLOGIC");}
    if(i==8){strcpy(text,"LLOGIC");}
    if(i==9){strcpy(text,"L2TA");}
    if(i==10){strcpy(text,"L2TP");}
    if(i==11){strcpy(text,"L2TEXT_ENA");}
    if(i==12){strcpy(text,"L2T_L1A_E");}
    if(i==13){strcpy(text,"L3T");}
    if(i==14){strcpy(text,"");}
    if(i==15){strcpy(text,"CLK");}
    if(i==16){strcpy(text,"ORBIT");}  
    if(i==17){strcpy(text,"L1A");}
    if(i==18){strcpy(text,"A1_L3T");}
    if(i==19){strcpy(text,"A2_L3T");}  
    if(i==20){strcpy(text,"OR_L3T");}
    if(i==21){strcpy(text,"STRG_OR");}
    if(i==22){strcpy(text,"STRG_AND");}
    if(i==23){strcpy(text,"CLK'");}
    if(i==24){strcpy(text,"BPTX1'");}
    if(i==25){strcpy(text,"BPTX2'");}
    if(i==26){strcpy(text,"CLK''");}
    if(i==27){strcpy(text,"L1A''");}
    if(i==28){strcpy(text,"SFC_0");}
    if(i==29){strcpy(text,"SFC_1");}
    if(i==30){strcpy(text,"SFC_2");}
    if(i==31){strcpy(text,"SFC_3");}
    if(i==32){strcpy(text,"SFC1");}
    if(i==33){strcpy(text,"SFC2");}
    if(i==34){strcpy(text,"SFC3");}
    
    x = 0.005+0.083*(i%12);
    y = 0.64-0.16*(i/12);
    l_cnt[i] = new TText(x,y,text);
    l_cnt[i]->SetTextSize(0.067);
    l_cnt[i]->SetTextColor(kGray+2);
    l_cnt[i]->Draw();
  }

  for(int i=0;i<35;i++){
    t_cnt[i]->Draw();
  }

  // fifo counter
  TText *l_fifol = new TText(0.01,0.14,"GPIO Counters FIFO");
  l_fifol->SetTextSize(0.090);
  l_fifol->Draw();
  for(int i=0;i<8;i++){
    t_fifo[i]->Draw();
  }
  c2pad2->Update();
  
  // TDC Value
  c2pad3->cd();
  TText *l_tdcl = new TText(0.01,0.93,"TDC");
  l_tdcl->SetTextSize(0.090);
  l_tdcl->Draw();
  
  for(int ich=0;ich<12;ich++){
    x = 0.005;
    y = 0.85 - 0.068*ich - 0.02*(ich/4);
    if(ich==0){strcpy(text,"ch0: CLK");}
    if(ich==1){strcpy(text,"ch1: L3T");}
    if(ich==2){strcpy(text,"ch2: BPTX1");}
    if(ich==3){strcpy(text,"ch3: BPTX2");}
    if(ich==4){strcpy(text,"ch4: SHOWER");}
    if(ich==5){strcpy(text,"ch5: ");}
    if(ich==6){strcpy(text,"ch6: ARM1 FC");}
    if(ich==7){strcpy(text,"ch7: ARM2 FC");}
    if(ich==8){strcpy(text,"ch8: 25mm OR");}
    if(ich==9){strcpy(text,"ch9: 32mm OR");}
    if(ich==10){strcpy(text,"ch10: ");}
    if(ich==11){strcpy(text,"ch11: ");}
    
    l_tdc[ich] =  new TText(x,y,text);
    l_tdc[ich]->SetTextSize(0.065);
    l_tdc[ich]->Draw();
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      t_tdc[ich][ihit]->Draw();
    }
  }

  
  c2pad3->Update();

  return OK;
}

int  A2CalEventHist::UpdateCanvas2(){
  if(c2pad1!=NULL) {c2pad1->Modified();c2pad1->Update();}
  if(c2pad2!=NULL) {c2pad2->Modified();c2pad2->Update();}
  if(c2pad3!=NULL) {c2pad3->Modified();c2pad3->Update();}
  if(c2pad4!=NULL) {c2pad4->Modified();c2pad4->Update();}
  if(c2!=NULL) {c2->Modified();c2->Update();}
  return OK;
}

int A2CalEventHist::DrawCanvas3(char *option){
  char name[256];
  char title[256];
  if(c3==NULL){
    sprintf(name,"%s_c3",cname);
    sprintf(title,"%s_canvas3",ctitle);
    c3 = new TCanvas(name,title,1000,800);
    c3->Divide(2,4);
  } 
  
  for(int il=0;il<4;il++){
    for(int ix=0;ix<2;ix++){
      c3->cd(il*2+ix+1);
      gPad->SetRightMargin(0.05);
      gPad->SetLeftMargin(0.18); 
      hist_silicon[il][ix][0]->Draw("hist"); 
      hist_silicon[il][ix][2]->Draw("hist,same");
      hist_silicon[il][ix][1]->Draw("hist,same");
    }
  }
  
  c3->Update();
  
  TH1* hbase;
  for(int il=0;il<4;il++){
    for(int ix=0;ix<2;ix++){
      c3->cd(il*2+ix+1);
      if(ix==0) sprintf(title,"%s Layer:%d X",this->GetTitle(),il);
      else      sprintf(title,"%s Layer:%d Y",this->GetTitle(),il);
      ChangeHistTitleOnPad((TPad*)gPad,title);
      hbase = GetTH1OnPad((TPad*)gPad);
      hbase->GetYaxis()->SetTitleOffset(1.15);
    }
  }
  UpdateCanvas3();
  
  return OK;
}

int  A2CalEventHist::UpdateCanvas3(){

  if(c3!=NULL) {
    for(int il=0;il<4;il++){
      for(int ix=0;ix<2;ix++){
	c3->cd(il*2+ix+1);
	OptimizeYRange((TPad*)gPad);
	gPad->Modified();
      }
      c3->Modified();
      c3->Update();
    }
  }
  return OK;
  
}

int  A2CalEventHist::SetCanvas3YRange(double min,double max){
  TH1* hbase;
  if(c3!=NULL) {
    for(int il=0;il<4;il++){
      for(int ix=0;ix<2;ix++){
	c3->cd(il*2+ix+1);
	hbase = GetTH1OnPad((TPad*)gPad);
	if(hbase){
	  hbase->GetYaxis()->SetRangeUser(min,max); 
	}
	gPad->Modified();
      }
    }
  }
  c3->Update();
  return OK;
}

int  A2CalEventHist::SetHistColor(int op){
  Color_t color=kBlack;
  int     style=1;
  int     width=1;
  // Color Configuration for Canvas3
  if(op==3){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int isample=0;isample<3;isample++){
	  if(hist_silicon[il][ixy][isample]){
	    if(isample==0){color=kGray+1; style=2; width=1;}
	    if(isample==1){color=kBlack;  style=1; width=1;}
	    if(isample==2){color=kGray+2; style=1; width=1;}
	    hist_silicon[il][ixy][isample]->SetLineColor(color);
	    hist_silicon[il][ixy][isample]->SetLineStyle(style);
	    hist_silicon[il][ixy][isample]->SetLineWidth(width);
	  }
	}
      }
    }
  }
  
  return OK;
}

int  A2CalEventHist::OptimizeYRange(TPad* pad){
  TObject *obj;
  TH1     *hbase = NULL;     
  double min=100000,max=-100000.;

  if(pad!=NULL){
    TIter next((TCollection*)pad->GetListOfPrimitives());
    while((obj = next())){
      if(strstr(obj->ClassName(),"TH1")!=0){
	if(strstr(next.GetOption(),"same")==NULL){
	  hbase = (TH1*) obj;
	  if( hbase->TestBit(TH1::kIsZoomed) ) break; 
	  hbase->SetMinimum();
	  hbase->SetMaximum();
	}
	if( ((TH1*)obj)->GetMinimum() < min ){
	  min = ((TH1*)obj)->GetMinimum();
	}
	if( ((TH1*)obj)->GetMaximum() > max ){
	  max =  ((TH1*)obj)->GetMaximum();
	}
      }
    }
    if( hbase!=NULL && !hbase->TestBit(TH1::kIsZoomed) ){
      hbase->SetMinimum(min-(max-min)*0.03);
      hbase->SetMaximum(max+(max-min)*0.05);
    }
  }
  return OK;
}

int A2CalEventHist::ChangeHistTitleOnPad(TPad* pad,char* title){
  TH1* hbase = GetTH1OnPad(pad);
  if(hbase==NULL){
    return ERROR;
  }
  
  hbase->SetTitle(title);
  return OK;
}

TH1* A2CalEventHist::GetTH1OnPad(TPad* pad){
  TObject *obj;
  TH1     *hbase = NULL;   
  if(pad!=NULL){
    TIter next((TCollection*)pad->GetListOfPrimitives());
    while((obj = next())){
      if(strstr(obj->ClassName(),"TH1")!=0){
	if(strstr(next.GetOption(),"same")==NULL){
	  hbase = (TH1*) obj;
	  break;
	}
      }
    }
  }
  return hbase;
}

// ====================================================================
//                     SELECTION OF DISPLAY FORMAT 
// ====================================================================
A2CalEventHist::GPIOLOGIC A2CalEventHist::SelGPIOLogicFormat(A2Cal1* d){
  if(d->counter[14] > 0 && d->counter[14] < 100000000){
    return GPIOLOGIC_V28;
  }
  else{
    return GPIOLOGIC_OLD;
  }
}

int A2CalEventHist::SetDisplayFormat(DISPLAY_VERSION version){
  switch (version){
  case VERSION_PP2010 :
    SetDisplayVersion_pp2010();
    return 0;
  case VERSION_PPB2013 :
    SetDisplayVersion_pPb2013();
    return 0;
  case VERSION_PP2015 :
    SetDisplayVersion_pp2015();
    return 0;   
  case VERSION_PPB2016 :
    SetDisplayVersion_pPb2016();
    return 0;  
  default :
    cerr << "[A2CalEventHist::SetDisplayFormat]" << " Unknown Format" << endl;
    return -1;
  }
  return -1;
}

// -------------------------------------------------------------
// ----                DISPLAY VERSION PP2010               ----
// -------------------------------------------------------------
void A2CalEventHist::SetDisplayVersion_pp2010(){
  f_DisplayVersion = VERSION_PP2010;
    
  // For GPIO Flags (LHCFLOGIC)
  for(int i=0;i<16;i++){
    char text[20];
    if(i==0)  {strcpy(text,"BPTX1");}
    if(i==1)  {strcpy(text,"BPTX2");}
    if(i==2)  {strcpy(text,"EXT_L1T");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"L2TA");}
    if(i==5)  {strcpy(text,"L2TP");}
    if(i==6)  {strcpy(text,"L2T_EXT");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"L2T_L1T");}
    if(i==9)  {strcpy(text,"    -");}
    if(i==10) {strcpy(text,"STRG");}
    if(i==11) {strcpy(text,"LTRG");}
    if(i==12) {strcpy(text,"BEAM");}
    if(i==13) {strcpy(text,"PEDE");}
    if(i==14) {strcpy(text,"LASER");}
    if(i==15) {strcpy(text,"ENABLE");}
     t_flag[0][i]->SetTitle(text);
  }
  // For GPIO Flags (LHCFCOUNTER)
  for(int i=0;i<24;i++){
    char text[20]; 
    if(i==0)  {strcpy(text,"A1ENA");}
    if(i==1)  {strcpy(text,"A1STR");}
    if(i==2)  {strcpy(text,"A1L3T");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"A2ENA");}
    if(i==5)  {strcpy(text,"A2STR");}
    if(i==6)  {strcpy(text,"A2L3T");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"BPTX1");}
    if(i==9)  {strcpy(text,"BPTX2");}
    if(i==10) {strcpy(text,"L1A");}
    if(i==11) {strcpy(text,"    -");}
    if(i==12) {strcpy(text,"A1_FC");}
    if(i==13) {strcpy(text,"A2_FC");}
    if(i==14) {strcpy(text,"L2TC");}
    if(i==15) {strcpy(text,"    -");}
    if(i==16) {strcpy(text,"A1FC0");}
    if(i==17) {strcpy(text,"A1FC1");}
    if(i==18) {strcpy(text,"A1FC2");}
    if(i==19) {strcpy(text,"A1FC3");}
    if(i==20) {strcpy(text,"A2FC0");}
    if(i==21) {strcpy(text,"A2FC1");}
    if(i==22) {strcpy(text,"A2FC2");}
    if(i==23) {strcpy(text,"A2FC3");}  
    t_flag[2][i]->SetTitle(text);
  }
  
  // GPIO Counter  
  for(int i=0;i<35;i++){
    char text[20];
    if(i==0){strcpy(text,"CLK");}
    if(i==1){strcpy(text,"L1T");}
    if(i==2){strcpy(text,"BPTX_AND");}
    if(i==3){strcpy(text,"L1T_ENA");}
    if(i==4){strcpy(text,"STRG");}
    if(i==5){strcpy(text,"LTRG");}
    if(i==6){strcpy(text,"SHOWER");}
    if(i==7){strcpy(text,"SLOGIC");}
    if(i==8){strcpy(text,"LLOGIC");}
    if(i==9){strcpy(text,"L2TA");}
    if(i==10){strcpy(text,"L2TP");}
    if(i==11){strcpy(text,"L2TEXT_ENA");}
    if(i==12){strcpy(text,"L2T_L1A_E");}
    if(i==13){strcpy(text,"L3T");}
    if(i==14){strcpy(text,"");}
    if(i==15){strcpy(text,"CLK");}
    if(i==16){strcpy(text,"ORBIT");}  
    if(i==17){strcpy(text,"L1A");}
    if(i==18){strcpy(text,"A1_L3T");}
    if(i==19){strcpy(text,"A2_L3T");}  
    if(i==20){strcpy(text,"OR_L3T");}
    if(i==21){strcpy(text,"STRG_OR");}
    if(i==22){strcpy(text,"STRG_AND");}
    if(i==23){strcpy(text,"CLK'");}
    if(i==24){strcpy(text,"BPTX1'");}
    if(i==25){strcpy(text,"BPTX2'");}
    if(i==26){strcpy(text,"CLK''");}
    if(i==27){strcpy(text,"L1A''");}
    if(i==28){strcpy(text,"SFC_0");}
    if(i==29){strcpy(text,"SFC_1");}
    if(i==30){strcpy(text,"SFC_2");}
    if(i==31){strcpy(text,"SFC_3");}
    if(i==32){strcpy(text,"SFC1");}
    if(i==33){strcpy(text,"SFC2");}
    if(i==34){strcpy(text,"SFC3");}
    l_cnt[i]->SetTitle(text);    
  }
  
   // For Scalers
  for(int ich=0;ich<16;ich++){
    char text[20];
    if(ich==0) {strcpy(text,"CLK");}
    if(ich==1) {strcpy(text,"->");}
    if(ich==2) {strcpy(text,"BPTX1");}
    if(ich==3) {strcpy(text,"->");}
    if(ich==4) {strcpy(text,"BPTX2");}
    if(ich==5) {strcpy(text,"->");}
    if(ich==6) {strcpy(text,"L3T");}
    if(ich==7) {strcpy(text,"L2TA");}
    if(ich==8) {strcpy(text,"FC2-1");}
    if(ich==9) {strcpy(text,"FC2-2");}
    if(ich==10){strcpy(text,"FC2-3");}
    if(ich==11){strcpy(text,"FC2-4");}
    if(ich==12){strcpy(text,"");}
    if(ich==13){strcpy(text,"");}
    if(ich==14){strcpy(text,"");}
    if(ich==15){strcpy(text,"");}
    l_scl[ich]->SetTitle(text);
  }
  // For TDC
  for(int ich=0;ich<12;ich++){
    char text[20];
    if(ich==0){strcpy(text,"ch0: CLK");}
    if(ich==1){strcpy(text,"ch1: L3T");}
    if(ich==2){strcpy(text,"ch2: BPTX1");}
    if(ich==3){strcpy(text,"ch3: BPTX2");}
    if(ich==4){strcpy(text,"ch4: SHOWER");}
    if(ich==5){strcpy(text,"ch5: ");}
    if(ich==6){strcpy(text,"ch6: ARM1 FC");}
    if(ich==7){strcpy(text,"ch7: ARM2 FC");}
    if(ich==8){strcpy(text,"ch8: 25mm OR");}
    if(ich==9){strcpy(text,"ch9: 32mm OR");}
    if(ich==10){strcpy(text,"ch10: ");}
    if(ich==11){strcpy(text,"ch11: ");}
    l_tdc[ich]->SetTitle(text);
  }

  UpdateCanvas2();
  return ;
}

void A2CalEventHist::SetDisplayVersion_pPb2013(){
  f_DisplayVersion = VERSION_PPB2013;
  
  // For GPIO Flags (LHCFLOGIC)
  for(int i=0;i<16;i++){
    char text[20];
    if(i==0)  {strcpy(text,"BPTX1");}
    if(i==1)  {strcpy(text,"BPTX2");}
    if(i==2)  {strcpy(text,"EXT_L1T");}
    if(i==3)  {strcpy(text,"BPTX_AND");}
    if(i==4)  {strcpy(text,"L2TA");}
    if(i==5)  {strcpy(text,"L2TP");}
    if(i==6)  {strcpy(text,"L2T_EXT");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"L2T_L1T");}
    if(i==9)  {strcpy(text,"    -");}
    if(i==10) {strcpy(text,"STRG");}
    if(i==11) {strcpy(text,"LTRG");}
    if(i==12) {strcpy(text,"BEAM");}
    if(i==13) {strcpy(text,"PEDE");}
    if(i==14) {strcpy(text,"LASER");}
    if(i==15) {strcpy(text,"ENABLE");}
    t_flag[0][i]->SetTitle(text);
  }
  // For GPIO Flags (LHCFCOUNTER)
  for(int i=0;i<24;i++){
    char text[20];
    if(i==0)  {strcpy(text,"    -");}
    if(i==1)  {strcpy(text,"    -");}
    if(i==2)  {strcpy(text,"    -");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"A2ENA");}
    if(i==5)  {strcpy(text,"A2STR");}
    if(i==6)  {strcpy(text,"A2L3T");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"BPTX1");}
    if(i==9)  {strcpy(text,"BPTX2");}
    if(i==10) {strcpy(text,"L1A");}
    if(i==11) {strcpy(text,"    -");}
    if(i==12) {strcpy(text,"    -");}
    if(i==13) {strcpy(text,"A2_FC");}
    if(i==14) {strcpy(text,"    -");}
    if(i==15) {strcpy(text,"    -");}
    if(i==16) {strcpy(text,"    -");}
    if(i==17) {strcpy(text,"    -");}
    if(i==18) {strcpy(text,"    -");}
    if(i==19) {strcpy(text,"    -");}
    if(i==20) {strcpy(text,"A2FC0");}
    if(i==21) {strcpy(text,"A2FC1");}
    if(i==22) {strcpy(text,"A2FC2");}
    if(i==23) {strcpy(text,"A2FC3");}  
    t_flag[2][i]->SetTitle(text);
  }
  
  // GPIO Counter
  for(int i=0;i<35;i++){
    char text[20];
    if(i==0){strcpy(text,"CLK");}
    if(i==1){strcpy(text,"L1T");}
    if(i==2){strcpy(text,"BPTX_AND");}
    if(i==3){strcpy(text,"L1T_ENA");}
    if(i==4){strcpy(text,"STRG");}
    if(i==5){strcpy(text,"LTRG");}
    if(i==6){strcpy(text,"SHOWER");}
    if(i==7){strcpy(text,"SLOGIC");}
    if(i==8){strcpy(text,"LLOGIC");}
    if(i==9){strcpy(text,"L2TA");}
    if(i==10){strcpy(text,"L2TP");}
    if(i==11){strcpy(text,"L2TEXT");}
    if(i==12){strcpy(text,"L2T_WOE");}
    if(i==13){strcpy(text,"L3T");}
    if(i==14){strcpy(text,"");}
    if(i==15){strcpy(text,"CLK");}
    if(i==16){strcpy(text,"ORBIT");}  
    if(i==17){strcpy(text,"L1A");}
    if(i==18){strcpy(text,"  -  ");}
    if(i==19){strcpy(text,"A2_L3T");}  
    if(i==20){strcpy(text,"  -  ");}
    if(i==21){strcpy(text,"  -  ");}
    if(i==22){strcpy(text,"  -  ");}
    if(i==23){strcpy(text,"CLK'");}
    if(i==24){strcpy(text,"BPTX1'");}
    if(i==25){strcpy(text,"BPTX2'");}
    if(i==26){strcpy(text,"CLK''");}
    if(i==27){strcpy(text,"L1A''");}
    if(i==28){strcpy(text,"SFC_0");}
    if(i==29){strcpy(text,"SFC_1");}
    if(i==30){strcpy(text,"SFC_2");}
    if(i==31){strcpy(text,"SFC_3");}
    if(i==32){strcpy(text,"FCL_OR");}
    if(i==33){strcpy(text,"FC_TRG");}
    if(i==34){strcpy(text,"FC&STRG");}
    l_cnt[i]->SetTitle(text);    
  }

  // For Scalers
  for(int ich=0;ich<16;ich++){
    char text[20];
    if(ich==0) {strcpy(text,"CLK");}
    if(ich==1) {strcpy(text,"->");}
    if(ich==2) {strcpy(text,"BPTX1");}
    if(ich==3) {strcpy(text,"->");}
    if(ich==4) {strcpy(text,"BPTX2");}
    if(ich==5) {strcpy(text,"->");}
    if(ich==6) {strcpy(text,"L3T");}
    if(ich==7) {strcpy(text,"L2TA");}
    if(ich==8) {strcpy(text,"FC2-1");}
    if(ich==9) {strcpy(text,"FC2-2");}
    if(ich==10){strcpy(text,"FC2-3");}
    if(ich==11){strcpy(text,"FC2-4");}
    if(ich==12){strcpy(text,"");}
    if(ich==13){strcpy(text,"FC2 TRG");}
    if(ich==14){strcpy(text,"");}
    if(ich==15){strcpy(text,"");}
    l_scl[ich]->SetTitle(text);
  }
  // For TDC
  for(int ich=0;ich<12;ich++){
    char text[20];
    if(ich==0) {strcpy(text,"ch0: CLK");}
    if(ich==1) {strcpy(text,"ch1: L3T");}
    if(ich==2) {strcpy(text,"ch2: BPTX1");}
    if(ich==3) {strcpy(text,"ch3: BPTX2");}
    if(ich==4) {strcpy(text,"ch4: SHOWER");}
    if(ich==5) {strcpy(text,"ch5: ATLAS L1A");}
    if(ich==6) {strcpy(text,"ch6: ");}
    if(ich==7) {strcpy(text,"ch7: ARM2 FC");}
    if(ich==8) {strcpy(text,"ch8: 25mm OR");}
    if(ich==9) {strcpy(text,"ch9: 32mm OR");}
    if(ich==10){strcpy(text,"ch10:QDC GATE1");}
    if(ich==11){strcpy(text,"ch11:QDC GATE2");}
    l_tdc[ich]->SetTitle(text);
  } 
  
  UpdateCanvas2();
  return ;
}

// -------------------------------------------------------------
// ----                DISPLAY VERSION PP2015               ----
// -------------------------------------------------------------
void A2CalEventHist::SetDisplayVersion_pp2015(){
  f_DisplayVersion = VERSION_PP2015;
  
  char text[20];
  // For GPIO Flags (LHCFLOGIC)
  lf_0->SetTitle("FLAG0 : DAQ LOGIC");
  for(int i=0;i<32;i++){
    if(i==0)  {strcpy(text,"BPTX1");}
    if(i==1)  {strcpy(text,"BPTX2");}
    if(i==2)  {strcpy(text,"B1&B2");}
    if(i==3)  {strcpy(text,"LASER");}
    if(i==4)  {strcpy(text,"L2TSHW");}
    if(i==5)  {strcpy(text,"L2TSPE");}
    if(i==6)  {strcpy(text,"L2TPED");}
    if(i==7)  {strcpy(text,"L2TL1T");} 
    if(i==8)  {strcpy(text,"L2TFC");}
    if(i==9)  {strcpy(text,"    -");}
    if(i==10) {strcpy(text,"STRG");}
    if(i==11) {strcpy(text,"LTRG");}
    if(i==12) {strcpy(text,"FBEAM");}
    if(i==13) {strcpy(text,"FPEDE");}
    if(i==14) {strcpy(text,"-");}
    if(i==15) {strcpy(text,"L1A");}
    if(i==16) {strcpy(text,"A2_L1T");}
    if(i==17) {strcpy(text,"A2_L3T");}
    if(i==18) {strcpy(text,"A2_ENA");}
    if(i==19) {strcpy(text,"A2_SHW");}
    if(i==20) {strcpy(text,"A1_L1T");}
    if(i==21) {strcpy(text,"A1_L3T");}
    if(i==22) {strcpy(text,"A1_ENA");}
    if(i==23) {strcpy(text,"A1_SHW");}
    if(i==24) {strcpy(text,"A2_FC0");}
    if(i==25) {strcpy(text,"A2_FC1");}
    if(i==26) {strcpy(text,"A2_FC2");}
    if(i==27) {strcpy(text,"A2_FC3");}
    if(i==28) {strcpy(text,"A1_FC0");}
    if(i==29) {strcpy(text,"A1_FC1");}
    if(i==30) {strcpy(text,"A1_FC2");}
    if(i==31) {strcpy(text,"A1_FC3");}
    t_flag[0][i]->SetTitle(text);
  }
  // GPIO[1] : Arm2 DSC
  lf_1->SetTitle("FLAG1 : ARM2 DSC");
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(it==0){ sprintf(text,"25-%02d",il); }
      if(it==1){ sprintf(text,"32-%02d",il); }
      t_flag[1][il+16*it]->SetTitle(text);
    }
  }
  // GPIO[2] : Arm1 DSC 
  lf_2->SetTitle("FLAG2 : ARM1 DSC");
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      if(it==0){ sprintf(text,"20-%02d",il); }
      if(it==1){ sprintf(text,"40-%02d",il); }
      t_flag[2][il+16*it]->SetTitle(text);
    }
  }
  
  // GPIO Counter
  for(int i=0;i<35;i++){
    if(i==0){strcpy(text,"CLK");}
    if(i==1){strcpy(text,"BPTX1");}
    if(i==2){strcpy(text,"BPTX2");}
    if(i==3){strcpy(text,"B1&B2");}
    if(i==4){strcpy(text,"ORBIT");}
    if(i==5){strcpy(text,"L1T");}
    if(i==6){strcpy(text,"L1T_BE");}
    if(i==7){strcpy(text,"STRG");}
    if(i==8){strcpy(text,"LTRG");}
    if(i==9){strcpy(text,"SLOGIC");}
    if(i==10){strcpy(text,"LLOGIC");}
    if(i==11){strcpy(text,"SHOWER");}
    if(i==12){strcpy(text,"SHOWER_B");}
    if(i==13){strcpy(text,"SPECIAL");}
    if(i==14){strcpy(text,"SPECIAL_B");}
    if(i==15){strcpy(text,"TRG_SHOWER");}
    if(i==16){strcpy(text,"TRG_SPECIAL");}  
    if(i==17){strcpy(text,"TRG_PEDE");}
    if(i==18){strcpy(text,"TRG_L1T");}
    if(i==19){strcpy(text,"L3T");}  
    if(i==20){strcpy(text,"L3T OR");}
    if(i==21){strcpy(text,"=MIX=");}
    if(i==22){strcpy(text,"BUNCH_POS");}
    if(i==23){strcpy(text,"BUNCH_B1");}
    if(i==24){strcpy(text,"BUNCH_B2");}
    if(i==25){strcpy(text,"ATLAS_CLK");}
    if(i==26){strcpy(text,"ATLAS_L1A");}
    if(i==27){strcpy(text,"SFC(0)");}
    if(i==28){strcpy(text,"SFC(1)");}
    if(i==29){strcpy(text,"SFC(2)");}
    if(i==30){strcpy(text,"SFC(3)");}
    if(i==31){strcpy(text,"FC_LOGIC");}
    if(i==32){strcpy(text,"FC_TRG");}
    if(i==33){strcpy(text,"A2SHW&A1FC");}
    if(i==34){strcpy(text,"A1FC&A2FC");}
    l_cnt[i]->SetTitle(text);    
  }

  // For Scalers
  for(int ich=0;ich<16;ich++){
    if(ich==0) {strcpy(text,"->");}
    if(ich==1) {strcpy(text,"CLK");}
    if(ich==2) {strcpy(text,"BPTX1");}
    if(ich==3) {strcpy(text,"BPTX2");}
    if(ich==4) {strcpy(text,"L3T");}
    if(ich==5) {strcpy(text,"FC1&FC2");}
    if(ich==6) {strcpy(text,"FC1 TRG");}
    if(ich==7) {strcpy(text,"FC2 TRG");}
    if(ich==8) {strcpy(text,"FC2-1");}
    if(ich==9) {strcpy(text,"FC2-2");}
    if(ich==10){strcpy(text,"FC2-3");}
    if(ich==11){strcpy(text,"FC2-4");}
    if(ich==12){strcpy(text,"");}
    if(ich==13){strcpy(text,"");}
    if(ich==14){strcpy(text,"");}
    if(ich==15){strcpy(text,"");}
    l_scl[ich]->SetTitle(text);
  }
  // For TDC
  for(int ich=0;ich<12;ich++){
    if(ich==0) {strcpy(text,"ch0: CLK");}
    if(ich==1) {strcpy(text,"ch1: L3T");}
    if(ich==2) {strcpy(text,"ch2: BPTX1");}
    if(ich==3) {strcpy(text,"ch3: BPTX2");}
    if(ich==4) {strcpy(text,"ch4: SHOWER");}
    if(ich==5) {strcpy(text,"ch5: ATLAS L1A");}
    if(ich==6) {strcpy(text,"ch6: ARM1 FC");}
    if(ich==7) {strcpy(text,"ch7: ARM2 FC");}
    if(ich==8) {strcpy(text,"ch8: 25mm OR");}
    if(ich==9) {strcpy(text,"ch9: 32mm OR");}
    if(ich==10){strcpy(text,"ch10:QDC GATE");}
    if(ich==11){strcpy(text,"ch11:-");}
    l_tdc[ich]->SetTitle(text);
  } 
  
  UpdateCanvas2();
  return ;
}

void A2CalEventHist::SetDisplayVersion_pPb2016(){
  f_DisplayVersion = VERSION_PPB2016;
  
  // For GPIO Flags (LHCFLOGIC)
  for(int i=0;i<16;i++){
    char text[20];
    if(i==0)  {strcpy(text,"BPTX1");}
    if(i==1)  {strcpy(text,"BPTX2");}
    if(i==2)  {strcpy(text,"EXT_L1T");}
    if(i==3)  {strcpy(text,"B1&B2");}
    if(i==4)  {strcpy(text,"L2TSHW");}
    if(i==5)  {strcpy(text,"L2TPEDE");}
    if(i==6)  {strcpy(text,"L2TEXT");}
    if(i==7)  {strcpy(text,"L2TSPE1");} 
    if(i==8)  {strcpy(text,"L2TL1T");}
    if(i==9)  {strcpy(text,"L2TSPE2");}
    if(i==10) {strcpy(text,"STRG");}
    if(i==11) {strcpy(text,"LTRG");}
    if(i==12) {strcpy(text,"BEAM");}
    if(i==13) {strcpy(text,"PEDE");}
    if(i==14) {strcpy(text,"LASER");}
    if(i==15) {strcpy(text,"ENABLE");}
    t_flag[0][i]->SetTitle(text);
  }
  // For GPIO Flags (LHCFCOUNTER)
  for(int i=0;i<24;i++){
    char text[20];
    if(i==0)  {strcpy(text,"    -");}
    if(i==1)  {strcpy(text,"    -");}
    if(i==2)  {strcpy(text,"    -");}
    if(i==3)  {strcpy(text,"    -");}
    if(i==4)  {strcpy(text,"A2ENA");}
    if(i==5)  {strcpy(text,"A2STR");}
    if(i==6)  {strcpy(text,"A2L3T");}
    if(i==7)  {strcpy(text,"    -");} 
    if(i==8)  {strcpy(text,"BPTX1");}
    if(i==9)  {strcpy(text,"BPTX2");}
    if(i==10) {strcpy(text,"L1A");}
    if(i==11) {strcpy(text,"    -");}
    if(i==12) {strcpy(text,"    -");}
    if(i==13) {strcpy(text,"A2_FC");}
    if(i==14) {strcpy(text,"    -");}
    if(i==15) {strcpy(text,"    -");}
    if(i==16) {strcpy(text,"    -");}
    if(i==17) {strcpy(text,"    -");}
    if(i==18) {strcpy(text,"    -");}
    if(i==19) {strcpy(text,"    -");}
    if(i==20) {strcpy(text,"A2FC0");}
    if(i==21) {strcpy(text,"A2FC1");}
    if(i==22) {strcpy(text,"A2FC2");}
    if(i==23) {strcpy(text,"A2FC3");}  
    t_flag[2][i]->SetTitle(text);
  }
  
  // GPIO Counter
  for(int i=0;i<35;i++){
    char text[20];
    if(i==0){strcpy(text,"CLK");}
    if(i==1){strcpy(text,"L1T");}
    if(i==2){strcpy(text,"BPTX_AND");}
    if(i==3){strcpy(text,"L1T_ENA");}
    if(i==4){strcpy(text,"STRG");}
    if(i==5){strcpy(text,"LTRG");}
    if(i==6){strcpy(text,"SHOWER");}
    if(i==7){strcpy(text,"SLOGIC");}
    if(i==8){strcpy(text,"LLOGIC");}
    if(i==9){strcpy(text,"L2TA/P");}
    if(i==10){strcpy(text,"L2TE/AW");}
    if(i==11){strcpy(text,"SP1/L2TSP1");}
    if(i==12){strcpy(text,"SP1/L2TSP1");}
    if(i==13){strcpy(text,"L3T");}
    if(i==14){strcpy(text,"L2TALTAS");}
    if(i==15){strcpy(text,"CLK");}
    if(i==16){strcpy(text,"ORBIT");}  
    if(i==17){strcpy(text,"ATLASL1A");}
    if(i==18){strcpy(text,"  -  ");}
    if(i==19){strcpy(text,"A2_L3T");}  
    if(i==20){strcpy(text,"  -  ");}
    if(i==21){strcpy(text,"  -  ");}
    if(i==22){strcpy(text,"  -  ");}
    if(i==23){strcpy(text,"CLK'");}
    if(i==24){strcpy(text,"BPTX1'");}
    if(i==25){strcpy(text,"BPTX2'");}
    if(i==26){strcpy(text,"CLK''");}
    if(i==27){strcpy(text,"L1A''");}
    if(i==28){strcpy(text,"SFC_0");}
    if(i==29){strcpy(text,"SFC_1");}
    if(i==30){strcpy(text,"SFC_2");}
    if(i==31){strcpy(text,"SFC_3");}
    if(i==32){strcpy(text,"FCL_OR");}
    if(i==33){strcpy(text,"FC_TRG");}
    if(i==34){strcpy(text,"FC&STRG");}
    l_cnt[i]->SetTitle(text);    
  }

  // For Scalers
  for(int ich=0;ich<16;ich++){
    char text[20];
    if(ich==0) {strcpy(text,"CLK");}
    if(ich==1) {strcpy(text,"->");}
    if(ich==2) {strcpy(text,"BPTX1");}
    if(ich==3) {strcpy(text,"->");}
    if(ich==4) {strcpy(text,"BPTX2");}
    if(ich==5) {strcpy(text,"->");}
    if(ich==6) {strcpy(text,"L3T");}
    if(ich==7) {strcpy(text,"L2TA");}
    if(ich==8) {strcpy(text,"FC2-1");}
    if(ich==9) {strcpy(text,"FC2-2");}
    if(ich==10){strcpy(text,"FC2-3");}
    if(ich==11){strcpy(text,"FC2-4");}
    if(ich==12){strcpy(text,"");}
    if(ich==13){strcpy(text,"FC2 TRG");}
    if(ich==14){strcpy(text,"(TEST1)");}
    if(ich==15){strcpy(text,"(TEST2)");}
    l_scl[ich]->SetTitle(text);
  }
  // For TDC
  for(int ich=0;ich<12;ich++){
    char text[20];
    if(ich==0) {strcpy(text,"ch0: CLK");}
    if(ich==1) {strcpy(text,"ch1: L3T");}
    if(ich==2) {strcpy(text,"ch2: BPTX1");}
    if(ich==3) {strcpy(text,"ch3: BPTX2");}
    if(ich==4) {strcpy(text,"ch4: SHOWER");}
    if(ich==5) {strcpy(text,"ch5: ATLAS L1A");}
    if(ich==6) {strcpy(text,"ch6: (LOGIC_OR)");}
    if(ich==7) {strcpy(text,"ch7: ARM2 FC");}
    if(ich==8) {strcpy(text,"ch8: 25mm OR");}
    if(ich==9) {strcpy(text,"ch9: 32mm OR");}
    if(ich==10){strcpy(text,"ch10:QDC GATE1");}
    if(ich==11){strcpy(text,"ch11:QDC GATE2");}
    l_tdc[ich]->SetTitle(text);
  } 
  
  UpdateCanvas2();
  return ;
}

#endif
