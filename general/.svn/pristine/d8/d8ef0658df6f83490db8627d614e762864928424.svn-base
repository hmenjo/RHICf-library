
//#define MAX_SIZE 0x1000000     /* 16 MB */
//#define TRACE_MAP 1
//#define EVENT_SIZE 14240       /* 3560*4 = 14240 Byte (= 3560 word) */

//#define NBOARDS 4                                                 /* # of readout boards */
//#define NFIFOXBOARD 16                                            /* # of FIFO */
//#define NBLOCKSXFIFO 12                                           /* # of trasmission blocks per each FIFO */
//#define NBYTESXBLOCK 18                                           /* Data size (1 block) */
//#define NBYTESXBOARD (NFIFOXBOARD*NBLOCKSXFIFO*NBYTESXBLOCK)      /* Data size (1 board) = 3456 Byte */

//#define NSAMPL (3)                         /* # of samplings (= # of read PACE cols) */
//#define NLAYXBOARD 2                       /* # of detector layers read by 1 board */
//#define NCHIPXLAY 12                       /* # of front-end chips per detector layer */
//#define NCHIPXBOARD (NLAYXBOARD*NCHIPXLAY) /* # of PACEs per readout board */


// +++++++ Definition from Data.h ++++++++

//---------------------
// Datafile definitions
//---------------------

#ifndef __SILICON_DATA_H__
#define __SILICON_DATA_H__

#define EVENT_PER_FILE (10000)  // Max number of events in one file
#define HEAD_ID (0xF1C0F1C0)
#define VME_ACQ_SETS 1          // number of aquisition set
#define VME_ACQ_FLAG 0          // packet integrity flag. 0=ok, 1=error
#define VME_ACQ_ERROR 1         // 
#define EVENT_MAX_SIZE (TRACKER_BUFF_SIZE)
#define NBYTEWORD 1             // 1 word is 1 byte
#define MESSAGE_RATE (100)

#define TRAIL_ID (0xC1A0C1A0)

#define DAQMAGIC1 (0x73)  // 1st magic word at start of readout board trasm
#define DAQMAGIC2 (0x21)  // 2nd magic word at start of readout board trasm

#define NSAMPL (3)        // # of samplings (= # of read PACE cols)

//---------------------
// Hardware definitions
//---------------------

#define NBOARDS 4                          // # of readout boards
#define NLAYXBOARD 2                       // # of detector layers read by 1 board
#define NCHIPXLAY 12                       // # of front-end chips per detector layer
#define NCHIPXBOARD (NLAYXBOARD*NCHIPXLAY) // # of PACEs per readout board
#define NCHXCHIP 32                        // # of channels per front-end chip
#define NREADXCH 3                         // # of reading per channels
#define NCHANTOT (NBOARDS*NLAYXBOARD*NCHIPXLAY*NREADXCH*NCHXCHIP)  // Total # of readout channels

#define NCHXLAY (NCHIPXLAY*NCHXCHIP)       // # of channels per detector layer

#define NFIFOXBOARD 16                     // # of FIFO
#define NBLOCKSXFIFO 12                    // # of trasmission blocks per each FIFO
#define NWORDSXFIFO (NCHXCHIP*NREADXCH)
#define NWORDSXBLOCK (NWORDSXFIFO/NBLOCKSXFIFO)

#define NBYTESXBLOCK 18                                           // Data size (1 block)
#define NBYTESXFIFO (NBLOCKSXFIFO*NBYTESXBLOCK)                   // Data size (1 FIFO)
#define NBYTESXBOARD (NFIFOXBOARD*NBLOCKSXFIFO*NBYTESXBLOCK)      // Data size (1 board)
#define NBYTESXEV (NBOARDS*NBYTESXBOARD)                          // Data size (1 ev)

#define TRKBYTESXBOARD (sizeof(struct DATA_Header)+NBYTESXBOARD+sizeof(struct DATA_Trailer))
#define TRKBYTESXEV (NBOARDS*TRKBYTESXBOARD)// Tot DAQ data size (1 ev)

#define NPLANES (NBOARDS)                   // Number of silicon modules (each module has x and y sensors)
#define NVIEWXPLANE (NLAYXBOARD)            // Number of view per module (2 views: x and y)
#define NSTRIPXVIEW (NCHIPXLAY*NCHXCHIP)    // Number of readout strips (sensor has 768 implantations, but
                                            // we readout 1 out of 2 --> 384) (NOT REALLY: first 4 and last
                                            // 4 implanted are not readout, that means 380 readout strips;
                                            // good readout channels are from 3 to 382 included)

// +++++++ Definition from DataAnalysis.h ++++++++

#define NBOARDSMAX 4
#define NBOARDSINFILE 4   // # of readout boards stored in datafile
#define NPLANESMAX (NBOARDSMAX)
#define NSEC 4            // Number of sections on each MDAQ board (num of readout half-hybrids)

#define NEVMINPED 10      // Min num of evts for ped calculation
#define NEVMAXPED 100000   // Max num of evts for ped calculation
#define NDATARAW  100
#define SHOWFREQ  50      // Frequency for output on screen

#define NRAWEVTS  100     // Number of raw events to print on output file

#define NBIGEVENT  100



#define HEAD_ID   (0xF1C0F1C0)
#define TRAIL_ID  (0xC1A0C1A0)
#define DAQMAGIC1 (0x73)                   /* 1st magic word at start of readout board trasm */
#define DAQMAGIC2 (0x21)                   /* 2nd magic word at start of readout board trasm */

#define VME_ADDRESS        0xCAF00000      /* BASE VME ADDRESS */
#define VME_OFFSET_SRESET  0x00000000      /* soft reset */
#define VME_OFFSET_READF   0x00010000      /* read FIFO */
#define VME_OFFSET_STATUS0 0x00020000      /* read SR */
#define VME_OFFSET_STATUS1 0x00021000      /* read SR and reset */
#define VME_OFFSET_STATUS2 0x00022000      /* read SR and reset TWA only */
#define VME_OFFSET_IFIFO   0x00030000      /* init FOXI */
#define VME_OFFSET_RFOXI   0x00040000      /* reset FOXI */
#define VME_OFFSET_MASKF   0x00050000      /* set FOXI mask */
#define VME_OFFSET_RTN     0x00060000      /* reset TN counter */
#define VME_OFFSET_RVER    0x00070000      /* read version */

struct DATA_Header {
    char Magics[2];                    /* 2 magic numbers for the event, 1byte+1byte */
    char ColAdd[NSAMPL][NCHIPXBOARD];  /* Column address for 3 samplings of 24 PACE */
    char JUMP_FF;                      /* 4 bits to check jumper ID of board   
					  4 bits to check FULL FIFO flag in fifos of 4 half-hybrids */
    char ColAddChk;                    /* 8bit variable for checking of column address:
					  (MSB) C12 - C23 - 3x - C1 -C2 - C3 (LSB)   (x=bit not used) */
    char DV_Al[NSAMPL][3];             /* Data valid alarm for 3 columns, 24 PACE (3x3 bits).
				       // For each col 3 bytes contains info for PACEs: (MSB) 1,...,24 (LSB) */
    char Alarms;                       /* (MSB) Master(2bit) - PLL - AE - FNE(4bits -> 4 half-hybrids) (LSB) */
    char Counters[4];                  /* ((Counters >> 28) & 0xF)  ->  rejected LV1 events
					  (Counters & 0xFFFFFFF)    ->  read event counter */
    char End[6];                       /* 6 magic numbers (bytes) for the event */
};

struct DATA_Trailer {
    char CRC;                      /* Check for consistency of data trasmission */
    char End[7];                   /* 7 fixed words (bytes) to end data trasmission */
};


struct DAQ_Board_Out {
    struct DATA_Header head;
    char  data[NBYTESXBOARD];
    struct DATA_Trailer trail;
};

struct VME_Header {
    //long int dummy;             /* magic number for the VME header */
    int dummy;                  /* magic number for the VME header */
    // time_t time_sec;         /* seconds since 01/01/1970 from gettimeofday */
    // time_t time_usec;        /* microseconds from gettimeofday() */
    //long int time_sec;
    //long int time_usec;
    int time_sec;
    int time_usec;
    int event_no;               /* event number from start */
    int acq_flag;               /* packet integrity flag */
    int acq_type;               /* acquisition type */
    int acq_nboards;            /* number of acquisition sets */
    int acq_size;               /* byte sizes of acquired sets */
};

struct VME_Trailer {
    int dummy[2];             /* magic number for the VME trailer  */
};

struct SILICON_RAW {
    struct VME_Header    acq_header;
    struct DAQ_Board_Out boardout[NBOARDS];
    struct VME_Trailer   acq_trailer;
};


#endif
