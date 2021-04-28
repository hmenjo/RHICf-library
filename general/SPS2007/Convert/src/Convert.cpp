#include <TROOT.h>
#include <TRint.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#if defined(__CINT__) && !defined(__MAKECINT__)
#include "libLHCfEvent.so"
#else
#include "LHCfEvent.h"
#include "SPSAdamo.h"
#endif
#include <iostream>
#include <iomanip>
using namespace std;

#include "RawTree.hh"
#include "Cal01.hh"
#include "CalFSIL1.hh"
#include "CalFlags1.hh"
#include "Cal01Calculation.hh"
#include "CalFSIL1Calculation.hh"
#include "CalFlags1Calculation.hh"

struct ArgParam{
  char ifilename[256];  
  char ofilename[256];
  int  detector;
  bool opdraw;
};

void printhelp();
void Convert(ArgParam &param);
int ConvertionSPSfromLHC(Raw       *rdata,
			 Cal01     *c1data, 
			 CalFSIL1  *cfsil1,
			 CalFlags1 *cflags1, 
			 A1Cal1    *cal1,
			 SPSAdamo  *adamo);
int ConvertionSPSfromLHC(Raw       *rdata,
			 Cal01     *c1data, 
			 CalFSIL1  *cfsil1,
			 CalFlags1 *cflags1, 
			 A2Cal1    *cal1,
			 SPSAdamo  *adamo);

#if !defined(__CINT__)
int main(int argc, char** argv){

  ArgParam param;
  strcpy(param.ifilename,""); 
  strcpy(param.ofilename,"");
  param.detector = 0;
  param.opdraw   = false;
  for(int i=1;i<argc;i++){
    if(strcmp(argv[i],"-i")==0){
      strcpy(param.ifilename,argv[++i]);
      strcpy(argv[i],""); 
    }
    if(strcmp(argv[i],"-o")==0){
      strcpy(param.ofilename,argv[++i]); 
      strcpy(argv[i],""); 
    } 
    if(strcmp(argv[i],"-arm1")==0 || strcmp(argv[i],"-Arm1")==0){
      param.detector = 1;
    }
    if(strcmp(argv[i],"-arm2")==0 || strcmp(argv[i],"-Arm2")==0){
      param.detector = 2;
    }
    if(strcmp(argv[i],"--draw")==0){
      param.opdraw = true;
    }
    if(strcmp(argv[i],"--nodraw")==0){
      param.opdraw = false;
    }    
    if(strcmp(argv[i],"-h")==0){
      printhelp();
      return 0;
    }
  }

  if(strcmp(param.ifilename,"")==0 || 
     strcmp(param.ofilename,"")==0 || 
     param.detector==0){
    printhelp();
    return 0;
  }

  TApplication theApp("App",&argc,argv,0,0);
  
  Convert(param);
  
  //theApp.Run();
  return 0;
}
#endif

void printhelp(){
  cout << " ++++++++++++++      Convert       +++++++++++++++++  \n"
       << " Convert beam test data from old format to new format \n" 
       << "                                                      \n" 
       << " Options)                                             \n"
       << "  -i    :   Input file (beam test data)               \n"
       << "  -o    :   Output file (with LHCfEvent)              \n"
       << "  -arm1/-arm2 :  Selection of detector                \n"
       << endl;
  return ;
}

void Convert(ArgParam &param){
  
  int detector = param.detector;

  // OPEN INPUT FILE +++++++++++++++++++++++++++++++++++++++++++++++
  RawTree *rtree = new RawTree();
  rtree->AddFile(param.ifilename);
  rtree->Open();
  Raw     *rdata = rtree->GetData();
  RawFSIL *rfsil = rtree->GetFSIL();
 

  // OPEN OUTPUT FILE +++++++++++++++++++++++++++++++++++++++++++++++
  gROOT->cd();
  LHCfEvent *oev = new LHCfEvent("LHCfEvent","");
  TFile *ofile = new TFile(param.ofilename,"RECREATE");
  TTree *otree = new TTree("LHCfEvents","SPS beam test in 2007");
  otree->Branch("ev.","LHCfEvent",&oev);
  A1Cal1   *a1cal = new A1Cal1("a1cal1","SPS BEAM TEST");
  A2Cal1   *a2cal = new A2Cal1("a2cal1","SPS BEAM TEST");
  SPSAdamo *adamo = new SPSAdamo("adamo","ADAMO AT BEAM TEST");

  // INITIALIZE FUNCTIONS +++++++++++++++++++++++++++++++++++++++++++
  const char* scifipos = "./tables/scifi_pos_table.dat";
  Cal01* c1data = new Cal01();
  Cal01Calculation*  c01calcalculation = new Cal01Calculation();
  c01calcalculation->SetRawData(rdata);
  c01calcalculation->SetCal01Data(c1data);
  c01calcalculation->ReadScifiPosTable((char*)scifipos);
  c01calcalculation->SetDetector(detector);
  
  CalFSIL1* cfsil1 = new CalFSIL1();
  CalFSIL1Calculation* calf1 = new CalFSIL1Calculation();
  calf1->SetRawFSILData(rfsil);
  calf1->SetCalFSIL1Data(cfsil1);
  
  CalFlags1 *cflags1 = new CalFlags1();
  CalFlags1Calculation* calflags1 = new CalFlags1Calculation();
  calflags1->SetRawData(rdata);
  calflags1->SetCalFlags1Data(cflags1);
  
  // PRINT INFORMATION +++++++++++++++++++++++++++++++++++++++++++++
  cout << " CONVERT FORMAT   " << (detector==1 ? "ARM1" : "ARM2" ) << endl
       << "    FROM (SPS) " << param.ifilename << endl
       << "    TO   (LHC) " << param.ofilename << endl;

  // LOOP ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  int nevent = rtree->GetEntries();
  cout << "NEVENT: "<< setw(7) << right  << nevent << endl;
  for(int ie=0;ie<nevent;ie++){
    rtree->GetEntry(ie);
   
    // PRINT NUBER OF EVENTS +++++++++++++++++++++++++++++++++++++++
    if(ie%100==0) {
      cout << "\033[60D";  // Move 60 spaces to right
      cout << "\033[K";    // Clear from this position to the end of line.
      cout << "EVENT:  " << setw(7) << right << ie << flush;
    }


    // CONVERSION FROM RAW TO CAL IN BEAM TEST FORMAT ++++++++++++++
    c01calcalculation->Calculate();
    calf1->Calculate(); 
    calflags1->Calculate();

    if(detector==1){
      ConvertionSPSfromLHC(rdata,c1data,cfsil1,cflags1,a1cal,adamo);
    }
    if(detector==2){
      ConvertionSPSfromLHC(rdata,c1data,cfsil1,cflags1,a2cal,adamo);
    }

    // FILL TO TTREE +++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    if(detector==1){ oev->run = a1cal->run; oev->gnumber = a1cal->gnumber ;}
    if(detector==2){ oev->run = a2cal->run; oev->gnumber = a2cal->gnumber ;}
    oev->a1number  = a1cal->number;
    oev->a2number  = a2cal->number;  
    oev->a1flag[0] = a1cal->flag[0];
    oev->a1flag[1] = a1cal->flag[2];   
    oev->a2flag[0] = a2cal->flag[0];
    oev->a2flag[1] = a2cal->flag[2];
    oev->ifile     = 0;
    oev->tnumber   = ie;
    oev->tag       = 0;
    if(detector==1)  oev->Add(a1cal);
    if(detector==2)  oev->Add(a2cal); 
    if(adamo->run>0) oev->Add(adamo);
    otree->Fill();
    oev->Clear(); 
  }
  cout << endl;
  
  // WRITE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  otree->Write("",TObject::kOverwrite);
  ofile->Close();
  
  return ;
}


// ----------------------------------------------------------------
// MEMO FOR THE DATA FORMAT OF BEAM TEST 
//   - ADC0 
//     FOR SMALL TOWER, NOT INCLUDE THE DELAYED GATE, 
//   - ADC1 
//     FOR LARGE TOWER, NOT INCLUDE THE DELAYED GATE, 
//   - ADC2
//     ???  TRIGGER SCINTILLATOER ?
//   
//   - I/O REGISTER
//     0 : BEAM FLAG
//     1 : PEDESTAL FLAG
//     2 : LASER FLAG
//     3 : SHOWER FLAG OF SMALL TOWER
//     4 : SHOWER FLAG OF LARGE TOWER
//     
//   - SCALWER
//     0 : SCINTILLATOR 1 (TRIGGER SCINTILLATOR?)
//     1 : SCINTILLATOR 2 (TRIGGER SCINTILLATOR?)
//     2 : SCINTILLATOR 3 (TRIGGER SCINTILLATOR?)
//     3 : COIN ??
//     4 : BCOIN ??
//     5 : TRIGGER 
//     6 :SHOWER OF SMALL TOWER
//     7 :SHOWER OF LARGE TOWER
//    
// -----------------------------------------------------------------
// ----- CONVERSION BEAM TEST FORMAT TO LHC FORMAT FOR AMR1  -------
// -----------------------------------------------------------------
int ConvertionSPSfromLHC(Raw       *rdata,
			 Cal01     *c1data, 
			 CalFSIL1  *cfsil1,
			 CalFlags1 *cflags1, 
			 A1Cal1    *cal1,
			 SPSAdamo  *adamo){
  cal1->clear();

  // ++ EVENT HEADER ++
  cal1->run     = c1data->Run;
  cal1->gnumber = c1data->Number;
  cal1->number  = c1data->Number;
  cal1->time[0] = cflags1->Time;

  // ++ FOR CALORIMETERS ++
  for(int il=0;il<16;il++){
    cal1->cal[0][il][0] = c1data->cADC0L[il];
    cal1->cal[0][il][1] = c1data->cADC0H[il];
    cal1->cal[1][il][0] = c1data->cADC1L[il];
    cal1->cal[1][il][1] = c1data->cADC1H[il]; 
  }

  // ++ FOR SCIFI ++
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      // 20mm
      for(int is=0;is<20;is++){
	cal1->scifi0[il][ixy][is] = c1data->cSCIF0[il][ixy][is];
      }
      // 40mm
      for(int is=0;is<40;is++){
	cal1->scifi1[il][ixy][is] = c1data->cSCIF1[il][ixy][is];
      }
    }
  }

  // ++ FOR THE OTHER ADC 
  for(int il=0;il<8;il++){
    cal1->emptyadc[il] = c1data->cADC2L[il];
  }
  
  // ++ FOR FLAGS ++
  cal1->flag_beam  = cflags1->inp0[0];   // BEAM 
  cal1->flag_pede  = cflags1->inp0[1];   // PEDE
  cal1->flag_laser = cflags1->inp0[2];   // LASER   
  cal1->flag[0]   |= (cflags1->inp0[0] ? 0x1000 : 0);   // BEAM FLAG
  cal1->flag[0]   |= (cflags1->inp0[1] ? 0x2000 : 0);   // PEDE FLAG
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x4000 : 0);   // LASER FLAG 
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x0400 : 0);   // SHOWER TRG AT SMALL TOWER
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x0800 : 0);   // SHOWER TRG AT LARGE TOWER  
  cal1->flag[0]   |= (cal1->flag_beam  ? 0x0013 : 0x0003); // DUMMY : BPTX1,BPTX2, L2TA
  
  // ++ FOR SCALER ++
  for(int i=0;i<8;i++){
    cal1->scl0[i]    = cflags1->scaler[i];
  }  
  
  // ++ FOR TDC ++
  unsigned int tmpdata;
  int tmpvalue;
  int tmpchannel;
  int tmpphase;
  int tmpvalid;
  int tmpend=1;
  int nhit[12]={0};
  for(int ib=0;ib<100;ib++){
    tmpdata = rdata->TDC0.TDC0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpvalue = tmpdata & 0xFFFF;
    tmpchannel = ((tmpdata >> 17) & 0xF);
    tmpphase = ((tmpdata >> 16) & 0x1);
    tmpvalid = ((tmpdata >> 21) & 0x1);
    tmpend = (tmpdata >> 23) & 0x1;
    if(tmpchannel >= 12){
      cerr << " Warning: TDC channel is >= 12;" 
           << tmpchannel << endl;
    }
    else {
      if(nhit[tmpchannel]>=16){
        cerr << " Warning: " 
             << "#hits of TDC["<< tmpchannel<<"] is over 16." << endl;   
      }
      else{
        cal1->tdc0[tmpchannel][nhit[tmpchannel]] = tmpvalue*1.0; 
        cal1->tdc0flag[tmpchannel][nhit[tmpchannel]] = 0x2*tmpvalid + 0x1*tmpphase;
        nhit[tmpchannel]++;
	//cout << "TDC " << tmpchannel << "  " << tmpvalue*1.0 << endl;
      }
    }
    if(tmpend==0){break;}
  }

  // ++ FOR ADAMO ++
  if(cfsil1->nFSIL > 0){
    adamo->run     = cal1->run;
    adamo->gnumber = cal1->gnumber;   
    adamo->number  = cal1->number;
    for(int il=0;il<5;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<5;istrip++){
	  adamo->strip[il][ixy][istrip] = cfsil1->cFSIL[il][ixy][istrip];
	}
      }
    }
  }

  return OK;
}

int ConvertionSPSfromLHC(Raw       *rdata,  
			 Cal01     *c1data, 
			 CalFSIL1  *cfsil1,
			 CalFlags1 *cflags1, 
			 A2Cal1    *cal1,
			 SPSAdamo  *adamo){

  cal1->clear();

  // ++ EVENT HEADER ++
  cal1->run     = c1data->Run;
  cal1->gnumber = c1data->Number;
  cal1->number  = c1data->Number;
  cal1->time[0] = cflags1->Time;

  // ++ FOR CALORIMETERS ++
  for(int il=0;il<16;il++){
    cal1->cal[0][il][0] = c1data->cADC0L[il];
    cal1->cal[0][il][1] = c1data->cADC0H[il];
    cal1->cal[1][il][0] = c1data->cADC1L[il];
    cal1->cal[1][il][1] = c1data->cADC1H[il]; 
  }

  // ++ FOR SILICON ++
  

  // ++ FOR THE OTHER ADC 
  for(int il=0;il<8;il++){
    cal1->emptyadc[il] = c1data->cADC2L[il];
  }
  
  // ++ FOR FLAGS ++
  cal1->flag_beam  = cflags1->inp0[0];   // BEAM 
  cal1->flag_pede  = cflags1->inp0[1];   // PEDE
  cal1->flag_laser = cflags1->inp0[2];   // LASER   
  cal1->flag[0]   |= (cflags1->inp0[0] ? 0x1000 : 0);   // BEAM FLAG
  cal1->flag[0]   |= (cflags1->inp0[1] ? 0x2000 : 0);   // PEDE FLAG
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x4000 : 0);   // LASER FLAG 
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x0400 : 0);   // SHOWER TRG AT SMALL TOWER
  cal1->flag[0]   |= (cflags1->inp0[2] ? 0x0800 : 0);   // SHOWER TRG AT LARGE TOWER 
  cal1->flag[0]   |= (cal1->flag_beam  ? 0x0013 : 0x0003); // DUMMY : BPTX1,BPTX2, L2TA 
  
  // ++ FOR SCALER ++
  for(int i=0;i<8;i++){
    cal1->scl0[i]    = cflags1->scaler[i];
  }  
  
  // ++ FOR TDC ++
  unsigned int tmpdata;
  int tmpvalue;
  int tmpchannel;
  int tmpphase;
  int tmpvalid;
  int tmpend=1;
  int nhit[12]={0};
  for(int ib=0;ib<100;ib++){
    tmpdata = rdata->TDC0.TDC0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpvalue = tmpdata & 0xFFFF;
    tmpchannel = ((tmpdata >> 17) & 0xF);
    tmpphase = ((tmpdata >> 16) & 0x1);
    tmpvalid = ((tmpdata >> 21) & 0x1);
    tmpend = (tmpdata >> 23) & 0x1;
    if(tmpchannel >= 12){
      cerr << " Warning: TDC channel is >= 12;" 
           << tmpchannel << endl;
    }
    else {
      if(nhit[tmpchannel]>=16){
        cerr << " Warning: " 
             << "#hits of TDC["<< tmpchannel<<"] is over 16." << endl;   
      }
      else{
        cal1->tdc0[tmpchannel][nhit[tmpchannel]] = tmpvalue*1.0; 
        cal1->tdc0flag[tmpchannel][nhit[tmpchannel]] = 0x2*tmpvalid + 0x1*tmpphase;
        nhit[tmpchannel]++;
	//cout << "TDC " << tmpchannel << "  " << tmpvalue*1.0 << endl;
      }
    }
    if(tmpend==0){break;}
  }

  // ++ FOR ADAMO ++
  if(cfsil1->nFSIL > 0){
    adamo->run     = cal1->run;
    adamo->gnumber = cal1->gnumber;   
    adamo->number  = cal1->number;
    for(int il=0;il<5;il++){
      for(int ixy=0;ixy<5;ixy++){
	for(int istrip=0;istrip<5;istrip++){
	  adamo->strip[il][ixy][istrip] = cfsil1->cFSIL[il][ixy][istrip];
	}
      }
    }
  }

  
  return OK;
}
