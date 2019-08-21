#ifndef __SPSADAMOPEDESUBTRACT_CPP__
#define __SPSADAMOPEDESUBTRACT_CPP__

//----------------------------------------------------------------------
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  04 Oct. 10: First edited by H.MENJO
//----------------------------------------------------------------------
 
#include "SPSAdamoPedeSubtract.h"

#if !defined(__CINT__)
ClassImp(SPSAdamoPedeSubtract);
#endif

#include <iostream>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <cstdio>
using namespace std;


const char* SPSAdamoPedeSubtract::PEDESTAL_NAME    = "spsadamo_pedestal";
const char* SPSAdamoPedeSubtract::PEDESIGMA_NAME   = "spsadamo_pedesigma";
const char* SPSAdamoPedeSubtract::PEDESTAL2_NAME   = "spsadamo_pedestal2";
const char* SPSAdamoPedeSubtract::PEDESIGMA2_NAME = "spsadamo_pedesigma2";
const char* SPSAdamoPedeSubtract::DEFAULT_FILENAME = "spsadamo_pedestal.root";

// ++++++++++++++++ SPSAdamoPedeSubtract ++++++++++++++++++++
SPSAdamoPedeSubtract::SPSAdamoPedeSubtract(){
  Initialize();
}


// +++++++++++++++++ ~SPSAdamoPedeSubtract ++++++++++++++++++
SPSAdamoPedeSubtract::~SPSAdamoPedeSubtract(){;}

// +++++++++++++++++++++++ Initialize +++++++++++++++++++++++
int SPSAdamoPedeSubtract::Initialize(){
  // Initialization 
  pedestal.SetName(PEDESTAL_NAME);
  pedesigma.SetName(PEDESIGMA_NAME);  
  pedestal2.SetName(PEDESTAL2_NAME);
  pedesigma2.SetName(PEDESIGMA2_NAME);  
  pedestal.SetTitle("Pedestal Average (before common noize subtraction)");
  pedesigma.SetTitle("Pedestal RMS (before common noize subtraction)");
  pedestal2.SetTitle("Pedestal Average (after common noize subtraction)");
  pedesigma2.SetTitle("Pedestal RMS (after common noize subtraction)");
  
  AccumClear(); 
  return OK;
}

int SPSAdamoPedeSubtract::SubtractPedeAverage(SPSAdamo* data){
  data->subtract(&pedestal);
  return OK;
}

int SPSAdamoPedeSubtract::SubtractCommonNoise(SPSAdamo* data){
  // Subtraction of common noise
  
  static const int NCHIP = 8;
  static const int NSTRIP_CHIP = SPSAdamo::NSTRIP/NCHIP;

  // Calculate common noise 
  int    nstrip[SPSAdamo::NLAYER][SPSAdamo::NXY][NCHIP];
  double average[SPSAdamo::NLAYER][SPSAdamo::NXY][NCHIP];
  double average_all[SPSAdamo::NLAYER][SPSAdamo::NXY][NCHIP];
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){   
      for(int ic=0;ic<NCHIP;ic++){  
	nstrip[il][ixy][ic] = 0;
	average[il][ixy][ic] = 0.;
	for(int is=0;is<NSTRIP_CHIP;is++){
	  if(SPSAdamo::IsValidStrip(il,ixy,ic*NSTRIP_CHIP+is)){
	    average[il][ixy][ic] += data->strip[il][ixy][ic*NSTRIP_CHIP+is];
	    nstrip[il][ixy][ic] ++;
	  }
	  average_all[il][ixy][ic] += data->strip[il][ixy][ic*NSTRIP_CHIP+is];
	}  
	if(nstrip[il][ixy][ic]!=0){
	  average[il][ixy][ic] /= (double)nstrip[il][ixy][ic];
	}
	average_all[il][ixy][ic] /= NSTRIP_CHIP;
      }
    }
  }

  // Subtract common noise
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){  
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	if(nstrip[il][ixy][is/NSTRIP_CHIP]){
	  data->strip[il][ixy][is] -= average[il][ixy][is/NSTRIP_CHIP];
	}
	else{
	  data->strip[il][ixy][is] -= average_all[il][ixy][is/NSTRIP_CHIP];
	}
      }
    }
  }
  
  return OK;
}



// +++++++++++++++++++++++ AccumClear +++++++++++++++++++++++
int SPSAdamoPedeSubtract::AccumClear(){
  // Clear the buffers for accumlated values

  nevent = 0;
  pedeaccum.clear();
  pedeaccum2.clear();

  pedeaccum_sub.clear();
  pedeaccum_sub2.clear();
  
  return OK;
}

// +++++++++++++++++++++++ FillPedeEvent +++++++++++++++++++++++
int SPSAdamoPedeSubtract::FillPedeEvent(SPSAdamo* data){
  // Fill an pedestal event to the buffers. 
  
  SPSAdamo datatmp;
  datatmp.copydata(data);

  // Simple summation   
  pedeaccum.add(&datatmp); 
  
  // summation of data**2
  double dtmp;
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	dtmp = datatmp.strip[il][ixy][is];
	pedeaccum2.strip[il][ixy][is] += dtmp*dtmp;
      }
    }
  }
  
  
  // Subtract simple average
  SubtractPedeAverage(&datatmp);
  // Subtract common noise
  SubtractCommonNoise(&datatmp);
 
  pedeaccum_sub.add(&datatmp);
  
  // summation of data**2 
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	dtmp = datatmp.strip[il][ixy][is];
	pedeaccum_sub2.strip[il][ixy][is] += dtmp*dtmp;
      }
    }
  } 

  nevent++;
  return OK;
}

// +++++++++++++++++++++++ CalPedestal +++++++++++++++++++++++
int SPSAdamoPedeSubtract::CalPedestal(){
  // Calculate the average and RMS of the filled pedestal events.

  double av,avs,tmp;
  
  // Calculate Average 
  pedeaccum.divide((double)nevent);
  pedestal.copydata(&pedeaccum);

  // Calculate RMS
  pedeaccum2.divide((double)nevent);
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	av  = pedeaccum.strip[il][ixy][is];
	avs = pedeaccum2.strip[il][ixy][is];
	tmp = sqrt(avs - av*av);
	pedeaccum2.strip[il][ixy][is] = tmp;
      }
    }
  }
  pedesigma.copydata(&pedeaccum2);
  
  // Calculate Average 
  pedeaccum_sub.divide((double)nevent);
  pedestal2.copydata(&pedeaccum_sub);
  
  // Calculate RMS
  pedeaccum_sub2.divide((double)nevent);
  for(int il=0;il<SPSAdamo::NLAYER;il++){
    for(int ixy=0;ixy<SPSAdamo::NXY;ixy++){
      for(int is=0;is<SPSAdamo::NSTRIP;is++){
	av  = pedeaccum_sub.strip[il][ixy][is];
	avs = pedeaccum_sub2.strip[il][ixy][is];
	tmp = sqrt(avs - av*av);
	pedeaccum_sub2.strip[il][ixy][is] = tmp;
      }
    }
  }
  pedesigma2.copydata(&pedeaccum_sub2);
  
  
  return OK;
}


// +++++++++++++++++++++++ WriteFile +++++++++++++++++++++++
int SPSAdamoPedeSubtract::WriteFile(char filename[]){
  if(strcmp(filename,"")==0){
    strcpy(filename,DEFAULT_FILENAME);
  }
  
  TFile* file = new TFile(filename,"UPDATE");
  pedestal.Write(PEDESTAL_NAME,TObject::kOverwrite);
  pedesigma.Write(PEDESIGMA_NAME,TObject::kOverwrite); 
  pedestal2.Write(PEDESTAL2_NAME,TObject::kOverwrite);
  pedesigma2.Write(PEDESIGMA2_NAME,TObject::kOverwrite);
  file->Close();
  
  return OK;
}

// +++++++++++++++++++++++ ReadFile +++++++++++++++++++++++
int SPSAdamoPedeSubtract::ReadFile(char filename[]){
  SPSAdamo *tmp;
  bool err_check = false;

  if(strcmp(filename,"")==0){
    strcpy(filename,DEFAULT_FILENAME);
  }
  
  TFile* file = new TFile(filename);
  if(file->IsZombie()){
    cerr << "[SPSAdamoPedeSubtract::ReadFile] "
	 << "Cannot Open " << filename << endl;
    return ERROR;
  }
  
  if(!file->Get(PEDESTAL_NAME)){
    cerr << "[SPSAdamoPedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESTAL_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (SPSAdamo*) file->Get(PEDESTAL_NAME) ;  
    pedestal.copydata(tmp);
  }
  
  if(!file->Get(PEDESIGMA_NAME)){
    cerr << "[SPSAdamoPedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESIGMA_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (SPSAdamo*) file->Get(PEDESIGMA_NAME) ;  
    pedesigma.copydata(tmp);
  } 

  if(!file->Get(PEDESTAL2_NAME)){
    cerr << "[SPSAdamoPedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESTAL2_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (SPSAdamo*) file->Get(PEDESTAL2_NAME) ;  
    pedestal2.copydata(tmp);
  }
  
  if(!file->Get(PEDESIGMA2_NAME)){
    cerr << "[SPSAdamoPedeSubtract::ReadFile] "
	 << "Cannot Find " << PEDESIGMA2_NAME << " in " << filename 
	 << endl;
    err_check = true;
  }
  else{
    tmp = (SPSAdamo*) file->Get(PEDESIGMA2_NAME) ;  
    pedesigma2.copydata(tmp);
  } 
  
  file->Close();

  return OK;
}

#endif
