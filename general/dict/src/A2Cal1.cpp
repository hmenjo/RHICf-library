#ifndef __A2CAL1_CPP__
#define __A2CAL1_CPP__

#include "A2Cal1.h"

//----------------------------------------------------------------------
// A2Cal1
//
// This class stores the calculated data of Frontend2 with a meaningful structure.
// In this class, raw data or pedestal subtracted data should be filled.
//
// =====================================================================
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO) For Operation in 2010
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - bool   flag_beam  (Beam Flag picked up from GPIO Flag Register)
//  - bool   flag_pede  (Pedestal Flag picked up from GPIO Flag Register)
//  - bool   flag_laser (Laser Flag picked up from GPIO Flag Register)
//
//  - double cal[2][16][2]  [tower][channel][range]
//     ADC values for PMTs in the 25 calorimeter.
//      tower: 0=25mm,1=32mm
//      channel: 0-15
//      range: 0=LowRange(0.025pC/count), 1=LowRange(0.20pC/count)
//
//  - double cald[2][16][2]  [tower][channel][range]
//     ADC values of delayed gate. The delayed gate is generated about 10usec
//     after the normal gate. It is useful for pedestal subtraction event by event.
//     However you must check if no accidental signals in the values.
//
//  - double fc[2][4]  [arm][channel]
//     ADC values of Front Counters.
//      arm: 0=Arm1,1=Arm2
//      channel: 0-3
//     In the final configuration of DAQ, only data of Arm1 FC is taken in Arm1 Frontend.
//
//  - double fcd[2][4]  [arm][channel]
//     ADC values of delayed gate for Front Counters
//
//  - double laser[2]  [channel]
//     ADC values of Laser Monitor PMTs
//      channel: 0="L", 1="R"
//
//  - double laserd[2]  [channel]
//     ADC values of Laser Monitor PMTs
//      channel: 0="L", 1="R"
//
//  - double emptyadc[8]  [channel]
//     ADC values of noise.
//     Data only in 0-2 chennel may be filled.
//
//  - double tdc0[12][16]       [channel][hit]
//     TDC value (sec)
//      channel: 0-11
//      hit:     0-15  if only have #hit, value of >#hit are 0.
//    Channel List:
//     [0]  :  Masked 40MHz Clock (first value not be used) 
//     [1]  :  L3T 
//     [2]  :  BPTX1
//     [3]  :  BPTX2
//     [4]  :  Shower Trigger 
//     [5]  :  ATLAS L1A
//     [6]  :  Arm1 FC Logic OR
//     [7]  :  Arm2 FC Logic OR
//     [8]  :  25mm Discriminator OR
//     [9]  :  32mm Discriminator OR
//     [10] :  no input
//     [11] :  no input
//
//  - char   tdc0flag[12][16]   [channel][hit]
//     Flag for each hit.
//      if no hit, -1 is filled.
//      bit 0x1 means phase of the hit.
//      bit 0x2 means valid/invalid flag.
//
//  - double  scl0[16]  [channel]
//     Scaler values
//     Channel List (for configuration in 2009)
//      [0] :  40MHz Clock
//      [1] :  Cascade from [0]
//      [2] :  BPTX1
//      [3] :  Cascade from [2]
//      [4] :  BPTX2
//      [5] :  Cascade from [4]
//      [6] :  L3T
//      [7] :  L2TA
//      [8] :  Arm2 FC1
//      [9] :  Arm2 FC2
//      [10]:  Arm2 FC3
//      [11]:  Arm2 FC4
//      [12]:  LHCFCOUNTER:MLEMO(10) Arm1 FC Logic OR
//      [13]:  LHCFCOUNTER:MLEMO(11) Arm2 FC Logic OR
//      [14]:  LHCFCOUNTER:MLEMO(9)  Coincident of Arm1 FC and Arm2 FC
//      [15]:  no input
//
//  - float silicon[4][2][384][3] [layer][xy][strip][sample]
//     ADC values of silicon
//      layer: 0-3
//      xy: 0="X",1="Y"
//      strip: #strip 
//      sample: 0-2
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int counter[35]
//     Counter values of GPIOs
//      [0-14]  Counter values in LHCFLOGIC
//      [15-34] Counter values in LHCFCOUNTER
//     Counter list (for LHCFLOGIC_V2.5 and LHCFCOUNTER_V2.5)
//      [0]  : 40MHz Clock (Cleared by LHCF_ECR)
//      [1]  : L1T (Cleared by LHCF_ECR)
//      [2]  : BPTX1 "AND" BPTX2 (Cleared by LHCF_ECR)
//      [3]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cleared by LHCF_ECR)
//      [4]  : Shower Trigger of 25mm cal. (Cleared by LHCF_ECR)
//      [5]  : Shower Trigger of 32mm cal. (Cleared by LHCF_ECR)
//      [6]  : Shower Trigger 25mm "OR" 32mm (Cleared by LHCF_ECR)
//      [7]  : Shower Trg. of 25mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [8]  : Shower Trg. of 32mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [9]  : L2TA (Cleared by LHCF_ECR)
//      [10] : L2TP (Cleared by LHCF_ECR)
//      [11] : L2T_EXT (Cleared by LHCF_ECR)
//      [12] : L2T_L1T (Cleared by LHCF_ECR)
//      [13] : L3T (Cleared by LHCF_ECR)
//      [14] : L3T_ATLAS
//      [15] : 40MHz Clock (Cleared by LHCF_ECR)
//      [16] : ORBIT  (Cleared by LHCF_ECR)
//      [17] : ATLAS L1A (Cleared by LHCF_ECR)
//      [18] : Arm1 L3T (Cleared by LHCF_ECR)
//      [19] : Arm2 L3T (Cleared by LHCF_ECR)
//      [20] : Arm1 L3T "OR" Arm2 L3T (Global Event Number) (Cleared by LHCF_ECR)
//      [21] : Shower Trg. of Arm1 "OR" Arm2 (Cleared by LHCF_ECR)
//      [22] : Shower Trg. of Arm1 "AND" Arm2 (Cleared by LHCF_ECR)
//      [23] : 40MHz Clock  (Cleared by ORBIT)
//      [24] : BPTX1 (Cleared by ORBIT)
//      [25] : BPTX2 (Cleared by ORBIT)
//      [26] : 40MHz  (Cleared by ATLAS_ECR)
//      [27] : ATLAS L1A  (Cleared by ATLAS_ECR)
//      [28] : Selected Front Counter signal (0) (Cleared by LHCF_ECR)
//      [29] : Selected Front Counter signal (1) (Cleared by LHCF_ECR)
//      [30] : Selected Front Counter signal (2) (Cleared by LHCF_ECR)
//      [31] : Selected Front Counter signal (3) (Cleared by LHCF_ECR)
//      [32] : Selected singal (0) (Cleared by LHCF_ECR)
//      [33] : Selected singal (1) (Cleared by LHCF_ECR)
//      [34] : Selected singal (2) (Cleared by LHCF_ECR)
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int fifocounter[2][4] [channel][hit]
//     Counter value of FIFO Counter in LHCFCOUNTER
//     For detail, please refer the manual of LHCFCOUNTER
//
//
// ==========================================================================
// DATA FORMAT:  (Updated 16 Jan. 2010 by H.MENJO) For Operation in 2013
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - bool   flag_beam  (Beam Flag picked up from GPIO Flag Register)
//  - bool   flag_pede  (Pedestal Flag picked up from GPIO Flag Register)
//  - bool   flag_laser (Laser Flag picked up from GPIO Flag Register)
//
//  - double cal[2][16][2]  [tower][channel][range]
//     ADC values for PMTs in the 25 calorimeter.
//      tower: 0=25mm,1=32mm
//      channel: 0-15
//      range: 0=LowRange(0.025pC/count), 1=LowRange(0.20pC/count)
//
//  - double cald[2][16][2]  [tower][channel][range]
//     ADC values of delayed gate. The delayed gate is generated about 10usec
//     after the normal gate. It is useful for pedestal subtraction event by event.
//     However you must check if no accidental signals in the values.
//
//  - double fc[2][4]  [arm][channel]
//     ADC values of Front Counters.
//      arm: 0=Arm1,1=Arm2 (Only 1(Arm2) are available.)
//      channel: 0-3
//     CAEN V965 is used for ADC (in 2010, it was a LeCroy one)
//     The high range values (high resolusion) are filled for it.
//
//  - double fcd[2][4]  [arm][channel]
//     ADC values of delayed gate for Front Counters
//
//  - double laser[2]  [channel]
//     ADC values of Laser Monitor PMTs
//      channel: 0="L", 1="R"
//
//  - double laserd[2]  [channel]
//     ADC values of Laser Monitor PMTs
//      channel: 0="L", 1="R"
//
//  - double emptyadc[8]  [channel]
//     ADC values of noise.
//     Data only in 0-2 chennel may be filled.
//
//  - double tdc0[12][16]       [channel][hit]
//     TDC value (sec)
//      channel: 0-11
//      hit:     0-15  if only have #hit, value of >#hit are 0.
//    Channel List:
//     [0]  :  Masked 40MHz Clock (first value not be used) 
//     [1]  :  L3T 
//     [2]  :  BPTX1
//     [3]  :  BPTX2
//     [4]  :  Shower Trigger 
//     [5]  :  ATLAS L1A
//     [6]  :  -
//     [7]  :  Arm2 FC Logic OR
//     [8]  :  25mm Discriminator OR
//     [9]  :  32mm Discriminator OR
//     [10] :  QGC Gate1
//     [11] :  QGC Gate2
//    *) To avoid the number of hits more than the array size (16), only the hits 
//       in the time window [-2usec, +1usec] from L3T.
//
//  - char   tdc0flag[12][16]   [channel][hit]
//     Flag for each hit.
//      if no hit, -1 is filled.
//      bit 0x1 means phase of the hit.
//      bit 0x2 means valid/invalid flag.
//
//  - double  scl0[16]  [channel]
//     Scaler values
//     Channel List 
//      [0] :  40MHz Clock
//      [1] :  Cascade from [0]
//      [2] :  BPTX1
//      [3] :  Cascade from [2]
//      [4] :  BPTX2
//      [5] :  Cascade from [4]
//      [6] :  L3T
//      [7] :  L2TA
//      [8] :  Arm2 FC1
//      [9] :  Arm2 FC2
//      [10]:  Arm2 FC3
//      [11]:  Arm2 FC4
//      [12]:  -
//      [13]:  LHCFCOUNTER:MLEMO(11) Arm2 FC Logic OR
//      [14]:  -
//      [15]:  -
//
//  - float silicon[4][2][384][3] [layer][xy][strip][sample]
//     ADC values of silicon
//      layer: 0-3
//      xy: 0="X",1="Y"
//      strip: #strip 
//      sample: 0-2
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int counter[35]
//     Counter values of GPIOs
//      [0-14]  Counter values in LHCFLOGIC
//      [15-34] Counter values in LHCFCOUNTER
//     Counter list (for LHCFLOGIC_V2.5 and LHCFCOUNTER_V2.5)
//      [0]  : 40MHz Clock (Cleared by LHCF_ECR)
//      [1]  : L1T (Cleared by LHCF_ECR)
//      [2]  : BPTX1 "AND" BPTX2 (Cleared by LHCF_ECR)
//      [3]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cleared by LHCF_ECR)
//      [4]  : Shower Trigger of 25mm cal. (Cleared by LHCF_ECR)
//      [5]  : Shower Trigger of 32mm cal. (Cleared by LHCF_ECR)
//      [6]  : Shower Trigger 25mm "OR" 32mm (Cleared by LHCF_ECR)
//      [7]  : Shower Trg. of 25mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [8]  : Shower Trg. of 32mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [9]  : L2TA and ENABLE(Cleared by LHCF_ECR)
//      [10] : L2TP and ENABLE(Cleared by LHCF_ECR)
//      [11] : L2T_EXT and ENABLE(Cleared by LHCF_ECR)
//      [12] : L2TA_WOE L2TA without coincidence with ENABLE(cleared by LHCF_ECR)
//      [13] : L3T (Cleared by LHCF_ECR)
//      [14] : -
//      [15] : 40MHz Clock (Cleared by LHCF_ECR)
//      [16] : ORBIT  (Cleared by LHCF_ECR)
//      [17] : ATLAS L1A (Cleared by LHCF_ECR)
//      [18] : -
//      [19] : Arm2 L3T (Cleared by LHCF_ECR)
//      [20] : - 
//      [21] : -
//      [22] : -
//      [23] : 40MHz Clock  (Cleared by ORBIT)
//      [24] : BPTX1 (Cleared by ORBIT)
//      [25] : BPTX2 (Cleared by ORBIT)
//      [26] : 40MHz  (Cleared by ATLAS_ECR)
//      [27] : ATLAS L1A  (Cleared by ATLAS_ECR)
//      [28] : FC Logic 1 (Cleared by LHCF_ECR)
//      [29] : FC Logic 2 (Cleared by LHCF_ECR)
//      [30] : FC Logic 3 (Cleared by LHCF_ECR)
//      [31] : FC Logic 4 (Cleared by LHCF_ECR)
//      [32] : Arm2 FC Logic OR (Cleared by LHCF_ECR)
//      [33] : Arm2 FC Trigger  (Cleared by LHCF_ECR)
//      [34] : Arm2 FC Trigger and Shower (Cleared by LHCF_ECR)
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int fifocounter[2][4] [channel][hit]
//     Counter value of FIFO Counter in LHCFCOUNTER
//     For detail, please refer the manual of LHCFCOUNTER
//
// ==========================================================================
// DATA FORMAT:  (Updated 23 Nov. 2016 by H.MENJO) For Operation in 2016
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    (Always 0)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//  - bool   flag_beam  (Beam Flag picked up from GPIO Flag Register)
//  - bool   flag_pede  (Pedestal Flag picked up from GPIO Flag Register)
//  - bool   flag_laser (Laser Flag; No laser operation in 2016)
//
//  - double cal[2][16][2]  [tower][channel][range]
//     ADC values for PMTs in the 25 calorimeter.
//      tower: 0=25mm,1=32mm
//      channel: 0-15
//      range: 0=LowRange(0.025pC/count), 1=LowRange(0.20pC/count)
//
//  - double cald[2][16][2]  [tower][channel][range]
//     ADC values of delayed gate. The delayed gate is generated about 10usec
//     after the normal gate. It is useful for pedestal subtraction event by event.
//     However you must check if no accidental signals in the values.
//
//  - double fc[2][4]  [arm][channel]
//     ADC values of Front Counters.
//      arm: 0=Arm1,1=Arm2 (Only 1(Arm2) are available.)
//      channel: 0-3
//     CAEN V965 is used for ADC (in 2010, it was a LeCroy one)
//     The high range values (high resolusion) are filled for it.
//
//  - double fcd[2][4]  [arm][channel]
//     ADC values of delayed gate for Front Counters
//
//  - double laser[2]  [channel]
//     Not use in 2016 
//
//  - double laserd[2]  [channel]
//     Not use in 2016
//
//  - double emptyadc[8]  [channel]
//     Not use in 2016
//
//  - double tdc0[12][16]       [channel][hit]
//     TDC value (sec)
//      channel: 0-11
//      hit:     0-15  if only have #hit, value of >#hit are 0.
//    Channel List:
//     [0]  :  Masked 40MHz Clock (first value not be used) 
//     [1]  :  L3T 
//     [2]  :  BPTX1
//     [3]  :  BPTX2
//     [4]  :  Shower Trigger 
//     [5]  :  ATLAS L1A
//     [6]  :  (Shower Logic (SLOGIC or LLOGIC)) <- Only fill > 5533
//     [7]  :  Arm2 FC Logic OR
//     [8]  :  25mm Discriminator OR
//     [9]  :  32mm Discriminator OR
//     [10] :  QGC Gate1
//     [11] :  QGC Gate2
//    *) To avoid the number of hits more than the array size (16), only the hits 
//       in the time window [-2usec, +1usec] from L3T.
//
//  - char   tdc0flag[12][16]   [channel][hit]
//     Flag for each hit.
//      if no hit, -1 is filled.
//      bit 0x1 means phase of the hit.
//      bit 0x2 means valid/invalid flag.
//
//  - double  scl0[16]  [channel]
//     Scaler values
//     Channel List 
//      [0] :  40MHz Clock
//      [1] :  Cascade from [0]
//      [2] :  BPTX1
//      [3] :  Cascade from [2]
//      [4] :  BPTX2
//      [5] :  Cascade from [4]
//      [6] :  L3T
//      [7] :  L2TA
//      [8] :  Arm2 FC1
//      [9] :  Arm2 FC2
//      [10]:  Arm2 FC3
//      [11]:  Arm2 FC4
//      [12]:  -
//      [13]:  Arm2 FC Logic OR
//      [14]:  TESTOUT1 OF LHCFLOGIC (Shower Logic (SLOGIC or LLOGIC)) <- Only fill > 5533
//      [15]:  TESTOUT1 OF LHCFLOGIC (Shower Logic (SLOGIC or LLOGIC)) <- Only fill > 5533
//
//  - float silicon[4][2][384][3] [layer][xy][strip][sample]
//     ADC values of silicon
//      layer: 0-3
//      xy: 0="X",1="Y"
//      strip: #strip 
//      sample: 0-2
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int counter[35]
//     Counter values of GPIOs
//      [0-14]  Counter values in LHCFLOGIC
//      [15-34] Counter values in LHCFCOUNTER
//     Counter list (for LHCFLOGIC_V2.5 and LHCFCOUNTER_V2.5)
//      [0]  : 40MHz Clock (Cleared by LHCF_ECR)
//      [1]  : L1T (Cleared by LHCF_ECR)
//      [2]  : BPTX1 "AND" BPTX2 (Cleared by LHCF_ECR)
//      [3]  : L1T "AND" ENABLE "AND" BEAMFLAG (Cleared by LHCF_ECR)
//      [4]  : Shower Trigger of 25mm cal. (Cleared by LHCF_ECR)
//      [5]  : Shower Trigger of 32mm cal. (Cleared by LHCF_ECR)
//      [6]  : Shower Trigger 25mm "OR" 32mm (Cleared by LHCF_ECR)
//      [7]  : Shower Trg. of 25mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [8]  : Shower Trg. of 32mm cal. without coincidence with L1T (Cleared by LHCF_ECR)
//      [9]  : (Combine)L2TA and ENABLE(Cleared by LHCF_ECR) / L2TP and ENABLE(Cleared by LHCF_ECR)
//             Bit[15-0]: L2TA,  Bit[31-16]: L2TP  
//      [10] : L2T_EXT and ENABLE(Cleared by LHCF_ECR) / L2TA (Cleared by LHCF_ECR)
//             Bit[15-0]:L2T_EXT , Bit[31-16]:  L2TA
//      [11] : Special1 trigger (Type1-Pi0) / L2T_Special1 (Cleared by LHCF_ECR)
//             Bit[15-0]:Special1 trigger, Bit[31-16]: L2T_Special1
//      [12] : Special2 trigger (Type1-Pi0) / L2T_Special2 (Cleared by LHCF_ECR)
//             Bit[15-0]:Special2 trigger, Bit[31-16]: L2T_Special2
//      [13] : L3T (Cleared by LHCF_ECR)
//      [14] : L3T sent to ATLAS (Cleared by LHCF_ECR)
//      [15] : 40MHz Clock (Cleared by LHCF_ECR)
//      [16] : ORBIT  (Cleared by LHCF_ECR)
//      [17] : ATLAS L1A (Cleared by LHCF_ECR)
//      [18] : -
//      [19] : Arm2 L3T (Cleared by LHCF_ECR)
//      [20] : - 
//      [21] : -
//      [22] : -
//      [23] : 40MHz Clock(Bunch ID)  (Cleared by ORBIT)
//      [24] : BPTX1 (Cleared by ORBIT)
//      [25] : BPTX2 (Cleared by ORBIT)
//      [26] : 40MHz  (Cleared by ATLAS_ECR)
//      [27] : ATLAS L1ID  (Cleared by ATLAS_ECR)
//      [28] : FC Logic 1 (Cleared by LHCF_ECR)
//      [29] : FC Logic 2 (Cleared by LHCF_ECR)
//      [30] : FC Logic 3 (Cleared by LHCF_ECR)
//      [31] : FC Logic 4 (Cleared by LHCF_ECR)
//      [32] : Arm2 FC Logic OR (Cleared by LHCF_ECR)
//      [33] : Arm2 FC Trigger  (Cleared by LHCF_ECR)
//      [34] : Arm2 FC Trigger and Shower (Cleared by LHCF_ECR)
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
//  - unsigned int fifocounter[2][4] [channel][hit]
//     Counter value of FIFO Counter in LHCFCOUNTER
//     For detail, please refer the manual of LHCFCOUNTER
//
//===========================================================================
// ++Logs
//  ?? ???. 08: First edited by H.MENJO
//  27 Aug. 08: Added silicon data [4][2][384][3]
//  09 Aug. 08: Modified the format of TDC
//              tdc[N_A2_TDC0]->tdc0flag[12][16];
//  10 Sep. 08: Change deta type: long -> int
//  21 Apr. 09: "enum bank" added by H.MENJO
//  30 Oct. 09: Added laserd and fcd by H.MENJO
//              and inclesed the version number 1->2.
//  12 Jan. 10: Added the functions, "pow" and "sqrt" 
//  14 Jan. 10: Fixed bugs in add, subtract ..., 
//              it affect for only fcd and laserd 
//  23 Feb. 10: Added functions for flags by H.MENJO
//  30 Aug. 10: Added some functions by H.MENJO
//              GetTDCofBPTX1,GetTDCofBPTX2 and CheckBunchCrossing
//--------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Cal1);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#include <globaldef.h>
#include <A2Cal2.h>

// ***********************************************************
// ***  A2Cal1::clear()  *************************************
// ***********************************************************
int A2Cal1::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  CAL,CALD,FC,FCD,LASER,LASERD,EMPTYADC,SILICON,
  //  TDC0,TDC0FLAG,SCL0,FLAG,COUNTER,FIFOCOUNTER,
  // 
  // exp.  clear(A2Cal::CAL & A2Cal::SILICON);

  run     = 0;
  number  = 0;
  gnumber = 0;
  time[0] = 0;
  time[1] = 0;
  flag_beam  = false;
  flag_pede  = false;
  flag_laser = false;
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  cal[it][il][ir] = 0.0;
	}
      }
    }
  }

  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  cald[it][il][ir] = 0.0;
	}
      }
    }
  }
  
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){ 
	for(int ir=0;ir<2;ir++){
	  cald[it][il][ir] = 0.0;
	}
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ laser[i] = 0.;} 
  if(option & LASERD)   for(int i=0;i<2;i++){ laserd[i] = 0.;}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ emptyadc[i] = 0.;}

  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    silicon[il][ixy][istrip][isample] = 0.;
	  }
	}
      }
    }
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     tdc0[ich][ihit] = 0.;
      if(option & TDC0FLAG) tdc0flag[ich][ihit] = -1;
    }
  }

  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ scl0[i] = 0.;}

  if(option & FLAG)    for(int i=0;i<3 ;i++) {flag[i]=0;}
  if(option & COUNTER) for(int i=0;i<35;i++) {counter[i]=0;}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	fifocounter[ich][ib]=0;
      }
    } 
  }
  
  return OK;
}

// ***********************************************************
// ***  A2Cal1::copy     *************************************
// ***********************************************************
int A2Cal1::copy(A2Cal1* d, bankio option){ 
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)

  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d, option);
}

// ***********************************************************
// ***  A2Cal1::copydata     *********************************
// ***********************************************************
int A2Cal1::copydata(A2Cal1* d, bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)

  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber; 
  this->time[0] = d->time[0];
  this->time[1] = d->time[1];
  this->flag_beam  = d->flag_beam;
  this->flag_pede  = d->flag_pede;
  this->flag_laser = d->flag_laser;
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  = d->cal[it][il][ir];
	}
      }
    }
  }

  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] = d->cald[it][il][ir];
	}
      }
    }
  }

  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC) { this->fc[it][il]  = d->fc[it][il]; }
	if(option & FCD){ this->fcd[it][il] = d->fcd[it][il]; }
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] = d->laser[i];}
  if(option & LASERD)  {for(int i=0;i<2;i++){ this->laserd[i] = d->laserd[i];}}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] = d->emptyadc[i];}
 
  if(option & SILICON){ 
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] 
	      = d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    } 
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     this->tdc0[ich][ihit] = d->tdc0[ich][ihit];
      if(option & TDC0FLAG) this->tdc0flag[ich][ihit] = d->tdc0flag[ich][ihit];
    }
  }

  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ this->scl0[i] = d->scl0[i];}

  if(option & FLAG)    for(int i=0;i<3 ;i++) {this->flag[i]=d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {this->counter[i]=d->counter[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]=d->fifocounter[ich][ib];
      }
    } 
  }

  return OK;
}

// ***********************************************************
// ***  A2Cal1::add      *************************************
// ***********************************************************
int A2Cal1::add(A2Cal1* d, bankio option){
  // Add data of "d" to this
  // (default option:0x1FF)
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  += d->cal[it][il][ir];
	}
      }
    }  
  }
  
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] += d->cald[it][il][ir];
	}
      }
    }  
  }

  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  += d->fc[it][il];
	if(option & FCD) this->fcd[it][il] += d->fcd[it][il];	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] += d->laser[i];}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] += d->laserd[i];}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] += d->emptyadc[i];}
 
  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] 
	      += d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    } 
  }
  
  for(int ich=0;ich<12;ich++){
    for(int ihit=0;ihit<16;ihit++){
      if(option & TDC0)     tdc0[ich][ihit] += d->tdc0[ich][ihit];
      //if(option & TDC0FLAG) tdc0flag[ich][ihit] += d->tdc0flag[ich][ihit];
    }
  }

  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ scl0[i] += d->scl0[i];}

  //if(option & FLAG)    for(int i=0;i<3 ;i++) {flag[i] += d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {counter[i] += d->counter[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
        fifocounter[ich][ib] += d-> fifocounter[ich][ib];
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A2Cal1::subtract   ***********************************
// ***********************************************************
int A2Cal1::subtract(A2Cal1* d, bankio option){
  // Subtract data of "d" from this
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir]  -= d->cal[it][il][ir];
	}
      }
    }  
  }

  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] -= d->cald[it][il][ir];
	}
      }
    }  
  }
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  -= d->fc[it][il];
	if(option & FCD) this->fcd[it][il] -= d->fcd[it][il];	
      }
    }
  }

  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] -= d->laser[i];}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] -= d->laserd[i];}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] -= d->emptyadc[i];} 

  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] 
	      -= d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    }
  }

  if(option & TDC0){
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	 if(option & TDC0) tdc0[ich][ihit] -= d->tdc0[ich][ihit];
	//if(option & TDC0FLAG) tdc0flag[ich][ihit] -= d->tdc0flag[ich][ihit];
      }
    }
  }

  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ scl0[i] -= d->scl0[i];}

  //if(option & FLAG)    for(int i=0;i<3 ;i++) {flag[i] -= d->flag[i];}
  if(option & COUNTER) for(int i=0;i<35;i++) {counter[i] -= d->counter[i];}
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
        fifocounter[ich][ib] -= d-> fifocounter[ich][ib];
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A2Cal1::multiply   ***********************************
// ***********************************************************
int A2Cal1::multiply(double d, bankio option){
  // Multiply data by the given factor of "d"
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir] *= d;
	}
      }
    }   
  }

  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cald[it][il][ir] *= d;
	}
      }
    }   
  }

  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il] *= d;
	if(option & FCD) this->fcd[it][il] *= d;	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] *= d;}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] *= d;}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] *= d;} 
 
  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] *= d;
	  }
	}
      }
    }
  }  

  if(option & TDC0){
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	 if(option & TDC0) tdc0[ich][ihit] *= d;
	//if(option & TDC0FLAG) tdc0flag[ich][ihit] *= d;
      }
    }
  }

  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ scl0[i] *= d;}

  //if(option & FLAG)    for(int i=0;i<3 ;i++) {flag[i] *= d;}
  if(option & COUNTER) for(int i=0;i<35;i++){
    counter[i] = (int)(d*counter[i]);
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
        fifocounter[ich][ib] = (int)(d*fifocounter[ich][ib]);
      }
    }
  }
  
  return OK;
}

// ***********************************************************
// ***  A2Cal1::divide   *************************************
// ***********************************************************
int A2Cal1::divide(double d, bankio option){
  return multiply(1./d);
}

// ***********************************************************
// ***  A2Cal1::pow   ****************************************
// ***********************************************************
int A2Cal1::pow(double d, bankio option){
  // calculate the d'th power of each value.
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cal[it][il][ir] = ::pow(this->cal[it][il][ir],d);
	}
      }
    } 
  }  
    
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cald[it][il][ir] = ::pow(this->cald[it][il][ir],d);
	}
      }
    } 
  }  
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)	 this->fc[it][il] = ::pow(this->fc[it][il],d);
	if(option & FCD) this->fcd[it][il] = ::pow(this->fcd[it][il],d);	
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] = ::pow(this->laser[i],d);}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] = ::pow(this->laserd[i],d);}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] = ::pow(this->emptyadc[i],d);} 
  
  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] 
	      = ::pow(this->silicon[il][ixy][istrip][isample],d);
	  }
	}
      }
    }
  }  

  if(option & TDC0){  
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	this->tdc0[ich][ihit] = ::pow(this->tdc0[ich][ihit],d);
      }
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ this->scl0[i] = ::pow(this->scl0[i],d);}

  if(option & COUNTER) for(int i=0;i<35;i++){
    this->counter[i] = (int)(::pow(this->counter[i],d));
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]
	  = (int)(::pow(this->fifocounter[ich][ib],d));
      }
    }
  }

  return OK;
}

// ***********************************************************
// ***  A2Cal1::sqrt   ****************************************
// ***********************************************************
int A2Cal1::sqrt(bankio option){
  // calculate the square root of each value.
  // (default option:0x1FF)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	  this->cal[it][il][ir] = ::sqrt(this->cal[it][il][ir]);
	}
      }
    } 
  }  
    
  if(option & CALD){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	for(int ir=0;ir<2;ir++){
	 this->cald[it][il][ir] = ::sqrt(this->cald[it][il][ir]);
	}
      }
    } 
  }  
  
  if(option & FC || option & FCD){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	if(option & FC)  this->fc[it][il]  = ::sqrt(this->fc[it][il]);
	if(option & FCD) this->fcd[it][il] = ::sqrt(this->fcd[it][il]);
      }
    }
  }
  
  if(option & LASER)    for(int i=0;i<2;i++){ this->laser[i] = ::sqrt(this->laser[i]);}
  if(option & LASERD)   for(int i=0;i<2;i++){ this->laserd[i] = ::sqrt(this->laserd[i]);}
  if(option & EMPTYADC) for(int i=0;i<8;i++){ this->emptyadc[i] = ::sqrt(this->emptyadc[i]);} 
  
  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] 
	      = ::sqrt(this->silicon[il][ixy][istrip][isample]);
	  }
	}
      }
    }
  }  

  if(option & TDC0){  
    for(int ich=0;ich<12;ich++){
      for(int ihit=0;ihit<16;ihit++){
	this->tdc0[ich][ihit] = ::sqrt(this->tdc0[ich][ihit]);
      }
    }
  }
  
  if(option & SCL0) for(int i=0;i<N_A2_SCL0;i++){ this->scl0[i] = ::sqrt(this->scl0[i]);}

  if(option & COUNTER) for(int i=0;i<35;i++){
    this->counter[i] = (int)(::sqrt(this->counter[i]));
  }
  if(option & FIFOCOUNTER){
    for(int ich=0;ich<2;ich++){
      for(int ib=0;ib<4;ib++){
	this->fifocounter[ich][ib]
	  = (int)(::sqrt(this->fifocounter[ich][ib]));
      }
    }
  }

  return OK;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ CONVERSION OF SCL0 VALUE                            +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double A2Cal1::clk(){
  //  scl0[1]*2^24+scl0[0]

  const int b24 = 16777216;
  return ((double)scl0[1])*b24 + scl0[0];  
}

double A2Cal1::bptx1(){
  //  scl0[3]*2^24+scl0[2]
  
  const int b24 = 16777216;
  return ((double)scl0[3])*b24 + scl0[2]; 
}

double A2Cal1::bptx2(){
  //  scl0[5]*2^24+scl0[4]

  const int b24 = 16777216;
  return ((double)scl0[5])*b24 + scl0[4]; 
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  USEFUL FUNCTIONS                                +++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int A2Cal1::CopySilicon(A2Cal2* d){
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
	for(int isample=0;isample<3;isample++){
	  this->silicon[il][ixy][istrip][isample] 
	    = d->silicon[il][ixy][istrip][isample];
	}
      }
    }
  }
  return OK;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++           Check Bunch Crossing                   +++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int A2Cal1::CheckBunchCrossing(){
  // Return bunch crossing configuration of this event.
  // Whether the event is with bunch crossing or not can be checked by several ways,
  //   1) BPTX flag, the easiest way but it cannot identify displaced bunch crossing. 
  //   2) Bunch ID,  if you know the filling scheme in this fill,
  //                 you can check whether the bunch crosses or not by bunch ID
  //   3) TDC,       TDC values of BPTX's also help to identify bunch crossing
  //                 event by event. This gives correct results.
  // This function take the mathod "3)"
  // 
  // Return values 
  //   if bunch crossing,                  return 1,
  //   if non-bunch crossing (Beam1),      return 2,
  //   if displaced beam crossing,         return 3,
  //   if non-bunch crossing (Beam2),      return 4,
  //   else (unknow or simulation)         return 0
  
  // Get TDC values
  double bptx1 = GetTDCofBPTX1();
  double bptx2 = GetTDCofBPTX2();
  
  // Check No TDC values or Simulation
  if(bptx1 > 0. && bptx2 > 0.){ return A2Cal1::UNKNOWN;}
  
  // Check non-bunch crossing
  // Only Beam1 (coming from IP to Arm2 detector)
  if(bptx1 < 0. && bptx2 > 0.){ return A2Cal1::NONCROSSING;}
  // Only Beam2 (out going from Arm2 detector to IP)
  if(bptx1 > 0. && bptx2 < 0.){ return A2Cal1::NONCROSSING2;}  
  
  // Check displaced bunch crossing 
  if(fabs( bptx1-bptx2 ) > 50.){ return A2Cal1::DISPLACED;}
  
  return A2Cal1::CROSSING;
}

double A2Cal1::GetTDCofBPTX1(){
  // Get TDC values of BPTX1 in the possible period for this event.
  // For the moment, the period is set to from -1300ns to -800ns.
  // This must be called after pedestal subtraction. 
  // it means that 0 is equal to the timing of L3T trigger.
  // if no hit, return +1. 
  const int ch = 2;
  for(int ih=0;ih<16;ih++){
    if(this->tdc0flag[ch][ih]<0) break;
    if(this->tdc0[ch][ih] > -1300. && this->tdc0[ch][ih] < -800.){
      return this->tdc0[ch][ih];
    }
  }
  return 1.;
}

double A2Cal1::GetTDCofBPTX2(){
  // Get TDC value of BPTX2 in the possible period for this event.
  // For the moment, the period is set to from -1300ns to -800ns. 
  // This must be called after pedestal subtraction. 
  // it means that 0 is equal to the timing of L3T trigger. 
  // if no hit, return +1. 
  const int ch = 3;
  for(int ih=0;ih<16;ih++){ 
    if(this->tdc0flag[ch][ih]<0) break;
    if(this->tdc0[ch][ih] > -1300. && this->tdc0[ch][ih] < -800.){
      return this->tdc0[ch][ih];
    }
  }
  return  1.;
}



#endif
