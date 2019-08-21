#ifndef __RHICFFC_H__
#define __RHICFFC_H__

#include <TNamed.h>

class RHICfFC : public TNamed {
 public:
  // Parameter
  static const Int_t N_FCCHANNEL = 2; 

  // Header 
  Int_t            run;                // Run Number
  Int_t            number;             // Event Number

  // Data 
  Int_t            FCNOP[N_FCCHANNEL];
  Double_t         FCdE[N_FCCHANNEL];

 public:
  RHICfFC();
  RHICfFC(const char* name, const char *title);
  RHICfFC(const RHICfFC&);
  RHICfFC& operator=(const RHICfFC&);
  
  ~RHICfFC();
  
  int       clear();
  int       copy(RHICfFC* d);
  void      Clear();

  ClassDef(RHICfFC,1);   // RHICf FC data 
};

#endif
