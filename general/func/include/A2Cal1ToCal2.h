#ifndef __A2CAL1TOCAL2_H__
#define __A2CAL1TOCAL2_H__

//-----------------------------------------------------------------
//                          A2Cal1ToCal2 
//-----------------------------------------------------------------

#include <TObject.h>

#include "globaldef.h"
#include "A2Cal1.h"
#include "A2Cal2.h"
#include "ADCRange.h"

class A2Cal1ToCal2 {
 private:
  double    threshold;
  ADCRange  adcrange;
  A2Cal1    defult_pede;
  bool      use_adcrange;
  
 public:
  A2Cal1ToCal2(){Initialize();}
  virtual ~A2Cal1ToCal2(){;}

  int       Initialize();
  ADCRange* GetADCRange(){return &adcrange;} 
  void      UseADCRange(bool use=true){use_adcrange = use;}
  int       ReadADCRangeTable(char* file);
  int       SetADCRangeThreshold(double th);
  double    GetADCRangeThreshold(){return threshold;}
  int       Convert(A2Cal1* cal1, A2Cal2* cal2, A2Cal1* pede=0);
  int       InverseConvert(A2Cal2* cal2, A2Cal1* cal1, A2Cal1* pede=0);
  int       CalculateADC(A2Cal1* cal1); 
  int       CheckADCOverRange(A2Cal1* cal1);

  //for Online Aanlysis
  int Init();
  int Exit(){return OK;}
  int Bor(){return OK;}
  int Eor(){return OK;}
  int Loop(){return OK;}

 private:
  static const double  DEFAULT_THRESHOLD;
  static const char*   DEFAULT_ADCRANGE_FILE; 
  static const int     ADC_OVERRANGE   = -5;
  static const int     SCIFI_OVERRANGE = -6; 

  ClassDef(A2Cal1ToCal2,1);   // Format conversion from A2Cal1 to A2Cal2
};

#endif 

