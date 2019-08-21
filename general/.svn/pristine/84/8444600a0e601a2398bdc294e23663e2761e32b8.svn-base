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
#include "A2CalEventHist.h"
#include "RawL1TDraw.h"
#include "SclL1T.h"
#include "LHCfRunInfoTable.h"
#include "gsetup.h"
using namespace std;

char* GetChar(const char* format,int val);
char* GetChar(const char* format,double val);

int main(int argc,char **argv){
  gsetup();

  // ++++++++ Manage optioons +++++++++++++++++++++++++++++
  char  datafile[256]="";
  char  runinfofile[256]="";
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  int   run=-1;

  for(int ic=0;ic<argc;ic++){
    if(strcmp(argv[ic],"-i")==0){
      strcpy(datafile,argv[++ic]);
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
    if(strcmp(argv[ic],"-runinfo")==0){
      strcpy(runinfofile,argv[++ic]);
      strcpy(argv[ic],"");
    }   
    if(strcmp(argv[ic],"-run")==0){
      run = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
           << " drawscl ---------------------------------------------------------- \n"
           << "  -run            :  run number\n"
           << "  -i       [file] :  run data file\n"
	   << "  -runinfo [file] :  runinfo file\n"
           << "  -nodraw         :  Not draw any histograms. \n"
           << "  -print [path]   :  Save Canvases\n"
           << "  -q,-b,          :  ROOT options. \n"
           << endl;
      return 0;
    }
  }

  if(strcmp(datafile,"")==0 || run < 0){
    cerr << "Error: Give a filename." << endl;
    exit(-1);
  }

  TRint app("drawruninfo",&argc,argv,0,0,kTRUE);

  // ++++++ OPEN FILE +++++++++++++++++++++++++++++++++++++++
  TFile *file = new TFile(datafile);
  if(file->IsZombie()){
    cerr << "Cannot Open " << datafile << endl;
    return -1;
  }


  A2Cal1 *a2callast = NULL; 
  RawL1T *a2rawl1tlast = NULL;
  SclL1T *a2scll1tlast = NULL;
  
  a2callast = (A2Cal1*) file->Get("a2cal1last");
  a2rawl1tlast = (RawL1T*) file->Get("a2rawl1tlast");
  a2scll1tlast = (SclL1T*) file->Get("a2scll1tlast"); 


  // +++++ OPEN INFO +++++++++++++++++++++++++++++++++++++++++
  LHCfRunInfo      *info = NULL;
  LHCfRunInfoTable *infotable = new LHCfRunInfoTable();
  if(strcmp(runinfofile,"")!=0 && infotable->ReadTable(runinfofile) == OK){
    if(infotable->GetRunInfo(run)){
      info = infotable->GetRunInfo(run);
    }
  }

  // ++++++ DRAW ++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas *c = new TCanvas("c","c",1000,650);
  c->cd();
  TPad* p_a1 = new TPad("p1","",0.0,0.65,1.0,0.95);
  p_a1->Draw();
  c->cd();
  TPad* p_a2 = new TPad("p2","",0.0,0.30,1.0,0.60);
  p_a2->Draw();
  c->cd(); 
  TPad* p_l1t = new TPad("pl1t","",0.0,0.00,1.0,0.25);
  p_l1t->Draw();
  
  c->cd();
  TText *text = new TText();
  text->DrawTextNDC(0.01,0.95,"ARM1 COUNTERS");
  text->DrawTextNDC(0.01,0.60,"ARM2 COUNTERS");
  text->DrawTextNDC(0.01,0.25,"L1T COUNTERS (ARM1)");
  

  A2CalEventHist *a2hists = new A2CalEventHist();
  a2hists->Initialize();
  RawL1TDraw *l1thists = new RawL1TDraw();
  l1thists->Initialize();
  
  // a1hists->c2pad2 = p_a1;
  a2hists->c2pad2 = p_a2;
  l1thists->canvas = (TCanvas*)  p_l1t;
  
  if(a2callast){
    a2hists->DrawCanvas2();
    a2hists->SetDisplayVersion_pPb2013();
    a2hists->Fill(a2callast); 
    a2hists->UpdateCanvas2(); 
    p_a2->Modified();
    p_a2->Update();
  }
  if(a2rawl1tlast){
    l1thists->Fill(a2rawl1tlast);
    l1thists->DrawCanvas();
    l1thists->SetDisplayFormat(RawL1TDraw::VERSION_PPB2013);
  }

  // +++++++ DRAW SCLL1T +++++++++++
  double deltat = 1.;
  double x,y,offx,offy;
  char tmp[256];
  int icounter1,icounter2;
  TText *texc = new TText();
  texc->SetTextSize(0.08);
  text->SetTextSize(0.12);

  TH1F *h1 = new TH1F("h1","FC1 RATE",20,0,20);
  TH1F *h2 = new TH1F("h2","FC2 RATE",20,0,20);

  TCanvas *c2 = new TCanvas("c2","c",800,500);
  TPad* p2_0 = new TPad("p2_0","",0.0,0.6,1.0,1.0);
  p2_0->Draw();
  TPad* p2_1 = new TPad("p2_1","",0.0,0.0,1.0,0.6);
  p2_1->Divide(2);
  p2_1->Draw();

  p2_0->cd();
  
  x = 0.02;
  y = 0.75;
  offx = 0.095;
  offy = 0.15;
  if(a2scll1tlast){
    if(info){
      deltat = a2scll1tlast->time[0] - info->start_time;
      text->DrawTextNDC(0.02,0.85,"FC1 RATE FOR EACH BUNCH (BEAM2) [Hz]");
      cout << "DELAT(T) : " << deltat << endl;
    }
    else{
      deltat = 1.;
      text->DrawTextNDC(0.02,0.85,"FC1 COUNTS FOR EACH BUNCH (BEAM2)");
    }
    for(int i=0;i<20;i++){
      sprintf(tmp,"%8.1lf",(double)a2scll1tlast->bcounters[i]/deltat);
      texc->DrawTextNDC(x+offx*(i%10),y-offy*(i/10),tmp);
      h1->Fill(i+0.5,a2scll1tlast->bcounters[i]/deltat);
    }
  }
  

  x = 0.02;
  y = 0.25;
  offx = 0.095;
  offy = 0.15;
  if(a2scll1tlast){ 
    if(info){
      deltat = a2scll1tlast->time[0] - info->start_time;
      text->DrawTextNDC(0.02,0.35,"FC2 RATE FOR EACH BUNCH (BEAM1) [Hz]");
      cout << "DELAT(T) : " << deltat << endl;
    }
    else{
      deltat = 1.;
      text->DrawTextNDC(0.02,0.35,"FC2 COUNTS FOR EACH BUNCH (BEAM1)");
    }
    for(int i=0;i<20;i++){
      sprintf(tmp,"%8.1lf",(double)a2scll1tlast->bcounters[i]/deltat);
      texc->DrawTextNDC(x+offx*(i%10),y-offy*(i/10),tmp);
      h2->Fill(i+0.5,a2scll1tlast->bcounters[i]/deltat);
    }
  }

  p2_1->cd(1);
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy(); 
  h1->SetFillColor(kRed);
  h1->SetXTitle("#BUNCH (BPTX2)");
  h1->Draw();
  gPad->Update();
  p2_1->cd(2);
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  h2->SetFillColor(kBlue);   
  h2->SetXTitle("#BUNCH (BPTX1)");
  h2->Draw();  
  gPad->Update();
  c2->Update();

  // +++++++ DRAW DAQ LIVE TIME ++++++++++++++++++
  text->SetTextSize(0.05);
  texc->SetTextSize(0.03);
  texc->SetTextFont(102);
  TCanvas *c3 = new TCanvas("c3","c",800,600);

  int ic=0;
  
//   // Arm1 
//   text->DrawTextNDC(0.02,0.92,"ARM1");
//   x = 0.01;
//   y = 0.85;
//   offx = 0.09;
//   offy = 0.04;
//   ic = 0;
//   if(0){
//     texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON LOGIC");
//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a1callast->counter[3]));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[1]));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a1callast->counter[3])/a1callast->counter[1]));
//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"L2TA/SHOWER_OR");
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a1callast->counter[9]));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[6]));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a1callast->counter[9])/a1callast->counter[6]));
//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"SHOWER_COIN/_OR");
//     icounter1 = (int)(a1callast->counter[4]+a1callast->counter[5])-(int)(a1callast->counter[6]);
//     icounter2 = (int)(a1callast->counter[6]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++; 
//     texc->DrawTextNDC(x,y-offy*ic,"SLOGIC/STRG");
//     icounter1 = (int)(a1callast->counter[7]);
//     icounter2 = (int)(a1callast->counter[4]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++; 
//     texc->DrawTextNDC(x,y-offy*ic,"LLOGIC/LTRG");
//     icounter1 = (int)(a1callast->counter[8]);
//     icounter2 = (int)(a1callast->counter[5]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++;
//     if(info && a1hists->gpioversion==A1CalEventHist::GPIOLOGIC_V28){
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA/L2TA_WOE");
//       icounter1 = (int)(a1callast->counter[9]);
//       icounter2 = (int)(a1callast->counter[12]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA_MB/MB");
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a1_nevent_L2TA_MB));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[6]));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a1_nevent_L2TA_MB)/a1callast->counter[6]));
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," MB_PRESET/MB");
//       icounter1 = (int)(info->a1_nevent_presetMB);
//       icounter2 = (int)(a1callast->counter[6]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," L2TA_MB/MB_PRE");
//       icounter1 = (int)(info->a1_nevent_L2TA_MB);
//       icounter2 = (int)(info->a1_nevent_presetMB);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA_SP/SP"); 
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a1_nevent_L2TA_SP));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[14]));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a1_nevent_L2TA_SP)/a1callast->counter[14])); 
//       ic++;  
//       texc->DrawTextNDC(x,y-offy*ic," SP_PRESET/SP");
//       icounter1 = (int)(info->a1_nevent_presetSP);
//       icounter2 = (int)(a1callast->counter[14]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," L2TA_SP/SP_PRE");
//       icounter1 = (int)(info->a1_nevent_L2TA_SP);
//       icounter2 = (int)(info->a1_nevent_presetSP);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"SP/MB");
//       icounter1 = (int)(a1callast->counter[14]);
//       icounter2 = (int)(a1callast->counter[6]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"SP/SHOWER_COIN");
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a1callast->counter[14]));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       icounter2 = (int)(a1callast->counter[4]+a1callast->counter[5])-(int)(a1callast->counter[6]);
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a1_nevent_L2TA_SP)/icounter2)); 
//       ic++;
//     }
//   }
  
  ic++;
  
  if(a2rawl1tlast){
    texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON L1T");
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
    icounter1 = (int)a2rawl1tlast->gpio2[6];
    icounter2 = (int)a2rawl1tlast->gpio2[4];  
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"L2TA_E/L2TA");
    icounter1 = (int)a2rawl1tlast->gpio2[11];
    icounter2 = (int)a2rawl1tlast->gpio2[10];  
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++;
  }

  // Arm2
  text->DrawTextNDC(0.52,0.92,"ARM2");
  x = 0.51;
  y = 0.85;
  offx = 0.09;
  offy = 0.04;
  ic = 0;
  if(a2callast){
    texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON LOGIC");
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[3]));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[1]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a2callast->counter[3])/a2callast->counter[1]));
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L2TA/SHOWER_OR");
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[9]));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[6]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a2callast->counter[9])/a2callast->counter[6]));
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"SHOWER_COIN/_OR");
    icounter1 = (int)(a2callast->counter[4]+a2callast->counter[5])-(int)(a2callast->counter[6]);
    icounter2 = (int)(a2callast->counter[6]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SLOGIC/STRG");
    icounter1 = (int)(a2callast->counter[7]);
    icounter2 = (int)(a2callast->counter[4]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"LLOGIC/LTRG");
    icounter1 = (int)(a2callast->counter[8]);
    icounter2 = (int)(a2callast->counter[5]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++;
    if(info && a2hists->gpioversion==A2CalEventHist::GPIOLOGIC_V28){
      texc->DrawTextNDC(x,y-offy*ic,"L2TA/L2TA_WOE");
      icounter1 = (int)(a2callast->counter[9]);
      icounter2 = (int)(a2callast->counter[12]);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic,"L2TA_MB/MB");
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a2_nevent_L2TA_MB));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[6]));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_MB)/a2callast->counter[6]));
      ic++; 
      texc->DrawTextNDC(x,y-offy*ic," MB_PRESET/MB");
      icounter1 = (int)(info->a2_nevent_presetMB);
      icounter2 = (int)(a2callast->counter[6]);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic," L2TA_MB/MB_PRE");
      icounter1 = (int)(info->a2_nevent_L2TA_MB);
      icounter2 = (int)(info->a2_nevent_presetMB);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic,"L2TA_SP/SP"); 
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a2_nevent_L2TA_SP));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[14]));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_SP)/a2callast->counter[14])); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic," SP_PRESET/SP");
      icounter1 = (int)(info->a2_nevent_presetSP);
      icounter2 = (int)(a2callast->counter[14]);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic," L2TA_SP/SP_PRE");
      icounter1 = (int)(info->a2_nevent_L2TA_SP);
      icounter2 = (int)(info->a2_nevent_presetSP);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
      ic++;
      texc->DrawTextNDC(x,y-offy*ic,"SP/MB");
      icounter1 = (int)(a2callast->counter[14]);
      icounter2 = (int)(a2callast->counter[6]);
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
      ic++;
      texc->DrawTextNDC(x,y-offy*ic,"SP/SHOWER_COIN");
      texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[14]));
      texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
      icounter2 = (int)(a2callast->counter[4]+a2callast->counter[5])-(int)(a2callast->counter[6]);
      texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
      texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_SP)/icounter2)); 
      ic++;
    }
  }
  
  ic++;
  
  if(a2rawl1tlast){
    texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON L1T");
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
    icounter1 = (int)a2rawl1tlast->gpio2[7];
    icounter2 = (int)a2rawl1tlast->gpio2[5];  
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"L2TA_E/L2TA");
    icounter1 = (int)a2rawl1tlast->gpio2[13];
    icounter2 = (int)a2rawl1tlast->gpio2[12];  
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++;
  }

  c3->Update();
  
  
  // ++++++++ SAVE CANVASES ++++++++++++++++++++++++++++++++++++
  char ch_run[20]="";
  char printname[256];
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%sscl1.gif",printpath,ch_run);
    c->Print(printname);
    sprintf(printname,"%s/%sscl2.gif",printpath,ch_run);
    c3->Print(printname);
    sprintf(printname,"%s/%sbcounters.gif",printpath,ch_run);
    c2->Print(printname);
  }
  
  app.Run();
  return 0;
}

char* GetChar(const char* format,int val){
  static char buf[256];
  sprintf(buf,format,val);
  return buf;
}

char* GetChar(const char* format,double val){
  static char buf[256];
  sprintf(buf,format,val);
  return buf;
}
