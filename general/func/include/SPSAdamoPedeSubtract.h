#ifndef __SPSADAMOPEDESUBTRACT_H__
#define __SPSADAMOPEDESUBTRACT_H__

//-----------------------------------------------------------------
//                       SPSAdamoPedeSubtract
//-----------------------------------------------------------------

#include <TObject.h>
#include <TFile.h>
#include "globaldef.h"
#include "SPSAdamo.h"

class SPSAdamoPedeSubtract {
 private:
  int nevent;
  SPSAdamo pedeaccum;       // Buffer to calculate pedestal average
  SPSAdamo pedeaccum2;      // Buffer to calculate pedestal RMS (contain square)
  SPSAdamo pedeaccum_sub;   // Buffer to calculate pedestal average
  SPSAdamo pedeaccum_sub2;  // Buffer to calculate pedestal RMS (contain square)

  SPSAdamo pedestal;     // Average (before common noise subtraction) 
  SPSAdamo pedesigma;    // RMS     (before common noise subtraction) 
  SPSAdamo pedestal2;    // Average (after common noise subtraction) 
  SPSAdamo pedesigma2;   // RMS     (after common noise subtraction) 
 
 public:
  SPSAdamoPedeSubtract();
  virtual ~SPSAdamoPedeSubtract();
  
  int  Initialize();
  int  SubtractPedeAverage(SPSAdamo* data);
  int  SubtractCommonNoise(SPSAdamo* data);
  
  int  FillPedeEvent(SPSAdamo* data);
  int  AccumClear();                   // Clear the buffers 
  int  CalPedestal();                  // Calculate Average and RMS from the buffers

  int  WriteFile(char filename[]=""); 
  int  ReadFile(char filename[]="");
    
  SPSAdamo* GetPedestal(){ return &pedestal;}
  SPSAdamo* GetPedesigma(){return &pedesigma;}
  SPSAdamo* GetPedestal2(){ return &pedestal2;}
  SPSAdamo* GetPedesigma2(){return &pedesigma2;}  

 private:
  static const char* PEDESTAL_NAME;
  static const char* PEDESIGMA_NAME;
  static const char* PEDESTAL2_NAME;
  static const char* PEDESIGMA2_NAME; 
  static const char* DEFAULT_FILENAME;

  ClassDef(SPSAdamoPedeSubtract,1);   // Pedestal subtraction for Adamo
};

#endif
