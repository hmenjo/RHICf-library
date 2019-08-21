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
#include "A1Cal1AccumHist.h"
#include "A2Cal1AccumHist.h"
#include "gsetup.h"
using namespace std;

int main(int argc,char **argv){  
  gsetup();
  gStyle->SetOptStat(1110);
  gStyle->SetTitleX(0.05);
  gStyle->SetTitleW(0.7);
  
  // ++++++++ Manage optioons +++++++++++++++++++++++++++++
  int   adcrange=0;         // Low:0  High:1  
  char  histfile[256]="";
  bool  drawall=true;
  bool  drawbeam=true;
  bool  drawpede=true; 
  bool  drawdelay=false;
  bool  drawlog=false;
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  char  savecanvas_tag[50]="";
  int   run=-1;

  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-i")==0){
      strcpy(histfile,argv[++ic]);
      strcpy(argv[ic],"");
    }
    if(strcmp(argv[ic],"-High")==0){
      adcrange = 1;
    }
    if(strcmp(argv[ic],"-Low")==0){
      adcrange = 0;
    }    if(strcmp(argv[ic],"-drawall")==0){
      drawall = true;
    }
    if(strcmp(argv[ic],"-nodrawall")==0){
      drawall = false;
    }
    if(strcmp(argv[ic],"-drawbeam")==0){
      drawbeam = true;
    }
    if(strcmp(argv[ic],"-nodrawbeam")==0){
      drawbeam = false;
    }
    if(strcmp(argv[ic],"-drawpede")==0){
      drawpede = true;
    }
    if(strcmp(argv[ic],"-nodrawpede")==0){
      drawpede = false;
    }    
    if(strcmp(argv[ic],"-drawdelay")==0){
      drawall  = false;
      drawbeam = false;
      drawpede = false;
      drawdelay = true;
    }
    if(strcmp(argv[ic],"-nodraw")==0){
      strcpy(argv[ic],"-b");
    }
    if(strcmp(argv[ic],"-Log")==0 || strcmp(argv[ic],"-log")==0){
      drawlog = true;
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
    if(strcmp(argv[ic],"-printtag")==0){
      strcpy( savecanvas_tag,argv[++ic]);  
    }
    if(strcmp(argv[ic],"-run")==0){
      run = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
	   << " drawhists ---------------------------------------------------------- \n"
	   << "  -i     :  Histogram file\n"
	   << "  -Low   :  Draw histograms of Low range ADC counts\n"
	   << "  -High  :  Draw histograms of High range ADC counts\n"
	   << "  -drawall/-nodrawall   : Draw (not draw) histograms for all events.\n"
	   << "  -drawbeam/-nodrawbeam : Draw (not draw) histograms for BEAM or LASER events.\n"
	   << "  -drawpede/-nodrawpede : Draw (not draw) histograms for PEDE events.\n"
	   << "  -nodraw :  Not draw any histograms. \n" 
	   << "  -Log    :  Set Y-axis to log scale\n"
	   << "  -print [path]   :  Save Canvases\n" 
	   << "  -printtag [tag] :  Tag of canvas name\n" 
	   << "  -run    :  run number for canvas name\n"
	   << "  -q,-b,  :  ROOT default options. \n"
	   << endl;
      return 0;
    }
  }
  
  if(strcmp(histfile,"")==0){
    cerr << "Error: Give a filename." << endl;
    exit(-1);
  }
  
  TRint app("drawhists",&argc,argv,0,0,kTRUE);
  
  // ++++ Open histograms ++++++++++++++++++++++++++++++++ 
  TFile *file = new TFile(histfile);
  if(file->IsZombie()){
    cerr << "Cannot open " << histfile << endl;
    exit(-1);
  }

  A1Cal1AccumHist *a1hist_all   = (A1Cal1AccumHist*) file->Get("a1hist_all");
  A1Cal1AccumHist *a1hist_beam  = (A1Cal1AccumHist*) file->Get("a1hist_beam");
  A1Cal1AccumHist *a1hist_pede  = (A1Cal1AccumHist*) file->Get("a1hist_pede");
  A1Cal1AccumHist *a1hist_delay = (A1Cal1AccumHist*) file->Get("a1hist_delay");  
  A2Cal1AccumHist *a2hist_all   = (A2Cal1AccumHist*) file->Get("a2hist_all");
  A2Cal1AccumHist *a2hist_beam  = (A2Cal1AccumHist*) file->Get("a2hist_beam");
  A2Cal1AccumHist *a2hist_pede  = (A2Cal1AccumHist*) file->Get("a2hist_pede");
  A2Cal1AccumHist *a2hist_delay = (A2Cal1AccumHist*) file->Get("a2hist_delay");   
  
  // +++++ Create Canvases ++++++++++++++++++++++++++++++
  a1hist_all->InitializeCanvases();
  a1hist_all->InitializeCanvasSciFi();
  a2hist_all->InitializeCanvases();
  a2hist_all->InitializeCanvasSilicon();
  
  a1hist_beam->SetCanvasCal0(a1hist_all->GetCanvasCal0());
  a1hist_beam->SetCanvasCal1(a1hist_all->GetCanvasCal1());
  a1hist_beam->SetCanvasADCs(a1hist_all->GetCanvasADCs());
  a1hist_beam->SetCanvasFlag(a1hist_all->GetCanvasFlag());
  a1hist_beam->SetCanvasTDC(a1hist_all->GetCanvasTDC()); 
  a1hist_beam->SetCanvasSciFi(a1hist_all->GetCanvasSciFi());

  a1hist_pede->SetCanvasCal0(a1hist_all->GetCanvasCal0());
  a1hist_pede->SetCanvasCal1(a1hist_all->GetCanvasCal1());
  a1hist_pede->SetCanvasADCs(a1hist_all->GetCanvasADCs());
  a1hist_pede->SetCanvasFlag(a1hist_all->GetCanvasFlag());
  a1hist_pede->SetCanvasTDC(a1hist_all->GetCanvasTDC()); 
  a1hist_pede->SetCanvasSciFi(a1hist_all->GetCanvasSciFi());

  a1hist_delay->SetCanvasCal0(a1hist_all->GetCanvasCal0());
  a1hist_delay->SetCanvasCal1(a1hist_all->GetCanvasCal1());
  a1hist_delay->SetCanvasADCs(a1hist_all->GetCanvasADCs());
  a1hist_delay->SetCanvasFlag(a1hist_all->GetCanvasFlag());
  a1hist_delay->SetCanvasTDC(a1hist_all->GetCanvasTDC());
  a1hist_delay->SetCanvasSciFi(a1hist_all->GetCanvasSciFi()); 

  a2hist_beam->SetCanvasCal0(a2hist_all->GetCanvasCal0());
  a2hist_beam->SetCanvasCal1(a2hist_all->GetCanvasCal1());
  a2hist_beam->SetCanvasADCs(a2hist_all->GetCanvasADCs());
  a2hist_beam->SetCanvasFlag(a2hist_all->GetCanvasFlag()); 
  a2hist_beam->SetCanvasTDC(a2hist_all->GetCanvasTDC()); 
  a2hist_beam->SetCanvasSilicon(a2hist_all->GetCanvasSilicon()); 
  
  a2hist_pede->SetCanvasCal0(a2hist_all->GetCanvasCal0());
  a2hist_pede->SetCanvasCal1(a2hist_all->GetCanvasCal1());
  a2hist_pede->SetCanvasADCs(a2hist_all->GetCanvasADCs());
  a2hist_pede->SetCanvasFlag(a2hist_all->GetCanvasFlag()); 
  a2hist_pede->SetCanvasTDC(a2hist_all->GetCanvasTDC()); 
  a2hist_pede->SetCanvasSilicon(a2hist_all->GetCanvasSilicon()); 

  a2hist_delay->SetCanvasCal0(a2hist_all->GetCanvasCal0());
  a2hist_delay->SetCanvasCal1(a2hist_all->GetCanvasCal1());
  a2hist_delay->SetCanvasADCs(a2hist_all->GetCanvasADCs());
  a2hist_delay->SetCanvasFlag(a2hist_all->GetCanvasFlag());
  a2hist_delay->SetCanvasTDC(a2hist_all->GetCanvasTDC()); 
  a2hist_delay->SetCanvasSilicon(a2hist_all->GetCanvasSilicon()); 
  

  // +++++++++ DRAW ++++++++++++++++++++++++++++++++++++
  if(drawlog){
    a1hist_all->SetLogy(); 
    a2hist_all->SetLogy();
  }
  
  bool checksame = false;
  cout << endl << "Draw Histograms: " << endl;
  if(drawall){
    a1hist_all->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_all->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_all->DrawADCs(checksame ? "same" : "");  
    a1hist_all->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_all->DrawTDC();}
    a2hist_all->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_all->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_all->DrawADCs(checksame ? "same" : "");  
    a2hist_all->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_all->DrawTDC();} 
    cout  << " Black: All Events " << endl;
    checksame = true;
  }

  if(drawbeam){
    a1hist_beam->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_beam->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_beam->DrawADCs(checksame ? "same" : "");  
    a1hist_beam->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_beam->DrawTDC();} 
    a2hist_beam->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_beam->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_beam->DrawADCs(checksame ? "same" : "");  
    a2hist_beam->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_beam->DrawTDC();}
    cout << " Red:   Events with BEAM Flag or LASER Flag " << endl;
    checksame = true;
  }
  
  if(drawpede){
    a1hist_pede->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_pede->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_pede->DrawADCs(checksame ? "same" : "");  
    a1hist_pede->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_pede->DrawTDC();}
    a2hist_pede->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_pede->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_pede->DrawADCs(checksame ? "same" : "");  
    a2hist_pede->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_pede->DrawTDC();}  
    cout << " Blue:  Events with PEDE Flag" << endl;
    checksame = true;
  }
 
  if(drawdelay){
    a1hist_delay->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_delay->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_delay->DrawADCs(checksame ? "same" : "");  
    a1hist_delay->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_delay->DrawTDC();}
    a2hist_delay->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_delay->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_delay->DrawADCs(checksame ? "same" : "");  
    a2hist_delay->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_delay->DrawTDC();}  
    cout << " Black: Delay ADC" << endl;
    checksame = true;
  }
  
  a1hist_all->SetLogySciFi(0); // Log OFF
  a1hist_beam->DrawSciFi();
  
  a2hist_all->SetLogySilicon(0); // Log OFF
  a2hist_beam->DrawSilicon();

  // ++++++++ SAVE CANVASES ++++++++++++++++++++++++++++++++++++
  char ch_run[20]="";
  char printname[256];
  char ch_tag[256]="";
  if(savecanvas){
    if(run > 0){sprintf(ch_run,"run%05d_",run);}
    if(strcmp(savecanvas_tag,"")!=0){sprintf(ch_tag,"_%s",savecanvas_tag);}
    
    if(a1hist_all->GetCanvasCal0()!=NULL){
      sprintf(printname,"%s/%sarm1_cal0%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasCal0()->Print(printname);
    }
    if(a1hist_all->GetCanvasCal1()!=NULL){
      sprintf(printname,"%s/%sarm1_cal1%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasCal1()->Print(printname);
    }
    if(a1hist_all->GetCanvasADCs()!=NULL){
      sprintf(printname,"%s/%sarm1_adcs%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasADCs()->Print(printname);
    }
    if(a1hist_all->GetCanvasFlag()!=NULL){
      sprintf(printname,"%s/%sarm1_flag%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasFlag()->Print(printname);
    }
    if(a1hist_all->GetCanvasTDC()!=NULL){
      sprintf(printname,"%s/%sarm1_tdc%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasTDC()->Print(printname);
    }
    if(a1hist_all->GetCanvasSciFi()!=NULL){
      sprintf(printname,"%s/%sarm1_scifi%s.gif",printpath,ch_run,ch_tag);
      a1hist_all->GetCanvasSciFi()->Print(printname);
    }  
    
    if(a2hist_all->GetCanvasCal0()!=NULL){
      sprintf(printname,"%s/%sarm2_cal0%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasCal0()->Print(printname);
    }
    if(a2hist_all->GetCanvasCal1()!=NULL){
      sprintf(printname,"%s/%sarm2_cal1%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasCal1()->Print(printname);
    }
    if(a2hist_all->GetCanvasADCs()!=NULL){
      sprintf(printname,"%s/%sarm2_adcs%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasADCs()->Print(printname);
    }
    if(a2hist_all->GetCanvasFlag()!=NULL){
      sprintf(printname,"%s/%sarm2_flag%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasFlag()->Print(printname);
    }
    if(a2hist_all->GetCanvasTDC()!=NULL){
      sprintf(printname,"%s/%sarm2_tdc%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasTDC()->Print(printname);
    }  

    if(a2hist_all->GetCanvasSilicon()!=NULL){
      sprintf(printname,"%s/%sarm2_si%s.gif",printpath,ch_run,ch_tag);
      a2hist_all->GetCanvasSilicon()->Print(printname);
    }
  }

  app.Run();
  
  return 0;
}
  
  
  
