#ifndef __READDAQLOG_H__

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ReadDAQLog{
 public:
  int    run;
  int    runmode;
  int    scifidaq;
  int    w_star;
  char   GPIOLogic[256];
  char   GPIOLogicFiles[2][256];
  char   GPIOSetup[256];
  char   GPIOSetupFile[256];
  char   Discri[256];
  int    presetMB;
  int    presetSP;
  
 public:
  ReadDAQLog();
  int Read(char* filename,int run_number);
  int ReplaceSpacesToUnderbars(char *);
};

ReadDAQLog::ReadDAQLog(){
  run = -1;
  runmode = -1;
  scifidaq = -1;
  w_star = -1;
  strcpy(GPIOLogic,"-");
  strcpy(GPIOLogicFiles[0],"-");
  strcpy(GPIOLogicFiles[1],"-");
  strcpy(GPIOSetup,"-");
  strcpy(GPIOSetupFile,"-");
  strcpy(Discri,"-");
  presetMB = 0;
  presetSP = 0;  
}

int ReadDAQLog::ReplaceSpacesToUnderbars(char *tmp){
  for(int i=0;i<strlen(tmp);i++){
	 if(tmp[i]==' ') tmp[i] = '_';
  }
  return 0;
}

int ReadDAQLog::Read(char* filename,int run_number){
  ifstream fin(filename);
  if(!fin){
    cerr << "[ReadDAQLog::Read] "
	 << "Cannot open " << filename << endl;
    return -1;
  }
  
  int icbuf = 0;
  string stmp;
  while(1){
    fin >> stmp;
    if(fin.eof()){break;}
  
    if(stmp=="RUN:"){fin >> run;}
    if(run!=run_number){continue;}
    
    if(stmp=="RUNMODE:")    {fin >> runmode;}
    else if(stmp=="SCIFI_DAQ:"){
      fin >> stmp;
      scifidaq = (stmp=="YES" ? 1 : 0) ;
    } 
    else if(stmp=="OPERATION_W_STAR:"){
      fin >> stmp;
      w_star = (stmp=="yes" ? 1 : 0) ;
    }
    else if(stmp=="GPIO_LOGIC:"){fin >> GPIOLogic;}
	 else if(stmp=="GPIO_FIELS:"){fin >> GPIOLogicFiles[0] >> GPIOLogicFiles[1];}
	 else if(stmp=="LOGIC_MODE:"){fin >> GPIOSetup;}   
    else if(stmp=="GPIO_SETUP:"){fin >> GPIOSetupFile;}  
    else if(stmp=="DISCRI:"){
		// fin >> Discri;
		getline(fin,stmp);
		strncpy(Discri,stmp.c_str()+6,stmp.length()-32);
		ReplaceSpacesToUnderbars(Discri);
	 } 
    else if(stmp=="COUNTERBUF"){
      fin >> icbuf;
      if(icbuf==0){fin >> presetMB;}
      if(icbuf==1){fin >> presetSP;}
    }
    if(stmp=="END_TIME:" && run==run_number){break;}
  }

  if(run==run_number){
    return 0;
  }
  else{
    return -2;
  }
}


#endif
