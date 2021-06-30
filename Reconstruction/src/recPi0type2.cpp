#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TDatime.h>
#include <TVector3.h>

#include <LHCfEvent.h>
#include <LHCfEvent.h>
#include <RHICfRaw_Op2017.h>
#include <A1Cal1.h>
#include <A1Cal2M.h>

#include <RHICfRec0.h>
#include <RHICfRec1.h>
#include <RHICfPhys.h>
#include <RHICfSimIncidents.h>

#include <A1Reconstruction.h>

class Pi0Type2 {
public:
  int    tower;
  double energy[2];
  double pos[2][2]; // hit, view

  double mgg;
  double pi0energy;

public:
  Pi0Type2(){
    Clear();
  }
  void Clear(){
    tower = 1;
    energy[0] = 0.;
    energy[1] = 0.;
    pos[0][0] = 0.;
    pos[0][1] = 0.;
    pos[1][0] = 0.;
    pos[1][1] = 0.;
    mgg = 0.;
    pi0energy = 0.;
  }
  int  Calculate();
  bool InFiducial();
  void Print();
};

int RecType2Pi0_Minho(RHICfPhys* phys, RHICfRec* rec, Pi0Type2* result);

class ReconstructionPi0Type1 : public A1Reconstruction {
public:
  ReconstructionPi0Type1() : A1Reconstruction() {;}
public:
  int Calculate(A1Cal2M *cal2, RHICfRec* rec, Pi0Type2* result);
};

// ======================= MAIN =================================== //
int main(int argc, char **argv){

  TString runtype = "";
  TString ifilename = "";
  TString ofilename = "hist.root";

  for (int i=1; i<argc; i++){
    
    TString ss = argv[i];
    if(ss=="-r" || ss=="--runtype"){
      runtype = argv[++i];
      strcpy(argv[i], "");
    }
    if (ss == "-i" || ss == "--input") {
      ifilename = argv[++i];
      strcpy(argv[i], "");
    }
    if (ss == "-o" || ss == "--output") {
      ofilename = argv[++i];
      strcpy(argv[i], "");
    }
  }



  TRint theApp("App", &argc, argv, 0, 0, kTRUE);
  gROOT->SetBatch(kTRUE);
  
  // A1Reconstruction.
  ReconstructionPi0Type1 *reconstruction = new ReconstructionPi0Type1();
  reconstruction->SetRunType(runtype);
  reconstruction->Initialize();

  // Input.
  LHCfEvent *ev   = new LHCfEvent();
  TChain    *tree = new TChain("LHCfEvents");
  tree->AddFile(ifilename.Data());
  tree->SetBranchAddress("ev.", &ev);
  
  // Output.
  TFile     *ofile = new TFile(ofilename, "RECREATE");
  TH1D* h1mass = new TH1D("h1mass","mass",500,0.,500.);
  TH2D *h2emass = new TH2D("h2emass","Mass vs Energy",
			   30.,0.,300., 500, 0., 500.);
  gROOT->cd();

  // ======================================================================
  int nevmax = tree->GetEntriesFast();
  int nevent = 0;
  RHICfPhys* phys = new RHICfPhys();
  Pi0Type2*  pi0  = new Pi0Type2();
  // ====================== Start event loop. =========================== //
  for (int iev = 0; iev < nevmax; iev++){
    Int_t ievlocal = tree->LoadTree(iev);
    if (ievlocal < 0){ break; }
    
    if (iev && iev % 200 == 0) { cerr << '*'; }
    if (iev && iev % 5000 == 0) { cerr << iev << endl; }
    ev->Delete();
    tree->GetEntry(iev);
    nevent++;
    
    pi0->Clear();
    A1Cal2M*  cal2 = (A1Cal2M*) ev->Get("a1cal2");
    RHICfRec* rec  = (RHICfRec*) ev->Get("a1rec");

    rec->FillToPhys(phys);

    // Event selection
    RHICfSimIncidents* simin;
    RHICfSimP* pp[2] = {0};
    if(ev->Check("a1simin")){
      simin = (RHICfSimIncidents*) ev->Get("a1simin");
      if(simin->GetNHit(10,1,10.0,2.0) == 2){
	pp[0] = simin->GetRef(0);
	pp[1] = simin->GetRef(1);
	//simin->Show(10,1);
      }
    }
    
    int ret;
    // Minho's algorithm 
    //ret = RecType2Pi0_Minho(phys, rec, pi0);
    // New LHCf-like algorithm 
    ret = reconstruction->Calculate(cal2, rec, pi0);

    if(ret<0) continue;
    if(pi0->InFiducial() == false) continue;

    h1mass->Fill(pi0->mgg);
    h2emass->Fill(pi0->pi0energy, pi0->mgg);
    
    //pi0->Print();
    
    
  } // End of Event loop
  cerr << endl;
  cout << "NEVENT " << nevent << endl;

  // Write the histograms to file 
  ofile->cd();
  ofile->Write();
  ofile->Close();

  theApp.Run();
  return 0;

}

// =============================================================




int Pi0Type2::Calculate(){
  static RHICfPhys phystmp;
  // Position reconstruction.
  static const double rhicfz = RHICfPhys::cDistance;

  double x1,y1,r1,x2,y2,r2, r;
  phystmp.pos[tower][0] = pos[0][0];
  phystmp.pos[tower][1] = pos[0][1];
  x1 = phystmp.GlobalPos_BC(tower, 0);
  y1 = phystmp.GlobalPos_BC(tower, 1);
  r1 = sqrt(pow(x1,2) + pow(y1,2) + pow(rhicfz,2));
  
  phystmp.pos[tower][0] = pos[1][0];
  phystmp.pos[tower][1] = pos[1][1];
  x2 = phystmp.GlobalPos_BC(tower, 0);
  y2 = phystmp.GlobalPos_BC(tower, 1);
  r2 = sqrt(pow(x2,2) + pow(y2,2) + pow(rhicfz,2));

  r = sqrt(pow((pos[0][0]-pos[1][0]),2) + pow((pos[0][1]-pos[1][1]),2));
  
  
  // Energy 
  this->pi0energy = energy[0] + energy[1];
  
  // mass
  // E, pT, mgg reconstruction.
  TVector3 p1 = TVector3((x1/r1)*energy[0], (y1/r1)*energy[0], (rhicfz/r1)*energy[0]);
  TVector3 p2 = TVector3((x2/r2)*energy[1], (y2/r2)*energy[1], (rhicfz/r2)*energy[1]);
  TVector3 p = p1+p2;

  //this->mgg = 1000.*sqrt(pow(pi0energy,2)-pow(p.X(),2)-pow(p.Y(),2)-pow(p.Z(),2));
  
  this->mgg = 1000.* r/rhicfz * TMath::Sqrt(energy[0] * energy[1]);


  return 1;
}

bool Pi0Type2::InFiducial(){
  const double size = (tower==0? 20.:40.);
  for(int ih=0;ih<2;ih++){
    for(int iv=0;iv<2;iv++){
      if(TMath::Abs(pos[ih][iv] - size/2) > size/2.-2.)
	return false;
    }
  }
  return true;
}

void Pi0Type2::Print(){
  cout << fixed ;
  for(int i=0;i<2;i++){
    cout << "g" << i << " : " << setw(5) << setprecision(1) << energy[i] << "  " 
	 << setw(5) << setprecision(2) << pos[i][0] << "  " 
	 << setw(5) << setprecision(2) << pos[i][1] << endl;
  }
       
  cout << "mgg = " << mgg << endl;
}

int RecType2Pi0_Minho(RHICfPhys* phys, RHICfRec* rec, Pi0Type2* result){

  static const int tower = 1;
  bool NOoverlap;

  int maxlay = rec -> GetMaxBarLayer(tower);
  int maxlay2 = rec -> GetMaxBarLayer2(tower);
  
  double edepx[2] = {0};
  double edepy[2] = {0};
  
  for(int imu=0;imu<2;imu++){
    
    edepx[imu] += rec -> GetMHPeakEstimated(tower, maxlay, 0, imu);
    edepx[imu] += rec -> GetMHPeakEstimated(tower, maxlay2, 0, imu);
    edepy[imu] += rec -> GetMHPeakEstimated(tower, maxlay, 1, imu);
    edepy[imu] += rec -> GetMHPeakEstimated(tower, maxlay2, 1, imu);
  }
  
  int xnum1 = TMath::LocMax(2, edepx);// "X imu" of higher peak sum.
  int xnum2 = TMath::LocMin(2, edepx);// Lower one.
  int ynum1 = TMath::LocMax(2, edepy);// "Y imu" of higher peak sum.
  int ynum2 = TMath::LocMin(2, edepy);// Lower one.
  
  double a1 = rec -> GetMHPosition(tower, maxlay, 0, xnum1);// Xbar # with higher peak sum.
  double a2 = rec -> GetMHPosition(tower, maxlay, 0, xnum2);// Lower one.
  double b1 = rec -> GetMHPosition(tower, maxlay, 1, ynum1);// Ybar # with higher peak sum.
  double b2 = rec -> GetMHPosition(tower, maxlay, 1, ynum2);// Lower one.
  
  double xpeak1 = rec -> GetMHPeakEstimated(tower, maxlay, 0, xnum1);
  double ypeak1 = rec -> GetMHPeakEstimated(tower, maxlay, 1, ynum1);
  double xpeak2 = rec -> GetMHPeakEstimated(tower, maxlay, 0, xnum2);
  double ypeak2 = rec -> GetMHPeakEstimated(tower, maxlay, 1, ynum2);

  double chi2x = rec -> GetChiSquare(tower, maxlay, 0, 1);
  double chi2y = rec -> GetChiSquare(tower, maxlay, 1, 1);
  
  // overlap, non-overlap.
  NOoverlap = false;
  
  //h1_pos[0] -> Fill(a1-a2);
  //h1_pos[1] -> Fill(b1-b2);
  
  double pratio, qratio;
  if(a1!=a2 && b1!=b2){
    
    NOoverlap = true;
    
    pratio = edepx[xnum1] + edepy[ynum1];
    qratio = edepx[xnum2] + edepy[ynum2];
  }
  else{
    return -1;
  }

  // cout << pratio << " " << qratio << endl;

  pratio = pratio/(pratio+qratio);
  qratio = 1 - pratio;
  
  // Each energy 
  double E = phys->Energy(tower);
  double E1 = E*pratio;
  double E2 = E*qratio;

  result->tower = tower;

  result->energy[0] = E1;
  result->energy[1] = E2;
  
  result->pos[0][0] = a1;
  result->pos[0][1] = b1;
  result->pos[1][0] = a2;
  result->pos[1][1] = b2;  

  result->Calculate();
  
  return 0;

}

int ReconstructionPi0Type1::Calculate(A1Cal2M *cal2, RHICfRec* rec, Pi0Type2* result){
  int tower = 1;
  
  // Require 2 hit in 1st and 2nd layers 
  if(rec->GetNumberOfHits(tower, 0, 0) != 2 || rec->GetNumberOfHits(tower, 0, 1) !=2 || 
     rec->GetNumberOfHits(tower, 1, 0) != 2 || rec->GetNumberOfHits(tower, 1, 1) !=2) {
    return -1;
  } 

  // ++ Hit pos matching ++
  // Fill data
  double tmp_pos[2][2][2]; // layer, xy, hit;
  double tmp_edep[2][2][2]; // layer, xy, hit;
  int overlap = false;
  for(int il=0;il<2;il++){
    for(int iv=0;iv<2;iv++){
      double tmp[2];
      tmp[0] = rec -> GetMHPeakEstimated(tower, il, iv, 0);
      tmp[1] = rec -> GetMHPeakEstimated(tower, il, iv, 1);
      //cout << il << " " << iv << " " << tmp[0] << " " << tmp[1] << endl;
      //cout << rec->GetMHPar(1,il,iv,0,0) << "  " << rec->GetMHPar(1,il,iv,1,0) << endl; 
      int imax = TMath::LocMax(2, tmp);
      int imin = TMath::LocMin(2, tmp);
      tmp_edep[il][iv][0] = tmp[imax];
      tmp_edep[il][iv][1] = tmp[imin];
      tmp_pos[il][iv][0] = rec->GetMHPosition(tower, il, iv, imax);
      tmp_pos[il][iv][1] = rec->GetMHPosition(tower, il, iv, imin);
      if(TMath::Abs(tmp_pos[il][iv][0] -  tmp_pos[il][iv][1]) < 2.) overlap = true;
    }
  }
  if(overlap){
    return -2;
  }
  
  // Matching in layer 1 and layer 2
  int maxlay = rec -> GetMaxBarLayer(tower);
  int nexlay = (maxlay==1?0:1);
  double pos[2][2][2]; // layer xy hit
  double edep[2][2][2];  // layer xy hit
  // believe maxlay
  for(int iv=0;iv<2;iv++){
    pos[maxlay][iv][0] = tmp_pos[maxlay][iv][0];
    pos[maxlay][iv][1] = tmp_pos[maxlay][iv][1];
    edep[maxlay][iv][0] = tmp_edep[maxlay][iv][0];
    edep[maxlay][iv][1] = tmp_edep[maxlay][iv][1];  
  }
  // matching 2nd layer 
  bool match = false;
  for(int iv=0;iv<2;iv++){
    if(TMath::Abs(tmp_pos[nexlay][iv][0] - pos[maxlay][iv][0]) < 1. && 
       TMath::Abs(tmp_pos[nexlay][iv][1] - pos[maxlay][iv][1]) < 1.  ){
      pos[nexlay][iv][0] = tmp_pos[nexlay][iv][0];
      pos[nexlay][iv][1] = tmp_pos[nexlay][iv][1];
      edep[nexlay][iv][0] = tmp_edep[nexlay][iv][0];
      edep[nexlay][iv][1] = tmp_edep[nexlay][iv][1];  
      match = true;
    }
    else if(TMath::Abs(tmp_pos[nexlay][iv][0] - pos[maxlay][iv][1]) < 1. && 
	    TMath::Abs(tmp_pos[nexlay][iv][1] - pos[maxlay][iv][0]) < 1. ){
      pos[nexlay][iv][0] = tmp_pos[nexlay][iv][1];
      pos[nexlay][iv][1] = tmp_pos[nexlay][iv][0];
      edep[nexlay][iv][0] = tmp_edep[nexlay][iv][1];
      edep[nexlay][iv][1] = tmp_edep[nexlay][iv][0];  
      match = true;
    }
  }

  // Final Position (take 1st layer result)
  double posf[2][2]; // xy, hit
  posf[0][0] = pos[0][0][0]; // x;
  posf[1][0] = pos[0][1][0]; // x;
  posf[0][1] = pos[0][0][1]; // x;
  posf[1][1] = pos[0][1][1]; // x;

  if(match == false) {
    return -3;
  }
  

  // Energy Reconstruction 
  // Estimate the fraction factors 
  double p[2], q[2];
  for(int il=0;il<2;il++){
    double total = edep[il][0][0]+edep[il][1][0] + edep[il][0][1]+edep[il][1][1];
    p[il] = (edep[il][0][0]+edep[il][0][0])/total;
    q[il] = 1 - p[il];
  }

  // Shower and Light yield correction
  double dE[2][16]; // hit, layer
  for(int i=0;i<16;i++){
    double c[2], tmpp, tmpq;
    c[0] = 1./fPosdep->GetEfficiency(1, tower, i, posf[0][0], posf[1][0]);
    c[1] = 1./fPosdep->GetEfficiency(1, tower, i, posf[0][1], posf[1][1]);
    
    if(i<=3){
      tmpp = p[0];
      tmpq = q[0];
    }
    else{
      tmpp = p[1];
      tmpq = q[1];      
    }
    dE[0][i]  = cal2->cal[tower][i];
    dE[0][i] *= (c[0]*c[1]*tmpp)/(c[0]*tmpq+c[1]*tmpp);
    dE[1][i]  = cal2->cal[tower][i];
    dE[1][i] *= (c[0]*c[1]*tmpq)/(c[0]*tmpq+c[1]*tmpp);
    //cout << (c[0]*c[1]*tmpp)/(c[0]*tmpq+c[1]*tmpp) << " " << (c[0]*c[1]*tmpq)/(c[0]*tmpq+c[1]*tmpp) << endl;
  }

  // Calculate energy
  double energy[2];
  for(int ih=0;ih<2;ih++){
    double sum = 0.;
    for(int i=1;i<=11;i++){
      sum += dE[ih][i];
    }
    energy[ih] = EnergyConversionPhoton(tower, sum);
  }
 
  
  result->tower = tower;

  result->energy[0] = energy[0];
  result->energy[1] = energy[1];  
  
  result->pos[0][0] = posf[0][0];
  result->pos[0][1] = posf[1][0];
  result->pos[1][0] = posf[0][1];
  result->pos[1][1] = posf[1][1];  

  result->Calculate();

  return 0;
}
