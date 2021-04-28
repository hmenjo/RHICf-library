#ifndef __RHICFZDC_H__
#define __RHICFZDC_H__

#include <TNamed.h>

class RHICfZDC : public TNamed {
 public:
  // Parameter
  static const Int_t N_ZDCCHANNEL = 3; 
  static const Int_t N_SMDHCHANNEL = 7; 
  static const Int_t N_SMDVCHANNEL = 8; 

  // Header 
  Int_t            run;                // Run Number
  Int_t            number;             // Event Number

  // Data 
  Int_t            ZDCNOP[N_ZDCCHANNEL];
  Int_t            SMDHNOP[N_SMDHCHANNEL];
  Int_t            SMDVNOP[N_SMDVCHANNEL];
  Double_t         ZDCdE[N_ZDCCHANNEL];
  Double_t         SMDHdE[N_SMDHCHANNEL];
  Double_t         SMDVdE[N_SMDVCHANNEL];

 public:
  RHICfZDC();
  RHICfZDC(const char* name, const char *title);
  RHICfZDC(const RHICfZDC&);
  RHICfZDC& operator=(const RHICfZDC&);
  
  ~RHICfZDC();
  
  int       clear();
  int       copy(RHICfZDC* d);
  void      Clear();

  ClassDef(RHICfZDC,1);   // RHICf ZDC data 
};

#endif
