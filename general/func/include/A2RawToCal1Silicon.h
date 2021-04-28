#ifndef __A2RAWTOCAL1SILICON_H__
#define __A2RAWTOCAL1SILICON_H__

//-----------------------------------------------------------------
//                      A2RawToCal1Silicon     
//-----------------------------------------------------------------

#include <TObject.h>
#include <TH1F.h>

#include <string>
#include "globaldef.h"
#include "A2Raw.h"
#include "A2Raw_pPb2013.h"
#include "A2Raw_pp2015.h"
#include "A2Raw_pPb2016.h"
#include "A2Cal1.h"
#include "silicon_data.h"

class A2RawToCal1Silicon {
 public:
  
  SILICON_RAW data;
  A2Cal1*     a2cal1;
  
  char       HybSeqMDAQ[NBOARDS][NSEC][4];
  int        id_board[NBOARDS]; 
  
  // for check of error
  int        err[NBOARDS];
  int        errold[NBOARDS];
  char       crceval[NBOARDS];
  static const unsigned char crctable[256];
  
  TH1F*      herror;

  int nconv;

 public:
  A2RawToCal1Silicon(){Initialize();}
  virtual ~A2RawToCal1Silicon(){;}
  
  void Initialize();
  
  int  Convert(TObject* raw_intput, A2Cal1* cal1);
  int  Convert_pp2010(A2Raw* raw, A2Cal1* cal1);
  int  Convert_pPb2013(A2Raw_pPb2013* raw, A2Cal1* cal1);
  int  Convert_pp2015(A2Raw_pp2015* raw, A2Cal1* cal1);
  int  Convert_pPb2016(A2Raw_pPb2016* raw, A2Cal1* cal1);

  // internal function
  void hyb_seq_decode(int,int,int*,int*,int*);
  void define_hyb_seq();
  void define_hyb_seq_pp2015();
  void read_hyb_seq(char file[256]="");
  void ExtractData();
  int  EventChk();
  int  checkSR();
  int  Check_id_board();

  // For CRC
  void CRC8_InitChecksum( unsigned char *crcvalue );
  void CRC8_Update( unsigned char *crcvalue, const unsigned char data );
  void CRC8_UpdateChecksum( unsigned char *crcvalue, const void *data, int length );
  void CRC8_FinishChecksum( unsigned char *crcvalue );
  unsigned char CRC8_BlockChecksum( const void *data, int length );
  
  std::string ErrorDecode();

  ClassDef(A2RawToCal1Silicon,1);   // Format conversion for silicon from A2Raw to A2Cal1
};

#endif
