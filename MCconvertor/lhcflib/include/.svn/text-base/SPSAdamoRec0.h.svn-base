#ifndef __SPSADAMOREC0_H__
#define __SPSADAMOREC0_H__

//--------------------------------------------------------------------
//                          SPSAdamoRec0
//      This is data contaner for the ADAMO reconstructed result.
//           This is for old analysis result (SPS2007) 
//--------------------------------------------------------------------

#include <TNamed.h>
#include <SPSAdamo.h>

class SPSAdamoRec0 : public TNamed {
  // Definitions
 public:
  static const int NLAYER = SPSAdamo::NLAYER;
  static const int NXY    = SPSAdamo::NXY;
  
 public:
  int            run;                 // Run Number
  int            number;              // Event Number
  int            gnumber;             // Grobal Event Number
 
  // From the format of old library (CalFSIL2)
  Double_t       pos[NXY];             // incident position (x,y) unit mm;
  Double_t       direction[NXY];       // incidnet direction (dx,xy) unit mm/mm;
  Int_t          clevel[NXY];          // number of coinsidence layers (x,y) max:5
  Int_t          clevel1[NXY];         // anther type max : > 5
  Int_t          ndiscri[NXY][NLAYER]; // number of discriminate channels.
  Int_t          ndata[NXY];           //
  Double_t       data[NXY][NLAYER];    // ?
  Double_t       dataz[NXY][NLAYER];   // ?

  Double_t       chi2[NXY];            // chi2 of linear fit
  Int_t          pad;

 public:
  SPSAdamoRec0();
  ~SPSAdamoRec0();
  int clear();
  int copy(SPSAdamoRec0* d);
  int copydata(SPSAdamoRec0* d);
  
  double GetPosition(int ixy);
  double GetX(){return GetPosition(0);}
  double GetY(){return GetPosition(1);}
  double GetDirection(int ixy);
  double GetDX(){return GetDirection(0);}
  double GetDY(){return GetDirection(1);}
  
  ClassDef(SPSAdamoRec0,1); // Data structure for ADAMO at beam tests
};

#endif 
