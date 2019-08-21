#ifndef __A2RAW_PP2015_H__
#define __A2RAW_PP2015_H__

//----------------------------------------------------------------------
// A1Raw_pp2015
//
// Data Format for the operation at p-p collisions in 2015
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - unsigned int time[2]
//      CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 25mm Cal.
//      This array contains 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[64] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contains 16ch*2ranges*2events 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      ADC values of FC2 (4ch), Laser Monitor installed in detector (1ch),
//      Monitoring noize (1ch)
//      This array contains 16ch*2ranges*2 buffers
//      [0]: FC(0),High  [1]: FC(0), Low
//      [2]: FC(1),High  [3]: FC(1), Low
//      ....
//      ch.0  FC2(0)    ch.1  FC2(1)
//      ch.2  FC2(2)    ch.3  FC2(3)
//      ch.4  -         ch.5  -
//      ch.6  Noise     ch.7  Laser Monitor
//      ch.8-15 -
//
//  - unsigned short adc3[0] 
//      no use.
//
//  - unsigned short adc4[0] 
//      no use.
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short arm2[14280] (Silicon readout board)
//      Silicon data
//      The arrangement of data is complicated.
//      Please refer the manual of silicon.
//
//  - unsigned int   tdc0[256] (CAEN V1290)
//      Data have the format of the buffer of CAEN V1290
//      The array size should be more than N_A2_TDC
//        0-20 bit: TDC value
//       25-21 bit: Channel
//       26 bit   : falling/rising flag 
//      For detail, refer the manual of V1290
//
//  - unsigned int   gpio0[50]
//      Flags and Counter valuse of the trigger module
//      [0] : Event Flag
//      [1] : Discriminator Flag (This detector)
//      [2] : Discriminator Flag (The other detector)
//      [3-34] : Counter values 
//      the others : no use
//      Please refer the manual of the trigger module
//
//  - unsigned int   gpio1[0]
//      no use
//
//=====================================================================
// ++Logs
//  12 Mar 2015: Copied A2Raw_pPb2013 to A2Raw_pp2015 and modified 
//               for pPb by H.MENJO  
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A2Raw_pp2015 : public TNamed {
 public:
  // Static constant values 
  static const int c_N_TIME = 2;
  static const int c_N_ADC0 = 64;
  static const int c_N_ADC1 = 64;
  static const int c_N_ADC2 = 64;
  static const int c_N_ADC3 = 4;
  static const int c_N_ADC4 = 0;
  static const int c_N_CAD0 = 5;
  static const int c_N_CAD1 = 5;
  static const int c_N_TDC0 = 256;
  static const int c_N_SCL0 = 16;
  static const int c_N_GPI0 = 50;
  static const int c_N_GPI1 = 0;
  static const int c_N_ARM2 = 14280;

 public:
  int   run;                       // Run Number
  int   number;                    // Arm2 Event Number 
  int   gnumber;                   // Glocal Event Number
  
  unsigned int   time[c_N_TIME];  // Time [0]:sec,[1]:usec
  unsigned short adc0[c_N_ADC0];  // ADC0 [64] For 20mm Cal. (16ch*2ranges*2events)
  unsigned short adc1[c_N_ADC1];  // ADC1 [64] For 40mm Cal. (16ch*2ranges*2events)
  unsigned short adc2[c_N_ADC2];  // ADC2 [64] For FC, Laser Monitor, Noise check
  unsigned short adc3[c_N_ADC3];  // ADC3 [4] For Laser Monitor (L,R)
  //unsigned short adc4[c_N_ADC4];  // ADC4 [0] no use
  unsigned int   cadc0[c_N_CAD0]; // Counter value of ADC0 [5] 
  unsigned int   cadc1[c_N_CAD1]; // Counter value of ADC1 [5]
  unsigned int   tdc0[c_N_TDC0];  // TDC0 [256] 
  unsigned int   scl0[c_N_SCL0];  // Scaler [16]
  unsigned int   gpio0[c_N_GPI0]; // GPIO [50] 3 Flags+32 Counter Values 
  //unsigned int   gpio1[c_N_GPI1]; // GPIO [0]
  char           arm2[c_N_ARM2];  // Silicon [14280] 

 public:
  typedef int bankio;
  enum bank {
    TIME  = 0x0001,
    ADC0  = 0x0002,
    ADC1  = 0x0004,
    ADC2  = 0x0008,
    ADC3  = 0x0010,
    ADC4  = 0x0020,
    CADC0 = 0x0040,
    CADC1 = 0x0080,
    TDC0  = 0x0100,
    SCL0  = 0x0200,
    GPIO0 = 0x0400,
    GPIO1 = 0x0800,
    ARM2  = 0x1000,
    ALL   = 0x1FFF
  };
  
 public:
  A2Raw_pp2015(){clear();}
  A2Raw_pp2015(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Raw_pp2015(){;}
  
  int  clear(bankio option=ALL);                        // Clear all data.
  int  copy(A2Raw_pp2015* data,bankio option=ALL);     // Copy all data to this.
  int  copydata(A2Raw_pp2015* data,bankio option=ALL); // Copy data to this except header data.
  int  add(A2Raw_pp2015* data,bankio option=ALL);      // Add data to this.

  ClassDef(A2Raw_pp2015,1);
};

#endif
