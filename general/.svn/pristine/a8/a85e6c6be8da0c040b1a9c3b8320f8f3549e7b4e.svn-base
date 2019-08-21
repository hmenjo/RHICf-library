#ifndef __A2RAWTOCAL1_H__
#define __A2RAWTOCAL1_H__

//-----------------------------------------------------------------
//                         A2RawToCal1  
//-----------------------------------------------------------------

#include <TObject.h>

#include "globaldef.h"
#include "A2Raw.h"
#include "A2Raw_pPb2013.h"
#include "A2Raw_pp2015.h"
#include "A2Raw_pPb2016.h"
#include "A2Cal1.h"

class A2RawToCal1 {
 public:
  enum RAWTOCAL_FORMAT{
    FORMAT_AUTO    = 0,       // Default
    FORMAT_OP2010  = 1,     
    FORMAT_OP2009  = 2,
    FORMAT_SPS2010 = 3,
    FORMAT_PPB2013 = 4,
    FORMAT_OP2015  = 5,  
  };

 private:
  int           format;

 public:
  A2RawToCal1();
  virtual ~A2RawToCal1(){;}
 
  int  Initialize();
  int  Convert(TObject* raw_input, A2Cal1* cal1);
  int  Convert_OP2009(A2Raw* raw, A2Cal1* cal1); // for data in 2009
  int  Convert_OP2010(A2Raw* raw, A2Cal1* cal1); // for data in 2010
  int  Convert_SPS2010(A2Raw* raw, A2Cal1* cal1);// for data of the beam test in 2010  
  int  Convert_pPb2013(A2Raw_pPb2013* raw, A2Cal1* cal1); // For data of pPb 2013
  int  Convert_OP2015(A2Raw_pp2015* raw, A2Cal1* cal1);   // For data taken in 2015 
  int  Convert_pPb2016(A2Raw_pPb2016* raw, A2Cal1* cal1);   // For data taken in 2015 
  int  InverseConvert(A2Cal1* cal1, A2Raw* raw);
  int  InverseConvert_OP2009(A2Cal1* cal1, A2Raw* raw); // for data in 2009 
  int  InverseConvert_OP2010(A2Cal1* cal1, A2Raw* raw); 
  int  InverseConvert_OP2015(A2Cal1* cal1, A2Raw* raw); 
  int  GetFormat(){return format;}
  void SetFormat(int f){format = f;}
  void SerFormatOp2009(){format = FORMAT_OP2009;}
  void SerFormatOp2010(){format = FORMAT_OP2010;}
  void SerFormatSPS2010(){format = FORMAT_SPS2010;}
  void SerFormatOp2015(){format = FORMAT_OP2015;}

  //Functions for 2015 data
  unsigned int   CounterFilter(unsigned int val,int mask, int offset=0);
  unsigned int   CounterCombine(unsigned int *val);

  //for Online Aanlysis
  int Init(){return OK;}
  int Exit(){return OK;}
  int Bor(){return OK;}
  int Eor(){return OK;}
  int Loop(){return OK;}
  
  
  ClassDef(A2RawToCal1,2);   // Format conversion from A2Raw to A2Cal1
};

#endif
