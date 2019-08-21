#ifndef __A1CAL1_CPP__
#define __A1CAL1_CPP__

#include "A1Cal1.h"

//----------------------------------------------------------------------
// A1Cal1
//
// This class stores the calculated data of Frontend1 with a meaningful structure.
// In this class, raw data or pedestal subtracted data should be filled.
//
// =========================================================================
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO) 
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - bool   flag_beam  (Beam Flag picked up from GPIO Flag Register)
//  - bool   flag_pede  (Pedestal Flag picked up from GPIO Flag Register)
//  - bool   flag_laser (Laser Flag picked up from GPIO Flag Register)
//
//  - double cal[2][16][2]  [tower][channel][range]
//     ADC values for PMTs in the 20 calorimeter.
//      tower: 0=20mm,1=40mm
//      channel: 0-15
//      range: 0=LowRange(0.025pC/count), 1=LowRange(0.20pC/count)
//
//  - double cald[2][16][2]  [tower][channel][range]
//     ADC values of delayed gate. The delayed gate is generated about 10usec
//     after the normal gate. It is useful for pedestal subtraction event by event.
//     However you must check if no accidental signals in the values.
//
//  - double fc[2][4]  [arm][channel]
//     ADC values of Front Counters.
//      arm: 0=Arm1,1=Arm2
//      channel: 0-3
//     In the final configuration of DAQ, only data of Arm2 FC is taken in Arm1 Frontend.
//
//  - double fcd[2][4]  [arm][channel]
//     ADC values of delayed gate for Front Counters
//
//  - double laser[2]  [channel]
//     ADC values of Laser Monitor PMTs
//      channel: 0="L", 1="R"
//
//  - double laserd[2]  [channel]
//     ADC values of delayed gate for Laser Monitor PMTs
//
//  - double emptyadc[8]  [channel]
//     ADC values of noise.
//     Data only in 0-2 chennel may be filled.
//
//  - double scifi0[4][2][20]   [layer][xy][fiber]
//     ADC values of SciFi in the 20mm caliorimeter.
//      layer: 0-3
//      xy:    0="X",1="Y"
//      fiber: 0-19
//
//  - double scifi1[4][2][40]   [layer][xy][fiber]
//     ADC values of SciFi in the 40mm caliorimeter.
//
//  - double tdc0[12][16]       [channel][hit]
//     TDC value (sec)
//      channel: 0-11
//      hit:     0-15  if only have #hit, value of >#hit are 0.
//    Channel List:
//     [0]  :  Masked 40MHz Clock (first value not be used) 
//     [1]  :  L3T 
//     [2]  :  BPTX1
//     [3]  :  BPTX2
//     [4]  :  Shower Trigger 
//     [5]  :  ATLAS L1A
//     [6]  :  Arm1 FC Logic OR
//     [7]  :  Arm2 FC Logic OR
//     [8]  :  20mm Discriminator OR
//     [9]  :  40mm Discriminator OR
//     [10] :  no input
//     [11] :  no input
//
//  - char   tdc0flag[12][16]   [channel][hit]
//     Flag for each hit.
//      if no hit, -1 is filled.
//      bit 0x1 means phase of the hit.
//      bit 0x2 means valid/invalid flag.
//
//  - double  scl0[16]  [channel]
//     Scaler values
//     Channel List (for configuration in 2009)
//      [0] :  40MHz Clock
//      [1] :  Cascade from [0]
//      [2] :  BPTX1
//      [3] :  Cascade from [2]
//      [4] :  BPTX2
//      [5] :  Cascade from [4]
//      [6] :  L3T
//      [7] :  L2TA
//      [8] :  Arm1 FC1
//      [9] :  Arm1 FC2
//      [10]:  Arm1 FC3
//      [11]:  Arm1 FC4
//      [12]:  LHCFCOUNTER:MLEMO(10) Arm1 FC Logic
//      [13]:  LHCFCOUNTER:MLEMO(11) Arm2 FC Logic
//      [14]:  LHCFCOUNTER:MLEMO(9)  Coincident of Arm1 FC and Arm2 FC
//      [15]:  no input
//
//     Channel List (for configuration in 2015)     
//      [0] :  Cascade from [0]
//      [1] :  40MHz Clock
//      [2] :  BPTX1
//      [3] :  BPTX2
//      [4] :  L3T
//      [5] :  FC Coincidence
//      [6] :  FC1 TRG
//      [7] :  FC2 TRG
//      [8] :  Arm1 FC1
//      [9] :  Arm1 FC2
//      [10]:  Arm1 FC3
//      [11]:  Arm1 FC4
//      [12]:  -
//      [13]:  -
//      [14]:  - 
//      [15]:  -
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int counter[35]
//     Counter values of GPIOs
//      [0-14]  Counter values in LHCFLOGIC
//      [15-34] Counter values in LHCFCOUNTER
//     Counter list (for LHCFLOGIC_V2.5 and LHCFCOUNTER_V2.5)
//      [0]  : 40MHz Clock (Cleared by LHCF_ECR)
//      [1]  : L1T (Cleared by LHCF_ECR)
//      [2]  : BPTX1 "AND" BPTX2 (Cleared by LHCF_ECR)
//      [3]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cleared by LHCF_ECR)
//      [4]  : Shower Trigger of 20mm cal. (Cleared by LHCF_ECR)
//      [5]  : Shower Trigger of 40mm cal. (Cleared by LHCF_ECR)
//      [6]  : Shower Trigger 20mm "OR" 40mm (Cleared by LHCF_ECR)
//      [7]  : Shower Trg. of 20mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [8]  : Shower Trg. of 40mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [9]  : L2TA (Cleared by LHCF_ECR)
//      [10] : L2TP (Cleared by LHCF_ECR)
//      [11] : L2T_EXT (Cleared by LHCF_ECR)
//      [12] : L2T_L1T (Cleared by LHCF_ECR)
//      [13] : L3T (Cleared by LHCF_ECR)
//      [14] : no use
//      [15] : 40MHz Clock (Cleared by LHCF_ECR)
//      [16] : ORBIT  (Cleared by LHCF_ECR)
//      [17] : ATLAS L1A (Cleared by LHCF_ECR)
//      [18] : Arm1 L3T (Cleared by LHCF_ECR)
//      [19] : Arm2 L3T (Cleared by LHCF_ECR)
//      [20] : Arm1 L3T "OR" Arm2 L3T (Global Event Number) (Cleared by LHCF_ECR)
//      [21] : Shower Trg. of Arm1 "OR" Arm2 (Cleared by LHCF_ECR)
//      [22] : Shower Trg. of Arm1 "AND" Arm2 (Cleared by LHCF_ECR)
//      [23] : 40MHz Clock  (Cleared by ORBIT)
//      [24] : BPTX1 (Cleared by ORBIT)
//      [25] : BPTX2 (Cleared by ORBIT)
//      [26] : 40MHz  (Cleared by ATLAS_ECR)
//      [27] : ATLAS L1A  (Cleared by ATLAS_ECR)
//      [28] : Selected Front Counter signal (0) (Cleared by LHCF_ECR)
//      [29] : Selected Front Counter signal (1) (Cleared by LHCF_ECR)
//      [30] : Selected Front Counter signal (2) (Cleared by LHCF_ECR)
//      [31] : Selected Front Counter signal (3) (Cleared by LHCF_ECR)
//      [32] : Selected singal (0) (Cleared by LHCF_ECR)
//      [33] : Selected singal (1) (Cleared by LHCF_ECR)
//      [34] : Selected singal (2) (Cleared by LHCF_ECR)
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int fifocounter[2][4] [channel][hit]
//     Counter value of FIFO Counter in LHCFCOUNTER
//     For detail, please refer the manual of LHCFCOUNTER
//
//
//
// =========================================================================
// DATA FORMAT: For RHICf Operation In 2017 
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    = number
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - bool   flag_beam  (Beam Flag picked up from GPIO Flag Register)
//  - bool   flag_pede  (Pedestal Flag picked up from GPIO Flag Register)
//  - bool   flag_laser not use
//
//  - double cal[2][16][2]  [tower][channel][range]
//     ADC values for the sampling layers. 
//     CAEN V965 -> Dual range Narrow range ADC value(NRADC), Wide range ADC value (WRADC) 
//      tower: 0=20mm,1=40mm
//      channel: 0-15
//      range: 0=LowRange(0.025pC/count), 1=HighRange(0.20pC/count)
//
//  - double cald[2][16][2]  [tower][channel][range]
//     ADC values of delayed gate. The delayed gate is generated about 10usec
//     after the normal gate. It is useful for pedestal subtraction event by event.
//     However you must check if no accidental signals in the values.
//
//  - double fc[2][4]  [arm][channel]
//     ADC values of Front Counter.
//      arm: only 0 is used. 
//      [0][0] : WRADC value of small tower.
//      [0][1] : NRADC value of small tower.
//      [0][2] : WRADC value of large tower.
//      [0][3] : NRADC value of large tower.
//
//  - double fcd[2][4]  [arm][channel]
//     ADC values of delayed gate for front counter.
//
//  - double laser[2]  [channel]
//     ADC values of LED Monitor PMT
//      [0]:   WRADC value of Monitor PMT
//      [1]:   NRADC value of Monitor PMT   
//
//  - double laserd[2]  [channel]
//     ADC values of delayed gate for Laser Monitor PMTs
//      [0],[1] : For WRADC,NRADC respectively.
//
//  - double emptyadc[8]  [channel]
//     not used
//
//  - double scifi0[4][2][20]   [layer][xy][fiber]
//     ADC values of SciFi in the 20mm caliorimeter.
//      layer: 0-3
//      xy:    0="X",1="Y"
//      fiber: 0-19
//
//  - double scifi1[4][2][40]   [layer][xy][fiber]
//     ADC values of SciFi in the 40mm caliorimeter.
//
//  - double tdc0[12][16]       [channel][hit]
//     TDC value (sec)
//      channel: 0-11
//      hit:     0-15  if only have #hit, value of >#hit are 0.
//    Channel List:
//     [0]  :  Bunch Clock ( 
//     [1]  :  L3T 
//     [2]  :  -
//     [3]  :  -
//     [4]  :  Shower Trigger 
//     [5]  :  STAR Trigger 
//     [6]  :  - 
//     [7]  :  -
//     [8]  :  20mm Discriminator OR
//     [9]  :  40mm Discriminator OR
//     [10] :  ADC Gate1 
//     [11] :  ADC Gate2
//
//  - char   tdc0flag[12][16]   [channel][hit]
//     Flag for each hit.
//      if no hit, -1 is filled.
//      bit 0x1 means phase of the hit.
//      bit 0x2 means valid/invalid flag.
//
//  - double  scl0[16]  [channel]
//     Not used in RHICf
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of RHICF_LOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of RHICF_GPIO
//     For detail, please refer the manual of RHICF_LOGIC and RHICF_GPIO
//
//  - unsigned int counter[35]
//     Counter values of GPIOs
//      [0-20]  Counter values in RHICF_LOGIC
//      [21-28] Counter values in RHICF_GPIO
//     Counter list (for LHCFLOGIC_V2.5 and LHCFCOUNTER_V2.5)
//      [0]  : Clock (5xBC)  (Cleared by ECR)
//      [1]  : Clock (Cascade from [1])
//      [2]  : L1T  (Cleared by ECR)
//      [3]  : L1T (Cascade from [2]) 
//      [4]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cleared by ECR)
//      [5]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cascade from [4]) 
//      [6]  : Shower Trigger of 20mm cal. (Cleared by ECR)
//      [7]  : Shower Trigger of 40mm cal. (Cleared by ECR)
//      [8]  : Shower Trg. of 20mm cal. without coincidence with L1T (Cleared by ECR)
//      [9]  : Shower Trg. of 40mm cal. without coincidence with L1T (Cleared by ECR)
//      [10] : TRG_SHOWER            (Cleared by ECR)
//      [11] : L2T_SHOWER w/o ENABLE (Cleared by ECR)
//      [12] : L2T_SHOWER            (Cleared by ECR)
//      [13] : TRG_PEDESAL           (Cleared by ECR)
//      [14] : TRG_SPECIAL1          (Cleared by ECR)
//      [15] : L2T_SPECIAL1          (Cleared by ECR)
//      [16] : TRG_SPECIAL2          (Cleared by ECR)
//      [17] : L2T_SPECIAL2          (Cleared by ECR)
//      [18] : -
//      [19] : L3T (Cleared by LHCF_ECR)
//      [20] : -
//      [21] : Bunch Clock  (Cleared by ECR)
//      [22] : Bunch Clock  (Cascade from [21]) 
//      [23] : L3T (Cleared by LHCF_ECR)
//      [24] : Bunch Clock  (Cleared by STAR ECR)
//      [25] : Bunch Clock  (Cascade from [24]) 
//      [26] : STAR TRIGGER (Cleared by STAR ECR) 
//      [27] : BCID
//      The others : -
//
//  - unsigned int fifocounter[2][4] [channel][hit]
//     Counter value of FIFO Counter in  RHICF_GPIO
//     For detail, please refer the manual of  RHICF_GPIO
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  21 Apr. 09: "enum bank" added by H.MENJO
//  30 Oct. 09: Added laserd and fcd by H.MENJO
//              and inclesed the version number 1->2.
//  12 Jan. 10: Added the functions, "pow" and "sqrt" 
//  14 Jan. 10: Fixed bugs in add, subtract ..., 
//              it affect for only fcd and laserd 
//  23 Feb. 10: Added functions for flags by H.MENJO
//--------------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(A1Cal1);
#endif

#include <math.h>

// ***********************************************************
// ***  A1Cal1::clear()  *************************************
// ***********************************************************
int A1Cal1::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  CAL,CALD,FC,FCD,LASER,LASERD,EMPTYADC,SCIFI0,SCIFI1,
  //  TDC0,TDC0FLAG,SCL0,FLAG,COUNTER,FIFOCOUNTER,
  // 
  // exp.  clear(A1Cal::CAL & A1Cal::SCIFI0);

  run     = 0;
  number  = 0;
  gnumber = 0;
  time[0] = 0;
  time[1] = 0;
  flag_beam  = false;
  flag_pede  = false;
  flag_laser = false;
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){ 
	for(int ir=0;ir<2;ir++){
	  cal[it][il][ir] = 0.0;
	}
      }
    }
  }
  
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){ 
	for(int ir=0;ir<2;ir++){
	  cald[it][il][ir] = 0.0;
	}
      }
    }
  }
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)	 fc[it][il]  = 0.;
	if(option & FCD) fcd[it][il] = 0.;
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ laser[i]  = 0.;}
  if(option & LASERD)   for(int i=0;i<2;i++){ laserd[i] = 0.;}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ emptyadc[i] = 0.;}

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  scifi0[il][ixy][ich] = 0.;
	}
      }
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  scifi1[il][ixy][ich] = 0.;
	}
      }
    }
  }

  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     tdc0[ich][ihit] = 0.;
      if(option & TDC0FLAG) tdc0flag[ich][ihit] = -1;
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ scl0[i] = 0.;}

  if(option & FLAG)    for(int i=0;i<3 ;i++) {flag[i]=0;}
  if(option & COUNTER) for(int i=0;i<35;i++) {counter[i]=0;}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	fifocounter[ich][ib]=0;
      }
    } 
  }

  return OK;
}

// ***********************************************************
// ***  A1Cal1::copy     *************************************
// ***********************************************************
int A1Cal1::copy(A1Cal1* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A1Cal1::copydata     *********************************
// ***********************************************************
int A1Cal1::copydata(A1Cal1* d, bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)

  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber; 
  this->time[0] = d->time[0];
  this->time[1] = d->time[1];
  this->flag_beam  = d->flag_beam;
  this->flag_pede  = d->flag_pede;
  this->flag_laser = d->flag_laser;
  
  if(option & CAL) {
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  = d->cal[it][il][ir];
	}
      }
    }
  } 
  
  if(option & CALD) {
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] = d->cald[it][il][ir];
	}
      }
    }
  }
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC) { this->fc[it][il]  = d->fc[it][il]; }
	if(option & FCD){ this->fcd[it][il] = d->fcd[it][il]; }
      }
    }
  }

  if(option & LASER)   {for(int i=0;i<2;i++){ this->laser[i]  = d->laser[i];}}
  if(option & LASERD)  {for(int i=0;i<2;i++){ this->laserd[i] = d->laserd[i];}}
  if(option & EMPTYADC){for(int i=0;i<8;i++){ this->emptyadc[i] = d->emptyadc[i];}}

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  this->scifi0[il][ixy][ich] = d->scifi0[il][ixy][ich];
	}
      }
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] = d->scifi1[il][ixy][ich];
	}
      }
    }
  }
 
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     this->tdc0[ich][ihit] = d->tdc0[ich][ihit];
      if(option & TDC0FLAG) this->tdc0flag[ich][ihit] = d->tdc0flag[ich][ihit];
    }
  } 
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] = d->scl0[i];}

  if(option & FLAG)    for(int i=0;i<3 ;i++) {this->flag[i]=d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {this->counter[i]=d->counter[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]=d->fifocounter[ich][ib];
      }
    } 
  }
  
  return OK;
}

// ***********************************************************
// ***  A1Cal1::add      *************************************
// ***********************************************************
int A1Cal1::add(A1Cal1* d, bankio option){
  // Add data of "d" to this
  // (default option:0x1FF)

  if(option & CAL) {
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  += d->cal[it][il][ir];
	}
      }
    }  
  }

  if(option & CALD) {
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	this->cald[it][il][ir] += d->cald[it][il][ir];
	}
      }
    }  
  }


  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  += d->fc[it][il];
	if(option & FCD) this->fcd[it][il] += d->fcd[it][il];	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i]  += d->laser[i];}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] += d->laserd[i];}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] += d->emptyadc[i];}

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){ 
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  this->scifi0[il][ixy][ich] += d->scifi0[il][ixy][ich];
	}
      }  
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] += d->scifi1[il][ixy][ich];
	}
      }
    }
  }

  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     this->tdc0[ich][ihit] = d->tdc0[ich][ihit];
      //if(option & TDC0FLAG) this->tdc0flag[ich][ihit] = d->tdc0flag[ich][ihit];
    }
  }

  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] = d->scl0[i];}

  //if(option & FLAG)    for(int i=0;i<3 ;i++) {this->flag[i]+=d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {this->counter[i]+=d->flag[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
        this->fifocounter[ich][ib]+=d->fifocounter[ich][ib];
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A1Cal1::subtract   ***********************************
// ***********************************************************
int A1Cal1::subtract(A1Cal1* d, bankio option){
  // Subtract data of "d" from this
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  -= d->cal[it][il][ir];
	}
      }
    }  
  }

  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] -= d->cald[it][il][ir];
	}
      }
    }  
  }

  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  -= d->fc[it][il];
	if(option & FCD) this->fcd[it][il] -= d->fcd[it][il];	
      }
    }
  }

  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] -= d->laser[i];}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] -= d->laserd[i];}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] -= d->emptyadc[i];} 

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<20;ich++){ 
	if(option & SCIFI0){
	  this->scifi0[il][ixy][ich] -= d->scifi0[il][ixy][ich];
	}
      } 
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] -= d->scifi1[il][ixy][ich];
	}
      }
    }
  }

  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     this->tdc0[ich][ihit] -= d->tdc0[ich][ihit];
      //if(option & TDC0FLAG) this->tdc0flag[ich][ihit] -= d->tdc0flag[ich][ihit];
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] -= d->scl0[i];}

  //if(option & FLAG)    for(int i=0;i<3 ;i++) {this->flag[i] -= d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {this->counter[i] -= d->counter[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib] -= d->fifocounter[ich][ib];
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A1Cal1::multiply   ***********************************
// ***********************************************************
int A1Cal1::multiply(double d, bankio option){
  // Multiply data by the given factor of "d"
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir] *= d;
	}
      }
    } 
  }  
    
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] *= d;
	}
      }
    } 
  }  
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il] *= d;
	if(option & FCD) this->fcd[it][il] *= d;	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] *= d;}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] *= d;}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] *= d;} 
  
  if( (option & SCIFI0) || (option & SCIFI0)){  
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ich=0;ich<20;ich++){
	  if(option & SCIFI0){
	    this->scifi0[il][ixy][ich] *= d;
	  }
	}
	if(option & SCIFI1){
	  for(int ich=0;ich<40;ich++){
	    this->scifi1[il][ixy][ich] *= d;
	  }
	}
      }
    }
  }

  if(option & TDC0){
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	this->tdc0[ich][ihit] *= d;
      }
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] *= d;}

  if(option & COUNTER){
    for(int i=0;i<35;i++){
      this->counter[i] = (int)(d*this->counter[i]);
    }
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]
	  = (int)(d*this->fifocounter[ich][ib]);
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A1Cal1::divide   *************************************
// ***********************************************************
int A1Cal1::divide(double d, bankio option){
  // divide by "d" (just alias multiply(1./d))
  return multiply(1./d,option);
}

// ***********************************************************
// ***  A1Cal1::pow   ****************************************
// ***********************************************************
int A1Cal1::pow(double d, bankio option){
  // calculate the d'th power of each value.
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cal[it][il][ir] = ::pow(this->cal[it][il][ir],d);
	}
      }
    } 
  }  
    
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cald[it][il][ir] = ::pow(this->cald[it][il][ir],d);
	}
      }
    } 
  }  
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)	 this->fc[it][il] = ::pow(this->fc[it][il],d);
	if(option & FCD) this->fcd[it][il] = ::pow(this->fcd[it][il],d);	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i]  = ::pow(this->laser[i],d);} 
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] = ::pow(this->laserd[i],d);}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] = ::pow(this->emptyadc[i],d);} 
  
  if( (option & SCIFI0) || (option & SCIFI0)){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ich=0;ich<20;ich++){
	  if(option & SCIFI0){
	    this->scifi0[il][ixy][ich] = ::pow(this->scifi0[il][ixy][ich],d);
	  }
	}
	if(option & SCIFI1){
	  for(int ich=0;ich<40;ich++){
	    this->scifi1[il][ixy][ich] = ::pow(this->scifi1[il][ixy][ich],d);
	  }
	}
      }
    }
  }

  if(option & TDC0){  
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	this->tdc0[ich][ihit] = ::pow(this->tdc0[ich][ihit],d);
      }
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] = ::pow(this->scl0[i],d);}

  if(option & COUNTER) for(int i=0;i<35;i++){
    this->counter[i] = (int)(::pow(this->counter[i],d));
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]
	  = (int)(::pow(this->fifocounter[ich][ib],d));
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A1Cal1::sqrt   ****************************************
// ***********************************************************
int A1Cal1::sqrt(bankio option){
  // calculate the square root of each value.
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir] = ::sqrt(this->cal[it][il][ir]);
	}
      }
    } 
  }  
    
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cald[it][il][ir] = ::sqrt(this->cald[it][il][ir]);
	}
      }
    } 
  }  
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  = ::sqrt(this->fc[it][il]);
	if(option & FCD) this->fcd[it][il] = ::sqrt(this->fcd[it][il]);
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] = ::sqrt(this->laser[i]);}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] = ::sqrt(this->laserd[i]);}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] = ::sqrt(this->emptyadc[i]);} 
  
  if( (option & SCIFI0) || (option & SCIFI0)){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int ich=0;ich<20;ich++){
	  if(option & SCIFI0){
	    this->scifi0[il][ixy][ich] = ::sqrt(this->scifi0[il][ixy][ich]);
	  }
	}
	if(option & SCIFI1){
	  for(int ich=0;ich<40;ich++){
	    this->scifi1[il][ixy][ich] = ::sqrt(this->scifi1[il][ixy][ich]);
	  }
	}
      }
    }
  }

  if(option & TDC0){  
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	this->tdc0[ich][ihit] = ::sqrt(this->tdc0[ich][ihit]);
      }
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A1_SCL0;i++){ this->scl0[i] = ::sqrt(this->scl0[i]);}

  if(option & COUNTER) for(int i=0;i<35;i++){
    this->counter[i] = (int)(::sqrt(this->counter[i]));
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]
	  = (int)(::sqrt(this->fifocounter[ich][ib]));
      }
    }
  }

  return OK;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ CONVERSION OF SCL0 VALUE                            +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double A1Cal1::clk(){
  //  scl0[1]*2^24+scl0[0]

  const int b24 = 16777216;
  return ((double)scl0[1])*b24 + scl0[0];  
}

double A1Cal1::bptx1(){
  //  scl0[3]*2^24+scl0[2]
  
  const int b24 = 16777216;
  return ((double)scl0[3])*b24 + scl0[2]; 
}

double A1Cal1::bptx2(){
  //  scl0[5]*2^24+scl0[4]

  const int b24 = 16777216;
  return ((double)scl0[5])*b24 + scl0[4]; 
}

#endif
