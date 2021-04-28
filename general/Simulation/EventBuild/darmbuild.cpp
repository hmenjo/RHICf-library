#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#if defined(__CINT__)
#include "../../dict/lib/libLHCfEvent.so"
#else
#include "../../dict/include/LHCfEvent.h"
#include "../../dict/include/SimIncidents.h"
#endif
#include "DarmToSimIncidents.h"
using namespace std;


int main(int argc, char** argv){

  int  run = 100; 
  char infilename[256] = "darm_run13551.out";
  char outfilename[256] = "";
  int nmax = 1000000;
  double offset_a1x=-1.6;
  double offset_a2x=-0.6;
  double cut_ke=20.0;
  double cut_x =50.0;
  double cut_y =50.0;
  bool cut_bp = true;
  bool cut_wall = true;
  
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-run")==0){
      run = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-i")==0){
      strcpy(infilename,argv[++i]);
    } 
    if(strcmp(argv[i],"-o")==0){
      strcpy(outfilename,argv[++i]);
    }  
    if(strcmp(argv[i],"-nmax")==0){
      nmax = atoi(argv[++i]);
    }  
    if(strcmp(argv[i],"-offset_a1x")==0){
       offset_a1x = atof(argv[++i]);
    }  
    if(strcmp(argv[i],"-offset_a2x")==0){
       offset_a2x = atof(argv[++i]);
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
    if(strcmp(argv[i],"-Cutbp")==0 || strcmp(argv[i],"-wCutbp")==0){
      cut_bp = true;
    }
    if(strcmp(argv[i],"-woCutbp")==0){
      cut_bp = false;
    }
    if(strcmp(argv[i],"-Cutwall")==0 || strcmp(argv[i],"-wCutwall")==0){
      cut_wall = true;
    }
    if(strcmp(argv[i],"-woCutwall")==0){
      cut_wall = false;
    } 
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-help")==0 ||
       argc==1){
      cout << endl;
      cout << "darmbuild ----------------------------------------------\n"
	   << " Convert Output of DoubleArm to ROOT File.\n"
	   << " ver1.0: 12,Nov.,2008 by H.MENJO \n"
	   << "Command)\n "
	   << " ./darmbuild -run #run -i input -o output \n"
	   << "   [-nmax 1000000] [-cutx 50.] [-cuty 50.] [-offset_a1x -1.6] [-offset_a2x -0.6]\n"
	   << "   [-wCutbp/-woCutbp] [-wCutwall/-woCutwall] \n";
      cout << "Option)\n "
	   << " -run    :  Run Number\n"
	   << " -i      :  Input File (DoubleArm)\n"
	   << " -o      :  Output File Name (***.root)\n"
	   << " -nmax   :  Maximum Number of Event [default 1000000]\n"
	   << " -cutke  :  [GeV] Threshold of Kinetic Energy [default 20GeV]\n"
	   << " -cutx   :  [mm] Postion X Cut [default 50mm]\n"
	   << " -cutx   :  [mm] Postion X Cut [default 50mm]\n"
	   << " -wCutbp/-woCutbp: With/Without event cut of \n" 
	   << "            the elliptic beam pipe [default -wCutbp]\n"
	   << " -wCutwall/-woCutwall: With/Without event cut of TAN wall\n"
	   << "            |x| < 4.6cm [default -wCutwall]\n"
	   << " -offset_a1x: [mm] Offset of TAN(arm1 detector) position [default -1.6mm]\n"
	   << " -offset_a2x: [mm] Offset of TAN(arm2 detector) position [default -0.6mm]\n"
	   << endl;
      return 0;
    }
  }
  
  if(run==0){
    cerr << "Error: Give a run number " << endl;
    return -1;
  }

  if(strcmp(outfilename,"")==0){
    sprintf(outfilename,"darm_run%05d.root",run);
  }
  
  DarmToSimIncidents* ftos = new DarmToSimIncidents();
  ftos->SetOffset_A1x(offset_a1x);
  ftos->SetOffset_A2x(offset_a2x);
  ftos->SetCutPosX(cut_x);
  ftos->SetCutPosY(cut_y);
  ftos->SetCutKE(cut_ke);
  ftos->SetCutBeampipe(cut_bp);
  ftos->SetCutTANWall(cut_wall);
  
  if(ftos->FileOpen(infilename)!=0){
    cerr << "Cannot open " << infilename << endl;
    return -1;
  }
  
  TFile *ofile = new TFile(outfilename,"RECREATE");
  LHCfEvent *ev = new LHCfEvent("event","DoubleArm");
  TTree* tree = new TTree("LHCfEvents","Tree of LHCfEvent");
  tree->Branch("ev.","LHCfEvent",&ev);
  
  SimIncidents* a1simin = new SimIncidents("a1simin","Arm#1");
  SimIncidents* a2simin = new SimIncidents("a2simin","Arm#2");

  int gnumber  = 0;
  while(1){
    if(ftos->Next(a1simin,a2simin) == -1){break;}
    
    // LHCfEvnet Header
    ev->Clear();
    ev->run = run;
    ev->gnumber = gnumber+1;
    ev->ifile = run*100 + 0;
    ev->tnumber = gnumber;
    ev->tag += 0x22000000;

    ev->a1number = gnumber+1;
    a1simin->run = run;
    a1simin->gnumber = gnumber+1;
    a1simin->number = ev->a1number;

    ev->a2number = gnumber+1; 
    a2simin->run = run;
    a2simin->gnumber = gnumber+1;
    a2simin->number = ev->a2number;
    
    ev->Add(a1simin);
    ev->Add(a2simin);
    tree->Fill();
    gnumber++; 
    
    if(gnumber%100==0) cerr << '*';
    if(gnumber%2000==0) cerr << " " << gnumber << endl;
    if(gnumber>=nmax){break;}
  }
  cerr << endl;
  
  cout << "INPUT:   " << infilename << endl
       << "OUTPUT:  " << outfilename << endl;

  cout << "RUN      " << setw(6) << run << endl
       << "GNUMBER  " << setw(6) << gnumber << endl;
      
  ev->Clear();
  tree->Write("",TObject::kOverwrite);
  ofile->Close();

  return 0;
}
