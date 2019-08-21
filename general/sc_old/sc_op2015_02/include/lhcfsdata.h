// ***************************************************************** 
// ***   Data format of the LHCf Slow Control System             ***
// *** --------------------------------------------------------- ***
// *** 04 Jun. 2008 : first edited by H.MENJO                    ***
// *** 05 Aug. 2009 : Modified as following by H.MENJO           ***
// ***    - Change the type of LHCFSDATA from structure to class.*** 
// ***    - Added a header with tag, version number and size of  ***
// ***      the structure.                                       ***
// ***    - Changed a number of channels for the 3rd slot of     ***
// ***      CPWS2 from 8 to 12.                                  ***
// ***      CPWS2_DATA.slot3[8] -> CPWS2_DATA.slot3[12]          ***
// ***    - Added dummy charactors in some structures for DIP    ***
// ***      due to keep consistency of structrure size between   ***
// ***      32bit PC's and 64bit PC's.                           ***
// ***    If you add some structrues in LHCFSDATA, the size of   ***
// ***    the structrue should be a multiple of 8 bytes.         ***
// *** 02 Nov. 2009 : removed DIP data from LHCFSDATA and        ***
// *** 19 Jan. 2009 : Change format of                           ***
// ***                LHCFSDATA_HEADER::headerword               ***
// ***                char -> unsigned char                      *** 
// *****************************************************************

#ifndef __LHCFSDATA_H__ 
#define __LHCFSDATA_H__ 

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string.h>

#define LHCFSDATA_HEADER_WORD  "LHCFSC"
#define LHCFSDATA_VERSION      102

#define AGN6700_MAXNUM   4         //Max number of Agilent N6700 modules
#define AGN6700_SECTIONS 4         //Number of output sections for each Agilent
#define AGN6700_NIVMEAS  4         //# of I/V measured quantities

typedef unsigned int GSTATUS;

struct LHCFSDATA_HEADER {
  unsigned char headerword[8];
  char          word[8];
  int           version;
  int           size;
};

// -----------------------------------------------------------------
// For SY2527: CAEN Power Supply
// Note: for each tower of both detectors there are 16 scintillators.
// -----------------------------------------------------------------
struct CPWS_CH {
  float          vmon;            // Voltage  [Volt]
  float          imon;            // Current. The unit depend on the power supply board.
  unsigned int   status;          // Status flag, bit field
};

struct CPWS1_DATA {
  GSTATUS  status;
  CPWS_CH  slot0[12];            // [A1833] H.V. board (12 ch)   for 20mm-(ch 00->11) 
  CPWS_CH  slot1[12];            // [A1833] H.V. board.          for 20mm-(ch 12->15) and 40mm-(ch 00->07) 
  CPWS_CH  slot2[12];            // [A1833] H.V. board.          for 40mm-(ch 08->15) 
  CPWS_CH  slot3[6];             // [A1513B] L.V. board. for ???
  CPWS_CH  slot5[6];             // [A1513B] L.V. board. for ???
  float    temperature[6];       // Temperateure of each board. [degrees centigrage]
};

struct CPWS2_DATA {  
  GSTATUS  status;
  CPWS_CH  slot0[12];            // [A1833] H.V. board. for 25mm-12,... 25mm-07 
  CPWS_CH  slot1[12];            // [A1833] H.V. board. for 25mm-12,... 32mm-07
  CPWS_CH  slot2[12];            // [A1833] H.V. board. for 32mm-08,... 32mm-15 and laser monitor 
  CPWS_CH  slot3[12];            // [??????] H.V. board. for Silicon
  CPWS_CH  slot4[6];             // [A1513B] L.V. board. for F.C. and Manipulator
  float    temperature[6];       // Temperateure of each board. [degrees centigrage]
};

// ---------------------------------------------------------------
// For Agilent LV Power Supply
// ---------------------------------------------------------------

struct AGILENT_CH {                  //Data for single output channel
  GSTATUS  status;                   //(MSB) "5b Operation Status" + "16b Questionable Status" (LSB)
  float    vmon;
  float    imon;
};
struct AGILENT_MOD {                 //Data for single module (4 ch)
  GSTATUS      status;               //(MSB) "1bit ON/OFF" + "8bit Std ev Status" + "8bit Status byte" (LSB)
  AGILENT_CH   ch[AGN6700_SECTIONS]; //single ch of LV Power Supplies for Arm2 Silicon System
};

struct AGILENT_DATA {                //Data for all Agilent N6700B (4 mod)
  GSTATUS      status;               //bits: (MSB) 4_unused + 4_warning + 4_err + 4_on/off (LSB)
  AGILENT_MOD  mod[AGN6700_MAXNUM];  //LV Power Supplies for Arm2 Silicon System
};

// ---------------------------------------------------------------
// For TRHX
// ---------------------------------------------------------------
struct TRHX_DATA{
  GSTATUS  status;
  float    temp[12];                 //temperature sensors on Arm2 detector
};

// ---------------------------------------------------------------
// For Encoder Counters of Manipulators
// ---------------------------------------------------------------
struct ENCODER_DATA{
  GSTATUS  status;
  float    encoder1;                 //read posistion of Arm1 manipulator
  float    encoder2;                 //read posistion of Arm2 manipulator
};

// ---------------------------------------------------------------
// For PCI AD converters
struct ADC_DATA{
  GSTATUS  status;
  unsigned short  adc[16];
  float	          vol[16];
  float           cal[16];
};

// ****************************************************************
// ---------------------------------------------------------------
// ALL DATA
// ---------------------------------------------------------------
// ****************************************************************


class LHCFSDATA {
 public:
  LHCFSDATA_HEADER header;
  unsigned int     number;
  int              time;
  
  CPWS1_DATA       cpws1;
  CPWS2_DATA       cpws2;
  AGILENT_DATA     ag;
  TRHX_DATA        trhx;
  ENCODER_DATA     encoder;
  ADC_DATA         adc;
 
 public:
  LHCFSDATA(){
    header.headerword[0] = 0xCA;
    header.headerword[1] = 0xFE;
    header.headerword[2] = 0xCA;
    header.headerword[3] = 0xFE;
    header.headerword[4] = 0x0;
    header.headerword[5] = 0x0;
    header.headerword[6] = 0x0;
    header.headerword[7] = 0x0;
    strcpy(header.word,LHCFSDATA_HEADER_WORD);
    header.version = LHCFSDATA_VERSION;
    header.size = sizeof(LHCFSDATA);
    number = 0;
    time   = 0;
  }
  int        GetVersion(){return header.version;}
  int        GetSize(){return header.size;}
  static int GetClassVersion(){return LHCFSDATA_VERSION;}
  static int GetClassSize(){return sizeof(LHCFSDATA);}
};

#endif 
