#include "Delaypede.h"
#include "../include/Delaypede.h"
#include <bitset>
#include "RHICfRaw_Op2017.h"
#include "RHICfRec0.h"
#include "RHICfRec1.h"
#include <iostream>
#include <fstream>
#include "TF1.h"
#include "TMath.h"
#include "A1Reconstruction.h"

using namespace std;


// Delaypede::Delaypede()
// {
  
// };

// Delaypede::~Delaypede(){
//   return;
// };

int Delaypede::GetRun(int run, double fmean[2][16]){
  cout << "test" << " " << fmean[0][0] << endl;
  return run; 
}


double Delaypede::GetParam(int run, double fmean[2][16], double fsigma[2][16])
{
   ifstream fin("/crhome/sato.kenta/RHICf/Analysis/Op2017/workspace/2018/src/RHICfEvent_delaypede/result_delaypede/delaypede_peak.dat");
  //cerr << "ここまで " << endl; 
  int buf_run;
  double buf[32];
  double dp[2][16];
  Int_t j=0;
  while(!fin.eof()){
      fin >> buf_run >> buf[0] >> buf[1] >> buf[2] >> buf[3] >> buf[4] >> buf[5] >>buf[6] >>buf[7] >>buf[8] >>buf[9] >>buf[10] >>buf[11] >>buf[12] >>buf[13] >>buf[14] >>buf[15] >>buf[16] >>buf[17] >>buf[18] >>buf[19] >>buf[20] >>buf[21] >>buf[22] >>buf[23] >>buf[24] >>buf[25] >>buf[26] >>buf[27] >>buf[28] >>buf[29] >>buf[30] >>buf[31];
      if ( fin.eof() ) break;
      if(run == buf_run){
  	for(int itower=0;itower<2;itower++){
  	  for(int ilayer=0; ilayer<16;ilayer++){
  	    if(itower ==0) dp[itower][ilayer]  = buf[ilayer];
  	    if(itower ==1) dp[itower][ilayer]  = buf[16+ilayer];
  	  }
  	}
  	break;
      }
      //cout << j << " " << fmean[j] <<" " << fsigma[j] << endl;
      j++;
  }

  
  ifstream fin1("/crhome/sato.kenta/RHICf/Analysis/Op2017/workspace/2018/src/RHICfEvent_delaypede/result_delaypede/delaypede_sigma.dat");
  double adc_sigma[2][16];
  j=0;
  while(!fin1.eof()){
    fin1 >> buf_run >> buf[0] >> buf[1] >> buf[2] >> buf[3] >> buf[4] >> buf[5] >>buf[6] >>buf[7] >>buf[8] >>buf[9] >>buf[10] >>buf[11] >>buf[12] >>buf[13] >>buf[14] >>buf[15] >>buf[16] >>buf[17] >>buf[18] >>buf[19] >>buf[20] >>buf[21] >>buf[22] >>buf[23] >>buf[24] >>buf[25] >>buf[26] >>buf[27] >>buf[28] >>buf[29] >>buf[30] >>buf[31];
    if ( fin1.eof() ) break;
      if(run== buf_run){
	for(int itower=0;itower<2;itower++){
	  for(int ilayer=0; ilayer<16;ilayer++){
	    if(itower ==0) adc_sigma[itower][ilayer] = buf[ilayer];
	    if(itower ==1) adc_sigma[itower][ilayer] = buf[16 + ilayer];
	  }
	}
	break;
      }
      //cout << j << " " << fmean[j] <<" " << fsigma[j] << endl;
      j++;
  }

  for(int itower=0;itower<2;itower++){
    for(int ilayer=0; ilayer<16;ilayer++){
      fmean[itower][ilayer] = dp[itower][ilayer];
      fsigma[itower][ilayer] = dp[itower][ilayer] + 5*adc_sigma[itower][ilayer];
      //cout << fmean[itower][ilayer] << " " << fsigma[itower][ilayer] << endl;
    }
  }
 
  
}



void Delaypede::CheckDelaypede(RHICfRaw_Op2017 *raw, double fmean[2][16], double fsigma[2][16], int delay_flag[2]){
  double delayadc[2][16] = {{0}};
  double delayadc_sub[2][16]= {{0}};
  
  bool particle[2][16] = {{false}};
  // double fmean[2][16]; //test
  // double fsigma[2][16]; //test
  //read adc_value & subtract fsigma value & partcle incident identification ;
  for(int tower =0;tower<2;tower++){
    if(tower==0){
      for(int layer=0;layer<16;layer++){
	delayadc[tower][layer] = raw->adc0[2*layer+1+32];                               //read adc_value
	delayadc_sub[tower][layer] = delayadc[tower][layer] - fsigma[tower][layer]; //subtract fsigma value
	//delayadc_sub[tower][layer] = delayadc[tower][layer] - b[tower][layer];
	if(delayadc_sub[tower][layer]>0) particle[tower][layer] =true;                  //partcle incident identification
      }
    }
    if(tower==1){
      for(int layer=0;layer<16;layer++){
	delayadc[tower][layer] = raw->adc1[2*layer+1+32];                              //read adc_value
	delayadc_sub[tower][layer] = delayadc[tower][layer] - fsigma[tower][layer];//subtract fsigma value
	//delayadc_sub[tower][layer] = delayadc[tower][layer] - b[tower][layer];
	if(delayadc_sub[tower][layer]>0) particle[tower][layer] =true;                 //partcle incident identification
      }
    }
  }
  
  //replace delay pedestal value
  if(particle[0][0] || particle[0][1] || particle[0][2] || particle[0][3] || particle[0][4] || particle[0][5] || 
     particle[0][6] || particle[0][7] || particle[0][8] || particle[0][9] || particle[0][10] || particle[0][11] || 
     particle[0][12] || particle[0][13] || particle[0][14] || particle[0][15]){
    //delay_flag = 1;
    delay_flag[0] = 1;
    //cout << "delay_flag " << delay_flag << endl; 
    for(int layer=0;layer<16;layer++){
      //cout << "0" << " " << layer << " " << raw->adc0[2*layer+1+32] << endl;
      raw->adc0[2*layer+1+32] = fmean[0][layer];
      //cout << "0" << " " << layer << " " << raw->adc0[2*layer+1+32] << endl;
    }
  }


  if(particle[1][0] || particle[1][1] || particle[1][2] || particle[1][3] || particle[1][4] || particle[1][5] || 
     particle[1][6] || particle[1][7] || particle[1][8] || particle[1][9] || particle[1][10] || particle[1][11] || 
     particle[1][12] || particle[1][13] || particle[1][14] || particle[1][15]){
    //delay_flag = 2;
    delay_flag[1] = 1;
    //cout << "delay_flag " << delay_flag << endl; 
    for(int layer=0;layer<16;layer++){
      //cout << "1" << " " << layer << " " << raw->adc1[2*layer+1+32] << endl;
      raw->adc1[2*layer+1+32] = fmean[1][layer];
      //cout << "1" << " " << layer << " " << raw->adc1[2*layer+1+32] << endl;
      // fmean[1][layer] = 0;
      // cout << "fmean[1][layer] " << fmean[1][layer] << endl;
    }
  } 
  
  //set AnalysisFlag
  //reconstruction->fRec->SetAnalysisFlags(2*delay_flag[1] + delay_flag[0]);
  //cout << "Flags " << bitset<8>(reconstruction->fRec->GetAnalysisFlags()) << endl;
    
};

void Delaypede::SetDelayPedeFlag(int delay_flag[2], A1Reconstruction *reconstruction){
  //set AnalysisFlag
  reconstruction->fRec->SetAnalysisFlags(2*delay_flag[1] + delay_flag[0]);
  //cout << "Flags " << bitset<8>(reconstruction->fRec->GetAnalysisFlags()) << endl;
}
