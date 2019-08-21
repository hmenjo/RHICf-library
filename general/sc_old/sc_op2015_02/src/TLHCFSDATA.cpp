#ifndef __TLHCFSDATA_CPP__
#define __TLHCFSDATA_CPP__

#include "TLHCFSDATA.h"

#if !defined(__CINT__)
ClassImp(TLHCFSDATA);  
#endif

// *****************************************************************
// ***   TLHCFSDATA::clear   ***************************************
// *****************************************************************
void TLHCFSDATA::clear(){
  run = 0;
  number = 0;
  DataClear();
}


// *****************************************************************
// ***   TLHCFSDATA::DataClear   ***********************************
// *****************************************************************
void TLHCFSDATA::DataClear(){

  data.time    =  0;
  data.number  =  0;
  
  CPWS_CH* data_ch = NULL;
  // ==========  CPWS1 =================================================
  data.cpws1.status = 0;
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==6) break;
      if(is==4) break;
      if(is==5 && ich==6) break;
      
      if(is==0){
	data_ch = &(data.cpws1.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws1.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws1.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws1.slot3[ich]);
      }
      if(is==5){
	data_ch = &(data.cpws1.slot5[ich]);
      }
      data_ch->vmon  =  0.;
      data_ch->imon  =  0.;
      data_ch->status = 0;
    }
    data.cpws1.temperature[is] = 0.;
  }  
  
  // ==========  CPWS2 ================================================= 
  data.cpws2.status = 0;
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==12) break;
      if(is==4 && ich==6) break;
      if(is==5) break;
      
      if(is==0){
	data_ch = &(data.cpws2.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws2.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws2.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws2.slot3[ich]);
      }
      if(is==4){
	data_ch = &(data.cpws2.slot4[ich]);
      }
      data_ch->vmon =  0.;
      data_ch->imon =  0.;
   
    }
    data.cpws2.temperature[is] = 0. ;
  }
  
  // ==========  Agilent ============================================
  data.ag.status = 0;
  for(int im=0;im<4;im++){
    data.ag.mod[im].status = 0;
    for(int ich=0;ich<4;ich++){
      data.ag.mod[im].ch[ich].vmon  = 0.;
      data.ag.mod[im].ch[ich].imon  = 0 ;
      data.ag.mod[im].ch[ich].status = 0; 
    }
  }
  
  // ==========  TRHX ============================================
  data.trhx.status = 0;
  for(int ich=0;ich<12;ich++){
    data.trhx.temp[ich] = 0;
  }

  // ==========  Encoder ============================================
  data.encoder.status = 0;
  data.encoder.encoder1 = 0.;
  data.encoder.encoder2 = 0.;
  
  // ==========  PCI-ADC ============================================
  data.adc.status = 0;
  for(int i=0;i<16;i++){
    data.adc.adc[i] = 0;
    data.adc.vol[i] = 0.;
    data.adc.cal[i] = 0.;
  }
  

}

// *****************************************************************
// ***   TLHCFSDATA::Add  ******************************************
// *****************************************************************
void TLHCFSDATA::Add(TLHCFSDATA* d){
  LHCFSDATA* add = d->GetData();
  
  data.time   += add->time;
  data.number += add->number;
  

  CPWS_CH* data_ch = NULL;
  CPWS_CH* add_ch =NULL;
  
  // ==========  CPWS1 =================================================
  data.cpws1.status |=  add->cpws1.status;
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==6) break;
      if(is==4) break;
      if(is==5 && ich==6) break;
      
      if(is==0){
	data_ch = &(data.cpws1.slot0[ich]);
	add_ch  = &(add->cpws1.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws1.slot1[ich]);
	add_ch  = &(add->cpws1.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws1.slot2[ich]);
	add_ch  = &(add->cpws1.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws1.slot3[ich]);
	add_ch  = &(add->cpws1.slot3[ich]);
      }
      if(is==5){
	data_ch = &(data.cpws1.slot5[ich]);
	add_ch  = &(add->cpws1.slot5[ich]);
      }
      data_ch->vmon +=  add_ch->vmon;
      data_ch->imon +=  add_ch->imon;
      data_ch->status |=  add_ch->status;
    }
    data.cpws1.temperature[is] += add->cpws1.temperature[is];
  }  
  
  // ==========  CPWS2 ================================================= 
  data.cpws2.status |=  add->cpws2.status;
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==12) break;
      if(is==4 && ich==6) break;
      if(is==5) break;
      
      if(is==0){
	data_ch = &(data.cpws2.slot0[ich]);
	add_ch  = &(add->cpws2.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws2.slot1[ich]);
	add_ch  = &(add->cpws2.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws2.slot2[ich]);
	add_ch  = &(add->cpws2.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws2.slot3[ich]);
	add_ch  = &(add->cpws2.slot3[ich]);
      }
      if(is==4){
	data_ch = &(data.cpws2.slot4[ich]);
	add_ch  = &(add->cpws2.slot4[ich]);
      }
      data_ch->vmon +=  add_ch->vmon;
      data_ch->imon +=  add_ch->imon;
      data_ch->status |=  add_ch->status;
    }
    data.cpws2.temperature[is] += add->cpws2.temperature[is];
  }

  // ==========  Agilent ============================================
  data.ag.status |= add->ag.status;
  for(int im=0;im<4;im++){
    data.ag.mod[im].status |=  add->ag.mod[im].status;
    for(int ich=0;ich<4;ich++){
      data.ag.mod[im].ch[ich].vmon  += add->ag.mod[im].ch[ich].vmon;
      data.ag.mod[im].ch[ich].imon  += add->ag.mod[im].ch[ich].imon;
      data.ag.mod[im].ch[ich].status |= add->ag.mod[im].ch[ich].status; 
    }
  }
  
  // ==========  TRHX ============================================
  data.trhx.status |= add->trhx.status;
  for(int ich=0;ich<12;ich++){
    data.trhx.temp[ich] += add->trhx.temp[ich];
  }
  
  // ==========  Encoder ============================================
  data.encoder.status |= add->encoder.status;
  data.encoder.encoder1 += add->encoder.encoder1;
  data.encoder.encoder2 += add->encoder.encoder2;
  
  // ==========  PCI-ADC ============================================
  data.adc.status |= add->adc.status;
  for(int i=0;i<16;i++){
    data.adc.adc[i] += add->adc.adc[i];
    data.adc.vol[i] += add->adc.vol[i];
    data.adc.cal[i] += add->adc.cal[i];
  }
  
}

// *****************************************************************
// ***   TLHCFSDATA::Divide  ***************************************
// *****************************************************************
void TLHCFSDATA::Divide(double div){

  data.time    =  (int)((double)data.time/div);
  data.number  =  (int)((double)data.number/div);
  CPWS_CH* data_ch = NULL;
  // ==========  CPWS1 =================================================
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==6) break;
      if(is==4) break;
      if(is==5 && ich==6) break;
      
      if(is==0){
	data_ch = &(data.cpws1.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws1.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws1.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws1.slot3[ich]);
      }
      if(is==5){
	data_ch = &(data.cpws1.slot5[ich]);
      }
      data_ch->vmon /=  div;
      data_ch->imon /=  div;
    }
    data.cpws1.temperature[is] /= div;
  }  
  
  // ==========  CPWS2 =================================================
  for(int is=0;is<6;is++){
    for(int ich=0;ich<12;ich++){
      if(is==0 && ich==12) break;
      if(is==1 && ich==12) break;
      if(is==2 && ich==12) break;
      if(is==3 && ich==12) break;
      if(is==4 && ich==6) break;
      if(is==5) break;
      
      if(is==0){
	data_ch = &(data.cpws2.slot0[ich]);
      }
      if(is==1){
	data_ch = &(data.cpws2.slot1[ich]);
      }
      if(is==2){
	data_ch = &(data.cpws2.slot2[ich]);
      }
      if(is==3){
	data_ch = &(data.cpws2.slot3[ich]);
      }
      if(is==4){
	data_ch = &(data.cpws2.slot4[ich]);
      }
      data_ch->vmon /=  div;
      data_ch->imon /=  div;
   
    }
    data.cpws2.temperature[is] /= div ;
  }


  // ==========  Agilent ============================================
  for(int im=0;im<4;im++){
    for(int ich=0;ich<4;ich++){
      data.ag.mod[im].ch[ich].vmon  /= div;
      data.ag.mod[im].ch[ich].imon  /= div;
    }
  }
  
  // ==========  TRHX ============================================
  //data.trhx.status = 0;
  for(int ich=0;ich<12;ich++){
    data.trhx.temp[ich] /= div;
  } 
  
  // ==========  Encoder ============================================
  //data.encoder.status = 0;
  data.encoder.encoder1 /= div;
  data.encoder.encoder2 /= div;
  
  // ==========  PCI-ADC ============================================
  //data.adc.status = 0;
  for(int i=0;i<16;i++){
    data.adc.adc[i]  = (unsigned short)(data.adc.adc[i]/div);
    data.adc.vol[i] /= div;
    data.adc.cal[i] /= div;
  }
  

}



#endif
