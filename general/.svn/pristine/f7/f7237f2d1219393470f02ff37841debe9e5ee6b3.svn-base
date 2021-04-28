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
#include "LHCfRunInfoTable.h"
#include "gsetup.h"
using namespace std;

char* GetChar(const char* format,int val);
char* GetChar(const char* format,double val);
char* GetChar(const char* format,char* val);
string CutdownV1495Load(char csetup[]);
string CutdownGPIOLoad(char csetup[]);
string CutdownGPIOSetup(char csetup[]);
string CutdownDiscri(char csetup[]);

int main(int argc,char **argv){  
  gsetup();
  char  runinfofile[256]="";
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  int   run=-1; 
  
  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-runinfo")==0){
      strcpy(runinfofile,argv[++ic]); 
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
	   << " drawhists ---------------------------------------------------------- \n"
	   << "  -run            :  run number\n"
	   << "  -runinfo [file] :  Runinfo file\n"
	   << "  -nodraw         :  Not draw any histograms. \n" 
	   << "  -print [path]   :  Save Canvases\n" 
	   << "  -q,-b,          :  ROOT options. \n"
	   << endl;
      return 0;
    }
  }

  if(strcmp(runinfofile,"")==0 || run < 0){
    cerr << "Error: Give a filename." << endl;
    exit(-1);
  }
  
  TRint app("drawruninfo",&argc,argv,0,0,kTRUE);

  // ++++++ DRAW ++++++++++++++++++++++++++++++++++++++++++++++
  LHCfRunInfo      *info = NULL;
  LHCfRunInfoTable *infotable = new LHCfRunInfoTable();
  if( infotable->ReadTable(runinfofile) == OK){ 
    if(infotable->GetRunInfo(run)){
      info = infotable->GetRunInfo(run);
    }
  }
  else{
    cerr << "Cannot open " << runinfofile << endl;
    exit(-1);
  }
  if(info==NULL){ 
    cerr << "No data for RUN:" << run << " in " << runinfofile << endl;
    exit(-1);
  } 

  TCanvas *c = new TCanvas("c","RunInfo",800,700);
  char text[256];
  double x,y,X,Y,offx,offy;
  TLatex *latex = new TLatex();
  latex->SetTextFont(102);
  // RUN NUMBER
  latex->SetTextSize(0.06);
  sprintf(text,"RUN%05d", run);
  latex->DrawTextNDC(0.38,0.94, text);
  // TIME
  X = 0.10;
  Y = 0.89;
  latex->SetTextSize(0.028);
  latex->DrawTextNDC(X,Y, "START:");
  time_t ts = info->start_time;
  latex->DrawTextNDC(X+0.1,Y, asctime(localtime(&ts)));
  latex->DrawTextNDC(X,Y-0.028, "END:");
  time_t te = info->end_time;
  latex->DrawTextNDC(X+0.1,Y-0.028, asctime(localtime(&te)));
  latex->DrawTextNDC(X+0.5,Y, "DAQ TIME:");
  sprintf(text,"%d sec", info->end_time-info->start_time);
  latex->DrawTextNDC(X+0.63,Y, text);
  double deltat = info->end_time-info->start_time;
  

  // BEAM CONFIG
  int nbunch_col=0,nbunch_non=0,nbunch_dis=0;
  for(int i=0;i<info->beam1_nbunches;i++){
    if(abs(info->beam1_tag[i])==1){ nbunch_col++;}
    if(abs(info->beam1_tag[i])==2){ nbunch_non++;}
    if(abs(info->beam1_tag[i])==3){ nbunch_dis++;}  
  }
  X = 0.05;
  Y = 0.80;  
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "BEAM CONFIGURATION: ");
  sprintf(text,"%dx%d",info->beam1_nbunches,info->beam2_nbunches);
  latex->DrawTextNDC(X+0.35,Y,text);
  latex->SetTextSize(0.028);
  latex->DrawTextNDC(X+0.45,Y-offy*1, GetChar("COL: %3d",nbunch_col));
  latex->DrawTextNDC(X+0.60,Y-offy*1, GetChar("NON: %3d",nbunch_non));
  latex->DrawTextNDC(X+0.75,Y-offy*1, GetChar("DIS: %3d",nbunch_dis));

  double livetime;
  // ARM1
  X = 0.05;
  Y = 0.74;
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "ARM1");
  latex->SetTextSize(0.025);
  X = 0.05;
  Y = 0.73;
  offx = 0.028;
  offy = 0.027; 
  latex->DrawTextNDC(X+0.12,Y-offy*0, " #EVENT");
  latex->DrawTextNDC(X+0.22,Y-offy*0, "RATE[Hz]");  
  latex->DrawTextNDC(X+0.02,Y-offy*1, "TRIGGER");
  latex->DrawTextNDC(X+0.02,Y-offy*2, "L2T_SHW");
  latex->DrawTextNDC(X+0.02,Y-offy*3, "L2T_SPE");
  latex->DrawTextNDC(X+0.02,Y-offy*4, "L2T_PEDE");  
  latex->DrawTextNDC(X+0.02,Y-offy*5, "L2T_FC");
  latex->DrawTextNDC(X+0.02,Y-offy*6, "LASER");
  latex->DrawTextNDC(X+0.02,Y-offy*7, "SCALER"); 
  latex->DrawTextNDC(X+0.02,Y-offy*8, "DAQ LIVE TIME");
  latex->DrawTextNDC(X+0.12,Y-offy*1, GetChar("%7d",info->a1_nevent));
  latex->DrawTextNDC(X+0.12,Y-offy*2, GetChar("%7d",info->a1_nevent_L2T_Shower));
  latex->DrawTextNDC(X+0.12,Y-offy*3, GetChar("%7d",info->a1_nevent_L2T_Special));
  latex->DrawTextNDC(X+0.12,Y-offy*4, GetChar("%7d",info->a1_nevent_L2T_Pedestal)); 
  latex->DrawTextNDC(X+0.12,Y-offy*5, GetChar("%7d",info->a1_nevent_L2T_FC));  
  latex->DrawTextNDC(X+0.12,Y-offy*6, GetChar("%7d",info->a1_nevent_laser));  
  latex->DrawTextNDC(X+0.12,Y-offy*7, GetChar("%7d",info->a1scl_nevent));
  latex->DrawTextNDC(X+0.22,Y-offy*1, GetChar("%8.2lf",info->a1_nevent/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*2, GetChar("%8.2lf",info->a1_nevent_L2T_Shower/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*3, GetChar("%8.2lf",info->a1_nevent_L2T_Special/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*4, GetChar("%8.2lf",info->a1_nevent_L2T_Pedestal/deltat)); 
  latex->DrawTextNDC(X+0.22,Y-offy*5, GetChar("%8.2lf",info->a1_nevent_L2T_FC/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*6, GetChar("%8.2lf",info->a1_nevent_laser/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*7, GetChar("%8.2lf",info->a1scl_nevent/deltat));  
  livetime = 100.*(double)info->a1_nevent_l1t_enable/(double)info->a1_nevent_l1t;
  latex->DrawTextNDC(X+0.21,Y-offy*8, GetChar("%5.2lf [\%%]",livetime));

  // ARM2
  X = 0.40;
  Y = 0.74;
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "ARM2");
  latex->SetTextSize(0.025);
  X = 0.40;
  Y = 0.73;
  offx = 0.028;
  offy = 0.027; 
  latex->DrawTextNDC(X+0.12,Y-offy*0, " #EVENT");
  latex->DrawTextNDC(X+0.22,Y-offy*0, "RATE[Hz]");  
  latex->DrawTextNDC(X+0.02,Y-offy*1, "TRIGGER");
  latex->DrawTextNDC(X+0.02,Y-offy*2, "L2T_SHW");
  latex->DrawTextNDC(X+0.02,Y-offy*3, "L2T_SPE");
  latex->DrawTextNDC(X+0.02,Y-offy*4, "L2T_PEDE"); 
  latex->DrawTextNDC(X+0.02,Y-offy*5, "L2T_FC");
  latex->DrawTextNDC(X+0.02,Y-offy*6, "LASER");
  latex->DrawTextNDC(X+0.02,Y-offy*7, "SCALER"); 
  latex->DrawTextNDC(X+0.02,Y-offy*8, "DAQ LIVE TIME");
  latex->DrawTextNDC(X+0.12,Y-offy*1, GetChar("%7d",info->a2_nevent));
  latex->DrawTextNDC(X+0.12,Y-offy*2, GetChar("%7d",info->a2_nevent_L2T_Shower));
  latex->DrawTextNDC(X+0.12,Y-offy*3, GetChar("%7d",info->a2_nevent_L2T_Special));
  latex->DrawTextNDC(X+0.12,Y-offy*4, GetChar("%7d",info->a2_nevent_L2T_Pedestal)); 
  latex->DrawTextNDC(X+0.12,Y-offy*5, GetChar("%7d",info->a2_nevent_L2T_FC));  
  latex->DrawTextNDC(X+0.12,Y-offy*6, GetChar("%7d",info->a2_nevent_laser));  
  latex->DrawTextNDC(X+0.12,Y-offy*7, GetChar("%7d",info->a2scl_nevent));
  latex->DrawTextNDC(X+0.22,Y-offy*1, GetChar("%8.2lf",info->a2_nevent/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*2, GetChar("%8.2lf",info->a2_nevent_L2T_Shower/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*3, GetChar("%8.2lf",info->a2_nevent_L2T_Special/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*4, GetChar("%8.2lf",info->a2_nevent_L2T_Pedestal/deltat)); 
  latex->DrawTextNDC(X+0.22,Y-offy*5, GetChar("%8.2lf",info->a2_nevent_L2T_FC/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*6, GetChar("%8.2lf",info->a2_nevent_laser/deltat));
  latex->DrawTextNDC(X+0.22,Y-offy*7, GetChar("%8.2lf",info->a2scl_nevent/deltat));  
  livetime = 100.*(double)info->a2_nevent_l1t_enable/(double)info->a2_nevent_l1t;
  latex->DrawTextNDC(X+0.21,Y-offy*8, GetChar("%5.2lf [\%%]",livetime));

  // Slow Data
  X = 0.75;
  Y = 0.74;
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "SC");
  latex->SetTextSize(0.025);
  X = 0.75;
  Y = 0.73;
  offx = 0.028;
  offy = 0.027; 
  latex->DrawTextNDC(X+0.12,Y-offy*0, " #EVENT"); 
  latex->DrawTextNDC(X+0.02,Y-offy*1, "SC");
  latex->DrawTextNDC(X+0.02,Y-offy*3, "DIPL");
  latex->DrawTextNDC(X+0.02,Y-offy*2, "DIPH");
  latex->DrawTextNDC(X+0.02,Y-offy*4, "DIPVH");
  latex->DrawTextNDC(X+0.12,Y-offy*1, GetChar("%7d",info->sc_nevent));
  latex->DrawTextNDC(X+0.12,Y-offy*2, GetChar("%7d",info->dipl_nevent));
  latex->DrawTextNDC(X+0.12,Y-offy*3, GetChar("%7d",info->diph_nevent));  
  latex->DrawTextNDC(X+0.12,Y-offy*4, GetChar("%7d",info->dipvh_nevent));  

  
  // DAQ Setup
  // Arm1 
  X = 0.05;
  Y = 0.42;
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "ARM1 SETUP");
  latex->SetTextSize(0.025);
  X = 0.05;
  Y = 0.38;
  offx = 0.028;
  offy = 0.027;
  latex->DrawTextNDC(X+0.02,Y-offy*0, "RUN MODE");
  latex->DrawTextNDC(X+0.02,Y-offy*1, "LOGIC");
  latex->DrawTextNDC(X+0.02,Y-offy*2, "SETUP");
  latex->DrawTextNDC(X+0.02,Y-offy*3, "PMT_HV");
  latex->DrawTextNDC(X+0.02,Y-offy*4, "SCIFI_HV");  
  latex->DrawTextNDC(X+0.02,Y-offy*5, "DISCRI");
  latex->DrawTextNDC(X+0.02,Y-offy*6, "POSITION");
  X = 0.10;
  Y = 0.38;
  latex->DrawTextNDC(X+0.12,Y-offy*0, GetChar("%d",info->a1_runmode));
  latex->DrawTextNDC(X+0.12,Y-offy*1, (CutdownV1495Load(info->a1_V1495Load)).c_str());
  latex->DrawTextNDC(X+0.12,Y-offy*2, info->a1_LogicMode);
  latex->DrawTextNDC(X+0.12,Y-offy*3, info->a1_PMTgain);
  latex->DrawTextNDC(X+0.12,Y-offy*4, info->a1_scifigain);
  latex->DrawTextNDC(X+0.12,Y-offy*5, (CutdownDiscri(info->a1_Discriminator)).c_str()); 
  latex->DrawTextNDC(X+0.12,Y-offy*6, info->a1_position); 
  // Arm2 
  X = 0.50;
  Y = 0.42;
  latex->SetTextSize(0.035);
  latex->DrawTextNDC(X,Y, "ARM2 SETUP");
  latex->SetTextSize(0.025);
  X = 0.50;
  Y = 0.38;
  offx = 0.028;
  offy = 0.027;
  latex->DrawTextNDC(X+0.02,Y-offy*0, "RUN MODE");
  latex->DrawTextNDC(X+0.02,Y-offy*1, "LOGIC");
  latex->DrawTextNDC(X+0.02,Y-offy*2, "SETUP");
  latex->DrawTextNDC(X+0.02,Y-offy*3, "PMT_HV");
  latex->DrawTextNDC(X+0.02,Y-offy*4, "SILICON");  
  latex->DrawTextNDC(X+0.02,Y-offy*5, "DISCRI");
  latex->DrawTextNDC(X+0.02,Y-offy*6, "POSITION");
  latex->DrawTextNDC(X+0.02,Y-offy*8, "CRC ERROR");
  X = 0.55;
  Y = 0.38;
  latex->DrawTextNDC(X+0.12,Y-offy*0, GetChar("%d",info->a2_runmode));
  latex->DrawTextNDC(X+0.12,Y-offy*1, (CutdownV1495Load(info->a2_V1495Load)).c_str());
  latex->DrawTextNDC(X+0.12,Y-offy*2, info->a2_LogicMode);
  latex->DrawTextNDC(X+0.12,Y-offy*3, info->a2_PMTgain);
  latex->DrawTextNDC(X+0.12,Y-offy*4, info->a2_silicongain);
  latex->DrawTextNDC(X+0.12,Y-offy*5, (CutdownDiscri(info->a2_Discriminator)).c_str()); 
  latex->DrawTextNDC(X+0.12,Y-offy*6, info->a2_position); 
  latex->DrawTextNDC(X+0.12,Y-offy*8, Form("%d",info->a2_ncrcerror)); 

  // ++++++++ SAVE CANVASES ++++++++++++++++++++++++++++++++++++
  char ch_run[20]="";
  char printname[256];
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    sprintf(printname,"%s/%sruninfo.gif",printpath,ch_run);
    c->Print(printname);
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

char* GetChar(const char* format,char* val){
  static char buf[256];
  sprintf(buf,format,val);
  return buf;
}

string CutdownV1495Load(char csetup[]){
  string ss = csetup;
  string cword;
  
  cword = "LHCF_";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
                   ss.size()-(ss.find(cword)+cword.size()));

  }
  cword = ".rbf";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(0,
                   ss.size()-(cword.size()));
  }
  return ss;
}

string CutdownGPIOLoad(char csetup[]){
  string ss = csetup;
  string cword;

  // For setup_a1_****.sh
  cword = "load_";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
                   ss.size()-(ss.find(cword)+cword.size()));

  }

  cword = ".csh";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(0,
                   ss.size()-(cword.size()));
  }
  return ss;
}

string CutdownGPIOSetup(char csetup[]){
  string ss = csetup;
  string cword;

  // For setup_a1_****.sh
  cword = "setup_a1_";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
                   ss.size()-(ss.find(cword)+cword.size()));

  }
  // For setup_a1_****.sh
  cword = "setup_a2_";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
                   ss.size()-(ss.find(cword)+cword.size()));
  }

  cword = ".sh";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(0,
                   ss.size()-(cword.size()));
  }
  return ss;
}

string CutdownDiscri(char csetup[]){
  string ss = csetup;
  string cword;

  cword = "discri.param.";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
                   ss.size()-(ss.find(cword)+cword.size()));

  }
  return ss;
}
