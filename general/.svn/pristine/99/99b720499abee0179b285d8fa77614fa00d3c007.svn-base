#include <iostream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#if defined(__CINT__) && !defined(__MAKECINT__)
#include "libLHCfEvent.so"
#include "libLHCfFunction.so"
#else
#include "LHCfRunInfoTable.h"
#endif
using namespace std;


int main(int argc, char** argv){

  char runtablefile[256] = "";
  int  srun = 0;
  int  erun = 0;
  for(int i=0;i<argc;i++){
   if(strcmp(argv[i],"-i")==0){
     strcpy(runtablefile,argv[++i]);
   }
   if(strcmp(argv[i],"-s")==0 || strcmp(argv[i],"-srun")==0){
     srun = atoi(argv[++i]); 
     strcpy(runtablefile,"");
   }
   if(strcmp(argv[i],"-e")==0 || strcmp(argv[i],"-erun")==0){
     erun = atoi(argv[++i]); 
     strcpy(runtablefile,"");
   }
   if(argc==0 || strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0){
     cout <<"\n" 
	  << "Caldaqtime\n"
	  << "  Calculate DAQ time and Statistics from RunInfo Table\n"
	  << "  You can choose which one runtable file or quick analysis results\n"
	  << "\n"
	  << " ./Caldaqtime -s [run number] -e [run number]\n"
	  << " Options)\n"
	  << "   -i [file]    : Input file \n"
	  << "   -s [run]     : Run number to calculate from quick analysis resutls.\n"
	  << "   -e [run]     : Run number to calculate from quick analysis resutls.\n"
	  << "\n"
	  << endl;
     exit(0);
   }
  }
  
  if((strcmp(runtablefile,"")==0 && (srun==0 || erun==0 || srun>erun ))){
    cerr << " Invalid arguments " << endl;
    exit(-1);
  }

  LHCfRunInfo* runinfo;
  LHCfRunInfoTable *runtable = new LHCfRunInfoTable();

  if(strcmp(runtablefile,"")){
    runtable->ReadTable(runtablefile);
  }
  else{
    for(int irun=srun;irun<=erun;irun++){
      sprintf(runtablefile,
	      "/data/analysis/quickanalysis/run%05d/runinfo_run%05d.dat",
	      irun,irun);
      runtable->ReadTable(runtablefile);
    }
  }
  
  int ninfo = runtable->GetNinfo();
  int totaltime=0;
  int total_a1_nevent=0,total_a1_l2ta=0;
  int total_a2_nevent=0,total_a2_l2ta=0;  
  int stime=0,etime=0;
  cout << endl;
  cout << setw(8)  << "RUN" 
       << setw(10) << "TIME"
       << setw(10) << "ARM1 TRG"
       << setw(10) << "ARM1 L2TA"
       << setw(10) << "ARM2 TRG"
       << setw(10) << "ARM2 L2TA"
       << endl;
  for(int i=0;i<ninfo;i++){
    runinfo = runtable->GetIinfo(i);
    cout << setw(8) << runinfo->run 
	 << setw(10) << runinfo->end_time - runinfo->start_time 
      	 << setw(10) << runinfo->a1_nevent
	 << setw(10) << runinfo->a1_nevent_L2TA
      	 << setw(10) << runinfo->a2_nevent
	 << setw(10) << runinfo->a2_nevent_L2TA
	 << endl;
    totaltime += runinfo->end_time - runinfo->start_time;
    total_a1_nevent += runinfo->a1_nevent;
    total_a1_l2ta   += runinfo->a1_nevent_L2TA;
    total_a2_nevent += runinfo->a2_nevent;
    total_a2_l2ta   += runinfo->a2_nevent_L2TA;
    if(stime==0) stime = runinfo->start_time;
    etime = runinfo->end_time;
  }
  cout << "----------------------------------------------------------"
       << endl;
  cout << setw(8) << "TOTAL" 
       << setw(10) << totaltime
       << setw(10) << total_a1_nevent
       << setw(10) << total_a1_l2ta
       << setw(10) << total_a2_nevent
       << setw(10) << total_a2_l2ta
       << endl;
  cout.setf(ios::fixed);
  cout << setprecision(2) 
       << setw(8)  << "RATE[Hz]" 
       << setw(10) << "-"
       << setw(10) << (double)total_a1_nevent/totaltime
       << setw(10) << (double)total_a1_l2ta/totaltime
       << setw(10) << (double)total_a2_nevent/totaltime
       << setw(10) << (double)total_a2_l2ta/totaltime
       << endl;

  time_t st,et;
  st = stime;
  et = etime;
  string stringst,stringet;
  stringst =  asctime(localtime(&st));
  stringet =  asctime(localtime(&et));
  cout << endl
       << "START: " << stringst
       << "END  : " << stringet
       << "TIME : " << (double)totaltime/3600 << " hours" << endl
       << endl;

  //totaltime += 2.66*3600.; // run 2341-2344 15min+25min+1h+1h
  //totaltime += 1.5*3600.; // run 2363
  //cout << "TOTAL " << totaltime << endl;

  return 0;
}
