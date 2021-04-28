#ifndef __A1CAL1ACCUMHIST_CPP__
#define __A1CAL1ACCUMHIST_CPP__

#include "A1Cal1AccumHist.h"

//---------------------------------------------------------------------- 
//  
// Make histograms from A1Cal1 Data (Arm#1 Cal1).
//
// ++Easy sample code.
//   *con = new A1Cal1AccumHist("name","title");
//   con->SetHistNbin(210);  // Histogram paramaters should be set
//                           // before calling Initialize().
//   con->Initialize();
//   for(i=0;i<100;i++){
//     tree->GetEntry(i);
//     a1cal = (A1Cal1*) ev->Get("a1cal");
//     con->Fill(a1cal);
//   }
//   con->Draw();
// 
//
// List of Histograms ----------------------------------------
// 
// - TH1F *hist_cal[2][16][2]      [tower][layer][adc range] 
//     Histograms of each adc value of scintillator layer
//    
// - TH1F *hist_noise[8]           [channel]
//     Histograms of each channel of ADC3
//     Data are filled in only [0-3]  
//     
// - TH1F *hist_fc[2][4]           [Arm(arm1-0,arm2-1)][Channel]
//     Histograms of FC ADC values
// 
// - TH1F *hist_laser[2]           [left:0,right:1]
//     Histograms of ADC of Laser Monitor PMT
// 
// - TH1F *haccum_scifi[2][4][2]   [Tower][Layer][XY]
//     Accumulate values of each fiber 
// 
// - TH1F *hist_scifi[2][4][2]    [Tower][Layer][XY]
//     Histograms of ADC values of typical fiber (one per layer.)
//
// - TH1F *hist_flag[3]           [flags]
//     Accumulate of flags
//     [0] : GPIO-LHCFLOGIC DAQ FLAG 
//     [1] : GPIO-LHCFLOGIC Discriminator 
//     [2] : GPIO-LHCFCOUNTER DAQ FLAG
//
// - TH1F *hist_tdc[7]            
//     Histograms of TDC values.
//     The range of eahc histogram is optimized. 
//     [0] : A1Cal1::tdc0[2]  BPTX1 (-1100/-1000)
//     [1] : A1Cal1::tdc0[3]  BPTX2 (-1100/-1000)
//     [2] : A1Cal1::tdc0[4]  Shower Trigger (-250/-150)
//     [3] : A1Cal1::tdc0[6]  Arm1 FC (-300/-200)
//     [4] : A1Cal1::tdc0[7]  Arm2 FC (-250/-150)
//     [5] : A1Cal1::tdc0[8]  20mm Discriminator (-330/-230)
//     [6] : A1Cal1::tdc0[9]  40mm Discriminator (-330/-230)
//     () : range of the histogram 
//     
// - TH1F *hist_scl[3]
//     Acummulate of Scaler Value
//     [0] : A1Cal1::counter[23] Bunch position (0-3564)
//     [1] : A1Cal1::counter[24] Bunch Index of beam1 (0-160)
//     [2] : A1Cal1::counter[25] Bunch Index of beam2 (0-160)
//     () : range of the histogram 
//
//
// ++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 14 Jul. 08: First Editted by H.MENJO
// 25 Jul. 09: Added some functions to contorl the number of bin
//             for histograms by H.MENJO 
// 12 Jan. 10: Added the histograms of hist_tdc and hist_scl by H.MENJO
//             Version 1 -> 2
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1Cal1AccumHist);
#endif

#include <TLegend.h>
#include <TCollection.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
using namespace std;

int A1Cal1AccumHist::icall = 0;
const int A1Cal1AccumHist::DEFAULT_hist_nbin;
const int A1Cal1AccumHist::DEFAULT_hist_binmin;
const int A1Cal1AccumHist::DEFAULT_hist_binmax;
const int A1Cal1AccumHist::DEFAULT_hscifi_nbin;
const int A1Cal1AccumHist::DEFAULT_hscifi_binmin;
const int A1Cal1AccumHist::DEFAULT_hscifi_binmax;
const int A1Cal1AccumHist::DEFAULT_hscifi_channel;

A1Cal1AccumHist::A1Cal1AccumHist(){
  char name[256];
  char title[256];
  sprintf(name,"a1c1hist%d",icall);
  sprintf(title,"A1Cal1 Histograms %d",icall);
  this->SetName(name);
  this->SetTitle(title); 
  InitializeMembers();
  icall++;
}

A1Cal1AccumHist::A1Cal1AccumHist(char* name, char *title) :
  TNamed(name,title) 
{
  InitializeMembers();
}

A1Cal1AccumHist::~A1Cal1AccumHist(){
  //DeleteHists();
  //DeleteCanvases();
}

int A1Cal1AccumHist::InitializeMembers(){
  // Fill NULL to the all histograms pointers
  
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	hist_cal[it][il][ir] = NULL;
      }
    }
  }
  for(int ie=0;ie<8;ie++){
    hist_noise[ie] = NULL;
  }
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw] = NULL;
    }
  }
  for(int it=0;it<2;it++){
    hist_laser[it] = NULL;
  }

  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy] = NULL;
      }
    }
  }  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	hist_scifi[it][il][ixy] = NULL;
      }
    }
  }  
  for(int i=0;i<3;i++){
    hist_flag[i] = NULL;
  }

  for(int i=0;i<7;i++){
    hist_tdc[i] = NULL;
  }

  for(int i=0;i<3;i++){
    hist_scl[i] = NULL;
  }

  c_cal0 = NULL;
  c_cal1 = NULL;
  c_adcs = NULL;
  c_flag = NULL;
  c_tdc  = NULL; 
  c_scifi= NULL;

  hist_nbin = DEFAULT_hist_nbin;
  hist_binmin = DEFAULT_hist_binmin;
  hist_binmax = DEFAULT_hist_binmax;
  hscifi_nbin = DEFAULT_hscifi_nbin;
  hscifi_binmin = DEFAULT_hscifi_binmin;
  hscifi_binmax = DEFAULT_hscifi_binmax;
  hscifi_channel = DEFAULT_hscifi_channel;
  
  f_DataVersion = VERSION_PP2015; // Default
  return OK;
}

int  A1Cal1AccumHist::InitializeHists(){
  // Initialize all histograms.
  // All parameters of nbin, minbin, maxbin should be set before this function is called.
  
  char name[256];
  char title[256];
  
  // for calorimter 
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	sprintf(name,"%s_hcal_%d_%02d_%d",
		this->GetName(),it,il,ir);
	sprintf(title,"%s_Tower:%d_Layer:%02d_Range:%d",
		this->GetTitle(),it,il,ir);
	hist_cal[it][il][ir] = new TH1F(name,title,
					hist_nbin,
					hist_binmin,
					hist_binmax);
	hist_cal[it][il][ir] ->SetXTitle("ADC Counts");	
	hist_cal[it][il][ir] ->SetYTitle("#DeltaN");
      }
    }
  }

  //for noise reduction
  for(int ie=0;ie<8;ie++){
    sprintf(name,"%s_noise_%d",
	    this->GetName(),ie);
    hist_noise[ie] = new TH1F(name,name,
				  hist_nbin,
				  hist_binmin,
				  hist_binmax);
    hist_noise[ie]->SetXTitle("ADC Counts");
    hist_noise[ie]->SetYTitle("#DeltaN");
  }

  //for frontcounter
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      sprintf(name,"%s_fc_%d_%d",
	    this->GetName(),it,iw);
      hist_fc[it][iw] = new TH1F(name,name,
				 hist_nbin,
				 hist_binmin,
				 hist_binmax);
      hist_fc[it][iw]->SetXTitle("ADC Counts");
      hist_fc[it][iw]->SetYTitle("#DeltaN");
    }
  }

  //for laser
  for(int it=0;it<2;it++){
    sprintf(name,"%s_laser_%d",
	    this->GetName(),it);
    hist_laser[it] = new TH1F(name,name,
				  hist_nbin,
				  hist_binmin,
				  hist_binmax);
    hist_laser[it]->SetXTitle("ADC Counts");
    hist_laser[it]->SetYTitle("#DeltaN");
  }
  
  // for scifi accumulation
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	sprintf(name,"%s_hacumscifi_%d_%d_%d",
		this->GetName(),it,il,ixy);
	sprintf(title,"%s Tower:%d Layer:%d XY:%d",
		this->GetTitle(),it,il,ixy);
	if(it==0){
	  haccum_scifi[it][il][ixy] = new TH1F(name,title,
					       20,0,20);
	  haccum_scifi[it][il][ixy]->SetXTitle("Fiber");
	  haccum_scifi[it][il][ixy]->SetYTitle("Sum of ADC counts");
	}
	if(it==1){
	  haccum_scifi[it][il][ixy] = new TH1F(name,title,
					       40,0,40);
	  haccum_scifi[it][il][ixy]->SetXTitle("Fiber");
	  haccum_scifi[it][il][ixy]->SetYTitle("Sum of ADC counts");
	}
      }
    }
  }

  // for scifi histograms
  int sch=0;
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	sch = hscifi_channel;
	if(it==1 || sch>=20){ sch-=20; }
	sprintf(name,"%s_hscifi_%d_%d_%d_%02d",
		this->GetName(),it,il,ixy,sch);
	sprintf(title,"%s Tower:%d Layer:%d XY:%d Ch:%d",
		this->GetTitle(),it,il,ixy,sch);
	hist_scifi[it][il][ixy] = new TH1F(name,title,
					   hscifi_nbin,
					   hscifi_binmax,
					   hscifi_binmax);
	hist_scifi[it][il][ixy]->SetXTitle("ADC counts");
	hist_scifi[it][il][ixy]->SetYTitle("#DeltaN");
      }
    }
  }
  
  // for flag 
  sprintf(name,"%s_flag_0",this->GetName());
  sprintf(title,"Flag [0]");
  hist_flag[0] = new TH1F(name,title,32,0,32);

  sprintf(name,"%s_flag_1",this->GetName());
  sprintf(title,"Flag [1]");
  hist_flag[1] = new TH1F(name,title,32,0,32); 
  
  sprintf(name,"%s_flag_2",this->GetName());
  sprintf(title,"Flag [2]");
  hist_flag[2] = new TH1F(name,title,32,0,32);  

  for(int i=0;i<3;i++){
    hist_flag[i]->SetXTitle("Bit");
    hist_flag[i]->SetYTitle("#DeltaN");
  }

  // for TDC 
  switch (f_DataVersion){
  case VERSION_PP2010:
    // BPTX1 (1044)
    sprintf(name,"%s_tdc_0",this->GetName());
    sprintf(title,"TDC BPTX1");
    hist_tdc[0] = new TH1F(name,title,100,-1100,-1000); // for Op2010
    // BPTX2 (1044)
    sprintf(name,"%s_tdc_1",this->GetName());
    sprintf(title,"TDC BPTX2");
    hist_tdc[1] = new TH1F(name,title,100,-1100,-1000); // for Op2010
    // Shower Trigger (190)
    sprintf(name,"%s_tdc_2",this->GetName());
    sprintf(title,"TDC Shower Trigger");
    hist_tdc[2] = new TH1F(name,title,100,-250,-150); // for Op2010
    // Arm1 FC (250)
    sprintf(name,"%s_tdc_3",this->GetName());
    sprintf(title,"TDC Arm1 FC");
    hist_tdc[3] = new TH1F(name,title,100,-300,-200); // for Op2010
    // Arm2 FC (200)
    sprintf(name,"%s_tdc_4",this->GetName());
    sprintf(title,"TDC Arm2 FC");
    hist_tdc[4] = new TH1F(name,title,100,-250,-150); // for Op2010
    // 20mm Discriminator OR (270)
    sprintf(name,"%s_tdc_5",this->GetName());
    sprintf(title,"TDC 20mm OR");
    hist_tdc[5] = new TH1F(name,title,100,-330,-230); // for Op2010
    // 40mm Discriminator OR (270)
    sprintf(name,"%s_tdc_6",this->GetName());
    sprintf(title,"TDC 40mm OR");
    hist_tdc[6] = new TH1F(name,title,100,-330,-230); // for Op200
    break;
  case VERSION_PP2015:
    // BPTX1 (1044)
    sprintf(name,"%s_tdc_0",this->GetName());
    sprintf(title,"TDC BPTX1");
    hist_tdc[0] = new TH1F(name,title,100,-930,-830); // for Op2015 
    // BPTX2 (1044)
    sprintf(name,"%s_tdc_1",this->GetName());
    sprintf(title,"TDC BPTX2");
    hist_tdc[1] = new TH1F(name,title,100,-930,-830); // for Op2015
    // Shower Trigger (190)
    sprintf(name,"%s_tdc_2",this->GetName());
    sprintf(title,"TDC Shower Trigger");
    hist_tdc[2] = new TH1F(name,title,100,-200,0); // for Op2015
    // Arm1 FC (250)
    sprintf(name,"%s_tdc_3",this->GetName());
    sprintf(title,"TDC Arm1 FC");
    hist_tdc[3] = new TH1F(name,title,100,-250,-50); // for Op2015
    // Arm2 FC (200)
    sprintf(name,"%s_tdc_4",this->GetName());
    sprintf(title,"TDC Arm2 FC");
    hist_tdc[4] = new TH1F(name,title,100,-250,-50); // for Op2015
    // 20mm Discriminator OR (270)
    sprintf(name,"%s_tdc_5",this->GetName());
    sprintf(title,"TDC 20mm OR");
    hist_tdc[5] = new TH1F(name,title,100,-250,-50); // for Op2015
    // 40mm Discriminator OR (270)
    sprintf(name,"%s_tdc_6",this->GetName());
    sprintf(title,"TDC 40mm OR");
    hist_tdc[6] = new TH1F(name,title,100,-250,-50); // for Op2015
    break;
  case VERSION_RHICF_OP2017:
     // BC
    sprintf(name,"%s_tdc_0",this->GetName());
    sprintf(title,"TDC BC");
    hist_tdc[0] = new TH1F(name,title,100,650,700); 
    // 
    sprintf(name,"%s_tdc_1",this->GetName());
    sprintf(title,"TDC Shower Trigger");
    hist_tdc[1] = new TH1F(name,title,1500,-2000,1000);
    // Shower Trigger 
    sprintf(name,"%s_tdc_2",this->GetName());
    sprintf(title,"TDC Shower Trigger");
    hist_tdc[2] = new TH1F(name,title,1500,-2000,1000); 
    // SLogic
    sprintf(name,"%s_tdc_3",this->GetName());
    sprintf(title,"TDC TS logic");
    hist_tdc[3] = new TH1F(name,title,1500,-2000,1000); 
    // LLogic
    sprintf(name,"%s_tdc_4",this->GetName());
    sprintf(title,"TDC TL logic");
    hist_tdc[4] = new TH1F(name,title,1500,-2000,1000);
    // 20mm Discriminator OR (270)
    sprintf(name,"%s_tdc_5",this->GetName());
    sprintf(title,"TDC 20mm OR");
    hist_tdc[5] = new TH1F(name,title,1500,-2000,1000); 
    // 40mm Discriminator OR (270)
    sprintf(name,"%s_tdc_6",this->GetName());
    sprintf(title,"TDC 40mm OR");
    hist_tdc[6] = new TH1F(name,title,1500,-2000,1000); 
    break;
  default:
    // BPTX1 (1044)
    sprintf(name,"%s_tdc_0",this->GetName());
    sprintf(title,"TDC BPTX1");
    hist_tdc[0] = new TH1F(name,title,100,-1100,-1000); // for Op2010
    // BPTX2 (1044)
    sprintf(name,"%s_tdc_1",this->GetName());
    sprintf(title,"TDC BPTX2");
    hist_tdc[1] = new TH1F(name,title,100,-1100,-1000); // for Op2010
    // Shower Trigger (190)
    sprintf(name,"%s_tdc_2",this->GetName());
    sprintf(title,"TDC Shower Trigger");
    hist_tdc[2] = new TH1F(name,title,100,-250,-150); // for Op2010
    // Arm1 FC (250)
    sprintf(name,"%s_tdc_3",this->GetName());
    sprintf(title,"TDC Arm1 FC");
    hist_tdc[3] = new TH1F(name,title,100,-300,-200); // for Op2010
    // Arm2 FC (200)
    sprintf(name,"%s_tdc_4",this->GetName());
    sprintf(title,"TDC Arm2 FC");
    hist_tdc[4] = new TH1F(name,title,100,-250,-150); // for Op2010
    // 20mm Discriminator OR (270)
    sprintf(name,"%s_tdc_5",this->GetName());
    sprintf(title,"TDC 20mm OR");
    hist_tdc[5] = new TH1F(name,title,100,-330,-230); // for Op2010
    // 40mm Discriminator OR (270)
    sprintf(name,"%s_tdc_6",this->GetName());
    sprintf(title,"TDC 40mm OR");
    hist_tdc[6] = new TH1F(name,title,100,-330,-230); // for Op200
    break;
  }
  
  // for Scaler value
  sprintf(name,"%s_scl_0",this->GetName());
  sprintf(title,"SCL CLK");
  hist_scl[0] = new TH1F(name,title,3564,0,3564); 
  sprintf(name,"%s_scl_1",this->GetName());
  sprintf(title,"SCL BPTX1");
  hist_scl[1] = new TH1F(name,title,160,0,160);
  sprintf(name,"%s_scl_2",this->GetName());
  sprintf(title,"SCL BPTX2");
  hist_scl[2] = new TH1F(name,title,160,0,160);

  return OK;
}

int  A1Cal1AccumHist::InitializeCanvases(){
  // Initialize all canvases for Cal0, Cal1, ADCs and Flag.
  InitializeCanvasCal0();
  InitializeCanvasCal1();
  InitializeCanvasADCs();
  InitializeCanvasFlag(); 
  InitializeCanvasTDC();
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasCal0(){
  if(c_cal0!=NULL){ 
    delete c_cal0;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_cal0",this->GetName());
    c_cal0 = new TCanvas(name,"Arm1 20mm Calorimeters",
			 50,0,1000,800); 
    c_cal0->Divide(4,4,0.001,0.001);
  }
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasCal1(){
  if(c_cal1!=NULL){
    delete c_cal1;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_cal1",this->GetName());
    c_cal1 = new TCanvas(name,"Arm1 40mm Calorimeters",
			 100,50,1000,800);
    c_cal1->Divide(4,4,0.001,0.001);
  }
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasADCs(){
  if(c_adcs!=NULL){
    delete c_adcs;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_adcs",this->GetName());
    c_adcs = new TCanvas(name,"Arm1 the other ADCs",
			 150,50,1000,800);
    c_adcs->Divide(4,4,0.001,0.001);
  }  
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasFlag(){
  if(c_flag!=NULL){
    delete c_flag;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_flag",this->GetName());
    c_flag = new TCanvas(name,"Arm1 Flags",
			 200,100,400,600);
    c_flag->Divide(1,3,0.001,0.001);
  }
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasTDC(){
  if(c_tdc!=NULL){
    delete c_tdc;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_tdc",this->GetName());
    c_tdc = new TCanvas(name,"Arm1 TDC",
			200,100,500,600);
    c_tdc->Divide(1,3,0.001,0.001);
  }
  return OK;
}

int  A1Cal1AccumHist::InitializeCanvasSciFi(){
  if(c_scifi!=NULL){
    delete c_scifi;
  }
  else{
    char name[256];
    sprintf(name,"%s_c_scifi",this->GetName());
    c_scifi = new TCanvas(name,"Arm1 SciFi",
			100,150,700,800);
    c_scifi->Divide(2,4,0.001,0.001);
  }
  return OK;
}

int  A1Cal1AccumHist::DeleteHists(){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	if(hist_cal[it][il][ir]!=NULL){
	  delete hist_cal[it][il][ir];
	  hist_cal[it][il][ir] = NULL;
	}
      }
    }
  }
  for(int ie=0;ie<8;ie++){
    if(hist_noise[ie]!=NULL){
      delete hist_noise[ie];
      hist_noise[ie] = NULL;
    }
  }
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      if(hist_fc[it][iw]!=NULL){
	delete hist_fc[it][iw];
	hist_fc[it][iw] = NULL;
      }
    }
  }
  for(int it=0;it<2;it++){
    if(hist_laser[it]!=NULL){
      delete hist_laser[it];
      hist_laser[it] = NULL;
    }
  }
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	if(haccum_scifi[it][il][ixy]!=NULL){
	  delete haccum_scifi[it][il][ixy];
	  haccum_scifi[it][il][ixy] = NULL;
	}
      }
    }
  }  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	if(hist_scifi[it][il][ixy]!=NULL){
	  delete hist_scifi[it][il][ixy];
	  hist_scifi[it][il][ixy] = NULL;
	}
      }
    }
  }  
  for(int i=0;i<3;i++){
    if(hist_flag[i]!=NULL){
      delete hist_flag[i];
      hist_flag[i] = NULL;
    }
  }
  for(int i=0;i<7;i++){
    if(hist_tdc[i]!=NULL){
      delete hist_tdc[i];
      hist_flag[i] = NULL;
    }
  }
  for(int i=0;i<3;i++){
    if(hist_scl[i]!=NULL){
      delete hist_scl[i];
      hist_scl[i] = NULL;
    }
  }
  return OK;
}

int  A1Cal1AccumHist::DeleteCanvases(){
  if(c_cal0!=NULL){ 
    delete c_cal0;
    c_cal0 = NULL;
  }
  if(c_cal1!=NULL){
    delete c_cal1;
    c_cal1 = NULL;
  }
  if(c_adcs!=NULL){
    delete c_adcs;
    c_adcs = NULL;
  }
  if(c_flag!=NULL){
    delete c_flag;
    c_flag = NULL;
  } 
  if(c_tdc!=NULL){
    delete c_tdc;
    c_tdc = NULL;
  } 
  if(c_scifi!=NULL){
    delete c_scifi;
    c_scifi = NULL;
  } 
  return OK;
}

int  A1Cal1AccumHist::Fill(A1Cal1 *d,
			   bool beam, 
			   bool pede,
			   bool laser){
  // Fill data with the A1Cal1 format to histograms if the flag of the data 
  // selected by the arguments (beam:pede:laser) is true.  
  // default 
  //   beam  = true; pede  = true; laser = true;
  // If the event filled to histogram, return 1. If not, return 0.
  
  if( (d->flag_beam==true && beam==true) ||
      (d->flag_pede==true && pede==true) ||
      (d->flag_laser==true && laser==true) ){
    
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  hist_cal[it][il][ir]->Fill(d->cal[it][il][ir]);
	}
      }
    }
    
    for(int ie=0;ie<4;ie++){
      hist_noise[ie]->Fill(d->emptyadc[ie]);
    }
    
    for(int it=0;it<2;it++){
      for(int iw=0;iw<4;iw++){
	hist_fc[it][iw]->Fill(d->fc[it][iw]);
      }
    }
    
    for(int it=0;it<2;it++){
      hist_laser[it]->Fill(d->laser[it]);
    }
    
    int nbin;
    int sch;
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	// accum
	nbin = haccum_scifi[0][il][ixy]->GetNbinsX();
	for(int ibin=0;ibin<nbin;ibin++){
	  haccum_scifi[0][il][ixy]->Fill(ibin+0.5,
					 d->scifi0[il][ixy][ibin]);
	}
	nbin = haccum_scifi[1][il][ixy]->GetNbinsX();
	for(int ibin=0;ibin<nbin;ibin++){
	  haccum_scifi[1][il][ixy]->Fill(ibin+0.5,
					 d->scifi1[il][ixy][ibin]);
	}
	
	// hist
	sch = hscifi_channel;
	if(hscifi_channel>=20) sch -= 20;
	hist_scifi[0][il][ixy]->Fill(d->scifi0[il][ixy][sch]);
	hist_scifi[1][il][ixy]->Fill(d->scifi1[il][ixy][hscifi_channel]);	
      }
    }

    // flag
    unsigned int mask=0xFFFFFFFF;
    for(int i=0;i<3;i++){
      for(int ib=0;ib<hist_flag[i]->GetNbinsX();ib++){
	mask = ( 0x1 << ib);
	if(d->flag[i] & mask){
	  hist_flag[i]->Fill(ib+0.5);
	}
      }
    }

    // TDC
    int ich=0;
    for(int i=0;i<7;i++){
      if     (i==0) ich = 2; // BPTX1
      else if(i==1) ich = 3; // BPTX2
      else if(i==2) ich = 4; // Shower Trigger
      else if(i==3) ich = 6; // Arm1 FC
      else if(i==4) ich = 7; // Arm2 FC
      else if(i==5) ich = 8; // 20mm Discriminator
      else if(i==6) ich = 9; // 40mm Discriminator

      
      // For RHICf
      if(f_DataVersion==VERSION_RHICF_OP2017){
		  if(i==0) ich = 0;
		  if(i==1) ich = 5;	
		  if(i==3) ich = 6;
		  if(i==4) ich = 7;
      }
      
      for(int ihit=0;ihit<16;ihit++){
	if(d->tdc0flag[ich][ihit]<0){break;}
	// hist_tdc[i]->Fill(-1.*d->tdc0[ich][ihit]);
	hist_tdc[i]->Fill(d->tdc0[ich][ihit]);
      }
    }
    
    // Scaler 
    hist_scl[0]->Fill(d->counter[23]); // 40MHz Clock
    hist_scl[1]->Fill(d->counter[24]); // BPTX1
    hist_scl[2]->Fill(d->counter[25]); // BPTX2    
    
    return 1;
  }

  return 0;
}

int  A1Cal1AccumHist::Reset(){
  // Clear values of the all histograms.
  
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	hist_cal[it][il][ir]->Reset();
      }
    }
  }  
  
  for(int ie=0;ie<8;ie++){
    hist_noise[ie]->Reset();
  }
  
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw]->Reset();
    }
  }
  
  for(int it=0;it<2;it++){
    hist_laser[it]->Reset();
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->Reset();
	hist_scifi[it][il][ixy]->Reset();
      }
    }
  }  

  for(int i=0;i<3;i++){
    hist_flag[i]->Reset();
  }

  for(int i=0;i<7;i++){
    hist_tdc[i]->Reset();
  }

  for(int i=0;i<3;i++){
    hist_scl[i]->Reset();
  }

  return OK;
}

int  A1Cal1AccumHist::CopyData(A1Cal1AccumHist* d){
  // Copy histograms stored in the given pointer to this.
  
  int nbin;
  double nentry;
  double tmp;

  // Calorimeter
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	// Copy the values
	for(int ibin=1;ibin<=hist_nbin;ibin++){
	  tmp = d->hist_cal[it][il][ir]->GetBinContent(ibin);
	  hist_cal[it][il][ir]->SetBinContent(ibin,tmp);
	}
	// Copy entries
	tmp = d->hist_cal[it][il][ir]->GetEntries();
	hist_cal[it][il][ir]->SetEntries(tmp);
      }
    }
  } 
  
  // Noise
  for(int ie=0;ie<4;ie++){
    for(int ibin=1;ibin<=hist_noise[ie]->GetNbinsX();ibin++){
      tmp = d->hist_noise[ie]->GetBinContent(ibin);
      hist_noise[ie]->SetBinContent(ibin,tmp);
    }
    tmp = d->hist_noise[ie]->GetEntries();
    hist_noise[ie]->SetEntries(tmp);
  }

  // FC
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      for(int ibin=1;ibin<=hist_fc[it][iw]->GetNbinsX();ibin++){
	tmp = d->hist_fc[it][iw]->GetBinContent(ibin);
	hist_fc[it][iw]->SetBinContent(ibin,tmp);
      }
      tmp = d->hist_fc[it][iw]->GetEntries();
      hist_fc[it][iw]->SetEntries(tmp);
    }
  }
  
  // Laser
  for(int ie=0;ie<2;ie++){
    for(int ibin=1;ibin<=hist_laser[ie]->GetNbinsX();ibin++){
      tmp = d->hist_laser[ie]->GetBinContent(ibin);
      hist_laser[ie]->SetBinContent(ibin,tmp);
    }
    tmp = d->hist_laser[ie]->GetEntries();
    hist_laser[ie]->SetEntries(tmp);
  }
  

  // Scifi 
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	// accum
	nbin = d->haccum_scifi[it][il][ixy]->GetNbinsX();
	nentry = d->haccum_scifi[it][il][ixy]->GetEntries();
	for(int ibin=1;ibin<=nbin;ibin++){
	  tmp = d->haccum_scifi[it][il][ixy]->GetBinContent(ibin);
	  this->haccum_scifi[it][il][ixy]->SetBinContent(ibin,tmp);
	}
	this->haccum_scifi[it][il][ixy]->SetEntries(nentry);

	// hist
	nbin = d->hist_scifi[it][il][ixy]->GetNbinsX();
	for(int ibin=1;ibin<=nbin;ibin++){
	  tmp = d->hist_scifi[it][il][ixy]->GetBinContent(ibin);
	  this->hist_scifi[it][il][ixy]->SetBinContent(ibin,tmp);
	}
	this->hist_scifi[it][il][ixy]->SetEntries(nentry);
      }
    }
  }
  
  // Flag
  for(int i=0;i<3;i++){
    for(int ibin=1;ibin<=d->hist_flag[i]->GetNbinsX();ibin++){
      tmp = d->hist_flag[i]->GetBinContent(ibin);
      this->hist_flag[i]->SetBinContent(ibin,tmp);
    }
  }
  
  // TDC
  for(int i=0;i<7;i++){
    for(int ibin=1;ibin<=d->hist_tdc[i]->GetNbinsX();ibin++){
      tmp = d->hist_tdc[i]->GetBinContent(ibin);
      this->hist_tdc[i]->SetBinContent(ibin,tmp);
    }
  }
  
  // Scaler
  for(int i=0;i<3;i++){
    for(int ibin=1;ibin<=d->hist_scl[i]->GetNbinsX();ibin++){
      tmp = d->hist_scl[i]->GetBinContent(ibin);
      this->hist_scl[i]->SetBinContent(ibin,tmp);
    }
  }
  
  return OK;
}

int  A1Cal1AccumHist::SetHistNbin(int nbin){
  hist_nbin = nbin;
  return OK;
}

int  A1Cal1AccumHist::SetHistBinMinimum(int binmin){
  hist_binmin = binmin;
  return OK;
}

int  A1Cal1AccumHist::SetHistBinMaximum(int binmax){
  hist_binmax = binmax;
  return OK;
}

int  A1Cal1AccumHist::SetHSciFiNbin(int nbin){
  hscifi_nbin = nbin;
  return OK;
}

int  A1Cal1AccumHist::SetHSciFiBinMinimum(int binmin){
  hscifi_binmin = binmin;
  return OK;
}

int  A1Cal1AccumHist::SetHSciFiBinMaximum(int binmax){
  hscifi_binmax = binmax;
  return OK;
} 

int  A1Cal1AccumHist::SetHSciFiChannel(int ch){
  if(ch<0 || ch>=40){
    cerr << "[A1Cal1AccumHist::SetHSciFiChannel]" 
	 << "invalid channel: " << ch << endl;
    return ERROR;
  }
  hscifi_channel = ch;
  return OK;
}

int A1Cal1AccumHist::SetTDCHistogram(int ich,int nbin,double binmin,double binmax){
  string name = "", title = "";
  ostringstream sout;
  if(ich>=7) {return ERROR;}
  if(hist_tdc[ich]){
    name  = hist_tdc[ich]->GetName();
    title = hist_tdc[ich]->GetTitle();
    delete hist_tdc[ich];
  }
  else{
    sout << this->GetName() << "_tdc_" << ich << endl;
    name = sout.str();
    if(ich==0){ title = "TDC BPTX1"; }
    if(ich==1){ title = "TDC BPTX2"; }
    if(ich==2){ title = "TDC Shower Trigger"; }
    if(ich==3){ title = "TDC Arm1 FC"; } 
    if(ich==4){ title = "TDC Arm2 FC"; }
    if(ich==5){ title = "TDC 20mm OR"; }
    if(ich==6){ title = "TDC 40mm OR"; }
  }
  hist_tdc[ich] = new TH1F(name.c_str(),title.c_str(),nbin,binmin,binmax);
  return OK;
}

int A1Cal1AccumHist::SetTDCHistogram(int ich,TH1F* h){
  if(hist_tdc[ich]){
    delete hist_tdc[ich];
  }
  hist_tdc[ich] = h;
  return OK;
}

void A1Cal1AccumHist::SetLineColor(Color_t c){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
		  hist_cal[it][il][ir]->SetLineColor(c);
      }
    }
  }  
  
  for(int ie=0;ie<8;ie++){
    hist_noise[ie]->SetLineColor(c);
  }
  
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw]->SetLineColor(c);
    }
  }
  
  for(int it=0;it<2;it++){
    hist_laser[it]->SetLineColor(c);
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->SetLineColor(c);
	hist_scifi[it][il][ixy]->SetLineColor(c);
      }
    }
  }  

  for(int i=0;i<3;i++){
    hist_flag[i]->SetLineColor(c);
  }
  
  for(int i=0;i<7;i++){
    hist_tdc[i]->SetLineColor(c);
  }

  for(int i=0;i<3;i++){
    hist_scl[i]->SetLineColor(c);
  }

}

void A1Cal1AccumHist::SetFillColor(Color_t c){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	hist_cal[it][il][ir]->SetFillColor(c);
      }
    }
  }  
  
  for(int ie=0;ie<8;ie++){
    hist_noise[ie]->SetFillColor(c);
  }
  
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw]->SetFillColor(c);
    }
  }
  
  for(int it=0;it<2;it++){
    hist_laser[it]->SetFillColor(c);
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->SetFillColor(c);
	hist_scifi[it][il][ixy]->SetFillColor(c);
      }
    }
  }  

  for(int i=0;i<3;i++){
    hist_flag[i]->SetFillColor(c);
  }

  
   for(int i=0;i<7;i++){
    hist_tdc[i]->SetFillColor(c);
  }

  for(int i=0;i<3;i++){
    hist_scl[i]->SetFillColor(c);
  }   
}

void A1Cal1AccumHist::SetFillStyle(int c){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	hist_cal[it][il][ir]->SetFillStyle(c);
      }
    }
  }  
  
  for(int ie=0;ie<8;ie++){
    hist_noise[ie]->SetFillStyle(c);
  }
  
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw]->SetFillStyle(c);
    }
  }
  
  for(int it=0;it<2;it++){
    hist_laser[it]->SetFillStyle(c);
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->SetFillStyle(c);
	hist_scifi[it][il][ixy]->SetFillStyle(c);
      }
    }
  }  

  for(int i=0;i<3;i++){
    hist_flag[i]->SetFillStyle(c);
  }
  
  for(int i=0;i<7;i++){
    hist_tdc[i]->SetFillStyle(c);
  }

  for(int i=0;i<3;i++){
    hist_scl[i]->SetFillStyle(c);
  }  

}

void A1Cal1AccumHist::Scale(double s){
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	hist_cal[it][il][ir]->Scale(s);
      }
    }
  }  
  
  for(int ie=0;ie<8;ie++){
    hist_noise[ie]->Scale(s);
  }
  
  for(int it=0;it<2;it++){
    for(int iw=0;iw<4;iw++){
      hist_fc[it][iw]->Scale(s);
    }
  }
  
  for(int it=0;it<2;it++){
    hist_laser[it]->Scale(s);
  }
  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	haccum_scifi[it][il][ixy]->Scale(s);
	hist_scifi[it][il][ixy]->Scale(s);
      }
    }
  }  

  for(int i=0;i<3;i++){
    hist_flag[i]->Scale(s);
  }

  for(int i=0;i<7;i++){
    hist_tdc[i]->Scale(s);
  }

  for(int i=0;i<3;i++){
    hist_scl[i]->Scale(s);
  }  

}

int  A1Cal1AccumHist::Draw(int adcrange, const char* option){
  // Draw all histograms for Cal0, Cal1, ADCs and Flag.
  // If the canvas for each histogram have not been cleated (pointer have NULL),
  // canvases are cleated.

  DrawCal0(adcrange,option);
  DrawCal1(adcrange,option);
  DrawADCs(option);
  DrawFlag(option);
  DrawTDC(option);
  return OK;
}

int  A1Cal1AccumHist::DrawCal0(int adcrange, const char* option){
  if(c_cal0==NULL){ 
    InitializeCanvasCal0();
  }
  
  if(adcrange!=0 && adcrange!=1){return ERROR;}

  for(int i=0;i<16;i++){
    c_cal0->cd(i+1);
    hist_cal[0][i][adcrange]->Draw(option);
  }
  c_cal0->Update();
  return OK;
}

int  A1Cal1AccumHist::DrawCal1(int adcrange, const char* option){
  if(c_cal1==NULL){
    InitializeCanvasCal1();
  }
  
  if(adcrange!=0 && adcrange!=1){return ERROR;}
 
  for(int i=0;i<16;i++){
    c_cal1->cd(i+1);
    hist_cal[1][i][adcrange]->Draw(option);
  } 
  c_cal1->Update(); 
  return OK;
}

int  A1Cal1AccumHist::DrawADCs(const char* option){
  if(c_adcs==NULL){
    InitializeCanvasADCs();
  } 
 
  for(int i=0;i<4;i++){
    c_adcs->cd(i+1);
    hist_noise[i]->Draw(option);
  }
  
  for(int iarm=0;iarm<2;iarm++){
    for(int ich=0;ich<4;ich++){
      c_adcs->cd(iarm*4+ich+1+4);
      hist_fc[iarm][ich]->Draw(option);
    }
  }

  for(int i=0;i<2;i++){
    c_adcs->cd(i+1+12);
    hist_laser[i]->Draw(option);
  } 
  
  c_adcs->Update(); 
  return OK;
}

int  A1Cal1AccumHist::DrawFlag(const char* option){
  if(c_flag==NULL){
    InitializeCanvasFlag();
  } 
  
  for(int i=0;i<3;i++){
    c_flag->cd(i+1);  
    hist_flag[i]->SetFillStyle(3004);
    hist_flag[i]->Draw(option);
  } 
  
  return OK;
}

int  A1Cal1AccumHist::DrawTDC(const char* option){
  if(c_tdc==NULL){
    InitializeCanvasTDC();
  } 

  if(strstr(option,"log")){
    c_tdc->cd(1);
    gPad->SetLogy();
    c_tdc->cd(2);
    gPad->SetLogy(); 
    c_tdc->cd(3);
    gPad->SetLogy();
  }
  
  TLegend *legend;
  c_tdc->cd(1);
  hist_tdc[0]->SetLineColor(kBlue);
  hist_tdc[0]->Draw(option);
  hist_tdc[1]->SetLineColor(kRed);
  hist_tdc[1]->Draw("same");
  legend = new TLegend(0.75,0.8,0.99,1.0);
  legend->SetFillColor(kWhite);
  legend->AddEntry(hist_tdc[0],"","l");
  legend->AddEntry(hist_tdc[1],"","l");  
  legend->Draw();
  OptimizeYRange((TPad*)gPad);

  c_tdc->cd(2);
  hist_tdc[2]->SetLineColor(1);
  hist_tdc[2]->Draw(option);
  hist_tdc[5]->SetLineColor(kRed);
  hist_tdc[5]->Draw("same");
  hist_tdc[6]->SetLineColor(kBlue);
  hist_tdc[6]->Draw("same"); 
  legend = new TLegend(0.75,0.8,0.99,1.0); 
  legend->SetFillColor(kWhite);
  legend->AddEntry(hist_tdc[2],"","l");
  legend->AddEntry(hist_tdc[5],"","l");
  legend->AddEntry(hist_tdc[6],"","l");
  legend->Draw();
  OptimizeYRange((TPad*)gPad);
  
  c_tdc->cd(3);  

  if(f_DataVersion==VERSION_RHICF_OP2017){
	 hist_tdc[2]->SetLineColor(1);
	 hist_tdc[2]->Draw(option);
	 hist_tdc[5]->SetLineColor(kRed);
	 hist_tdc[5]->SetFillStyle(0);
	 hist_tdc[5]->Draw("same");
	 hist_tdc[6]->SetLineColor(kBlue);
	 hist_tdc[6]->SetFillStyle(0);
	 hist_tdc[6]->Draw("same"); 
	 hist_tdc[3]->SetLineColor(kMagenta);
	 hist_tdc[3]->SetFillStyle(0);
	 hist_tdc[3]->Draw("same");
	 hist_tdc[4]->SetLineColor(kCyan+2);
	 hist_tdc[4]->SetFillStyle(0);
	 hist_tdc[4]->Draw("same"); 
	 legend = new TLegend(0.75,0.6,0.99,1.0); 
	 legend->SetFillColor(kWhite);
	 legend->AddEntry(hist_tdc[2],"","l");
	 legend->AddEntry(hist_tdc[5],"","l");
	 legend->AddEntry(hist_tdc[6],"","l");
	 legend->AddEntry(hist_tdc[3],"","l");
	 legend->AddEntry(hist_tdc[4],"","l");
	 legend->Draw();
  }
  else{
	 hist_tdc[1]->SetLineColor(1);
	 hist_tdc[1]->Draw(option);
	 hist_tdc[3]->SetLineColor(kRed);
	 hist_tdc[3]->Draw("same");
	 hist_tdc[4]->SetLineColor(kBlue);
	 hist_tdc[4]->Draw("same");
	 legend = new TLegend(0.75,0.8,0.99,1.0); 
	 legend->SetFillColor(kWhite);
	 legend->AddEntry(hist_tdc[1],"","l");
	 legend->AddEntry(hist_tdc[3],"","l");
	 legend->AddEntry(hist_tdc[4],"","l");
	 legend->Draw();
  }

  OptimizeYRange((TPad*)gPad);
 
  c_tdc->Update();
  
  return OK;
}

int  A1Cal1AccumHist::DrawSciFi(const char* option){
  if(c_scifi==NULL){
    InitializeCanvasSciFi();
  } 
  TLegend *legend;  
  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      c_scifi->cd(il*2+it+1);   
      haccum_scifi[it][il][0]->SetFillStyle(0);
      haccum_scifi[it][il][0]->SetLineColor(kBlue); 
      haccum_scifi[it][il][0]->SetLineStyle(1);
      haccum_scifi[it][il][0]->Draw("");
      haccum_scifi[it][il][1]->SetFillStyle(0);
      haccum_scifi[it][il][1]->SetLineColor(kRed); 
      haccum_scifi[it][il][1]->SetLineStyle(1);
      haccum_scifi[it][il][1]->Draw("same");
      OptimizeYRange((TPad*)gPad);
      gPad->Update(); 
      
      legend = new TLegend(0.85,0.8,0.99,1.0);
      legend->SetFillColor(kWhite);
      legend->AddEntry(haccum_scifi[it][il][0],"X","l");
      legend->AddEntry(haccum_scifi[it][il][1],"Y","l");
      legend->Draw();    
    }
  } 
  
  return OK;
}



int  A1Cal1AccumHist::OptimizeYRange(TPad* pad){
  TObject *obj;
  TH1     *hbase = NULL;     
  double min=10000000.,max=-10000000.;

  if(pad!=NULL){
    TIter next((TCollection*)pad->GetListOfPrimitives());
    while((obj = next())){
      if(strstr(obj->ClassName(),"TH1")!=0){
        if(strstr(next.GetOption(),"same")==NULL){
          hbase = (TH1*) obj;
          if( hbase->TestBit(TH1::kIsZoomed) ) break; 
          hbase->SetMinimum();
          hbase->SetMaximum();
        }
        if( ((TH1*)obj)->GetMinimum() < min ){
          min = ((TH1*)obj)->GetMinimum();
        }
        if( ((TH1*)obj)->GetMaximum() > max ){
          max =  ((TH1*)obj)->GetMaximum();
        }
      }
    } 
    if( hbase!=NULL && !hbase->TestBit(TH1::kIsZoomed) ){
      if(max < 1.0) {max = 1.0;}
      //hbase->SetMinimum(min-(max-min)*0.03);
      hbase->SetMinimum(0.5);
		if(pad->GetLogy()){
		  if(min < 0.01) min = 0.5;
		  hbase->SetMaximum(TMath::Power(10.,TMath::Log10(max)+(TMath::Log10(max)-TMath::Log10(min))*0.05));
		}
		else{ 
		  hbase->SetMaximum(max+(max-min)*0.05);
		}
    } 
  }
  return OK;
}

int  A1Cal1AccumHist::SetLogy(TCanvas* c,int op){
  TObject *obj;
  TPad *pad;
  if(c==NULL){return OK;}
  TIter next((TCollection*)c->GetListOfPrimitives());
  while((obj = next())){
    if(strstr(obj->ClassName(),"TPad")!=0){
      pad = (TPad*) obj;
      pad->SetLogy(op);
    }
  }
  return OK;
}

int  A1Cal1AccumHist::SetLogy(int op){
  SetLogyCal0(op);
  SetLogyCal1(op);
  SetLogyADCs(op);
  SetLogyFlag(op);
  SetLogyTDC(op);
  //SetLogySciFi(op);
  return OK;
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ Functions for online analysis                              +++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int  A1Cal1AccumHist::Init(){
  // For online analysis
  return Initialize();
}

int  A1Cal1AccumHist::Bor(){
  // For online analysis
  return OK;
}

int  A1Cal1AccumHist::Eor(){
  // For online analysis 
  return OK;
}

int  A1Cal1AccumHist::Loop(A1Cal1 *d){
  // For online analysis
  return OK;
}


#endif
