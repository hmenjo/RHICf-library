#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <TROOT.h>
#include <TRint.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include "A1Cal1AccumHist.h"
#include "A2Cal1AccumHist.h"
#include "gsetup.h"
using namespace std;

int main(int argc,char **argv){  
  gsetup();
  gStyle->SetTitleX(0.05);
  gStyle->SetTitleW(0.7);
  
  // ++++++++ Manage optioons +++++++++++++++++++++++++++++ 
  char  histfile[256]="";
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  int   run=-1;

  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-i")==0){
      strcpy(histfile,argv[++ic]);
      strcpy(argv[ic],"");
    }
    if(strcmp(argv[ic],"-nodraw")==0){
      strcpy(argv[ic],"-b");
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
	   << " drawbeamconfig ---------------------------------------------------------- \n"
	   << "  -i            :  Histogram file\n"
	   << "  -nodraw       :  Not draw any histograms. \n" 
	   << "  -print [path] :  Save Canvases\n" 
	   << "  -run          :  run number for canvas name\n"
	   << "  -q,-b,        :  ROOT options. \n"
	   << endl;
      return 0;
    }
  }
  
  if(strcmp(histfile,"")==0){
    cerr << "Error: Give a filename." << endl;
    exit(-1);
  }
  
  TRint app("drawbeamconfig",&argc,argv,0,0,kTRUE);
  
  // ++++ Open histograms ++++++++++++++++++++++++++++++++ 
  TFile *file = new TFile(histfile);
  if(file->IsZombie()){
    cerr << "Cannot open " << histfile << endl;
    exit(-1);
  }
 
  TH1F* hbconf_a1_all  = (TH1F*) file->Get("hbconf_a1_all");
  TH1F* hbconf_a1_l2ta = (TH1F*) file->Get("hbconf_a1_l2ta");
  TH1F* hbconf_a2_all  = (TH1F*) file->Get("hbconf_a2_all");  
  TH1F* hbconf_a2_l2ta = (TH1F*) file->Get("hbconf_a2_l2ta"); 
  TH1F* hbconf_a1_bptx1 = (TH1F*) file->Get("hbconf_a1_bptx1");
  TH1F* hbconf_a1_bptx2 = (TH1F*) file->Get("hbconf_a1_bptx2");
  TH1F* hbconf_a2_bptx1 = (TH1F*) file->Get("hbconf_a2_bptx1"); 
  TH1F* hbconf_a2_bptx2 = (TH1F*) file->Get("hbconf_a2_bptx2"); 

  // +++++++++ DRAW ++++++++++++++++++++++++++++++++++++
  TH1F* hwaku;
  char title[256];
  TCanvas *c = new TCanvas("c","",800,700);
  TPad* cpad1 = new TPad("cpad1","",0.0,0.0,0.6,1.0);
  cpad1->Draw();
  cpad1->Divide(1,2,0.001,0.001);
  cpad1->cd(2);
  gPad->SetLogy();
  gPad->SetGridx();  
  gPad->SetGridy(); 
  hbconf_a1_all->SetMinimum(0.1);
  hbconf_a1_all->SetLineColor(kBlack); 
  hbconf_a1_all->SetFillColor(kBlack);
  hbconf_a1_all->Draw();
  hbconf_a1_bptx1->SetLineColor(kBlue);
  hbconf_a1_bptx1->SetFillColor(kBlue);
  hbconf_a1_bptx1->Draw("same");  
  hbconf_a1_l2ta->SetLineColor(kRed); 
  hbconf_a1_l2ta->SetFillColor(kRed);
  hbconf_a1_l2ta->Draw("same");
  hwaku = hbconf_a1_all;
  if(run>0){sprintf(title,"RUN%05d: Bunch config of Arm1 (BPTX2)",run);}
  else{sprintf(title,"Bunch config of Arm1 (BPTX2)");}
  hwaku->SetTitle(title);
  hwaku->SetXTitle("#Bunch");
  hwaku->SetYTitle("Events");
  hwaku->GetXaxis()->SetNdivisions(505); 
  hwaku->GetYaxis()->SetTitleSize(0.06);
  hwaku->GetYaxis()->SetTitleOffset(1.0);
  TLegend *legend1 = new TLegend(0.8,0.86,0.99,0.99);
  legend1->SetFillColor(kWhite);
  legend1->AddEntry(hbconf_a1_all,"ALL","l");
  legend1->AddEntry(hbconf_a1_l2ta,"L2TA","l");
  legend1->Draw();

  cpad1->cd(1);
  gPad->SetLogy(); 
  gPad->SetGridx(); 
  gPad->SetGridy(); 
  hbconf_a2_all->SetMinimum(0.1); 
  hbconf_a2_all->SetLineColor(kBlue); 
  hbconf_a2_all->SetFillColor(kBlue);
  hbconf_a2_all->Draw(); 
  hbconf_a2_bptx1->SetLineColor(kBlue);
  hbconf_a2_bptx1->SetFillColor(kBlue);
  hbconf_a2_bptx1->Draw("same");  
  hbconf_a2_l2ta->SetLineColor(kRed); 
  hbconf_a2_l2ta->SetFillColor(kRed);
  hbconf_a2_l2ta->Draw("same"); 
  hwaku = hbconf_a2_all; 
  if(run>0){sprintf(title,"RUN%05d: Bunch config of Arm2 (BPTX1)",run);}
  else{sprintf(title,"Bunch config of Arm2 (BPTX1)");}
  hwaku->SetTitle(title);
  hwaku->SetXTitle("#Bunch"); 
  hwaku->SetYTitle("Events"); 
  hwaku->GetXaxis()->SetNdivisions(505);
  hwaku->GetYaxis()->SetTitleSize(0.06); 
  hwaku->GetYaxis()->SetTitleOffset(1.0);
  TLegend *legend2 = new TLegend(0.8,0.86,0.99,0.99);
  legend2->SetFillColor(kWhite);
  legend2->AddEntry(hbconf_a2_all,"ALL","l");
  legend2->AddEntry(hbconf_a2_l2ta,"L2TA","l");
  legend2->Draw();
  cpad1->Update();

  c->cd();
  TPad* cpad2 = new TPad("cpad2","",0.6,0.0,1.0,1.0);
  cpad2->Draw();
  cpad2->cd();
  char value[256];
  int total_nfill =0;
  int arm1_nfill = 0, arm2_nfill = 0;

  const int boffset = -176; 
  double x_t = 0.1;
  double x_a2  = 0.25;
  double x_a2b = 0.35;
  double x_a1  = 0.6;
  double x_a1b = 0.70;
  double y;
  TLatex *latex = new TLatex(); 
  latex->SetTextSize(0.05);
  latex->DrawTextNDC(0.6,0.94,"ARM1(BPTX2)");
  latex->DrawTextNDC(0.2,0.94,"ARM2(BPTX1)");
  latex->SetTextSize(0.04);
  latex->DrawTextNDC(0.05,0.92, "#TOTAL");
  latex->DrawTextNDC(0.25,0.92, "#B1");
  latex->DrawTextNDC(0.35,0.92,"#CLK");
  latex->DrawTextNDC(0.6,0.92, "#B2");
  latex->DrawTextNDC(0.70,0.92,"#CLK");  
  for(int i=1;i<hbconf_a1_bptx2->GetNbinsX();i++){
    y = 0.9-0.021*total_nfill;
    if(hbconf_a1_bptx2->GetBinContent(i)>0.1 &&
       hbconf_a2_bptx1->GetBinContent(i)>0.1 ){
      sprintf(value,"%d",total_nfill++);
      latex->DrawTextNDC(x_t,y,value);
      sprintf(value,"%d",arm1_nfill++);
      latex->DrawTextNDC(x_a1,y,value);
      sprintf(value,"%d",i+boffset);
      latex->DrawTextNDC(x_a1b,y,value);
      sprintf(value,"%d",arm2_nfill++);
      latex->DrawTextNDC(x_a2,y,value);
      sprintf(value,"%d",i+boffset);
      latex->DrawTextNDC(x_a2b,y,value);
    }
    else if(hbconf_a1_bptx2->GetBinContent(i)>0.1){
       sprintf(value,"%d",total_nfill++);
      latex->DrawTextNDC(x_t,y,value);
      sprintf(value,"%d",arm1_nfill++);
      latex->DrawTextNDC(x_a1,y,value);
      sprintf(value,"%d",i+boffset);
      latex->DrawTextNDC(x_a1b,y,value);
    }
    else if(hbconf_a2_bptx1->GetBinContent(i)>0.1 ){
      sprintf(value,"%d",total_nfill++);
      latex->DrawTextNDC(x_t,y,value);
      latex->DrawTextNDC(x_a1,y, "");
      latex->DrawTextNDC(x_a1b,y,"");
      sprintf(value,"%d",arm2_nfill++);
      latex->DrawTextNDC(x_a2,y,value);
      sprintf(value,"%d",i+boffset);
      latex->DrawTextNDC(x_a2b,y,value);
    }
    if(total_nfill>45){
      latex->DrawTextNDC(x_t,y,"and more...");
    }
  }
  
  sprintf(value,"OFFSET= %d",boffset);
  latex->DrawTextNDC(0.4,0.01,value);



  // ++++++++ SAVE CANVASES ++++++++++++++++++++++++++++++++++++
  char ch_run[20]="";
  char printname[256];
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%sbeamconfig.gif",printpath,ch_run);
    c->Print(printname);
  }

  app.Run();
  
  return 0;
}
  
  
  
