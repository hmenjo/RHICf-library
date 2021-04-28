// ***********************************************************
// ***  Raw Class                                          ***
// ***   this class is for format SPS2006 raw data         ***
// ***  13 Sep. 06 : first edited                          ***
// ***  03 Oct. 06 : modified.                             ***
// ***               parameter definition -> sturct type   *** 
// ***********************************************************

#ifndef __RAW__
#define __RAW__

#include <iostream>
#include <iomanip>
#include <ctime>

#define  RAW_IDATAFORMAT     1
#define  RAW_DATAFORMAT   "RAW"

#define  RAW_OK      0
#define  RAW_ERROR  -1
#define  RAW_USE     1
#define  RAW_NOUSE   0

class Raw 
{
private:
public:
  int            idataformat;
  char           dataformat[20];

public:
  struct {
    Int_t           Run;
    Int_t           Number;
    UInt_t          Time;
  } Number; 
  struct {
    Int_t           nTIME;
    UInt_t          TIME[1];   //[nTIME]
  } TIME;
  struct {
    Int_t           nINP0;
    UChar_t         INP0[8];   //[nTIME]
  } INP0;
  struct {
    Int_t           nSCL0;
    UInt_t          SCL0[8];   //[nSCL0]
  } SCL0;
  struct{
    Int_t           nADC0;
    UShort_t        ADC0[64];   //[nADC0]
  } ADC0;
  struct{
    Int_t           nADC1;
    UShort_t        ADC1[64];   //[nADC1] 
  } ADC1;
  struct{
    Int_t           nADC2;
    UShort_t        ADC2[64];   //[nADC1] 
  } ADC2;
  struct{
    Int_t           nCAD0;
    UInt_t          CAD0[64];   //[nADC1] 
  } CAD0;    
  struct{
    Int_t           nCAD1;
    UInt_t          CAD1[64];   //[nADC1] 
  } CAD1;    
  struct{
    Int_t           nCAD2;
    UInt_t          CAD2[64];   //[nADC1] 
  } CAD2;  
  struct{
    Int_t           nSCIF;
    UShort_t          SCIF[512];   //[nSCIF]
  } SCIF;
  struct{
    Int_t           nFSIL;
    UShort_t        FSIL[15394]; //[nFSIL]
  } FSIL;
  struct{
    Int_t           nTDC0;
    UInt_t          TDC0[32];     //[nTDC0]
  } TDC0;
  struct{
    Int_t           nSADC;
    UShort_t        SADC[16];     //[nTDC0]
  } SADC;
  struct {
    Int_t           nARM2;        
    UChar_t         ARM2[14228]; 
  } ARM2;

public:
  Raw();
  ~Raw();

  int     Init();
  int     Clear();
  int     Copy(const Raw& obj);
  int     GetIDataFormat(){return idataformat;}
  char*   GetDataFormat(){return dataformat;}
  int     PrintStatus();

};

Raw::Raw() { 
//   Init();
  return ;
}

Raw::~Raw() {
  return ;
}

int Raw::Init(){
  idataformat = RAW_IDATAFORMAT;
  strcpy(dataformat,RAW_DATAFORMAT);
  Clear();
  return RAW_OK;
}

int Raw::Clear(){
  Number.Run = 0;
  Number.Number = 0;
  Number.Time = 0;
  TIME.nTIME = 0;
  INP0.nINP0 = 0;
  SCL0.nSCL0 = 0;
  ADC0.nADC0 = 0;
  ADC1.nADC1 = 0;
  ADC2.nADC2 = 0;
  CAD0.nCAD0 = 0;
  CAD1.nCAD1 = 0; 
  CAD2.nCAD2 = 0;
  SCIF.nSCIF = 0;
  TDC0.nTDC0 = 0;
  SADC.nSADC = 0;
  ARM2.nARM2 = 0;

  TIME.TIME[0] = 0;
  for(int i=0;i<8;i++){INP0.INP0[i]=0;}
  for(int i=0;i<64;i++){ADC0.ADC0[i]=0;} 
  for(int i=0;i<64;i++){ADC1.ADC1[i]=0;}
  for(int i=0;i<64;i++){ADC2.ADC2[i]=0;}
  for(int i=0;i<5;i++){CAD0.CAD0[i]=0;}
  for(int i=0;i<5;i++){CAD1.CAD1[i]=0;} 
  for(int i=0;i<5;i++){CAD2.CAD2[i]=0;}
  for(int i=0;i<512;i++){SCIF.SCIF[i]=0;} 
  for(int i=0;i<15394;i++){FSIL.FSIL[i]=0;}
  for(int i=0;i<32;i++){TDC0.TDC0[i]=0;}
  for(int i=0;i<16;i++){SADC.SADC[i]=0;}
  for(int i=0;i<14228;i++){ARM2.ARM2[i]=0;}
  
  return RAW_OK;  
}

int Raw::Copy(const Raw& obj){
  idataformat = obj.idataformat;
  strcpy(dataformat,obj.dataformat);
  Number.Run = obj.Number.Run;
  Number.Number = obj.Number.Number;
  Number.Time = obj.Number.Time;
  
  TIME.nTIME = obj.TIME.nTIME;
  TIME.TIME[0] = obj.TIME.TIME[0];
  
  INP0.nINP0 =  obj.INP0.nINP0;
  for(int i=0;i<INP0.nINP0;i++){
    INP0.INP0[i] =  obj.INP0.INP0[i];
  }

  SCL0.nSCL0 =  obj.SCL0.nSCL0;
  for(int i=0;i<SCL0.nSCL0;i++){
    SCL0.SCL0[i] =  obj.SCL0.SCL0[i];
  } 

  ADC0.nADC0 =  obj.ADC0.nADC0;
  for(int i=0;i<ADC0.nADC0;i++){
    ADC0.ADC0[i] =  obj.ADC0.ADC0[i];
  } 

  ADC1.nADC1 =  obj.ADC1.nADC1;
  for(int i=0;i<ADC1.nADC1;i++){
    ADC1.ADC1[i] =  obj.ADC1.ADC1[i];
  }   
  
  ADC2.nADC2 =  obj.ADC2.nADC2;
  for(int i=0;i<ADC2.nADC2;i++){
    ADC2.ADC2[i] =  obj.ADC2.ADC2[i];
  }   
  
  CAD0.nCAD0 =  obj.CAD0.nCAD0;
  for(int i=0;i<CAD0.nCAD0;i++){
    CAD0.CAD0[i] =  obj.CAD0.CAD0[i];
  }  

  CAD1.nCAD1 =  obj.CAD1.nCAD1;
  for(int i=0;i<CAD1.nCAD1;i++){
    CAD1.CAD1[i] =  obj.CAD1.CAD1[i];
  } 
  
  CAD2.nCAD2 =  obj.CAD2.nCAD2;
  for(int i=0;i<CAD1.nCAD1;i++){
    CAD2.CAD2[i] =  obj.CAD2.CAD2[i];
  }
  
  SCIF.nSCIF =  obj.SCIF.nSCIF;
  for(int i=0;i<SCIF.nSCIF;i++){
    SCIF.SCIF[i] =  obj.SCIF.SCIF[i];
  }    

  FSIL.nFSIL =  obj.FSIL.nFSIL;
  for(int i=0;i<FSIL.nFSIL;i++){
    FSIL.FSIL[i] =  obj.FSIL.FSIL[i];
  }  
  
  TDC0.nTDC0 =  obj.TDC0.nTDC0;
  for(int i=0;i<TDC0.nTDC0;i++){
    TDC0.TDC0[i] =  obj.TDC0.TDC0[i];
  }    

  ARM2.nARM2 = obj.ARM2.nARM2;
  for(int i=0;i<ARM2.nARM2;i++){
    ARM2.ARM2[i] =  obj.ARM2.ARM2[i];
  }  
  
  return RAW_OK;
}

int Raw::PrintStatus(){
  struct tm *lt;
  time_t t = (time_t)TIME.TIME[0];
  lt = gmtime(&(t));
  cout << "Format:  " << dataformat << endl;
  cout << " Run: " << setw(4) << Number.Run << "    " 
       << " Event: " << setw(6) << Number.Number << endl
       << " Time(UT):     " << asctime(lt) 
       << " nTIME: " << setw(5) << TIME.nTIME 
       << " nINP0: " << setw(5) << INP0.nINP0 
       << endl
       << " nSCL0: " << setw(5) << SCL0.nSCL0 
       << " nADC0: " << setw(5) << ADC0.nADC0
       << " nADC1: " << setw(5) << ADC1.nADC1
       << " nADC2: " << setw(5) << ADC2.nADC2
       << endl
       << " nCAD0: " << setw(5) << CAD0.nCAD0
       << " nCAD1: " << setw(5) << CAD1.nCAD1
       << " nCAD2: " << setw(5) << CAD2.nCAD2
       << endl
       << " nSCIF: " << setw(5) << SCIF.nSCIF
       << " nFSIL: " << setw(5) << FSIL.nFSIL
       << " nTDC0: " << setw(5) << TDC0.nTDC0 
       << " nSADC: " << setw(5) << SADC.nSADC 	    
       << endl
       << " nARM2: " << setw(5) << ARM2.nARM2 	    
       << endl;
  return RAW_OK;
}

#endif
