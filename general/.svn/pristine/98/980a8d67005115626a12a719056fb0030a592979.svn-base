#ifndef __A1COUNTARRAY_CPP__
#define __A1COUNTARRAY_CPP__

#include "A1CountArray.h"

//---------------------------------------------------------------------
// 
// This class store counter values of some events.
// It is mainly used for online analyzer and display. 
//
//  Filled Data from A1Scl (OLD)
//    count[0] : A1Scl::scl0[8]   F.C ch0 of this Arm1
//    count[1] : A1Scl::scl0[9]   F.C ch1 of this Arm1
//    count[2] : A1Scl::scl0[10]  F.C ch2 of this Arm1
//    count[3] : A1Scl::scl0[11]  F.C ch3 of this Arm1
//    count[4] : A1Scl::scl0[14]  Arm1 Shower and F.C.1
//    count[5] : A1Scl::scl0[0+1] 40MHz Clock
//    count[6] : A1Scl::scl0[2+3] BPTX1
//    count[7] : A1Scl::scl0[4+5] BPTX2
//    count[8] : A1Scl::scl0[7]   L2TA
//
//  Filled Data from A1Scl (pp2015)
//    count[0] : A1Scl::scl0[8]   F.C ch0 of this Arm1
//    count[1] : A1Scl::scl0[9]   F.C ch1 of this Arm1
//    count[2] : A1Scl::scl0[10]  F.C ch2 of this Arm1
//    count[3] : A1Scl::scl0[11]  F.C ch3 of this Arm1
//    count[4] : A1Scl::scl0[?]  Arm1 Shower and F.C.1
//    count[5] : A1Scl::scl0[0+1] 40MHz Clock
//    count[6] : A1Scl::scl0[2] BPTX1
//    count[7] : A1Scl::scl0[3] BPTX2
//    count[8] : A1Scl::scl0[?]   L2TA
//
//  Filled Data from A1Cal1
//    count[0] : A1Cal1::counter[4]  Shower Trigger of small tower
//    count[1] : A1Cal1::counter[5]  Shower Trigger of large tower
//    count[2] : A1Cal1::counter[17] ATLAS_L1A (cleared by LHCF_ECR)
//    count[3] : A1Cal1::counter[32] LHCFCOUNTER:SFC1 "FC TRG of Arm1"
//    count[4] : A1Cal1::counter[33] LHCFCOUNTER:SFC2 "A2_FCL_OR and A1_STRG"
//    count[5] : A1Cal1::counter[34] LHCFCOUNTER:SFC3 "A1_FCL_OR and A2_FCL_OR"
//    count[6] : A1Cal1::counter[22] Arm1 L2TA "AND" Arm2 L2TA
//    count[7] : A1Cal1::counter[1]  L1T
//    count[8] : A1Cal1::counter[13] L3T
//    count[9] : A1Cal1::counter[27] ATLAS_L1A (cleared by ATLAS_ECR)
//    count[10]: A1Cal1::counter[7]  SLOGIC
//    count[11]: A1Cal1::counter[8]  LLOGIC
//    count[12]: A1Cal1::counter[6]  20mm Shower "OR"  40mm Shower
//    count[13]: Calculate           20mm Shower "AND" 40mm Shower
//    count[14]: A1Cal1::counter[9]  L2TA
//    count[15]: A1Cal1::counter[10] L2TP
//    count[16]: A1Cal1::counter[11] L2T_EXT
//    count[17]: A1Cal1::counter[12] L2T_L1T
//   
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 27 Jul. 08: First Editted by H.MENJO
// 29 Nov. 09: L3T channel corrected by Sako
// 11 Jan. 10: Modified the array by H.MENJO 
//             Actually just addition of channels
//             Version 1 -> 2 
// 30 Apr. 15: For pp2015 by Y.Makino 
//---------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1CountArray);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
#include <TH1F.h>
using namespace std;

const int A1CountArray::NCH;
const int A1CountArray::NDATA;
const int A1CountArray::NTIME_A1CAL1;

A1CountArray::A1CountArray(){
  // Just call Initalize();
  Initalize();
}

A1CountArray::A1CountArray(char* name, char *title) : TNamed(name,title){
  // Just call Initalize();
  Initalize();
}

A1CountArray::~A1CountArray(){
  // Nothing 
}

int A1CountArray::Initalize(){
  // Just call Clear(); 
  Clear();
  return OK;
}

int A1CountArray::Clear(){
  // Clear all data.

  ndata = 0;
  idata = -1;
  
  for(int i=0;i<NDATA;i++){
    time[i] = 0.;
    for(int ich=0;ich<NCH;ich++){
      count[ich][i] = 0.;
      rate[ich][i] = 0.;
    }
  }

  a1scl.clear();
  a1cal1.clear();

  return OK;
}

int A1CountArray::Next(int n){
  // return the data number of next data
  
  n++;
  if(n>=NDATA){
    n = 0;
  }
  return n;
}

int A1CountArray::Previous(int n){
  // return the data number of previous data
  
  n--;
  if(n<0){
    n=NDATA-1;
  }
  return n;
}


// int A1CountArray::Fill(A1Scl* d){
//   // Fill A1Scl data to the array
  
//   const double b24 = 16777216.;
  
//   if(d->run != a1scl.run){
//     a1scl.copydata(d);
//     return OK;
//   }
  
//   idata = Next(idata);
  
//   nchannel = 9;
//   time[idata] = d->time[0];
//   count[0][idata] = d->scl0[8];  
//   count[1][idata] = d->scl0[9];
//   count[2][idata] = d->scl0[10];
//   count[3][idata] = d->scl0[11];
//   count[4][idata] = d->scl0[14];
//   count[5][idata] = (double)d->scl0[1]*b24 + (double)d->scl0[0];
//   count[6][idata] = (double)d->scl0[3]*b24 + (double)d->scl0[2];
//   count[7][idata] = (double)d->scl0[5]*b24 + (double)d->scl0[4];
//   count[8][idata] = d->scl0[7];
   
//   double dtime;
//   dtime =  (d->scl0[0]>>21)*0.0524288 + d->scl0[1]*0.4194304;  
//   dtime -= (a1scl.scl0[0]>>21)*0.0524288 + a1scl.scl0[1]*0.4194304; 
//   rate[0][idata] = (float)(d->scl0[8] -a1scl.scl0[8]) /dtime;
//   rate[1][idata] = (float)(d->scl0[9] -a1scl.scl0[9]) /dtime;
//   rate[2][idata] = (float)(d->scl0[10]-a1scl.scl0[10])/dtime;
//   rate[3][idata] = (float)(d->scl0[11]-a1scl.scl0[11])/dtime;
//   rate[4][idata] = (float)(d->scl0[14]-a1scl.scl0[14])/dtime;
//   rate[5][idata] = (b24*((double)d->scl0[1]-(double)a1scl.scl0[1])
// 		    +((double)d->scl0[0]-(double)a1scl.scl0[0]))/dtime;
//   rate[6][idata] = (b24*((double)d->scl0[3]-(double)a1scl.scl0[3])
// 		    +((double)d->scl0[2]-(double)a1scl.scl0[2]))/dtime; 
//   rate[7][idata] = (b24*((double)d->scl0[5]-(double)a1scl.scl0[5])
// 		    +((double)d->scl0[4]-(double)a1scl.scl0[4]))/dtime; 
//   rate[8][idata] = (float)(d->scl0[7]-a1scl.scl0[7])/dtime;

//   a1scl.copydata(d);
  
//   if(ndata<NDATA){
//     ndata++; 
//   }
  
//   return OK;
// }

int A1CountArray::Fill(A1Cal1* d){ 
  // Fill A1Cal1 data to the array
  
  if(d->run != a1cal1.run){
    a1cal1.copydata(d);
    return OK;
  }

  if(d->time[0]-a1cal1.time[0] < NTIME_A1CAL1){
    return OK;
  }

  idata = Next(idata);
  
  nchannel = 18;
  time[idata] = d->time[0];
  count[0][idata] = d->counter[7];  // Shower Trigger of small tower
  count[1][idata] = d->counter[8];  // Shower Trigger of large tower
  count[2][idata] = d->counter[26]; // ATLAS_L1A 
  count[3][idata] = d->counter[32]; // SFC1 
  count[4][idata] = d->counter[33]; // SFC2 
  count[5][idata] = d->counter[34]; // SFC3 
  count[6][idata] = d->counter[21]; // STRG_AND
  count[7][idata] = d->counter[5];  // L1T
  count[8][idata] = d->counter[19]; // L3T
  count[9][idata] = d->counter[26]; // ATLAS_L1A
  count[10][idata]= d->counter[9];  // SLOGIC
  count[11][idata]= d->counter[10];  // LLOGIC
  count[12][idata]= d->counter[11];  // STRG_OR 
  count[13][idata]= d->counter[7] + d->counter[8]- d->counter[11]; // STRG_AND
  count[14][idata]= d->counter[9];  // L2TA ?
  count[15][idata]= d->counter[10]; // L2TP ?
  count[16][idata]= d->counter[11]; // L2T_EXT ? 
  count[17][idata]= d->counter[12]; // L2T_L1T ?

  // --- Following are the old version ---
  // count[0][idata] = d->counter[4];  // Shower Trigger of small tower
  // count[1][idata] = d->counter[5];  // Shower Trigger of large tower
  // count[2][idata] = d->counter[17]; // ATLAS_L1A 
  // count[3][idata] = d->counter[32]; // SFC1
  // count[4][idata] = d->counter[33]; // SFC2
  // count[5][idata] = d->counter[34]; // SFC3
  // count[6][idata] = d->counter[22]; // STRG_AND
  // count[7][idata] = d->counter[1];  // L1T
  // count[8][idata] = d->counter[13]; // L3T
  // count[9][idata] = d->counter[27]; // ATLAS_L1A
  // count[10][idata]= d->counter[7];  // SLOGIC
  // count[11][idata]= d->counter[8];  // LLOGIC
  // count[12][idata]= d->counter[6];  // STRG_OR
  // count[13][idata]= d->counter[4] - d->counter[6] + d->counter[5]; // STRG_AND
  // count[14][idata]= d->counter[9];  // L2TA
  // count[15][idata]= d->counter[10]; // L2TP
  // count[16][idata]= d->counter[11]; // L2T_EXT
  // count[17][idata]= d->counter[12]; // L2T_L1T



  double dtime,tmp1,tmp2;
  dtime = (d->time[0] - a1cal1.time[0] )
    +(d->time[1]-a1cal1.time[1])/1000000.;
  rate[0][idata] = (float)(d->counter[4] -a1cal1.counter[4] )/dtime;
  rate[1][idata] = (float)(d->counter[5] -a1cal1.counter[5] )/dtime;
  rate[2][idata] = (float)(d->counter[17]-a1cal1.counter[17])/dtime;
  rate[3][idata] = (float)(d->counter[32]-a1cal1.counter[32])/dtime;
  rate[4][idata] = (float)(d->counter[33]-a1cal1.counter[33])/dtime;
  rate[5][idata] = (float)(d->counter[34]-a1cal1.counter[34])/dtime; 
  rate[6][idata] = (float)(d->counter[22]-a1cal1.counter[22])/dtime; 
  rate[7][idata] = (float)(d->counter[1] -a1cal1.counter[1] )/dtime;
  rate[8][idata] = (float)(d->counter[13]-a1cal1.counter[13])/dtime; 
  rate[9][idata] = (float)(d->counter[27]-a1cal1.counter[27])/dtime; 
  rate[10][idata]= (float)(d->counter[7] -a1cal1.counter[7] )/dtime;   
  rate[11][idata]= (float)(d->counter[8] -a1cal1.counter[8] )/dtime; 
  rate[12][idata]= (float)(d->counter[6] -a1cal1.counter[6] )/dtime; 
  tmp1 = d->counter[4] - d->counter[6] + d->counter[5];
  tmp2 = a1cal1.counter[4] - a1cal1.counter[6] + a1cal1.counter[5];
  rate[13][idata]= (tmp1-tmp2)/dtime;
  rate[14][idata]= (float)(d->counter[9] -a1cal1.counter[9] )/dtime;   
  rate[15][idata]= (float)(d->counter[10]-a1cal1.counter[10])/dtime; 
  rate[16][idata]= (float)(d->counter[11]-a1cal1.counter[11])/dtime; 
  rate[17][idata]= (float)(d->counter[12]-a1cal1.counter[12])/dtime;

  a1cal1.copydata(d);

  if(ndata<NDATA){
    ndata++; 
  }
  return OK;
}

// -----------------------------------------------------------
//                    Fill(A1Scl_pp2015* )
// -----------------------------------------------------------
int A1CountArray::Fill(A1Scl_pp2015* d){
  // Please write it here for 2015.
  const double b24 = 16777216.;
  
  if(d->run != a1scl.run){
    a1scl.copydata(d);
    return OK;
  }
  
  idata = Next(idata);
  
  nchannel = 9;
  time[idata] = d->time[0];
  count[0][idata] = d->scl0[8];  
  count[1][idata] = d->scl0[9];
  count[2][idata] = d->scl0[10];
  count[3][idata] = d->scl0[11];
  count[4][idata] = d->scl0[14];
  count[5][idata] = (double)d->scl0[0]*b24 + (double)d->scl0[1];
  count[6][idata] = (double)d->scl0[2];
  count[7][idata] = (double)d->scl0[3];
  count[8][idata] = d->scl0[7];
   
  double dtime;
  dtime =  (d->scl0[0]>>21)*0.0524288 + d->scl0[1]*0.4194304;  
  dtime -= (a1scl.scl0[0]>>21)*0.0524288 + a1scl.scl0[1]*0.4194304; 
  rate[0][idata] = (float)(d->scl0[8] -a1scl.scl0[8]) /dtime;
  rate[1][idata] = (float)(d->scl0[9] -a1scl.scl0[9]) /dtime;
  rate[2][idata] = (float)(d->scl0[10]-a1scl.scl0[10])/dtime;
  rate[3][idata] = (float)(d->scl0[11]-a1scl.scl0[11])/dtime;
  rate[4][idata] = (float)(d->scl0[14]-a1scl.scl0[14])/dtime;
  rate[5][idata] = (b24*((double)d->scl0[1]-(double)a1scl.scl0[1])
		    +((double)d->scl0[0]-(double)a1scl.scl0[0]))/dtime;
  rate[6][idata] = (b24*((double)d->scl0[3]-(double)a1scl.scl0[3])
		    +((double)d->scl0[2]-(double)a1scl.scl0[2]))/dtime; 
  rate[7][idata] = (b24*((double)d->scl0[5]-(double)a1scl.scl0[5])
		    +((double)d->scl0[4]-(double)a1scl.scl0[4]))/dtime; 
  rate[8][idata] = (float)(d->scl0[7]-a1scl.scl0[7])/dtime;

  a1scl.copydata(d);
  
  if(ndata<NDATA){
    ndata++; 
  }
  
  return OK;
}

TGraph* A1CountArray::MakeTGraph(int ch,int sel,int mode){
  // Make a TGraph. 
  //   ch  :  channel
  //   sel :  selection of count(0) or rate(1)
  //   mode:  selection of data source A1Scl(0) or A1Cal1(1)
  //          if give -1, it is automattically selected. 
  
  if(mode==-1){
    if(nchannel<10){mode=0;}
    else           {mode=1;}
  }
  
  int    ip=idata;
  double x[NDATA],y[NDATA];
  
  for(int i=0;i<ndata;i++){
    x[i] = time[ip];
    if(sel==1){
      y[i] = rate[ch][ip];
    }
    else{
      y[i] = count[ch][ip];
    }
    ip = Previous(ip);
  }
  
  TGraph *g = new TGraph(ndata,x,y);
  g->GetHistogram()->SetTitle(GetCounterTitle(mode,ch));
  return g;
}

TGraph* A1CountArray::FillToTGraph(int ch,int sel,TGraph* g){
  // Fill data in the given TGraph
  //   ch  :  channel
  //   sel :  selection of count(0) or rate(1)
  
  int ip = idata;
  double x,y;
  g->Set(ndata);
  for(int i=0;i<ndata;i++){
    x = time[ip];
    if(sel==1){
      y = rate[ch][ip];
    }
    else{
      y = count[ch][ip];
    }
    g->SetPoint(i,x,y);
    ip = Previous(ip);
  }
  return g;
}

const char* A1CountArray::GetCounterTitle(int sel, int ich){
  // for Ver 1
  
  // A1Scl
  if(sel==0){
    if(ich==0)     {return "FC1";}
    else if(ich==1){return "FC2";}
    else if(ich==2){return "FC3";}
    else if(ich==3){return "FC4";}
    else if(ich==4){return "COIN";}   
    else if(ich==5){return "40MHz CLK";} 
    else if(ich==6){return "BPTX1";} 
    else if(ich==7){return "BPTX2";} 
    else if(ich==8){return "L2TA";}  
    else {return "";}
  }
  // A1Cal1
  else if(sel==1){
    if(ich==0)     {return "STRG";}
    else if(ich==1){return "LTRG";}
    else if(ich==2){return "ATLAS L1A";}
    else if(ich==3){return "FC1 TRG";}   
    else if(ich==4){return "A1S & FC2";} 
    else if(ich==5){return "FC1 & FC2";}
    else if(ich==6){return "A1S & A2S";}
    else if(ich==7){return "L1T";}   
    else if(ich==8){return "L3T";}
    else if(ich==9){return "ATLAS_L1A";}
    else if(ich==10){return "SLOGIC";}
    else if(ich==11){return "LLOGIC";}
    else if(ich==12){return "20mm OR 40mm";}
    else if(ich==13){return "20mm AND 40mm";} 
    else if(ich==14){return "L2TA";}
    else if(ich==15){return "L2TP";} 
    else if(ich==16){return "L2T_EXT";}
    else if(ich==17){return "L2T_L1T";}
    else {return "";}
 }
  else{
    return "";
  }
}

#endif
