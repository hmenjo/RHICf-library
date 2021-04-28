#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <TTree.h>
#include <TFile.h> 
#include "SimP.h"
#include "SimIncidents.h"
#include "LHCfEvent.h"
#include "FileToSimIncidents.h"
#include "A1Cal1AccumHist.h"
using namespace std;

int main(int argc,char** argv){
  
  int run = 0;
  char a1filename[256] = "";
  char ofilename[256] = "";
  int nmax = 100000;
  double cut_ke=20.0;
  double cut_x =5.0;
  double cut_y =5.0;
  
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-run")==0){
      run = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-a1")==0){
      strcpy(a1filename,argv[++i]);
    }
    if(strcmp(argv[i],"-o")==0){
      strcpy(ofilename,argv[++i]);
    } 
    if(strcmp(argv[i],"-nmax")==0){
      nmax = atoi(argv[++i]);
    }  
    if(strcmp(argv[i],"-cutke")==0){
       cut_ke = atof(argv[++i]);
    }  
    if(strcmp(argv[i],"-cutx")==0){
       cut_x = atof(argv[++i]);
    }      
    if(strcmp(argv[i],"-cuty")==0){
       cut_y = atof(argv[++i]);
    }  
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-help")==0 ||
       argc==1){
      cout << "simbuild_arm1 ------------------------------------------------\n"
	   << " convert ascii output of simulation to root file.\n"
	   << " ver1.0 : can convert only arm1 data.\n"
	   << "Command)\n"
	   << " ./simbuild -run #run [-i file] [-o filename] [-nmax 100000]\n"
	   << "            [-cutke 20.0] [-cutx 5.0] [-cuty 5.0]\n"        
	   << "Option)\n"
	   << "   -run    :  Run Number\n"
	   << "   -a1     :  Input file for Arm#1 [default end2end_run(#run).out]\n"
	   << "   -o      :  Output file [default srun(#run).out]\n"
	   << "   -nmax   :  Maximum Number of Event [default 100000]\n"
	   << "   -cutke  :  [GeV] Threshold Kinetic Energy [default 20GeV]\n"
	   << "   -cutx   :  [cm] Postion X Cut for SimP [default 5.0cm]\n"
	   << "   -cuty   :  [cm] Postion Y Cut for SimP [default 5.0cm]\n"
	   << endl;
      return 0;
    }
  }
  
  if(run==0){
    cerr << "Error: Give a run number " << endl;
    return 0;
  }
  if(strcmp(a1filename,"")==0){
    sprintf(a1filename,"end2end_run%05d.out",run);
  }
  if(strcmp(ofilename,"")==0){
    sprintf(ofilename,"srun%05d.root",run);
  }
  
  int a1number = 0; 
  int a2number = 0;
  int gnumber  = 0; 

  FileToSimIncidents* a1ftos = new FileToSimIncidents(1,a1filename);
  a1ftos->SetCutKE(cut_ke);
  a1ftos->SetCutPosX(cut_x);
  a1ftos->SetCutPosY(cut_y);
  a1ftos->SetDetector(1);
  if(a1ftos->FileOpen(a1filename)<0){
    return -1;
  }
  
  TFile *ofile = new TFile(ofilename,"RECREATE");
  LHCfEvent *ev = new LHCfEvent("event","LHCf Event 2008");
  TTree* tree = new TTree("LHCfEvents","Tree of LHCfEvent");
  tree->Branch("ev.","LHCfEvent",&ev);

  A1Cal2 *a1sim = new A1Cal2("a1sim","Simulation");
  SimIncidents* a1simin = new SimIncidents("a1simin","Arm#1 Incident");
  a1sim->clear();

  int i=0;
  while(1){
    if( a1ftos->Next(a1sim,a1simin) !=0 ){
      break;
    } 
    else{  
      ev->Clear();
      ev->run = run;
      ev->gnumber = gnumber+1;
      ev->a1number = a1number+1;
      ev->a1flag[0] = 0x1013;
      ev->a1flag[1] = 0x0;
      ev->a2flag[0] = 0x0;
      ev->a2flag[1] = 0x0;
      ev->ifile = run*100 + 0;
      ev->tnumber = gnumber;
      
      a1sim->run = run;
      a1sim->number =  a1number+1;
      a1sim->gnumber = gnumber+1;

      a1simin->run = run;
      a1simin->number = a1number+1;
      a1simin->gnumber = gnumber+1;

      ev->tag += 0x01000000;
      ev->tag += 0x02000000;
      
      ev->Add(a1sim);
      ev->Add(a1simin);
      tree->Fill();
      
      a1number++;
      gnumber++;
      cout << "Number: " << gnumber << "   " << a1ftos->np << endl;
      
    }
    if(i>=nmax){break;}
  }
  
  cout << "ARM1:    " << a1filename << endl
       << "OUTPUT:  " << ofilename << endl;
  
  cout << "RUN      " << setw(6) << run << endl
       << "GNUMBER  " << setw(6) << gnumber << endl
       << "A1NUMBER " << setw(6) << a1number << endl;
  
  tree->Write("",TObject::kOverwrite);
  ofile->Close();
  return 0;
}
