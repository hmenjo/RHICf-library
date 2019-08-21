#ifndef __RAWL1TDRAW_H__
#define __RAWL1TDRAW_H__

#include <TNamed.h>
#include <TCanvas.h>
#include <TText.h>
#include "RawL1T.h"

class RawL1TDraw {
 public:
  static const int cNcounts = 14; 
  
  TCanvas   *canvas;    
 
  //TText     *l_header[4];    // label
  TText     *t_header[4];    // value
  TText     *l_counts[cNcounts];   //! label
  TText     *t_counts[cNcounts];   // value

  
  // For Scaler, TDC, 
  enum DISPLAY_VERSION {
    VERSION_PP2010     = 2010,
    VERSION_PPB2013    = 2013,
    VERSION_UNKNOW     = 0
  };

  DISPLAY_VERSION    f_DisplayVersion;   //!

 private:
  static int  icall;
  char cname[256];
  
 public:
  RawL1TDraw();
  ~RawL1TDraw();
  
  int  Initialize();
  int  Delete(Option_t* option = "");
  int  Fill(RawL1T *d);
  int  Reset();

  int  SetDisplayFormat(DISPLAY_VERSION version); // VERSION_PP2010 or VERSION_PPB2013
  void SetDisplayVersion_pp2010();                // Display format for 2010
  void SetDisplayVersion_pPb2013();               // Display format for 2013
  
  void SetCanvas(TCanvas* c);
  int  DrawCanvas();
  int  UpdateCanvas();
  int  ClearCanvas();
};


#endif
