#include <TROOT.h>
#include <TApplication.h>
#include <TGWindow.h>
#include <TGClient.h>
#include <TGFrame.h>

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cmath>

#include "gsetup.h"
#include "LHCfParamFiles.h"
#include "FrameEventView.h"
using namespace std;

int main(int argc, char **argv){
  int tmp=1;
  TApplication theApp("App", &tmp, argv);
  
  char ifile[256]="";
  char pedefile[256]="";
  char configdir[256]="";

  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-i")==0){
      strcpy(ifile,argv[++i]);
    }
    if(strcmp(argv[i],"-pede")==0){
      strcpy(pedefile,argv[++i]);
    }
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-help")==0){
      cout << " ------------------------ LHCf Event Viewer ---------------------------\n"
	   << "  v2.0 : Modified by H.MENJO at 15 Feb 2010"
	   << "\n"
	   << " Command)\n"
	   << "  ./eventview [-i file] [-pede file]\n"
	   << " Options)\n"
	   << "  -i    :  Input File \n"
	   << "  -pede :  Pedestal File for pedestal subtraction\n"
	   << " GUI)\n"
	   << "  [Next]     : Go to next event.\n"
	   << "  [Previous] : Go to previous event.\n"
	   << "  [Go]       : Go to the event filled in the command window.\n"
	   << "  [Search Arm1]  : If ON, Search Arm1 Event\n"
	   << "  [Search Arm2]  : If ON, Search Arm2 Event\n"
	   << "  [Pedestal Subtraction] : If you give a pedestal file by -pede option\n"
	   << "                           Create the histograms with pedestal subtraction\n"
	   << "  [Tool]  : Show a tool bar.\n"
	   << "  [Print] : Print the selected canvas \n"
	   << "            as a name filled in the command window.\n "
	   << " Comment)\n"
	   << "  -To make a pedestal file, -pede option of adchists_arm* is available.\n"
	   << "  -If you want to fix the range of Y axis, you should use [SetRangeUser].\n"
	   << "   It can be found in the list which appear by right-click on each Y-axis.\n"
	   << "  -On the pedestal subtraction mode, histogram[normal] of calorimeters \n"
	   << "   are made by [normal-delayed] event by event, and [delayed] are made by\n"
	   << "   [delayed-pedestal(fixed)]. the other histograms are done \n"
           << "   by [value-pedestal(fixed)]\n"
	   << endl;
      return 0;
    }
  }
  
  if(argc==2 && strcmp(ifile,"")==0 && strstr(argv[1],"root") ){
    strcpy(ifile,argv[1]);
  }


#ifdef EVENTVIEWDIR
  char command[256];
  sprintf(configdir,"%s/.eventview",EVENTVIEWDIR);
  sprintf(command,"mkdir -p %s",configdir);
#else
  strcpy(configdir,"./.eventview");
#endif

  gsetup();
  FrameEventView *fMain = new FrameEventView(gClient->GetRoot(),980,900);
  fMain->SetConfigDir(configdir);
  fMain->MakeFrame();
  fMain->Initialize();
  
  if(strcmp(ifile,"")==0){
    cout << "Give data file from [File->Open Data File]" << endl;
  }
  else{
    fMain->OpenFile(ifile);
  }
  
  if(strcmp(pedefile,"")!=0){
    fMain->ReadPedeFile(pedefile);
  }

  theApp.Run();
  return 0;
}


