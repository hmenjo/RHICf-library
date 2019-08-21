#ifndef __A1CAL1_H__
#define __A1CAL1_H__


// --------------------------------------------------------------------
//                               A1Cal1
//             For detail, see A1Cal1.cpp or Online Manual
// --------------------------------------------------------------------


#include <TNamed.h>
#include "globaldef.h"
#include "feparam_arm1.h"

class A1Cal1 : public TNamed {
 public:
  int            run;                // Run Number
  int            number;             // Arm1 Event Number
  int            gnumber;            // Grobal Event Number
  double         time[2];            // [0]:sec,[1]:usec
  // +++++ DATA FLAGS +++++
  bool           flag_beam;          // Beam Flag 
  bool           flag_pede;          // Pedestal Flag
  bool           flag_laser;         // Laser Flag
  // +++++ DATA +++++ 
  double         cal[2][16][2];      // [tower][layer][range] range0=L,1=H
  double         cald[2][16][2];     // delayed gate event
  double         fc[2][4];           // [arm][channel] for both FCs
  double         fcd[2][4];          // delayed gate event
  double         laser[2];           // [channel] for laser monitor PMTs (0="L",1="R")
  double         laserd[2];          // delayed gate event
  double         emptyadc[8];        // [channel] for noise reduction
  double         scifi0[4][2][20];   // [layer][xy][fiber] (xy:0="x",1="y") for 20mm cal.
  double         scifi1[4][2][40];   // [layer][xy][fiber] (xy:0="x",1="y") for 40mm cal.
  double         tdc0[12][16];       // [channel][hit]
  char           tdc0flag[12][16];   // [channel][hit] flag(-1:nodata 0x1:Phase,0x2:Valid)
  double         scl0[N_A1_SCL0];    // [scaler data]
  
  unsigned int   flag[3];            // GPIO0:2ch  + GPIO:1ch
  unsigned int   counter[35];        // GPIO0:15ch + GPIO:20ch
  unsigned int   fifocounter[2][4];  // [channel][hit] FIFO in LHCFCOUNTER
 
 public:
  typedef int bankio;
  enum bank {
    CAL         = 0x0001,
    CALD        = 0x0002,
    FC          = 0x0004,
    FCD         = 0x0008,
    LASER       = 0x0010,
    LASERD      = 0x0020,
    EMPTYADC    = 0x0040,
    SCIFI0      = 0x0080,
    SCIFI1      = 0x0100,
    TDC0        = 0x0200,
    TDC0FLAG    = 0x0400,
    SCL0        = 0x0800,
    FLAG        = 0x1000,
    COUNTER     = 0x2000,
    FIFOCOUNTER = 0x4000,
    ALL = 0x7FFF
  };
  
  //  == For Operation 2010 ==
  enum GPIOFLAG0{
    FLAG0_BPTX1      = 0x0001,
    FLAG0_BPTX2      = 0x0002,
    FLAG0_EXT_L1T    = 0x0004,
    FLAG0_L2TA       = 0x0010,
    FLAG0_L2TP       = 0x0020,
    FLAG0_L2T_EXT    = 0x0040,
    FLAG0_L2T_L1T    = 0x0100,
    FLAG0_STRG       = 0x0400,
    FLAG0_LTRG       = 0x0800,
    FLAG0_BEAMFLAG   = 0x1000,
    FLAG0_PEDEFLAG   = 0x2000,
    FLAG0_LASERFLAG  = 0x4000,
    FLAG0_ENABLEFLAG = 0x8000
  };
  
  // == For Operation 2010 == 
  enum GPIOFLAG2{
    FLAG2_A1_ENABLE  = 0x0001,
    FLAG2_A1_STR     = 0x0002,
    FLAG2_A1_L3T     = 0x0004,
    FLAG2_A2_ENABLE  = 0x0010,
    FLAG2_A2_STR     = 0x0020,
    FLAG2_A2_L3T     = 0x0040,
    FLAG2_BPTX1      = 0x0100,
    FLAG2_BPTX2      = 0x0200, 
    FLAG2_L1A        = 0x0400,
    FLAG2_A1_FC_TRG  = 0x1000,
    FLAG2_A2_FC_TRG  = 0x2000, 
    FLAG2_L2TC       = 0x4000, 
    FLAG2_A1_FC0     = 0x010000,
    FLAG2_A1_FC1     = 0x020000,
    FLAG2_A1_FC2     = 0x040000,
    FLAG2_A1_FC3     = 0x080000,
    FLAG2_A2_FC0     = 0x100000,
    FLAG2_A2_FC1     = 0x200000,
    FLAG2_A2_FC2     = 0x400000,
    FLAG2_A2_FC3     = 0x800000
  };

 public:
  A1Cal1(){ clear(); }
  A1Cal1(char* name, char *title) : TNamed(name,title){ clear();}
  ~A1Cal1(){;}
  
  int       clear(bankio option=ALL);
  int       copy(A1Cal1* d, bankio option=ALL);
  int       copydata(A1Cal1* d, bankio option=ALL);
  int       add(A1Cal1* d, bankio option=0x1FF);
  int       subtract(A1Cal1* d, bankio option=0x1FF);
  int       multiply(double d, bankio option=0x1FF);
  int       divide(double d, bankio option=0x1FF);
  int       pow(double d, bankio option=0x1FF);
  int       sqrt(bankio option=0x1FF);
  
  // ----- FOR SCALER VALUES -----
  double    clk();    //  scl0[1]*2^24+scl0[0]
  double    bptx1();  //  scl0[3]*2^24+scl0[2]
  double    bptx2();  //  scl0[5]*2^24+scl0[4]
  
  // ----- FOR FLAGS ------
  int       CheckFlag(unsigned int i,unsigned int mask){return (i&mask) ? 1 : 0;}
  int       IsBPTX1Flag(){return CheckFlag(flag[0],FLAG0_BPTX1);}
  int       IsBPTX2Flag(){return CheckFlag(flag[0],FLAG0_BPTX2);}
  int       IsEXTL1TFlag(){return CheckFlag(flag[0],FLAG0_EXT_L1T);}
  int       IsL2TAFlag(){return CheckFlag(flag[0],FLAG0_L2TA);}
  int       IsL2TPFlag(){return CheckFlag(flag[0],FLAG0_L2TP);}
  int       IsL2TEXTFlag(){return CheckFlag(flag[0],FLAG0_L2T_EXT);}
  int       IsL2TL1TFlag(){return CheckFlag(flag[0],FLAG0_L2T_L1T);}
  int       IsSTRGFlag(){return CheckFlag(flag[0],FLAG0_STRG);}
  int       IsSTrgSmallFlag(){return IsSTRGFlag();}
  int       IsLTRGFlag(){return CheckFlag(flag[0],FLAG0_LTRG);}
  int       IsSTrgLargeFlag(){return IsLTRGFlag();}
  int       IsBeamFlag(){return CheckFlag(flag[0],FLAG0_BEAMFLAG);}  
  int       IsPedeFlag(){return CheckFlag(flag[0],FLAG0_PEDEFLAG);}  
  int       IsLaserFlag(){return CheckFlag(flag[0],FLAG0_LASERFLAG);}   
  int       IsEnableFlag(){return CheckFlag(flag[0],FLAG0_ENABLEFLAG);}     
  int       IsA1EnableFlag(){return CheckFlag(flag[2],FLAG2_A1_ENABLE);}
  int       IsA1STrgFlag(){return CheckFlag(flag[2],FLAG2_A1_STR);}
  int       IsA1ShowerTrgFlag(){return IsA1STrgFlag();}
  int       IsA1L3TFlag(){return CheckFlag(flag[2],FLAG2_A1_L3T);}
  int       IsA2EnableFlag(){return CheckFlag(flag[2],FLAG2_A2_ENABLE);}
  int       IsA2STrgFlag(){return CheckFlag(flag[2],FLAG2_A2_STR);}
  int       IsA2ShowerTrgFlag(){return IsA2STrgFlag();}
  int       IsA2L3TFlag(){return CheckFlag(flag[2],FLAG2_A2_L3T);}
  int       IsATLASL1AFlag(){return CheckFlag(flag[2],FLAG2_L1A);}
  int       IsA1FCTrgFlag(){return CheckFlag(flag[2],FLAG2_A1_FC_TRG);}
  int       IsA2FCTrgFlag(){return CheckFlag(flag[2],FLAG2_A2_FC_TRG);}
  int       IsL2TCFlag(){return CheckFlag(flag[2],FLAG2_L2TC);}
  int       IsFCFlag(int arm,int channel) {return CheckFlag(flag[2],(0x010000 << (4*(arm-1)+channel)));}
  int       IsDSCFlag(int tower,int layer){return CheckFlag(flag[1],(0x1 << (16*(tower)+layer)));}
  

  ClassDef(A1Cal1,2);   // Data structure for Arm1 data
};

#endif
