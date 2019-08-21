// ***********************************************************
// ****           Parameters List for SPS2007             ****  
// ****  19 Aug. 07 : Improved by H.Menjo                 ****
// ****  17 Apr. 10 : Added ARM1_FE_LOGFILE2              ****
// ****  05 Jan  10 : PARAM_A1_TDC0_MAXBUFFER  64 -> 128  ****
// ****               ARM1_FEPARAM_VERSION 3 -> 4         ****
// ****  14 Jun  10 : Added parameters of LHCFL1T         ****
// ****               VERSION 4 -> 5                      ****
// ***********************************************************
 
// version 001  
// type    001

#ifndef ARM1_FEPARAM
#define ARM1_FEPARAM

// *** General parameter 
#define ARM1_FEPARAM_VERSION      5
#define ARM1_FEPARAM_TYPE         1
//#define ARM1_FE_LOGFILE           "/home/lhcf/LHCf/Data/LogFrontend1/frontend_arm1_log"
#define ARM1_FE_LOGFILE           "./frontend_arm1_log1.tmp"
//#define ARM1_FE_LOGFILE2          "/nfs/lhcfds4/data1/DAQLogs/LogFrontend1/frontend_arm1_log2"
#define ARM1_FE_LOGFILE2          "./frontend_arm1_log2.tmp"

// *** VME Addresses of each modules
// for Arm#1
#define BASE_A1_ADD_ADC0    0xEEEE0000  // A32D16 and A32D32 CAEN V965
#define BASE_A1_ADD_ADC1    0xEEFF0000  // A32D16 and A32D32 CAEN V965
#define BASE_A1_ADD_ADC2    0x500000    // A24D16 LeCroy1182
#define BASE_A1_ADD_ADC3    0x520000    // A24D16 LeCroy1182
#define BASE_A1_ADD_ADC4    0x540000    // A24D16 LeCroy1182
#define BASE_A1_ADD_DSC0    0xDDEE0000  // A32D16 CAEN V814B
#define BASE_A1_ADD_DSC1    0xDDFF0000  // A32D16 CAEN V814B
#define BASE_A1_ADD_IO0     0x5500      // A16D16 RPV-130
#define BASE_A1_ADD_SCL0    0x200000    // A24D32 CAEN V260
#define BASE_A1_ADD_SADC    0x00FF00    // A24D16 GNV_150
#define BASE_A1_ADD_FEC     0xF00000    // A24D32 CP 80057
#define BASE_A1_ADD_TDC0    0x330000    // A24D32 LeCroy1171
#define BASE_A1_ADD_GPIO0   0xFF010000  // A32D32 GPIO  (LHCFLOGIC)
#define BASE_A1_ADD_GPIO1   0xFF000000  // A32D32 GPIO  (LHCFCOUNTER)
#define BASE_A1_ADD_GPIO2   0xFF040000  // A32D32 GPIO  (LHCFL1T)
#define BASE_A1_ADD_LTP     0xAAAA00    // A24D16 ATLAS LTP (not used in fe)

// *** Device for serial port 
#define SERIALPORT_A1_DEVICE "/dev/ttyS1"

// *** for ADC0 ADC1 
#define PARAM_A1_ADC0_IPED         150
#define PARAM_A1_ADC1_IPED         150
#define PARAM_A1_ADC0_NCH           32    // 16ch*2
#define PARAM_A1_ADC1_NCH           32    // 16ch*2

// *** for ADC2 ADC3 ADC4 
#define PARAM_A1_ADC2_NCH            4    // 8ch
#define PARAM_A1_ADC3_NCH            8    // 8ch
#define PARAM_A1_ADC4_NCH            8    // 8ch
#define PARAM_A1_ADC2_NEVENT         1    // Normal Trigger
#define PARAM_A1_ADC3_NEVENT         2    // Normal Trigger + Delayed Trigger 
#define PARAM_A1_ADC4_NEVENT         2    // Normal Trigger + Delayed Trigger 
#define PARAM_A1_ADC2_NWORD          4    // PARAM_A1_ADC2_NCH * PARAM_A1_ADC2_NEVENT
#define PARAM_A1_ADC3_NWORD         16    // PARAM_A1_ADC3_NCH * PARAM_A1_ADC3_NEVENT
#define PARAM_A1_ADC4_NWORD         16    // PARAM_A1_ADC4_NCH * PARAM_A1_ADC4_NEVENT

#define PARAM_A1_SADC_NCH           16

// *** for I/O register : IO0            
#define  PARAM_A1_IO0_CH_STOP        0    // pulse output
#define  PARAM_A1_IO0_CH_PEDE        1    // level output
#define  PARAM_A1_IO0_CH_ENABLE1     2    // level output
#define  PARAM_A1_IO0_CH_BEAMON      3    // level output
#define  PARAM_A1_IO0_CH_PEDEON      4    // level output
#define  PARAM_A1_IO0_CH_LASERON     5    // level output

#define  PARAM_A1_IO0_NCN_INT1       8    // number of channel on latch1
#define  PARAM_A1_IO0_NCH_INT2       8    // number of channel on latch2
#define  PARAM_A1_IO0_INT_TRIG       1    // interapt 1 for trigger      
#define  PARAM_A1_IO0_INT_FLAG       2    // interapt 2 for flag 

// *** for Scalor : SCL0
#define  PARAM_A1_SCL0_NCH            16    // 

// *** for Disrimineter : DSC0 DSC1
#define  PARAM_A1_DSC0_NCH            16   // 
#define  PARAM_A1_DSC1_NCH            16   //
#define  PARAM_A1_DSC0_DEFULT_VALUE   10   
#define  PARAM_A1_DSC1_DEFULT_VALUE   10
#define  PARAM_A1_DSC0_PULSE_WIDTH    255  
#define  PARAM_A1_DSC1_PULSE_WIDTH    255  
#define  PARAM_A1_DSC_PARAMFILE       "./discri.param"

// *** for Scifi : SCIF
#define  PARAM_A1_SCIF_NCH           512

// *** for TDC
#define  PARAM_A1_TDC0_MAXBUFFER     128

// *** for GPIO 
#define  PARAM_A1_GPIO0_FALG_NCH       2
#define  PARAM_A1_GPIO0_CNT_NCH       15
#define  PARAM_A1_GPIO1_FALG_NCH       1
#define  PARAM_A1_GPIO1_CNT_NCH       18
#define  PARAM_A1_GPIO1_FIFO_NWORD     8
#define  PARAM_A1_GPIO2_CNT1_NCH      14
#define  PARAM_A1_GPIO2_CNT2_NCH      20

// *** waiting times : each module 
const int PARAM_A1_WAIT_LOOP   =       0;    // usec
const int PARAM_A1_WAIT_IO0    =       0;    // usec
const int PARAM_A1_WAIT_IO1    =       0;    // usec
const int PARAM_A1_WAIT_FEC     =      0;    // usec
#endif

#ifndef GENERAL_A1_PARAMETER_LIST
#define GENERAL_A1_PARAMETER_LIST
// number of each data
#define N_A1_TIME        2   // DWORD 
#define N_A1_INP0        8   // BYTE  Not used 
#define N_A1_SCL0       16   // DWORD 
#define N_A1_ADC0       64   // WORD  16ch.*2ranges*2event  0H 0L 1H 1L 2H 2L ...
#define N_A1_ADC1       64   // WORD  16ch.*2ranges*2event  0H 0L 1H 1L 2H 2L ...
#define N_A1_ADC2        8   // WORD   8ch.  (Only 4 words are filled, but the format should be kept.)
#define N_A1_ADC3       16   // WORD   8ch. x 2 Events
#define N_A1_ADC4       16   // WORD   8ch. x 2 Events
#define N_A1_CAD0        5   // DWORD Event counter of ADC0
#define N_A1_CAD1        5   // DWORD Event counter of ADC1
#define N_A1_SCIF      512   // WORD
#define N_A1_TDC0      128   // DWORD
#define N_A1_GPI0       17   // DWORD
#define N_A1_GPI1       27   // DWORD
#define N_A1_GPI2       14   // DWORD
#define N_A1_PTIM        1   // DWORD
#define N_A1_PSCL       16   // DWORD Scaler Value
#define N_A1_PSAD       16   // WORD  No used 
#define N_A1_PGP0       15   // DWORD No used
#define N_A1_PGP1       17   // DWORD No used
#define N_A1_PGP2       20   // DWORD

#endif
