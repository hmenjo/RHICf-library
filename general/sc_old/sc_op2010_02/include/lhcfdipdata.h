//---------------------------------------------------------------------- 
//  DIP data structure for the LHCf experiment                  
//  This data used in the slowcontrol system of LHCf. The data   
//  will be filled in SlowConrol-DIP and recode in the slow      
//  control server.                                              
//  ------------------------------------------------------------ 
//  02 Nov. 2009: created by H.MENJO                             
//                mainly copied from old lhcfsdata.h             
//  08 Dev. 2009: added IntensityPerBunch by H.MENJO             
//                LHCFDIPDATAL_VERSION      301 -> 302           
//
//  27 Feb. 2010:                                                
//   Added the structures                                        
//     DIP_ACC_BEAM_BPM_M   BPM_LSS1L B1                         
//     DIP_ACC_BEAM_BPM_M   BPM_LSS1L B2                         
//     DIP_ACC_BEAM_BPM_M   BPM_LSS1R B1                         
//     DIP_ACC_BEAM_BPM_M   BPM_LSS1R B2                         
//     DIP_ACC_BEAM_LUMINOSITYPERBUNCH_S Beam1_intensityperbunch 
//     DIP_ACC_BEAM_LUMINOSITYPERBUNCH_S Beam2_intensityperbunch 
//   LHCFDIPDATAH_VERSION   201 -> 202                         
//   LHCFDIPDATAL_VERSION   301 -> 302  (Forgot increment the number 02Mar2010)       
//      
//  02 Mar. 2010          
//   Added two structure for DIP in LHCFDIPDATAH
//     DIP_ATLAS_CLOCK_SELECTION        Atlasclocl;
//     DIP_LHCF_DOSIMETER               dosimeterL;
//     DIP_LHCF_DOSIMETER               dosimeterR;
//   LHCFDIPDATAH_VERSION     202 -> 203
//   LHCFDIPDATAL_VERSION     301 -> 302
//----------------------------------------------------------------------

#ifndef __LHCFDIPDATA_H__
#define __LHCFDIPDATA_H__

#include "lhcfsdata.h"

#define LHCFDIPDATAH_HEADER_WORD  "DIPH"
#define LHCFDIPDATAL_HEADER_WORD  "DIPL"
#define LHCFDIPDATAVH_HEADER_WORD "DIPVH"
#define LHCFDIPDATAH_VERSION      203      // start from 201
#define LHCFDIPDATAL_VERSION      302      // start from 301
#define LHCFDIPDATAVH_VERSION     401      // start from 401

typedef  long long LongLong; 

#define DIP_STRING_LENGTH 24

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++            DIP DATA FORMAT FOR EACH MODULE               +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ---  Published by LHCf -----------------------------------------

struct DIP_LHCF_Arm{
  int     Quality;
  int     Time;
  char    STATUS[DIP_STRING_LENGTH];
  char    FC_STATUS[DIP_STRING_LENGTH];
  char    POSITION_STR[DIP_STRING_LENGTH];
  int     RUNNUMBER;
  char    dummy[4];
  double  POSITION_DBL;
  double  FC_RATE;
  double  SHOWER0;
  double  SHOWER1;
  double  BEAM_POS0_H;
  double  BEAM_POS0_V;
  double  BEAM_POS1_H;
  double  BEAM_POS1_V;
};

struct DIP_LHCF_COINCIDENCE{
  int     Quality;
  int     Time;
  char    STATUS[DIP_STRING_LENGTH];
  double  FC1_FC2_RATE;
  double  SHOWER1_SHOWER2_RATE;
  double  FC2_SHOWER1_RATE;
  double  FC1_SHOWER2_RATE;
};

struct DIP_LHCF_EXPTSTATUS{
  int     Quality;
  int     Time;
  char    Status[DIP_STRING_LENGTH]; 
};

struct DIP_LHCF_INTERLOCK{
  int     Quality;
  int     Time;
  char    dummy[4];
  int     beam_injection_accept;
};

struct DIP_LHCF_LUMINOSITY{
  int     Quality;
  int     Time;
  float   Lumi_TotInst;
  char    dummy[4];
  char    Source[DIP_STRING_LENGTH]; 
};

struct DIP_LHCF_HS_LHC_INJECTION{
  int     Quality; 
  int     Time;
  char    DIP_DEFAULT[DIP_STRING_LENGTH]; 
};

struct DIP_LHCF_HS_LHC_ADJUST{
  int     Quality;
  int     Time;
  char    DIP_DEFAULT[DIP_STRING_LENGTH];
};

struct DIP_LHCF_HS_LHC_BEAMDUMP{
  int     Quality; 
  int     Time;
  char    DIP_DEFAULT[DIP_STRING_LENGTH];  
};


// --- BRAM INFORMATION --------------------------------------------

struct DIP_ACC_BEAM_BPM{
  int        Quality;
  int        Time;
  double     verticalPos[4];    
  double     horizontalPos[4];  
  // Actual the sizes of arrays are [26]. But [0-3] only related at IP1 
};

struct DIP_ACC_BEAM_BPM_M{
  int        Quality;
  int        Time;
  char       bpmNames[8][DIP_STRING_LENGTH];
  int        statusV[8];
  int        statusH[8];
  double     errorV[8];
  double     errorH[8]; 
  double     verticalPos[8];    
  double     horizontalPos[8];  
  // Actual the sizes of arrays are [26]. But [0-3] only related at IP1 
};

struct DIP_ACC_BEAM_ENERGY{
  int        Quality;
  int        Time;
  int        payload;
  char       dummy[4];     // for machines with 64 bit CPU
};

struct DIP_ACC_BEAM_INTENSITY{
  int        Quality;
  int        Time;
  LongLong   acqTimestamp;
  double     primitiveLifetime;
  double     totalIntensity;
};

struct DIP_ACC_BEAM_INTENSITYPERBUNCH{
  int        Quality;
  int        Time;
  float      averageBunchIntensities[3564];
  double     averageBeamIntensity;
  double     bestLifetime;
};

struct DIP_ACC_BEAM_INTENSITYPERBUNCH_S{
  int        Quality;
  int        Time;
  int        filledbunches[160];
  float      averageBunchIntensities[160];
};


struct DIP_ACC_BEAM_LUMINOSITYAVERAGE{
  int        Quality;
  int        Time;
  int        acqMode;
  char       dummy[4];
  double     meanLuminosity;
  double     meanCrossingAngle;
};

struct DIP_ACC_BEAM_LUMINOSITYPERBUNCH{
  int        Quality;
  int        Time;
  int        acqMode;
  char       dummy[4];
  double     bunchByBunchLuminosity[3564];
};

struct DIP_ACC_BEAM_LUMINOSITYSCAN{
  int        Quality;
  int        Time;
  char       LumiScan_Status[DIP_STRING_LENGTH];
  bool       Acquisition_Flag;
  char       dummy[4];
  char       Plane[DIP_STRING_LENGTH];
  int        IP;
  int        Beam;
  double     Step_Progress;
  double     Nominal_Separation;
};

struct DIP_ACC_BEAM_SIZE{
  int        Quality;
  int        Time;
  char       acqTime[DIP_STRING_LENGTH];
  char       cycleName[DIP_STRING_LENGTH];
  double     positionSet1; 
  double     positionSet2;
  int        acqCounter;
  int        acqState;
  int        nbDataSets;  
  int        planeSet1;
  int        planeSet2;
  char       dummy[4];
  double     sigmaSet1;
  double     sigmaSet2;
  char       deviceName[DIP_STRING_LENGTH];
  char       cycleTime[DIP_STRING_LENGTH];
  char       acqMsg[DIP_STRING_LENGTH];
  double     amplitudeSet2;
  double     amplitudeSet1;
};

// --  Handshake  ------------------------------------------------
struct DIP_ACC_HS_LHC_INJECTION{
  int     Quality;
  int     Time;
  char    value[DIP_STRING_LENGTH]; 
};

struct DIP_ACC_HS_LHC_ADJUST{
  int     Quality;
  int     Time;
  char    value[DIP_STRING_LENGTH]; 
};

struct DIP_ACC_HS_LHC_BEAMDUMP{
  int     Quality;  
  int     Time;
  char    value[DIP_STRING_LENGTH];
};

// --  Run Control  ----------------------------------------------
struct DIP_ACC_RUNCONTROL_BEAMMODE{
  int        Quality;
  int        Time;
  char       value[DIP_STRING_LENGTH];
};

struct DIP_ACC_RUNCONTROL_BUNCHCONFIG{
  int        Quality;
  int        Time;
  int        value[2808];
};

struct DIP_ACC_RUNCONTROL_FILLNUMBER{
  int        Quality;
  int        Time;
  int        value;
  char       dummy[4];
};

struct DIP_ACC_RUNCONTROL_FILLSCHEMA{
  int        Quality;
  int        Time;
  int        value;
  char       dummy[4];
};

struct DIP_ACC_RUNCONTROL_MACHINEMODE{
  int        Quality;
  int        Time;
  char       value[DIP_STRING_LENGTH];
};

struct DIP_ACC_RUNCONTROL_PAGE{
  int        Quality;
  int        Time;
  char       value[DIP_STRING_LENGTH];
};

struct DIP_ACC_RUNCONTROL_SAFEBEAM{
  int        Quality;
  int        Time;
  int        payload;
  char       dummy[4];
};

// --  Timing  ---------------------------------------------------
struct DIP_ACC_TIMING_POSTMORTEM{
  int        Quality;
  int        Time;
  LongLong   acqUTC;
  LongLong   cycleC;
  LongLong   oCounter;
  LongLong   acqNano;
  int        payload;
  char       dummy[4];
  LongLong   cycleNano ;
  LongLong   cycleUTC;
  LongLong   acqC;
};

// -- ATLAS CLOCK STATUS ----------------------------------------
struct DIP_ATLAS_CLOCK_SELECTION {
  int        Quality;
  int        Time;
  char       ORBIT[DIP_STRING_LENGTH];
  char       BC[DIP_STRING_LENGTH];
};

// -- LHCF DOSIMETERS ------------------------------------------
struct DIP_LHCF_DOSIMETER {
  int        Quality;
  int        Time;
  LongLong   seu_count3V;
  double     doseHighSensitivity;
  double     doseMediumSensitivity;
  double     neutronsHighSensitivity;
  double     temp;
  
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++                     LHCFDIPDATAH                           +++
// +++         This is a data container for DIP data token        +++
// +++         at high flequency  (every 10sec)                   +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LHCFDIPDATAH {
 public:

  LHCFSDATA_HEADER header;  // for identification of data type, version;  
  unsigned int     number;
  int              time;
  GSTATUS          status;
  char             dummy[4];
  
  DIP_LHCF_Arm                     Arm1;
  DIP_LHCF_Arm                     Arm2;
  DIP_LHCF_COINCIDENCE             Coincidence;
  DIP_LHCF_EXPTSTATUS              LHCf_Status;
  DIP_LHCF_INTERLOCK               Interlock;
  DIP_LHCF_LUMINOSITY              LHCf_Luminosity;
  DIP_LHCF_HS_LHC_INJECTION        LHCf_Injection;
  DIP_LHCF_HS_LHC_ADJUST           LHCf_Adjust;
  DIP_LHCF_HS_LHC_BEAMDUMP         LHCf_Beamdump;
  DIP_ACC_HS_LHC_INJECTION         Dummy_LHC_Injection;
  DIP_ACC_HS_LHC_ADJUST            Dummy_LHC_Adjust;
  DIP_ACC_HS_LHC_BEAMDUMP          Dummy_LHC_Beamdump;

  //DIP_ACC_BEAM_BPM                 BPM; // old structure, removed at 27 Feb 2010
  DIP_ACC_BEAM_BPM_M               BPM_LSS1L_B1;
  DIP_ACC_BEAM_BPM_M               BPM_LSS1L_B2;
  DIP_ACC_BEAM_BPM_M               BPM_LSS1R_B1;
  DIP_ACC_BEAM_BPM_M               BPM_LSS1R_B2;
  DIP_ACC_BEAM_ENERGY              Energy; 
  DIP_ACC_BEAM_INTENSITY           Beam1_intensity;
  DIP_ACC_BEAM_INTENSITY           Beam2_intensity;
  DIP_ACC_BEAM_INTENSITYPERBUNCH_S Beam1_intensityperbunch; 
  DIP_ACC_BEAM_INTENSITYPERBUNCH_S Beam2_intensityperbunch;
  //DIP_ACC_BEAM_INTENSITYPERBUNCH Beam1_intensityperbunch; 
  //DIP_ACC_BEAM_INTENSITYPERBUNCH Beam2_intensityperbunch;
  DIP_ACC_BEAM_LUMINOSITYAVERAGE   BranA_4L1_av;
  DIP_ACC_BEAM_LUMINOSITYAVERAGE   BranA_4R1_av;
  DIP_ACC_BEAM_LUMINOSITYAVERAGE   BranP_4L1_av;
  DIP_ACC_BEAM_LUMINOSITYAVERAGE   BranP_4R1_av;
  //DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranA_4L1_pb; in LHCFDIPDATAL
  //DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranA_4R1_pb; in LHCFDIPDATAL
  //DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranP_4L1_pb; in LHCFDIPDATAL 
  //DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranP_4R1_pb; in LHCFDIPDATAL
  DIP_ACC_BEAM_LUMINOSITYSCAN      Lumiscan;  // also recoded in LHCFDIPDATAVH 
  DIP_ACC_BEAM_SIZE                Beam1_size;
  DIP_ACC_BEAM_SIZE                Beam2_size;
  
  DIP_ACC_HS_LHC_INJECTION         LHC_Injection;
  DIP_ACC_HS_LHC_ADJUST            LHC_Adjust;
  DIP_ACC_HS_LHC_BEAMDUMP          LHC_Beamdump;

  DIP_ACC_RUNCONTROL_BEAMMODE      BeamMode; 
  //DIP_ACC_RUNCONTROL_BUNCHCONFIG   Beam1_bunchconfig; in LHCFDIPDATAL
  //DIP_ACC_RUNCONTROL_BUNCHCONFIG   Beam2_bunchconfig; in LHCFDIPDATAL
  DIP_ACC_RUNCONTROL_FILLNUMBER    Fillnumber;
  DIP_ACC_RUNCONTROL_FILLSCHEMA    Fillschema;
  DIP_ACC_RUNCONTROL_MACHINEMODE   Machinemode;
  DIP_ACC_RUNCONTROL_PAGE          Page1;
  DIP_ACC_RUNCONTROL_SAFEBEAM      Safebeam1;
  DIP_ACC_RUNCONTROL_SAFEBEAM      Safebeam2;
  
  DIP_ACC_TIMING_POSTMORTEM        Postmortem;
  
  DIP_ATLAS_CLOCK_SELECTION        Atlasclock;     // added at 02 Mar.2010

  DIP_LHCF_DOSIMETER               dosimeterL;     // added at 02 Mar.2010
  DIP_LHCF_DOSIMETER               dosimeterR;     // added at 02 Mar.2010

 public:
  LHCFDIPDATAH(){  
    header.headerword[0] = 0xCA;
    header.headerword[1] = 0xFE;
    header.headerword[2] = 0xCA;
    header.headerword[3] = 0xFE;
    header.headerword[4] = 0x0;
    header.headerword[5] = 0x0;
    header.headerword[6] = 0x0;
    header.headerword[7] = 0x0;
    strcpy(header.word,LHCFDIPDATAH_HEADER_WORD);
    header.version = LHCFDIPDATAH_VERSION;
    header.size    = sizeof(LHCFDIPDATAH);
    number = 0;
    time   = 0;

    Arm1.Time = 0;
    Arm2.Time = 0;
    Coincidence.Time = 0;
    LHCf_Status.Time = 0;
    Interlock.Time = 0;
    LHCf_Luminosity.Time = 0;
    LHCf_Injection.Time = 0;
    LHCf_Adjust.Time = 0;
    LHCf_Beamdump.Time = 0;
    //BPM.Time = 0;
    BPM_LSS1L_B1.Time = 0;
    BPM_LSS1L_B2.Time = 0;
    BPM_LSS1R_B1.Time = 0;
    BPM_LSS1R_B2.Time = 0;
    Energy.Time = 0;
    Beam1_intensity.Time = 0;
    Beam2_intensity.Time = 0;
    Beam1_intensityperbunch.Time = 0;
    Beam2_intensityperbunch.Time = 0; 
    BranA_4L1_av.Time = 0;
    BranA_4R1_av.Time = 0;
    BranP_4L1_av.Time = 0;
    BranP_4R1_av.Time = 0;
    Lumiscan.Time = 0;
    Beam1_size.Time = 0;
    Beam2_size.Time = 0;
    LHC_Injection.Time = 0;
    LHC_Adjust.Time = 0;
    LHC_Beamdump.Time = 0;
    BeamMode.Time = 0;
    Fillnumber.Time = 0;
    Fillschema.Time = 0;
    Machinemode.Time = 0;
    Page1.Time = 0;
    Safebeam1.Time = 0;
    Safebeam2.Time = 0;
    Postmortem.Time = 0;
  }
  
  char*        GetType(){return header.word;};
  int          GetVersion(){return header.version;}
  int          GetSize(){return header.size;}
  static char* GetClassType(){return LHCFDIPDATAH_HEADER_WORD;}
  static int   GetClassVersion(){return LHCFDIPDATAH_VERSION;}
  static int   GetClassSize(){return sizeof(LHCFDIPDATAH);}
  
  bool  CheckType(){
    return (strcmp(header.word,GetClassType())==0) ? true : false;
  }

  bool  CheckVersion(){
    return (header.version == GetClassVersion()) ? true : false;
  }
  
  bool  CheckSize(){
    return (header.size == GetClassSize()) ? true : false;
  }
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++                     LHCFDIPDATAL                           +++
// +++         This is a data container for DIP data token        +++
// +++         at low flequency  (every 1min)                     +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LHCFDIPDATAL {
 public:

  LHCFSDATA_HEADER header;  // for identification of data type, version;  
  unsigned int     number;
  int              time;
  GSTATUS          status;
  char             dummy[4];

  DIP_ACC_BEAM_INTENSITYPERBUNCH   Beam1_intensityperbunch; 
  DIP_ACC_BEAM_INTENSITYPERBUNCH   Beam2_intensityperbunch;

  DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranA_4L1_pb;
  DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranA_4R1_pb;
  DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranP_4L1_pb;
  DIP_ACC_BEAM_LUMINOSITYPERBUNCH  BranP_4R1_pb;
  
  DIP_ACC_RUNCONTROL_BUNCHCONFIG   Beam1_bunchconfig;
  DIP_ACC_RUNCONTROL_BUNCHCONFIG   Beam2_bunchconfig; 

 public:
  LHCFDIPDATAL(){
    header.headerword[0] = 0xCA;
    header.headerword[1] = 0xFE;
    header.headerword[2] = 0xCA;
    header.headerword[3] = 0xFE;
    header.headerword[4] = 0x0;
    header.headerword[5] = 0x0;
    header.headerword[6] = 0x0;
    header.headerword[7] = 0x0;
    strcpy(header.word,LHCFDIPDATAL_HEADER_WORD);
    header.version = LHCFDIPDATAL_VERSION;
    header.size    = sizeof(LHCFDIPDATAL);
    number = 0;
    time   = 0;

    Beam1_intensityperbunch.Time = 0;
    Beam2_intensityperbunch.Time = 0;
    BranA_4L1_pb.Time = 0;
    BranA_4R1_pb.Time = 0;
    BranP_4L1_pb.Time = 0;
    BranP_4R1_pb.Time = 0;
    Beam1_bunchconfig.Time = 0;
    Beam2_bunchconfig.Time = 0;  
  }
  
  char*        GetType(){return header.word;};
  int          GetVersion(){return header.version;}
  int          GetSize(){return header.size;}
  static char* GetClassType(){return LHCFDIPDATAL_HEADER_WORD;}
  static int   GetClassVersion(){return LHCFDIPDATAL_VERSION;}
  static int   GetClassSize(){return sizeof(LHCFDIPDATAL);}
  
  bool  CheckType(){
    return (strcmp(header.word,GetClassType())==0) ? true : false;
  }

  bool  CheckVersion(){
    return (header.version == GetClassVersion()) ? true : false;
  }
  
  bool  CheckSize(){
    return (header.size == GetClassSize()) ? true : false;
  }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++                     LHCFDIPDATAVH                          +++
// +++         This is a data container for DIP data token        +++
// +++         at very high flequency (every 1sec)                +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LHCFDIPDATAVH {
 public:

  LHCFSDATA_HEADER header;  // for identification of data type, version;  
  unsigned int     number;
  int              time;
  GSTATUS          status;
  char             dummy[4];

  DIP_ACC_BEAM_LUMINOSITYSCAN      Lumiscan;

 public:
  LHCFDIPDATAVH(){
    header.headerword[0] = 0xCA;
    header.headerword[1] = 0xFE;
    header.headerword[2] = 0xCA;
    header.headerword[3] = 0xFE;
    header.headerword[4] = 0x0;
    header.headerword[5] = 0x0;
    header.headerword[6] = 0x0;
    header.headerword[7] = 0x0;
    strcpy(header.word,LHCFDIPDATAVH_HEADER_WORD);
    header.version = LHCFDIPDATAVH_VERSION;
    header.size    = sizeof(LHCFDIPDATAVH);
    number = 0;
    time   = 0;
    
    Lumiscan.Time = 0;
  }
  
  char*        GetType(){return header.word;}
  int          GetVersion(){return header.version;}
  int          GetSize(){return header.size;}
  static char* GetClassType(){return LHCFDIPDATAVH_HEADER_WORD;}
  static int   GetClassVersion(){return LHCFDIPDATAVH_VERSION;}
  static int   GetClassSize(){return sizeof(LHCFDIPDATAVH);}
  
  bool  CheckType(){
    return (strcmp(header.word,GetClassType())==0) ? true : false;
  }

  bool  CheckVersion(){
    return (header.version == GetClassVersion()) ? true : false;
  }
  
  bool  CheckSize(){
    return (header.size == GetClassSize()) ? true : false;
  }
};

#endif
