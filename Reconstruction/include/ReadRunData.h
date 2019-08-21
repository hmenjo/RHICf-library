#ifndef __READRUNDATA_H__

#include <iostream>
#include <iomanip>
#include <cmath>
#include <TFile.h>
#include "TLHCFSDATA.h"
#include "TLHCFDIPDATAH.h"
using namespace std;

class ReadRunData{
 public:
  char  a1_PMTgain[32];
  char  a2_PMTgain[32];
  char  a1_scifigain[32];
  char  a1_position[32]; 
  char  a2_position[32];   
  int   stable_beam;

  TLHCFSDATA     *sc;
  TLHCFDIPDATAH  *diph; 

 public:
  ReadRunData();

  int    Read(char *filename);
  int    CheckArm1PMT();
  int    CheckArm2PMT();
  int    CheckArm1SciFi();
  int    CheckArm1Position();  
  int    CheckArm2Position();
  int    CheckV(double V0,double V1);
  double GetVmonArm1(int it, int ich);
  double GetVmonArm2(int it, int ich);
  
};

ReadRunData::ReadRunData(){
  strcpy(a1_PMTgain,"");
  strcpy(a2_PMTgain,""); 
  strcpy(a1_scifigain,""); 
  strcpy(a1_position,"");
  strcpy(a2_position,""); 
  stable_beam = -1;

  sc   = NULL;
  diph = NULL;
}

int ReadRunData::Read(char *filename){

  TFile *file = new TFile(filename);
  if(file->IsZombie()){
    cerr << "[ReadRunData::Read] "
	 << "Cannot open " <<  filename << endl;
    return -1;
  }
  
  sc   = (TLHCFSDATA*)    file->Get("sc_first");
  diph = (TLHCFDIPDATAH*) file->Get("diph_first");
  if(sc==NULL || diph==NULL){
    cerr << "NO SLOWCONTROL INFORMATION IN " <<  filename << endl;
    return -2;
  }
  else{
    // HV for Arm1
    CheckArm1PMT();
    // HV for Arm2
    CheckArm2PMT();
    // HV for SciFi
    CheckArm1SciFi();
    // Arm1 Detector Position
    CheckArm1Position();
    // Arm2 Detector Position
    CheckArm2Position();  
    
    if(diph->GetData()->Safebeam1.payload ==15 && 
       diph->GetData()->Safebeam2.payload ==15){
      stable_beam = 1;  
    }
    else{
      stable_beam = 0;  
    }
    

    return 0;
  }
}

int ReadRunData::CheckArm1PMT(){

  int check = 0;
  
  // Check Off -------------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm1(it,ich),0.);    
    }
  }  
  if(check==0){
    strcpy(a1_PMTgain,"off");
    return 0;
  }
  
  // Check All600V ----------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm1(it,ich),600.);
      cout << it << "   " << ich << "   " <<GetVmonArm1(it,ich) << endl;
    }
  }
  if(check==0){
    strcpy(a1_PMTgain,"All600V"); 
    return 0;
  }

  // Check All450V ----------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm1(it,ich),450.);
    }
  }
  if(check==0){
    strcpy(a1_PMTgain,"All450V"); 
    return 0;
  }
  
  // Check Normal at 7TeV cms -----------------
  check = 0;
  check += CheckV(GetVmonArm1(0, 0),500.0); // 20mm-00
  check += CheckV(GetVmonArm1(0, 1),475.0); // 20mm-01
  check += CheckV(GetVmonArm1(0, 2),500.0); // 20mm-02
  check += CheckV(GetVmonArm1(0, 3),500.0); // 20mm-03
  check += CheckV(GetVmonArm1(0, 4),500.0); // 20mm-04
  check += CheckV(GetVmonArm1(0, 5),550.0); // 20mm-05 
  check += CheckV(GetVmonArm1(0, 6),500.0); // 20mm-06
  check += CheckV(GetVmonArm1(0, 7),500.0); // 20mm-07
  check += CheckV(GetVmonArm1(0, 8),500.0); // 20mm-08
  check += CheckV(GetVmonArm1(0, 9),475.0); // 20mm-09
  check += CheckV(GetVmonArm1(0,10),500.0); // 20mm-10
  check += CheckV(GetVmonArm1(0,11),500.0); // 20mm-11
  check += CheckV(GetVmonArm1(0,12),500.0); // 20mm-12
  check += CheckV(GetVmonArm1(0,13),500.0); // 20mm-13
  check += CheckV(GetVmonArm1(0,14),500.0); // 20mm-14
  check += CheckV(GetVmonArm1(0,15),500.0); // 20mm-15
  
  check += CheckV(GetVmonArm1(1, 0),475.0); // 40mm-00
  check += CheckV(GetVmonArm1(1, 1),475.0); // 40mm-01
  check += CheckV(GetVmonArm1(1, 2),475.0); // 40mm-02
  check += CheckV(GetVmonArm1(1, 3),500.0); // 40mm-03
  check += CheckV(GetVmonArm1(1, 4),500.0); // 40mm-04
  check += CheckV(GetVmonArm1(1, 5),500.0); // 40mm-05 
  check += CheckV(GetVmonArm1(1, 6),500.0); // 40mm-06
  check += CheckV(GetVmonArm1(1, 7),500.0); // 40mm-07
  check += CheckV(GetVmonArm1(1, 8),475.0); // 40mm-08
  check += CheckV(GetVmonArm1(1, 9),475.0); // 40mm-09
  check += CheckV(GetVmonArm1(1,10),475.0); // 40mm-10
  check += CheckV(GetVmonArm1(1,11),500.0); // 40mm-11
  check += CheckV(GetVmonArm1(1,12),475.0); // 40mm-12
  check += CheckV(GetVmonArm1(1,13),475.0); // 40mm-13
  check += CheckV(GetVmonArm1(1,14),475.0); // 40mm-14
  check += CheckV(GetVmonArm1(1,15),475.0); // 40mm-15  
  if(check==0){
    strcpy(a1_PMTgain,"Normal"); 
    return 0;
  }  
  
  // Check Normal-High -----------------
  check = 0;
  check += CheckV(GetVmonArm1(0, 0),500.0); // 20mm-00
  check += CheckV(GetVmonArm1(0, 1),475.0); // 20mm-01
  check += CheckV(GetVmonArm1(0, 2),500.0); // 20mm-02
  check += CheckV(GetVmonArm1(0, 3),500.0); // 20mm-03
  check += CheckV(GetVmonArm1(0, 4),500.0); // 20mm-04
  check += CheckV(GetVmonArm1(0, 5),550.0); // 20mm-05 
  check += CheckV(GetVmonArm1(0, 6),500.0); // 20mm-06
  check += CheckV(GetVmonArm1(0, 7),500.0); // 20mm-07
  check += CheckV(GetVmonArm1(0, 8),500.0); // 20mm-08
  check += CheckV(GetVmonArm1(0, 9),475.0); // 20mm-09
  check += CheckV(GetVmonArm1(0,10),500.0); // 20mm-10
  check += CheckV(GetVmonArm1(0,11),500.0); // 20mm-11
  check += CheckV(GetVmonArm1(0,12),500.0); // 20mm-12
  check += CheckV(GetVmonArm1(0,13),500.0); // 20mm-13
  check += CheckV(GetVmonArm1(0,14),500.0); // 20mm-14
  check += CheckV(GetVmonArm1(0,15),500.0); // 20mm-15
  
  check += CheckV(GetVmonArm1(1, 0),600.0); // 40mm-00
  check += CheckV(GetVmonArm1(1, 1),600.0); // 40mm-01
  check += CheckV(GetVmonArm1(1, 2),600.0); // 40mm-02
  check += CheckV(GetVmonArm1(1, 3),600.0); // 40mm-03
  check += CheckV(GetVmonArm1(1, 4),600.0); // 40mm-04
  check += CheckV(GetVmonArm1(1, 5),600.0); // 40mm-05 
  check += CheckV(GetVmonArm1(1, 6),600.0); // 40mm-06
  check += CheckV(GetVmonArm1(1, 7),600.0); // 40mm-07
  check += CheckV(GetVmonArm1(1, 8),600.0); // 40mm-08
  check += CheckV(GetVmonArm1(1, 9),600.0); // 40mm-09
  check += CheckV(GetVmonArm1(1,10),600.0); // 40mm-10
  check += CheckV(GetVmonArm1(1,11),600.0); // 40mm-11
  check += CheckV(GetVmonArm1(1,12),600.0); // 40mm-12
  check += CheckV(GetVmonArm1(1,13),600.0); // 40mm-13
  check += CheckV(GetVmonArm1(1,14),600.0); // 40mm-14
  check += CheckV(GetVmonArm1(1,15),600.0); // 40mm-15  
  if(check==0){
    strcpy(a1_PMTgain,"Normal-High"); 
    return 0;
  } 
  
  // Check High-Normal -----------------
  check = 0;
  check += CheckV(GetVmonArm1(0, 0),600.0); // 20mm-00
  check += CheckV(GetVmonArm1(0, 1),600.0); // 20mm-01
  check += CheckV(GetVmonArm1(0, 2),600.0); // 20mm-02
  check += CheckV(GetVmonArm1(0, 3),600.0); // 20mm-03
  check += CheckV(GetVmonArm1(0, 4),600.0); // 20mm-04
  check += CheckV(GetVmonArm1(0, 5),600.0); // 20mm-05 
  check += CheckV(GetVmonArm1(0, 6),600.0); // 20mm-06
  check += CheckV(GetVmonArm1(0, 7),600.0); // 20mm-07
  check += CheckV(GetVmonArm1(0, 8),600.0); // 20mm-08
  check += CheckV(GetVmonArm1(0, 9),600.0); // 20mm-09
  check += CheckV(GetVmonArm1(0,10),600.0); // 20mm-10
  check += CheckV(GetVmonArm1(0,11),600.0); // 20mm-11
  check += CheckV(GetVmonArm1(0,12),600.0); // 20mm-12
  check += CheckV(GetVmonArm1(0,13),600.0); // 20mm-13
  check += CheckV(GetVmonArm1(0,14),600.0); // 20mm-14
  check += CheckV(GetVmonArm1(0,15),600.0); // 20mm-15

  check += CheckV(GetVmonArm1(1, 0),475.0); // 40mm-00
  check += CheckV(GetVmonArm1(1, 1),475.0); // 40mm-01
  check += CheckV(GetVmonArm1(1, 2),475.0); // 40mm-02
  check += CheckV(GetVmonArm1(1, 3),500.0); // 40mm-03
  check += CheckV(GetVmonArm1(1, 4),500.0); // 40mm-04
  check += CheckV(GetVmonArm1(1, 5),500.0); // 40mm-05 
  check += CheckV(GetVmonArm1(1, 6),500.0); // 40mm-06
  check += CheckV(GetVmonArm1(1, 7),500.0); // 40mm-07
  check += CheckV(GetVmonArm1(1, 8),475.0); // 40mm-08
  check += CheckV(GetVmonArm1(1, 9),475.0); // 40mm-09
  check += CheckV(GetVmonArm1(1,10),475.0); // 40mm-10
  check += CheckV(GetVmonArm1(1,11),500.0); // 40mm-11
  check += CheckV(GetVmonArm1(1,12),475.0); // 40mm-12
  check += CheckV(GetVmonArm1(1,13),475.0); // 40mm-13
  check += CheckV(GetVmonArm1(1,14),475.0); // 40mm-14
  check += CheckV(GetVmonArm1(1,15),475.0); // 40mm-15  
  if(check==0){
    strcpy(a1_PMTgain,"High-Normal"); 
    return 0;
  }  

  // Check Low -----------------
  check = 0;
  check += CheckV(GetVmonArm1(0, 0),450.0); // 20mm-00
  check += CheckV(GetVmonArm1(0, 1),425.0); // 20mm-01
  check += CheckV(GetVmonArm1(0, 2),450.0); // 20mm-02
  check += CheckV(GetVmonArm1(0, 3),450.0); // 20mm-03
  check += CheckV(GetVmonArm1(0, 4),450.0); // 20mm-04
  check += CheckV(GetVmonArm1(0, 5),500.0); // 20mm-05 
  check += CheckV(GetVmonArm1(0, 6),450.0); // 20mm-06
  check += CheckV(GetVmonArm1(0, 7),450.0); // 20mm-07
  check += CheckV(GetVmonArm1(0, 8),450.0); // 20mm-08
  check += CheckV(GetVmonArm1(0, 9),425.0); // 20mm-09
  check += CheckV(GetVmonArm1(0,10),450.0); // 20mm-10
  check += CheckV(GetVmonArm1(0,11),450.0); // 20mm-11
  check += CheckV(GetVmonArm1(0,12),450.0); // 20mm-12
  check += CheckV(GetVmonArm1(0,13),450.0); // 20mm-13
  check += CheckV(GetVmonArm1(0,14),450.0); // 20mm-14
  check += CheckV(GetVmonArm1(0,15),450.0); // 20mm-15
  check += CheckV(GetVmonArm1(1, 0),425.0); // 40mm-00
  check += CheckV(GetVmonArm1(1, 1),425.0); // 40mm-01
  check += CheckV(GetVmonArm1(1, 2),425.0); // 40mm-02
  check += CheckV(GetVmonArm1(1, 3),450.0); // 40mm-03
  check += CheckV(GetVmonArm1(1, 4),450.0); // 40mm-04
  check += CheckV(GetVmonArm1(1, 5),450.0); // 40mm-05 
  check += CheckV(GetVmonArm1(1, 6),450.0); // 40mm-06
  check += CheckV(GetVmonArm1(1, 7),450.0); // 40mm-07
  check += CheckV(GetVmonArm1(1, 8),425.0); // 40mm-08
  check += CheckV(GetVmonArm1(1, 9),425.0); // 40mm-09
  check += CheckV(GetVmonArm1(1,10),425.0); // 40mm-10
  check += CheckV(GetVmonArm1(1,11),450.0); // 40mm-11
  check += CheckV(GetVmonArm1(1,12),425.0); // 40mm-12
  check += CheckV(GetVmonArm1(1,13),425.0); // 40mm-13
  check += CheckV(GetVmonArm1(1,14),425.0); // 40mm-14
  check += CheckV(GetVmonArm1(1,15),425.0); // 40mm-15

  if(check==0){
    strcpy(a1_PMTgain,"Low"); 
    return 0;
  }  
 

  // No defined
  strcpy(a1_PMTgain,"Unknown"); 
  return -1;
}

int ReadRunData::CheckArm2PMT(){

  int check = 0;
  // Check Off -------------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm2(it,ich),0.);    
    }
  }  
  if(check==0){
    strcpy(a2_PMTgain,"off");
    return 0;
  }
  
  // Check All600V ----------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm2(it,ich),600.);
    }
  }
  if(check==0){
    strcpy(a2_PMTgain,"All600V"); 
    return 0;
  }

  // Check All600V ----------------------------
  check = 0;
  for(int it=0;it<2;it++){
    for(int ich=0;ich<16;ich++){
      check += CheckV(GetVmonArm2(it,ich),450.);
    }
  }
  if(check==0){
    strcpy(a2_PMTgain,"All450V"); 
    return 0;
  }
  
  // Check Normal at 7TeV cms -----------------
  check = 0;
  check += CheckV(GetVmonArm2(0, 0),500.0); // 25mm-00
  check += CheckV(GetVmonArm2(0, 1),475.0); // 25mm-01
  check += CheckV(GetVmonArm2(0, 2),500.0); // 25mm-02
  check += CheckV(GetVmonArm2(0, 3),500.0); // 25mm-03
  check += CheckV(GetVmonArm2(0, 4),500.0); // 25mm-04
  check += CheckV(GetVmonArm2(0, 5),500.0); // 25mm-05 
  check += CheckV(GetVmonArm2(0, 6),500.0); // 25mm-06
  check += CheckV(GetVmonArm2(0, 7),500.0); // 25mm-07
  check += CheckV(GetVmonArm2(0, 8),500.0); // 25mm-08
  check += CheckV(GetVmonArm2(0, 9),500.0); // 25mm-09
  check += CheckV(GetVmonArm2(0,10),500.0); // 25mm-10
  check += CheckV(GetVmonArm2(0,11),500.0); // 25mm-11
  check += CheckV(GetVmonArm2(0,12),500.0); // 25mm-12
  check += CheckV(GetVmonArm2(0,13),475.0); // 25mm-13
  check += CheckV(GetVmonArm2(0,14),500.0); // 25mm-14
  check += CheckV(GetVmonArm2(0,15),500.0); // 25mm-15
  
  check += CheckV(GetVmonArm2(1, 0),500.0); // 32mm-00
  check += CheckV(GetVmonArm2(1, 1),500.0); // 32mm-01
  check += CheckV(GetVmonArm2(1, 2),500.0); // 32mm-02
  check += CheckV(GetVmonArm2(1, 3),500.0); // 32mm-03
  check += CheckV(GetVmonArm2(1, 4),500.0); // 32mm-04
  check += CheckV(GetVmonArm2(1, 5),500.0); // 32mm-05 
  check += CheckV(GetVmonArm2(1, 6),500.0); // 32mm-06
  check += CheckV(GetVmonArm2(1, 7),500.0); // 32mm-07
  check += CheckV(GetVmonArm2(1, 8),500.0); // 32mm-08
  check += CheckV(GetVmonArm2(1, 9),500.0); // 32mm-09
  check += CheckV(GetVmonArm2(1,10),500.0); // 32mm-10
  check += CheckV(GetVmonArm2(1,11),500.0); // 32mm-11
  check += CheckV(GetVmonArm2(1,12),500.0); // 32mm-12
  check += CheckV(GetVmonArm2(1,13),500.0); // 32mm-13
  check += CheckV(GetVmonArm2(1,14),500.0); // 32mm-14
  check += CheckV(GetVmonArm2(1,15),500.0); // 32mm-15  

  if(check==0){
    strcpy(a2_PMTgain,"Normal"); 
    return 0;
  }  

  // Check Normal-High -----------------
  check = 0;
  check += CheckV(GetVmonArm2(0, 0),500.0); // 20mm-00
  check += CheckV(GetVmonArm2(0, 1),475.0); // 20mm-01
  check += CheckV(GetVmonArm2(0, 2),500.0); // 20mm-02
  check += CheckV(GetVmonArm2(0, 3),500.0); // 20mm-03
  check += CheckV(GetVmonArm2(0, 4),500.0); // 20mm-04
  check += CheckV(GetVmonArm2(0, 5),500.0); // 20mm-05 
  check += CheckV(GetVmonArm2(0, 6),500.0); // 20mm-06
  check += CheckV(GetVmonArm2(0, 7),500.0); // 20mm-07
  check += CheckV(GetVmonArm2(0, 8),500.0); // 20mm-08
  check += CheckV(GetVmonArm2(0, 9),500.0); // 20mm-09
  check += CheckV(GetVmonArm2(0,10),500.0); // 20mm-10
  check += CheckV(GetVmonArm2(0,11),500.0); // 20mm-11
  check += CheckV(GetVmonArm2(0,12),500.0); // 20mm-12
  check += CheckV(GetVmonArm2(0,13),475.0); // 20mm-13
  check += CheckV(GetVmonArm2(0,14),500.0); // 20mm-14
  check += CheckV(GetVmonArm2(0,15),500.0); // 20mm-15
  
  check += CheckV(GetVmonArm2(1, 0),600.0); // 32mm-00
  check += CheckV(GetVmonArm2(1, 1),600.0); // 32mm-01
  check += CheckV(GetVmonArm2(1, 2),600.0); // 32mm-02
  check += CheckV(GetVmonArm2(1, 3),600.0); // 32mm-03
  check += CheckV(GetVmonArm2(1, 4),600.0); // 32mm-04
  check += CheckV(GetVmonArm2(1, 5),600.0); // 32mm-05 
  check += CheckV(GetVmonArm2(1, 6),600.0); // 32mm-06
  check += CheckV(GetVmonArm2(1, 7),600.0); // 32mm-07
  check += CheckV(GetVmonArm2(1, 8),600.0); // 32mm-08
  check += CheckV(GetVmonArm2(1, 9),600.0); // 32mm-09
  check += CheckV(GetVmonArm2(1,10),600.0); // 32mm-10
  check += CheckV(GetVmonArm2(1,11),600.0); // 32mm-11
  check += CheckV(GetVmonArm2(1,12),600.0); // 32mm-12
  check += CheckV(GetVmonArm2(1,13),600.0); // 32mm-13
  check += CheckV(GetVmonArm2(1,14),600.0); // 32mm-14
  check += CheckV(GetVmonArm2(1,15),600.0); // 32mm-15  

  if(check==0){
    strcpy(a2_PMTgain,"Normal-High"); 
    return 0;
  }

  // Check High-Normal -----------------
  check = 0;
  check += CheckV(GetVmonArm2(0, 0),600.0); // 20mm-00
  check += CheckV(GetVmonArm2(0, 1),600.0); // 20mm-01
  check += CheckV(GetVmonArm2(0, 2),600.0); // 20mm-02
  check += CheckV(GetVmonArm2(0, 3),600.0); // 20mm-03
  check += CheckV(GetVmonArm2(0, 4),600.0); // 20mm-04
  check += CheckV(GetVmonArm2(0, 5),600.0); // 20mm-05 
  check += CheckV(GetVmonArm2(0, 6),600.0); // 20mm-06
  check += CheckV(GetVmonArm2(0, 7),600.0); // 20mm-07
  check += CheckV(GetVmonArm2(0, 8),600.0); // 20mm-08
  check += CheckV(GetVmonArm2(0, 9),600.0); // 20mm-09
  check += CheckV(GetVmonArm2(0,10),600.0); // 20mm-10
  check += CheckV(GetVmonArm2(0,11),600.0); // 20mm-11
  check += CheckV(GetVmonArm2(0,12),600.0); // 20mm-12
  check += CheckV(GetVmonArm2(0,13),600.0); // 20mm-13
  check += CheckV(GetVmonArm2(0,14),600.0); // 20mm-14
  check += CheckV(GetVmonArm2(0,15),600.0); // 20mm-15

  check += CheckV(GetVmonArm2(1, 0),500.0); // 32mm-00
  check += CheckV(GetVmonArm2(1, 1),500.0); // 32mm-01
  check += CheckV(GetVmonArm2(1, 2),500.0); // 32mm-02
  check += CheckV(GetVmonArm2(1, 3),500.0); // 32mm-03
  check += CheckV(GetVmonArm2(1, 4),500.0); // 32mm-04
  check += CheckV(GetVmonArm2(1, 5),500.0); // 32mm-05 
  check += CheckV(GetVmonArm2(1, 6),500.0); // 32mm-06
  check += CheckV(GetVmonArm2(1, 7),500.0); // 32mm-07
  check += CheckV(GetVmonArm2(1, 8),500.0); // 32mm-08
  check += CheckV(GetVmonArm2(1, 9),500.0); // 32mm-09
  check += CheckV(GetVmonArm2(1,10),500.0); // 32mm-10
  check += CheckV(GetVmonArm2(1,11),500.0); // 32mm-11
  check += CheckV(GetVmonArm2(1,12),500.0); // 32mm-12
  check += CheckV(GetVmonArm2(1,13),500.0); // 32mm-13
  check += CheckV(GetVmonArm2(1,14),500.0); // 32mm-14
  check += CheckV(GetVmonArm2(1,15),500.0); // 32mm-15  

  if(check==0){
    strcpy(a2_PMTgain,"high-Normal"); 
    return 0;
  } 

  // Check Low -----------------
  check = 0;
  check += CheckV(GetVmonArm2(0, 0),450.0); // 25mm-00
  check += CheckV(GetVmonArm2(0, 1),425.0); // 25mm-01
  check += CheckV(GetVmonArm2(0, 2),450.0); // 25mm-02
  check += CheckV(GetVmonArm2(0, 3),450.0); // 25mm-03
  check += CheckV(GetVmonArm2(0, 4),450.0); // 25mm-04
  check += CheckV(GetVmonArm2(0, 5),450.0); // 25mm-05 
  check += CheckV(GetVmonArm2(0, 6),450.0); // 25mm-06
  check += CheckV(GetVmonArm2(0, 7),450.0); // 25mm-07
  check += CheckV(GetVmonArm2(0, 8),450.0); // 25mm-08
  check += CheckV(GetVmonArm2(0, 9),450.0); // 25mm-09
  check += CheckV(GetVmonArm2(0,10),450.0); // 25mm-10
  check += CheckV(GetVmonArm2(0,11),450.0); // 25mm-11
  check += CheckV(GetVmonArm2(0,12),450.0); // 25mm-12
  check += CheckV(GetVmonArm2(0,13),425.0); // 25mm-13
  check += CheckV(GetVmonArm2(0,14),450.0); // 25mm-14
  check += CheckV(GetVmonArm2(0,15),450.0); // 25mm-15
  
  check += CheckV(GetVmonArm2(1, 0),450.0); // 32mm-00
  check += CheckV(GetVmonArm2(1, 1),450.0); // 32mm-01
  check += CheckV(GetVmonArm2(1, 2),450.0); // 32mm-02
  check += CheckV(GetVmonArm2(1, 3),450.0); // 32mm-03
  check += CheckV(GetVmonArm2(1, 4),450.0); // 32mm-04
  check += CheckV(GetVmonArm2(1, 5),450.0); // 32mm-05 
  check += CheckV(GetVmonArm2(1, 6),450.0); // 32mm-06
  check += CheckV(GetVmonArm2(1, 7),450.0); // 32mm-07
  check += CheckV(GetVmonArm2(1, 8),450.0); // 32mm-08
  check += CheckV(GetVmonArm2(1, 9),450.0); // 32mm-09
  check += CheckV(GetVmonArm2(1,10),450.0); // 32mm-10
  check += CheckV(GetVmonArm2(1,11),450.0); // 32mm-11
  check += CheckV(GetVmonArm2(1,12),450.0); // 32mm-12
  check += CheckV(GetVmonArm2(1,13),450.0); // 32mm-13
  check += CheckV(GetVmonArm2(1,14),450.0); // 32mm-14
  check += CheckV(GetVmonArm2(1,15),450.0); // 32mm-15  

  if(check==0){
    strcpy(a2_PMTgain,"Low"); 
    return 0;
  }  

  // No defined
  strcpy(a2_PMTgain,"Unknown"); 
  return -1;
}

int ReadRunData::CheckArm1SciFi(){
  double scifihv = sc->GetData()->adc.cal[13];
  if(fabs(scifihv+0.)  <5.){ strcpy(a1_scifigain,"off"); return 0;}
  if(fabs(scifihv+600.)<5.){ strcpy(a1_scifigain,"600V");return 0;}
  if(fabs(scifihv+540.)<5.){ strcpy(a1_scifigain,"540V");return 0;} 
  if(fabs(scifihv+480.)<5.){ strcpy(a1_scifigain,"480V");return 0;}
  if(fabs(scifihv+950.)<5.){ strcpy(a1_scifigain,"950V");return 0;}  
  strcpy(a1_scifigain,"-");
  return -1;
}

int ReadRunData::CheckArm1Position(){
  double position = sc->GetData()->adc.cal[9];
  if(position > 90.){
    sprintf(a1_position,"garage(%.2lf)",position); 
    return 0;
  }
  if(fabs(position-0.1)<0.5){
    sprintf(a1_position,"tmp_beam_center(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+5.0)<0.5){
    sprintf(a1_position,"5mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+6.0)<0.5){
    sprintf(a1_position,"6mmlower(%.2lf)",position); 
    return 0;
  } 
  if(fabs(position+8.0)<0.5){
    sprintf(a1_position,"8mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+9.0)<0.5){
    sprintf(a1_position,"9mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+10.0)<0.5){
    sprintf(a1_position,"10mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+14.0)<0.5){
    sprintf(a1_position,"14mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+19.0)<0.5){
    sprintf(a1_position,"19mmlower(%.2lf)",position); 
    return 0;
  } 
  if(fabs(position+21.2)<0.5){
    sprintf(a1_position,"bottom(%.2lf)",position); 
    return 0;
  }
  sprintf(a1_position,"no_defined(%.2lf)",position); 
  return -1;
}

int ReadRunData::CheckArm2Position(){
  double position = sc->GetData()->adc.cal[11];
  if(position > 90.){
    sprintf(a2_position,"garage(%.2lf)",position); 
    return 0;
  }
  if(fabs(position-4.3)<0.5){
    sprintf(a2_position,"tmp_beam_center(%.2lf)",position); 
    return 0;
  }
  if(fabs(position-0.1)<0.5){
    sprintf(a2_position,"beam_center(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+0.7)<0.5){
    sprintf(a2_position,"5mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+3.7)<0.5){
    sprintf(a2_position,"8mmlower(%.2lf)",position); 
    return 0;
  }
   if(fabs(position+4.7)<0.5){
    sprintf(a2_position,"9mmlower(%.2lf)",position); 
    return 0;
   } 
   if(fabs(position+5.7)<0.5){
    sprintf(a2_position,"10mmlower(%.2lf)",position); 
    return 0;
  }
  if(fabs(position+9.7)<0.5){
    sprintf(a2_position,"14mmlower(%.2lf)",position); 
    return 0;
  }  
  if(fabs(position+14.7)<0.5){
    sprintf(a2_position,"19mmlower(%.2lf)",position); 
    return 0;
  } 
  if(fabs(position+17.7)<0.5){
    sprintf(a2_position,"22mmlower(%.2lf)",position); 
    return 0;
  }
  sprintf(a2_position,"no_defined(%.2lf)",position); 
  return -1;
}

int ReadRunData::CheckV(double V0,double V1){
  const double threshold=2.;
  if(fabs(V0-V1)<threshold){
    return 0;
  }
  else{
    return 1;
  }
}

double ReadRunData::GetVmonArm1(int it, int ich){
  int slot2ch[2][16][2] = {
    {
      {0, 0},   // ch00
      {0, 1},   // ch01
      {0, 2},   // ch02
      {0, 3},   // ch03
      {0, 4},   // ch04
      {0, 5},   // ch05
      {0, 6},   // ch06
      {0, 7},   // ch07
      {0, 8},   // ch08
      {0, 9},   // ch09
      {0,10},   // ch10
      {0,11},   // ch11
      {1, 0},   // ch12
      {1, 1},   // ch13
      {1, 2},   // ch14
      {1, 3}    // ch15
    },
    {
      {1, 4},   // ch00
      {1, 5},   // ch01
      {1, 6},   // ch02
      {1, 7},   // ch03
      {1, 8},   // ch04
      {1, 9},   // ch05
      {1,10},   // ch06
      {1,11},   // ch07
      {2, 8},   // ch08
      {2, 1},   // ch09
      {2, 2},   // ch10
      {2, 3},   // ch11
      {2, 4},   // ch12
      {2, 5},   // ch13
      {2, 6},   // ch14
      {2, 7}    // ch15
    }
  };
  
  if(slot2ch[it][ich][0]==0){
    return sc->GetData()->cpws1.slot0[ slot2ch[it][ich][1] ].vmon;
  }
  else if(slot2ch[it][ich][0]==1){
    return sc->GetData()->cpws1.slot1[ slot2ch[it][ich][1] ].vmon;  
  }
  else if(slot2ch[it][ich][0]==2){
    return sc->GetData()->cpws1.slot2[ slot2ch[it][ich][1] ].vmon;  
  }
  return 0;
}


double ReadRunData::GetVmonArm2(int it, int ich){
  int slot2ch[2][16][2] = {
    {
      {0, 0},   // ch00
      {0, 1},   // ch01
      {0, 2},   // ch02
      {0, 3},   // ch03
      {0, 4},   // ch04
      {0, 5},   // ch05
      {0, 6},   // ch06
      {0, 7},   // ch07
      {0, 8},   // ch08
      {0, 9},   // ch09
      {0,10},   // ch10
      {0,11},   // ch11
      {1, 0},   // ch12
      {1, 1},   // ch13
      {1, 2},   // ch14
      {1, 3}    // ch15
    },
    {
      {1, 4},   // ch00
      {1, 5},   // ch01
      {1, 6},   // ch02
      {1, 7},   // ch03
      {1, 8},   // ch04
      {1, 9},   // ch05
      {1,10},   // ch06
      {1,11},   // ch07
      {2, 0},   // ch08
      {2, 1},   // ch09
      {2, 2},   // ch10
      {2, 3},   // ch11
      {2, 4},   // ch12
      {2, 5},   // ch13
      {2, 6},   // ch14
      {2, 7}    // ch15
    }
  };
  
  if(slot2ch[it][ich][0]==0){
    return sc->GetData()->cpws2.slot0[ slot2ch[it][ich][1] ].vmon;
  }
  else if(slot2ch[it][ich][0]==1){
    return sc->GetData()->cpws2.slot1[ slot2ch[it][ich][1] ].vmon;  
  }
  else if(slot2ch[it][ich][0]==2){
    return sc->GetData()->cpws2.slot2[ slot2ch[it][ich][1] ].vmon;  
  }
  return 0;
}





#endif
