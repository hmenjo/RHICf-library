#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <TROOT.h>
#include <TRint.h>
#include <TApplication.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "A1CalEventHist.h"
#include "A2CalEventHist.h"
#include "A1PedeSubtract.h"
#include "A2PedeSubtract.h"
#include "gsetup.h"
using namespace std;


int main(int argc,char **argv){  
  gsetup();
  gStyle->SetTitleX(0.05);
  gStyle->SetTitleW(0.7);

  char  pedefile[256]; 
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  int   run = -1;
  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-i")==0){
      strcpy(pedefile,argv[++ic]);
      strcpy(argv[ic],"");
    } 
    if(strcmp(argv[ic],"-print")==0){
      savecanvas=true;
      if((ic+1)==argc || *(argv[ic+1])=='-'){
	strcpy(printpath,"./graphs");
      }
      else{
	strcpy(printpath,argv[++ic]);  
	strcpy(argv[ic],"");
      }
    }  
    if(strcmp(argv[ic],"-run")==0){
      run = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
	   << " drawpede ----------------------------------------\n"
	   << "   -i           :  pedestal file\n"
	   << "  -print [path] :  Save Canvases\n" 
	   << "  -run          :  run number for canvas name\n"
	   << "  -q,-b,        :  ROOT default options. \n"
	   << endl;
      exit(0);
    }
  }
  
  if(strcmp(pedefile,"")==0){
    cerr << "Error: Give a filename." << endl;
    exit(-1);
  }

  TRint app("drawpede",&argc,argv,0,0,kTRUE);

  // ++++ OPEN PEDESTAL FILE ++++++++++++++++++++++++

  A1PedeSubtract *a1pedesubtract = new A1PedeSubtract();
  a1pedesubtract->ReadFile(pedefile);
  A2PedeSubtract *a2pedesubtract = new A2PedeSubtract();
  a2pedesubtract->ReadFile(pedefile);

  
  // ++++ INITIALIZE HISTOGRAMS +++++++++++++++++++++

  TH1F* h1calav[4];
  TH1F* h1calsav[4];
  TH1F* h1calrms[4];
  TH1F* h1calsrms[4];
  char ch_run[20]="";
  char ch_tower[20];
  char name[256]; 
  char title[256];  
  for(int it=0;it<4;it++){
    if(run > 0){sprintf(ch_run,"run%05d: ",run);}
    if(it==0){strcpy(ch_tower,"20mm");}
    if(it==1){strcpy(ch_tower,"40mm");}
    if(it==2){strcpy(ch_tower,"25mm");}
    if(it==3){strcpy(ch_tower,"32mm");}
    
    sprintf(name,"h1calav_%d",it);
    sprintf(title,"%s%s Pede Av.",ch_run,ch_tower);
    h1calav[it] = new TH1F(name,title,16,0,16);
    sprintf(name,"h1caldav_%d",it);   
    sprintf(title,"%s%s Pede-delay Av.",ch_run,ch_tower);
    h1calsav[it] = new TH1F(name,title,16,0,16); 
    sprintf(name,"h1calrms_%d",it);
    sprintf(title,"%s%s Pede. RMS",ch_run,ch_tower);
    h1calrms[it] = new TH1F(name,title,16,0,16);
    sprintf(name,"h1calsrms_%d",it);   
    sprintf(title,"%s%s Pede. RMS",ch_run,ch_tower);
    h1calsrms[it] = new TH1F(name,title,16,0,16);
  }

  for(int i=0;i<16;i++){
    h1calav[0]->SetBinContent(i+1,a1pedesubtract->GetPedestal()->cal[0][i][0]);
    h1calav[1]->SetBinContent(i+1,a1pedesubtract->GetPedestal()->cal[1][i][0]);
    h1calav[2]->SetBinContent(i+1,a2pedesubtract->GetPedestal()->cal[0][i][0]);
    h1calav[3]->SetBinContent(i+1,a2pedesubtract->GetPedestal()->cal[1][i][0]); 
    
    h1calsav[0]->SetBinContent(i+1,a1pedesubtract->GetPedestal2()->cal[0][i][0]);
    h1calsav[1]->SetBinContent(i+1,a1pedesubtract->GetPedestal2()->cal[1][i][0]);
    h1calsav[2]->SetBinContent(i+1,a2pedesubtract->GetPedestal2()->cal[0][i][0]);
    h1calsav[3]->SetBinContent(i+1,a2pedesubtract->GetPedestal2()->cal[1][i][0]); 

    h1calrms[0]->SetBinContent(i+1,a1pedesubtract->GetPedesigma()->cal[0][i][0]);
    h1calrms[1]->SetBinContent(i+1,a1pedesubtract->GetPedesigma()->cal[1][i][0]);
    h1calrms[2]->SetBinContent(i+1,a2pedesubtract->GetPedesigma()->cal[0][i][0]);
    h1calrms[3]->SetBinContent(i+1,a2pedesubtract->GetPedesigma()->cal[1][i][0]);  
  
    h1calsrms[0]->SetBinContent(i+1,a1pedesubtract->GetPedesigma2()->cal[0][i][0]);
    h1calsrms[1]->SetBinContent(i+1,a1pedesubtract->GetPedesigma2()->cal[1][i][0]);
    h1calsrms[2]->SetBinContent(i+1,a2pedesubtract->GetPedesigma2()->cal[0][i][0]);
    h1calsrms[3]->SetBinContent(i+1,a2pedesubtract->GetPedesigma2()->cal[1][i][0]);  
  }  
  
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadLeftMargin(0.18); 
  TCanvas *c_av = new TCanvas("c_av","Cal. Average",800,800);
  c_av->Divide(2,4);
  for(int it=0;it<4;it++){
    c_av->cd(2*it+1);
    gPad->SetGridx();
    gPad->SetGridy();
    h1calav[it]->Draw();
    h1calav[it]->SetXTitle("Layer");
    h1calav[it]->SetYTitle("Pedestal Average");
    h1calav[it]->GetXaxis()->SetTitleSize(0.07);
    h1calav[it]->GetYaxis()->SetTitleSize(0.07);
    h1calav[it]->GetXaxis()->SetLabelSize(0.06);
    h1calav[it]->GetYaxis()->SetLabelSize(0.06);
    h1calav[it]->GetYaxis()->SetNdivisions(505);
    
    c_av->cd(2*it+2);
    gPad->SetGridx();
    gPad->SetGridy();
    h1calsav[it]->Draw();
    h1calsav[it]->SetXTitle("Layer");
    h1calsav[it]->SetYTitle("Pedestal Average");
    h1calsav[it]->GetXaxis()->SetTitleSize(0.07);
    h1calsav[it]->GetYaxis()->SetTitleSize(0.07);
    h1calsav[it]->GetXaxis()->SetLabelSize(0.06);
    h1calsav[it]->GetYaxis()->SetLabelSize(0.06);
    h1calsav[it]->GetYaxis()->SetNdivisions(505);
    h1calsav[it]->SetMaximum(20);
    h1calsav[it]->SetMinimum(-20); 
  }
  c_av->Update();

  
  TLegend *legend = new TLegend();
  TCanvas *c_rms = new TCanvas("c_rms","Cal. RMS",400,800);
  c_rms->Divide(1,4);
  for(int it=0;it<4;it++){
    c_rms->cd(it+1);
    gPad->SetGridx();
    gPad->SetGridy();
    h1calrms[it]->Draw();
    h1calsrms[it]->Draw("same");  
    h1calrms[it]->SetXTitle("Layer");
    h1calrms[it]->SetYTitle("Pedestal RMS");
    h1calrms[it]->GetXaxis()->SetTitleSize(0.07);
    h1calrms[it]->GetYaxis()->SetTitleSize(0.07);
    h1calrms[it]->GetXaxis()->SetLabelSize(0.06);
    h1calrms[it]->GetYaxis()->SetLabelSize(0.06); 
    h1calrms[it]->GetYaxis()->SetNdivisions(505);
    h1calrms[it]->SetMaximum(80);
    h1calrms[it]->SetMinimum(0);  
    
    h1calrms[it]->SetLineColor(kBlue);
    h1calsrms[it]->SetLineColor(kRed);

    legend = new TLegend(0.75,0.8,0.99,1.0);
    legend->SetFillColor(kWhite);
    legend->AddEntry(h1calrms[it],"Raw","l");
    legend->AddEntry(h1calsrms[it],"Sub.","l");  
    legend->Draw();
  }
  c_rms->Update();
  
  char printname[256];
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%scalpede_average.gif",printpath,ch_run);
    c_av->Print(printname);
    sprintf(printname,"%s/%scalpede_rms.gif",printpath,ch_run);
    c_rms->Print(printname);
  }

  
  // ++++ SCIFI ++++++++++++++++++++++++++++++++++++++++++++++++
  if(run > 0){ sprintf(title,"Mean of Pedestal: RUN%05d",run); }
  else       { sprintf(title,"Mean of Pedestal");}
  A1CalEventHist* a1evhist_pede
    = new A1CalEventHist("a1pede", title); 
  a1evhist_pede->Initialize();
  a1evhist_pede->Fill(a1pedesubtract->GetPedestal());
  a1evhist_pede->DrawCanvas3();

  if(run > 0){ sprintf(title,"RMS of Pedestal: RUN%05d",run);}
  else       { sprintf(title,"RMS of Pedestal"); }
  A1CalEventHist* a1evhist_rms
    = new A1CalEventHist("a1evhist_rms",title);
  a1evhist_rms->Initialize();
  a1evhist_rms->Fill(a1pedesubtract->GetPedesigma());
  a1evhist_rms->DrawCanvas3();
  a1evhist_rms->SetCanvas3YRange(0,10);

  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%sscifipede_average.gif",printpath,ch_run);
    a1evhist_pede->c3->Print(printname);
    sprintf(printname,"%s/%sscifipede_rms.gif",printpath,ch_run);
    a1evhist_rms->c3->Print(printname);
  }

  // ++++ SILICON ++++++++++++++++++++++++++++++++++++++++++++++
  if(run > 0){ sprintf(title,"Mean of Pedestal: RUN%05d",run); }
  else       { sprintf(title,"Mean of Pedestal");}
  A2CalEventHist* a2evhist_pede
    = new A2CalEventHist("a2pede", title); 
  a2evhist_pede->Initialize();
  a2evhist_pede->Fill(a2pedesubtract->GetPedestal());
  a2evhist_pede->SetHistColor(3);
  a2evhist_pede->DrawCanvas3();
  //a2evhist_pede->SetCanvas3YRange(1400.,1700.);
  

  if(run > 0){ sprintf(title,"RMS of Pedestal: RUN%05d",run);}
  else       { sprintf(title,"RMS of Pedestal"); }
  A2CalEventHist* a2evhist_rms
    = new A2CalEventHist("a2evhist_rms",title);
  a2evhist_rms->Initialize();
  a2evhist_rms->Fill(a2pedesubtract->GetPedesigma());
  a2evhist_rms->SetHistColor(3);
  a2evhist_rms->DrawCanvas3();
  a2evhist_rms->SetCanvas3YRange(0,5);
  
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%ssipede_average.gif",printpath,ch_run);
    a2evhist_pede->c3->Print(printname);
    sprintf(printname,"%s/%ssipede_rms.gif",printpath,ch_run);
    a2evhist_rms->c3->Print(printname);
  }

  app.Run();
  
  return 0;
  
}
