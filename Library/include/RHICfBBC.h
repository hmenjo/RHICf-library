#ifndef __RHICFBBC_H__
#define __RHICFBBC_H__

#include <TNamed.h>

class RHICfBBC : public TNamed {
 public:
  // Parameter
  static const Int_t N_CHANNEL = 36; 
  static const Int_t N_EASTWEST = 2; 

  // Header 
  Int_t            run;                // Run Number
  Int_t            number;             // Event Number

  // Data 
  Double_t         dE[N_EASTWEST][N_CHANNEL];
  Int_t         NOP[N_EASTWEST][N_CHANNEL];

 public:
  RHICfBBC();
  RHICfBBC(const char* name, const char *title);
  RHICfBBC(const RHICfBBC&);
  RHICfBBC& operator=(const RHICfBBC&);
  ~RHICfBBC();
  
  int       clear();
  int       copy(RHICfBBC* d);

  ClassDef(RHICfBBC,1);   // RHICf BBC data 
};

#endif
