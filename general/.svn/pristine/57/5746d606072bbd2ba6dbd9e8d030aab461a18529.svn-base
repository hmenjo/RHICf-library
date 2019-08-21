#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
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
#include "gsetup.h"
using namespace std;

void print_help(){
  cout << "drawdschist --run 40000 -i hists_run40000.root  \n"
       << "Op) \n"
       << "  --nodraw/-b   : no shows the histograms \n" 
       << "  --print       : save the canvases\n"
       << endl;
}

int main(int argc,char **argv){  

  // ===  CONTROL ARGUMENTS == 
  int    run=-1;
  string histfile="";
  string printpath="";
  bool  savecanvas=false;
  
  for(int ic=0;ic<argc;ic++){ 
    string ss = argv[ic];
    if(ss=="--run"||ss=="-r"){
      run = atoi(argv[++ic]);
    }
    if(ss=="-i"){
      histfile = argv[++ic];
      strcpy(argv[ic],"");
    }   
    if(ss=="--nodraw"){
      strcpy(argv[ic],"-b");
    }
    if(ss=="--print"){
      savecanvas=true;
      if((ic+1)==argc || *(argv[ic+1])=='-'){
        printpath = "./graphs";
      }
      else{
	printpath = argv[++ic];
        strcpy(argv[ic],"");
      }
    }
    if(ss=="-h"||ss=="-help" || argc==1){
      print_help();
      return 0;
    }
  }

  if(histfile==""){
    cout << "Give the file path. " << endl;
    print_help();
    return -1;
  }

  // == INITIALIZATION ==
  TRint app("drawdschist",&argc,argv,0,0,kTRUE);
  gsetup();
  gStyle->SetTitleX(0.5);

  // == OPEN FILE ==
  TFile *file = new TFile(histfile.c_str());
  if(file->IsZombie()){
    cerr << "Cannot open " << histfile << endl;
    exit(-1);
  }
  file->cd("DscHists");

  TH1F *hcal[2][2][16][2];
  TH1F *hfc[2][4][4];

  int check=0;

  int rebin = 10;
  for(int arm=0;arm<2;arm++){
    for(int tower=0;tower<2;tower++){
      for(int layer=0;layer<16;layer++){
	check=0;
	for(int scut=0;scut<2;scut++){
	  string hname = Form("h1_a%dadc_%d_%02d_%d",arm+1,tower,layer,scut);
	  hcal[arm][tower][layer][scut] 
	    = (TH1F*) gDirectory->Get(hname.c_str());
	  if(hcal[arm][tower][layer][scut]==0) {check++; continue;}
	  hcal[arm][tower][layer][scut]->Rebin(rebin);
	}
	hcal[arm][tower][layer][1]->Divide(hcal[arm][tower][layer][0]);
      }
    }
  }

  rebin = 10;
  for(int arm=0;arm<2;arm++){
    for(int channel=0;channel<4;channel++){
      for(int scut=0;scut<2;scut++){
	string hname = Form("h1_%sfcadc_%d_%d",(arm==0?"a1":"a2"),channel,scut);
	hfc[arm][channel][scut] 
	  = (TH1F*) gDirectory->Get(hname.c_str());
	if(hfc[arm][channel][scut]==0) {check++; continue;}
	hfc[arm][channel][scut]->Rebin(rebin);
      }	
      hfc[arm][channel][2] =  (TH1F*)hfc[arm][channel][0]->Clone();
      hfc[arm][channel][3] =  (TH1F*)hfc[arm][channel][1]->Clone();
      hfc[arm][channel][1]->Divide(hfc[arm][channel][0]);
    }
  }
  

  // ===== Draw =====
  // Calorimters
  for(int arm=0;arm<2;arm++){
    for(int tower=0;tower<2;tower++){
      TCanvas *c = new TCanvas(Form("ccal%d",arm*2+tower),"",1000,800);
      c->Divide(4,4,0.001,0.001); 
      for(int layer=0;layer<16;layer++){
	c->cd(layer+1);
	hcal[arm][tower][layer][1]->SetLineColor(kRed);
	hcal[arm][tower][layer][1]->SetXTitle("NRADC");
	hcal[arm][tower][layer][1]->SetYTitle("Efficiency");	
	hcal[arm][tower][layer][1]->Draw("");
      }
      c->Update();
      if(savecanvas){
	string printname;
	printname = Form("%s/run%05d_dsc_%s_cal%d.gif",
			 printpath.c_str(),run,(arm==0?"a1":"a2"),tower);
	c->Print(printname.c_str());
      }
    }
  }
  // FC's
  TCanvas *c = new TCanvas("cfc","",1000,800);
  c->Divide(4,4,0.001,0.001); 
  for(int arm=0;arm<2;arm++){
    for(int channel=0;channel<4;channel++){
      c->cd(arm*4+channel+1);
      hfc[arm][channel][2]->SetXTitle("NRADC");
      hfc[arm][channel][2]->SetYTitle("Events"); 
      hfc[arm][channel][2]->SetLineColor(kBlack);
      hfc[arm][channel][3]->SetLineColor(kRed); 
      hfc[arm][channel][2]->GetXaxis()->SetNdivisions(508);
      hfc[arm][channel][2]->Draw("");
      hfc[arm][channel][3]->Draw("same");

      c->cd(8+arm*4+channel+1);
      hfc[arm][channel][1]->SetLineColor(kRed);
      hfc[arm][channel][1]->SetXTitle("NRADC");
      hfc[arm][channel][1]->SetYTitle("Efficiency");   
      hfc[arm][channel][1]->GetXaxis()->SetNdivisions(508);
      hfc[arm][channel][1]->Draw("");
    }
  }

  c->Update();
  if(savecanvas){
    string printname;
    printname = Form("%s/run%05d_dsc_fc.gif",printpath.c_str(),run);
    c->Print(printname.c_str());
  }  

  // == Run ==
  app.Run();
  return 0;
}
  
