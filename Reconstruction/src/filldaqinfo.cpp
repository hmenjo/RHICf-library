#include <iostream>
#include <iomanip>
#include <RHICfRunInfoTable.h>
#include <ReadDAQLog.h>
using namespace std;

int main(int argc,char** argv){

  int   run = -1;
  char  logfile_frontend_arm1[256] = "";
  char  rundatafile[256] = "";
  char  runinfofile[256] = "";
  for(int ic=0;ic<argc;ic++){
    if(strcmp(argv[ic],"-run")==0 || strcmp(argv[ic],"-r")==0  ){
      run = atoi(argv[++ic]);
    }
    if(strcmp(argv[ic],"-a1log")==0){
      strcpy(logfile_frontend_arm1,argv[++ic]);
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
	   << "     -runinfo runinfo_run03000.dat\n"
	   << "  options)\n"
	   << "    -run      : run number \n"
	   << "    -a1log    : Arm1 Frontend log file (input)\n"
	   << "    -rundata  : Run data including sc_first, alcal1last etc.(input)\n"
	   << "    -runinfo  : Runinfo file (updated)\n"
	   << endl;
      exit(1);
    }    
  }

  if(run < 0 ){cerr << "Give run number" << endl; exit(-1);}
  if(strcmp(logfile_frontend_arm1,"")==0){ cerr << "Give arm1 log file" << endl; exit(-1);} 
  if(strcmp(runinfofile,"")==0){ cerr << "Give runinfo file" << endl; exit(-1);} 
  
  // Open Runinfo File +++++++++++++++++++++++++++++++++++++++++++
  RHICfRunInfo      *info;
  RHICfRunInfoTable *infotable = new RHICfRunInfoTable();
  infotable->ReadTable(runinfofile);
  if(infotable->Get(run)){
    info = infotable->Get(run);
  }
  else{
    info = infotable->CreateInfo(); 
  }
  cout << endl << " RUN: " << run << endl;
  
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
	 strcpy(info->a1_LogicMode, a1log.GPIOSetup);
    strcpy(info->a1_GPIOLoad,  a1log.GPIOLogic);
	 strcpy(info->a1_GPIOLoadFiles[0],  a1log.GPIOLogicFiles[0]);
	 strcpy(info->a1_GPIOLoadFiles[1],  a1log.GPIOLogicFiles[1]);
    strcpy(info->a1_GPIOSetup, a1log.GPIOSetupFile);
    strcpy(info->a1_Discriminator, a1log.Discri);
    info->a1_scifidaq = a1log.scifidaq;
    info->a1_nevent_presetMB = a1log.presetMB;
    info->a1_nevent_presetSP = a1log.presetSP;
	 info->common_operation = a1log.w_star;
  }

  // Write to runinfo file ++++++++++++++++++++++++++++++++++++++
  infotable->WriteTable(runinfofile,1);
  cout << " UPDATED " << runinfofile << endl;
 
  cout << endl;
  return 0;
}

