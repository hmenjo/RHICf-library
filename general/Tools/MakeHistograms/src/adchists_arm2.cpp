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
#include "A1RawToCal1.h"
#include "A2RawToCal1.h"
#include "A2Cal1AccumHist.h"
#include "A1PedeSubtract.h"
#include "A2PedeSubtract.h"
#include "A2RawToCal1Silicon.h"
#include "gsetup.h"
using namespace std;

int main(int argc,char **argv){  

  int   adcrange=0;
  int   nfile=0;
  char  filename[10][256]; 
  int   nevent=100000;
  int   hist_nbin=210;
  int   hist_binmin=-104;
  int   hist_binmax=4096;
  bool  delay=false;
  bool  sdelay=false;
  bool  checkpede=false;
  char  pedefile[256]="";  
  char  outfile[256]="";
  bool  drawall=true;
  bool  drawbeam=true;
  bool  drawpede=true; 
  bool  drawlog=false;
  char  printpath[256]="graphs/";
  bool  savecanvas=false;

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
    if(strcmp(argv[ic],"-pede")==0){
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
    if(strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0 || argc==1){
      cout << endl
	   << " adchists_arm2 ------------------------------------------------------ \n"
	   << "  Draw the histgrams of Arm2 Raw Data \n" 
	   << "  Edited by H.MENJO\n"
	   << " \n" 
	   << " command) \n"
	   << " ./adchists_arm2 -i file [-i file2] [-o file] [-pede file] [-High] [-Low] [-delay] [-subd]\n"
	   << "            [-nevent 10000] [-nbin 210] [-binmin -104] [-binmax 4096] \n"
	   << "            [-drawall/-nodrawall] [-drawbeam/-nodrawbeam] [-drawpede/-nodrawpede]\n"
	   << "\n"
	   << " options) \n"
	   << "  -i     :  Data File made by EventBuild\n"
	   << "            Max 10 files can read at same time. -i file1 -i file2 -i file3..."
	   << "  -o (-outfile) [file] : Save histograms in the file\n" 
	   << "  -pede [file]  : Create pedestal file [default: pedestal.root]\n" 
	   << "  -Low   :  Draw histograms of Low range ADC counts\n"
	   << "  -High  :  Draw histograms of High range ADC counts\n"
	   << "  -delay :  Make histograms of ADC counts with delayed gate\n"
	   << "            it affect only calorimeters + FC\n"
	   << "  -subd  :  Subtract ADC counts with delayed gate from that with normal gate.\n"
	   << "            it affect only calorimeters + FC.\n" 
	   << "  -drawall/-nodrawall   : Draw (not draw) histograms for all events.\n"
	   << "  -drawbeam/-nodrawbeam : Draw (not draw) histograms for BEAM or LASER events.\n"
	   << "  -drawpede/-nodrawpede : Draw (not draw) histograms for PEDE events.\n"
	   << "  -nodraw :  Not draw any histograms. \n"  
	   << "  -nevent value : Maximum number of filled events. [defult 10000]\n"
	   << "  -nbin   :  Number of bins of histograms [default: 210]\n"
	   << "  -binmin :  Minimum value of histogram bin [default: -104]\n"
	   << "  -binmax :  Maximum value of histogram bin [default: 4096]\n"
	   << "          :  if binmin==binmax, the range is set automatically.\n" 
	   << "  -Log    :  Set Y-axis to log scale\n"  
	   << "  -print [path] :  Save Canvases\n" 
	   << endl;
	return 0;
    }
  }
  
  if(nfile==0){
    cerr << "Error: Give a filename." << endl;
    return -1;
  }
  
  //TApplication app("adchists_arm2",&tmp,argv);
  TRint app("adchists_arm2",&argc,argv,0,0,kTRUE);  

  gsetup();
  gStyle->SetOptStat(1110);
  gStyle->SetTitleX(0.01);
  gStyle->SetTitleW(0.7);

  gROOT->cd();  
  
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

  A1Cal1 *a1cal1 = new A1Cal1();
  A1RawToCal1 *a1conv = new A1RawToCal1();
  a1conv->ReadScifiPosTable("config/scifi_pos_table_080408.dat");
  int    na1pede=0;
 
  A2Cal1 *a2cal1 = new A2Cal1();
  A2RawToCal1 *a2conv = new A2RawToCal1();
  int    na2pede=0;
  
  char title[256];
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

  for(int itdc=2;itdc<=6;itdc++){
    a2hist_all->SetTDCHistogram(itdc, 500,-500, 0);   
    a2hist_beam->SetTDCHistogram(itdc,500,-500,0); 
    a2hist_pede->SetTDCHistogram(itdc,500,-500,0);       
  }    

  A1PedeSubtract* a1pedesubtract = new A1PedeSubtract();
  
  A2RawToCal1Silicon *a2rawtocal1si = new A2RawToCal1Silicon();
  A2PedeSubtract* a2pedesubtract = new A2PedeSubtract();

  if(tree->GetEntries()<nevent){
    nevent = tree->GetEntries();
  } 
 
  int nev_all  = 0;
  int nev_beam = 0;
  int nev_pede = 0;
  for(int i=0;i<nev;i++){
    ev->Delete(); 
    tree->GetEntry(i); 
    if(ev->CheckA2Trg()){
      a2conv->Convert(ev->GetA2Raw("a2raw"),a2cal1);

      if(checkpede==true && a2cal1->flag_pede){
	a2rawtocal1si->Convert(ev->GetA2Raw("a2raw"),a2cal1);
	a2pedesubtract->FillPedeEvent(a2cal1);
	na2pede++;
      }
    
      if(delay==true){
	for(int it=0;it<2;it++){
	  for(int il=0;il<16;il++){
	    for(int ir=0;ir<2;ir++){
	      a2cal1->cal[it][il][ir] = a2cal1->cald[it][il][ir];
	    }
	  }
	}
	for(int iarm=0;iarm<2;iarm++){
	  for(int ich=0;ich<4;ich++){
	    a2cal1->fc[iarm][ich] = ev->GetA2Raw("a2raw")->adc3[8+iarm*4+ich];
	  }
	}
      }
      if(sdelay==true){
// 	for(int it=0;it<2;it++){
// 	  for(int il=0;il<16;il++){
// 	    for(int ir=0;ir<2;ir++){
// 	      a2cal1->cal[it][il][ir] -= a2cal1->cald[it][il][ir];
// 	    }
// 	  }
// 	}	
// 	for(int iarm=0;iarm<2;iarm++){
// 	  for(int ich=0;ich<4;ich++){
// 	    a2cal1->fc[iarm][ich] -= ev->GetA2Raw("a2raw")->adc3[8+iarm*4+ich];
// 	  }
// 	}
	a2pedesubtract->Subtraction(a2cal1);
      }

      nev_all  += a2hist_all->Fill(a2cal1,true,true,true);
      nev_beam += a2hist_beam->Fill(a2cal1,true,false,true); 
      nev_pede += a2hist_pede->Fill(a2cal1,false,true,false); 
    }  
    
    if(ev->CheckA1Trg()){
      a1conv->Convert(ev->GetA1Raw("a1raw"),a1cal1);
      if(checkpede==true && a1cal1->flag_pede){
	a1pedesubtract->FillPedeEvent(a1cal1);
	na1pede++;
      }
    }

    if(nev_all>=nevent){break;}   
    if(i!=0 && i%1000==0) {cerr << '*';}
    if(i!=0 && i%10000==0){cerr << " " << i << endl;}
  }
  cerr << endl;

  // +++++ Print +++++
  cout << endl;
  cout << "Numbers of filled events." << endl
       << " #All           : " << nev_all  << endl
       << " #BEAM or LASER : " << nev_beam << endl
       << " #PEDE          : " << nev_pede << endl;
  
  // +++++ Create Canvases +++++
  if( drawall || drawbeam || drawpede){ a2hist_all->InitializeCanvases(); }

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
  
  // +++++ Draw Histograms +++++
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
    a2hist_all->SetLogy();
  }
 
  bool checksame = false;
  cout << endl << "Draw Histograms: " << endl;
  if(drawall){
    //a2hist_all->Draw(adcrange, checksame ? "same" : "");
    a2hist_all->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_all->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_all->DrawADCs(checksame ? "same" : "");  
    a2hist_all->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_all->DrawTDC();}
    cout  << " Black: All Events " << endl;
    checksame = true;
  }
  
  if(drawbeam){
    //a2hist_beam->Draw(adcrange, checksame ? "same" : "");
    a2hist_beam->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_beam->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_beam->DrawADCs(checksame ? "same" : "");  
    a2hist_beam->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_beam->DrawTDC();}
    cout << " Red:   Events with BEAM Flag or LASER Flag " << endl;
    checksame = true;
  }
  
  if(drawpede){
    //a2hist_pede->Draw(adcrange, checksame ? "same" : "");
    a2hist_pede->DrawCal0(adcrange, checksame ? "same" : "");
    a2hist_pede->DrawCal1(adcrange, checksame ? "same" : ""); 
    a2hist_pede->DrawADCs(checksame ? "same" : "");  
    a2hist_pede->DrawFlag(checksame ? "same" : "");
    if(!checksame){a2hist_pede->DrawTDC();}
    cout << " Blue:  Events with PEDE Flag" << endl;
    checksame = true;
  }

  // ++++++ Save Canvases +++++++++++++++++++++++
  char printname[256];
  if(savecanvas){
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
  
  // +++++ Save the pedestal in the pedefile +++++
  if(checkpede==true){
    cout << endl;
    cout << "Number of Arm1 pedestal event = " << na1pede << endl;
    cout << "Number of Arm2 pedestal event = " << na2pede << endl;
    
    if(na1pede==0 && na2pede==0){
      cout << "Error: Cannot create pedestal file" << endl;
    }
    else{
      //TFile* pfile = new TFile(pedefile,"RECREATE");
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
  
  // +++++ Write Histograms in the outfile +++++
  if(strcmp(outfile,"")!=0){
    TFile *ofile = new TFile(outfile,"RECREATE");
    a2hist_all->Write();
    a2hist_beam->Write();
    a2hist_pede->Write(); 
    cout << endl
	 << "Histograms were saved in \"" << outfile  << "\" : " 
	 << endl;
    ofile->ls();
    cout << endl;
    ofile->Close();
  }
  
  if(drawall || drawbeam || drawpede){
    app.Run();
  } 

  return 0;
  
}
