#ifndef __RHICFRAW_OP2017_H__
#define __RHICFRAW_OP2017_H__

//----------------------------------------------------------------------
// RHICfRaw_Op2017
//
// Data Format for the RHICf operation in 2017 
//
// DATA FORMAT:  (Updated 29 Sep 2016 by H.MENJO)
//  - unsigned int time[2]
//     CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned int trgm[1]
//     Token + flag
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 20mm Cal.
//      This array contain 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[32] (CAEN V965)
//      ADC values for the PMTs of 40mm Cal.
//      This array contain 16ch*2ranges
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      Laser Monitor installed inside detector (1ch),
//      Monitoring noize (1ch)
//      This array contains 16ch*2ranges*2 buffers
//      ch.0  Laser Monitor    ch.1  -
//      ch.2  -                ch.3  -
//      ch.4  Noise            ch.5  -
//      ch.6  -                ch.7  -
//      ch.8-15 -
//
//  - unsigned short adc3[0] 
//      not used 
//
//  - unsigned short adc4[0] 
//      not used
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short scifi[512] (SciFi readout board)
//      ADC values of SciFi.
//      The arrangement of data is complicated.
//      Please refer "xxxxx.dat"
//
//  - unsigned int   tdc0[256] (LeCroy1171)
//      Data have the format of the buffer of CAEN V1290
//      The array size should be more than N_A1_TDC0.
//        0-20 bit: TDC value
//       25-21 bit: Channel
//       26 bit   : falling/rising flag 
//      For detail, refer the manual of V1290
//
//  - unsigned int   gpio0[19]
//      Flags and Counter valuse of the trigger module
//      [0] : Event Flag
//      [1] : Discriminator Flag 
//      [2-18] : Counter values
//      Please refer the manual of the trigger module
//
//  - unsigned int   gpio1[17]
//      Flags, Counter values, Fifo counter of the GPIO( RHICF_GPIO )
//      [0]   : Event Flag
//      [1-8] : Counter values
//      [9-16]: Fifo counter values
//
//=====================================================================
// ++Logs
//  12 Mar 2015 : Copied  Arm1_pp2015 to RHICfRaw_Op2017 and modified
//                by Menjo
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class RHICfRaw_Op2017 : public TNamed {
 public:
  // Static constant values 
  static const int c_N_TIME = 2;
  static const int c_N_TRGM = 1;
  static const int c_N_ADC0 = 64;
  static const int c_N_ADC1 = 64;
  static const int c_N_ADC2 = 64;
  static const int c_N_ADC3 = 0;
  static const int c_N_ADC4 = 0;
  static const int c_N_CAD0 = 5;
  static const int c_N_CAD1 = 5;
  static const int c_N_TDC0 = 256;
  static const int c_N_SCL0 = 0;
  static const int c_N_GPI0 = 19;
  static const int c_N_GPI1 = 17;
  static const int c_N_SCIF = 512;

 public:
  int   run;                        // Run Number
  int   number;                     // Arm1 Event Number
  int   gnumber;                    // Global Event Number
  
  unsigned int   time[c_N_TIME];   // Time [0]:sec,[1]:usec
  unsigned int   trgm[c_N_TRGM];   // TRGM [0] token + trigger flag
  unsigned short adc0[c_N_ADC0];   // ADC0 [64] For 20mm Cal. (16ch*2ranges*2events)
  unsigned short adc1[c_N_ADC1];   // ADC1 [64] For 40mm Cal. (16ch*2ranges*2events)
  unsigned short adc2[c_N_ADC2];   // ADC2 [64]  ADC2 [64] For FC, Laser Monitor, Noise check
  //unsigned short adc3[c_N_ADC3];   // ADC3 [4]  For Laser Monitor (L,R)
  //unsigned short adc4[c_N_ADC4];   // ADC4 [0] 
  unsigned int   cadc0[c_N_CAD0];  // Counter value of ADC0 [5] 
  unsigned int   cadc1[c_N_CAD0];  // Counter value of ADC1 [5]
  unsigned short scifi[c_N_SCIF];  // Scifi [512] 
  unsigned int   tdc0[c_N_TDC0];    // TDC0 [256] it independs on [c_N_TDC0] but should be >.   
  //unsigned int   scl0[c_N_SCL0];   // Scaler [16] 
  unsigned int   gpio0[c_N_GPI0];  // GPIO [19] 2 Flags+17 Counter Values 
  unsigned int   gpio1[c_N_GPI1];  // GPIO [17] 1 Flags+26 counter Values

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
    SCIFI = 0x1000,
    TRGM  = 0x2000,
    ALL   = 0x2FFF
  };
  
 public:
  RHICfRaw_Op2017(){clear();}
  RHICfRaw_Op2017(char* name, char *title) : TNamed(name,title){clear();}
  ~RHICfRaw_Op2017(){;}
  
  int clear(bankio option=ALL);                // Clear all data.
  int copy(RHICfRaw_Op2017* data,bankio option=ALL);     // Copy all data to this.   
  int copydata(RHICfRaw_Op2017* data,bankio option=ALL); // Copy data to this except header data.  
  int add(RHICfRaw_Op2017* data,bankio option=ALL);      // Add data to this.

  ClassDef(RHICfRaw_Op2017,1); // Data structure for raw data of Arm1
};

#endif
