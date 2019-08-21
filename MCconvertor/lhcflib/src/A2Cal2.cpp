#ifndef __A2CAL2_CPP__
#define __A2CAL2_CPP__

#include "A2Cal2.h"

//----------------------------------------------------------------------
// A2Cal2
//
// Data structure for Arm2.
// Only calibrated data or simulation results are filled.
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - int    run        (Run Number)
//  - int    number     (Arm#2 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//
//  - double cal[2][16]   [tower][layer]
//     Energy deposit in each scintillator layer.
//     [unit] Energy deposit by 150MeV Muon (0.453MeV)
//      tower: 0=25mm,1=32mm
//      layer: 0-15
//
//  - double fc[2][4]   [arm][channel]
//     Energy deposit in F.C.s
//     [unit] 0.453MeV for simulation result
//      arm: 0=Arm1,1=Arm2
//      channel: 0-3
//
//  - double silicon[4][2][384][3]; [layer][xy][strip][sample]
//     Energy deposit in each silicon strip
//     [unit] MeV for simulation result
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
// +++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  27 Aug. 08: Added silicon data [4][2][384][3]
//  10 Sep. 08: Change deta type: long -> int
//  26 Apr. 09: "enum bank" added by H.MENJO
//  05 Sep. 09: Added functions, calsum2 and siliconsum
//  23 Feb. 10: Added functions for flags by H.MENJO
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A2Cal2);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#include <globaldef.h>
#include <A2Cal1.h>

// ***********************************************************
// ***  A2Cal2::clear()  *************************************
// ***********************************************************
int A2Cal2::clear(bankio option){
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  CAL,FC,SILICON,FLAG
  // exp.  clear(A2Cal2::CAL & A2Cal2::SILICON);

  run     = 0;
  number  = 0;
  gnumber = 0;
  time[0] = 0;
  time[1] = 0;
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	cal[it][il] = 0.0;
      }
    }
  }
  
  if(option & FC){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	fc[it][il] = 0.;
      }
    }
  }
  
  if(option & SILICON){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    silicon[il][ixy][istrip][isample] = 0.;
	  }
	}
      }
    }
  }

 
  if(option & FLAG)  for(int i=0;i<3 ;i++) {flag[i]=0;}
  
  return OK;
}

// ***********************************************************
// ***  A2Cal2::copy     *************************************
// ***********************************************************
int A2Cal2::copy(A2Cal2* d, bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A2Cal2::copydata     *********************************
// ***********************************************************
int A2Cal2::copydata(A2Cal2* d, bankio option){
  // Copy only data of "d" to "this"
  // (default option:ALL)
  
  this->run     = d->run;
  this->number  = d->number;
  this->gnumber  = d->gnumber; 
  this->time[0] = d->time[0];
  this->time[1] = d->time[1];
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	this->cal[it][il]  = d->cal[it][il];
      }
    }
  }
  
  if(option & FC){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	this->fc[it][il] = d->fc[it][il];
      }
    }
  }

  if(option & SILICON){ 
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample]
	      = d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++) {this->flag[i]=d->flag[i];}

  return OK;
}

// ***********************************************************
// ***  A2Cal2::add      *************************************
// ***********************************************************
int A2Cal2::add(A2Cal2* d, bankio option){
  // Add data of "d" to "this"
  // (default option:ALL-FLAG)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	this->cal[it][il]  += d->cal[it][il];
      }
    }  
  }

  if(option & FC){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	this->fc[it][il] += d->fc[it][il];
      }
    }
  }

  if(option & SILICON){ 
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample]
	      += d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    }
  }
  
  if(option & FLAG) for(int i=0;i<3 ;i++){this->flag[i]+=d->flag[i];}

  return OK;
}

// ***********************************************************
// ***  A2Cal2::subtract   ***********************************
// ***********************************************************
int A2Cal2::subtract(A2Cal2* d, bankio option){
  // Subtract of "d" from "this"
  // (default option:ALL-FLAG)

  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	this->cal[it][il]  -= d->cal[it][il];
      }
    }  
  }

  if(option & FC){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	this->fc[it][il] -= d->fc[it][il];
      }
    }
  }
  
  if(option & SILICON){ 
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample]
	      -= d->silicon[il][ixy][istrip][isample];
	  }
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++){this->flag[i]-=d->flag[i];}

  return OK;
}

// ***********************************************************
// ***  A2Cal2::multiply   ***********************************
// ***********************************************************
int A2Cal2::multiply(double d, bankio option){
  // Multiply this by factor "d"
  // (default option:ALL-FLAG)
  
  if(option & CAL){
    for(int it=0;it<2;it++){
      for(int il=0;il<16;il++){
	this->cal[it][il] *= d;
      }
    }   
  }
  
  if(option & FC){
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	this->fc[it][il] *= d;
      }
    }
  }

  if(option & SILICON){ 
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int istrip=0;istrip<384;istrip++){
	  for(int isample=0;isample<3;isample++){
	    this->silicon[il][ixy][istrip][isample] *= d;
	  }
	}
      }
    }
  }
  
  return OK;
}

// ***********************************************************
// ***  A2Cal2::divide   *************************************
// ***********************************************************
int A2Cal2::divide(double d, bankio option){
  // multiply(1./d)
  // (default option:ALL-FLAG)

  return multiply(1./d);
}

// ***********************************************************
// ***  A2Cal2::calsum   *************************************
// ***********************************************************
double A2Cal2::calsum(int it,int sl,int ie){
  // Simple summation of cal[] from the layer #sl up to the layer #ie.
  //  it:  Tower. 0 or 20=20mm cal., 1 or 40=40mm cal.  
  //  sl:  First layer of the summation
  //  ie:  End layer of the summation
  // (default: sl=0,ie=15)

  double sum=0;
  for(int il=sl;il<=ie;il++){
    sum += cal[it][il]; 
  }
  return sum;
}

// ***********************************************************
// ***  A2Cal2::calsum2  *************************************
// ***********************************************************
double A2Cal2::calsum2(int it,int sl,int ie){
  // Modified summation of cal[] for energy estimation.
  // In layer>10, cal[layer] scaled up by the factor of 2. 
  //  it:  Tower. 0 or 20=20mm cal., 1 or 40=40mm cal.  
  //  sl:  First layer of the summation
  //  ie:  End layer of the summation
  // (default: sl=0,ie=15)

  double sum=0;
  for(int il=sl;il<=ie;il++){
    if(il<11){
      sum += cal[it][il];
    }
    else{
      sum += cal[it][il]*2.0;
    }
  }
  return sum;
}

// ***********************************************************
// ***  A2Cal2::siliconsum  **********************************
// ***********************************************************
double A2Cal2::siliconsum(int il,int ixy, int isample, 
			  int sstrip,int estrip){
  // Summation of silicon[il][ixy][isample][] 
  // from #strips "sstrip" up to "estrip"  
  //  il: Layer (0-3)
  //  ixy: X or Y. 0="X",1="Y"
  //  isample: #sample (0-2)
  //  sstrip: First strip of the summation
  //  estrip: End strip of the summation
  // (default: sstrip=0,estrip=383)
  
  double sum=0.;
  for(int is=sstrip;is<=estrip;is++){
    sum += silicon[il][ixy][is][isample];
  }
  return sum;
}

// ***********************************************************
// ***  A2Cal2::CopySilicon **********************************
// ***********************************************************
int A2Cal2::CopySilicon(A2Cal1* d){
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      for(int istrip=0;istrip<384;istrip++){
        for(int isample=0;isample<3;isample++){
          this->silicon[il][ixy][istrip][isample]
            = d->silicon[il][ixy][istrip][isample];
        } 
      }
    }
  }   
  return OK;
} 


// ***********************************************************
// ***  A2Cal2::Show        **********************************
// ***********************************************************
void A2Cal2::Show(){
  cout << " ===========      A2Cal2     ============" << endl;
  cout << " RUN: " << setw(6) << run << "    "
       << "GNUMBER: " << setw(7) << gnumber << "  "
       << "NUMBER: " << setw(7) << number << "   "
       << endl;
  // Sum dE's
  cout.setf(ios::fixed);
  cout << "                 "
       << setw(11) << "  --- 25mm ---"
       << setw(11) << "  --- 32mm ---" 
       << endl;
  cout << "  SumdE(0-15)  : "
       << setw(11) << setprecision(1) <<  this->calsum2(0)
       << setw(11) << setprecision(1) <<  this->calsum2(1)
       << endl;
  cout << "  SumdE(1-12)  : "
       << setw(11) << setprecision(1) <<  this->calsum2(0,1,12)
       << setw(11) << setprecision(1) <<  this->calsum2(1,1,12)
       <<endl;
  return ;
}

#endif
