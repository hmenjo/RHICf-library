#ifndef __A2PEDESUBTACT_H__
#define __A2PEDESUBTACT_H__

//-----------------------------------------------------------------
//                           A2PedeSubtract
//-----------------------------------------------------------------

#include <TObject.h>
#include <TFile.h>
#include "globaldef.h"
#include "A2Cal1.h"

class A2PedeSubtract {
 private:
  int    nevent;
  A2Cal1 *pedeaccum;
  A2Cal1 *pedeaccum2;      // contain silicon*2
  A2Cal1 *pedestal;
  A2Cal1 *pedesigma;       // contain RMS of silicon
  
  // For subtraction of offset after subtraction by delayed gate
  // if opoffsetsubtraction is true (default), subtract the offset. 
  bool    opoffsetsubtraction;
  A2Cal1 *pedeaccum2_1;
  A2Cal1 *pedeaccum2_2;    // contain silicon*2
  A2Cal1 *pedestal2;       // 
  A2Cal1 *pedesigma2;      // contain RMS of silicon
  A2Cal1 datatmp;

  double silicon_accum[4][2][384][3];
  double silicon_accum2[4][2][384][3];

  int    accum_nevent;     // number of accumrated event for pedestal.
  
 public:
  A2PedeSubtract();
  virtual ~A2PedeSubtract();
  
  int  Initialize(); 
  int  SetPedestal(A2Cal1* p){pedestal->copydata(p);return OK;}
  int  SetAccumNEvent(int n){accum_nevent=n; return OK;}
  int  AccumClear();
  int  FillPedeEvent(A2Cal1* data);
  int  CalPedestal();
  int  Subtract(A2Cal1* data, A2Cal1* pede=0); // Subtraction including cal. of pedestal.   
  int  Subtraction(A2Cal1* data);              // Only subtraction
  int  Subtraction1(A2Cal1* data, int op=0);   // op : for internal use. 
  int  Subtraction2(A2Cal1* data);             // Offset subtraction
  void SetOffsetSubtraction(bool b=true){opoffsetsubtraction = b;}
  bool GetOffsetSubtraction(){return opoffsetsubtraction;} 
  int  WriteFile(char filename[]=""); 
  int  ReadFile(char filename[]="");

  A2Cal1* GetPedestal()  {return pedestal;}
  A2Cal1* GetPedesigma() {return pedesigma;}
  A2Cal1* GetPedestal2() {return pedestal2;}
  A2Cal1* GetPedesigma2(){return pedesigma2;}
  
  // internal function
  int  AddSqare(A2Cal1* data);  
  int  AddSqare2(A2Cal1* data); // After subtraction od delayed gate
  int  CalSigma();             
  int  CalSigma2();             // After subtraction od delayed gate

  // for online analysis
  int Init(A2Cal1* pede = 0);
  int Exit();
  int Bor();
  int Eor();
  int Loop(A2Cal1* data,A2Cal1* pede){return Subtract(data,pede);}
  
 private:
  static const int    DEFAULT_ACCUM_NEVENT = 100;
  static const char*  PEDESTAL_NAME;
  static const char*  PEDESTAL_TITLE;
  static const char*  PEDESIGMA_NAME;
  static const char*  PEDESIGMA_TITLE; 
  static const char*  PEDESTAL2_NAME;
  static const char*  PEDESTAL2_TITLE;
  static const char*  PEDESIGMA2_NAME;
  static const char*  PEDESIGMA2_TITLE;
  static const char*  DEFAULT_FILENAME;

  ClassDef(A2PedeSubtract,1);   // Pedestal subtraction for Arm2
};

#endif
