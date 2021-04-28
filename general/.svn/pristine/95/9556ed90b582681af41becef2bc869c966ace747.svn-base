#include __CONDISCRILEVEL_CPP__
#define  __CONDISCRILEVEL_CPP__

#include "ConDiscriLevel.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

const int ConDiscriLevel::NBOARD;
const int ConDiscriLevel::NCH;

ConDiscriLevel::ConDiscriLevel(){;}

ConDiscriLevel::~ConDiscriLevel(){;}

int  ConDiscriLevel::Read(char *file, char* option){
  int dscparam_version = 0;
  int dscparam_type = 0;
    
  ifstream fin;
  fin.open(paramfile);
  
  if(!fin){
    cerr << "[frontend:begin_of_run] Cannot Open "
	 << paramfile << endl;
    return -1;
  }
  
  char a[256];
  while(1){
    fin >> a;
    if(fin.eof()) {break}
    
    if(strcmp(a,"DSC_PARAM_END")==0){break;}
    if(strcmp(a,"DSC_PARAM_START")==0){check=true;}
    if(check!=true){continue;}
    if(strcmp(a,"DSCPARAM_VERSION:")==0){fin >> dscparam_version;}
    if(strcmp(a,"DSCPARAM_TYPE:")==0){fin >> dscparam_type;}
    if(strcmp(a,"DSC0:")==0){
      for(int ich=0;ich<PARAM_A1_DSC0_NCH;ich++){ fin >> dsc0_dlevel[ich];}
    }
    if(strcmp(a,"DSC1:")==0){
      for(int ich=0;ich<PARAM_A1_DSC1_NCH;ich++){ fin >> dsc1_dlevel[ich];}
    }
  }
}
fin.close();

    
}
