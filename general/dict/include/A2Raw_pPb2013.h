#ifndef __A2RAW_PPB2013_H__
#define __A2RAW_PPB2013_H__

//----------------------------------------------------------------------
// A1Raw2_pPb2013
//
// Data Format for the operation at p-Pb collisions in 2013
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - unsigned int time[2]
//      CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
//
//  - unsigned short adc0[64] (CAEN V965)
//      ADC values for the PMTs of 25mm Cal.
//      This array contain 16ch*2ranges*2evnets
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc1[64] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contain 16ch*2ranges*2events 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[64] (CAEN V965)
//      ADC values of FC (4ch), Laser (2ch), Mornitering noise(3ch)
//      This array contain 16ch*2ranges*2events 
//      [0]: FC(0),High  [1]: FC(0), Low
//      [2]: FC(1),High  [3]: FC(1), Low
//      ....
//      ch.0  FC(0)    ch.1  FC(1)
//      ch.2  FC(2)    ch.3  FC(3)
//      ch.4  -        ch.5  -
//      ch.6  Laser R  ch.7  Laser L
//      ch.8  Noise(0) ch.9  Noise(1)
//      ch.10 Noise(2) ch.11 -
//      ch.12-15 -
//
//  - unsigned short adc3[0] (LeCroy 1182)
//      no use.
//
//  - unsigned short adc4[0] (LeCroy 1182)
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
//      The array size should be more than N_A2_TDC0
//       0-15bit  :  Value (1count=1nsec)
//       16bit    :  phase
//       17-20bit :  channel
//       21bit    :  valid flag
//       23bit    :  end flag
//      For detail, refer the manual of this module.
//
//  - unsigned int   gpio0[17]
//      Flags and Counter valuse of LHCFLOGIC
//      [0] : Event Flag
//      [1] : Discri Flag
//      the others : counter valuse
//      Please refer the manual of LHCFLOGIC
//
//  - unsigned int   gpio1[27]
//      Flag and Counter valuse of LHCFCOUNTER
//      [0] : Event Flag
//      [1-19]  : counter valuse
//      [20-27] : fifo counter values
//      Please refer the manual of LHCFCOUNTER
//
//=====================================================================
// ++Logs
//  15 Dec 2012: Copied A2Raw to A2Raw_pPb2013 and modified for pPb 
//               by H.MENJO
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A2Raw_pPb2013 : public TNamed {
 public:
  // Static constant values 
  static const int c_N_TIME = 2;
  static const int c_N_ADC0 = 64;
  static const int c_N_ADC1 = 64;
  static const int c_N_ADC2 = 64;
  static const int c_N_ADC3 = 0;
  static const int c_N_ADC4 = 0;
  static const int c_N_CAD0 = 5;
  static const int c_N_CAD1 = 5;
  static const int c_N_TDC0 = 256;
  static const int c_N_SCL0 = 16;
  static const int c_N_GPI0 = 17;
  static const int c_N_GPI1 = 27;
  static const int c_N_ARM2 = 14280;

 public:
  int   run;                       // Run Number
  int   number;                    // Arm2 Event Number 
  int   gnumber;                   // Glocal Event Number
  
  unsigned int   time[c_N_TIME];  // Time [0]:sec,[1]:usec
  unsigned short adc0[c_N_ADC0];  // ADC0 [64] For 20mm Cal. (16ch*2ranges*2events)
  unsigned short adc1[c_N_ADC1];  // ADC1 [64] For 40mm Cal. (16ch*2ranges*2events)
  unsigned short adc2[c_N_ADC2];  // ADC2 [64] For FC, Laser, Noise check
  unsigned short adc3[c_N_ADC3];  // ADC3 [0] no use 
  unsigned short adc4[c_N_ADC4];  // ADC4 [0] no use
  unsigned int   cadc0[c_N_CAD0]; // Counter value of ADC0 [5] 
  unsigned int   cadc1[c_N_CAD1]; // Counter value of ADC1 [5]
  unsigned int   tdc0[c_N_TDC0];  // TDC0 [256] 
  unsigned int   scl0[c_N_SCL0];  // Scaler [16]
  unsigned int   gpio0[c_N_GPI0]; // GPIO [17] 2 Flags+15 Counter Values 
  unsigned int   gpio1[c_N_GPI1]; // GPIO [27] 1 Flags+26 counter Values
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
  A2Raw_pPb2013(){clear();}
  A2Raw_pPb2013(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Raw_pPb2013(){;}
  
  int  clear(bankio option=ALL);                        // Clear all data.
  int  copy(A2Raw_pPb2013* data,bankio option=ALL);     // Copy all data to this.
  int  copydata(A2Raw_pPb2013* data,bankio option=ALL); // Copy data to this except header data.
  int  add(A2Raw_pPb2013* data,bankio option=ALL);      // Add data to this.

  ClassDef(A2Raw_pPb2013,1);
};

#endif
