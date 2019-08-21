#ifndef __A1CAL2M_H__
#define __A1CAL2M_H__

// --------------------------------------------------------------------
//                               A1Cal2M
//                       This is a modified A1Cal2 
//             For detail, see A1Cal2.cpp or Online Manual
// --------------------------------------------------------------------

#include "A1Cal2.h" 
#include "Rec0.h"

class A1Cal2M : public A1Cal2 {
 public:
  
  // Additional variables
  double         tdc0[12][16];       // [channel][hit]
  char           tdc0flag[12][16];   // [channel][hit] flag(-1:nodata 0x1:Phase,0x2:Valid)
  double         scl0[16];           // [scaler data]
  unsigned int   counter[35];        // [counter data on FPGA]
  unsigned int   fifocounter[2][4];  // [channel][hit] FIFO in LHCFCOUNTER
  
 public:
  A1Cal2M(){ clear(); }
  A1Cal2M(char* name, char *title) : A1Cal2(name,title){clear();}
  virtual ~A1Cal2M(){;}

  virtual int clear(bankio option=ALL);
  virtual int copy(A1Cal2* d, bankio option=ALL);
  virtual int copydata(A1Cal2* d, bankio option=ALL);  
  int         copy(A1Cal2M* d, bankio option=ALL);
  int         copydata(A1Cal2M* d, bankio option=ALL);
  
  // +++++  USEFUL FUNCTIONS  +++++
  // ----- FOR SCALER VALUES -----
  double    clk();    //  scl0[1]*2^24+scl0[0]
  double    bptx1();  //  scl0[3]*2^24+scl0[2]
  double    bptx2();  //  scl0[5]*2^24+scl0[4]

  // ----- For Beam information ---
  enum BUNCHCONFFLAG{
    CROSSING         = Rec0::CROSSING,
    DISPLACED        = Rec0::DISPLACED,
    NONCROSSING      = Rec0::NONCROSSING,   // Single of Beam1
    NONCROSSING2     = Rec0::NONCROSSING2,   // Single of Beam2 
    UNKNOWN          = Rec0::UNKNOWN 
  };
  double    GetTDCofBPTX1();
  double    GetTDCofBPTX2();
  int       CheckBunchCrossing();

  ClassDef(A1Cal2M,1);   // Modified A1Cal2
};

#endif
