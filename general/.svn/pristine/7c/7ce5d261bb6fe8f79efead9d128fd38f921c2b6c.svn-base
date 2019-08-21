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
using namespace std;

int main(int argc,char** argv){
  
  int run = 0;
  char a1filename[256] = "";
  char a2filename[256] = "";
  bool check_a1=false;
  bool check_a2=false;
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
      check_a1 = true;
    }
    if(strcmp(argv[i],"-a2")==0){
      strcpy(a2filename,argv[++i]);  
      check_a2 = true;
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
      cout << "simbuild ------------------------------------------------\n"
	   << " convert ascii output of simulation to root file.\n"
	   << " ver2.0 : can convert arm1 and arm2 data.\n"
	   << "Command)\n"
	   << " ./simbuild -run #run [-a1 file] [-a2 file] [-o filename] \n"
	   << "      [-nmax 100000] [-cutke 20.0] [-cutx 5.0] [-cuty 5.0]\n"        
	   << "Option)\n"
	   << "   -run    :  Run Number\n"
	   << "   -a1     :  Input file for Arm#1\n"
	   << "   -a2     :  Input file for Arm#2\n"
	   << "   -o      :  Output file [default srun(#run).out]\n"
	   << "   -nmax   :  Maximum Number of Event [default 100000]\n"
	   << "   -cutke  :  [GeV] Threshold of Kinetic Energy for SimP [default 20GeV]\n"
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
  if(strcmp(ofilename,"")==0){
    sprintf(ofilename,"srun%05d.root",run);
  }

  FileToSimIncidents* a1ftos = new FileToSimIncidents();
  a1ftos->SetCutKE(cut_ke);
  a1ftos->SetCutPosX(cut_x);
  a1ftos->SetCutPosY(cut_y);
  a1ftos->SetDetector(1);
  if(check_a1==true && a1ftos->FileOpen(a1filename)<0){
    check_a1 = false;
  }

  FileToSimIncidents* a2ftos = new FileToSimIncidents();
  a2ftos->SetCutKE(cut_ke);
  a2ftos->SetCutPosX(cut_x);
  a2ftos->SetCutPosY(cut_y);
  a2ftos->SetDetector(2);
  if(check_a2==true && a2ftos->FileOpen(a2filename)<0){
    check_a2 = false;
  }
  
  TFile *ofile = new TFile(ofilename,"RECREATE");
  LHCfEvent *ev = new LHCfEvent("event","LHCf Event 2008");
  TTree* tree = new TTree("LHCfEvents","Tree of LHCfEvent");
  tree->Branch("ev.","LHCfEvent",&ev);

  A1Cal2 *a1sim = new A1Cal2("a1sim","Arm1 Simulation");
  SimIncidents* a1simin = new SimIncidents("a1simin","Arm#1 Incident");
  a1sim->clear();
  
  A2Cal2 *a2sim = new A2Cal2("a2sim","Arm2 Simulation");
  SimIncidents* a2simin = new SimIncidents("a2simin","Arm#2 Incident");
  a2sim->clear();

  int check_a1ev=-1;
  int check_a2ev=-1;
  int a1number = 0; 
  int a2number = 0;
  int gnumber  = 0; 
  while(1){
    if(check_a1==true){ check_a1ev = a1ftos->Next(a1sim,a1simin);}
    if(check_a2==true){ check_a2ev = a2ftos->Next(a2sim,a2simin);}
    if(check_a1ev!=0 && check_a2ev!=0){break;}

    // LHCfEvnet Header
    ev->Clear();
    ev->run = run;
    ev->gnumber = gnumber+1; 
    ev->ifile = run*100 + 0;
    ev->tnumber = gnumber;

    if(check_a1==true && check_a1ev==0){
      ev->a1number = a1number+1; 
      ev->a1flag[0] = 0x1013; 
      ev->a1flag[1] = 0;
      ev->tag += 0x01000000;
      ev->tag += 0x02000000; 
      a1sim->run = run;
      a1sim->number =  a1number+1;
      a1sim->gnumber = gnumber+1;
      a1simin->run = run;
      a1simin->number = a1number+1;
      a1simin->gnumber = gnumber+1;  
      if(check_a2==true && check_a2ev==0){
	for(int i=0;i<4;i++){
	  a1sim->fc[1][i] = a2sim->fc[1][i];
	}
      }
      ev->Add(a1sim);
      ev->Add(a1simin); 
      a1number++;
    }
    else{
      ev->a1number = 0;   
      ev->a1flag[0] = 0;
      ev->a1flag[1] = 0;
    }

    if(check_a2==true && check_a2ev==0){
      ev->a2number = a2number+1; 
      ev->a2flag[0] = 0x1013; 
      ev->a2flag[1] = 0;
      ev->tag += 0x10000000;
      ev->tag += 0x20000000; 
      a2sim->run = run;
      a2sim->number =  a2number+1;
      a2sim->gnumber = gnumber+1;
      a2simin->run = run;
      a2simin->number = a2number+1;
      a2simin->gnumber = gnumber+1; 
      if(check_a1==true && check_a1ev==0){
	for(int i=0;i<4;i++){
	  a2sim->fc[0][i] = a1sim->fc[0][i];
	}
      }
      ev->Add(a2sim);
      ev->Add(a2simin);
      a2number++;
    }
    else{
      ev->a2number = 0;   
      ev->a2flag[0] = 0;
      ev->a2flag[1] = 0;
    }
    
    tree->Fill();
    gnumber++;
    //cout << "Number: " << gnumber << "   " << a1ftos->np << endl;
    if(gnumber%100==0) cerr << '*';
    if(gnumber%2000==0) cerr << " " << gnumber << endl;
    if(gnumber>=nmax){break;}
  }
  cerr << endl;
  
  cout << "ARM1:    " << a1filename << endl
       << "ARM2:    " << a2filename << endl
       << "OUTPUT:  " << ofilename << endl;
  
  cout << "RUN      " << setw(6) << run << endl
       << "GNUMBER  " << setw(6) << gnumber << endl
       << "A1NUMBER " << setw(6) << a1number << endl
       << "A2NUMBER " << setw(6) << a2number << endl;

  tree->Write("",TObject::kOverwrite);
  ofile->Close();
  return 0;
}
