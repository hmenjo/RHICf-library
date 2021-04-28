#ifndef __RHICFRoman_H__
#define __RHICFRoman_H__

#include <TNamed.h>

class RHICfRoman : public TNamed {
 public:
  // Parameter
  static const Int_t N_CHANNEL = 36; 

  // Header 
  Int_t            run;                // Run Number
  Int_t            number;             // Event Number

  // Data 
  Double_t         dE[N_CHANNEL];

 public:
  RHICfRoman();
  RHICfRoman(const char* name, const char *title);
  ~RHICfRoman();
  
  int       clear();
  int       copy(RHICfRoman* d);

  ClassDef(RHICfRoman,1);   // RHICf Roman data 
};

#endif
