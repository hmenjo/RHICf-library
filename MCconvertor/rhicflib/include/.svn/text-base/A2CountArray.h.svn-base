#ifndef __A2COUNTARRAY_H__
#define __A2COUNTARRAY_H__

// --------------------------------------------------------------------
//                            A2CountArray
//         For detail, see A2CountArray.cpp or Online Manual 
// --------------------------------------------------------------------

#include "globaldef.h"
#include "A2Scl.h"
#include "A2Scl_pp2015.h"
#include "A2Cal1.h"
#include <TNamed.h>
#include <TGraph.h>

class A2CountArray : public TNamed {
 public:
  static const int NCH   = 18;
  static const int NDATA = 720;
  
  int    nchannel;           // Number of channel
  int    ndata;              // Number of stored data
  int    idata;              // Newest data number
  double time[NDATA];        // Time [sec]
  float  count[NCH][NDATA];  // Array of Count
  float  rate[NCH][NDATA];   // Array of Rate [Hz]
  
  A2Scl_pp2015   a2scl;             //!
  A2Cal1  a2cal1;            //!
  
 public:
  A2CountArray();
  A2CountArray(char* name, char *title);
  ~A2CountArray();

  int     Initalize();
  int     Clear();
  int     GetNdata(){return ndata;}
  int     GetIdata(){return idata;}
  int     Next(int );
  int     Previous(int );
  //int     Fill(A2Scl* d);
  int     Fill(A2Cal1* d);
  int     Fill(A2Scl_pp2015* d);
  TGraph* MakeTGraph(int ch,int sel=0,int mode=-1); // sel 0:count 1:rate mode 0:Scl 1:Cal 
  TGraph* FillToTGraph(int ch,int sel,TGraph* g);   // sel 0:count 1:rate
  const char* GetCounterTitle(int sel, int ich);

  // ----- FOR ONLINE ANALYSIS ----
  int     Init(){return Initalize();}
  int     Bor(){return Clear();}
  int     Eor(){return OK;}
  //int     Loop(A2Scl* d){return Fill(d);}
  int     Loop(A2Scl_pp2015* d){return Fill(d);}
  int     Loop(A2Cal1* d){return Fill(d);}
  static const int NTIME_A2CAL1 = 10;      // interval of filling A2Cal1[sec]
  
  ClassDef(A2CountArray,2);   // Array of Counter Values for Arm2
};


#endif
