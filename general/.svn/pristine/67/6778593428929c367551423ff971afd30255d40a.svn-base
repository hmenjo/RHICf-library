#ifndef __A2PEDESUBTACT_CPP__
#define __A2PEDESUBTACT_CPP__

#include "A2PedeSubtract.h"

//----------------------------------------------------------------------
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2PedeSubtract);
#endif

#include <iostream>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <cstdio>
using namespace std;

// ******* A2PedeSubtract Definition *********************
const int   A2PedeSubtract::DEFAULT_ACCUM_NEVENT;
const char* A2PedeSubtract::PEDESTAL_NAME    = "a2pedestal";
const char* A2PedeSubtract::PEDESTAL_TITLE   = "Arm#2 Pedestal";
const char* A2PedeSubtract::PEDESIGMA_NAME   = "a2pedesigma";
const char* A2PedeSubtract::PEDESIGMA_TITLE  = "Arm#2 RMS of pedestal";
const char* A2PedeSubtract::PEDESTAL2_NAME   = "a2pedestal2";
const char* A2PedeSubtract::PEDESTAL2_TITLE  = "Arm#2 Offset of Pedestal";
const char* A2PedeSubtract::PEDESIGMA2_NAME  = "a2pedesigma2";
const char* A2PedeSubtract::PEDESIGMA2_TITLE = "Arm#2 RMS After subtruction";
const char* A2PedeSubtract::DEFAULT_FILENAME  = "config/pedestal.root";

// ******* A2PedeSubtract::A2PedeSubtract  ****************
A2PedeSubtract::A2PedeSubtract(){
  accum_nevent = DEFAULT_ACCUM_NEVENT;
  Initialize();
  
  return ;
}

// ******* A2PedeSubtract::~A2PedeSubtract  ****************
A2PedeSubtract::~A2PedeSubtract(){
  if(pedeaccum)    delete pedeaccum;
  if(pedeaccum2)   delete pedeaccum2;
  if(pedestal)     delete pedestal;
  if(pedesigma)    delete pedesigma;
  if(pedeaccum2_1) delete pedeaccum2_1;
  if(pedeaccum2_2) delete pedeaccum2_2;
  if(pedestal2)    delete pedestal2;
  if(pedesigma2)   delete pedesigma2;  
  return ;
}

// ******* A2PedeSubtract::Init ***************************
int A2PedeSubtract::Init(A2Cal1* pede){ 
  ReadFile((char*)DEFAULT_FILENAME);
  cout << "[PedeSubtract] Loaded " << DEFAULT_FILENAME << endl;
  if(pede){
    pede->copydata(pedestal);
  }
  return OK;
}

// ******* A2PedeSubtract::Exit ***************************
int A2PedeSubtract::Exit(){ 
  WriteFile((char*)DEFAULT_FILENAME);
  cout << "[PedeSubtract] Wrote " << DEFAULT_FILENAME << endl;
  return OK;
}

// ******* A2PedeSubtract::Bor ****************************
int A2PedeSubtract::Bor(){
  return OK;
}

// ******* A2PedeSubtract::Eor ****************************
int A2PedeSubtract::Eor(){
  return OK;
}

// ******* A2PedeSubtract::Initialize *********************
int A2PedeSubtract::Initialize(){
  pedeaccum    = new A2Cal1();
  pedeaccum2   = new A2Cal1();
  pedestal     = new A2Cal1((char*)PEDESTAL_NAME,(char*)PEDESTAL_TITLE);
  pedesigma    = new A2Cal1((char*)PEDESIGMA_NAME,(char*)PEDESIGMA_TITLE);
  pedeaccum2_1 = new A2Cal1();
  pedeaccum2_2 = new A2Cal1();
  pedestal2    = new A2Cal1((char*)PEDESTAL2_NAME,(char*)PEDESTAL2_TITLE);
  pedesigma2   = new A2Cal1((char*)PEDESIGMA2_NAME,(char*)PEDESIGMA2_TITLE);
  opoffsetsubtraction = true;

  AccumClear();
  return OK;
}

// ******* A2PedeSubtract::AccumClear  ********************
int A2PedeSubtract::AccumClear(){
  nevent = 0;

  pedeaccum->clear();
  pedeaccum2->clear();
  
  pedeaccum2_1->clear();
  pedeaccum2_2->clear();
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  silicon_accum[il][ixy][istrip][isample]  = 0.;
	  silicon_accum2[il][ixy][istrip][isample] = 0.;
	}
      }
    }
  }

  return OK;
}

// ******* A2PedeSubtract::FillPedeEvent  ********************
int A2PedeSubtract::FillPedeEvent(A2Cal1* data){
  if(nevent==0){
    pedeaccum->copydata(data ,0);
    pedeaccum2->copydata(data ,0);
  }
    
  pedeaccum->add(data,
		 (A2Cal1::CAL | A2Cal1::CALD | A2Cal1::FC | A2Cal1::FCD | 
		  A2Cal1::LASER | A2Cal1::LASERD | A2Cal1::EMPTYADC) ); 
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  silicon_accum[il][ixy][istrip][isample] 
	    += data->silicon[il][ixy][istrip][isample];
	}
      }
    }
  }

  AddSqare(data);
  
  
  // For offset subtraction After subtraction of delayed gate
  if(opoffsetsubtraction){  
    if(nevent==0){
      pedeaccum2_1->copydata(data ,0);
      pedeaccum2_2->copydata(data ,0);
    }
    datatmp.copydata( data, 
		      A2Cal1::CAL | A2Cal1::CALD  | A2Cal1::FC |  
		      A2Cal1::FCD | A2Cal1::LASER | A2Cal1::LASERD);
    Subtraction1(&datatmp); // subtraction of delayed gate
    pedeaccum2_1->add(&datatmp,
		      (A2Cal1::CAL | A2Cal1::FC | A2Cal1::LASER) );   
    AddSqare2(&datatmp);
  }

  nevent++;
  return OK;
}

// ******* A2PedeSubtract::CalPedestal  ********************
int A2PedeSubtract::CalPedestal(){
  
  pedeaccum->divide((double)nevent,
		    A2Cal1::CAL | A2Cal1::CALD | A2Cal1::FC | A2Cal1::FCD | 
		    A2Cal1::LASER | A2Cal1::LASERD | A2Cal1::EMPTYADC);
  pedestal->copydata(pedeaccum,
		     A2Cal1::CAL | A2Cal1::CALD | A2Cal1::FC | A2Cal1::FCD | 
		     A2Cal1::LASER | A2Cal1::LASERD | A2Cal1::EMPTYADC);
  pedeaccum2->divide((double)nevent,
		     A2Cal1::CAL | A2Cal1::CALD | A2Cal1::FC | A2Cal1::FCD | 
		     A2Cal1::LASER | A2Cal1::LASERD | A2Cal1::EMPTYADC);
  
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  silicon_accum[il][ixy][istrip][isample]  /= (double)nevent;
	  silicon_accum2[il][ixy][istrip][isample] /= (double)nevent;
	  pedestal->silicon[il][ixy][istrip][isample]
	    = silicon_accum[il][ixy][istrip][isample];
	}
      }
    }
  }
  
  CalSigma();  // results are filled in pedesigma  
  
  // For offset subtraction After subtraction of delayed gate
  if(opoffsetsubtraction){
    pedeaccum2_1->divide((double)nevent,
			 A2Cal1::CAL | A2Cal1::FC  | A2Cal1::LASER);
    pedestal2->copydata(pedeaccum2_1,
			A2Cal1::CAL | A2Cal1::FC  | A2Cal1::LASER);
    pedeaccum2_2->divide((double)nevent,
			 A2Cal1::CAL | A2Cal1::FC  | A2Cal1::LASER );
    CalSigma2();  // results are filled in pedesigma  
  }  

  AccumClear();
  return OK;
}

// ******* A2PedeSubtract::Subtract  **********************
int A2PedeSubtract::Subtract(A2Cal1* data, A2Cal1* pede){
  // Subtraction of pedestal and calculation of average and rms of pedestal.
  // 

  // ***** PEDESTAL DATA *****
  if(data->flag_pede){
    FillPedeEvent(data);

    if(accum_nevent>0 && nevent>=accum_nevent){     
      CalPedestal();    
      if(pede!=0) pede->copydata(pedestal);
    }
  }
  
  Subtraction(data);
  return OK;
}

// ******* A2PedeSubtract::Subtraction  **********************
int A2PedeSubtract::Subtraction(A2Cal1* data){
  // Only subtraction of pedestal
  
  if( Subtraction1(data) != OK) {return ERROR;}
  if( opoffsetsubtraction ){
    if( Subtraction2(data) != OK) {return ERROR;}  
  }
  return OK;
}

int A2PedeSubtract::Subtraction1(A2Cal1* data, int op){
  
  // +++++ for calorimeter +++++
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	data->cal[it][il][ir]  -= data->cald[it][il][ir];
	data->cald[it][il][ir] -= pedestal->cald[it][il][ir];
      }
    }
  }

  // +++++ for the other ADCs +++++
  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      //data->fc[id][ich] -= pedestal->fc[id][ich];
      data->fc[id][ich]  -= data->fcd[id][ich]; 
      data->fcd[id][ich] -= pedestal->fcd[id][ich];
    }
  }
  for(int imon=0;imon<2;imon++){
    data->laser[imon]  -= data->laserd[imon];
    data->laserd[imon] -= pedestal->laserd[imon];
  }
  for(int ich=0;ich<8;ich++){
    data->emptyadc[ich] -= pedestal->emptyadc[ich];
  } 
  
  if(op==-1){return OK;} // For internal function

  // +++++ for TDC0 +++++
  // Subtract the offset of L3T[ch1]
  double tdc_base;
  if(data->tdc0flag[1][0]>=0){
    tdc_base = data->tdc0[1][0];
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
        if(data->tdc0flag[ich][ihit]<0){continue;}
        data->tdc0[ich][ihit] -= tdc_base;
      }
    }
  }

  // +++++ for Silicon +++++
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  data->silicon[il][ixy][istrip][isample]
	    -=  pedestal->silicon[il][ixy][istrip][isample];
	}
      }
    }
  }
  
  return OK;
}

int A2PedeSubtract::Subtraction2(A2Cal1* data){
  data->subtract(pedestal2, A2Cal1::CAL | A2Cal1::FC | A2Cal1::LASER);
  return OK;
}

// ******* A2PedeSubtract::WriteFile  **********************
int A2PedeSubtract::WriteFile(char filename[]){
  if(strcmp(filename,"")==0){
    strcpy(filename,DEFAULT_FILENAME);
  }
  
  TFile* file = new TFile(filename,"UPDATE");
  pedestal->Write(0,TObject::kOverwrite);
  pedesigma->Write(0,TObject::kOverwrite); 
  pedestal2->Write(0,TObject::kOverwrite);
  pedesigma2->Write(0,TObject::kOverwrite);
  file->Close();
  
  return OK;
}

// ******* A2PedeSubtract::ReadFile  **********************
int A2PedeSubtract::ReadFile(char filename[]){
  A2Cal1 *tmp;
  bool err_check = false;

  if(strcmp(filename,"")==0){
    strcpy(filename,DEFAULT_FILENAME);
  }
  
  TFile* file = new TFile(filename);
  if(file->IsZombie()){
    cerr << "[A2PedeSubtract::ReadFile] "
	 << "Cannot Open " << filename << endl;
    return ERROR;
  }
  
  if(!file->Get(PEDESTAL_NAME)){
    cerr << "[A2PedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESTAL_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (A2Cal1*) file->Get(PEDESTAL_NAME) ;  
    pedestal->copydata(tmp);
  }
  
  if(!file->Get(PEDESIGMA_NAME)){
    cerr << "[A2PedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESIGMA_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (A2Cal1*) file->Get(PEDESIGMA_NAME) ;  
    pedesigma->copydata(tmp);
  } 

  if(!file->Get(PEDESTAL2_NAME)){
    cerr << "[A2PedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESTAL2_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (A2Cal1*) file->Get(PEDESTAL2_NAME) ;  
    pedestal2->copydata(tmp);
  }
  
  if(!file->Get(PEDESIGMA2_NAME)){
    cerr << "[A2PedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESIGMA2_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (A2Cal1*) file->Get(PEDESIGMA2_NAME) ;  
    pedesigma2->copydata(tmp);
  } 
  
  file->Close();

  return OK;
}

// ********  A2PedeSubtract::AddSqare  **********
int A2PedeSubtract::AddSqare(A2Cal1* data){
  double tmp;
  
  // for Calorimeter
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	tmp = data->cal[it][il][ir];
	pedeaccum2->cal[it][il][ir] += tmp*tmp;
	tmp = data->cald[it][il][ir];
	pedeaccum2->cald[it][il][ir] += tmp*tmp;
      }
    }
  }
  
  // +++++ for the other ADCs +++++
  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      tmp =  data->fc[id][ich];
      pedeaccum2->fc[id][ich] += tmp*tmp;
      tmp =  data->fcd[id][ich];
      pedeaccum2->fcd[id][ich] += tmp*tmp;  
    }
  }
  for(int imon=0;imon<2;imon++){
    tmp = data->laser[imon];
    pedeaccum2->laser[imon] += tmp*tmp;
    tmp = data->laserd[imon];
    pedeaccum2->laserd[imon] += tmp*tmp; 
  }
  for(int ich=0;ich<8;ich++){
    tmp = data->emptyadc[ich];
    pedeaccum2->emptyadc[ich] += tmp*tmp;
  } 

  // For Silicon
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  tmp = (double)data->silicon[il][ixy][istrip][isample];
	  silicon_accum2[il][ixy][istrip][isample] += tmp*tmp;
	}
      }
    }
  } 
  return OK;
}

int A2PedeSubtract::AddSqare2(A2Cal1* data){
  double tmp;
  
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	tmp = data->cal[it][il][ir];
	pedeaccum2_2->cal[it][il][ir] += tmp*tmp;
      }
    }
  }
  
  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      tmp =  data->fc[id][ich];
      pedeaccum2_2->fc[id][ich] += tmp*tmp;
    }
  }

  for(int imon=0;imon<2;imon++){
    tmp = data->laser[imon];
    pedeaccum2_2->laser[imon] += tmp*tmp;
  }
  
  return OK;
}

int A2PedeSubtract::CalSigma(){
  double av,avs;
  if(nevent==0){return ERROR;}
  
  pedesigma->copydata(pedeaccum2,0);

  // +++++ for Calorimeter +++++++
  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	av  = pedeaccum->cal[it][il][ir];
	avs = pedeaccum2->cal[it][il][ir];
	pedesigma->cal[it][il][ir] = sqrt(avs - av*av);
	av  = pedeaccum->cald[it][il][ir];
	avs = pedeaccum2->cald[it][il][ir];
	pedesigma->cald[it][il][ir] = sqrt(avs - av*av);	
      }
    }
  }
  
  // +++++ for the other ADCs +++++
  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      av  = pedeaccum->fc[id][ich];
      avs = pedeaccum2->fc[id][ich];
      pedesigma->fc[id][ich] = sqrt(avs - av*av);

      av  = pedeaccum->fcd[id][ich] ; 
      avs = pedeaccum2->fcd[id][ich] ; 
      pedesigma->fcd[id][ich]  = sqrt(avs - av*av);
    }
  }
  for(int imon=0;imon<2;imon++){  
    av  = pedeaccum->laser[imon] ; 
    avs = pedeaccum2->laser[imon] ; 
    pedesigma->laser[imon]  = sqrt(avs - av*av);
    av  = pedeaccum->laserd[imon] ; 
    avs = pedeaccum2->laserd[imon] ; 
    pedesigma->laserd[imon]  = sqrt(avs - av*av); 
  }
  for(int ich=0;ich<8;ich++){
    av  = pedeaccum->emptyadc[ich] ; 
    avs = pedeaccum2->emptyadc[ich] ; 
    pedesigma->emptyadc[ich]  = sqrt(avs - av*av); 
  } 

  if(nevent==0){return ERROR;}
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  av  = silicon_accum[il][ixy][istrip][isample];
	  avs = silicon_accum2[il][ixy][istrip][isample];
	  pedesigma->silicon[il][ixy][istrip][isample] = (float)sqrt(avs - av*av);
	}
      }
    }
  }

  return OK;
}

int A2PedeSubtract::CalSigma2(){
  double av,avs;
  if(nevent==0){return ERROR;}
  
  pedesigma2->copydata(pedeaccum2_2,0);

  for(int it=0;it<2;it++){
    for(int il=0;il<16;il++){
      for(int ir=0;ir<2;ir++){
	av  = pedeaccum2_1->cal[it][il][ir];
	avs = pedeaccum2_2->cal[it][il][ir];
	pedesigma2->cal[it][il][ir] = sqrt(avs - av*av);	
      }
    }
  }

  for(int id=0;id<2;id++){
    for(int ich=0;ich<4;ich++){
      av  = pedeaccum2_1->fc[id][ich];
      avs = pedeaccum2_2->fc[id][ich];
      pedesigma2->fc[id][ich] = sqrt(avs - av*av);
    }
  }
  for(int imon=0;imon<2;imon++){  
    av  = pedeaccum2_1->laser[imon] ; 
    avs = pedeaccum2_2->laser[imon] ; 
    pedesigma2->laser[imon]  = sqrt(avs - av*av);
  }

  return OK;
}

#endif 
