/**********************************************************************\
         Smaring simulation data with adding pedestal data 


    Simulation data set should be made with simbuild 
    Pedestal event set should be made with makepedestalevents 

    Nov. 2015 : Copy sim2exp from 2010 analysis by Menjo 
                Modified to fit for 2015 data set.

\**********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TRandom3.h>
using namespace std;

#include "LHCfEvent.h"
#include "SimIncidents.h"
#include "A1RawToCal1.h"
#include "A1PedeSubtract.h"
#include "A1Cal1ToCal2.h"
#include "A1GainCalibration.h"
#include "A1PedeSubtract.h"
#include "A1LHCCrossTalk.h"


// --------------------------------------------------------------
void printhelp(){
  cout << "sim2exp : Make experimental like data set from simulation output \n"
       << "          with adding pedestal data and converting integure values\n"
       << " \n"
       << " ./sim2exp -i (inputfile) -o (outputfile) -p (pedestal file) -d (pedestal events)\n"
       << "  inputfile : From simbuild \n"
       << "  oututfile : Contain A1Cal1 data without pedestal subtraction\n"
       << "  pedestal file   : Pedestal file made from (pedestal events) \n "
       << "  pedestal events : From makedpedstalevents\n "
       << endl;
  return ;
}

int HardwareTrigger(A1Cal2* sim, A1Cal1* cal1){
  double  threshold = 0.2; // (Temporal) Threshold 0.2 GeV 
                           // (Temporal) Appried the constant value for all layers

  unsigned int flag1 = 0;  // Hardware trigger flags (refer the logic manual )
  unsigned int flag2 = 0;  // Discriminator Flag for each channels 
  
  // Set the Discriminator Flag 
  for(int tower=0;tower<2;tower++){
    for(int layer=0;layer<16;layer++){
      if(sim->cal[tower][layer]>threshold){flag2 += 1 << (16*tower+layer);}
    }
  }

  // Shower Flag 
  int strg=0, ltrg=0, shower_trg=0;
  for(int layer=0;layer<16-2;layer++){
    if((flag2>>(0*16+layer)) == 0x7){strg++;} // Small Tower  
    if((flag2>>(1*16+layer)) == 0x7){ltrg++;} // Large Tower
  }
  if(strg>0||ltrg>0){shower_trg=1;}
  
  // Special Trigger 
  int strg_spe=0, ltrg_spe=0, special_trg=0;
  for(int layer=0;layer<5;layer++){
    if((flag2>>(0*16+layer)) == 0x7){strg++;} // Small Tower  
    if((flag2>>(1*16+layer)) == 0x7){ltrg++;} // Large Tower
  }
  if(strg_spe>0 && ltrg_spe>0){ special_trg = 1;}

  // Set the flags 
  // Bit map (refer the logic manual for Op2015)
  // 0 : BPTX1
  // 1 : BPTX2
  // 2 : BPTX_AND
  // 3 : LASER
  // 4 : L2T_SHOWER
  // 5 : L2T_SPECIAL
  // 6 : L2T_PEDESTAL
  // 7 : L2T_L1T
  // 8 : L2T_FC
  // 9 : - 
  // 10: Small Shower Trigger
  // 11: Large Shower Trigger 
  // 12: Beam Flag
  // 13: Pedestal Flag
  // 14 - 
  // 15: ATLAS_L1T
  // 16: Arm1 L1T
  // 17: Arm1 L3T
  // 18: Arm1 Enable
  // 19: Arm1 Shower Trigger & BPTX
  // 20: Arm1 L1T
  // 21: Arm1 L3T
  // 22: Arm1 Enable
  // 23: Arm1 Shower Trigger & BPTX  
  flag1 += 0x7; 
  flag1 += (shower_trg==1)? 0x10 : 0;
  flag1 += (special_trg==1)? 0x20 : 0; 
  flag1 += 0x80;
  flag1 += (strg>0)? 0x400 : 0;
  flag1 += (ltrg>0)? 0x800 : 0;
  flag1 += 0x1000;
  flag1 += 0x70000;
  flag1 += (shower_trg==1)? 0x80000 : 0;
  
  sim->flag[0] = flag1;
  sim->flag[1] = flag2;
  cal1->flag[0] = flag1;
  cal1->flag[1] = flag2;
  

  return shower_trg;
}


///////////////////////////////////////////////////////////////////
//                            MAIN                               //
///////////////////////////////////////////////////////////////////
int main(int argc, char** argv){
  
  // +++++ Argument Control +++++
  TString arg_inputfilename = "";
  TString arg_outputfilename = "";
  TString arg_pedefilename="";
  TString arg_pedeeventfilename="";

  for(int i=1;i<argc;i++){
    string ss = argv[i];
   
    if(ss=="-i"||ss=="--input")    {arg_inputfilename     = argv[++i];strcpy(argv[i],"");}
    if(ss=="-o"||ss=="--output")   {arg_outputfilename    = argv[++i];strcpy(argv[i],"");}
    if(ss=="-p"||ss=="--pedestal") {arg_pedefilename      = argv[++i];strcpy(argv[i],"");}
    if(ss=="-d"||ss=="--dummypede"){arg_pedeeventfilename = argv[++i];strcpy(argv[i],"");}  
    if(ss=="-h"||ss=="--help") {printhelp();return 0;}
      
  }
  
  if(arg_inputfilename=="" || arg_outputfilename=="" || 
     arg_pedefilename==""  || arg_pedeeventfilename=="" ){
    printhelp();
    return -1;
  }
  
  // +++++ PARAMETERS ++++++
  TString inputfilename     = arg_inputfilename;
  TString outputfilename    = arg_outputfilename;
  TString pedefilename      = arg_pedefilename;
  TString pedeeventfilename = arg_pedeeventfilename; 
  
  TString  dirLibrary             = LIBDIR;       // LIBDIR is defined in Makefile
  TString  paramConversionTable   = dirLibrary+"/tables/160208_conversion_factors.tab"; // adc/gev
  TString  paramHVgainTable       = dirLibrary+"/tables/GainsheetforCERN060812_1609.txt";
  TString  paramHvtable           = dirLibrary+"/config/hvtable_arm1_6.5TeVnormal.txt";
  TString  paramGSObarHVtable     = dirLibrary+"/tables/scifigaintable_160727.out";
  TString  paramAdcrange          = dirLibrary+"/tables/adcrange_002_100412.dat";
  Double_t paramAdcrangeThreshold = 3600.;
  Double_t paramAttenuation       = 0.908;         // See the slide by Menjo (27 Aug, Analysis meeting)
  Bool_t   paramPMTsaturationCollection = kFALSE; // For 2015, kFALSE
  TString  paramPMTSatuPath       = "";
  TString  paramPMTSatuFile       = "";
  TString  paramGSObarCrossTalk   = dirLibrary+"/tables/20141215_XtalkMatrixTemplate.root";
  TString  paramMAPMTtable        = dirLibrary+"/tables/GSObar_map9.tab";

  // ++++++ INITIALIZATIONS ++++++++++++++++++++
  TRint theApp("App",&argc,argv,0,0,kTRUE);
  
  A1Cal1ToCal2* cal1tocal2_inv = new A1Cal1ToCal2();
  cal1tocal2_inv->ReadADCRangeTable((char*)paramAdcrange.Data());
  cal1tocal2_inv->SetADCRangeThreshold(paramAdcrangeThreshold); 

  A1GainCalibration *gaincalibration = new A1GainCalibration();
  gaincalibration->ReadParticleDefineTable((char*)paramConversionTable.Data());
  gaincalibration->ReadPMTGainTable((char*)paramHVgainTable.Data());
  gaincalibration->ReadHVTable((char*)paramHvtable.Data());
  gaincalibration->SetPdefFactorPMT(paramAttenuation);
  gaincalibration->ReadScifiGainTable((char*)paramGSObarHVtable.Data());
  gaincalibration->ShowHVTable();
  
  A1Cal1* pedeav = new A1Cal1();
  TFile *fpede = new TFile(pedefilename);
  pedeav->copy((A1Cal1*)fpede->Get("a1pedestal"));
  fpede->Close();
  
  A1PedeSubtract     *pedesubtract = new A1PedeSubtract();
  pedesubtract->SetAccumNEvent(10000000);


  A1LHCCrossTalk     *a1lhccrosstalk = new A1LHCCrossTalk();  // 2016.09.02 Makino 
  a1lhccrosstalk->CTReadFile((char*)paramGSObarCrossTalk.Data());

  // ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
  // For Simulation Data
  LHCfEvent *ev   = new LHCfEvent();
  TChain    *tree = new TChain("LHCfEvents");
  tree->AddFile(inputfilename.Data());
  tree->SetBranchAddress("ev.",&ev);
  
  // For Dummy Pedestal Event Data
  LHCfEvent *ev_pede = new LHCfEvent();
  TChain    *tree_pede = new TChain("LHCfEvents");
  tree_pede->AddFile(pedeeventfilename.Data());
  tree_pede->SetBranchAddress("ev.",&ev_pede);
  
  // +++++ OPEN OUTPUT FILE +++++++++++++++++++++++++
  TFile     *ofile = new TFile(outputfilename,"RECREATE");
  LHCfEvent *oev   = new LHCfEvent();
  TTree     *otree = new TTree("LHCfEvents","Collision Events");
  otree->Branch("ev.","LHCfEvent",&oev);
  otree->SetMaxTreeSize(4000000000);
  gROOT->cd();
  
  // +++++ EVENT LOOP +++++++++++++++++++++++++++++++
  TRandom3 *rand = new TRandom3();
  rand->SetSeed(0); // set to the machine clock 
  int  nevent = tree->GetEntries();
  int  ievent = 0;
  int  nevent_pede = tree_pede->GetEntries();  
  int  ievent_pede = rand->Integer(nevent_pede);
  int  trg_event = 0;
  bool checkout = false;  
  A1Cal1* cal1 = new A1Cal1("a1cal1","");
  A1Cal1* cal1tmp = new A1Cal1(); 
  A1Cal1* pede; 
  A1Cal2* sim;
  A1Cal2* simtmp = new A1Cal2();
  A1Cal2* cal2 = new A1Cal2("a1cal2",""); 
  SimIncidents* simin;
  cout << "NEVENT: " << nevent << endl;

  //  == START OF EVENT LOOP == 
  for(int ie=0;ie<nevent;ie++){
    ev->Delete();
    ev_pede->Delete();
    tree->GetEntry(ie);
    tree_pede->GetEntry(ievent_pede);
    if(! ev->Check("a1sim")) continue;
    if(! ev_pede->Check("a1cal1")) continue;

    sim      = (A1Cal2*) ev->Get("a1sim"); 
    simin    = (SimIncidents*) ev->Get("a1simin");
    pede     = (A1Cal1*) ev_pede->Get("a1cal1");
    checkout = false;
    
    // ========== CALCULATE ==============
    // == A1Cal2("a1sim") -> A1Cal1 ==
    simtmp->copy(sim);

    // Applying crosstalk effect on GSObars ( 20160902 Added by Makino)
    a1lhccrosstalk->CalibCrossTalk_wOrgM(simtmp);

    gaincalibration->InverseCalculate(simtmp);
    cal1tocal2_inv->InverseConvert(simtmp,cal1,pede);

    // == CONVERT THE VALUE TO INTEGUERS ==
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  cal1->cal[it][il][ir] = (int)cal1->cal[it][il][ir];
	}
      }
    }
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int is=0;is<20;is++){
	  cal1->scifi0[il][ixy][is] = (int)cal1->scifi0[il][ixy][is];
	}
	for(int is=0;is<40;is++){
	  cal1->scifi1[il][ixy][is] = (int)cal1->scifi1[il][ixy][is];
	}
      }
    }
    
    // == Add pedestal values ==
    cal1->add(pede);

    // == Overflow ==
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  if(cal1->cal[it][il][ir] > 4000){ cal1->cal[it][il][ir] = 8000;}
	}
      }
    }
    // For the momonet, don't apply the overflow emulation in this conversion
//     for(int il=0;il<4;il++){
//       for(int ixy=0;ixy<2;ixy++){
// 	for(int is=0;is<20;is++){
// 	  if(cal1->scifi0[il][ixy][is] > 65500){ cal1->scifi0[il][ixy][is] = 65300;}
// 	}
// 	for(int is=0;is<40;is++){
// 	  if(cal1->scifi1[il][ixy][is] > 65500){ cal1->scifi1[il][ixy][is] = 65300;}
// 	}
//       }
//     }  

    ievent_pede++;
    if(ievent_pede>=nevent_pede) {ievent_pede=0;}
    cal1tmp->copy(cal1);

    // ========== EVENT SELECTION ========
    if(HardwareTrigger(sim,cal1)){
      checkout = true;
      trg_event++;
    }

    // ======== FILL TO SIMULATION ======
    oev->HeaderCopy(ev);
    oev->Add(simin);
    oev->Add(sim); // For debug
    oev->Add(cal1);
    otree->Fill();
    oev->Clear();
    ievent++;
    
    //if(ie>1000){ break; }
    if(ie && ie%500==0){ cerr << '*' ; }
    if(ie && ie%10000==0){cerr << ie << endl;}
  }
  cerr << endl;
  
  cout << "NEVENT:  " << ievent << endl
       << "TRGGERD: " << trg_event << endl
       << "Efficiency: " << (double)trg_event/(double)ievent << endl;


  // ++++++++++++++++ WRITE OUTPUT TREE ++++++++++++++++++++
  ofile->cd();
  otree->Write("",TObject::kOverwrite);
  ofile->Close();

}
