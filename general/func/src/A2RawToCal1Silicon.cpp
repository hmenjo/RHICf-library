#ifndef __A2RAW2CAL1SILICON_CPP__
#define __A2RAW2CAL1SILICON_CPP__

#include "A2RawToCal1Silicon.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  27 Aug. 08: a skeleton make by H.MENJO
//  ?? ???. 09: Copy the functions in the extract codes for silicon  
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2RawToCal1Silicon);
#endif

#include "silicon_data.h" // = "acq_version_1.2.1/include/data.h" 
#include "feparam_arm2.h" // in this file, N_A2_ARM2(=14228) is defined
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
using namespace std;

const unsigned char A2RawToCal1Silicon::crctable[256] = {
  0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
  0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
  0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
  0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
  0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
  0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
  0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
  0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
  0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
  0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
  0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
  0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
  0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
  0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
  0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
  0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
  0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
  0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
  0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
  0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
  0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
  0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
  0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
  0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
  0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
  0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
  0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
  0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
  0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
  0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
  0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
  0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};


void A2RawToCal1Silicon::Initialize(){
  //define_hyb_seq();
  herror = new TH1F("herror_silicon","Error Flags of Silicon",80,0,80);
  nconv = 0;
}

int A2RawToCal1Silicon::Convert(TObject* raw_input, A2Cal1* cal1){
  if(strcmp(raw_input->ClassName(),"A2Raw")==0){
    if(nconv == 0) define_hyb_seq();
    Convert_pp2010((A2Raw*)raw_input,cal1);
  }
  // ==============================================================
  // For the format of p-Pb 2013 
  else if(strcmp(raw_input->ClassName(),"A2Raw_pPb2013")==0){
    if(nconv == 0) define_hyb_seq();	  
    return Convert_pPb2013((A2Raw_pPb2013*)raw_input,cal1);
  }
  // ==============================================================
  // For the format of p-p 2015
  else if(strcmp(raw_input->ClassName(),"A2Raw_pp2015")==0){
    if(nconv == 0) define_hyb_seq_pp2015();	  
    return Convert_pp2015((A2Raw_pp2015*)raw_input,cal1);
  }
  // ==============================================================
  // For the format of p-Pb 2016
  else if(strcmp(raw_input->ClassName(),"A2Raw_pPb2016")==0){
    if(nconv == 0) define_hyb_seq_pp2015();	  
    return Convert_pPb2016((A2Raw_pPb2016*)raw_input,cal1);
  } else {
    cerr << "[A2RawToCal1_Silicon::Convert] Error : Unknow Class "
	 << raw_input->ClassName() << endl; 
    return ERROR; 
  }
}

int A2RawToCal1Silicon::Convert_pp2010(A2Raw* raw, A2Cal1* cal1){
  int err;

  
  // A2Raw  has a array of char  arm2[14228].
  // A2Cal1 has a array of float silicon[4][2][384][3].

  a2cal1 = cal1;
 
  /*cout << endl << "Event Header " << endl;
  cout << showbase << internal << setfill('0');
  cout << hex << data.acq_header.dummy << endl;
  cout << hex << data.acq_header.time_sec << endl;
  cout << hex << data.acq_header.time_usec << endl;
  cout << hex << data.acq_header.event_no << endl;
  cout << hex << data.acq_header.acq_flag << endl;
  cout << hex << data.acq_header.acq_type << endl;
  cout << hex << data.acq_header.acq_nboards << endl;
  cout << hex << data.acq_header.acq_size << endl;
  cout << dec;*/ 
  int sizeof_header = sizeof(struct VME_Header);
  memcpy((char*)&(data.acq_header),raw->arm2,sizeof_header);

  
  int nbyte=0;
  int sizeof_boarddata = TRKBYTESXBOARD*NBOARDS;
  for(int i=0;i<TRKBYTESXBOARD;i++){
    for(int j=0;j<NBOARDS;j++){
      ((char*)&(data.boardout[j]))[i]=raw->arm2[nbyte+sizeof_header];
      nbyte++;
    }
  }
  

  int sizeof_trailer = sizeof(struct VME_Trailer);
  memcpy((char*)&(data.acq_trailer),&(raw->arm2[sizeof_header+sizeof_boarddata]),sizeof_trailer);
  
    // Check the parameter of id_board;
  Check_id_board();

 err = EventChk(); // CRS check 
 if(err!=0){
    cerr << "[A2RawToCal1Silicon::Convert] detect CRC error " << endl; 
    return ERROR;
  }

  // Convert SILICON_RAW to A2Cal1::silicon[4][2][384][3].
  ExtractData();
 
  ++nconv;

  return OK;
}

// ***********************************************************
// ***  A2RawToCal1Silicon::Convert_pPb2013      *************
// ***********************************************************
int A2RawToCal1Silicon::Convert_pPb2013(A2Raw_pPb2013* raw, A2Cal1* cal1){
  // Format conversion of silicon data from A2Raw_pPb2013 to A2Cal1.
  
  // Copy data to tmp with A2Raw format
  A2Raw tmp;
  for(int i=0;i<A2Raw_pPb2013::c_N_ARM2;i++){
    tmp.arm2[i] = raw->arm2[i];
  }
  
  return Convert_pp2010(&tmp, cal1);
}

// ***********************************************************
// ***  A2RawToCal1Silicon::Convert_pp2015      **************
// ***********************************************************
int A2RawToCal1Silicon::Convert_pp2015(A2Raw_pp2015* raw, A2Cal1* cal1){
  // Format conversion of silicon data from A2Raw_pp2015 to A2Cal1.
  
  // Copy data to tmp with A2Raw format
  A2Raw tmp;

  for(int i=0;i<A2Raw_pp2015::c_N_ARM2;i++){
    tmp.arm2[i] = raw->arm2[i];
  }
  
  return Convert_pp2010(&tmp, cal1);
}

// ***********************************************************
// ***  A2RawToCal1Silicon::Convert_pPb2016      **************
// ***********************************************************
int A2RawToCal1Silicon::Convert_pPb2016(A2Raw_pPb2016* raw, A2Cal1* cal1){
  // Format conversion of silicon data from A2Raw_pPb2016 to A2Cal1.
  
  // Copy data to tmp with A2Raw format
  A2Raw tmp;

  for(int i=0;i<A2Raw_pPb2016::c_N_ARM2;i++){
    tmp.arm2[i] = raw->arm2[i];
  }
  
  return Convert_pp2010(&tmp, cal1);
}

int  A2RawToCal1Silicon::Check_id_board(){
  // Check the board identification number;
  for(int i=0;i<NBOARDS;i++) {
    if ((data.boardout[i].head.Magics[0]==0x0)&&(data.boardout[i].head.Magics[1]==0x0)){
      id_board[i]=-1;
    }
    else{
      switch ((data.boardout[i].head.JUMP_FF>>4) & 0x3)
	{
	case 1:
	  id_board[i]=1;
	  break;
	case 2:
	  id_board[i]=2;
	  break;
	case 3:
	  id_board[i]=3;
	  break;
	case 0:
	  id_board[i]=4;
	  break;
	}
      //printf("Readout board %d: #%d (%d)\n",i,id_board[i],((data.boardout[i].head.JUMP_FF>>4) & 0x3));
    }
  }
  return OK;
}


void  A2RawToCal1Silicon::ExtractData(){
  int i,j,k;
  int ibo,ifi,iblk,ibyte;
  int ilay,ichip,iread;
  int iplane,iview,istrip,isampl,isec, ihyb;

  char FIFOTRASM[NBOARDS][NFIFOXBOARD][NBLOCKSXFIFO][NBYTESXBLOCK];     
  // Store a single event as transmitted
  int FIFO[NBOARDS][NFIFOXBOARD][NWORDSXFIFO];            
  // Store a single event in FIFO order
  int ADC[NBOARDS][NLAYXBOARD][NCHIPXLAY][NCHXCHIP*NREADXCH]; 
  // Store a single event in ADC order


//****************************************
// Take data buffer and fill FIFOTRASM
// with 8 bit data as they are transmitted
//****************************************
// FIFOTRASM[NBOARDS][NFIFOXBOARD][NBLOCKSXFIFO][NBYTESXBLOCK]

  for(ibo=0;ibo<NBOARDS;ibo++){
    for(ifi=0;ifi<NFIFOXBOARD;ifi++){
      for(iblk=0;iblk<NBLOCKSXFIFO;iblk++){
	for(ibyte=0;ibyte<NBYTESXBLOCK;ibyte++){
          // Define integer to select bytes of FIFO-data for board 'ibo'.
          // First line jump to FIFO data for correct board
	  // second line select single bytes.
	  i=ifi*NBYTESXFIFO+iblk*NBYTESXBLOCK+ibyte;
	  FIFOTRASM[ibo][ifi][iblk][ibyte]=data.boardout[ibo].data[i]&0xff;
	}
      }
    }
  }

//************************************************************************************
//************************************************************************************
//                    This part must be changed when data
//                    packing changes in trasmission from
//                    readout board to VME
//************************************************************************************
//************************************************************************************

//***************************************
// Now take FIFOTRASM, containing 8 bit 
// data and fill var FIFO with real
// 18 bit fifo words
//***************************************
// FIFO[NBOARDS][NFIFOXBOARD][NWORDSXFIFO]

  for(ibo=0;ibo<NBOARDS;ibo++){
    for(ifi=0;ifi<NFIFOXBOARD;ifi++){
      for(iblk=0;iblk<NBLOCKSXFIFO;iblk++){
	for(ibyte=0;ibyte<NBYTESXBLOCK-2;ibyte+=2){     
	  i=iblk*NWORDSXBLOCK+ibyte/2;                  // Index of fifo word
	  j=((ibyte/2)<4?16:17);                        // Index of word containing the 2 LSB
	  k=((ibyte/2)%4);                              // Position of the 2 LSB in packed word
	  FIFO[ibo][ifi][i]=((FIFOTRASM[ibo][ifi][iblk][ibyte]&0xFF)<<10);  
	  FIFO[ibo][ifi][i]|=((FIFOTRASM[ibo][ifi][iblk][ibyte+1]&0xFF)<<2);
	  FIFO[ibo][ifi][i]|=((FIFOTRASM[ibo][ifi][iblk][j]>>((3-k)*2))&0x3);
	}
      }
    }
  }

//**************************************************
// Take FIFO and extract data on adc basis, filling
// the new variable ADC
//**************************************************
// Three 12 bit chips are stored in two 18 bit fifos
// There is a repetitive structure for each 3 
// consecutive chips. Operations to do are similar
// depending from the position of considered chip in
// its triplet.
//************************************************** 
// ADC[NBOARDS][NLAYXBOARD][NCHIPXLAY][NCHXCHIP*NREADXCH]

  for(ibo=0;ibo<NBOARDS;ibo++){
    for(ilay=0;ilay<NLAYXBOARD;ilay++){
      for(ichip=0;ichip<NCHIPXLAY;ichip++){
	for(iread=0;iread<NCHXCHIP*NREADXCH;iread++){
	  if (ichip%3==0){
	    ifi=ilay*(NFIFOXBOARD/NLAYXBOARD)+(ichip/3)*2;
	    ADC[ibo][ilay][ichip][iread]=(FIFO[ibo][ifi][iread])&0xFFF;
	  }
	  else if (ichip%3==1){
	    i=ilay*(NFIFOXBOARD/NLAYXBOARD)+(2*ichip+1)/3-1;
	    j=ilay*(NFIFOXBOARD/NLAYXBOARD)+(2*ichip+1)/3;
	    ADC[ibo][ilay][ichip][iread]=((FIFO[ibo][i][iread]>>12)&0x3F)|((FIFO[ibo][j][iread]&0x3F)<<6);
	  }
	  else if (ichip%3==2){
	    ifi=ilay*(NFIFOXBOARD/NLAYXBOARD)+(2*ichip-1)/3;
	    ADC[ibo][ilay][ichip][iread]=(FIFO[ibo][ifi][iread]>>6)&0xFFF ;
	  }
	}
      }
    }
  }

//*******************************************************
// Now rearranging ADC values to obtain the correct
// sequence of strips. Note that it is not anymore
// true that board #i is used to store data for plane #i.
// In fact new connection of hybrid sections on the 4
// motherboards are given in the following table.
//********************************************************
// Considering that each MB read 2 hybrids and is therefore
// divided into two parts, 1 and 2, each divided in two
// sections, F and S (First and Second), due to difficulties
// in the cabling procedures, the choosen assignment of
// half-hybrids on the motherboard sections is as following:
//
// MDAQ-BOARD   sec-1F  sec-1S  sec-2F  sec-2S
//     1          3XL     3XR     1XR     1XL
//     2          1YR     1YL     3YL     3YR
//     3          4XL     4XR     2XR     2XL
//     4          2YR     2YL     4YL     4YR
//**************************************************
// Filling STRIP variable: remember that 
// STRIP[...][...][0,1,382,383][...] are not wire bonded!

  for(ibo=0;ibo<NBOARDS;ibo++){
    if (id_board[ibo]>=0) {
      for(ilay=0;ilay<NLAYXBOARD;ilay++){
	for(ichip=0;ichip<NCHIPXLAY;ichip++){
	  if (ichip<(int)NCHIPXLAY/2)
	    isec=2*ilay;
	  else 
	    isec=2*ilay+1;
	  hyb_seq_decode(id_board[ibo]-1,isec,&iplane,&iview,&ihyb);
	  //cout << "T:" << id_board[ibo] << "  " << isec << endl;
	  for(iread=0;iread<NCHXCHIP*NREADXCH;iread++){
	    if (ihyb==0){
	      istrip=ichip*NCHXCHIP+(NCHXCHIP-1-iread%NCHXCHIP);
	      if (isec==1||isec==3) istrip=istrip-(int)(NCHIPXLAY/2)*NCHXCHIP;
	    }
	    else{
	      istrip=((int)(3*NCHIPXLAY/2)-1-ichip)*NCHXCHIP+(NCHXCHIP-1-iread%NCHXCHIP);
	      if (isec==0||isec==2) istrip=istrip-(int)(NCHIPXLAY/2)*NCHXCHIP;
	    }
	    isampl=(int)(iread/NCHXCHIP);
	    a2cal1->silicon[iplane][iview][istrip][isampl]=(float)ADC[ibo][ilay][ichip][iread];
	    //cout << a2cal1->silicon[iplane][iview][istrip][isampl] << endl;
	    if(istrip==0){
// 	      cout << "VALUE: " << ADC[ibo][ilay][ichip][iread] << "    "  
// 		   << a2cal1->silicon[0][0][0][0] << endl;
//	      cout << iplane << "  " << iview << "  " << istrip << " " << isampl << endl;
	    }
	    
	  }
	}
      }
    }
  } 

}  //    End of ExtractData routine


void A2RawToCal1Silicon::read_hyb_seq(char file[256]){
  if(strcmp(file,"")==0){
    strcpy(file,"hybrids_sequence.txt");
  }
  FILE *hybridsord;
  //if(!(hybridsord=fopen("hybrids_sequence.txt","r"))){
  if(!(hybridsord=fopen(file,"r"))){
    printf("\nError opening file \"hybrids_sequence.txt\": check its existence and permissions.\nExiting...\n\n");
    exit(1);
  }
  for(int ibo=0; ibo<NBOARDS; ibo++){
    for(int ise=0; ise<NSEC; ise++){
      fscanf(hybridsord,"%s",HybSeqMDAQ[ibo][ise]);
    }
  }
  fclose(hybridsord);
}

void A2RawToCal1Silicon::define_hyb_seq(){
   char tmp[4][4][10] = {{"3XL","3XR", "1XR", "1XL"},
			{"1YR","1YL", "3YL", "3YR"},
			{"4XL","4XR", "2XR", "2XL"},
			{"2YR","2YL", "4YL", "4YR"}};

  for(int ibo=0; ibo<NBOARDS; ibo++){
    for(int ise=0; ise<NSEC; ise++){
      strcpy(HybSeqMDAQ[ibo][ise],tmp[ibo][ise]);
      //cout << ibo << " " << ise << "  " << HybSeqMDAQ[ibo][ise] << endl;
    }
  }
}

void A2RawToCal1Silicon::define_hyb_seq_pp2015(){
  char tmp[4][4][10] = {{"3XL", "3XR", "1XL", "1XR"},
                        {"1YL", "1YR", "3YL", "3YR"},
                        {"4XL", "4XR", "2XL", "2XR"},
                        {"2YL", "2YR", "4YL", "4YR"}};

  for(int ibo=0; ibo<NBOARDS; ibo++){
    for(int ise=0; ise<NSEC; ise++){
      strcpy(HybSeqMDAQ[ibo][ise],tmp[ibo][ise]);
      //cout << ibo << " " << ise << "  " << HybSeqMDAQ[ibo][ise] << endl;
    }
  }
}

void A2RawToCal1Silicon::hyb_seq_decode(int ibo,int isec,
					int *iplane,int *iview, int *ihyb){

  char temp[1];

  temp[0]=HybSeqMDAQ[ibo][isec][0];
  //printf("%c",temp[0]);
  *iplane=atoi(temp)-1;
  temp[0]=HybSeqMDAQ[ibo][isec][1];
  //printf("%c",temp[0]);
  if (*temp=='X' || *temp=='x')
    *iview=0;
  else
    *iview=1;
  temp[0]=HybSeqMDAQ[ibo][isec][2];
  //printf("%c\n",temp[0]);
  if (*temp=='L' || *temp=='l')
    *ihyb=0;
  else
    *ihyb=1;
  
  

}

int  A2RawToCal1Silicon::EventChk(){
  int err_CRC;                    // At least one board with CRC error
  // Keep in memory previous event errors
  int i;
  int ibo;
  short tmp;
  char Daqtrail_end[7];
  Daqtrail_end[0] = 0xC1;
  Daqtrail_end[1] = 0xCA;
  Daqtrail_end[2] = 0xC0;
  Daqtrail_end[3] = 0xBA;
  Daqtrail_end[4] = 0xDA;
  Daqtrail_end[5] = 0xBA;
  Daqtrail_end[6] = 0xDA;

  err_CRC=0;

  for(ibo=0;ibo<NBOARDS;ibo++){
    err[ibo]=0;

    if (id_board[ibo]>=0){

      //----------------------------------------------------------------------------------------
      // struct DATA_Header {
      //   char Magics[2];           // 2 magic numbers for the event, 1byte+1byte
      //   char ColAdd[NSAMPL][NCHIPXBOARD];// Column address for 3 samplings of 24 PACE
      //   char JUMP_FF;             // 4 bits to check jumper ID of board
      //                             // 4 bits to check FULL FIFO flag in fifos of 4 half-hybrids
      //   char ColAddChk;           // 8bit variable for checking of column address:
      //                             //(MSB) C12 - C23 - 3x - C1 -C2 - C3 (LSB)   (x=bit not used)
      //   char DV_Al[NSAMPL][3];    // Data valid alarm for 3 columns, 24 PACE (3x3 bits).
      //                             // For each col 3 bytes contains info for PACEs: (MSB) 1,...,24 (LSB)
      //   char Alarms;              // (MSB) Master(2bit) - PLL - AE - FNE(4bits -> 4 half-hybrids) (LSB)
      //   char Counters[4];         // ((Counters >> 28) & 0xF)  ->  rejected LV1 events
      //                             //(Counters & 0xFFFFFFF)    ->  read event counter 
      //   char End[6];              // 6 magic numbers (bytes) for the event
      // };
      //----------------------------------------------------------------------------------------
      //
      // Readout-board trailer.
      //----------------------------------------------------------------------------------------
      // struct DATA_Trailer {
      //   char CRC;                 // Check for consistency of data trasmission
      //   char End[7];              // 7 fixed words (bytes) to end data trasmission
      // };

      // Check of the dummy words at beginning of header
      if ((data.boardout[ibo].head.Magics[0]==DAQMAGIC1)&&(data.boardout[ibo].head.Magics[1]==DAQMAGIC2)) {
      }
      else{
      	//cout << "MAGIC WRONG on " << ibo << endl; 
	err[ibo]|=0x2;
      }

      // Chk col. addr.
      tmp=(int)data.boardout[ibo].head.ColAddChk;
      if (   ((tmp>>7)&0x1)||((tmp>>6)&0x1)||((tmp>>2)&0x1)||((tmp>>1)&0x1)||(tmp&0x1)){
	//cout << "Chk col WRONG on " << ibo << endl;
	err[ibo]|=0x4;
      }

      // Check FF status
      tmp=(int)data.boardout[ibo].head.JUMP_FF;
      if (tmp&0xF){
	//cout << "Chk FF on " << ibo << endl;
	err[ibo]|=0x8;
      }

      // Check data valid alarm
      tmp=0;
      for (i=0;i<NSAMPL;i++){
	if ((data.boardout[ibo].head.DV_Al[i][0]<<16)|(data.boardout[ibo].head.DV_Al[i][1]<<8)|data.boardout[ibo].head.DV_Al[i][2]) tmp=1;
      }
      if (tmp) {
	//cout << "Data alarm on " << ibo << endl; 
	err[ibo]|=0x10;
      }

      // Check general alarm variable
      tmp=data.boardout[ibo].head.Alarms;
      if (  (((tmp>>7)&0x1) & ((tmp>>6)&0x1))||((tmp>>5)&0x1)||((tmp>>4)&0x1)||(tmp&0xF)) {
	//cout << "General alarm on " << ibo << endl;  
	err[ibo]|=0x20;
      }

      //********************************************
      //******* Check event trailer ****************
      //********************************************


      // Perform check of dummy word in DAQ trailer
      for (i=0;i<(int)sizeof(data.boardout[ibo].trail.End);i++){
	if(data.boardout[ibo].trail.End[i]!=Daqtrail_end[i]){
   	  //cout << "DAQ trailer WRONG on " << ibo << endl;
	  err[ibo]|=0x40;
	}
      }

      // Perform CRC calculation and compare with transmitted value
      crceval[ibo]=0x0;
      crceval[ibo]=CRC8_BlockChecksum((const char *)&data.boardout[ibo],(sizeof(struct DAQ_Board_Out)-sizeof(struct DATA_Trailer)));
      if (crceval[ibo]!=data.boardout[ibo].trail.CRC){
	err[ibo]|=0x80;
	err_CRC=1;
     
	//cout << "CRC ERROR ON " << ibo << endl; 
      }


    } // End od if(id_board[ibo]>=0)  (active boards)

  } //End of loop over all boards


  for(ibo=0;ibo<NBOARDS;ibo++){
    for(int ibit=0;ibit<8;ibit++){
      if(err[ibo] | (0x01<<ibit) ) {herror->Fill(ibo*20+ibit+0.5);}
    }
  }

  return err_CRC;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  FOUNCTION FOR CRC  +++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define CRC8_INIT_VALUE		0x00
#define CRC8_XOR_VALUE		0x00

void A2RawToCal1Silicon::CRC8_InitChecksum( unsigned char *crcvalue ) {
    *crcvalue = CRC8_INIT_VALUE;
}

void A2RawToCal1Silicon::CRC8_Update( unsigned char *crcvalue, const unsigned char data ) {
  *crcvalue = crctable[*crcvalue ^ data];
}

void A2RawToCal1Silicon::CRC8_UpdateChecksum( unsigned char *crcvalue, const void *data, int length ) {
    unsigned char crc;
    const unsigned char *buf = (const unsigned char *) data;

    crc = *crcvalue;
    while( length-- ) {
	crc = crctable[crc ^ *buf++];
    }
    *crcvalue = crc;
}

void A2RawToCal1Silicon::CRC8_FinishChecksum( unsigned char *crcvalue ) {
    *crcvalue ^= CRC8_XOR_VALUE;
}

unsigned char A2RawToCal1Silicon::CRC8_BlockChecksum( const void *data, int length ) {
    unsigned char crc;

    CRC8_InitChecksum( &crc );
    CRC8_UpdateChecksum( &crc, data, length );
    CRC8_FinishChecksum( &crc );
    return crc;
}


string A2RawToCal1Silicon::ErrorDecode(){

  ostringstream sout; 

  //***********************************************************
  // In case of ny error, write some comments
  //***********************************************************
  
  int errflag=0;
  int domsg=0;
  int tmp;
  static int  same_err_count;
  int   ev_in_data[NBOARDS];
  unsigned int ibo; 

  for(ibo=0;ibo<NBOARDS;ibo++) {
    if (err[ibo]!=errold[ibo]) errflag=1;   // errflag=1 if error variables change with respect to previous event
    domsg|=err[ibo];                        // domsg<>0 if there is error
  }

  if ((domsg)&&(!errflag)) {
    if (same_err_count<9) {     
      if (same_err_count==0) sout << endl;
      sout << "Same error " << endl;

      if (same_err_count==8) {
	sout << "...\n...\n...\n" << endl;
      }
      same_err_count++;
    }
  }

  if ((domsg)&&(errflag)) {
  
    for(int ibo=0;ibo<NBOARDS;ibo++) {
      ev_in_data[ibo]=((int)(data.boardout[ibo].head.Counters[3]&0xff) | (int)((data.boardout[ibo].head.Counters[2]&0xff)<<8) |
		       (int)((data.boardout[ibo].head.Counters[1]&0xff)<<16)| (int)((data.boardout[ibo].head.Counters[0]&0xf)<<24));

    }
    
    sout << "****************************************************************************\n" 
	 << "   Error of Silicon " << endl;
    for(int ibo=0;ibo<NBOARDS;ibo++){ sout << setw(5) << ev_in_data[ibo] << " ";}
    sout << endl;
    sout << "****************************************************************************\n";

    for(int ibo=0;ibo<NBOARDS;ibo++){
      if (err[ibo]){
	tmp=(int)data.boardout[ibo].head.JUMP_FF;
	tmp=(tmp>>4)&0xF;
	sout << "---------- >>> Event " << setw(5) << data.acq_header.event_no << " - " 
	     <<  ibo+1 << "  (jumper = " << hex << ((tmp>>1)&0x1) << (tmp&0x1) << dec << ") <<< ----------"
	     << endl;
	sout << endl;

	if (err[ibo]&0x2){
	  sout << "     --> WRONG DUMMY WORDS IN DAQ HEADER: 0x" 
	       << hex << data.boardout[ibo].head.Magics[0] << " and 0x" 
	       << hex << data.boardout[ibo].head.Magics[1]
	       << dec << endl;
	}
	if (err[ibo]&0x4){
	  tmp=(int)data.boardout[ibo].head.ColAddChk;
	  sout << "     --> WRONG COL. ADDR. CHECK: "
	       << "C12=" << ((tmp>>7)&0x1) << " "
	       << "C23=" << ((tmp>>6)&0x1) << " "
	       << "C1=" << ((tmp>>2)&0x1) << " "
	       << "C2=" << ((tmp>>1)&0x1) << " "
	       << "C3=" << ((tmp>>0)&0x1) << " " << endl;
	}
	if (err[ibo]&0x8){
	  tmp=(int)data.boardout[ibo].head.JUMP_FF;
	  sout << "     --> WRONG FF flag:  FF="
	       << ((tmp>>3)&0x1) << ((tmp>>2)&0x1) << ((tmp>>1)&0x1) << ((tmp&0x1)) << endl;
	}
	
	if (err[ibo]&0x10){
	  sout << "     --> WRONG DATA VALID CHECK: " 
	       << "col1=" << hex 
	       <<  ((((data.boardout[ibo].head.DV_Al[0][0]&0xFF)<<16)|((data.boardout[ibo].head.DV_Al[0][1]&0xFF)<<8)|(data.boardout[ibo].head.DV_Al[0][2]&0xFF))&0xffffff)
	       << "  "
	       << "col2=" << hex 
	       <<  ((((data.boardout[ibo].head.DV_Al[1][0]&0xFF)<<16)|((data.boardout[ibo].head.DV_Al[1][1]&0xFF)<<8)|(data.boardout[ibo].head.DV_Al[1][2]&0xFF))&0xffffff)
	       << "  "
	       << "col3=" << hex    
	       << ((((data.boardout[ibo].head.DV_Al[2][0]&0xFF)<<16)|((data.boardout[ibo].head.DV_Al[2][1]&0xFF)<<8)|(data.boardout[ibo].head.DV_Al[2][2]&0xFF))&0xffffff)
	       << dec << endl;
	    }
	    if (err[ibo]&0x20){
	      tmp=data.boardout[ibo].head.Alarms;
	      sout << "     --> WRONG ALARM CHECK: "
		   << "master=" <<  (((tmp>>7)&0x1)&((tmp>>6)&0x1)) << "  "
		   << "IP=" << ((tmp>>5)&0x1) << "  "
		   << "AE=" << ((tmp>>4)&0x1) << "  "
		   << "FNE=" << ((tmp>>3)&0x1) << ((tmp>>2)&0x1) << ((tmp>>1)&0x1) << (tmp&0x1) 
		   << endl; 
	    }
	    if (err[ibo]&0x40){
	      sout << "   --> WRONG DAQ TRAILER DUMMY WORDS" << endl;
	    }
	    if (err[ibo]&0x80){
	      sout << "   --> WRONG CRC VALUE: "
		   << "calculated=0x" << hex << (crceval[ibo]&0xff) << " / "
		   << "transmitted=0x" << hex << (data.boardout[ibo].trail.CRC&0xff) 
		   << dec << endl;
	    }
	  }
      }
      
    sout << endl;
  }
  
  for (ibo=0;ibo<NBOARDS;ibo++) errold[ibo]=err[ibo];
  
  return sout.str();
}

int A2RawToCal1Silicon::checkSR(){

  char byte_flag;
  int j;
  
  int nerr=0;

  unsigned long word_status[2];

  word_status[0]=data.acq_header.acq_flag;
  word_status[1]=data.acq_header.acq_type;

  // decode status register                                                                                                                                                                                     
  //sprintf(status_line,"event %5d ",k+1);
  for(j=0;j<4;j++){
    byte_flag = (word_status[0]>>(j*8)) & 0xFF;

    if( byte_flag & 0x40 ){
      //strcat(status_line," LFE");
      nerr++;
      //flag_lfe[j]++;
    }

    if( byte_flag & 0x20 ){
      //strcat(status_line," MM ");
      nerr++;
      //flag_mm[j]++;
    }

    if( byte_flag & 0x10 ){
      //strcat(status_line," CE ");
      nerr++;
      //flag_ce[j]++;
    }

    if( byte_flag & 0x08 ){
      //strcat(status_line, " IFE");
      nerr++;
      //flag_ife[j]++;
    }

    if( byte_flag & 0x04 ){
      //strcat(status_line, " FDN");
      nerr++;
      //flag_fdn[j]++;
    }

    if( byte_flag & 0x02 ){
      //strcat(status_line, " FF ");
      nerr++;
      //flag_ff[j]++;
    }

    if( byte_flag & 0x01 ){
      //strcat(status_line," FV ");
      nerr++;
      //flag_fv[j]++;
    }

    for(int ibit=0;ibit<7;ibit++){
      if( byte_flag | (0x01<<ibit) ) {herror->Fill(j*20+ibit+8+0.5);}
    }
  }  
  
  return (-1)*nerr;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ FOR ONLINE ANALYSIS +++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++





#endif
