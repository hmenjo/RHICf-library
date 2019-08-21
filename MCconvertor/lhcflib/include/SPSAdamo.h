#ifndef __SPSADAMO_H__
#define __SPSADAMO_H__

// --------------------------------------------------------------------
//                              SPSAdamo
//             For detail, see SPSAdamo.cpp or Online Manual
// --------------------------------------------------------------------

#include <TNamed.h>
#include "globaldef.h"

class  SPSAdamo: public TNamed {
 public:
  static const int NSR    = 3;       // Number of status register words
  static const int NLAYER = 5;       // Number of silicon XY layer
  static const int NXY    = 2;       // Number of silicon in 1 layer (X and Y)
  static const int NSTRIP = 1024;    // Number of strip in one x or y layer.
  
  int    run;                        // Run Number
  int    number;                     // Event Number
  int    gnumber;                    // Event Number

  bool         valid;                       // Valid event or not 
  unsigned int SR[NSR];                     // Status Register (3 words)
                                            // See the hardware manual. 
  double       strip[NLAYER][NXY][NSTRIP];  // [layer][xy][channel]
  unsigned int eventcounter;                // Event Counter Value

 public:
  SPSAdamo(){clear();}
  SPSAdamo(char* name, char *title) : TNamed(name,title){clear();}
  ~SPSAdamo(){;}
  
  int clear();
  int copy(SPSAdamo* d);
  int copydata(SPSAdamo* d);  
  int add(SPSAdamo* d);
  int subtract(SPSAdamo* d);
  int multiply(double d);
  int divide(double d);

  bool IsValid(){return valid;}
  
  static bool IsValidStrip(int il,int ixy,int is); // Valid channel if valid, return true. 
  static bool IsDeadStrip(int il,int ixy,int is);  // Dead channel. if dead, return true. 
  static bool IsBadStrip(int il,int ixy,int is);   // Noisy channel if bad, return true. 
  static bool IsIwataStrip(int il,int ixy,int is);   // Noisy channel if bad, dead channel if dead, return true. 
  
  ClassDef(SPSAdamo,1); // Data structure for ADAMO at beam tests
};

#endif
