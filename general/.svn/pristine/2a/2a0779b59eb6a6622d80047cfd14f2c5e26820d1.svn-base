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
#include "GencolToSimIncidents.h"
using namespace std;

int main(int argc, char** argv){
  
  int  run = 16651;
  char infilename[256] = "gencol_run16651.out";
  char outfilename[256] = "";
  int nmax = 1000000;
  int    maxnp = 20;
  double cut_wz = 0.0;
  double cut_ke = 100.;
  int    iformat=0;

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
    if(strcmp(argv[i],"-maxnp")==0){
      maxnp = atoi(argv[++i]);
    }
    if(strcmp(argv[i],"-cutwz")==0){
       cut_wz = atof(argv[++i]);
    }
    if(strcmp(argv[i],"-cutke")==0){
       cut_ke = atof(argv[++i]);
    }
    if(strcmp(argv[i],"-format")==0){
      if(strcmp(argv[i+1],"gencol")==0 || atoi(argv[i+1])==0){
	iformat=0;
      }
      else if(strcmp(argv[i+1],"primary")==0 || atoi(argv[i+1])==1){
	iformat=1;
      }
      i++;
    }
    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-help")==0 ||
       argc==1){
      cout << endl;
      cout << "gencolbuild ----------------------------------------------\n"
           << " Convert Output of Gencol to ROOT File, that include a TTree \n"
	   << " with LHCfEvent. Data of each event are filled in SimIncidents.\n"
           << " ver1.0: 14,Nov.,2008 by H.MENJO \n"
	   << " ver1.1: 24,Jan.,2009 by H.MENJO \n"
	   << "         Add a input format parameter to read DoubleArm primary files.\n"
           << "Command)\n "
           << " ./gencolbuild -run #run -i input -o output \n"
	   << "    [-nmax 100000] [-maxnp 20] [-cutwz 0.] [-cutke 100.] [-format 0]\n";
      cout << "Option)\n" 
	   << " -i      :  Input File (Gencol)\n"
           << " -o      :  Output File Name (***.root)\n"
           << " -nmax   :  Maximum Number of Event [default 1000000]\n"
	   << " -maxnp  :  Maximum Number of particles in each event [default 20]\n"
           << " -cutke  :  [GeV] Threshold of Kinetic Energy [default 100GeV]\n"
	   << " -cutwz  :  Threshold of z-axis component of direction vector(wz)\n" 
	   << "            [default:0.0]\n"
	   << " -format :  0 or genecol:for genecol output\n"
	   << "            1 or primary:for doublearm +primary [default:0]\n" ;
      cout << endl;
      return 0;
    }
  }

  if(run==0){
    cerr << "Error: Give a run number " << endl;
    return -1;
  }
  if(strcmp(outfilename,"")==0){
    sprintf(outfilename,"gencol_run%05d.root",run);
  }

  GencolToSimIncidents* ftos = new GencolToSimIncidents();
  ftos->SetMaxParticles(maxnp);
  ftos->SetCutWz(cut_wz);
  ftos->SetCutKE(cut_ke);
  ftos->SetInputFormat(iformat);

  if(ftos->FileOpen(infilename)!=0){
    cerr << "Cannot open " << infilename << endl;
    return -1;
  }
  
  TFile *ofile = new TFile(outfilename,"RECREATE");
  LHCfEvent *ev = new LHCfEvent("event","DoubleArm");
  TTree* tree = new TTree("LHCfEvents","Tree of LHCfEvent");
  tree->Branch("ev.","LHCfEvent",&ev);

  SimIncidents* gencol = new SimIncidents("gencol","Gencol");
  
  int gnumber  = 0;

  while(1){
    if(ftos->Next(gencol) == -1){break;}
    
    // LHCfEvnet Header
    ev->Clear();
    ev->run = run;
    ev->gnumber = gnumber+1;
    ev->a1number = ev->gnumber;
    ev->a2number = ev->gnumber; 
    ev->ifile = run*100 + 0;
    ev->tnumber = gnumber;
    ev->tag += 0x00000000;

    gencol->run = run;
    gencol->gnumber = gnumber+1;
    gencol->number = gencol->gnumber;
    ev->Add(gencol);
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
