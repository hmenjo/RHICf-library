#ifndef __A2RAW_PPB2016_H__
#define __A2RAW_PPB2016_H__

//----------------------------------------------------------------------
//                             A2Raw_pPb2016
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class A2Raw_pPb2016 : public TNamed {
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
  A2Raw_pPb2016(){clear();}
  A2Raw_pPb2016(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Raw_pPb2016(){;}
  
  int  clear(bankio option=ALL);                        // Clear all data.
  int  copy(A2Raw_pPb2016* data,bankio option=ALL);     // Copy all data to this.
  int  copydata(A2Raw_pPb2016* data,bankio option=ALL); // Copy data to this except header data.
  int  add(A2Raw_pPb2016* data,bankio option=ALL);      // Add data to this.

  ClassDef(A2Raw_pPb2016,1);
};

#endif
