#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TFile.h>
#include <TLatex.h>
#include "LHCfEvent.h"
#include "A2Cal1AccumHist.h"
#include "gsetup.h"
using namespace std;

int main(int argc,char **argv){ 
  int tmp=1;
  TApplication app("adchists",&tmp,argv);
  
  int    adcrange=0;
  int    nfile=0;
  string filename[10];
  double scale[10];
  bool   autoscale=false;
  int    dataid=0;   // 0: all, 1: beam, 2: pede

  for(int i=0;i<10;i++){scale[i]=1.0;}

  for(int ic=0;ic<argc;ic++){ 
    if(strcmp(argv[ic],"-i")==0){
      filename[nfile] = argv[++ic];
      if(ic+1<argc && argv[ic+1][0]!='-'){
	scale[nfile] = atof(argv[++ic]);
      }
      nfile++;
      if(nfile>10){nfile=10;}
    }
    if(strcmp(argv[ic],"-autoscale")==0){
      autoscale = true;
    }
    if(strcmp(argv[ic],"-High")==0){
      adcrange = 1;
    }
    if(strcmp(argv[ic],"-Low")==0){
      adcrange = 0;
    }
    if(strcmp(argv[ic],"-drawall")==0){
      dataid = 0;
    }
    if(strcmp(argv[ic],"-drawbeam")==0){
      dataid = 1;
    }  
    if(strcmp(argv[ic],"-drawpede")==0){
      dataid = 1;
    }     
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
	   << " comphists_arm2 ------------------------------------------------------ \n"
	   << "  Draw some histograms made by adchists_arm2 in same canvas \n"
	   << "  to compare the histograms.\n" 
	   << "  Edited by H.MENJO\n"
	   << " \n" 
	   << " command) \n"
	   << " ./comphists_arm1 -i file0 -i file1 (scale_value1) -i file2 (scale_value2)\n" 
	   << "            [-drawall] [-drawbeam] [-drawpede] [-High] [-Low]\n"
	   << "\n"
	   << " options) \n"
	   << "  -i     :  Histogram file made by adchists_arm2.\n"
	   << "            if value is given at next of filename, the histogram is scaled\n" 
	   << "            -i filename scale [Max. 10 files]\n"
	   << "  -autoscale : Scale values are set automatically." 
	   << "  -drawall   : Draw histograms for all events. [default]\n"
	   << "  -drawbeam  : Draw histograms for BEAM or LASER events.\n"
	   << "  -drawpede  : Draw histograms for PEDE events.\n" 
	   << "  -Low   :  Draw histograms of Low range ADC counts [default]\n"
	   << "  -High  :  Draw histograms of High range ADC counts\n"
	   << endl;
	return 0;
    }
  }

  bool   check=false;
  bool   ch[10];
  TFile *file[10];
  int    run[10]; 
  double nev[10] = {0.};
  string sfilename[10];
  A2Cal1AccumHist* a2hist[10];

  for(int i=0;i<10;i++) ch[i] = false;

  char   dataname[16];
  if(dataid==0) strcpy(dataname,"a2hist_all");
  if(dataid==1) strcpy(dataname,"a2hist_beam");
  if(dataid==2) strcpy(dataname,"a2hist_pede"); 
  
  unsigned long itmp;
  string stmp;
  double base_nev = -1.;
  for(int i=0;i<nfile;i++){
    file[i] = new TFile(filename[i].c_str());
    gROOT->cd();
    if(file[i]->IsZombie()){
      cerr << "FILE" << i << " : Cannot open " << filename[i] << endl;
      ch[i] = false;
      continue;
    }
    a2hist[i] = (A2Cal1AccumHist*) file[i]->Get(dataname);
    if(a2hist[i]==NULL){
      cerr << "FILE" << i << " : No data in " << filename[i] << endl; 
      ch[i] = false;
      file[i]->Close();
      continue;
    } 

    
    itmp = filename[i].rfind("/");
    if(itmp==string::npos){
      sfilename[i] = filename[i];
    }
    else {
      sfilename[i] = filename[i].substr(itmp+1);
    }
    
    stmp = a2hist[i]->GetTitle();
    run[i] = atoi(stmp.substr(3,5).c_str());
    nev[i] = a2hist[i]->hist_cal[0][0][0]->GetEntries();
    if(base_nev<0){base_nev = nev[i];}
    if(autoscale && nev[i]>0){ scale[i] = base_nev/nev[i];}
    
    cout << "FILE" << i << " : ";
    cout << setfill('0');
    cout << "RUN" << setw(5) << run[i] << "  ";
    cout << setfill(' ');
    cout << "#EV " << setw(6) << (int)nev[i] << "  ";
    cout << showpoint;
    cout << "SCLAE" << setprecision(3) << setw(5) << scale[i] << "  ";
    cout << noshowpoint;
    cout << "File: " << sfilename[i] 
	 << endl;
    ch[i] = true;
    check = true;
  }
  
  if(!check){
    cerr << endl 
	 << " No data in the given files" << endl
	 << endl;
    return -1;
  }
  
  // +++++ DRAW ++++++  
  gsetup();
  gStyle->SetOptStat(0);
  gStyle->SetTitleX(0.01);
  gStyle->SetTitleW(0.9);
  
  A2Cal1AccumHist* canvas = new A2Cal1AccumHist();
  canvas->InitializeCanvases();
  
  Color_t color[10] = {kBlack, kRed, kBlue, kGreen, kMagenta,
		       kYellow, kMagenta, kCyan, kViolet, kOrange};
  bool checksame = false;
  for(int i=0;i<nfile;i++){
    if(!ch[i]) { continue; }
    
    a2hist[i]->SetCanvasCal0(canvas->GetCanvasCal0());
    a2hist[i]->SetCanvasCal1(canvas->GetCanvasCal1());
    a2hist[i]->SetCanvasADCs(canvas->GetCanvasADCs());
    a2hist[i]->SetCanvasFlag(canvas->GetCanvasFlag());
    
    a2hist[i]->SetLineColor(color[i]);
    a2hist[i]->SetFillStyle(0);
    a2hist[i]->Scale(scale[i]);
    a2hist[i]->Draw(adcrange, checksame ? "same" : "");
    checksame = true;
  }
  
  TCanvas *c_panel = new TCanvas("c_panel","Lines",800,600,250,300);
  TLine  *line = new TLine();
  TLatex *tex  = new TLatex();
  tex->SetTextSize(0.065);
  char label[100];
  for(int i=0;i<nfile;i++){
    if(!ch[i]) { continue; } 
    line->SetLineWidth(2);
    line->SetLineColor(color[i]);
    line->DrawLineNDC(0.05,0.95-0.09*i,0.15,0.95-0.09*i);
    sprintf(label,"RUN%05d %s",run[i],sfilename[i].c_str());
    tex->DrawTextNDC(0.18,0.93-0.09*i,label);
  }
  
  c_panel->Update();
  
  app.Run();
  
  return 0;
}
