#ifndef __READDAQLOG_H__

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ReadDAQLog_Op2015{
 public:
  int    run;
  int    runmode;
  int    scifidaq;
  int    silicondaq;
  char   LTPmode[50];
  char   LogicMode[50];
  char   V1495Logic[50];
  char   V1495Setup[50];
  char   GPIOLogic[50];
  char   GPIOSetup[50];
  char   Discri[50];
  char   SiliconGain[50];
  char   SiliconLatency[50];
  int    presetMB;
  int    presetSP;
  
 public:
  ReadDAQLog_Op2015();
  int Read(char* filename,int run_number);
};

ReadDAQLog_Op2015::ReadDAQLog_Op2015(){
  run = -1;
  runmode = -1;
  scifidaq = -1;
  silicondaq = -1;
  strcpy(LTPmode,"-");
  strcpy(LogicMode,"-");
  strcpy(V1495Logic,"-");
  strcpy(V1495Setup,"-");
  strcpy(GPIOLogic,"-");
  strcpy(GPIOSetup,"-");
  strcpy(Discri,"-");
  strcpy(SiliconGain,"-");
  strcpy(SiliconLatency,"-");
  presetMB = 0;
  presetSP = 0;  
}

int ReadDAQLog_Op2015::Read(char* filename,int run_number){
  ifstream fin(filename);
  if(!fin){
    cerr << "[ReadDAQLog_Op2015::Read] "
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
    else if(stmp=="SILICON_DAQ:"){
      fin >> stmp;
      silicondaq = (stmp=="YES" ? 1 : 0) ;
    }
    else if(stmp=="LTP_SETUP:"){fin >> LTPmode;}
    else if(stmp=="LOGIC_MODE:"){fin >> LogicMode;}
    else if(stmp=="V1495_LOGIC:"){fin >> V1495Logic;}
    else if(stmp=="V1495_SETUP:"){fin >> V1495Setup;}      
    else if(stmp=="GPIO_LOGIC:"){fin >> GPIOLogic;}
    else if(stmp=="GPIO_SETUP:"){fin >> GPIOSetup;}  
    else if(stmp=="DISCRI:"){fin >> Discri;} 
    else if(stmp=="SILICON_GAIN:"){fin >> SiliconGain;}
    else if(stmp=="SILICON_LATENCY:"){fin >> SiliconLatency;} 
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
