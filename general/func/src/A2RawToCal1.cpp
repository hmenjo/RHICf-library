#ifndef __A2RAW2CAL1_CPP__
#define __A2RAW2CAL1_CPP__

#include "A2RawToCal1.h"

//----------------------------------------------------------------------
//                                              
//  This class can convert data with A2Raw format to data with
//  A1Cal2 format. This class needs a table for Silicon
//  table to convert Silicon raw format to meaningful array.
//  But the convertion for the silicon data is not implemented yet.
//
//  Example for convertion from A2Raw to A2Cal1.
//   A2RawToCal1 *a2conv = new A2RawToCal1();
//   A2Cal1 *a2cal1 = new A2Cal1("a2cal1","");
//   for(i;i<nevent;i++){
//     a2conv->Convert(a2raw,a2cal1);
//   }
//
//  About Format 
//    There are three formats of the conversion, FORMAT_OP2010,FORMAT_OP2009 and FORMAT_SPS2010.
//    The defference between these formats is just for FC adc. 
//     in OP2009
//         ADC valuse of Arm2 FCs are filled in ADC4 ch4-7
//         No ADC data of Arm2 FCs.
//     in OP2010
//         ADC valuse of Arm1 FCs are filled in ADC3 ch0-3
//         ADC valuse of Arm2 FCs are filled in ADC3 ch4-7
//
//    To convert event data with OP2009, there are two way.
//        - call Convert_OP2009() instead of simple Convert() function.
//        - call SerFormatOp2009() once before the conversion, then call Convert().
//    if you call Convert() without call of SerFormat***(), 
//    automatically the conversion format is selected by using valuse of ADC3. 
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  20 Apr. 09: Fuction "InverseConvert" was added by H.MENJO.
//              This function can convert  A2Cal1 to A2Raw. But,
//              Conversion for TDC and Silicon data is not implemented yet.
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//  05 Feb. 10: Defined format to convert data in 2009 and 2010 by this class.
//  19 Oct. 10: Defined the format convertion for the beam test data in 2010
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2RawToCal1);
#endif

#include "feparam_arm2.h"

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

A2RawToCal1::A2RawToCal1(){
  Initialize();
}

int A2RawToCal1::Initialize(){
  format = FORMAT_AUTO;
  return OK;
}

// ***********************************************************
// ***  A2Raw::Convert     ***********************************
// ***********************************************************
int A2RawToCal1::Convert(TObject* raw_input, A2Cal1* cal1){
  // Convert A2Raw to A2Cal1.
  // There are three data formats of A2Raw, OP2009, OP2010 and SPS2010. 
  // if you call SerFormatOp2009() before call this function, data is converted by Convert_OP2009.
  // if you call SerFormatOp2010() before call this function, data is converted by Convert_OP2010.
  // Otherwize this function automatically selects the conversion format.
  
  if(strcmp(raw_input->ClassName(),"A2Raw")==0){
    static int tmpformat = -1;
    if(format==FORMAT_AUTO){
      // FOR SPS2010 
      // In the beam test in 2010, only ADC2 in ADC2,3,4 was used.
      // So all values of ADC3,4 are filled to 0.
      A2Raw *raw = (A2Raw*)raw_input;
      if(raw->adc4[0] < 0.1 && raw->adc4[2] < 0.1 && 
	 raw->adc4[4] < 0.1 && raw->adc4[6] < 0.1 &&
	 raw->adc3[0] < 0.1 && raw->adc3[2] < 0.1 && 
	 raw->adc3[4] < 0.1 && raw->adc3[6] < 0.1 ){
	if(tmpformat < 0){ tmpformat=FORMAT_SPS2010 ;}
	else {
	  if(tmpformat!=FORMAT_SPS2010){
	    cerr << "[A2RawToCal1::Convert] " 
		 << "WARNING: Data format was changed from " 
		 << tmpformat << " to " << FORMAT_SPS2010 << endl;
	    tmpformat = FORMAT_SPS2010;
	  }
	}
	return Convert_SPS2010((A2Raw*)raw_input,cal1);
      }
      // FOR OP2010 
      if(raw->adc3[0] > 0.1 || raw->adc3[2] > 0.1 || 
	 raw->adc3[4] > 0.1 || raw->adc3[6] > 0.1 ){
	if(tmpformat < 0){ tmpformat=FORMAT_OP2010 ;}
	else {
	  if(tmpformat!=FORMAT_OP2010){
	    cerr << "[A2RawToCal1::Convert] " 
		 << "WARNING: Data format was changed from " 
		 << tmpformat << " to " << FORMAT_OP2010 << endl;
	    tmpformat = FORMAT_OP2010;
	  }
	}
	return Convert_OP2010((A2Raw*)raw_input,cal1);
      }
      // FOR OP2009  
      // In the beam test in 2010, only ADC2 in ADC2,3,4 was used.
      // So all values of ADC3,4 are filled to 0.
      else{ 
	if(tmpformat < 0){ tmpformat=FORMAT_OP2009 ;}
	else {
	  if(tmpformat!=FORMAT_OP2009){
	    cerr << "[A2RawToCal1::Convert] " 
		 << "WARNING: Data format was changed from " 
		 << tmpformat << " to " << FORMAT_OP2009 << endl;
	    tmpformat = FORMAT_OP2009;
	  }
	}
	return Convert_OP2009((A2Raw*)raw_input,cal1);
      }
    }
    else if(format==FORMAT_OP2010){return Convert_OP2010((A2Raw*)raw_input,cal1);}
    else if(format==FORMAT_OP2009){return Convert_OP2009((A2Raw*)raw_input,cal1);}
    else{
      cerr << "[A2RawToCal1::Convert] " 
	   << "ERROR: Invalid format : " << format << endl;
      return ERROR;
    }
  }
  // ==============================================================
  // For the format of p-Pb 2013 
  else if(strcmp(raw_input->ClassName(),"A2Raw_pPb2013")==0){
    return Convert_pPb2013((A2Raw_pPb2013*)raw_input,cal1);
  }
  // ==============================================================
  // For the format for 2015 Operation  
  else if(strcmp(raw_input->ClassName(),"A2Raw_pp2015")==0){
    return Convert_OP2015((A2Raw_pp2015*)raw_input,cal1);
  }
  // ==============================================================
  // For the format for 2016 Operation  
  else if(strcmp(raw_input->ClassName(),"A2Raw_pPb2016")==0){
    return Convert_pPb2016((A2Raw_pPb2016*)raw_input,cal1);
  } else {
    cerr << "[A2RawToCal1::Convert] Error : Unknow Class " << raw_input->ClassName() << endl; 
    return ERROR; 
  }
}

// ************************** Convert_OP2009 ***********************
int A2RawToCal1::Convert_OP2009(A2Raw* raw, A2Cal1* cal1){
  // Convert data token in 2009
  
  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1];
  cal1->flag_beam  = (raw->gpio0[0] >> 12) & 0x1;
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_laser = (raw->gpio0[0] >> 14) & 0x1;

  // ************   For ADCs    ***********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }
  
  // ************  For the Other ADCs ******************

  for(int ie=0;ie<8;ie++) {
    cal1->emptyadc[ie] = raw->adc2[ie];
  }

  for(int ich=0;ich<4;ich++){
    cal1->fc[0][ich]  = raw->adc4[ 4+ich];
    cal1->fcd[0][ich] = raw->adc4[12+ich]; 
  }
  
  for(int ir=0;ir<2;ir++){
    cal1->laser[ir]  = raw->adc4[ir];
    cal1->laserd[ir] = raw->adc4[ir+8];
  }
  
  // ************   For TDC   **************************
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<N_A2_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	cerr << "[A2RawToCal1::Convert] Warning: TDC channel is >= 12;"
           << tmpchannel << endl;
      }
      else {
	if(nhit[tmpchannel]>=16){
	  cerr << "[A2RawToCal1::Convert] Warning: "
	       << "#hits of TDC["<< tmpchannel<<"] is over 16." << endl;
	}   
	else{
	  cal1->tdc0[tmpchannel][nhit[tmpchannel]] = tmpvalue*0.025;
	  cal1->tdc0flag[tmpchannel][nhit[tmpchannel]] = 0x1*tmpphase;
	  nhit[tmpchannel]++;
	}
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==N_A2_TDC0){
      cerr << "[A2RawToCal1::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (128)" << endl;
    }
  }
  
  
  // ************   For SCL   **************************
  for(int i=0;i<N_A2_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  //  ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio1[0];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<=14;ich++){
    cal1->counter[ich] = raw->gpio0[ch_gpio0];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<=34;ich++){
    if(ch_gpio1==9){
      cal1->counter[ich] = raw->gpio1[ch_gpio1] & 0xFFFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 16) & 0xFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 24) & 0xFF;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  } 
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      cal1->fifocounter[ififo][ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }

  return OK;
}

// ************************** Convert_OP2010 ***********************
int A2RawToCal1::Convert_OP2010(A2Raw* raw, A2Cal1* cal1){
  // Convert data token in 2010 and later
  
  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1];
  cal1->flag_beam  = (raw->gpio0[0] >> 12) & 0x1;
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_laser = (raw->gpio0[0] >> 14) & 0x1;

  // ************   For ADCs    ***********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }
  
  // ************  For the Other ADCs ******************

  for(int ie=0;ie<8;ie++) {
    cal1->emptyadc[ie] = raw->adc2[ie];
  }

  // FC
  for(int ich=0;ich<4;ich++){
    // Arm1 FC
    cal1->fc[0][ich]  = raw->adc3[ ich];
    cal1->fcd[0][ich] = raw->adc3[ ich+8];
    // Arm2 FC
    cal1->fc[1][ich]  = raw->adc3[ ich+4];
    cal1->fcd[1][ich] = raw->adc3[ ich+12]; 
  }
  
  for(int ir=0;ir<2;ir++){
    cal1->laser[ir]  = raw->adc4[ir];
    cal1->laserd[ir] = raw->adc4[ir+8];
  }
  
  // ************   For TDC   **************************
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<N_A2_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	cerr << "[A2RawToCal1::Convert] Warning: TDC channel is >= 12;"
           << tmpchannel << endl;
      }
      else {
	if(nhit[tmpchannel]>=16){
	  cerr << "[A2RawToCal1::Convert] Warning: "
	       << "#hits of TDC["<< tmpchannel<<"] is over 16." << endl;
	}   
	else{
	  cal1->tdc0[tmpchannel][nhit[tmpchannel]] = tmpvalue*0.025;
	  cal1->tdc0flag[tmpchannel][nhit[tmpchannel]] = 0x1*tmpphase;
	  nhit[tmpchannel]++;
	}
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==N_A2_TDC0){
      cerr << "[A2RawToCal1::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (128)" << endl;
    }
  }
  
  
  // ************   For SCL   **************************
  for(int i=0;i<N_A2_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  //  ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio1[0];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<15;ich++){
    cal1->counter[ich] = raw->gpio0[ch_gpio0];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      cal1->counter[ich] = raw->gpio1[ch_gpio1] & 0xFFFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 16) & 0xFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 24) & 0xFF;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  } 
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      cal1->fifocounter[ififo][ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }

  return OK;
}

// **********************************************************
// **** CONVERSION FOR SPS2010 ******************************
// **********************************************************
int A2RawToCal1::Convert_SPS2010(A2Raw* raw, A2Cal1* cal1){
  // Convert data token in 2010 and later
  
  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1]; 
  // Always the hardware beam flag is ON. 
  // So the only pedestal flag is useful for identification of 
  // beam and pedestal events. 
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_beam  = cal1->flag_pede==1 ? 0 : 1 ;
  cal1->flag_laser = (raw->gpio0[0] >> 14) & 0x1;

  // ************   For ADCs    ***********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }
  
  // ************  For the Other ADCs ******************

  for(int ie=0;ie<4;ie++) {
    cal1->emptyadc[ie] = raw->adc2[ie];
  }

  // For FC
  // only Arm1 FC values with normal gate are available. 
  // (no values of delayed gate)
  for(int ich=0;ich<4;ich++) {
    cal1->fc[1][ich] = raw->adc2[ich+4];
  }
  
  // ************   For TDC   **************************
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<N_A2_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	cerr << "[A2RawToCal1::Convert] Warning: TDC channel is >= 12;"
           << tmpchannel << endl;
      }
      else {
	if(nhit[tmpchannel]>=16){
	  cerr << "[A2RawToCal1::Convert] Warning: "
	       << "#hits of TDC["<< tmpchannel<<"] is over 16." << endl;
	}   
	else{
	  cal1->tdc0[tmpchannel][nhit[tmpchannel]] = tmpvalue*0.025;
	  cal1->tdc0flag[tmpchannel][nhit[tmpchannel]] = 0x1*tmpphase;
	  nhit[tmpchannel]++;
	}
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==N_A2_TDC0){
      cerr << "[A2RawToCal1::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (128)" << endl;
    }
  }
  
  
  // ************   For SCL   **************************
  for(int i=0;i<N_A2_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  //  ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio1[0];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<15;ich++){
    cal1->counter[ich] = raw->gpio0[ch_gpio0];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      cal1->counter[ich] = raw->gpio1[ch_gpio1] & 0xFFFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 16) & 0xFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 24) & 0xFF;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  } 
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      cal1->fifocounter[ififo][ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }

  return OK;
}

// ***********************************************************
// *** A2RawToCal1::Convert_pPb2013    ***********************
// ***********************************************************
int A2RawToCal1::Convert_pPb2013(A2Raw_pPb2013* raw, A2Cal1* cal1){
  // Format conversion from A2Raw_pPb2013 to A2Cal1.
  // Mostly same as the A2Raw::Convert_OP2010 but some parts 
  // has been modified for p-Pb operation.
  // Because to keep same array in A2Cal1, the following values are not filled 
  // into A2Cal1,
  //      fc      : Filled only high range values 
  //      laser   : Filled only high range values
  //      emptyadc: Filled only low range values 
  //      tdc0    : Filled only hits in the range of [L3T-2usec, L3T+1usec] 
  // 

  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1];
  cal1->flag_beam  = (raw->gpio0[0] >> 12) & 0x1;
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_laser = (raw->gpio0[0] >> 14) & 0x1;
  
  // ************   For ADCs    ***********************
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      int tmpch;
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }

  // Arm2 FC
  // To keeping same array of A2Cal1, only the high range values 
  // are filled to A2Cal2
  // FC(0) : ch.0 of ADC2 
  // FC(1) : ch.1 of ADC2
  // FC(2) : ch.2 of ADC2
  // FC(3) : ch.3 of ADC2 

  for(int ich=0;ich<4;ich++){
    int tmpch = ich*2;
    cal1->fc[1][ich]  = raw->adc2[tmpch];
    tmpch = ich*2 + 32;
    cal1->fcd[1][ich] = raw->adc2[tmpch]; 
  }

  // Laser
  // To keeping same array of A2Cal1, only the high range values 
  // are filled to A2Cal2
  // Laser Monitor PMT R : ch 6 of ADC2
  // Laser Monitor PMT L : ch 7 of ADC2
  cal1->laser[0]  = raw->adc2[6*2];
  cal1->laser[1]  = raw->adc2[7*2];
  cal1->laserd[0] = raw->adc2[32+6*2];
  cal1->laserd[1] = raw->adc2[32+7*2];

  // For Noise
  // To keeping same array of A2Cal1, only the low range values 
  // are filled to A2Cal2
  // The input channels are ch.8,9 and 10 of ADC2 
  cal1->emptyadc[0] = raw->adc2[2*8];
  cal1->emptyadc[1] = raw->adc2[2*9];
  cal1->emptyadc[2] = raw->adc2[2*10];

  // ************   For TDC   **************************
  // Because the limitation of number of values in a array, the window for each channels are 
  // applied as software cut. 
  // ch0 CLK with 100nsec mask    :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch1 L3T                      :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch2 BPTX1                    :   [L3T-2usec, L3T+1usec]
  // ch3 BPTX2                    :   [L3T-2usec, L3T+1usec]
  // ch4 Shower Trigger           :   [L3T-2usec, L3T+1usec]
  // ch5 ATLAS L1A                :   [L3T-2usec, L3T+1usec]
  // ch6 -                        :   No mask
  // ch7 Arm2 FC Logic OR         :   [L3T-2usec, L3T+1usec]
  // ch8 25mm Discriminator OR    :   [L3T-2usec, L3T+1usec]  
  // ch9 32mm Discriminator OR    :   [L3T-2usec, L3T+1usec] 
  // ch10 -                       :   No mask
  // ch11 -                       :   No mask
  const int L3T_channel = 1; 
  double L3T_value = 0.;
  vector<double> tmptdc0[12];
  vector<char>   tmptdc0flag[12];
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel = 0;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<A2Raw_pPb2013::c_N_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader    = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue   = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase   = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	cerr << "[A2RawToCal1_pPb2012::Convert] Warning: The number of TDC channels is >= 12;"
           << tmpchannel << endl;
      }
      else {
	tmptdc0[tmpchannel].push_back(tmpvalue*0.025);
	tmptdc0flag[tmpchannel].push_back(0x1*tmpphase);
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==A2Raw_pPb2013::c_N_TDC0){
      cerr << "[A2RawToCal1_pPb2012::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (256)" << endl;
    }
    
  }
  
  // Check of number of hits of L3T and Set base value (L3T_value)
  if(tmptdc0[L3T_channel].size()==1){
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()>1){
    cerr << "[A2RawToCal1_pPb2012::Convert] Warning: " 
	 << "TDC ch1 (L3T) has more than one hit " << tmptdc0[L3T_channel].size()
	 << endl;
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()==0){
    cerr << "[A2RawToCal1_pPb2012::Convert] Warning: " 
	 << "TDC ch1 (L3T) has no hit " 
	 << endl;
    L3T_value = 9200;   
  }

  // Fill with the window
  for(int ich=0;ich<12;ich++){
    for(int i=0;i<(int)tmptdc0[ich].size();i++){
      // check the signal is in the window or not.
      // The window is [L3T-2usec, L3T+1usec]
      if(tmptdc0[ich][i] < L3T_value-2000 || tmptdc0[ich][i] > L3T_value+1000){
	continue;
      }
      
      if(nhit[ich]>=16){
	cerr << "[A2RawToCal1_pPb2012::Convert] Warning: "
	     << "#hits of TDC["<< ich <<"] is over 16." << endl;
      }
      else{
	cal1->tdc0[ich][nhit[ich]]     = tmptdc0[ich][i];
	cal1->tdc0flag[ich][nhit[ich]] = tmptdc0flag[ich][i];
	nhit[ich]++;
      }
    }
  }
  

  // ************   For SCL   **************************
  for(int i=0;i<A2Raw_pPb2013::c_N_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  //  ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio1[0];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<35;ich++){
    cal1->counter[ich] = raw->gpio0[ch_gpio0];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      cal1->counter[ich] = raw->gpio1[ch_gpio1] & 0xFFFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 16) & 0xFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 24) & 0xFF;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  } 
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      cal1->fifocounter[ififo][ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }

  return OK;
}

// ***********************************************************
// *** A2RawToCal1::Convert_OP2015    ***********************
// ***********************************************************
int A2RawToCal1::Convert_OP2015(A2Raw_pp2015* raw, A2Cal1* cal1){
  // Format conversion from A2Raw_pp2015 to A2Cal1.
  // This is mostly same as the Convert_pPb2013 but some parts 
  // has been modified for 2015 operation.
  // Because to keep same array in A2Cal1, the following values are not filled 
  // into A2Cal1,
  //      fc      : Filled only high range values 
  //      laser   : Filled only high range values
  //      emptyadc: Filled only low range values 
  //      tdc0    : Filled only hits in the range of [L3T-2usec, L3T+1usec] 
  // The GPIO outputs, flag, counters and fifo counter, were fully modified in 2015. 

  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1];

  cal1->flag_beam  = (raw->gpio0[0] >> 12) & 0x1;
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_laser = 0; // No laser flag in 2015

  // ************   For ADCs    ***********************
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      int tmpch;
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }
  
  // ************ ADC's For FC ***********
  // CAEN V965 Module is used for data taking.
  // Becase two values from the durl range ADC is not fitted to the A1Cal1 format. 
  // Only the HRADC (wide range ADC) values are filled into the class 
  for(int ich=0;ich<4;ich++){
    cal1->fc[0][ich] = raw->adc2[8+ich*2];  // For Arm1
    cal1->fc[1][ich] = raw->adc2[ich*2]; // For Arm2 
  }

  // **** ADC's For Laser Monitors *****
  // Laser Monitor in the laser box 
  cal1->laser[0] = raw->adc3[0];
  cal1->laser[1] = raw->adc3[1];
  cal1->laserd[0] = raw->adc3[2];
  cal1->laserd[1] = raw->adc3[3];

  // Laser Monitor in the detector
  // This is the monitor newly installed in 2015 operation.
  // No variable fitted to the value is available. 
  // So the values fill into the emptyadc array 
  cal1->emptyadc[0] = raw->adc2[17]; //  LRADC 
  cal1->emptyadc[1] = raw->adc2[19]; //  LRADC  delayed gate
  cal1->emptyadc[2] = raw->adc2[16]; //  HRADC 
  cal1->emptyadc[3] = raw->adc2[18]; //  HRADC  delayed gate
    
  // ************  For the Other ADCs ******************
  // ??

  // ************   For TDC   **************************
  // Because the limitation of number of values in a array, the window for each channels are 
  // applied as software cut. 
  // ch0 CLK with 100nsec mask    :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch1 L3T                      :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch2 BPTX1                    :   [L3T-2usec, L3T+1usec]
  // ch3 BPTX2                    :   [L3T-2usec, L3T+1usec]
  // ch4 Shower Trigger           :   [L3T-2usec, L3T+1usec]
  // ch5 ATLAS L1A                :   [L3T-2usec, L3T+1usec]
  // ch6 -                        :   No mask
  // ch7 Arm2 FC Logic OR         :   [L3T-2usec, L3T+1usec]
  // ch8 25mm Discriminator OR    :   [L3T-2usec, L3T+1usec]  
  // ch9 32mm Discriminator OR    :   [L3T-2usec, L3T+1usec] 
  // ch10 -                       :   No mask
  // ch11 -                       :   No mask
  const int L3T_channel = 1; 
  double L3T_value = 0.;
  vector<double> tmptdc0[12];
  vector<char>   tmptdc0flag[12];
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel = 0;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<A2Raw_pp2015::c_N_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader    = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue   = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase   = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	cerr << "[A2RawToCal1::Convert_OP2015] Warning: The number of TDC channels is >= 12;"
           << tmpchannel << endl;
      }
      else {
	tmptdc0[tmpchannel].push_back(tmpvalue*0.025);
	tmptdc0flag[tmpchannel].push_back(0x1*tmpphase);
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==A2Raw_pp2015::c_N_TDC0){
      cerr << "[A2RawToCal1_pp2015::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (256)" << endl;
    }
    
  }
  
  // Check of number of hits of L3T and Set base value (L3T_value)
  if(tmptdc0[L3T_channel].size()==1){
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()>1){
    cerr << "[A2RawToCal1::Convert_OP2015] Warning: " 
	 << "TDC ch1 (L3T) has more than one hit " << tmptdc0[L3T_channel].size()
	 << endl;
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()==0){
    cerr << "[A2RawToCal1::Convert_OP2015] Warning: " 
	 << "TDC ch1 (L3T) has no hit " 
	 << endl; 
    L3T_value = 9200;   
  }

  // Fill with the window
  for(int ich=0;ich<12;ich++){
    for(int i=0;i<(int)tmptdc0[ich].size();i++){
      // check the signal is in the window or not.
      // The window is [L3T-2usec, L3T+1usec]
      if(tmptdc0[ich][i] < L3T_value-2000 || tmptdc0[ich][i] > L3T_value+1000){
	continue;
      }
      
      if(nhit[ich]>=16){
	cerr << "[A2RawToCal1::Convert_OP2015] Warning: "
	     << "#hits of TDC["<< ich <<"] is over 16." << endl;
      }
      else{
	cal1->tdc0[ich][nhit[ich]]     = tmptdc0[ich][i];
	cal1->tdc0flag[ich][nhit[ich]] = tmptdc0flag[ich][i];
	nhit[ich]++;
      }
    }
  }
  

  // ************   For SCL   **************************
  for(int i=0;i<A2Raw_pp2015::c_N_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  // ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio0[2];
  
  unsigned int *val = &(raw->gpio0[0]);
  cal1->counter[0]  = CounterFilter(val[3],32);     // CLK
  cal1->counter[1]  = CounterFilter(val[4],32);     // BPTX1
  cal1->counter[2]  = CounterFilter(val[5],32);     // BPTX2
  cal1->counter[3]  = CounterFilter(val[6],32);     // BPTX_AND
  cal1->counter[4]  = CounterFilter(val[7],24);     // ORBIT
  cal1->counter[5]  = CounterFilter(val[8],32);     // L1T
  cal1->counter[6]  = CounterFilter(val[9],32);     // L1T ENABLE
  cal1->counter[7]  = CounterFilter(val[10],24);    // STRG(Small Shower Trigger)
  cal1->counter[8]  = CounterFilter(val[11],24);    // LTRG(Large Shower Trigger)
  cal1->counter[9]  = CounterFilter(val[12],24);    // SLOGIC(Small Shower Logic-out)
  cal1->counter[10] = CounterCombine(&(val[10]));   // LLOGIC(Large Shower logic-out)
  cal1->counter[11] = CounterFilter(val[13],24);    // L2T_Shower_Trg 
  cal1->counter[12] = CounterFilter(val[14],24);    // L2T_Shower_BPTX 
  cal1->counter[13] = CounterFilter(val[15],24);    // L2T_Special_Trg
  cal1->counter[14] = CounterCombine(&(val[13]));   // L2T_Special_BPTX
  cal1->counter[15] = CounterFilter(val[16],16);    // L2T_SHOWER "AND" L3T
  cal1->counter[16] = CounterFilter(val[16],16,16); // L2T_SPECIAL "AND" L3T
  cal1->counter[17] = CounterFilter(val[17],16);    // L2T_PEDE "AND" L3T 
  cal1->counter[18] = CounterFilter(val[17],16,16); // L2T_L1T "AND" L3T
  cal1->counter[19] = CounterFilter(val[18],16);    // L3T
  cal1->counter[20] = CounterFilter(val[18],16,16); // L3T_A1 "OR" L3T_A2
  cal1->counter[21] = CounterFilter(val[19],32);    // !! Two Counter Values !! A1 A2 Showers "AND" / ATLAS_L1_LHCF 
  cal1->counter[22] = CounterFilter(val[20],16);    // CLK cleared by Orbit
  cal1->counter[23] = CounterFilter(val[20],8,16);  // BPTX1 cleared by Orbit
  cal1->counter[24] = CounterFilter(val[20],8,24);  // BPTX2 cleared by Orbit
  cal1->counter[25] = CounterFilter(val[21],32);    // CLK cleared by ATLAS-ECR
  cal1->counter[26] = CounterFilter(val[22],32);    // ATLAS_L1A cleared by ATLAS-ECR
  cal1->counter[27] = CounterFilter(val[23],24);    // FC(0) (A2_FC(0) or A2_FCL(0))
  cal1->counter[28] = CounterFilter(val[24],24);    // FC(1) (A2_FC(1) or A2_FCL(1))
  cal1->counter[29] = CounterFilter(val[25],24);    // FC(2) (A2_FC(2) or A2_FCL(2))
  cal1->counter[30] = CounterCombine(&(val[23]));   // FC(3) (A2_FC(3) or A2_FCL(3))
  cal1->counter[31] = CounterFilter(val[26],24);    // A2_FCL
  cal1->counter[32] = CounterFilter(val[27],24);    // A2_FC_TRG
  cal1->counter[33] = CounterFilter(val[28],24);    // A2_SHOWER_BPTX AND A1_FC_TRG 
  cal1->counter[34] = CounterCombine(&(val[26]));   // A2_FC_TRG AND A1_FC_TRG
           
  cal1->fifocounter[0][0] = val[29];
  cal1->fifocounter[0][1] = val[30];
  cal1->fifocounter[0][2] = val[31];
  cal1->fifocounter[1][0] = val[32];
  cal1->fifocounter[1][1] = val[33];
  cal1->fifocounter[1][2] = val[34];

  return OK;
}

// ***********************************************************
// *** A2RawToCal1::Convert_pPb2016    ***********************
// ***********************************************************
int A2RawToCal1::Convert_pPb2016(A2Raw_pPb2016* raw, A2Cal1* cal1){
  // Format conversion from A2Raw_pPb2016 to A2Cal1.
  // This is copied from Convert_pPb2016 but 
  // changes in DAQ Logic Flag are needed.

  cal1->clear();
  
  // ************   For Headers   ********************
  cal1->run = raw->run;
  cal1->number = raw->number;
  cal1->gnumber = raw->gnumber;
  cal1->time[0] = raw->time[0];
  cal1->time[1] = raw->time[1];
  cal1->flag_beam  = (raw->gpio0[0] >> 12) & 0x1;
  cal1->flag_pede  = (raw->gpio0[0] >> 13) & 0x1;
  cal1->flag_laser = (raw->gpio0[0] >> 14) & 0x1;

  // ************   For ADCs    ***********************
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      int tmpch;
      tmpch = il*2 + (1-ir);
      cal1->cal[0][il][ir] = raw->adc0[tmpch];
      cal1->cal[1][il][ir] = raw->adc1[tmpch];
      tmpch = 32 + il*2 + (1-ir);
      cal1->cald[0][il][ir] = raw->adc0[tmpch];
      cal1->cald[1][il][ir] = raw->adc1[tmpch];
    }
  }

  // Arm2 FC
  // To keeping same array of A2Cal1, only the high range values 
  // are filled to A2Cal2
  // FC(0) : ch.0 of ADC2 
  // FC(1) : ch.1 of ADC2
  // FC(2) : ch.2 of ADC2
  // FC(3) : ch.3 of ADC2 

  for(int ich=0;ich<4;ich++){
    int tmpch = ich*2;
    cal1->fc[1][ich]  = raw->adc2[tmpch];
    tmpch = ich*2 + 32;
    cal1->fcd[1][ich] = raw->adc2[tmpch]; 
  }

  // Laser
  // To keeping same array of A2Cal1, only the high range values 
  // are filled to A2Cal2
  // Laser Monitor PMT R : ch 6 of ADC2
  // Laser Monitor PMT L : ch 7 of ADC2
  /*cal1->laser[0]  = raw->adc2[6*2];
  cal1->laser[1]  = raw->adc2[7*2];
  cal1->laserd[0] = raw->adc2[32+6*2];
  cal1->laserd[1] = raw->adc2[32+7*2];*/

  //This part was copied from pp2015
  // **** ADC's For Laser Monitors *****
  // Laser Monitor in the laser box 
  cal1->laser[0]  = raw->adc3[0];
  cal1->laser[1]  = raw->adc3[1];
  cal1->laserd[0] = raw->adc3[2];
  cal1->laserd[1] = raw->adc3[3];

  // For Noise
  // To keeping same array of A2Cal1, only the low range values 
  // are filled to A2Cal2
  // The input channels are ch.8,9 and 10 of ADC2 
  cal1->emptyadc[0] = raw->adc2[2*8];
  cal1->emptyadc[1] = raw->adc2[2*9];
  cal1->emptyadc[2] = raw->adc2[2*10];

  // ************   For TDC   **************************
  // Because the limitation of number of values in a array, the window for each channels are 
  // applied as software cut. 
  // ch0 CLK with 100nsec mask    :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch1 L3T                      :   [L3T-2usec, L3T+1usec] no effect is expected
  // ch2 BPTX1                    :   [L3T-2usec, L3T+1usec]
  // ch3 BPTX2                    :   [L3T-2usec, L3T+1usec]
  // ch4 Shower Trigger           :   [L3T-2usec, L3T+1usec]
  // ch5 ATLAS L1A                :   [L3T-2usec, L3T+1usec]
  // ch6 -                        :   No mask
  // ch7 Arm2 FC Logic OR         :   [L3T-2usec, L3T+1usec]
  // ch8 25mm Discriminator OR    :   [L3T-2usec, L3T+1usec]  
  // ch9 32mm Discriminator OR    :   [L3T-2usec, L3T+1usec] 
  // ch10 -                       :   No mask
  // ch11 -                       :   No mask
  const int L3T_channel = 1; 
  double L3T_value = 0.;
  vector<double> tmptdc0[12];
  vector<char>   tmptdc0flag[12];
  unsigned int  tmpdata;
  int tmpvalue;
  int tmpchannel = 0;
  int tmpheader;
  int tmpphase;
  int nhit[12]={0};
  for(int ib=0;ib<A2Raw_pPb2016::c_N_TDC0;ib++){
    tmpdata = raw->tdc0[ib];
    if(tmpdata==0xFFFFFFFF){break;}
    tmpheader    = (tmpdata >> 27) & 0x1F;
    if(tmpheader==0){
      tmpvalue   = tmpdata & 0x1FFFFF;
      tmpchannel = (tmpdata >> 21) & 0x1F;
      tmpphase   = (tmpdata >> 26) & 0x1;
      if(tmpchannel >= 12){
	//cerr << "[A2RawToCal1_pPb2016::Convert] Warning: The number of TDC channels is >= 12;"
	//       << tmpchannel << endl;
      }
      else {
	tmptdc0[tmpchannel].push_back(tmpvalue*0.025);
	tmptdc0flag[tmpchannel].push_back(0x1*tmpphase);
      }
    }
    else if(tmpheader==0x10){
      break;
    }
    
    if(ib+1==A2Raw_pPb2016::c_N_TDC0){
      cerr << "[A2RawToCal1_pPb2016::Convert] Warning: "
           << "Nhits of TDC is over the buffer size (256)" << endl;
    }
    
  }
  
  // Check of number of hits of L3T and Set base value (L3T_value)
  if(tmptdc0[L3T_channel].size()==1){
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()>1){
    cerr << "[A2RawToCal1_pPb2016::Convert] Warning: " 
	 << "TDC ch1 (L3T) has more than one hit " << tmptdc0[L3T_channel].size()
	 << endl;
    L3T_value = tmptdc0[L3T_channel][0];
  }
  else if(tmptdc0[L3T_channel].size()==0){
    cerr << "[A2RawToCal1_pPb2016::Convert] Warning: " 
	 << "TDC ch1 (L3T) has no hit " 
	 << endl;
    L3T_value = 9200;   
  }

  // Fill with the window
  for(int ich=0;ich<12;ich++){
    for(int i=0;i<(int)tmptdc0[ich].size();i++){
      // check the signal is in the window or not.
      // The window is [L3T-2usec, L3T+1usec]
      if(tmptdc0[ich][i] < L3T_value-2000 || tmptdc0[ich][i] > L3T_value+1000){
	continue;
      }
      
      if(nhit[ich]>=16){
	if(ich!=2 && ich!=3){
	  cerr << "[A2RawToCal1_pPb2016::Convert] Warning: "
	       << "#hits of TDC["<< ich <<"] is over 16." << endl;
	}      
      }
      else{
	cal1->tdc0[ich][nhit[ich]]     = tmptdc0[ich][i];
	cal1->tdc0flag[ich][nhit[ich]] = tmptdc0flag[ich][i];
	nhit[ich]++;
      }
    }
  }
  

  // ************   For SCL   **************************
  for(int i=0;i<A2Raw_pPb2016::c_N_SCL0;i++){
    cal1->scl0[i] = raw->scl0[i];
  }
  
  //  ************   For GPIOs    ***********************
  cal1->flag[0] = raw->gpio0[0];
  cal1->flag[1] = raw->gpio0[1];
  cal1->flag[2] = raw->gpio1[0];

  int ch_gpio0 = 2;
  for(int ich=0;ich<15;ich++){
    cal1->counter[ich] = raw->gpio0[ch_gpio0];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      cal1->counter[ich] = raw->gpio1[ch_gpio1] & 0xFFFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 16) & 0xFF;
      ich ++;  
      cal1->counter[ich] = (raw->gpio1[ch_gpio1] >> 24) & 0xFF;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  } 
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      cal1->fifocounter[ififo][ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }

  return OK;

}

// ------------------------------------------------------
//       Functions for Conversion of Counter values
// ------------------------------------------------------
unsigned int A2RawToCal1::CounterFilter(unsigned int val, int mask, int offset){
  int filter=0;
  switch(mask){
  case(8):
    filter = 0xFF;
    break;
  case(16):
    filter = 0xFFFF;
    break;
  case(24):
    filter = 0xFFFFFF;
    break;
  case(32):
    filter = 0xFFFFFFFF;
    break;
  }

  return (val>>offset)&filter;
}

unsigned int A2RawToCal1::CounterCombine(unsigned int *val){
  return ((val[0]>>24)&0xFF)+((val[1]>>16)&0xFF00)+((val[2]>>8)&&0xFF0000);
}

// ***********************************************************
// ***  A2Raw::InverseConvert     ****************************
// ***********************************************************
int A2RawToCal1::InverseConvert(A2Cal1* cal1, A2Raw* raw){
  // Inverse Convert from A2Cal1 to A2Raw.
  // If format is not set, it call InverseConvert_OP2010();
  
  if(strcmp(raw->ClassName(),"A2Raw")==0){
	  static int icall = 0;
	  if(format==FORMAT_AUTO){
	    // As default
	    if(icall==0){
	      cerr << "[A2RawToCal1::InverseConvert] "
		   << " Format OP2010 was used for this conversion." 
		   << endl;
	      icall++;
	    }
	    return InverseConvert_OP2010(cal1,raw);
	  }
	  else if(format==FORMAT_OP2010){return InverseConvert_OP2010(cal1,raw);}
	  else if(format==FORMAT_OP2009){return InverseConvert_OP2009(cal1,raw);}
	  else{
	    cerr << "[A2RawToCal1::InverseConvert] " 
		 << "ERROR: Invalid format : " << format << endl;
	    return ERROR;
	  }
  }
  // ==============================================================
  // For the format for 2015 Operation  
  else if(strcmp(raw->ClassName(),"A2Raw_pp2015")==0){
    return InverseConvert_OP2015(cal1, (A2Raw*)raw);
  }
}

// ******************  A2RawToCal1::InverseConvert_OP2010  *******************
int  A2RawToCal1::InverseConvert_OP2009(A2Cal1* cal1, A2Raw* raw){
  // Inverse Conversion with 2009 format.
  
  raw->clear();

  raw->run = cal1->run;
  raw->number = cal1->number;
  raw->gnumber = cal1->gnumber;
  raw->time[0] = (int)cal1->time[0];
  raw->time[1] = (int)cal1->time[1];

  // ************   For ADCs (CAEN V965) *********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      // For normal gate
      tmpch = il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cal[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cal[1][il][ir];
      // For delayed gate
      tmpch = 32 + il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cald[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cald[1][il][ir];
    }
  } 

  // ************  For the Other ADCs ******************
  for(int ie=0;ie<8;ie++) {
    raw->adc2[ie] = (int) cal1->emptyadc[ie];
  }

  for(int ich=0;ich<4;ich++){
    raw->adc4[ 4+ich] = (int)cal1->fc[0][ich];
    raw->adc4[12+ich] = (int)cal1->fcd[0][ich]; 
  }

  for(int ir=0;ir<2;ir++){
    raw->adc4[ir]   = (int) cal1->laser[ir]; 
    raw->adc4[ir+8] = (int) cal1->laserd[ir]; 
  }

  // ************   For TDC   ************************** 
  // not yet

  // ************   For SCL   **************************
  for(int i=0;i<N_A2_SCL0;i++){
    raw->scl0[i] = (int) cal1->scl0[i];
  }
  
  // ************   For GPIOs    ***********************
  raw->gpio0[0] = cal1->flag[0];
  raw->gpio0[1] = cal1->flag[1];
  raw->gpio1[0] = cal1->flag[2];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<14;ich++){
    raw->gpio0[ch_gpio0] = cal1->counter[ich];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      raw->gpio1[ch_gpio1] =  (cal1->counter[ich] & 0xFFFF);
      ich ++;  
      raw->gpio1[ch_gpio1] += (cal1->counter[ich] & 0xFF) << 16;
      ich ++;  
      raw->gpio1[ch_gpio1] += (cal1->counter[ich] & 0xFF) << 24;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      raw->gpio1[ch_gpio1] = cal1->fifocounter[ififo][ich];
      ch_gpio1++;
    }
  }
  
  return OK;
}

// ******************  A2RawToCal1::InverseConvert_OP2010  *******************
int  A2RawToCal1::InverseConvert_OP2010(A2Cal1* cal1, A2Raw* raw){
  // Inverse Conversion with 2010 format.
  
  raw->clear();

  raw->run = cal1->run;
  raw->number = cal1->number;
  raw->gnumber = cal1->gnumber;
  raw->time[0] = (int)cal1->time[0];
  raw->time[1] = (int)cal1->time[1];

  // ************   For ADCs (CAEN V965) *********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      // For normal gate
      tmpch = il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cal[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cal[1][il][ir];
      // For delayed gate
      tmpch = 32 + il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cald[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cald[1][il][ir];
    }
  } 

  // ************  For the Other ADCs ******************
  for(int ie=0;ie<8;ie++) {
    raw->adc2[ie] = (int) cal1->emptyadc[ie];
  }

  for(int ich=0;ich<4;ich++){
    raw->adc3[ich+0]  = (int)cal1->fc[0][ich];
    raw->adc3[ich+8]  = (int)cal1->fcd[0][ich]; 
    raw->adc3[ich+4]  = (int)cal1->fc[1][ich];
    raw->adc3[ich+12] = (int)cal1->fcd[1][ich]; 
  }

  for(int ir=0;ir<2;ir++){
    raw->adc4[ir]   = (int) cal1->laser[ir]; 
    raw->adc4[ir+8] = (int) cal1->laserd[ir]; 
  }

  // ************   For TDC   ************************** 
  // not yet

  // ************   For SCL   **************************
  for(int i=0;i<N_A2_SCL0;i++){
    raw->scl0[i] = (int) cal1->scl0[i];
  }
  
  // ************   For GPIOs    ***********************
  raw->gpio0[0] = cal1->flag[0];
  raw->gpio0[1] = cal1->flag[1];
  raw->gpio1[0] = cal1->flag[2];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<15;ich++){
    raw->gpio0[ch_gpio0] = cal1->counter[ich];
    ch_gpio0++;
  }

  int ch_gpio1 = 1;
  for(int ich=15;ich<35;ich++){
    if(ch_gpio1==9){
      raw->gpio1[ch_gpio1] =  (cal1->counter[ich] & 0xFFFF);
      ich ++;  
      raw->gpio1[ch_gpio1] += (cal1->counter[ich] & 0xFF) << 16;
      ich ++;  
      raw->gpio1[ch_gpio1] += (cal1->counter[ich] & 0xFF) << 24;
      ch_gpio1++;
    }
    else{
      cal1->counter[ich] = raw->gpio1[ch_gpio1];
      ch_gpio1++;
    }
  }
  
  for(int ififo=0;ififo<2;ififo++){
    for(int ich=0;ich<4;ich++){
      raw->gpio1[ch_gpio1] = cal1->fifocounter[ififo][ich];
      ch_gpio1++;
    }
  }
  
  return OK;
}


// ******************  A2RawToCal1::InverseConvert_OP2010  *******************
int  A2RawToCal1::InverseConvert_OP2015(A2Cal1* cal1, A2Raw* raw){
  // Inverse Conversion with 2010 format.
  
  raw->clear();

  raw->run = cal1->run;
  raw->number = cal1->number;
  raw->gnumber = cal1->gnumber;
  raw->time[0] = (int)cal1->time[0];
  raw->time[1] = (int)cal1->time[1];

  // ************   For ADCs (CAEN V965) *********************
  int tmpch;
  for(int il=0;il<16;il++){
    for(int ir=0;ir<2;ir++){
      // For normal gate
      tmpch = il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cal[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cal[1][il][ir];
      // For delayed gate
      tmpch = 32 + il*2 + (1-ir);
      raw->adc0[tmpch] = (int) cal1->cald[0][il][ir];
      raw->adc1[tmpch] = (int) cal1->cald[1][il][ir];
    }
  } 

  // ************  For the Other ADCs ******************
  for(int ich=0;ich<4;ich++){
    raw->adc2[8+ich*2] = cal1->fc[0][ich] ;  // For Arm1
    raw->adc2[ich*2] = cal1->fc[1][ich]; // For Arm2 
  }

  raw->adc2[17] = cal1->emptyadc[0]; //  LRADC 
  raw->adc2[19] = cal1->emptyadc[1]; //  LRADC  delayed gate
  raw->adc2[16] = cal1->emptyadc[2]; //  HRADC 
  raw->adc2[18] = cal1->emptyadc[3]; //  HRADC  delayed gate

  raw->adc3[0] = cal1->laser[0];
  raw->adc3[1] = cal1->laser[1];
  raw->adc3[2] = cal1->laser[2];
  raw->adc3[3] = cal1->laser[3];


  // ************   For TDC   ************************** 
  // not yet

  // ************   For SCL   **************************
  for(int i=0;i<A2Raw_pPb2013::c_N_SCL0;i++){
    raw->scl0[i] = (int) cal1->scl0[i];
  }
  
  // ************   For GPIOs    ***********************
  raw->gpio0[0] = cal1->flag[0];
  raw->gpio0[1] = cal1->flag[1];
  raw->gpio1[0] = cal1->flag[2];
  
  int ch_gpio0 = 2;
  for(int ich=0;ich<15;ich++){
    raw->gpio0[ch_gpio0] = cal1->counter[ich];
    ch_gpio0++;
  }
  
  return OK;
}
#endif
