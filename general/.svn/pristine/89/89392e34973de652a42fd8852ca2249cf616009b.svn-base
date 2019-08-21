#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TLegend.h>
#include <TBox.h>
#if defined(__CINT__) && !defined(__MAKECINT__)
#include "libLHCfEvent.so"
#include "libLHCfFunction.so"
#else
#include "LHCfEvent.h"
#include "A2RawToCal1.h"
#include "LHCfRunInfoTable.h"
#endif
using namespace std;

void printhelp();
void EventSelection(char* filename);

#if !defined(__CINT__)
int main(int argc, char** argv){
  char filename[256];
  strcpy(filename,"");
  
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-i")==0){
      strcpy(filename,argv[++i]);
    }
    if(argc==1 ||
       strcmp(argv[i],"-h")==0){
      printhelp();
      return -1;
    }
  }
  
  if(strcmp(filename,"")==0){
    cout << "Please give the input file." << endl;
    return -1;
  }
  
  int tmp=1;
  TApplication theApp("App",&tmp,argv);
  EventSelection(filename);
  return 0;
}
#endif

void printhelp(){
  cout << "\n"
       << " EventSelection : Sample for LHCfRunInfo \n"
       << "   ./EventSelection -i [inputfile]\n"
       << endl;
}

void EventSelection(char* filename){

  // +++++++++++ OPEN DATA FILE ++++++++++++++
  LHCfEvent *ev = new LHCfEvent();
  TChain* tree = new TChain("LHCfEvents");
  tree->AddFile(filename);
  tree->SetBranchAddress("ev.",&ev);
  cout << "NEVENT: " << tree->GetEntries() << endl;
  
  // +++++++++ INITIALIZE FUNCTIONS ++++++++++
  
  A2RawToCal1 *a2rawtocal1 = new A2RawToCal1();

  // RunInfoTable ----------------------------
  //   LHCfRunInfo      : information of one run.
  //   LHCfRunInfoTable : Array of LHCfRunInfo
  LHCfRunInfo      *runinfo;   
  LHCfRunInfoTable *runtable = new LHCfRunInfoTable();
  // Fill the data from a ASCII file 
  // to LHCfRunInfo Array in LHCfRunInfoTable.
  runtable->ReadTable("runinfotable_Op2009.dat");

  // +++++++++++++++++++ LOOP ++++++++++++++++++++++++++
  int nevent = tree->GetEntries();
  int run,bunchtag;
  A2Raw  *a2raw;
  A2Cal1 *a2cal1 = new A2Cal1();
  int count_bc=0,count_non=0,count_dis=0;
  for(int ie=0;ie<nevent;ie++){
    ev->Delete();
    tree->GetEntry(ie);
    
    // +++++ Get Arm2 Event and convert to A2Cal1 +++++
    if(!ev->Check("a2raw")){continue;}
    a2raw = (A2Raw*)ev->Get("a2raw");
    a2rawtocal1->Convert(a2raw,a2cal1);
    
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++          Event Selection by LHCfRunInfo         +++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    run = a2cal1->run;
    // Get LHCfRunInfo of the run from LHCfRunInfoTable.
    // If no info of the run in the table, return NULL
    runinfo = runtable->GetRunInfo(run);
    if(runinfo==NULL){
      cerr << " No information of RUN" << run 
	   << " in the runtable. " << endl;
      break;
    }
    else{
      // Event cut by time.
      // Use LHCfRunInfo::CheckTime, the function return 1 
      // if the time of the event is in the time window for the physics analysis.
      // if not, it return 0. 
      // The time window is LHCfRunInfo::analysis_cut_stime - analysis_cut_etime
      // The function also check a quality parameter of analysis_quality.
      // If it is -1 (bad), always return 0.
      if( !runinfo->CheckTime(a2cal1) ){ continue; }
      
      // Get Identify number of 
      // "bunch crossing","non-bunch crossing","displaced bunch crossing" 
      // if the quality of the bunch is bad (exp. too low intensity), return negative value.
      bunchtag = runinfo->GetBunchTag(a2cal1);

      // Event cut by Bunch Quality.
      if(bunchtag<0){continue;}
      
      // Select Bunch-Crossing events 
      if(bunchtag==LHCfRunInfo::COLLIDING){
	count_bc++;	
      }
      // Select Non Bunch Crossing events 
      else if(bunchtag==LHCfRunInfo::NONCOLLIDING){
	count_non++;
      }
      // Select Displaced Bunch Crossing events
      else if(bunchtag==LHCfRunInfo::DISPLACED){
	count_dis++;
      }
      else{
	cerr << "No information of this bunch in the LHCfRunInfoTabke" << endl;
      }
    }  
    
  }
   
  // ++++++++++++ PRINT INFORMATION ++++++++++++++
  cout << endl
       << "BUNCH CROSSING           :   " << count_bc << endl
       << "NON-BUNCH CROSSING       :   " << count_non << endl
       << "DISPLACED BUNCH CROSSING :   " << count_dis << endl
       << endl;

  return ;

}
