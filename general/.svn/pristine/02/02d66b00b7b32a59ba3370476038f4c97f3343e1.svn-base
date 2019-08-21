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
#include "A1CalEventHist.h"
#include "A2CalEventHist.h"
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

  A1Cal1 *a1callast = NULL;
  A2Cal1 *a2callast = NULL; 
  
  a1callast = (A1Cal1*) file->Get("a1cal1last");
  a2callast = (A2Cal1*) file->Get("a2cal1last");

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
  
  c->cd();
  TText *text = new TText();
  text->DrawTextNDC(0.01,0.95,"ARM1 COUNTERS");
  text->DrawTextNDC(0.01,0.60,"ARM2 COUNTERS");
  
  A1CalEventHist *a1hists = new A1CalEventHist();
  a1hists->Initialize();
  A2CalEventHist *a2hists = new A2CalEventHist();
  a2hists->Initialize();
  
  a1hists->c2pad2 = p_a1;
  a2hists->c2pad2 = p_a2;
  
  if(a1callast){
    a1hists->DrawCanvas2();
    a1hists->SetDisplayVersion_pp2015();
    a1hists->Fill(a1callast); 
    a1hists->UpdateCanvas2();
    p_a1->Modified();
    p_a1->Update();
  }
  if(a2callast){
    a2hists->DrawCanvas2();
    a2hists->SetDisplayVersion_pp2015();
    a2hists->Fill(a2callast); 
    a2hists->UpdateCanvas2(); 
    p_a2->Modified();
    p_a2->Update();
  }

  // ============ END OF COUNTER 1 ===============
  
  // +++++++ DRAW DAQ LIVE TIME ++++++++++++++++++
  double deltat = 1.;
  double x,y,offx,offy;
  char tmp[256];
  int icounter1,icounter2,icounter3,icounter4;
  TText *texc = new TText();
  text->SetTextSize(0.05);
  texc->SetTextSize(0.03);
  texc->SetTextFont(102);
  TCanvas *c3 = new TCanvas("c3","c",1000,600);

  int ic=0;
  
  // Arm1 
  text->DrawTextNDC(0.02,0.92,"ARM1");
  x = 0.01;
  y = 0.85;
  offx = 0.09;
  offy = 0.04;
  ic = 0;
  if(a2callast){
    icounter3 = (int)(a2callast->counter[12]);
  }
  if(a1callast){
    texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON LOGIC");
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a1callast->counter[6]));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[5]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a1callast->counter[6])/a1callast->counter[5]));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_L3T/SHW_TRG");
    icounter1 = (int)(a1callast->counter[15]);
    icounter2 = (int)(a1callast->counter[11]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SPE_L3T/SPE_TRG");
    icounter1 = (int)(a1callast->counter[16]);
    icounter2 = (int)(a1callast->counter[13]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"STRG/SLOGIC");
    icounter1 = (int)(a1callast->counter[7]);
    icounter2 = (int)(a1callast->counter[9]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"LTRG/LLOGIC");
    icounter1 = (int)(a1callast->counter[8]);
    icounter2 = (int)(a1callast->counter[10]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_TRG/SHW_BPTXX");
    icounter1 = (int)(a1callast->counter[11]);
    icounter2 = (int)(a1callast->counter[12]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SPE_TRG/SPE_BPTXX");
    icounter1 = (int)(a1callast->counter[13]);
    icounter2 = (int)(a1callast->counter[14]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_SHOWER/L3T");
    icounter1 = (int)(a1callast->counter[15]);
    icounter2 = (int)(a1callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));   
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_SPECIAL/L3T");
    icounter1 = (int)(a1callast->counter[16]);
    icounter2 = (int)(a1callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_PEDE/L3T");
    icounter1 = (int)(a1callast->counter[17]);
    icounter2 = (int)(a1callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_L1T/L3T");
    icounter1 = (int)(a1callast->counter[18]);
    icounter2 = (int)(a1callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));   
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"A1_L3T/L3T_OR");
    icounter1 = (int)(a1callast->counter[19]);
    icounter2 = (int)(a1callast->counter[20]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"COIN_SHW/A1_SHW");
    icounter1 = (int)(a1callast->counter[21]& 0xFFFF);
    icounter2 = (int)(a1callast->counter[12]+icounter3 - icounter1);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a1callast->counter[12]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter2)/a1callast->counter[12]));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"ATLAS_LHCF/L3T_OR");
    icounter1 = (int)(a1callast->counter[21]>>16);
    icounter2 = (int)(a1callast->counter[20]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"FC_TRG/FC_LOGIC");
    icounter1 = (int)(a1callast->counter[32]);
    icounter2 = (int)(a1callast->counter[31]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));            
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_AND_FC/COIN_FC");
    icounter1 = (int)(a1callast->counter[33]);
    icounter2 = (int)(a1callast->counter[34]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
  }
  
  ic++;

  // Arm2
  text->DrawTextNDC(0.52,0.92,"ARM2");
  x = 0.51;
  y = 0.85;
  offx = 0.09;
  offy = 0.04;
  ic = 0;
  if(a1callast){
    icounter4 = (int)(a1callast->counter[12]);
  }
  if(a2callast){
    texc->DrawTextNDC(x,y-offy*ic,"COUNTERS ON LOGIC");
    ic++;
    texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[6]));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[5]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a2callast->counter[6])/a2callast->counter[5]));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_L3T/SHW_TRG");
    icounter1 = (int)(a2callast->counter[15]);
    icounter2 = (int)(a2callast->counter[11]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SPE_L3T/SPE_TRG");
    icounter1 = (int)(a2callast->counter[16]);
    icounter2 = (int)(a2callast->counter[13]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"STRG/SLOGIC");
    icounter1 = (int)(a2callast->counter[7]);
    icounter2 = (int)(a2callast->counter[9]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"LTRG/LLOGIC");
    icounter1 = (int)(a2callast->counter[8]);
    icounter2 = (int)(a2callast->counter[10]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_TRG/SHW_BPTXX");
    icounter1 = (int)(a2callast->counter[11]);
    icounter2 = (int)(a2callast->counter[12]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SPE_TRG/SPE_BPTXX");
    icounter1 = (int)(a2callast->counter[13]);
    icounter2 = (int)(a2callast->counter[14]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_SHOWER/L3T");
    icounter1 = (int)(a2callast->counter[15]);
    icounter2 = (int)(a2callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));   
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_SPECIAL/L3T");
    icounter1 = (int)(a2callast->counter[16]);
    icounter2 = (int)(a2callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_PEDE/L3T");
    icounter1 = (int)(a2callast->counter[17]);
    icounter2 = (int)(a2callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"TRG_L1T/L3T");
    icounter1 = (int)(a2callast->counter[18]);
    icounter2 = (int)(a2callast->counter[19]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));   
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"A2_L3T/L3T_OR");
    icounter1 = (int)(a2callast->counter[19]);
    icounter2 = (int)(a2callast->counter[20]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"COIN_SHW/A2_SHW");
    icounter1 = (int)(a2callast->counter[21]& 0xFFFF);
    icounter2 = (int)(a2callast->counter[12]+icounter4 - icounter1);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[12]));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter2)/a2callast->counter[12]));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"ATLAS_LHCF/L3T_OR");
    icounter1 = (int)(a2callast->counter[21]>>16);
    icounter2 = (int)(a2callast->counter[20]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"FC_TRG/FC_LOGIC");
    icounter1 = (int)(a2callast->counter[32]);
    icounter2 = (int)(a2callast->counter[31]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));            
    ic++; 
    texc->DrawTextNDC(x,y-offy*ic,"SHW_AND_FC/COIN_FC");
    icounter1 = (int)(a2callast->counter[33]);
    icounter2 = (int)(a2callast->counter[34]);
    texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
    texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
    texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
    texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
  }
  
  ic++;

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



//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"L1T_E/L1T");
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[3]));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[1]));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a2callast->counter[3])/a2callast->counter[1]));
//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"L2TA/SHOWER_OR");
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[9]));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[6]));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(a2callast->counter[9])/a2callast->counter[6]));
//     ic++;
//     texc->DrawTextNDC(x,y-offy*ic,"SHOWER_COIN/_OR");
//     icounter1 = (int)(a2callast->counter[4]+a2callast->counter[5])-(int)(a2callast->counter[6]);
//     icounter2 = (int)(a2callast->counter[6]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++; 
//     texc->DrawTextNDC(x,y-offy*ic,"SLOGIC/STRG");
//     icounter1 = (int)(a2callast->counter[7]);
//     icounter2 = (int)(a2callast->counter[4]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++; 
//     texc->DrawTextNDC(x,y-offy*ic,"LLOGIC/LTRG");
//     icounter1 = (int)(a2callast->counter[8]);
//     icounter2 = (int)(a2callast->counter[5]);
//     texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//     texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//     texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//     texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//     ic++;
//     if(info && a2hists->gpioversion==A2CalEventHist::GPIOLOGIC_V28){
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA/L2TA_WOE");
//       icounter1 = (int)(a2callast->counter[9]);
//       icounter2 = (int)(a2callast->counter[12]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA_MB/MB");
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a2_nevent_L2TA_MB));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[6]));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_MB)/a2callast->counter[6]));
//       ic++; 
//       texc->DrawTextNDC(x,y-offy*ic," MB_PRESET/MB");
//       icounter1 = (int)(info->a2_nevent_presetMB);
//       icounter2 = (int)(a2callast->counter[6]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," L2TA_MB/MB_PRE");
//       icounter1 = (int)(info->a2_nevent_L2TA_MB);
//       icounter2 = (int)(info->a2_nevent_presetMB);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"L2TA_SP/SP"); 
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",info->a2_nevent_L2TA_SP));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",(int)a2callast->counter[14]));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_SP)/a2callast->counter[14])); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," SP_PRESET/SP");
//       icounter1 = (int)(info->a2_nevent_presetSP);
//       icounter2 = (int)(a2callast->counter[14]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic," L2TA_SP/SP_PRE");
//       icounter1 = (int)(info->a2_nevent_L2TA_SP);
//       icounter2 = (int)(info->a2_nevent_presetSP);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2)); 
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"SP/MB");
//       icounter1 = (int)(a2callast->counter[14]);
//       icounter2 = (int)(a2callast->counter[6]);
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",icounter1));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(icounter1)/icounter2));
//       ic++;
//       texc->DrawTextNDC(x,y-offy*ic,"SP/SHOWER_COIN");
//       texc->DrawTextNDC(x+offx*2.0,y-offy*ic,GetChar("%8d",(int)a2callast->counter[14]));
//       texc->DrawTextNDC(x+offx*3.1,y-offy*ic,"/");
//       icounter2 = (int)(a2callast->counter[4]+a2callast->counter[5])-(int)(a2callast->counter[6]);
//       texc->DrawTextNDC(x+offx*3.2,y-offy*ic,GetChar("%8d",icounter2));
//       texc->DrawTextNDC(x+offx*4.2,y-offy*ic,GetChar("%8.4lf",(double)(info->a2_nevent_L2TA_SP)/icounter2)); 
//       ic++;
//     }
