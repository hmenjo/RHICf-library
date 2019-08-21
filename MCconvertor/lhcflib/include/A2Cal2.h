#ifndef __A2CAL2_H__
#define __A2CAL2_H__


// --------------------------------------------------------------------
//                               A2Cal2
//             For detail, see A2Cal2.cpp or Online Manual
// --------------------------------------------------------------------

#include <TNamed.h>

class A2Cal1;

class A2Cal2 : public TNamed {
 public:
  // event infomation
  int            run;                   // run number
  int            number;                // Arm#2  event number
  int            gnumber;               // Grobal event number
  double         time[2];               // Time 0:sec 1:usec

  // data
  double         cal[2][16];            // Scintillator Layers [tower:layer]
  double         fc[2][4];              // Front counters [arm:channel]
  float          silicon[4][2][384][3]; // Silicon Layers [layer:xy:strip:sample]
  
  unsigned int   flag[3];               // Flags in GPIOs (GPIO0:2ch+GPIO:1ch)

 public:
  typedef int bankio;
  enum bank {
    CAL         = 0x0001,
    FC          = 0x0004,
    SILICON     = 0x0020, 
    TDC0        = 0x0200,
    TDC0FLAG    = 0x0100,
    SCL0        = 0x0800, 
    FLAG        = 0x0400,
    COUNTER     = 0x2000,
    FIFOCOUNTER = 0x4000,
    ALL         = 0xFFFF
  };
  
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
  A2Cal2(){ clear(); }
  A2Cal2(char* name, char *title) : TNamed(name,title){clear();}
  virtual ~A2Cal2(){;} 

  virtual int clear(bankio option=ALL);
  virtual int copy(A2Cal2* d, bankio option=ALL);
  virtual int copydata(A2Cal2* d, bankio option=ALL);
  int       add(A2Cal2* d, bankio option=0x25);
  int       subtract(A2Cal2* d, bankio option=0x25);
  int       multiply(double d, bankio option=0x25);
  int       divide(double d, bankio option=0x25);
  
  double    calsum(int it,int sl=0,int ie=15);   // Sum of calorimeter
  double    calsum2(int it,int sl=0,int ie=15);  // Modified Sum (if layer>10,*2)
  double    siliconsum(int il,int ixy, int isample, 
		       int sstrip=0,int estrip=383);

  int       CopySilicon(A2Cal1* d); 
  
  virtual void Show();
  
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
  

  ClassDef(A2Cal2,1);   // Data structure for Arm2 data
};

#endif
