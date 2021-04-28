#ifndef __RAWL1TDRAW_CPP__
#define __RAWL1TDRAW_CPP__


#include "RawL1TDraw.h"

#include <iostream>
#include <iomanip>
using namespace std;

int  RawL1TDraw::icall = 0;

RawL1TDraw::RawL1TDraw(){
  sprintf(cname,"cRawL1TDraw_%d",icall);
  icall++; 
  f_DisplayVersion = VERSION_PP2010;
  canvas = NULL;
  for(int i=0;i<4;i++){ t_header[i] = NULL; }
  for(int i=0;i<cNcounts;i++){
    l_counts[i] = NULL; 
    t_counts[i] = NULL; 
  }
}

RawL1TDraw::~RawL1TDraw(){;}

int RawL1TDraw::Initialize(){
  double x,y;
  char  text[20];
  for(int i=0;i<4;i++){
    strcpy(text,"-");
    x = 0.12;
    y = 0.84 - 0.08*i;
    t_header[i] = new TText(x,y,text); 
    t_header[i]->SetTextSize(0.080);
    t_header[i]->SetTextFont(102);
  }
  
  for(int i=0;i<14;i++){
    strcpy(text,"-");
    x = 0.01 + 0.12*(i%8);
    y = 0.51 - 0.20*(i/8) - 0.09;
    t_counts[i] = new TText(x,y,text); 
    t_counts[i]->SetTextSize(0.080);
    t_counts[i]->SetTextFont(102);
  } 
  return 0;
}

int RawL1TDraw::Delete(Option_t* option ){
  for(int i=0;i<4;i++){
    if(t_header[i]) delete t_header[i];
  }
  for(int i=0;i<14;i++){
    if(t_counts[i]) delete t_counts[i];
  }
  return 0;
}

int  RawL1TDraw::Fill(RawL1T *d){
  unsigned int ivalue = 0;
  char text[20];
  for(int i=0;i<4;i++){
    if(i==0) ivalue = d->run;
    if(i==1) ivalue = d->gnumber;
    if(i==2) ivalue = d->number;  
    if(i==3) ivalue = d->time[0];
    sprintf(text,"%8d",ivalue);
    t_header[i]->SetTitle(text);
  }
  
  for(int i=0;i<14;i++){
    sprintf(text,"%8u",d->gpio2[i]);
    t_counts[i]->SetTitle(text);
  }
  return 0;
}

int  RawL1TDraw::Reset(){
  for(int i=0;i<4;i++) {t_header[i]->SetTitle("");}
  for(int i=0;i<14;i++){t_counts[i]->SetTitle("");}
  return 0;
}

int RawL1TDraw::SetDisplayFormat(DISPLAY_VERSION version){
  switch (version){
  case VERSION_PP2010 :
    SetDisplayVersion_pp2010();
    return 0;
  case VERSION_PPB2013 :
    SetDisplayVersion_pPb2013();
    return 0;
  default :
    cerr << "[A2CalEventHist::SetDisplayFormat]" << " Unknown Format" << endl;
    return -1;
  }
  return -1;
}

void RawL1TDraw::SetDisplayVersion_pp2010(){
  f_DisplayVersion = VERSION_PP2010;
  if(l_counts[0]){l_counts[0]->SetTitle("BPTX1");}
  if(l_counts[1]){l_counts[1]->SetTitle("BPTX2");}
  if(l_counts[2]){l_counts[2]->SetTitle("B1&B2");}
  if(l_counts[3]){l_counts[3]->SetTitle("B1&B2+DIS");}
  if(l_counts[4]){l_counts[4]->SetTitle("A1_L1T");}
  if(l_counts[5]){l_counts[5]->SetTitle("A2_L1T");}
  if(l_counts[6]){l_counts[6]->SetTitle("A1_L1T_ENA");}
  if(l_counts[7]){l_counts[7]->SetTitle("A2_L1T_ENA");}
  if(l_counts[8]){l_counts[8]->SetTitle("A1_LASER");}
  if(l_counts[9]){l_counts[9]->SetTitle("A2_LASER");}
  if(l_counts[10]){l_counts[10]->SetTitle("A1_L2TEXT");}
  if(l_counts[11]){l_counts[11]->SetTitle("A1_L2TEXT_ENA");}
  if(l_counts[12]){l_counts[12]->SetTitle("A2_L2TEXT");}
  if(l_counts[13]){l_counts[13]->SetTitle("A2_L2TEXT_ENA");}
}

void RawL1TDraw::SetDisplayVersion_pPb2013(){
  f_DisplayVersion = VERSION_PPB2013;
  if(l_counts[0]){l_counts[0]->SetTitle("BPTX1");}
  if(l_counts[1]){l_counts[1]->SetTitle("BPTX2");}
  if(l_counts[2]){l_counts[2]->SetTitle("B1&B2");}
  if(l_counts[3]){l_counts[3]->SetTitle("B1&B2+DIS");}
  if(l_counts[4]){l_counts[4]->SetTitle("A1_L1T_WOPRE");}
  if(l_counts[5]){l_counts[5]->SetTitle("A2_L1T");}
  if(l_counts[6]){l_counts[6]->SetTitle("-");}
  if(l_counts[7]){l_counts[7]->SetTitle("A2_L1T_ENA");}
  if(l_counts[8]){l_counts[8]->SetTitle("-");}
  if(l_counts[9]){l_counts[9]->SetTitle("A2_LASER");}
  if(l_counts[10]){l_counts[10]->SetTitle("-");}
  if(l_counts[11]){l_counts[11]->SetTitle("-");}
  if(l_counts[12]){l_counts[12]->SetTitle("-");}
  if(l_counts[13]){l_counts[13]->SetTitle("-");}
}

void RawL1TDraw::SetCanvas(TCanvas* c){
  if(canvas) delete canvas;
  canvas = c;
}

int  RawL1TDraw::DrawCanvas(){
  if(!canvas){
    canvas = new TCanvas(cname,cname,600,300);
  }
  canvas->cd();
  
  double x,y;
  char   text[256];
  TText *ltext;
  
  ltext = new TText(0.01,0.92,"RawL1T");
  ltext->SetTextSize(0.090);
  ltext->Draw();
  
  for(int i=0;i<4;i++){
    if(i==0) strcpy(text,"RUN");
    if(i==1) strcpy(text,"GNUMBER");
    if(i==2) strcpy(text,"NUMBER"); 
    if(i==3) strcpy(text,"TIME");  
    x = 0.01;
    y = 0.84 - 0.08*i;
    ltext = new TText(x,y,text);
    ltext->SetTextSize(0.080);
    ltext->SetTextFont(102);
    ltext->Draw();
    t_header[i]->Draw();
  }
  
  for(int i=0;i<cNcounts;i++){
    x = 0.01 + 0.12*(i%8);
    y = 0.51 - 0.20*(i/8);
    l_counts[i] = new TText(x,y,"");
    l_counts[i]->SetTextSize(0.080);
    l_counts[i]->SetTextFont(102);
    l_counts[i]->SetTextColor(kGray+3);
    l_counts[i]->Draw();
    t_counts[i]->Draw();
  } 
  SetDisplayFormat(f_DisplayVersion);
    
  canvas->Update();
  return 0;
}

int  RawL1TDraw::UpdateCanvas(){
  canvas->Modified();
  canvas->Update(); 
  return 0;
}

int  RawL1TDraw::ClearCanvas(){
  canvas->Clear();  
  return 0;
}

#endif
