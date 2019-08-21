#ifndef __LHCFRUNINFORTABLE_H__
#define __LHCFRUNINFORTABLE_H__

// --------------------------------------------------------------------
//                    LHCfRunInfo &  LHCfRunInfoTable                    
// --------------------------------------------------------------------

#include <TObject.h>

#include <iostream>
#include <string>
#include <vector>
#include "globaldef.h"
#include "A1Cal1.h"
#include "A1Cal2.h"
#include "A2Cal1.h"
#include "A2Cal2.h"
using namespace std;

class LHCfRunInfo {
 public:
  // definition 
  static const int NBUNCHES      = 200;
  static const int STRING_LENGTH = 512; 
  enum DEF_BEAMTAG{
    COLLIDING    = 1,
    NONCOLLIDING = 2,
    DISPLACED    = 3
  };

  int   ioformat;                         // Format of the ASCII file.
  
 public:
  // --- GENERAL INFORMATION---
  int   run;                              // Run Number
  int   start_time;                       // DAQ start time.
  int   end_time;                         // DAQ end time.
  char  general_comments[STRING_LENGTH];  // Comments

  // --- DAQ INFORMATION ---
  int   a1_runmode;                       // Run Mode of Frontend1
  int   a2_runmode;                       // Run Mode of Frontend2
  char  LTPmode[32];                      // Mode of the LTP module 
  char  a1_LogicMode[32];                 // Run Mode
  char  a2_LogicMode[32];                 // Run Mode
  char  a1_V1495Load[32];
  char  a2_V1495Load[32];  
  char  a1_V1495Setup[32];
  char  a2_V1495Setup[32];  
  char  a1_GPIOLoad[32];                  // GPIO Load File for Arm1
  char  a2_GPIOLoad[32];                  // GPIO Load File for Arm2
  char  a1_GPIOSetup[32];                 // GPIO Setup for Arm1
  char  a2_GPIOSetup[32];                 // GPIO Setup for Arm2
  char  a1_Discriminator[32];             // Discriminator setup for Arm1
  char  a2_Discriminator[32];             // Discriminator setup for Arm2
  int   a1_scifidaq;                      // SCIFI   DAQ, 1: ON, 0: OFF, -1: Unknown
  int   a2_silicondaq;                    // Silicon DAQ, 1: ON, 0: OFF, -1: Unknown
  char  a1_PMTgain[32];                   // Gain Configuration of Arm1 PMTs (string)
  char  a2_PMTgain[32];                   // Gain Configuration of Arm2 PMTs (string)
  char  a1_scifigain[32];                 // Gain Configuration of SciFi (string)
  char  a2_silicongain[32];               // Gain Configuration of Silicon (string)
  char  a1_position[32];                  // Arm1 Detector position
  char  a2_position[32];                  // Arm2 Detector position
  int   daq_beam1_scl_nbunch_offset;      // Offset of BC counts due to GPIO Configuration.
  int   daq_beam2_scl_nbunch_offset;      // Offset of BC counts due to GPIO Configuration.
  char  daq_comments[STRING_LENGTH];      // Comments
  
  // --- NUMBER OF EVENTS ---
  int   nevent;                           // Total events in run including SlowControl. 
  int   a1_nevent;                        // Number of Arm1 events
  int   a1_nevent_L2TA;                   // Number of Arm1 L2TA events
  int   a1_nevent_L2TA_MB;                // Number of Arm1 L2TA (Minimum bias) events
  int   a1_nevent_L2TA_SP;                // Number of Arm1 L2TA (Pi0 trigger) events
  int   a1_nevent_L2TP;                   // Number of Arm1 L2TP(Pedestal) event
  int   a1_nevent_laser;                  // Number of Arm1 Laser events
  int   a2_nevent;                        // Number of Arm2 events
  int   a2_nevent_L2TA;                   // Number of Arm2 L2TA(Shower) events  
  int   a2_nevent_L2TA_MB;                // Number of Arm1 L2TA (Minimum bias) events
  int   a2_nevent_L2TA_SP;                // Number of Arm1 L2TA (Pi0 trigger) events
  int   a2_nevent_L2TP;                   // Number of Arm2 L2TP(Pedestal) events
  int   a2_nevent_laser;                  // Number of Arm2 Laser events
  // For Operation 2015
  int   a1_nevent_L2T_Shower;
  int   a1_nevent_L2T_Special;
  int   a1_nevent_L2T_Pedestal;
  int   a1_nevent_L2T_L1T;
  int   a1_nevent_L2T_FC;
  int   a2_nevent_L2T_Shower;
  int   a2_nevent_L2T_Special;
  int   a2_nevent_L2T_Pedestal;
  int   a2_nevent_L2T_L1T;
  int   a2_nevent_L2T_FC;
  int   a1scl_nevent;                     // Number of Arm1 Scaler events
  int   a2scl_nevent;                     // Number of Arm2 Scaler events
  int   sc_nevent;                        // Number of SlowControl events
  int   dipl_nevent;                      // Number of DIPL events
  int   diph_nevent;                      // Number of DIPH events
  int   dipvh_nevent;                     // Number of DIPVH events
  unsigned int a1_nevent_l1t;             // Number of Arm1 L1T
  unsigned int a1_nevent_l1t_enable;      // Number of Arm1 L1T with BEAM and ENABLE
  unsigned int a2_nevent_l1t;             // Number of Arm2 L1T
  unsigned int a2_nevent_l1t_enable;      // Number of Arm2 L1T with BEAM and ENABLE
  int   a1_nevent_presetMB;
  int   a1_nevent_presetSP;
  int   a2_nevent_presetMB;
  int   a2_nevent_presetSP;
  int   a2_ncrcerror;                     // Number of CRC error;

  // --- BEAM CONFIGURATION ---
  int   stable_beam;                      // Stable Beam Flag  -1: unknown, 0: no 1:stable_beam
  int   crossingangle;                    // Clossing Angle -1: unknown, 0; no, 1; yes
  int   beam1_nbunches;                   // Number of Bunches of Beam1
  int   beam2_nbunches;                   // Number of Bunches of Beam2
  int   beam1_bunches[NBUNCHES];          // Bunch Position of Beam1 
  int   beam2_bunches[NBUNCHES];          // Bunch Position of Beam2
  int   beam1_tag[NBUNCHES];              // Tag of each Bunch, 1: col., 2: non, 3:displaced col.  < 0 : bad bunch 
  int   beam2_tag[NBUNCHES];              // Tag of each Bunch, 1: col., 2: non, 3:displaced col.  < 0 : bad bunch 
                                          // if bunches quality is bad, negative filled. 
  double beam1_avintensity;               // Average Intensity of Beam1 (in time window of Analysis cut.)
  double beam2_avintensity;               // Average Intensity of Beam2 (in time window of Analysis cut.)
  double beam1_avintensitypb[NBUNCHES];   // Average Intensity per Bunch  (in time window of Analysis cut.)
  double beam2_avintensitypb[NBUNCHES];   // Average Intensity per Bunch  (in time window of Analysis cut.)
  double beam_avluminositypb[NBUNCHES];   // Average Luminosity per Bunch (in same order as beam1_bunches)
  int    done_lumiscan;                   // Done Lumonosity Scan -1:unknown, 0: no, the others IP.                
  char   beam_comments[STRING_LENGTH];    // Comments
  
  // --- ANALYSIS INFORMATION ---
  int   analysis_quality;                 // Data Quality for Physics Analysis 1: good, -1:bad
  int   analysis_cut_stime;               // Start Time of the Good Quality Data;
  int   analysis_cut_etime;               // End Time of the Good Quality Data;
  int   analysis_a1_nevent;               // Number of Arm1 Events in the Time Window.
  int   analysis_a1_nevent_L2TA;          // Number of Arm1 Shower Events in the Time Window.
  int   analysis_a2_nevent;               // Number of Arm2 Events in the Time Window.
  int   analysis_a2_nevent_L2TA;          // Number of ARm2 Shower Events in the Time Window.
  char  analysis_comments[STRING_LENGTH]; // Comments

 public:
  LHCfRunInfo();
  virtual ~LHCfRunInfo();
  void clear();                                    
  void clear_general(char op[]="");
  void clear_daq(char op[]="");
  void clear_nevents(char op[]="");
  void clear_beam(char op[]="");
  void clear_analysis(char op[]="");
  int  WriteFile(char *filename,int format=1); 
  int  Print(std::ostream& out= std::cout,int format=-1);  
  void PrintGeneral(std::ostream& out= std::cout,int format=-1);
  void PrintDAQ(std::ostream& out= std::cout,int format=-1);
  void PrintNEvents(std::ostream& out= std::cout,int format=-1);
  void PrintBeam(std::ostream& out= std::cout,int format=-1);
  void PrintAnalysis(std::ostream& out= std::cout,int format=-1);
  
  int  Read(std::istream& in);
  int  ReadFile(char* filename);                   // Read the file with ASCII format.
  void removespace(std::string& s);                // internal function.
 
  int  IndexToBunch(int beam,int index); 
  int  BunchToIndex(int beam,int bunch);           // beam: 1 or 2
  int  CountBCtoBunch(int beam, int count);        // BC counts to #Bunch
  int  CountBCtoIndex(int beam, int count);        // BC counts to Index 
  int  GetBunchTagByIndex(int beam,int index);     // 
  int  GetBunchTag(int beam,int bunch);            // 
  int  GetBunchTagByCountBC(int beam, int bunch);  // 
  int  GetBunchTag(A1Cal1* cal){return GetBunchTagByCountBC(2,cal->counter[23]);}
  int  GetBunchTag(A2Cal1* cal){return GetBunchTagByCountBC(1,cal->counter[23]);}

  int  CheckTime(int t);                           // if t is in time window of physics analysis, return 1. if not, return 0.  
  int  CheckTime(A1Cal1* cal){ return CheckTime((int)cal->time[0]); }
  int  CheckTime(A1Cal2* cal){ return CheckTime((int)cal->time[0]); }
  int  CheckTime(A2Cal1* cal){ return CheckTime((int)cal->time[0]); }
  int  CheckTime(A2Cal2* cal){ return CheckTime((int)cal->time[0]); }
  int  CheckBunchQuality(A1Cal1* cal);            // if bunch quality is good, return 1. if not, return 0.
  int  CheckBunchQuality(A2Cal1* cal);            // if bunch quality is good, return 1. if not, return 0.
  
  string CutdownGPIOSetup(char csetup[]);

  // for fast conversion of #bunch->#index in beam1_bunches.
  static int    buf_run;
  static int    buf_beam1_nbunches;
  static int    buf_beam2_nbunches;
  static int    buf_beam1_bunches[NBUNCHES];
  static int    buf_beam2_bunches[NBUNCHES];
  static int    buf_beam1_bunches_index[3565];
  static int    buf_beam2_bunches_index[3565];

  // Default Values:
  static const int DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET = 203;
  static const int DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET = 202;

  ClassDef(LHCfRunInfo,1);   // Run information
};


// --------------------------------------------------------------------
// -------                 LHCfRunInfoTable                      ------
// --------------------------------------------------------------------

class LHCfRunInfoTable{
 public:
  int           ioformat;
  int           ninfo;
  int           iinfo;   // current info number
  int           irun;    // current run number
  vector<LHCfRunInfo*> runinfo;  //!
  
 public:
  LHCfRunInfoTable(); 
  LHCfRunInfoTable(char* filename,int format=-1);
  virtual ~LHCfRunInfoTable();  

  void  Clear();
  int   ReadTable(char filename[256]);
  int   WriteTable(char* filename,int format=-1);
  int   GetNinfo(){return ninfo;}
  LHCfRunInfo*  SetRun(int run);
  LHCfRunInfo*  GetRunInfo(int run){return SetRun(run);} 
  LHCfRunInfo*  Get(int run){return SetRun(run);} 
  LHCfRunInfo*  GetIinfo(int i);
  LHCfRunInfo*  CreateInfo();     // Create new RunInfo   
  
  ClassDef(LHCfRunInfoTable,1);   // Run information table
};

#endif
