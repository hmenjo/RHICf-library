#ifndef __A1COUNTARRAY_H__
#define __A1COUNTARRAY_H__

// --------------------------------------------------------------------
//                            A1CountArray
// --------------------------------------------------------------------


#include "globaldef.h"
#include "A1Scl.h"
#include "A1Scl_pp2015.h"
#include "A1Cal1.h"
#include <TNamed.h>
#include <TGraph.h>

class A1CountArray : public TNamed {
 public:
  static const int NCH   = 18;
  static const int NDATA = 720;
  
  int    nchannel;           // Number of channel
  int    ndata;              // Number of stored data
  int    idata;              // Newest data number
  double time[NDATA];        // Time [sec]
  float  count[NCH][NDATA];  // Array of Counts 
  float  rate[NCH][NDATA];   // Array of Rate [Hz]

  //  A1Scl   a1scl;             //!
  A1Scl_pp2015   a1scl;             //!
  A1Cal1  a1cal1;            //!
  
 public:
  A1CountArray();
  A1CountArray(char* name, char *title);
  ~A1CountArray();

  int     Initalize();
  int     Clear();
  int     GetNdata(){return ndata;}
  int     GetIdata(){return idata;}
  int     Next(int );
  int     Previous(int );
  //  int     Fill(A1Scl* d);
  int     Fill(A1Cal1* d);
  int     Fill(A1Scl_pp2015* d); // For 2015 Operation
  TGraph* MakeTGraph(int ch,int sel=0,int mode=-1); // sel 0:count 1:rate, mode 0:Scl 1:Cal 
  TGraph* FillToTGraph(int ch,int sel,TGraph* g);   // sel 0:count 1:rate
  const char* GetCounterTitle(int sel, int ich);
  
  // ----- FOR ONLINE ANALYSIS ----
  int     Init(){return OK;}
  int     Bor(){return Clear();}
  int     Eor(){return OK;}
  //  int     Loop(A1Scl* d){return Fill(d);}
  int     Loop(A1Scl_pp2015* d){return Fill(d);}
  int     Loop(A1Cal1* d){return Fill(d);}
  static const int NTIME_A1CAL1 = 10;         // interval of filling A1Cal1[sec]
  
  ClassDef(A1CountArray,2);       // Array of Counter Values for Arm1 
};


#endif
