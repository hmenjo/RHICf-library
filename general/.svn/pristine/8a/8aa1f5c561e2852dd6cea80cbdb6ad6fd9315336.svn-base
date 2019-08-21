#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#if defined(__CINT__) && !defined(__MAKECINT__)
#include "libLHCfEvent.so"
#else
#include "LHCfEvent.h"
#include "SimIncidents.h"
#endif
#include "A1RawToCal1.h"
#include "A1PedeSubtract.h"
#include "A1Cal1ToCal2.h"
#include "A1GainCalibration.h"
#include "A1PedeSubtract.h"
using namespace std;

void mkdummy_arm1();
void mkdummy();
int  HardwareTrigger(A1Cal2* cal);
void FillHardwareFlags_TRG(A1Cal2* cal, A1Raw* raw);
void FillHardwareFlags_PEDE(A1Raw* raw);

int    nsimfile=0;
char   simfile[10][256];
int    npedefile=0;
char   pedefile[10][256];
char   hvtable[256];
double dsc=150.;
int    nsim_max =1000000;
int    npede_max=1000000;
const double particle2mev = 1./0.453;

#if !defined(__CINT__)
int main(int argc, char** argv){
  int   tmp = 2;
  char* tmpargv[2];
  bool  checkq = true; 
  tmpargv[0] = argv[0];
  tmpargv[1] = "-b";
  TApplication theApp("App",&tmp,tmpargv);
  
  strcpy(hvtable,"config/hvtable_arm1_LL_SHV480.txt");
  dsc = 150.;
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-sim")==0){
      strcpy(simfile[nsimfile++],argv[++i]);
    }
    if(strcmp(argv[i],"-pede")==0){
      strcpy(pedefile[npedefile++],argv[++i]);
    } 
    if(strcmp(argv[i],"-hv")==0){
      strcpy(hvtable,argv[++i]);
    } 
    if(strcmp(argv[i],"-dsc")==0){
      dsc = atof(argv[++i]);
    }   
    if(strcmp(argv[i],"-nsim_max")==0){
      nsim_max = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-npede_max")==0){
      npede_max = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-help")==0 || 
       argc==1){
      cout << " mkdummy_arm1 --------------------------------------------\n"
	   << "  It makes dummy data for Frontend1 from simulation data and\n"
	   << "  pedestal data obtained with actual DAQ system. \n"
	   << "  An outpuf file of \"dummyevents.root\"(fixed name) should be\n"
	   << "  copy in the derectory of \"Frontend1/dummy/\"\n"
	   << "  v1.0 : coded by H.MENJO at 20 Apr. 2009.\n"
	   << "Command)\n"
	   << " ./mkdummy_arm1 -sim erun0001.root -pede pede0001.root \n"
	   << " [-hv hvtable.txt] [-dsc 150] [-nsim_max 1000000] [-nsim_pede 1000000]\n"
	   << "Option)\n"
	   << " -sim   : Simulation data converted to \"LHCfEvents\". \n"
	   << "          Some files can be listed (up to 10files) as following.\n"
	   << "          -sim run001.root -sim run002.root -sim -run003.root\n"
	   << " -pede  : Pedestal data event-built. Some files can be listed.\n"
	   << " -hv    : HV table. The table file should have correct format.\n"
	   << "          (default config/hvtable_arm1_LL_SHV480.txt)\n"
	   << " -dsc   : Vertual discriminator level[MeV]. (default 150MeV)\n"
	   << " -nsim_max  : Maximum number of trigger events.  (default 1000000)\n"
	   << " -npede_max : Maximum number of pedestal events. (default 1000000)\n"
	   << endl;
      return 0;
    }
  }
  
  if(nsimfile==0 || npedefile==0){
    cerr << "Please set simulation/pedestal files." << endl; 
    return -1;
  }
  
  mkdummy();

  if(!checkq){theApp.Run();}
  return 0;
}
#endif

void mkdummy_arm1(){
  strcpy(simfile[nsimfile++],"end2end_dpm0001.root");
  strcpy(pedefile[npedefile++],"erun00859.root");
  strcpy(hvtable,"config/hvtable_arm1_LL_SHV480.txt");
  dsc = 150.;
  mkdummy();
  return ;
}

void mkdummy(){
  // ********* Parameters *********************************************
  char scifipostable[] = "../../tables/scifi_pos_table_080408.dat";
  char adcrangetable[] = "../../tables/adcrange_dummy.dat";
  char pdeftable_adc[] = "../../tables/pdef_sps07_arm1_080828.out";
  char pdeftable_scifi[] = "../../tables/pardef_scifi_102_071019.txt";
  char pmtgaintable[] = "../../tables/GainsheetforCERN060812_1609.txt";
  char scifigaintable[] = "../../tables/scifigaintable_081103.out";
  // char hvtable[] = "config/hvtable_arm1_LL_SHV480.txt";
  // char hvtable[] = "config/hvtable_arm1_HH_SHV480.txt";

  // ********* Open Inputfiles *****************************************
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  for(int ifile=0;ifile<nsimfile;ifile++){
    tree->AddFile(simfile[ifile]);
  }
  tree->SetBranchAddress("ev.",&ev);

  LHCfEvent *ev_pede = new LHCfEvent();
  TChain* tree_pede = new TChain("LHCfEvents");  
  for(int ifile=0;ifile<npedefile;ifile++){
    tree_pede->AddFile(pedefile[ifile]);
  }
  tree_pede->SetBranchAddress("ev.",&ev_pede);

  // ************** Initializetion of Calibration Functions **************
  A1RawToCal1* a1rawtocal1 = new A1RawToCal1();
  a1rawtocal1->ReadScifiPosTable(scifipostable); 
  
  A1Cal1ToCal2* a1cal1tocal2 = new A1Cal1ToCal2();
  a1cal1tocal2->ReadADCRangeTable(adcrangetable);
  a1cal1tocal2->SetADCRangeThreshold(4000.);
  
  A1GainCalibration *a1gaincalibration = new A1GainCalibration();
  a1gaincalibration->ReadParticleDefineTable(pdeftable_adc,"ADC");
  a1gaincalibration->ReadParticleDefineTable(pdeftable_scifi,"SCIFI");
  a1gaincalibration->ReadPMTGainTable(pmtgaintable);
  a1gaincalibration->ReadScifiGainTable(scifigaintable);
  a1gaincalibration->ReadHVTable(hvtable);

  // *************** Open outputfile ************************************
  TFile *file = new TFile("./dummyevent.root","RECREATE");

  A1Raw *trg = new A1Raw();
  A1Raw *pede = new A1Raw();
  TTree* tree_Trg  = new TTree("Trigger", "Arm#1 Trigger Event");
  TTree* tree_Pede = new TTree("Pedestal","Arm#1 Pedestal Event");

  tree_Trg->Branch("ev.","A1Raw",&trg);
  tree_Pede->Branch("ev.","A1Raw",&pede);
  
  // *************** Print Parameters *********************************
  cout << "=============== mkdummy3_arm1 v1.0  =================\n";
  cout << "  Simulation File: " << simfile[0] << endl;
  for(int i=1;i<nsimfile;i++){
    cout << "                   " << simfile[0] << endl;  
  }
  cout << "  Pedestal File:   " << pedefile[0] << endl;
  for(int i=1;i<npedefile;i++){
    cout << "                   " << pedefile[0] << endl;  
  }
  cout << "  HV Table : " << hvtable << endl;
  a1gaincalibration->ShowHVTable();
  // ****************** LOOP *******************************************
  A1Cal2* a1sim;
  A1Cal2* a1sim_tmp = new A1Cal2(); 
  A1Raw*  a1pede;
  A1Cal1* a1cal1 = new A1Cal1(); 
  A1Cal1* a1pede_cal1 = new A1Cal1();
  // ------------- For Trigger event ----------------------------------
  int  nevent = tree->GetEntries();
  int  ievent = 0;
  int  nevent_pede = tree_pede->GetEntries();  
  int  ievent_pede = 0;
  int  trg_event = 0;
  bool checkout = false;
  cout << endl 
       << "Loop start for trgger event.................." << endl;
  cout << "NEVENT: " << nevent << endl;
  for(int ie=0;ie<nevent;ie++){ 
    if(ie && ie%500==0){ cerr << '*' ; }
    if(ie && ie%10000==0){cerr << ie << endl;}
    ev->Delete();
    tree->GetEntry(ie);

    if(! ev->Check("a1sim")) continue; 
    a1sim = (A1Cal2*) ev->Get("a1sim"); 
    ievent++; 
    
    // ********************* Event Selection **********************
    checkout = false;
    if(HardwareTrigger(a1sim)){
      checkout = true;
    }
    else{
      continue;
    }
    
    // ********************** Get Pedestal Event *************************
    for(int ie_pede=ievent_pede;ie_pede<nevent_pede;ie_pede++){
      ev_pede->Delete();
      tree_pede->GetEntry(ie_pede);
      ievent_pede++;
      if(ievent_pede>=nevent_pede) {ie_pede=0; ievent_pede=0;}
      if(ev_pede->Check("a1raw")) break;
    }
    
    a1pede = (A1Raw*) ev_pede->Get("a1raw");

    // *************************** Conversion *****************************
    a1rawtocal1->Convert(a1pede,a1pede_cal1); 
    // A1Cal2("a1sim") -> A1Cal1 ("a1cal1")
    a1sim_tmp->copydata(a1sim);
    a1gaincalibration->InverseCalculate(a1sim);
    a1cal1tocal2->InverseConvert(a1sim,a1cal1,a1pede_cal1);
    // A1Cal2("a1cal1") -> A1Raw ("trg")
    a1rawtocal1->InverseConvert(a1cal1,trg);    
    trg->add(a1pede, A1Raw::ALL-A1Raw::TDC0-A1Raw::GPIO0-A1Raw::GPIO1);
    trg->copydata(a1pede,A1Raw::TDC0+A1Raw::GPIO0+A1Raw::GPIO1);

    // ********************* Fill calculated event ****************
    if(checkout==true){
      FillHardwareFlags_TRG(a1sim_tmp,trg);  
      tree_Trg->Fill();
      trg_event++;
    }
    if(trg_event>=nsim_max) break;
  }
  cerr << endl;
  cout << "NEVENT:   " << ievent << endl
       << "TRGGERD:  " << trg_event << endl;
  
  // ------------- For Pedestal events ----------------------------------
  cout << endl
       << "Loop start for pedestal event.................." << endl;
  cout << "NEVENT:  " << nevent_pede << endl;
  ievent=0;
  trg_event=0;
  for(int ie=0;ie<nevent_pede;ie++){
    if(ie && ie%500==0){ cerr << '*' ; }
    if(ie && ie%10000==0){cerr << ie << endl;}
    ev_pede->Delete();
    tree_pede->GetEntry(ie);
    ievent++;
    if(! ev_pede->Check("a1raw")) continue;
    
    a1pede = (A1Raw*) ev_pede->Get("a1raw");
    pede->copydata(a1pede); 
    FillHardwareFlags_PEDE(pede);
    tree_Pede->Fill();
    trg_event++; 
    
    if(trg_event>=npede_max) break;
  }
  cerr << endl;
  cout << "NEVENT:   " << ievent << endl
       << "PEDESTAL: " << trg_event << endl;
  
  // ********************* Write in output file ************* 
  tree_Trg->Write("",TObject::kOverwrite); 
  tree_Pede->Write("",TObject::kOverwrite);
  file->Close();
  
}

int HardwareTrigger(A1Cal2* cal){
  double threshold = dsc*particle2mev;
  int     hwtrg=0;
  for(int it=0;it<2;it++){
    for(int i=0;i<16-2;i++){
      if(cal->cal[it][i]   > threshold &&
	 cal->cal[it][i+1] > threshold &&
	 cal->cal[it][i+2] > threshold){
	hwtrg++;
      }
    }
  }
  return hwtrg;
}

void FillHardwareFlags_TRG(A1Cal2* cal, A1Raw* raw){
  double threshold = dsc*particle2mev;
  // Simulate LHCFLOGIC Event Flags2 Register 
  raw->gpio0[1] = 0;
  // Small Tower
  for(int i=0;i<16;i++){
    if(cal->cal[0][i] > threshold){
      raw->gpio0[1] += (0x1 << i);
    }
  }
  // Large Tower
  for(int i=0;i<16;i++){
    if(cal->cal[1][i] > threshold){
      raw->gpio0[1] += (0x1 << (i+16));
    }
  } 

  // Simulate LHCFLOGIC Event Flags1 Register
  raw->gpio0[0] = 0x0; 
  // BPTX1 and 2
  raw->gpio0[0] += 0x3;
  // L2TA and L2T_L1T
  raw->gpio0[0] += 0x110;
  // BEAMFLAG and ENABLEFLAG
  raw->gpio0[0] += 0x9000;
  // Small tower
  int     hwtrg=0;
  for(int i=0;i<16-2;i++){
    if(cal->cal[0][i]   > threshold &&
       cal->cal[0][i+1] > threshold &&
       cal->cal[0][i+2] > threshold){
      hwtrg = 1;
    }
  }
  if(hwtrg==1){ raw->gpio0[0] += ( 0x1 << 10 ); }
  hwtrg=0;
  for(int i=0;i<16-2;i++){
    if(cal->cal[1][i]   > threshold &&
       cal->cal[1][i+1] > threshold &&
       cal->cal[1][i+2] > threshold){
      hwtrg = 1;
    }
  } 
  if(hwtrg==1){ raw->gpio0[0] += ( 0x1 << 11 ); }
  return ;
}

void FillHardwareFlags_PEDE(A1Raw* raw){
  // Simulate LHCFLOGIC Event Flags2 Register
  raw->gpio0[1] = 0;

  // Simulate LHCFLOGIC Event Flags1 Register
  raw->gpio0[0] = 0;
  // BPTX1 and 2
  raw->gpio0[0] += 0x3;
  // L2TP and L2T_L1T
  raw->gpio0[0] += 0x120;
  // PEDEFLAG and ENABLEFLAG
  raw->gpio0[0] += 0xA000;
}
