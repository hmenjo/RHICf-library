/************************************************************************\

            The simplest code for touching raw data of RHICf  

                  Class References can be found in 
  http://lhcfs1.stelab.nagoya-u.ac.jp/analysis/ClassIndex/ClassIndex.html

\************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
#include <cmath>
#include <cstring>
#include <cstdio>
#include <TROOT.h>
#include <TRint.h>
#include <TApplication.h>

#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <LHCfEvent.h>
#include <RHICfRaw_Op2017.h>
#include <RHICfScl_Op2017.h>
#include <RHICfRunInfoTable.h>
#include <TStyle.h>
#include <TLatex.h>
// typedef just for simplicity 
typedef LHCfEvent        RHICfEvent;
typedef RHICfRaw_Op2017  RHICfRaw;
typedef RHICfScl_Op2017  RHICfScl;


void printhelp(){
  cout << "./sample_eventloop -i inputfile -run runnumber -info runinfofile" << endl;
}

/////////////////////////////////////////////////////////////////////
//                              MAIN 
/////////////////////////////////////////////////////////////////////
int main(int argc,char **argv){

  vector<string> inputfiles;
  vector<string> runinfofiles;
  string         outputfile = "";
  char runinfofile[256] ="";
  int run=-1;
  for(int i=1;i<argc;i++){
	 string ss = argv[i];
	 if(strcmp(argv[i], "-info")==0){
	   strcpy(runinfofile,argv[i++]);
	   strcpy(argv[i],"");
	 }
	 if(strcmp(argv[i], "-run")==0){
	   run = atoi(argv[++i]);
	 }
	 
	 if(ss=="-h" || ss=="--help"){
		printhelp();
		return -1;
	 }
  }

 
  cerr << " kokomade " << endl;
  

//TApplication app("sample",&argc,argv);
  

  // +++++++++++++++++++ Define histogram +++++++++++++++++++++++
 

  double buf1,buf2,buf3, buf4;

  double fmean[34];
  double fsigma[34];

  //if ( !fin ) continue;

  // for(int i=0;i<tablefiles.size();i++){ 
  //   ifstream fin(tablefiles[i].c_str());
  // }
  RHICfRunInfo* info = NULL;
  RHICfRunInfoTable *infotable = new RHICfRunInfoTable();
  if( infotable->ReadTable(runinfofile) == OK){ 
    if(infotable->GetRunInfo(run)){
      info = infotable->GetRunInfo(run);
      cerr << "kokomade" << endl;
    }
  }
  // else{
  //   cerr << "Cannnot open" << runinfofiles << endl;
  //   exit(-1);
  // }

  // ++++++++++++++++++++++ EVENT LOOP ++++++++++++++++++++++++++
 
 
  cerr << endl;

  
  //app.Run();
  return 0;
}
