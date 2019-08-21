#ifndef __CALFSIL1__
#define __CALFSIL1__

#define  CALFSIL1_IDATAFORMAT     32
#define  CALFSIL1_DATAFORMAT "CALFSIL1"

#include "Cal01.hh"

class CalFSIL1
{
private:
  int       idataformat;
  char      dataformat[20];

public: 
  Int_t     nFSIL;
  Double_t  cFSIL[5][2][1024]; // [layer][xy][channel]

public:
  CalFSIL1();
  int Init();
  int Clear();
  int Copy(CalFSIL1 *obj);
  int Reduce(CalFSIL1 *obj);  
  int PrintStatus();

  int   GetIDataFormat(){return idataformat;}
  char* GetDataFormat(){return dataformat;}
};

CalFSIL1::CalFSIL1(){
  Init();
}

int CalFSIL1::Init(){
  idataformat = CALFSIL1_IDATAFORMAT;
  strcpy(dataformat,CALFSIL1_DATAFORMAT);
  Clear();
  return CAL01_OK;
}

int CalFSIL1::Clear(){
  nFSIL = 0;
  for(int il=0;il<5;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<1024;ich++){
	cFSIL[il][ixy][ich] = 0.;
      }
    }
  }
  return CAL01_OK;
}

int CalFSIL1::Copy(CalFSIL1 *obj){
  nFSIL = obj->nFSIL; 
  for(int il=0;il<5;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<1024;ich++){
	cFSIL[il][ixy][ich] = obj->cFSIL[il][ixy][ich];
      }
    }
  }
  return CAL01_OK; 
}

int CalFSIL1::Reduce(CalFSIL1 *obj){
  for(int il=0;il<5;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int ich=0;ich<1024;ich++){
	cFSIL[il][ixy][ich] -= obj->cFSIL[il][ixy][ich];
      }
    }
  }
  return CAL01_OK; 
}

int CalFSIL1::PrintStatus(){
  cout << "Format:  " << dataformat << endl
       << " nFSIL: " << setw(3) << nFSIL << endl;
  return CAL01_OK;
}

#endif
