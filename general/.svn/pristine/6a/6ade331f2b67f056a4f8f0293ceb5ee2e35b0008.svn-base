#ifndef __A1RAW_H__
#define __A1RAW_H__

//----------------------------------------------------------------------
// A1Raw1
//
// Data structure for the raw data of Arm1.
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - unsigned int time[2]
//     CPU time of trigger was detected by Frontend PC,
//      [0]:sec, [1]:usec
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
//      [4-7] : channel 0-4 of Arm2 FC
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
//  - unsigned short scifi[512] (SciFi readout board)
//      ADC values of SciFi.
//      The arrangement of data is complicated.
//      Please refer "scifi_pos_table_080408.dat"
//
//  - unsigned int   tdc0[160] (LeCroy1171)
//      Data have the format of the buffer of LeCroy1171
//      The array size should be more than N_A1_TDC0.
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
//  20 Apr. 09: Fuction copy(A1Raw* ), copydata(A1Raw*),           
//              add(A1Raw) was added by H.MENJO.             
//  21 Apr. 09: "enum bank" added by H.MENJO
//----------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"
#include "feparam_arm1.h"

class A1Raw : public TNamed {
 public:
  int   run;                        // Run Number
  int   number;                     // Arm1 Event Number
  int   gnumber;                    // Global Event Number
  
  unsigned int   time[N_A1_TIME];   // Time [0]:sec,[1]:usec
  unsigned short adc0[N_A1_ADC0];   // ADC0 [64] For 20mm Cal. (16ch*2ranges*2events)
  unsigned short adc1[N_A1_ADC1];   // ADC1 [64] For 40mm Cal. (16ch*2ranges*2events)
  unsigned short adc2[N_A1_ADC2];   // ADC2 [8]  For Noise check
  unsigned short adc3[N_A1_ADC3];   // ADC3 [16] no use 
  unsigned short adc4[N_A1_ADC4];   // ADC4 [16] For Laser and F.C (8ch*2evnets)
  unsigned int   cadc0[N_A1_CAD0];  // Counter value of ADC0 [5] 
  unsigned int   cadc1[N_A1_CAD0];  // Counter value of ADC1 [5]
  unsigned short scifi[N_A1_SCIF];  // Scifi [512] 
  unsigned int   tdc0[160];         // TDC0 [160] it independs on [N_A1_TDC0] but should be >.   
  unsigned int   scl0[N_A1_SCL0];   // Scaler [16] 
  unsigned int   gpio0[N_A1_GPI0];  // GPIO [17] 2 Flags+15 Counter Values 
  unsigned int   gpio1[N_A1_GPI1];  // GPIO [27] 1 Flags+26 counter Values

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
    ALL   = 0x1FFF
  };
  
 public:
  A1Raw(){clear();}
  A1Raw(char* name, char *title) : TNamed(name,title){clear();}
  ~A1Raw(){;}
  
  int clear(bankio option=ALL);                // Clear all data.
  int copy(A1Raw* data,bankio option=ALL);     // Copy all data to this.   
  int copydata(A1Raw* data,bankio option=ALL); // Copy data to this except header data.  
  int add(A1Raw* data,bankio option=ALL);      // Add data to this.

  ClassDef(A1Raw,3); // Data structure for raw data of Arm1
};

#endif
