#ifndef __A1CAL1TOCAL2_H__
#define __A1CAL1TOCAL2_H__

//-----------------------------------------------------------------
//                           A1Cal1ToCal2
//-----------------------------------------------------------------

#include <TObject.h>

#include "globaldef.h"
#include "A1Cal1.h"
#include "A1Cal2.h"
#include "ADCRange.h"

class A1Cal1ToCal2 {
 private:
  double    threshold;
  ADCRange  adcrange;
  A1Cal1    defult_pede;
  bool      use_adcrange;

 public:
  A1Cal1ToCal2(){Initialize();}
  virtual  ~A1Cal1ToCal2(){;}

  //for Online Aanlysis
  int Init();
  int Exit(){return OK;}
  int Bor(){return OK;}
  int Eor(){return OK;}
  int Loop(){return OK;}

  int       Initialize();
  ADCRange* GetADCRange(){return &adcrange;}
  void      UseADCRange(bool use=true){use_adcrange = use;}
  int       ReadADCRangeTable(char* file);
  int       SetADCRangeThreshold(double th);
  double    GetADCRangeThreshold(){return threshold;}
  int       Convert(A1Cal1* cal1, A1Cal2* cal2, A1Cal1* pede=0);
  int       InverseConvert(A1Cal2* cal2, A1Cal1* cal1, A1Cal1* pede=0);
  int       CalculateADC(A1Cal1* cal1); 
  int       CheckADCOverRange(A1Cal1* cal1);

 private:
  static const double  DEFAULT_THRESHOLD;
  static const char*   DEFAULT_ADCRANGE_FILE;
  static const int     ADC_OVERRANGE   = -5;
  static const int     SCIFI_OVERRANGE = -6;

  ClassDef(A1Cal1ToCal2,1);   // Format conversion from A1Cal1 to A1Cal2.
};


#endif 


