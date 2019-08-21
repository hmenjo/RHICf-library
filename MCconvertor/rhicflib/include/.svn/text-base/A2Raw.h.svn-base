#ifndef __A2RAW_H__
#define __A2RAW_H__

//----------------------------------------------------------------------
// A1Raw2
//
// Data structure for the raw data of Arm2.
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
//  - unsigned short adc1[32] (CAEN V965)
//      ADC values for the PMTs of 32mm Cal.
//      This array contain 16ch*2ranges 
//      [0]: ch.0,High   [1]: ch.0,Low
//      [2]: ch.1,High   [3]: ch.1,Low ...
//      [32-63] : adc values of a delayed gate.
//
//  - unsigned short adc2[8] (LeCroy 1182)
//      ADC values for monitering event by event noise
//      This array contain 8ch
//      [0-2] 3 empty channels of preamp.
//      [3]   ADC value of no input channel
//      [4-7] no use
//
//  - unsigned short adc3[16] (LeCroy 1182)
//      no use.
//
//  - unsigned short adc4[16] (LeCroy 1182)
//      This array contain 8ch*2events
//      ADC values of laser monitor
//      [0] : Laser monitor-L
//      [1] : Laser monitor-R
//      [4-7] : channel 0-4 of Arm1 FC
//      [8-15]: adc values of a delayed gate.
//
//  - unsigned int   cadc0[5]  (CAEN V965)
//      Internal counter values of ADC0
//      It is for only check of the DAQ system
//
//  - unsigned int   cadc1[5]  (CAEN V965)
//      Internal counter values of ADC1
//      It is for only check of the DAQ system
//
//  - unsigned short arm2[512] (Silicon readout board)
//      Silicon data
//      The arrangement of data is complicated.
//      Please refer the manual of silicon.
//
//  - unsigned int   tdc0[160] (CAEN V1290)
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
//  ?? ???. 08: First edited by H.MENJO             
//  21 Apr. 09: Fuction copy(A2Raw* ), copydata(A2Raw*),      
//              add(A2Raw) was added by H.MENJO.          
//  21 Apr. 09: "enum bank" added by H.MENJO
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"
#include "feparam_arm2.h"

class A2Raw : public TNamed {
 public:
  int   run;                       // Run Number
  int   number;                    // Arm2 Event Number 
  int   gnumber;                   // Glocal Event Number
  
  unsigned int   time[N_A2_TIME];  // Time [0]:sec,[1]:usec
  unsigned short adc0[N_A2_ADC0];  // ADC0 [64] For 20mm Cal. (16ch*2ranges*2events)
  unsigned short adc1[N_A2_ADC1];  // ADC1 [64] For 40mm Cal. (16ch*2ranges*2events)
  unsigned short adc2[N_A2_ADC2];  // ADC2 [8]  For Noise check
  unsigned short adc3[N_A2_ADC3];  // ADC3 [16] no use 
  unsigned short adc4[N_A2_ADC4];  // ADC4 [16] For Laser and F.C (8ch*2evnets)
  unsigned int   cadc0[N_A2_CAD0]; // Counter value of ADC0 [5] 
  unsigned int   cadc1[N_A2_CAD0]; // Counter value of ADC1 [5]
  unsigned int   tdc0[N_A2_TDC0];  // TDC0 [64] 
  unsigned int   scl0[N_A2_SCL0];  // Scaler [16] 
  unsigned int   gpio0[N_A2_GPI0]; // GPIO [17] 2 Flags+15 Counter Values 
  unsigned int   gpio1[N_A2_GPI1]; // GPIO [27] 1 Flags+26 counter Values
  char           arm2[N_A2_ARM2];  // Silicon [14280] 

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
  A2Raw(){clear();}
  A2Raw(char* name, char *title) : TNamed(name,title){clear();}
  ~A2Raw(){;}
  
  int  clear(bankio option=ALL);                // Clear all data.
  int  copy(A2Raw* data,bankio option=ALL);     // Copy all data to this.
  int  copydata(A2Raw* data,bankio option=ALL); // Copy data to this except header data.
  int  add(A2Raw* data,bankio option=ALL);      // Add data to this.

  ClassDef(A2Raw,3);
};

#endif
