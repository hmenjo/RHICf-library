#ifndef __A1CAL2_CPP__
#define __A1CAL2_CPP__

#include "A1Cal2.h"


//----------------------------------------------------------------------
// A1Cal2
//
// Data structure for Arm1.
// Only calibrated data or simulation results are filled.
//
// DATA FORMAT:  (Updated 07 Oct. 2009 by H.MENJO)
//  - int    run        (Run Number)
//  - int    number     (Arm#1 Event Number)
//  - int    gnumber    (Global Event Number)
//  - double time[2]    (CPU time [0]:sec,[1]:usec)
//
//  - double cal[2][16]   [tower][layer]
//     Energy deposit in each scintillator layer.
//     [unit] Energy deposit by 150MeV Muon (0.453MeV)
//      tower: 0=20mm,1=40mm
//      layer: 0-15
//
//  - double fc[2][4]   [arm][channel]
//     Energy deposit in F.C.s
//     [unit] 0.453MeV for simulation result
//      arm: 0=Arm1,1=Arm2
//      channel: 0-3
//
//  - double scifi0[4][2][20]  [layer][xy][fiber]
//     Energy deposit in each SciFi of the 20mm cal.
//     [unit] 0.151MeV for simulation result
//      layer: 0-3
//      xy:    0="X",1="Y"
//      fiber: 0-19
//
//  - double scifi1[4][2][40]  [layer][xy][fiber]
//     Energy deposit in each SciFi of the 40mm cal.
//     [unit] 0.151MeV for simulation result
//
//  - unsigned int flag[3]
//     Flags of GPIOs
//      [0]:  Event flag of LHCFLOGIC
//      [1]:  Discriminator flag of LHCFLOGIC
//      [2]:  Event flag of LHCFCOUNTER
//     For detail, please refer the manual of LHCFLIGIC and LHCFCOUNTER
//
// +++ Logs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO 
//  26 Apr. 09: "enum bank" added
//  23 Feb. 10: Added functions for flags by H.MENJO
//------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1Cal2);
#endif

// ***********************************************************
// ***  A1Cal2::clear()  *************************************
// ***********************************************************
int A1Cal2::clear(bankio option){  
  // Clear data selectied. (default:ALL)
  // List of option
  //  ALL,
  //  CAL,FC,SCIFI0,SCIFI1,FLAG,
  // exp.  clear(A2Cal2::CAL & A1Cal2::SCIFI0);
  
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
 
  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){ 
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  scifi0[il][ixy][ich] = 0.;
	}
      }  
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  scifi1[il][ixy][ich] = 0.;
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++) {flag[i]=0;}
  
  return OK;
}

// ***********************************************************
// ***  A1Cal2::copy     *************************************
// ***********************************************************
int A1Cal2::copy(A1Cal2* d,bankio option){
  // Copy data, name and title of "d" to "this"
  // (default option:ALL)
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d,option);
}

// ***********************************************************
// ***  A1Cal2::copydata     *********************************
// ***********************************************************
int A1Cal2::copydata(A1Cal2* d,bankio option){
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

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  this->scifi0[il][ixy][ich] = d->scifi0[il][ixy][ich];
	}
      } 
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] = d->scifi1[il][ixy][ich];
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++) {this->flag[i]=d->flag[i];}

  return OK;
}

// ***********************************************************
// ***  A1Cal2::add      *************************************
// ***********************************************************
int A1Cal2::add(A1Cal2* d,bankio option){
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

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  this->scifi0[il][ixy][ich] += d->scifi0[il][ixy][ich];
	}
      } 
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] += d->scifi1[il][ixy][ich];
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++) {this->flag[i] += d->flag[i];}
  
  return OK;
}

// ***********************************************************
// ***  A1Cal2::subtract   ***********************************
// ***********************************************************
int A1Cal2::subtract(A1Cal2* d,bankio option){
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

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){  
	  this->scifi0[il][ixy][ich] -= d->scifi0[il][ixy][ich];
	}
      }
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] -= d->scifi1[il][ixy][ich];
	}
      }
    }
  }

  if(option & FLAG) for(int i=0;i<3 ;i++) {this->flag[i] -= d->flag[i];}

  return OK;
}

// ***********************************************************
// ***  A1Cal2::multiply   ***********************************
// ***********************************************************
int A1Cal2::multiply(double d,bankio option){
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

  for(int il=0;il<4;il++){
    for(int ixy=0;ixy<2;ixy++){
      if(option & SCIFI0){
	for(int ich=0;ich<20;ich++){
	  this->scifi0[il][ixy][ich] *= d;
	}
      }  
      if(option & SCIFI1){
	for(int ich=0;ich<40;ich++){
	  this->scifi1[il][ixy][ich] *= d;
	}
      }
    }
  }

  //if(option & FLAG) for(int i=0;i<3 ;i++) {this->flag[i] ;}

  return OK;
}

// ***********************************************************
// ***  A1Cal2::divide   *************************************
// ***********************************************************
int A1Cal2::divide(double d,bankio option){
  // multiply(1./d)
  // (default option:ALL-FLAG)
  
  return multiply(1./d);
}

// ***********************************************************
// ***  A1Cal2::calsum   *************************************
// ***********************************************************
double A1Cal2::calsum(int it,int sl,int ie){
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
// ***  A1Cal2::calsum2  *************************************
// ***********************************************************
double A1Cal2::calsum2(int it,int sl,int ie){
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
// ***  A1Cal2::scifisum  ************************************
// ***********************************************************
double A1Cal2::scifisum(int it,int il,int ixy){
  // Summation of scifi[il][ixy][] 
  // Fibers with <-9000(dead channels) are skipped in the summation.
  //  it: Tower.  0 or 20:20mm cal., 1 or 40 : 40mm cal.  
  //  il: Layer
  //  ixy: X or Y. 0="X",1="Y"

  double sum=0;
  if(it==0 || it==20){
    for(int ich=0;ich<20;ich++){
      if(scifi0[il][ixy][ich]>-9000.){
	sum += scifi0[il][ixy][ich];
      }
    }
  }
  else if(it==1 || it==40){
    for(int ich=0;ich<40;ich++){
      if(scifi1[il][ixy][ich]>-9000.){
	sum += scifi1[il][ixy][ich];
      }
    }
  }
  return sum;
}


#endif
