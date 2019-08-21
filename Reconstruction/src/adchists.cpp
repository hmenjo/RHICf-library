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
#include <TH1D.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TTree.h>
#include "LHCfEvent.h"
#include "RHICfRaw_Op2017.h"
#include "RHICfScl_Op2017.h"
#include "A1RawToCal1.h"
#include "A1Cal1ToCal2.h"
#include "A1Cal1AccumHist.h"
#include "A1PedeSubtract.h"

#include "RHICfRunInfoTable.h"
#include "gsetup.h"
using namespace std;



enum FLAG_RHICF {
  F_BPTX1           = 0x000001,
  F_BPTX2           = 0x000002,
  F_EXT_L1T         = 0x000004,
  F_BPTX_AND        = 0x000008,
  F_L2T_SHOWER      = 0x000010,
  F_L2T_PEDESTAL    = 0x000020,
  F_L2T_EXT         = 0x000040,
  F_L2T_SPECIAL1    = 0x000080,
  F_L2T_L1T         = 0x000100,
  F_L2T_SPECIAL2    = 0x000200,
  F_STRG            = 0x000400,
  F_LTRG            = 0x000800,
  F_BEAMFLAG        = 0x001000,
  F_PEDEFLAG        = 0x002000,
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
  int   nevent=100000000;
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
  A1Cal1ToCal2   *a2conv = new A1Cal1ToCal2();

  //RHICfCal1toCal2 *rhicfconv = new RHICfCal1toCal2();
  a1conv->ReadScifiPosTable("tables/GSObar_map9.tab");
  //a2conv->ReadADCRangeTable("tables/adcrange_003_20151120.dat");

  A1PedeSubtract *a1pedesubtract = new A1PedeSubtract();
  if(strcmp(ipedefile,"")!=0){
    a1pedesubtract->ReadFile(ipedefile);
  }
  

  int    na1pede=0;
  A1Cal1 *a1pedestal = new A1Cal1("a1pedestal","Arm#1 Pedestal");
  a1pedestal->clear();
  
  RHICfScl_Op2017* a1scllast = new RHICfScl_Op2017(); 

  // +++++ INITIALIZE RUNINFO TABLE +++++++++++++++++++++++++++++
  RHICfRunInfo      *info;
  RHICfRunInfoTable *infotable = new RHICfRunInfoTable();
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
  sprintf(title,"RUN%08d Arm1 all",run);
  A1Cal1AccumHist *a1hist_all = new A1Cal1AccumHist("a1hist_all",title);
  a1hist_all->SetHistNbin(hist_nbin);
  a1hist_all->SetHistBinMinimum(hist_binmin);
  a1hist_all->SetHistBinMaximum(hist_binmax);
  a1hist_all->SetDataVersion(A1Cal1AccumHist::VERSION_RHICF_OP2017);
  a1hist_all->Initialize(); 
  sprintf(title,"RUN%08d Arm1 beam",run);
  A1Cal1AccumHist *a1hist_beam = new A1Cal1AccumHist("a1hist_beam",title);  
  a1hist_beam->SetHistNbin(hist_nbin);
  a1hist_beam->SetHistBinMinimum(hist_binmin);
  a1hist_beam->SetHistBinMaximum(hist_binmax); 
  a1hist_beam->SetDataVersion(A1Cal1AccumHist::VERSION_RHICF_OP2017);
  a1hist_beam->Initialize();  
  sprintf(title,"RUN%08d Arm1 pede",run);
  A1Cal1AccumHist *a1hist_pede = new A1Cal1AccumHist("a1hist_pede",title);  
  a1hist_pede->SetHistNbin(hist_nbin);
  a1hist_pede->SetHistBinMinimum(hist_binmin);
  a1hist_pede->SetHistBinMaximum(hist_binmax); 
  a1hist_pede->SetDataVersion(A1Cal1AccumHist::VERSION_RHICF_OP2017);
  a1hist_pede->Initialize(); 
  sprintf(title,"RUN%08d Arm1 delay",run);
  A1Cal1AccumHist *a1hist_delay = new A1Cal1AccumHist("a1hist_delay",title);  
  a1hist_delay->SetHistNbin(hist_nbin);
  a1hist_delay->SetHistBinMinimum(hist_binmin);
  a1hist_delay->SetHistBinMaximum(hist_binmax); 
  a1hist_delay->SetDataVersion(A1Cal1AccumHist::VERSION_RHICF_OP2017);
  a1hist_delay->Initialize();  

  // HISTOGRAM FOR BEAM CONFIGURATION
  TH1D *hbconf               =new TH1D("hbconf","Bunch Conf",130,0,130);  
  TH1D *hbconf_L3T_ALL       = (TH1D*)hbconf->Clone("hbconf_L3T_ALL");
  TH1D *hbconf_L3T_Shower    = (TH1D*)hbconf->Clone("hbconf_L3T_Shower");
  TH1D *hbconf_L3T_Special1  = (TH1D*)hbconf->Clone("hbconf_L3T_Special1");
  TH1D *hbconf_L3T_Special2  = (TH1D*)hbconf->Clone("hbconf_L3T_Special2");
  TH1D *hbconf_L3T_Pedestal  = (TH1D*)hbconf->Clone("hbconf_L3T_Pedestal");
  TH1D *hbconf_L3T_Shower_TS = (TH1D*)hbconf->Clone("hbconf_L3T_Shower_TS");
  TH1D *hbconf_L3T_Shower_TL = (TH1D*)hbconf->Clone("hbconf_L3T_Shower_TL");

  // HISTOGRAMS FOR CHECKING DISCRIMINATOR THRESHOLD
  TH1D *h1_a1adc[2][16][2];  // [tower][layer][type(w/o or w/ selection)] 
  TH1D *h1_a1adc_before[2][16][2];  // [tower][layer][type(w/o or w/ selection)] for test
  TH1D *h1_a1adc_after[2][16][2];  // [tower][layer][type(w/o or w/ selection)] for test
  TH1D *h1_fcadc[2][4][2];   // [arm][channel][type(w/o or w/ selection)]
  for(int tower=0;tower<2;tower++){
    for(int layer=0;layer<16;layer++){
      for(int scut=0;scut<2;scut++){
	string hname,htitle;
	hname  = Form("h1_a1adc_%d_%02d_%d",tower,layer,scut);
	htitle = Form("Arm1 Tower:%d,Layer:%d,%s",tower,layer,(scut==0?"w/o":"w/o"));
	if(layer!=3){ 
	  h1_a1adc[tower][layer][scut] = new TH1D(hname.c_str(),htitle.c_str(),1000,-100,900);

	}
	else{
	  h1_a1adc[tower][layer][scut] = new TH1D(hname.c_str(),htitle.c_str(),1000,-100,2000);
	  //h1_a1adc[tower][layer][scut] = new TH1D(hname.c_str(),htitle.c_str(),1000,0,4000);
	}
      }
    }
  }

  for(int arm=0;arm<1;arm++){
    for(int channel=0;channel<4;channel++){
      for(int scut=0;scut<2;scut++){
	string hname,htitle;
	hname  = Form("h1_%sfcadc_%d_%d",(arm==0?"a1":"a2"),channel,scut);
	htitle = Form("%s FC Channel:%d,%s",(arm==0?"Arm1":"Arm2"),channel,(scut==0?"w/o":"w/o"));
	h1_fcadc[arm][channel][scut] = new TH1D(hname.c_str(),htitle.c_str(),500,-1000,4000); 
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
  int tt,tstart=-1,tend=-1,tstart_tmp=-1,tend_tmp=-1;
  int tend_tmpa1=-1,tend_tmpa2=-1;  
  int lumiscan = -1;
  bool chk_diph_first=false,chk_dipl_first=false;
  int bunchpos = 0;
  int n_crcerror = 0;
  for(int i=0;i<nev;i++){
    ev->Delete();
    tree->GetEntry(i);

	 UInt_t flag_trigger = 0;
	 RHICfRaw_Op2017 *a1raw = NULL; 
	 if(ev->Check("a1raw")){
		a1raw = (RHICfRaw_Op2017*) ev->Get("a1raw");
		flag_trigger = ((a1raw->trgm[0] >> 20) & 0x3);
		// flag_trigger = 0x1; // For debug
	 }

    // Fill to run info
    if(info->run<=0) {info->run = ev->run;}
    // RHICf Trigger Event 
    if((flag_trigger&0x1)){
      if(ev->Check("a1raw")) { info->a1_nevent++; }
      if(ev->CheckA1Flag(0,F_BEAMFLAG)){
	if(ev->CheckA1Flag(0,F_L2T_SHOWER))  { info->a1_nevent_L3T_Shower++; } 
	if(ev->CheckA1Flag(0,F_L2T_SPECIAL1)){ info->a1_nevent_L3T_Special1++;}
	if(ev->CheckA1Flag(0,F_L2T_SPECIAL2)){ info->a1_nevent_L3T_Special2++;}
	if(ev->CheckA1Flag(0,F_L2T_L1T))     { info->a1_nevent_L3T_L1T++;}	
	if(ev->CheckA1Flag(0,F_STRG))        { info->a1_nevent_L3T_Shower_TS++;}	
	if(ev->CheckA1Flag(0,F_LTRG))        { info->a1_nevent_L3T_Shower_TL++;}	
      }
      else if(ev->CheckA1Flag(0,F_PEDEFLAG)){
	if(ev->CheckA1Flag(0,F_L2T_PEDESTAL))  { info->a1_nevent_L3T_Pedestal++; }	
      }
      if(ev->Check("a1raw")) { info->analysis_a1_nevent++; }
    }
    // Scaler Event 
    if(ev->Check("a1scl")) { info->a1scl_nevent++;}   
    // For Common Operation 
    if(flag_trigger==0x3)  { info->a1_nevent_L3T_STAR++;}
    if(flag_trigger==0x2)  { info->a1_nevent_STAR_Only++;}
    
    tt = ev->EventTime();
    if(tt>0 && tstart<0){tstart = tt;}
    if(tt>0){tend = tt;}
    
    run = ev->run;

    // -------------- For Arm1 -------------------
    if((flag_trigger&0x1)){
      a1conv->Convert(ev->Get("a1raw"),a1cal1);
      tend_tmpa1 = (int)a1cal1->time[0];
      info->a1_nevent_l1t        = (Long64_t)a1cal1->counter[2]+(((Long64_t)a1cal1->counter[3])<<32);
      info->a1_nevent_l1t_enable = (Long64_t)a1cal1->counter[4]+(((Long64_t)a1cal1->counter[5])<<32);

      // Event selection for pedestal calculation 
      if(checkpede==true      && a1cal1->flag_pede && 
			a1cal1->flag[1]==0x0 ){
		  a1pedesubtract->FillPedeEvent(a1cal1);
		  na1pede++;
      }
      
      if(sdelay==true){	
		  a1pedesubtract->Subtraction(a1cal1);
		}

      na1ev_all  += a1hist_all->Fill(a1cal1,true,true,true);
      na1ev_beam += a1hist_beam->Fill(a1cal1,true,false,true);
      na1ev_pede += a1hist_pede->Fill(a1cal1,false,true,false); 

		// For checking bunch configuration ------
		bunchpos = a1cal1->counter[27]+0.5;
		hbconf_L3T_ALL->Fill(bunchpos); 
		if(a1cal1->flag_beam){
		  if(a1cal1->CheckFlag(a1cal1->flag[0],F_L2T_SHOWER))  {
			 hbconf_L3T_Shower->Fill(bunchpos);
			 if(a1cal1->CheckFlag(a1cal1->flag[0],F_STRG)){hbconf_L3T_Shower_TS->Fill(bunchpos);}
			 if(a1cal1->CheckFlag(a1cal1->flag[0],F_LTRG)){hbconf_L3T_Shower_TL->Fill(bunchpos);}
		  }
		  if(a1cal1->CheckFlag(a1cal1->flag[0],F_L2T_SPECIAL1)){ hbconf_L3T_Special1->Fill(bunchpos);}
		  if(a1cal1->CheckFlag(a1cal1->flag[0],F_L2T_SPECIAL2)){ hbconf_L3T_Special2->Fill(bunchpos);}
		}
		else if(a1cal1->flag_pede){
		  hbconf_L3T_Pedestal->Fill(bunchpos);
		}
		// ---------------------------------------
		
      // For Calculation of Discriminator Efficiency 
      if(sdelay==true){
	  // == For Calorimeter ==
	  // Event Selection
	if(  ev->CheckA1Trg() && 
	     ev->CheckA1Flag(0,F_L2T_SHOWER)){
	      for(int tower =0;tower<2;tower++){
	      	      for(int layer=0;layer<16;layer++){
	      	    	    h1_a1adc[tower][layer][0]->Fill(a1cal1->cal[tower][layer][1]);
	      	    	    if(DSCFlag(a1cal1->flag[1],tower,layer)){
	      	    	     h1_a1adc[tower][layer][1]->Fill(a1cal1->cal[tower][layer][1]);
	      	    	    }
		      }
	      }
	
	
	      bool dsc[2][16]={{false}};
	      bool dsc_shower[2]= {false};
	      for(int tower=0;tower<2;tower++){
		for(int layer=0;layer<16;layer++){
		  if(DSCFlag(a1cal1->flag[1],tower,layer))
		    dsc[tower][layer] = true;
		}
	      }
	
		  
	


		    bool pat_trig[2][14] = {{false}};
		    for(int tower =0; tower<2; tower++){
		      if(dsc[tower][0]&&dsc[tower][1]&&dsc[tower][2]) pat_trig[tower][0] = true;
		      if(dsc[tower][1]&&dsc[tower][2]) pat_trig[tower][1] = true;
		      if(dsc[tower][2]&&dsc[tower][4]) pat_trig[tower][2] = true;
		      if(dsc[tower][4]&&dsc[tower][5]) pat_trig[tower][3] = true;
		      if(dsc[tower][4]&&dsc[tower][5]&&dsc[tower][6]) pat_trig[tower][4] = true;
		      if(dsc[tower][5]&&dsc[tower][6]&&dsc[tower][7]) pat_trig[tower][5] = true;
		      if(dsc[tower][6]&&dsc[tower][7]&&dsc[tower][8]) pat_trig[tower][6] = true;
		      if(dsc[tower][7]&&dsc[tower][8]&&dsc[tower][9]) pat_trig[tower][7] = true;
		      if(dsc[tower][8]&&dsc[tower][9]&&dsc[tower][10]) pat_trig[tower][8] = true;
		      if(dsc[tower][9]&&dsc[tower][10]&&dsc[tower][11]) pat_trig[tower][9] = true;
		      if(dsc[tower][10]&&dsc[tower][11]&&dsc[tower][12]) pat_trig[tower][10] = true;
		      if(dsc[tower][11]&&dsc[tower][12]&&dsc[tower][13]) pat_trig[tower][11] = true;
		      if(dsc[tower][12]&&dsc[tower][13]&&dsc[tower][14]) pat_trig[tower][12] = true;
		      if(dsc[tower][13]&&dsc[tower][14]&&dsc[tower][15]) pat_trig[tower][13] = true;
		    }
		    bool nonbias[2][16] = {{false}};
		    bool shower_trg[2] = {false};
		    for(int tower =0; tower <2; tower++){
		      if(pat_trig[tower][1]||pat_trig[tower][2]||pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][0] = true;
		      if(pat_trig[tower][2]||pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][1] = true;
		      if(pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][2] = true;
		      if(dsc[tower][0]||dsc[tower][1]||dsc[tower][2]||
		    	 dsc[tower][3]||
		    	 dsc[tower][4]||dsc[tower][5]||dsc[tower][6]||
		    	 dsc[tower][7]||dsc[tower][8]||dsc[tower][9]||
		    	 dsc[tower][10]||dsc[tower][11]||dsc[tower][12]||
		    	 dsc[tower][13]||dsc[tower][14]||dsc[tower][15]
		    	 )nonbias[tower][3] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||
		    	 pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][4] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][5] = true;
		       if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][6] = true;
		       if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][7] = true;
		       if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][8] = true; 
		       if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][9] = true;
		       if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][10] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])nonbias[tower][11] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][13])nonbias[tower][12] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10])nonbias[tower][13] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11])nonbias[tower][14] = true;
		      if(pat_trig[tower][0]||pat_trig[tower][1]||pat_trig[tower][2]||
		    	 pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12])
		    	nonbias[tower][15] = true;
		      if(pat_trig[tower][0]||
		    	 pat_trig[tower][1]||pat_trig[tower][2]||pat_trig[tower][3]||
		    	 pat_trig[tower][4]||pat_trig[tower][5]||pat_trig[tower][6]||
		    	 pat_trig[tower][7]||pat_trig[tower][8]||pat_trig[tower][9]||
		    	 pat_trig[tower][10]||pat_trig[tower][11]||pat_trig[tower][12]||
		    	 pat_trig[tower][13])shower_trg[tower] = true;
		      
		    }
		      
		    //non bias selection
		    		       
		    //for(int tower =0;tower<2;tower++){
		    //  for(int layer=0;layer<16;layer++){
		    //	if(layer == 3){
		    //	  if(nonbias[tower][layer] == true){
		    //	    h1_a1adc[tower][layer][0]->Fill(a1cal1->cal[tower][layer][1]);
		    //	    if(dsc[tower][layer] == true){
		    //	      h1_a1adc[tower][layer][1]->Fill(a1cal1->cal[tower][layer][1]);
		    //	    }
		    //	  }
		    //	}
		    //	else if(nonbias[tower][layer] == true){
		    //	  h1_a1adc[tower][layer][0]->Fill(a1cal1->cal[tower][layer][0]);
		    //	  if(dsc[tower][layer] == true){
		    //	    h1_a1adc[tower][layer][1]->Fill(a1cal1->cal[tower][layer][0]);  
		    //	  }
		    //	}
		    //  }
		    //}
	}
	
		    
		    
		  
           
      		 // end of DSC 
	          
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
      }
    
    // -------------- END For Arm1 ----------------------
	 
    // --------- For SCL ----------
    if(ev->Check("a1scl")){
      a1scllast->copydata((RHICfScl_Op2017*)ev->Get("a1scl"));
    }

    if(na1ev_all>=nevent){break;}
    
    if(i!=0 && i%1000==0) {cerr << '*';}
    if(i!=0 && i%10000==0){cerr << " " << i << endl;}

  }
  cerr << endl;
  // ==============      END OF LOOP      =========================== 
  
  // ++++ Print run info ++++
  tend_tmp = tend_tmpa1;
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

  // Fill the run info file up ++++++++++++++++++++++++++++++++++
  if(strcmp(runinfofile,"")){
    info->nevent = nevent;
    info->start_time = tstart;
    info->end_time   = tend;
    info->analysis_cut_stime = tstart_tmp;
    info->analysis_cut_etime = tend_tmp;
    info->analysis_quality = 1;
    info->clear_beam("exc_comments");
    
    infotable->WriteTable(runinfofile,1);
  }
  
  // +++++ Print +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  cout << endl;
  cout << "Numbers of filled events." << endl
       << " Arm1 #All           : " << na1ev_all  << endl
       << " Arm1 #BEAM or LASER : " << na1ev_beam << endl
       << " Arm1 #PEDE          : " << na1ev_pede << endl;

  // +++++ Create Canvases ++++++++++++++++++++++++++++++++++++++++++++++
  if(drawall || drawbeam || drawpede){
    a1hist_all->InitializeCanvases();
    //a1hist_delay->InitializeCanvases();
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
  
  if(drawlog){
    a1hist_all->SetLogy(); 
  }

  bool checksame = false;
  cout << endl << "Draw Histograms: " << endl;
  if(drawall){
    a1hist_all->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_all->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_all->DrawADCs(checksame ? "same" : "");  
    a1hist_all->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_all->DrawTDC();}
    cout  << " Black: All Events " << endl;
    checksame = true;
  }
  
  if(drawbeam){
    a1hist_beam->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_beam->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_beam->DrawADCs(checksame ? "same" : "");  
    a1hist_beam->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_beam->DrawTDC();} 
    cout << " Red:   Events with BEAM Flag or LASER Flag " << endl;
    checksame = true;
  }
  
  if(drawpede){
    a1hist_pede->DrawCal0(adcrange, checksame ? "same" : "");
    a1hist_pede->DrawCal1(adcrange, checksame ? "same" : ""); 
    a1hist_pede->DrawADCs(checksame ? "same" : "");  
    a1hist_pede->DrawFlag(checksame ? "same" : "");
    if(!checksame){a1hist_pede->DrawTDC();}
    cout << " Blue:  Events with PEDE Flag" << endl;
    checksame = true;
  }

  // ++++++ Save Canvases ++++++++++++++++++++++++++++++++++++++++
  char printname[256];
  if(savecanvas){
    if(a1hist_all->GetCanvasCal0()!=NULL){
      sprintf(printname,"%s/run%08d_arm1_cal0.gif",printpath,run);
      a1hist_all->GetCanvasCal0()->Print(printname);
    }
    if(a1hist_all->GetCanvasCal1()!=NULL){
      sprintf(printname,"%s/run%08d_arm1_cal1.gif",printpath,run);
      a1hist_all->GetCanvasCal1()->Print(printname);
    }
    if(a1hist_all->GetCanvasADCs()!=NULL){
      sprintf(printname,"%s/run%08d_arm1_adcs.gif",printpath,run);
      a1hist_all->GetCanvasADCs()->Print(printname);
    }
    
    if(a1hist_all->GetCanvasFlag()!=NULL){
      sprintf(printname,"%s/run%08d_arm1_flag.gif",printpath,run);
      a1hist_all->GetCanvasFlag()->Print(printname);
    }
    if(a1hist_all->GetCanvasTDC()!=NULL){
      sprintf(printname,"%s/run%08d_arm1_tdc.gif",printpath,run);
      a1hist_all->GetCanvasTDC()->Print(printname);
    }
  }

  // +++++ Save the pedestal in the pedefile +++++++++++++++++++++++++
  if(checkpede==true){
    cout << endl;
    cout << "Number of Arm1 pedestal event = " << na1pede << endl;
 
    if(na1pede==0){
      cout << "Error: Cannot create Arm1 pedestal" << endl;
    } 
    else{
      a1pedesubtract->CalPedestal();
      a1pedesubtract->WriteFile(pedefile);
    } 
      
    cout << "Create pedestal file: " << pedefile << endl;
  }

  // +++++ Write Histograms in the outfile +++++++++++++++++++++++
  if(strcmp(outfile,"")!=0){
    TFile *ofile = new TFile(outfile,"RECREATE");
    a1hist_all->Write();
    a1hist_beam->Write(); 
    a1hist_pede->Write();
    a1hist_delay->Write();

    hbconf_L3T_ALL->Write();
    hbconf_L3T_Shower->Write(); 
	 hbconf_L3T_Shower_TS->Write(); 
	 hbconf_L3T_Shower_TL->Write(); 
    hbconf_L3T_Special1->Write();
    hbconf_L3T_Special2->Write();
    hbconf_L3T_Pedestal->Write();	 

    ofile->mkdir("DscHists");
    ofile->cd("DscHists");
    for(int tower=0;tower<2;tower++){
      for(int layer=0;layer<16;layer++){
		  for(int scut=0;scut<2;scut++){ 
			 h1_a1adc[tower][layer][scut]->Write();
		  }
      }
    }
    for(int arm=0;arm<1;arm++){
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
    a1scllast->Write("a1scllast",TObject::kOverwrite);
    ofile_rundata->Close();
  }
  
  if(drawall || drawbeam || drawpede){
    app.Run();
  } 

  return 0;
  
 }
