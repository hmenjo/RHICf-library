#ifndef __CAL01CALCULATION__
#define __CAL01CALCULATION__

#include "Raw.hh"
#include "Cal01.hh"

#include "ConPedestalADC.hh"
#include "ConPedestalSCIF.hh"
#include "ScifiPosTable.hh"
#include "ADCRange.hh"

class Cal01Calculation 
{
protected:
  Raw*             rdata;
  Cal01*           c01data;

  int              detector;
  ConPedestalADC   peADC;
  ConPedestalSCIF  peSCIF;
  ScifiPosTable    posSCIF;
  ADCRange         rADC;

public:
  Cal01Calculation();
  
  int    InitCal01Cal();

  int    SetRawData(Raw* r);
  Raw*   GetRawData(){return rdata;}
  int    SetCal01Data(Cal01* c);
  Cal01* GetCal01Data(){return c01data;}  
  
  int    SetDetector(int d){detector = d;return CAL01_OK;}
  int    ReadPedeFileADC(char *file);
  int    ReadPedeFileSCIF(char *file);
  int    ReadScifiPosTable(char *file);
  int    ReadADCRangeTable(char *file);
  
  ConPedestalADC*  GetConPedestalADC(){ return  &peADC;}
  ConPedestalSCIF* GetConPedestalSCIF(){ return &peSCIF;}
  ScifiPosTable*   GetScifiPosTable(){return &posSCIF;}
  ADCRange*        GetADCRange(){return &rADC;}


  int    Calculate();
  int    CalculateHeader();
  int    CalculateADC();
  int    CalculateSCIF();
};

Cal01Calculation::Cal01Calculation(){
  InitCal01Cal();
}

int Cal01Calculation::InitCal01Cal(){
  detector = 0;
  rdata = NULL;
  c01data = NULL;
  return CAL01_OK;
}

int Cal01Calculation::SetRawData(Raw* r){
  rdata = r;
  return CAL01_OK;
}

int Cal01Calculation::SetCal01Data(Cal01* c){
  c01data = c;
  return CAL01_OK;
}  

int Cal01Calculation::ReadPedeFileADC(char* file){
  return peADC.ReadFile(file);
}

int Cal01Calculation::ReadPedeFileSCIF(char* file){
  return peSCIF.ReadFile(file);
}

int Cal01Calculation::ReadScifiPosTable(char *file){
  return posSCIF.ReadPositionTable(file);
}

int Cal01Calculation::ReadADCRangeTable(char *file){
  return rADC.ReadFile(file);
}

int Cal01Calculation::Calculate(){
  if( CalculateHeader()==CAL01_OK && 
      CalculateADC() == CAL01_OK &&
      CalculateSCIF() == CAL01_OK){
    return CAL01_OK;
  }
  return  CAL01_ERROR;
}

int Cal01Calculation::CalculateHeader(){
  if(rdata ==NULL || c01data==NULL){
    cerr << "[Cal01Calculation::CalculateHeader]" 
	 << " Please Set Raw and Cal01."<< endl;
    return CAL01_ERROR;
  }

  c01data->Run = rdata->Number.Run;
  c01data->Number = rdata->Number.Number;
  return CAL01_OK;
}

int Cal01Calculation::CalculateADC(){
  if(rdata ==NULL || c01data==NULL){
    cerr << "[Cal01Calculation::CalculateADC]" 
	 << " Please Set Raw and Cal01."<< endl;
    return CAL01_ERROR;
  }
  
  if(rdata->ADC0.nADC0==0 || rdata->ADC1.nADC1==0){
    c01data->cADC = CAL01_NOUSE;
    return CAL01_ERROR;
  }

  // convert Raw->Cal01
  for(int i=0;i<32;i++){
    if(i%2==0){ 
      c01data->cADC0H[i/2] = rdata->ADC0.ADC0[i];
      c01data->cADC1H[i/2] = rdata->ADC1.ADC1[i];
      c01data->cADC2H[i/2] = rdata->ADC2.ADC2[i];
    }
    else if(i%2==1){
      c01data->cADC0L[i/2] = rdata->ADC0.ADC0[i];
      c01data->cADC1L[i/2] = rdata->ADC1.ADC1[i];
      c01data->cADC2L[i/2] = rdata->ADC2.ADC2[i];
    }
  }
  
  // ADC Range 
  if(detector==1){
    for(int i=0;i<16;i++){
      c01data->cADC0W[i] = rADC.Get(0,i,
				    c01data->cADC0L[i],
				    c01data->cADC0H[i]);
      c01data->cADC1W[i] = rADC.Get(1,i,
				    c01data->cADC1L[i],
				    c01data->cADC1H[i]);
      c01data->cADC2W[i] = rADC.Get(2,i,
				    c01data->cADC2L[i],
				    c01data->cADC2H[i]); 
    }
  }
  else if(detector==2){ 
    for(int i=0;i<16;i++){
      c01data->cADC0W[i] = rADC.Get(2,i,
				    c01data->cADC0L[i],
				    c01data->cADC0H[i]);
      c01data->cADC1W[i] = rADC.Get(3,i,
				    c01data->cADC1L[i],
				    c01data->cADC1H[i]);
      c01data->cADC2W[i] = rADC.Get(0,i,
				    c01data->cADC2L[i],
				    c01data->cADC2H[i]); 
    }
  }
  else{  
    for(int i=0;i<16;i++){
      c01data->cADC0W[i] = c01data->cADC0L[i];
      c01data->cADC1W[i] = c01data->cADC1L[i];  
      c01data->cADC2W[i] = c01data->cADC2L[i];  
    }
  }
  
  // pedestal subtaction
  for(int i=0;i<16;i++){ 
    c01data->cADC0H[i] -= peADC.GetPedestal(0,i*2);
    c01data->cADC0L[i] -= peADC.GetPedestal(0,i*2+1);
    c01data->cADC0W[i] -= peADC.GetPedestal(0,i*2+1);
    c01data->cADC1H[i] -= peADC.GetPedestal(1,i*2);
    c01data->cADC1L[i] -= peADC.GetPedestal(1,i*2+1);
    c01data->cADC1W[i] -= peADC.GetPedestal(1,i*2+1); 
    c01data->cADC2H[i] -= peADC.GetPedestal(2,i*2);
    c01data->cADC2L[i] -= peADC.GetPedestal(2,i*2+1);
    c01data->cADC2W[i] -= peADC.GetPedestal(2,i*2+1);  
  } 

  c01data->cADC = CAL01_USE;
  
  return CAL01_OK;
}

int Cal01Calculation::CalculateSCIF(){
  if(rdata ==NULL || c01data==NULL){
    cerr << "[Cal01Calculation::CalculateSCIF]" 
	 << " Please Set Raw and Cal01."<< endl;
    return CAL01_ERROR;
  }
  
  if(rdata->SCIF.nSCIF<512){
    c01data->cSCIF = CAL01_NOUSE;
    return CAL01_ERROR;
  }
  
  int iscif;
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ipos=0;ipos<20;ipos++){ 
	iscif = posSCIF.GetChannel(0,il,ixy,ipos); 
        c01data->cSCIF0[il][ixy][ipos]
	  = rdata->SCIF.SCIF[iscif] - peSCIF.GetPedestal(iscif);
      }
      for(int ipos=0;ipos<40;ipos++){
	iscif = posSCIF.GetChannel(1,il,ixy,ipos); 
        c01data->cSCIF1[il][ixy][ipos] 
	  = rdata->SCIF.SCIF[iscif] - peSCIF.GetPedestal(iscif);
      }
    }
  }
  c01data->cSCIF = CAL01_USE;

  return CAL01_OK;
}  

#endif
