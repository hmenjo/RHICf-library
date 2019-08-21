#ifndef __CALFSIL1CALCULATION__
#define __CALFSIL1CALCULATION__

#include "RawFSIL.hh"
#include "CalFSIL1.hh"
#include "ConPedestalFSIL.hh"

class CalFSIL1Calculation
{
protected:
  RawFSIL*            rfsil;
  CalFSIL1*           cfsil1;
  int                 tmp[5][2];

  ConPedestalFSIL*    pfsil;

public:
  CalFSIL1Calculation();
  
  int       InitCalFSIL1Cal();
  int       SetRawFSILData(RawFSIL* r);
  RawFSIL*  GetRawFSILData(){return rfsil;}
  int       SetCalFSIL1Data(CalFSIL1* c);
  CalFSIL1* GetCalFSIL1Data(){return cfsil1;}
  int       ReadPedeFileFSIL(char *file);

  ConPedestalFSIL*  GetConPedestalFSIL(){return pfsil;}
  int               SetConPedestalFSIL(ConPedestalFSIL* p){pfsil = p;return CAL01_OK;}

  int    Calculate();
  int    CalculateFSIL();
  int    DataComvert();
};

CalFSIL1Calculation::CalFSIL1Calculation(){
  InitCalFSIL1Cal();
}

int CalFSIL1Calculation::InitCalFSIL1Cal(){
  rfsil = 0;
  cfsil1 = 0;
  pfsil = new ConPedestalFSIL();
  return CAL01_OK;
}

int CalFSIL1Calculation::SetRawFSILData(RawFSIL* r){
  rfsil = r;
  return CAL01_OK;
}

int CalFSIL1Calculation::SetCalFSIL1Data(CalFSIL1* c){
  cfsil1 = c;
  return CAL01_OK;
}

int CalFSIL1Calculation::ReadPedeFileFSIL(char *file){
  return pfsil->ReadFile(file);
}

int CalFSIL1Calculation::Calculate(){
  DataComvert();
  CalculateFSIL();
  return CAL01_OK;
}

int CalFSIL1Calculation::DataComvert(){
  int k=9;   //+++ first 3 bytes are dummy +++
  cfsil1->nFSIL = 0;
  for(int ich=0; ich<1024; ich++){
    cfsil1->nFSIL++;
    
    tmp[0][0] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[1][0] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[0][0] |= (rfsil->FSIL.FSIL[k]&0x0F)<<8;
    tmp[1][0] |= (rfsil->FSIL.FSIL[k++]&0xF0)<<4;
    
    tmp[2][0] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[3][0] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[2][0] |= (rfsil->FSIL.FSIL[k]&0x0F)<<8;
    tmp[3][0] |= (rfsil->FSIL.FSIL[k++]&0xF0)<<4;
    
    tmp[4][0] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[0][1] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[4][0] |= (rfsil->FSIL.FSIL[k]&0x0F)<<8;
    tmp[0][1] |= (rfsil->FSIL.FSIL[k++]&0xF0)<<4;
    
    tmp[1][1] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[2][1] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[1][1] |= (rfsil->FSIL.FSIL[k]&0x0F)<<8;
    tmp[2][1] |= (rfsil->FSIL.FSIL[k++]&0xF0)<<4;
    tmp[3][1] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[4][1] = rfsil->FSIL.FSIL[k++]&0xFF;
    tmp[3][1] |= (rfsil->FSIL.FSIL[k]&0x0F)<<8;
    tmp[4][1] |= (rfsil->FSIL.FSIL[k++]&0xF0)<<4;
    
    for(int il=0;il<5;il++){
      for(int ixy=0;ixy<2;ixy++){
	if(ixy==0){
	  cfsil1->cFSIL[il][ixy][ich] = (double)tmp[il][ixy];
	}
	else{
	  cfsil1->cFSIL[il][ixy][ich] = -1.*(double)tmp[il][ixy];
	}
      }
    }
  }
  
  return CAL01_OK;
}

int CalFSIL1Calculation::CalculateFSIL(){
  cfsil1->Reduce(pfsil->GetPedestal());
  return CAL01_OK;
}



#endif
