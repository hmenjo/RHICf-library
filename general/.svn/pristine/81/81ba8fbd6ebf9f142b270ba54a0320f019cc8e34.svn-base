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
#include <TChain.h>
#include <TTree.h>
#include "LHCfEvent.h"
#include "A1Raw_pp2015.h"
#include "A2Raw_pp2015.h"
#include "A1Scl_pp2015.h"
#include "A2Scl_pp2015.h"
#include "A1RawToCal1.h"
#include "A2RawToCal1.h"
#include "A1Cal1AccumHist.h"
#include "A2Cal1AccumHist.h"
#include "A1PedeSubtract.h"
#include "A2PedeSubtract.h"
#include "A2RawToCal1Silicon.h"
#include "LHCfRunInfoTable.h"
#include "TLHCFDIPDATAH.h"
#include "TLHCFDIPDATAL.h"
#include "gsetup.h"
using namespace std;

enum FLAG_OP2015 {
  F_BPTX1           = 0x000001,
  F_BPTX2           = 0x000002,
  F_BPTXX           = 0x000004,
  F_LASER           = 0x000008,
  F_L2T_SHOWER      = 0x000010,
  F_L2T_SPECIAL     = 0x000020,
  F_L2T_PEDESTAL    = 0x000040,
  F_L2T_L1T         = 0x000080,
  F_L2T_FC          = 0x000100,
  F_STRG            = 0x000400,
  F_LTRG            = 0x000800,
  F_BEAMFLAG        = 0x001000,
  F_PEDEFLAG        = 0x002000,
  F_ATLAS_L1A       = 0x008000,
  F_A1_L1T          = 0x010000,
  F_A1_L3T          = 0x020000,
  F_A1_ENABLE       = 0x040000,
  F_A1_SHOWER_BPTXX = 0x080000,
  F_A2_L1T          = 0x100000,
  F_A2_L3T          = 0x200000,
  F_A2_ENABLE       = 0x400000,
  F_A2_SHOWER_BPTXX = 0x800000 
};

int DSCFlag(unsigned int flag, int tower,int layer){
  return ((flag >> (16*tower+layer))&0x1);
}


int FcDSCFlag(unsigned int flag, int channel){
  return ((flag >> (24+channel))&0x1);
}



int main(int argc,char **argv){  

  // ++++++++ Manage optioons +++++++++++++++++++++++++++++

  int   adcrange=0;         // Low:0  High:1  
  int   nfile=0;
  char  filename[10][256]; 
  int   nevent=100000;
  int   hist_nbin=210;
  int   hist_binmin=-104;
  int   hist_binmax=4096;
  bool  delay=false;
  bool  sdelay=false;
  bool  checkpede=false;
  char  ipedefile[256]=""; 
  char  pedefile[256]="";
  char  outfile[256]="";
  bool  drawall=true;
  bool  drawbeam=true;
  bool  drawpede=true; 
  bool  drawlog=false;
  char  printpath[256]="graphs/";
  bool  savecanvas=false;
  char  runinfofile[256]="";
  char  rundatafile[256]="";

  for(int ic=0;ic<argc;ic++){  
    if(strcmp(argv[ic],"-i")==0){
      strcpy(filename[nfile],argv[++ic]);
      strcpy(argv[ic],"");
      nfile++;
      if(nfile>10){
	cerr << "Only 10 input files are accepable." << endl;
	return 0;
      }
    }
    if(strcmp(argv[ic],"-o")==0 || strcmp(argv[ic],"-outfile")==0){
      strcpy(outfile,argv[++ic]);
      strcpy(argv[ic],"");
    }
    if(strcmp(argv[ic],"-ipede")==0){
      strcpy(ipedefile,argv[++ic]);
      strcpy(argv[ic],"");
    } 
    if(strcmp(argv[ic],"-opede")==0){
      checkpede=true;
      if((ic+1)==argc || *(argv[ic+1])=='-'){
	strcpy(pedefile,"pedestal.root");
      }
      else{
	strcpy(pedefile,argv[++ic]);  
	strcpy(argv[ic],"");
      }
    }  
    if(strcmp(argv[ic],"-High")==0){
      adcrange = 1;
    }
    if(strcmp(argv[ic],"-Low")==0){
      adcrange = 0;
    } 
    if(strcmp(argv[ic],"-subd")==0){
      sdelay = true;
    }  
    if(strcmp(argv[ic],"-delay")==0){
      delay = true;
    }
    if(strcmp(argv[ic],"-nevent")==0){
      nevent = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-nbin")==0){
      hist_nbin = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-binmin")==0){
      hist_binmin = atoi(argv[++ic]);
    } 
    if(strcmp(argv[ic],"-binmax")==0){
      hist_binmax = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-drawall")==0){
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
    if(strcmp(argv[ic],"-nodraw")==0){
      drawall = false;
      drawbeam = false;
      drawpede = false;
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
    if(strcmp(argv[ic],"--runinfo")==0 || strcmp(argv[ic],"-runinfo")==0){
      strcpy(runinfofile,argv[++ic]);
    }
    if(strcmp(argv[ic],"--rundata")==0 || strcmp(argv[ic],"-rundata")==0){
      strcpy(rundatafile,argv[++ic]);
    }
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
	   << " adchists ---------------------------------------------------------- \n"
	   << "  Draw the histgrams\n"
	   << "  Edited by H.MENJO\n"
	   << " \n" 
	   << " command) \n"
	   << " ./adchists_arm1 -i file [-i file2] [-o file] [-pede file] [-High] [-Low] [-delay] [-subd]\n" 
	   << "            [-nevent 10000] [-nbin 210] [-binmin -104] [-binmax 4096] \n"
	   << "\n"
	   << " options) \n"
	   << "  -i     :  Data File made by EventBuild\n"
	   << "            Max 10 files can read at same time. -i file1 -i file2 -i file3...\n"
	   << "  -o (-outfile) [file] : Save histograms in the file\n" 
	   << "  -ipede [file]  :  Read pedestal file.\n" 
	   << "  -opede [file]  :  Create pedestal file [default: pedestal.root]\n" 	 
	   << "  -Low   :  Draw histograms of Low range ADC counts\n"
	   << "  -High  :  Draw histograms of High range ADC counts\n"
	   << "  -subd  :  Subtract ADC counts with delayed gate from that with normal gate.\n"
	   << "            it affect only calorimeters and FCs.\n"
	   << "  -drawall/-nodrawall   : Draw (not draw) histograms for all events.\n"
	   << "  -drawbeam/-nodrawbeam : Draw (not draw) histograms for BEAM or LASER events.\n"
	   << "  -drawpede/-nodrawpede : Draw (not draw) histograms for PEDE events.\n"
	   << "  -nodraw :  Not draw any histograms. \n" 
	   << "  -nevent value : Maximum number of filled events. [default 10000]\n"
	   << "  -nbin   :  Number of bins of histograms [default: 210]\n"
	   << "  -binmin :  Minimum value of histogram bin [default: -104]\n"
	   << "  -binmax :  Maximum value of histogram bin [default: 4096]\n"
	   << "          :  if binmin==binmax, the range is set automatically.\n" 
	   << "  -Log    :  Set Y-axis to log scale\n"
	   << "  -print [path]   : Save Canvases\n" 
	   << "  -runinfo [file] : Create RunInfoTable\n" 
	   << "  -rundata [file] : Create a file including fisrt sc,diph and diph \n"
	   << "                    and last a1cal1 , a2cal1\n" 
	   << endl;
	return 0;
    }
  }
  
  if(nfile==0){
    cerr << "Error: Give a filename." << endl;
    return -1;
  }
  

  //TApplication app("adchists",&argc,argv);
  TRint app("adchists_arm1",&argc,argv,0,0,kTRUE);  
 
  gsetup();
  gStyle->SetOptStat(1110);
  gStyle->SetTitleX(0.5);
  gStyle->SetTitleW(0.7);
  gROOT->cd();
    
  // ++++++ OPEN INPUT FILES +++++++++++++++++++++++++++++++++++++
  
  int run=0;
  int nev=0;
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  for(int i=0;i<nfile;i++){ 
    cout << "Opened : " << filename[i] << endl;
    tree->Add(filename[i]);
  }
  
  tree->SetBranchAddress("ev.",&ev);
  nev = tree->GetEntries();
  tree->GetEntry(0);
  run = ev->run;
  cout << "RUN number : " << setw(6) << run << "   "
       << "Total Events in the file: " << nev << endl; 

  // +++++ INITIALIZE VALUABLES AND FUNCTIONS ++++++++++++++++++ 
  A1Cal1         *a1cal1 = new A1Cal1();
  A1RawToCal1    *a1conv = new A1RawToCal1();
  a1conv->ReadScifiPosTable("tables/GSObar_map9.tab");
  A1PedeSubtract *a1pedesubtract = new A1PedeSubtract();
  if(strcmp(ipedefile,"")!=0){
    a1pedesubtract->ReadFile(ipedefile);
  }

  A2Cal1             *a2cal1 = new A2Cal1();
  A2RawToCal1        *a2conv = new A2RawToCal1();
  A2RawToCal1Silicon *a2rawtocal1si = new A2RawToCal1Silicon();
  A2PedeSubtract     *a2pedesubtract = new A2PedeSubtract();
  if(strcmp(ipedefile,"")!=0){
    a2pedesubtract->ReadFile(ipedefile);
  }

  int    na1pede=0;
  A1Cal1 *a1pedestal = new A1Cal1("a1pedestal","Arm#1 Pedestal");
  a1pedestal->clear();
  
  int    na2pede=0;
  A2Cal1 *a2pedestal = new A2Cal1("a2pedestal","Arm#2 Pedestal");
  a2pedestal->clear();

  A1Scl_pp2015* a1scllast = new A1Scl_pp2015();
  A2Scl_pp2015* a2scllast = new A2Scl_pp2015();  

  TLHCFDIPDATAH      *diph;
  TLHCFDIPDATAL      *dipl;

  // +++++ INITIALIZE RUNINFO TABLE +++++++++++++++++++++++++++++
  LHCfRunInfo      *info;
  LHCfRunInfoTable *infotable = new LHCfRunInfoTable();
  if(strcmp(runinfofile,"")!=0){ infotable->ReadTable(runinfofile); }
  if(infotable->Get(run)){
    info = infotable->Get(run);
    info->clear_nevents("ext_comments");
  }
  else{
    info = infotable->CreateInfo(); 
    info->clear();
  }

  // +++++ INITIALIZE HISTOGRAMS +++++++++++++++++++++++++++++++
  char title[256];
  sprintf(title,"RUN%05d Arm1 all",run);
  A1Cal1AccumHist *a1hist_all = new A1Cal1AccumHist("a1hist_all",title);
  a1hist_all->SetHistNbin(hist_nbin);
  a1hist_all->SetHistBinMinimum(hist_binmin);
  a1hist_all->SetHistBinMaximum(hist_binmax);  
  a1hist_all->Initialize(); 
  sprintf(title,"RUN%05d Arm1 beam",run);
  A1Cal1AccumHist *a1hist_beam = new A1Cal1AccumHist("a1hist_beam",title);  
  a1hist_beam->SetHistNbin(hist_nbin);
  a1hist_beam->SetHistBinMinimum(hist_binmin);
  a1hist_beam->SetHistBinMaximum(hist_binmax); 
  a1hist_beam->Initialize();  
  sprintf(title,"RUN%05d Arm1 pede",run);
  A1Cal1AccumHist *a1hist_pede = new A1Cal1AccumHist("a1hist_pede",title);  
  a1hist_pede->SetHistNbin(hist_nbin);
  a1hist_pede->SetHistBinMinimum(hist_binmin);
  a1hist_pede->SetHistBinMaximum(hist_binmax); 
  a1hist_pede->Initialize(); 
  sprintf(title,"RUN%05d Arm1 delay",run);
  A1Cal1AccumHist *a1hist_delay = new A1Cal1AccumHist("a1hist_delay",title);  
  a1hist_delay->SetHistNbin(hist_nbin);
  a1hist_delay->SetHistBinMinimum(hist_binmin);
  a1hist_delay->SetHistBinMaximum(hist_binmax); 
  a1hist_delay->Initialize();  

  sprintf(title,"RUN%05d Arm2 all",run);
  A2Cal1AccumHist *a2hist_all = new A2Cal1AccumHist("a2hist_all",title);  
  a2hist_all->SetHistNbin(hist_nbin);
  a2hist_all->SetHistBinMinimum(hist_binmin);
  a2hist_all->SetHistBinMaximum(hist_binmax); 
  a2hist_all->Initialize();
  sprintf(title,"RUN%05d Arm2 beam",run);
  A2Cal1AccumHist *a2hist_beam = new A2Cal1AccumHist("a2hist_beam",title); 
  a2hist_beam->SetHistNbin(hist_nbin);
  a2hist_beam->SetHistBinMinimum(hist_binmin);
  a2hist_beam->SetHistBinMaximum(hist_binmax); 
  a2hist_beam->Initialize(); 
  sprintf(title,"RUN%05d Arm2 pede",run);
  A2Cal1AccumHist *a2hist_pede = new A2Cal1AccumHist("a2hist_pede",title);  
  a2hist_pede->SetHistNbin(hist_nbin);
  a2hist_pede->SetHistBinMinimum(hist_binmin);
  a2hist_pede->SetHistBinMaximum(hist_binmax); 
  a2hist_pede->Initialize(); 
  sprintf(title,"RUN%05d Arm2 delay",run); 
  A2Cal1AccumHist *a2hist_delay = new A2Cal1AccumHist("a2hist_delay",title);  
  a2hist_delay->SetHistNbin(hist_nbin);
  a2hist_delay->SetHistBinMinimum(hist_binmin);
  a2hist_delay->SetHistBinMaximum(hist_binmax); 
  a2hist_delay->Initialize(); 

  for(int itdc=2;itdc<=6;itdc++){
    a1hist_all->SetTDCHistogram(itdc,300,-350,-50);   
    a1hist_beam->SetTDCHistogram(itdc,300,-350,-50); 
    a1hist_pede->SetTDCHistogram(itdc,300,-350,-50);  
    a2hist_all->SetTDCHistogram(itdc, 500,-500,0);   
    a2hist_beam->SetTDCHistogram(itdc,500,-500,0); 
    a2hist_pede->SetTDCHistogram(itdc,500,-500,0);         
  }    

  // HISTOGRAM FOR BEAM CONFIGURATION
  TH1F *hbconf =new TH1F("hbconf","Bunch Conf",4000,0,4000);  
  TH1F *hbconf_a1_all  = (TH1F*)hbconf->Clone("hbconf_a1_all");
  TH1F *hbconf_a1_l2ta = (TH1F*)hbconf->Clone("hbconf_a1_l2ta");
  TH1F *hbconf_a2_all  = (TH1F*)hbconf->Clone("hbconf_a2_all"); 
  TH1F *hbconf_a2_l2ta = (TH1F*)hbconf->Clone("hbconf_a2_l2ta");
  TH1F *hbconf_a1_bptx1 = (TH1F*)hbconf->Clone("hbconf_a1_bptx1");
  TH1F *hbconf_a1_bptx2 = (TH1F*)hbconf->Clone("hbconf_a1_bptx2");
  TH1F *hbconf_a2_bptx1 = (TH1F*)hbconf->Clone("hbconf_a2_bptx1");
  TH1F *hbconf_a2_bptx2 = (TH1F*)hbconf->Clone("hbconf_a2_bptx2"); 

  // HISTOGRAMS FOR CHECKING DISCRIMINATOR THRESHOLD
  TH1F *h1_a1adc[2][16][2];  // [tower][layer][type(w/o or w/ selection)] 
  TH1F *h1_a2adc[2][16][2];  // [tower][layer][type(w/o or w/ selection)] 
  TH1F *h1_fcadc[2][4][2];   // [arm][channel][type(w/o or w/ selection)]
  for(int tower=0;tower<2;tower++){
    for(int layer=0;layer<16;layer++){
      for(int scut=0;scut<2;scut++){
	string hname,htitle;
	hname  = Form("h1_a1adc_%d_%02d_%d",tower,layer,scut);
	htitle = Form("Arm1 Tower:%d,Layer:%d,%s",tower,layer,(scut==0?"w/o":"w/o"));
	h1_a1adc[tower][layer][scut] = new TH1F(hname.c_str(),htitle.c_str(),600,-100,500);
	hname  = Form("h1_a2adc_%d_%02d_%d",tower,layer,scut);
	htitle = Form("Arm2 Tower:%d,Layer:%d,%s",tower,layer,(scut==0?"w/o":"w/o"));
	h1_a2adc[tower][layer][scut] = new TH1F(hname.c_str(),htitle.c_str(),600,-100,500);	
      }
    }
  }
  for(int arm=0;arm<2;arm++){
    for(int channel=0;channel<4;channel++){
      for(int scut=0;scut<2;scut++){
	string hname,htitle;
	hname  = Form("h1_%sfcadc_%d_%d",(arm==0?"a1":"a2"),channel,scut);
	htitle = Form("%s FC Channel:%d,%s",(arm==0?"Arm1":"Arm2"),channel,(scut==0?"w/o":"w/o"));
	h1_fcadc[arm][channel][scut] = new TH1F(hname.c_str(),htitle.c_str(),500,-1000,4000); 
      }
    }
  }

  // INITIALIZE RUN DATA FILE WHICH INCLUDING FIRST SLOWCONTROL AND DIP,
  // LAST EVENT DATA
  TFile *ofile_rundata = NULL;
  if(strcmp(rundatafile,"")!=0){
    ofile_rundata = new TFile(rundatafile,"UPDATE");
    gROOT->cd();
  }

  // ++++++++ LOOP ++++++++++++++++++++++++++++++++++++++++++++++++
  if(tree->GetEntries()<nevent){
    nevent = tree->GetEntries();
  } 

  const int arm2_clkoffset = 1;
  int na1ev_all   = 0;
  int na1ev_beam  = 0;
  int na1ev_pede  = 0;
  int na1ev_delay = 0; 
  int na2ev_all   = 0;
  int na2ev_beam  = 0;
  int na2ev_pede  = 0;
  int na2ev_delay = 0; 
  int tt,tstart=-1,tend=-1,tstart_tmp=-1,tend_tmp=-1;
  int tend_tmpa1=-1,tend_tmpa2=-1;  
  int lumiscan = -1;
  bool chk_diph_first=false,chk_dipl_first=false;
  int bunchpos = 0;
  int n_crcerror = 0;
  for(int i=0;i<nev;i++){
    ev->Delete();
    tree->GetEntry(i);

    // Fill to run info
    if(info->run<=0) {info->run = ev->run;}
    // Arm1
    if(ev->Check("a1raw")) { info->a1_nevent++; }
    if(ev->CheckA1Flag(0,F_BEAMFLAG)){
      if(ev->CheckA1Flag(0,F_L2T_SHOWER)) { info->a1_nevent_L2T_Shower++; } 
      if(ev->CheckA1Flag(0,F_L2T_SPECIAL)){ info->a1_nevent_L2T_Special++;}
      if(ev->CheckA1Flag(0,F_L2T_FC))     { info->a1_nevent_L2T_FC++;}
      if(ev->CheckA1Flag(0,F_L2T_L1T))    { info->a1_nevent_L2T_L1T++;}	
    }
    else if(ev->CheckA1Flag(0,F_PEDEFLAG)){
	if(ev->CheckA1Flag(0,F_L2T_PEDESTAL)) { info->a1_nevent_L2T_Pedestal++; }	
    }
    if(ev->CheckA1Flag(0,F_LASER)){ info->a1_nevent_laser++; }
    // Arm2
    if(ev->Check("a2raw")) { info->a2_nevent++;}
    if(ev->CheckA2Flag(0,F_BEAMFLAG)){
      if(ev->CheckA2Flag(0,F_L2T_SHOWER)) { info->a2_nevent_L2T_Shower++; } 
      if(ev->CheckA2Flag(0,F_L2T_SPECIAL)){ info->a2_nevent_L2T_Special++;}
      if(ev->CheckA2Flag(0,F_L2T_FC))     { info->a2_nevent_L2T_FC++;}
      if(ev->CheckA2Flag(0,F_L2T_L1T))    { info->a2_nevent_L2T_L1T++;}
    }
    else if(ev->CheckA2Flag(0,F_PEDEFLAG)){
      if(ev->CheckA2Flag(0,F_L2T_PEDESTAL)) { info->a2_nevent_L2T_Pedestal++; } 
    }
    if(ev->CheckA2Flag(0,F_LASER)){ info->a2_nevent_laser++;}
    // Scaler Event 
    if(ev->Check("a1scl")) { info->a1scl_nevent++;}
    if(ev->Check("a2scl")) { info->a2scl_nevent++;}
    // SlowControl 
    if(ev->Check("sc"))    {
      // Fill first slow control event to the rundata file. 
      if(ofile_rundata && info->sc_nevent==0){
	ofile_rundata->cd();
	ev->Get("sc")->Write("sc_first",TObject::kOverwrite);
	gROOT->cd();
      }
      info->sc_nevent++;
    } 
    if(ev->Check("diph"))  { 
      diph = (TLHCFDIPDATAH*)ev->Get("diph");
      // Fill first diph event to the rundata file. 
      if(ofile_rundata && chk_diph_first==false && diph->GetData()->time){
	ofile_rundata->cd();
	diph->Write("diph_first",TObject::kOverwrite);
	gROOT->cd();
	chk_diph_first = true;
      }
      // Check Luminosity Scan
      if(!strstr(diph->GetData()->Lumiscan.LumiScan_Status,"No Scan")){
	if(lumiscan!=1){
	  lumiscan = diph->GetData()->Lumiscan.IP;
	}
      }
      else{
	if(lumiscan==-1){lumiscan = 0;}
      }
      info->diph_nevent++;
    }       
    if(ev->Check("dipl"))  {  
      dipl = (TLHCFDIPDATAL*)ev->Get("dipl");
      // Fill first dipl event to the rundata file. 
      if(ofile_rundata && chk_dipl_first==false && dipl->GetData()->time){
	ofile_rundata->cd();
	ev->Get("dipl")->Write("dipl_first",TObject::kOverwrite);
	gROOT->cd();
	chk_dipl_first = true;
      }
      info->dipl_nevent++;
    }
    if(ev->Check("dipvh")) { info->dipvh_nevent++;}  

    tt = ev->EventTime();
    if(tt>0 && tstart<0){tstart = tt;}
    if(tt>0){tend = tt;}
    
    if(ev->Check("a1raw")) { info->analysis_a1_nevent++; }
    if(ev->CheckA1Flag(0,F_L2T_SHOWER)) { info->analysis_a1_nevent_L2TA++; }
    if(ev->Check("a2raw")) { info->analysis_a2_nevent++; }
    if(ev->CheckA2Flag(0,F_L2T_SHOWER)) { info->analysis_a2_nevent_L2TA++; }

    run = ev->run;

    // -------------- For Arm1 -------------------
    if( na1ev_all<nevent && ev->CheckA1Trg()){
      //a1raw = (A1Raw_pp2015*)ev->Get("a1raw");
      a1conv->Convert(ev->Get("a1raw"),a1cal1);
      tend_tmpa1 = (int)a1cal1->time[0];
      info->a1_nevent_l1t        = a1cal1->counter[5];
      info->a1_nevent_l1t_enable = a1cal1->counter[6];

      // Event selection for pedestal calculation 
      if(checkpede==true && a1cal1->flag_pede && 
	 a1cal1->flag[1]==0x0 && a1cal1->flag[2]==0x0){
	a1pedesubtract->FillPedeEvent(a1cal1);
	na1pede++;
      }
      
      if(sdelay==true){	
	a1pedesubtract->Subtraction(a1cal1);

	// For checking bunch configuration 
	bunchpos = a1cal1->counter[22];
	hbconf_a1_all->Fill(bunchpos); // Bunch position 
	if(a1cal1->flag_beam && 
	   (a1cal1->CheckFlag(a1cal1->flag[0],F_L2T_SHOWER) || 
	    a1cal1->CheckFlag(a1cal1->flag[0],F_L2T_SPECIAL))){
	  hbconf_a1_l2ta->Fill(bunchpos); // Bunch position 
	}
	if(a1cal1->CheckFlag(a1cal1->flag[0],F_BPTX1)) hbconf_a1_bptx1->Fill(bunchpos);
	if(a1cal1->CheckFlag(a1cal1->flag[0],F_BPTX2)) hbconf_a1_bptx2->Fill(bunchpos);	
      
      }

      na1ev_all  += a1hist_all->Fill(a1cal1,true,true,true);
      na1ev_beam += a1hist_beam->Fill(a1cal1,true,false,true);
      na1ev_pede += a1hist_pede->Fill(a1cal1,false,true,false); 

      // For Calculation of Discriminator Efficiency 
      if(sdelay==true){
	//  == For Calorimeter ==
	// Event Selection
	if( ev->CheckA2Trg() && 
	    (ev->CheckA2Flag(0,F_L2T_SHOWER) || ev->CheckA2Flag(0,F_L2T_SPECIAL))){
	  //if( ev->CheckA1Trg() && 
	  //(ev->CheckA1Flag(0,F_L2T_SHOWER) || ev->CheckA1Flag(0,F_L2T_SPECIAL))){
	  for(int tower=0;tower<2;tower++){
	    for(int layer=0;layer<16;layer++){
	      h1_a1adc[tower][layer][0]->Fill(a1cal1->cal[tower][layer][0]);
	      if(DSCFlag(a1cal1->flag[1],tower,layer)){
		h1_a1adc[tower][layer][1]->Fill(a1cal1->cal[tower][layer][0]);
	      }
	    }
	  }
	}
	// == For FC ==
	//if(ev->CheckA1Flag(0,F_L2T_SHOWER) || ev->CheckA1Flag(0,F_L2T_SPECIAL)){
	  for(int channel=0;channel<4;channel++){
	    h1_fcadc[0][channel][0]->Fill(a1cal1->fc[0][channel]);
	    if(FcDSCFlag(a1cal1->flag[0],channel)){
	      h1_fcadc[0][channel][1]->Fill(a1cal1->fc[0][channel]);
	    }
	  }
	//}
      } // end of DSC 

      
      // For delay ----
      for(int it=0;it<2;it++){
	  for(int il=0;il<16;il++){
	    for(int ir=0;ir<2;ir++){
	      a1cal1->cal[it][il][ir] = a1cal1->cald[it][il][ir];
	    }
	  }
      }
      for(int iarm=0;iarm<2;iarm++){
	for(int ich=0;ich<4;ich++){
	  a1cal1->fc[iarm][ich] = a1cal1->fcd[iarm][ich];
	}
      }
      for(int im=0;im<2;im++){
	a1cal1->laser[im] = a1cal1->laserd[im];
      }
      na1ev_delay  += a1hist_delay->Fill(a1cal1,true,true,true);



    }  
    // -------------- END For Arm1 ----------------------
    
    // ---------------   For Arm2   ---------------------
    if(na2ev_all<nevent && ev->CheckA2Trg() && ev->Check("a2raw")){
      //a2raw = ev->GetA2Raw("a2raw");
      a2conv->Convert(ev->Get("a2raw"),a2cal1);
      int checkcrc = a2rawtocal1si->Convert(ev->Get("a2raw"),a2cal1);
      tend_tmpa2 = (int)a2cal1->time[0]; 
      info->a2_nevent_l1t        = a2cal1->counter[5];
      info->a2_nevent_l1t_enable = a2cal1->counter[6];
      
      if(checkcrc==-1){n_crcerror++;}

      if(checkpede==true && checkcrc==0 && a2cal1->flag_pede && 
	 a2cal1->CheckFlag(a2cal1->flag[0],F_L2T_PEDESTAL) &&
	 a2cal1->flag[1]==0x0 && a2cal1->flag[2]==0x0){
	a2pedesubtract->FillPedeEvent(a2cal1);
	na2pede++;
      }
      
      if(sdelay==true){
	a2pedesubtract->Subtraction(a2cal1);

	bunchpos = a2cal1->counter[22];
	hbconf_a2_all->Fill(bunchpos);
	
	if(a2cal1->flag_beam &&
	   (a2cal1->CheckFlag(a2cal1->flag[0],F_L2T_SHOWER) || 
	    a2cal1->CheckFlag(a2cal1->flag[0],F_L2T_SPECIAL))){
	  hbconf_a2_l2ta->Fill(bunchpos);
	}
	if(a2cal1->CheckFlag(a2cal1->flag[0],F_BPTX1)) hbconf_a2_bptx1->Fill(bunchpos);
	if(a2cal1->CheckFlag(a2cal1->flag[0],F_BPTX2)) hbconf_a2_bptx2->Fill(bunchpos);
      }

      na2ev_all  += a2hist_all->Fill(a2cal1,true,true,true);
      na2ev_beam += a2hist_beam->Fill(a2cal1,true,false,true);
      na2ev_pede += a2hist_pede->Fill(a2cal1,false,true,false); 

      if(sdelay==true){
	//  == For Calorimeter ==
	// Event Selection
	if( ev->CheckA1Trg() && 
	    (ev->CheckA1Flag(0,F_L2T_SHOWER) || ev->CheckA1Flag(0,F_L2T_SPECIAL))){
	//if( ev->CheckA2Trg() && 
	//    (ev->CheckA2Flag(0,F_L2T_SHOWER) || ev->CheckA2Flag(0,F_L2T_SPECIAL))){
	  for(int tower=0;tower<2;tower++){
	    for(int layer=0;layer<16;layer++){
	      h1_a2adc[tower][layer][0]->Fill(a2cal1->cal[tower][layer][0]);
	      if(DSCFlag(a2cal1->flag[1],tower,layer)){
		h1_a2adc[tower][layer][1]->Fill(a2cal1->cal[tower][layer][0]);
	      }
	    }
	  }
	}
	// == For FC ==
	//if(ev->CheckA2Flag(0,F_L2T_SHOWER) || ev->CheckA2Flag(0,F_L2T_SPECIAL)){
	  for(int channel=0;channel<4;channel++){
	    h1_fcadc[1][channel][0]->Fill(a2cal1->fc[1][channel]);
	    if(FcDSCFlag(a2cal1->flag[0],channel)){
	      h1_fcadc[1][channel][1]->Fill(a2cal1->fc[1][channel]);
	    }
	  }
	//}
      } // end of DSC 
      

      // For delay ----
      for(int it=0;it<2;it++){
	  for(int il=0;il<16;il++){
	    for(int ir=0;ir<2;ir++){
	      a2cal1->cal[it][il][ir] = a2cal1->cald[it][il][ir];
	    }
	  }
      }
      for(int iarm=0;iarm<2;iarm++){
	for(int ich=0;ich<4;ich++){
	  a2cal1->fc[iarm][ich] = a2cal1->fcd[iarm][ich];
	}
      }
      for(int im=0;im<2;im++){
	a2cal1->laser[im] = a2cal1->laserd[im];
      }
      na2ev_delay  += a2hist_delay->Fill(a2cal1,true,true,true);
    }
    // -----------   End for Arm2    ------------------

    
    // --------- For SCL ----------
    if(ev->Check("a1scl")){
      a1scllast->copydata((A1Scl_pp2015*)ev->Get("a1scl"));
    }
    if(ev->Check("a2scl")){
      a2scllast->copydata((A2Scl_pp2015*)ev->Get("a2scl"));
    }

    if(na1ev_all>=nevent && na2ev_all>=nevent){break;}
    
    if(i!=0 && i%1000==0) {cerr << '*';}
    if(i!=0 && i%10000==0){cerr << " " << i << endl;}

  }
  cerr << endl;
  // ==============      END OF LOOP      =========================== 
  
  // ++++ Print run info ++++
  if(tend_tmpa1 < tend_tmpa2) {tend_tmp = tend_tmpa1;}
  else                        {tend_tmp = tend_tmpa2;}

  tstart_tmp = tstart;

  time_t ts,te;
  ts = (time_t) tstart;
  te = (time_t) tend;  
  cout << "DATA" << endl;
  cout << " START:  "  
       << setw(15) << tstart << "   "
       << asctime(localtime(&ts))
       << " END:    "  
       << setw(15) << tend << "   "
       << asctime(localtime(&te))
       << endl;  
  ts = (time_t) tstart_tmp;
  te = (time_t) tend_tmp;  
  cout << "CUT" << endl;
  cout << " START:  "  
       << setw(15) << tstart_tmp << "   "
       << asctime(localtime(&ts))
       << " END:    "  
       << setw(15) << tend_tmp << "   "
       << asctime(localtime(&te))
       << endl;

  if(strcmp(runinfofile,"")){
    info->nevent = nevent;
    info->start_time = tstart;
    info->end_time   = tend;
    info->analysis_cut_stime = tstart_tmp;
    info->analysis_cut_etime = tend_tmp;
    info->analysis_quality = 1;
    info->clear_beam("exc_comments");
    info->a2_ncrcerror = n_crcerror;
    
    int offset_beam1 = 176;
    int offset_beam2 = 176;
    
    const int range_displaced = 10;
    for(int i=1;i<hbconf_a1_all->GetNbinsX();i++){
      if(hbconf_a1_bptx2->GetBinContent(i)>0.1 &&
	 hbconf_a2_bptx1->GetBinContent(i)>0.1 ){
	info->beam1_bunches[info->beam1_nbunches] = i + offset_beam1;
	info->beam2_bunches[info->beam2_nbunches] = i + offset_beam2;
	info->beam1_tag[info->beam1_nbunches] = LHCfRunInfo::COLLIDING;
	info->beam2_tag[info->beam2_nbunches] = LHCfRunInfo::COLLIDING;	
	info->beam1_nbunches++;
	info->beam2_nbunches++;	
      }
      else if(hbconf_a1_bptx2->GetBinContent(i)>0.1){
	info->beam2_bunches[info->beam2_nbunches] = i + offset_beam2;
	if(hbconf_a2_bptx1->Integral(i-range_displaced,i+range_displaced) > 0.1){
	  info->beam2_tag[info->beam2_nbunches] = LHCfRunInfo::DISPLACED;
	}
	else{
	  info->beam2_tag[info->beam2_nbunches] = LHCfRunInfo::NONCOLLIDING; 
	}
	info->beam2_nbunches++;	
      }
      else if(hbconf_a2_bptx1->GetBinContent(i)>0.1){
	info->beam1_bunches[info->beam1_nbunches] = i + offset_beam1;
	if(hbconf_a1_bptx2->Integral(i-range_displaced,i+range_displaced) > 0.1){
	  info->beam1_tag[info->beam1_nbunches] = LHCfRunInfo::DISPLACED;
	}
	else{
	  info->beam1_tag[info->beam1_nbunches] = LHCfRunInfo::NONCOLLIDING; 
	}
	info->beam1_nbunches++;	
      }
      if(info->beam1_nbunches >= LHCfRunInfo::NBUNCHES || 
	 info->beam2_nbunches >= LHCfRunInfo::NBUNCHES ){
	cerr << " !! Over the NBUNCHES !! " << endl;
	break;
      }
    }
    info->done_lumiscan = lumiscan;
    infotable->WriteTable(runinfofile,1);
  }

  // +++++ Print +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  cout << endl;
  cout << "Numbers of filled events." << endl
       << " Arm1 #All           : " << na1ev_all  << endl
       << " Arm1 #BEAM or LASER : " << na1ev_beam << endl
       << " Arm1 #PEDE          : " << na1ev_pede << endl
       << " Arm2 #All           : " << na2ev_all  << endl
       << " Arm2 #BEAM or LASER : " << na2ev_beam << endl
       << " Arm2 #PEDE          : " << na2ev_pede << endl;

  // +++++ Create Canvases ++++++++++++++++++++++++++++++++++++++++++++++
  if(drawall || drawbeam || drawpede){
    a1hist_all->InitializeCanvases();
    a2hist_all->InitializeCanvases();
    //a1hist_delay->InitializeCanvases();
    //a2hist_delay->InitializeCanvases();
  }

  a1hist_beam->SetCanvasCal0(a1hist_all->GetCanvasCal0());
  a1hist_beam->SetCanvasCal1(a1hist_all->GetCanvasCal1());
  a1hist_beam->SetCanvasADCs(a1hist_all->GetCanvasADCs());
  a1hist_beam->SetCanvasFlag(a1hist_all->GetCanvasFlag());
  a1hist_beam->SetCanvasTDC(a1hist_all->GetCanvasTDC());

  a1hist_pede->SetCanvasCal0(a1hist_all->GetCanvasCal0());
  a1hist_pede->SetCanvasCal1(a1hist_all->GetCanvasCal1());
  a1hist_pede->SetCanvasADCs(a1hist_all->GetCanvasADCs());
  a1hist_pede->SetCanvasFlag(a1hist_all->GetCanvasFlag());
  a1hist_pede->SetCanvasTDC(a1hist_all->GetCanvasTDC()); 

  a2hist_beam->SetCanvasCal0(a2hist_all->GetCanvasCal0());
  a2hist_beam->SetCanvasCal1(a2hist_all->GetCanvasCal1());
  a2hist_beam->SetCanvasADCs(a2hist_all->GetCanvasADCs());
  a2hist_beam->SetCanvasFlag(a2hist_all->GetCanvasFlag()); 
  a2hist_beam->SetCanvasTDC(a2hist_all->GetCanvasTDC()); 
  
  a2hist_pede->SetCanvasCal0(a2hist_all->GetCanvasCal0());
  a2hist_pede->SetCanvasCal1(a2hist_all->GetCanvasCal1());
  a2hist_pede->SetCanvasADCs(a2hist_all->GetCanvasADCs());
  a2hist_pede->SetCanvasFlag(a2hist_all->GetCanvasFlag()); 
  a2hist_pede->SetCanvasTDC(a2hist_all->GetCanvasTDC()); 

  // +++++ Draw Histograms +++++++++++++++++++++++++++++++++++++++++++
  a1hist_all->SetLineColor(kBlack);
  a1hist_all->SetFillColor(kBlack);
  a1hist_all->SetFillStyle(3004);
  
  a1hist_beam->SetLineColor(kRed);
  a1hist_beam->SetFillColor(kRed); 
  a1hist_beam->SetFillStyle(3004);

  a1hist_pede->SetLineColor(kBlue);
  a1hist_pede->SetFillColor(kBlue); 
  a1hist_pede->SetFillStyle(3004); 
  
  a2hist_all->SetLineColor(kBlack);
  a2hist_all->SetFillColor(kBlack);
  a2hist_all->SetFillStyle(3004);
  
  a2hist_beam->SetLineColor(kRed);
  a2hist_beam->SetFillColor(kRed); 
  a2hist_beam->SetFillStyle(3004);

  a2hist_pede->SetLineColor(kBlue);
  a2hist_pede->SetFillColor(kBlue); 
  a2hist_pede->SetFillStyle(3004);

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

  // ++++++ Save Canvases ++++++++++++++++++++++++++++++++++++++++
  char printname[256];
  if(savecanvas){
    if(a1hist_all->GetCanvasCal0()!=NULL){
      sprintf(printname,"%s/run%05d_arm1_cal0.gif",printpath,run);
      a1hist_all->GetCanvasCal0()->Print(printname);
    }
    if(a1hist_all->GetCanvasCal1()!=NULL){
      sprintf(printname,"%s/run%05d_arm1_cal1.gif",printpath,run);
      a1hist_all->GetCanvasCal1()->Print(printname);
    }
    if(a1hist_all->GetCanvasADCs()!=NULL){
      sprintf(printname,"%s/run%05d_arm1_adcs.gif",printpath,run);
      a1hist_all->GetCanvasADCs()->Print(printname);
    }
    if(a1hist_all->GetCanvasFlag()!=NULL){
      sprintf(printname,"%s/run%05d_arm1_flag.gif",printpath,run);
      a1hist_all->GetCanvasFlag()->Print(printname);
    }
    if(a1hist_all->GetCanvasTDC()!=NULL){
      sprintf(printname,"%s/run%05d_arm1_tdc.gif",printpath,run);
      a1hist_all->GetCanvasTDC()->Print(printname);
    }
    
    if(a2hist_all->GetCanvasCal0()!=NULL){
      sprintf(printname,"%s/run%05d_arm2_cal0.gif",printpath,run);
      a2hist_all->GetCanvasCal0()->Print(printname);
    }
    if(a2hist_all->GetCanvasCal1()!=NULL){
      sprintf(printname,"%s/run%05d_arm2_cal1.gif",printpath,run);
      a2hist_all->GetCanvasCal1()->Print(printname);
    }
    if(a2hist_all->GetCanvasADCs()!=NULL){
      sprintf(printname,"%s/run%05d_arm2_adcs.gif",printpath,run);
      a2hist_all->GetCanvasADCs()->Print(printname);
    }
    if(a2hist_all->GetCanvasFlag()!=NULL){
      sprintf(printname,"%s/run%05d_arm2_flag.gif",printpath,run);
      a2hist_all->GetCanvasFlag()->Print(printname);
    }
    if(a2hist_all->GetCanvasTDC()!=NULL){
      sprintf(printname,"%s/run%05d_arm2_tdc.gif",printpath,run);
      a2hist_all->GetCanvasTDC()->Print(printname);
    }  
  }

  // +++++ Save the pedestal in the pedefile +++++++++++++++++++++++++
  if(checkpede==true){
    cout << endl;
    cout << "Number of Arm1 pedestal event = " << na1pede << endl;
    cout << "Number of Arm2 pedestal event = " << na2pede << endl;
    
    if(na1pede==0 && na2pede==0){
      cout << "Error: Cannot create pedestal file" << endl;
    }
    else{
      if(na1pede==0){
	cout << "Error: Cannot create Arm1 pedestal" << endl;
      } 
      else{
	a1pedesubtract->CalPedestal();
	a1pedesubtract->WriteFile(pedefile);
      } 
      
      if(na2pede==0){
	cout << "Error: Cannot create Arm2 pedestal" << endl;
      } 
      else{
	a2pedesubtract->CalPedestal();
	a2pedesubtract->WriteFile(pedefile);
      } 
      
      cout << "Create pedestal file: " << pedefile << endl;
    }
  }

  // +++++ Write Histograms in the outfile +++++++++++++++++++++++
  if(strcmp(outfile,"")!=0){
    TFile *ofile = new TFile(outfile,"RECREATE");
    a1hist_all->Write();
    a1hist_beam->Write(); 
    a1hist_pede->Write();
    a1hist_delay->Write();
    a2hist_all->Write();
    a2hist_beam->Write(); 
    a2hist_pede->Write();
    a2hist_delay->Write();  
    
    hbconf_a1_all->Write();
    hbconf_a1_l2ta->Write(); 
    hbconf_a2_all->Write();
    hbconf_a2_l2ta->Write();
    hbconf_a1_bptx1->Write();
    hbconf_a1_bptx2->Write();
    hbconf_a2_bptx1->Write();
    hbconf_a2_bptx2->Write();

    ofile->mkdir("DscHists");
    ofile->cd("DscHists");
    for(int tower=0;tower<2;tower++){
      for(int layer=0;layer<16;layer++){
	for(int scut=0;scut<2;scut++){ 
	  h1_a1adc[tower][layer][scut]->Write();
	  h1_a2adc[tower][layer][scut]->Write();  
	}
      }
    }
    for(int arm=0;arm<2;arm++){
      for(int channel=0;channel<4;channel++){
	for(int scut=0;scut<2;scut++){
	  h1_fcadc[arm][channel][scut]->Write();
	}
      }
    }

    cout << endl
	 << "Histograms were saved in \"" << outfile  << "\" : " 
	 << endl; 
    ofile->ls();
    cout << endl;
    ofile->Close();            
  }

  // +++++ Write last events (A1Cal1 & A1Cal2) ++++++++++++++++++
  if(ofile_rundata){
    ofile_rundata->cd();
    a1cal1->Write("a1cal1last",TObject::kOverwrite);
    a2cal1->Write("a2cal1last",TObject::kOverwrite);
    a1scllast->Write("a1scllast",TObject::kOverwrite);
    a2scllast->Write("a2scllast",TObject::kOverwrite);
    ofile_rundata->Close();
  }
  
  if(drawall || drawbeam || drawpede){
    app.Run();
  } 

  return 0;
  
}
