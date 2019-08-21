#ifndef __A2CAL2M_H__
#define __A2CAL2M_H__

// --------------------------------------------------------------------
//                               A2Cal2M
//                       This is a modified A2Cal2 
//             For detail, see A2Cal2.cpp or Online Manual
// --------------------------------------------------------------------

#include "A2Cal2.h" 
#include "Rec0.h"

class A2Cal2M : public A2Cal2 {
 public:
  
  // Additional variables
  double         tdc0[12][16];       // [channel][hit]
  char           tdc0flag[12][16];   // [channel][hit] flag(-1:nodata 0x1:Phase,0x2:Valid)
  double         scl0[16];           // [scaler data]
  unsigned int   counter[35];        // GPIO0:15ch + GPIO:20ch
  unsigned int   fifocounter[2][4];  // [channel][hit] FIFO in LHCFCOUNTER
  
 public:
  A2Cal2M(){ clear(); }
  A2Cal2M(char* name, char *title) : A2Cal2(name,title){clear();}
  virtual ~A2Cal2M(){;}

  virtual int clear(bankio option=ALL);
  virtual int copy(A2Cal2* d, bankio option=ALL);
  virtual int copydata(A2Cal2* d, bankio option=ALL);  
  int         copy(A2Cal2M* d, bankio option=ALL);
  int         copydata(A2Cal2M* d, bankio option=ALL);
  
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

  ClassDef(A2Cal2M,1);   // Modified A2Cal2
};

#endif
