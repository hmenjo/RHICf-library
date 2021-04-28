#ifndef __PMTSATUCORRECTION_H__
#define __PMTSATUCORRECTION_H__

//-----------------------------------------------------------------------
//                            PMTSatuCorrection
//            For detail, see PMTSatuCorrection.cpp or Online Manual
//-----------------------------------------------------------------------

#include <TObject.h>

#include "globaldef.h"
#include "PMTSatu.h"
#include "A1Cal1.h"
#include "A1Cal2.h"
#include "A2Cal1.h"
#include "A2Cal2.h"
#include "A1GainCalibration.h"
#include "A2GainCalibration.h"

class PMTSatuCorrection : public PMTSatu {
  
 private:
  int  hvtable[2][2][16];

 public:
  PMTSatuCorrection();
  PMTSatuCorrection( char* tpath, char* fname ); 
  virtual ~PMTSatuCorrection();
  
  int Initialize(char *tpath="", char* fname=""); 
  int ReadHVTable(A1GainCalibration* gain);
  int ReadHVTable(A2GainCalibration* gain);
  int ReadHVTable(char filename[],int arm=-1);

  int Calculate(A1Cal1* );
  int Calculate(A2Cal1* );
  int Calculate(A1Cal2* );
  int Calculate(A2Cal2* );
  int Correct(A1Cal1* cal){return Calculate(cal);}
  int Correct(A2Cal1* cal){return Calculate(cal);}
  int Correct(A1Cal2* cal){return Calculate(cal);}
  int Correct(A2Cal2* cal){return Calculate(cal);}
  
  int InvCalculate(A1Cal1* );
  int InvCalculate(A2Cal1* );
  int InvCalculate(A1Cal2* );
  int InvCalculate(A2Cal2* );
  
  ClassDef(PMTSatuCorrection,1);
};



#endif
