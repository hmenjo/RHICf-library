#ifndef __RHICFRUNINFORTABLE_H__
#define __RHICFRUNINFORTABLE_H__

// --------------------------------------------------------------------
//                    RHICfRunInfo &  RHICfRunInfoTable                    
// --------------------------------------------------------------------

#include <TObject.h>

#include <iostream>
#include <string>
#include <vector>
#include "globaldef.h"
#include "A1Cal1.h"
#include "A1Cal2.h"
using namespace std;

class RHICfRunInfo {
 public:
  // definition 
  static const Int_t NBUNCHES      = 200;
  static const Int_t STRING_LENGTH = 512; 
  enum DEF_BEAMTAG{
    COLLIDING    = 1,
    NONCOLLIDING = 2,
    DISPLACED    = 3
  };

  Int_t   ioformat;                         // Format of the ASCII file.
  
 public:
  // --- GENERAL INFORMATION---
  Int_t   run;                              // Run Number
  Int_t   start_time;                       // DAQ start time.
  Int_t   end_time;                         // DAQ end time.
  char  general_comments[STRING_LENGTH];  // Comments

  // --- DAQ INFORMATION ---
  Int_t   a1_runmode;                       // Run Mode of Frontend1
  char    a1_LogicMode[256];                // Run Mode
  char    a1_GPIOLoad[256];                 // GPIO Load File for Arm1
  char    a1_GPIOLoadFiles[2][256];            // GPIO Load File for Arm1
  char    a1_GPIOSetup[256];                // GPIO Setup for Arm1
  char    a1_Discriminator[256];            // Discriminator setup for Arm1
  Int_t   a1_scifidaq;                      // SCIFI   DAQ, 1: ON, 0: OFF, -1: Unknown 
  Int_t   common_operation;                 // Common Operation Mode 1:Yes 0:No, -1: Unknown
  char    a1_PMTgain[32];                   // Gain Configuration of Arm1 PMTs (string)
  char    a1_scifigain[32];                 // Gain Configuration of SciFi (string)
  char    a1_position[32];                  // Arm1 Detector position
  Int_t   daq_beam1_scl_nbunch_offset;      // Offset of BC counts due to GPIO Configuration.
  Int_t   daq_beam2_scl_nbunch_offset;      // Offset of BC counts due to GPIO Configuration.
  char    daq_comments[STRING_LENGTH];      // Comments
  
  // --- NUMBER OF EVENTS ---
  Long64_t   nevent;                        // Total events in run including SlowControl. 
  Long64_t   a1_nevent;                     // Number of Arm1 events5
  Long64_t   a1_nevent_L3T_Shower;
  Long64_t   a1_nevent_L3T_Special1;
  Long64_t   a1_nevent_L3T_Special2;
  Long64_t   a1_nevent_L3T_Pedestal;
  Long64_t   a1_nevent_L3T_L1T;
  Long64_t   a1_nevent_L3T_Shower_TS;
  Long64_t   a1_nevent_L3T_Shower_TL;       
  Long64_t   a1_nevent_L3T_STAR;
  Long64_t   a1_nevent_STAR_Only;
  Long64_t   a1scl_nevent;                  // Number of Arm1 Scaler events
  Long64_t   sc_nevent;                     // Number of SlowControl events
  ULong64_t  a1_nevent_l1t;                 // Number of Arm1 L1T
  ULong64_t  a1_nevent_l1t_enable;          // Number of Arm1 L1T with BEAM and ENABLE
  Int_t      a1_nevent_presetMB;
  Int_t      a1_nevent_presetSP;

  // --- BEAM CONFIGURATION ---
  Int_t   stable_beam;                      // Stable Beam Flag  -1: unknown, 0: no 1:stable_beam
  Int_t   crossingangle;                    // Clossing Angle -1: unknown, 0; no, 1; yes
  Int_t   beam1_nbunches;                   // Number of Bunches of Beam1
  Int_t   beam2_nbunches;                   // Number of Bunches of Beam2
  Int_t   beam1_bunches[NBUNCHES];          // Bunch Position of Beam1 
  Int_t   beam2_bunches[NBUNCHES];          // Bunch Position of Beam2
  Int_t   beam1_tag[NBUNCHES];              // Tag of each Bunch, 1: col., 2: non, 3:displaced col.  < 0 : bad bunch 
  Int_t   beam2_tag[NBUNCHES];              // Tag of each Bunch, 1: col., 2: non, 3:displaced col.  < 0 : bad bunch 
                                          // if bunches quality is bad, negative filled. 
  Double_t beam1_avintensity;               // Average Intensity of Beam1 (in time window of Analysis cut.)
  Double_t beam2_avintensity;               // Average Intensity of Beam2 (in time window of Analysis cut.)
  Double_t beam1_avintensitypb[NBUNCHES];   // Average Intensity per Bunch  (in time window of Analysis cut.)
  Double_t beam2_avintensitypb[NBUNCHES];   // Average Intensity per Bunch  (in time window of Analysis cut.)
  Double_t beam_avluminositypb[NBUNCHES];   // Average Luminosity per Bunch (in same order as beam1_bunches)
  Int_t    done_lumiscan;                   // Done Lumonosity Scan -1:unknown, 0: no, the others IP.                
  char     beam_comments[STRING_LENGTH];    // Comments
  
  // --- ANALYSIS INFORMATION ---
  Int_t   analysis_quality;                 // Data Quality for Physics Analysis 1: good, -1:bad
  Int_t   analysis_cut_stime;               // Start Time of the Good Quality Data;
  Int_t   analysis_cut_etime;               // End Time of the Good Quality Data;
  Int_t   analysis_a1_nevent;               // Number of Arm1 Events in the Time Window.
  //Int_t   analysis_a1_nevent_L2T_Shower;    // Number of Arm1 Shower Events in the Time Window.
  //Int_t   analysis_a1_nevent_L2T_Special;   // Number of Arm1 Shower Events in the Time Window.
  char  analysis_comments[STRING_LENGTH]; // Comments

 public:
  RHICfRunInfo();
  virtual ~RHICfRunInfo();
  void   clear();                                    
  void   clear_general(char op[]="");
  void   clear_daq(char op[]="");
  void   clear_nevents(char op[]="");
  void   clear_beam(char op[]="");
  void   clear_analysis(char op[]="");
  Int_t  WriteFile(char *filename,Int_t format=1); 
  Int_t  Print(std::ostream& out= std::cout,Int_t format=-1);  
  void   PrintGeneral(std::ostream& out= std::cout,Int_t format=-1);
  void   PrintDAQ(std::ostream& out= std::cout,Int_t format=-1);
  void   PrintNEvents(std::ostream& out= std::cout,Int_t format=-1);
  void   PrintBeam(std::ostream& out= std::cout,Int_t format=-1);
  void   PrintAnalysis(std::ostream& out= std::cout,Int_t format=-1);
  
  Int_t  Read(std::istream& in);
  Int_t  ReadFile(char* filename);                   // Read the file with ASCII format.
  void   removespace(std::string& s);                // internal function.
 
  Int_t  IndexToBunch(Int_t beam,Int_t index); 
  Int_t  BunchToIndex(Int_t beam,Int_t bunch);           // beam: 1 or 2
  Int_t  CountBCtoBunch(Int_t beam, Int_t count);        // BC counts to #Bunch
  Int_t  CountBCtoIndex(Int_t beam, Int_t count);        // BC counts to Index 
  Int_t  GetBunchTagByIndex(Int_t beam,Int_t index);     // 
  Int_t  GetBunchTag(Int_t beam,Int_t bunch);            // 
  Int_t  GetBunchTagByCountBC(Int_t beam, Int_t bunch);  // 
  Int_t  GetBunchTag(A1Cal1* cal){return GetBunchTagByCountBC(2,cal->counter[23]);}

  Int_t  CheckTime(Int_t t);                           // if t is in time window of physics analysis, return 1. if not, return 0.  
  Int_t  CheckTime(A1Cal1* cal){ return CheckTime((int)cal->time[0]); }
  Int_t  CheckBunchQuality(A1Cal1* cal);            // if bunch quality is good, return 1. if not, return 0.

  string CutdownGPIOSetup(char csetup[]);

  // for fast conversion of #bunch->#index in beam1_bunches.
  static Int_t    buf_run;
  static Int_t    buf_beam1_nbunches;
  static Int_t    buf_beam2_nbunches;
  static Int_t    buf_beam1_bunches[NBUNCHES];
  static Int_t    buf_beam2_bunches[NBUNCHES];
  static Int_t    buf_beam1_bunches_index[3565];
  static Int_t    buf_beam2_bunches_index[3565];

  // Default Values:
  static const Int_t DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET = 203;
  static const Int_t DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET = 202;

  ClassDef(RHICfRunInfo,1);   // Run information
};


// --------------------------------------------------------------------
// -------                 RHICfRunInfoTable                      ------
// --------------------------------------------------------------------

class RHICfRunInfoTable{
 public:
  Int_t           ioformat;
  Int_t           ninfo;
  Int_t           iinfo;   // current info number
  Int_t           irun;    // current run number
  vector<RHICfRunInfo*> runinfo;  //!
  
 public:
  RHICfRunInfoTable(); 
  RHICfRunInfoTable(char* filename,Int_t format=-1);
  virtual ~RHICfRunInfoTable();  

  void    Clear();
  Int_t   ReadTable(char filename[256]);
  Int_t   WriteTable(char* filename,Int_t format=-1);
  Int_t   GetNinfo(){return ninfo;}
  RHICfRunInfo*  SetRun(Int_t run);
  RHICfRunInfo*  GetRunInfo(Int_t run){return SetRun(run);} 
  RHICfRunInfo*  Get(Int_t run){return SetRun(run);} 
  RHICfRunInfo*  GetIinfo(Int_t i);
  RHICfRunInfo*  CreateInfo();     // Create new RunInfo   
  
  ClassDef(RHICfRunInfoTable,1);   // Run information table
};

#endif
