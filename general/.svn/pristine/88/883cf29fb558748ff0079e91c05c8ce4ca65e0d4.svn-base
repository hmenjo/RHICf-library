
#ifndef __A1RAWTOCAL1_H__
#define __A1RAWTOCAL1_H__

//-----------------------------------------------------------------
//                         A1RawToCal1  
//-----------------------------------------------------------------

#include <TObject.h>
#include "globaldef.h"
#include "A1Raw.h"
#include "A1Raw_pp2015.h"
#include "RHICfRaw_Op2017.h"
#include "A1Cal1.h"
#include "ScifiPosTable.h"

class A1RawToCal1 {
  public:
  enum RAWTOCAL_FORMAT{
    FORMAT_AUTO    = 0,       // Default
    FORMAT_OP2010  = 1,     
    FORMAT_OP2009  = 2,
    FORMAT_SPS2010 = 3,
    FORMAT_OP2015  = 5,  
    FORMAT_RHICF_OP2017 = 11
  };

 private:
  int           format;
  ScifiPosTable posSCIF;
  
 public:
  A1RawToCal1();
  virtual ~A1RawToCal1(){;}
  
  int            Initialize();
  int            Convert(TObject* raw_input, A1Cal1* cal1); 
  int            Convert_OP2009( A1Raw* raw, A1Cal1* cal1);        // for data in 2009
  int            Convert_OP2010( A1Raw* raw, A1Cal1* cal1);        // for data in 2010  
  int            Convert_SPS2010(A1Raw* raw, A1Cal1* cal1);        // for data of the beam test in 2010
  int            Convert_OP2015( A1Raw_pp2015* raw, A1Cal1* cal1); // for data in 2015
  int            Convert_RHICF_OP2017( RHICfRaw_Op2017* raw, A1Cal1* cal1); // for data of RHICf Op2017
  int            InverseConvert(A1Cal1* cal1, A1Raw* raw);
  int            InverseConvert_OP2009(A1Cal1* cal1, A1Raw* raw); // for data in 2009 
  int            InverseConvert_OP2010(A1Cal1* cal1, A1Raw* raw);  
  int            InverseConvert(A1Cal1* cal1, A1Raw_pp2015* raw); // Not yet
  int            InverseConvert_OP2015(A1Cal1* cal1, A1Raw_pp2015* raw); // Not yet 
  int            InverseConvert_RHICF_OP2017(A1Cal1* cal1, RHICfRaw_Op2017* raw); // Not yet 

  ScifiPosTable* GetScifiPosTable(){ return &posSCIF;}
  int            ReadScifiPosTable(char *file);
  int            GetFormat(){return format;}
  void           SetFormat(int f){format = f;}
  void           SerFormatOp2009(){format = FORMAT_OP2009;}
  void           SerFormatOp2010(){format = FORMAT_OP2010;}
  void           SerFormatSPS2010(){format = FORMAT_SPS2010;}
  void           SerFormatOp2015(){format = FORMAT_OP2015;} 
  void           SerFormatRHICfOp2017(){format = FORMAT_RHICF_OP2017;}
  
  //Functions for 2015 data
  unsigned int   CounterFilter(unsigned int val,int mask, int offset=0);
  unsigned int   CounterCombine(unsigned int *val);

  //for Online Aanlysis
  int Init();
  int Exit(){return OK;}
  int Bor(){return OK;}
  int Eor(){return OK;}
  int Loop(){return OK;}
  
 private:
  static const char*  DEFULT_SCIFIPOSTABLE;

  ClassDef(A1RawToCal1,2);   // Format conversion from A1Raw to A1Cal1

};


#endif
