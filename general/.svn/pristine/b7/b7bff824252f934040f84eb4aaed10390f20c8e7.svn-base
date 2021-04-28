#ifndef __CAL01__
#define __CAL01__

#include <iostream>
#include <iomanip>
using namespace std;

#define  CAL01_IDATAFORMAT     2
#define  CAL01_DATAFORMAT "CAL01"

#define  CAL01_OK      0
#define  CAL01_ERROR  -1
#define  CAL01_USE     1
#define  CAL01_NOUSE   0

class Cal01
{
private:
  int       idataformat;
  char      dataformat[20];

public:
  Int_t     Run;
  Int_t     Number;

  Int_t     cADC;
  Double_t  cADC0L[16];   // ADC0 Low  Range
  Double_t  cADC0H[16];   // ADC0 High Range
  Double_t  cADC1L[16];   // ADC1 Low  Range
  Double_t  cADC1H[16];   // ADC1 High Range
  Double_t  cADC2L[16];   // ADC1 Low  Range
  Double_t  cADC2H[16];   // ADC1 High Range
  Double_t  cADC0W[16];   // ADC0 Conbine Low with High
  Double_t  cADC1W[16];   // ADC1 Conbine Low with High
  Double_t  cADC2W[16];   // ADC1 Conbine Low with High
   
  Int_t     cSCIF;
  Double_t  cSCIF0[4][2][20];  // Scifi 20mm Tower
  Double_t  cSCIF1[4][2][40];  // Scifi 40mm Tower
public:
  Cal01();
  int Init();
  int Clear();
  int Copy(Cal01 *obj);
  int PrintStatus();
  
  int   GetIDataFormat(){return idataformat;}
  char* GetDataFormat(){return dataformat;}
};

Cal01::Cal01(){
  Init();
}

int Cal01::Init(){
  idataformat = CAL01_IDATAFORMAT;
  strcpy(dataformat,CAL01_DATAFORMAT);
  Clear();
  return CAL01_OK;
}
int Cal01::Clear(){
  Run = 0;
  Number = 0;
  
  cADC = CAL01_USE;
  for(int i=0;i<16;i++){
    cADC0L[i] = 0.;
    cADC0H[i] = 0.;
    cADC1L[i] = 0.;
    cADC1H[i] = 0.;
    cADC2L[i] = 0.;
    cADC2H[i] = 0.;
    cADC0W[i] = 0.;
    cADC1W[i] = 0.;
    cADC2W[i] = 0.;
  }
  cSCIF = CAL01_USE;
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ipos=0;ipos<20;ipos++){
	cSCIF0[il][ixy][ipos]=0.;
      }
      for(int ipos=0;ipos<40;ipos++){
	cSCIF1[il][ixy][ipos]=0.;
      }
    }
  }
  return CAL01_OK;
}

int Cal01::Copy(Cal01 *obj){
  Run = obj->Run;
  Number = obj->Number;
  cADC = obj->cADC;
  for(int i=0;i<16;i++){
    cADC0L[i] = obj->cADC0L[i];
    cADC0H[i] = obj->cADC0H[i];
    cADC1L[i] = obj->cADC1L[i];
    cADC1H[i] = obj->cADC1H[i];
    cADC2L[i] = obj->cADC2L[i];
    cADC2H[i] = obj->cADC2H[i];
    cADC0W[i] = obj->cADC0W[i];
    cADC1W[i] = obj->cADC1W[i];
    cADC2W[i] = obj->cADC2W[i];
  } 
  cSCIF = obj->cSCIF;
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ipos=0;ipos<20;ipos++){
	cSCIF0[il][ixy][ipos]=obj->cSCIF0[il][ixy][ipos];
      }
      for(int ipos=0;ipos<40;ipos++){
	cSCIF1[il][ixy][ipos]=obj->cSCIF1[il][ixy][ipos];
      }
    }
  }
  return CAL01_OK;
}

int Cal01::PrintStatus(){
  cout << "Format:  " << dataformat << endl
       << " Run: " << setw(4) << Run << "   "
       << " Event: " << setw(6) << Number << endl
       << " cADC: " << setw(3) << cADC << "   "
       << " cSCIF: " << setw(3) << cSCIF << endl;
  return CAL01_OK;
}

#endif
