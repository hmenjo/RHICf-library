#include <iostream>
#include <iomanip>
#include <LHCfRunInfoTable.h>
#include <ReadDAQLog.h>
#include <ReadRunData.h>
using namespace std;

int main(int argc,char** argv){

  int   run = -1;
  char  logfile_frontend_arm1[256] = "";
  char  logfile_frontend_arm2[256] = "";
  char  rundatafile[256] = "";
  char  runinfofile[256] = "";
  for(int ic=0;ic<argc;ic++){
    if(strcmp(argv[ic],"-run")==0 || strcmp(argv[ic],"-r")==0  ){
      run = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-a1log")==0){
      strcpy(logfile_frontend_arm1,argv[++ic]);
    } 
    if(strcmp(argv[ic],"-a2log")==0){
      strcpy(logfile_frontend_arm2,argv[++ic]);
    } 
    if(strcmp(argv[ic],"-rundata")==0){
      strcpy(rundatafile,argv[++ic]);
    }
    if(strcmp(argv[ic],"-runinfo")==0){
      strcpy(runinfofile,argv[++ic]);
    } 
    if(argc==1 || strcmp(argv[ic],"-h")==0 || strcmp(argv[ic],"-help")==0){
      cerr << " filldaqinfo  \n" 
	   << " Read frontend log files and fill daq infomation to runinfo.\n" 
	   << "  exp.)\n"
	   << "   ./filldaqinfo -run 3000 -a1log frontend_arm1_log2 \\ \n" 
	   << "    -a2log frontend_arm2_log2 -runinfo runinfo_run03000.dat\n"
	   << "  options)\n"
	   << "    -run      : run number \n"
	   << "    -a1log    : Arm1 Frontend log file (input)\n"
	   << "    -a2log    : Arm2 Frontend log file (input)\n"
	   << "    -rundata  : Run data including sc_first, alcal1last etc.(input)\n"
	   << "    -runinfo  : Runinfo file (updated)\n"
	   << endl;
      exit(1);
    }    
  }

  if(run < 0 ){cerr << "Give run number" << endl; exit(-1);}
  if(strcmp(logfile_frontend_arm1,"")==0){ cerr << "Give arm1 log file" << endl; exit(-1);}
  if(strcmp(logfile_frontend_arm2,"")==0){ cerr << "Give arm2 log file" << endl; exit(-1);}  
  if(strcmp(runinfofile,"")==0){ cerr << "Give runinfo file" << endl; exit(-1);} 
  
  // Open Runinfo File +++++++++++++++++++++++++++++++++++++++++++
  LHCfRunInfo      *info;
  LHCfRunInfoTable *infotable = new LHCfRunInfoTable();
  infotable->ReadTable(runinfofile);
  if(infotable->Get(run)){
    info = infotable->Get(run);
  }
  else{
    info = infotable->CreateInfo(); 
  }
  cout << endl
       << " RUN: " << run << endl;
  
  // Read Frontend Log File ++++++++++++++++++++++++++++++++++++++
  
  int check = 0;
  // For Arm1
  ReadDAQLog a1log;
  check = a1log.Read(logfile_frontend_arm1,run);
  if(check==-2){ 
    cerr << "No run " << run << "  in " << logfile_frontend_arm1 << endl;
  }
  else if(check >= 0){
    cout << " READ : " << logfile_frontend_arm1 << endl;
    info->a1_runmode  = a1log.runmode;
    strcpy(info->LTPmode,      a1log.LTPmode);
    strcpy(info->a1_GPIOLoad,  a1log.GPIOLogic);
    strcpy(info->a1_GPIOSetup, a1log.GPIOSetup);
    strcpy(info->a1_Discriminator, a1log.Discri);
    info->a1_scifidaq = a1log.scifidaq;
    info->a1_nevent_presetMB = a1log.presetMB;
    info->a1_nevent_presetSP = a1log.presetSP;
  }
  
  // For Arm2
  ReadDAQLog a2log;
  check = a2log.Read(logfile_frontend_arm2,run);
  if(check==-2){ 
    cerr << "No run " << run << "  in " << logfile_frontend_arm2 << endl;
  }
  else if(check >= 0){
    cout << " READ : " << logfile_frontend_arm2 << endl;
    info->a2_runmode  = a2log.runmode;
    strcpy(info->a2_GPIOLoad,  a2log.GPIOLogic);
    strcpy(info->a2_GPIOSetup, a2log.GPIOSetup);
    strcpy(info->a2_Discriminator, a2log.Discri);
    info->a2_silicondaq = a2log.silicondaq;
    sprintf(info->a2_silicongain,"%s,%s",a2log.SiliconGain,a2log.SiliconLatency); 
    info->a2_nevent_presetMB = a2log.presetMB;
    info->a2_nevent_presetSP = a2log.presetSP;
  }

  // for SPS data
  strcpy(info->a1_GPIOLoad,  "-");
  strcpy(info->a1_GPIOLoad,  "-");
  
  // Fill from RunData ++++++++++++++++++++++++++++++++++++++++++
  
  ReadRunData rundata;
  if(rundata.Read(rundatafile)==0){
    strcpy(info->a1_PMTgain,  rundata.a1_PMTgain);
    strcpy(info->a2_PMTgain,  rundata.a2_PMTgain);
    strcpy(info->a1_scifigain,rundata.a1_scifigain);
    strcpy(info->a1_position, rundata.a1_position);
    strcpy(info->a2_position, rundata.a2_position);
    
    info->stable_beam = rundata.stable_beam;
    
  }


  // Write to runinfo file ++++++++++++++++++++++++++++++++++++++
  infotable->WriteTable(runinfofile,1);
  cout << " UPDATED " << runinfofile << endl;
 
  cout << endl;
  return 0;
}

