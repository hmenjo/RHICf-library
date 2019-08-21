#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include "RHICfSimEvent.hpp"
#include "A1Cal2.h"
#include "A1Cal2M.h"
#include "RHICfSimEvent.hpp"
#include "RHICfBBC.h"
#include "RHICfZDC.h"
#include "LHCfEvent.h"
#include "RunInfo.hpp"
#include "BBCContainer.hpp"
#include "ZDCContainer.hpp"
#include "MCDataContainer.hpp"
#include "RHICfSimP.h"
#include "RHICfSimIncidents.h"
#include "TDatabasePDG.h"
#include "RHICfFlag.h"

const double rhicf_posz=17799.7; /// position of the 1st tungsten

typedef LHCfEvent RHICfEvent;
using namespace std;

// For Help ---------------------------------------------------------
void printhelp(){
    
  //cout << "-i inputfilename -o outputfilename" << endl;
  return ;
}


TVector3 GetProjection(TVector3 pos, TLorentzVector mom, double z)
{
  double k=(z-pos.z())/mom.Vect().z();
  //cout << z << " " << pos.z() << endl;
  return pos+mom.Vect()*k;
}

vector<Forward*> SameIntermediates(vector<Forward*> forward, int ipart)
{
  vector<Forward*> intermediate;
  intermediate.clear();
  
  if(forward[ipart]->GetIntermediate()!=NULL) {
	 Forward* ip=forward[ipart]->GetIntermediate(); 
	 for(unsigned int j=0; j<forward.size(); j++) {
		if(ipart==j ||
			forward[j]->GetIntermediate()==NULL) continue;
		Forward* jp=forward[j]->GetIntermediate(); 
		if(ip->GetPDGcode() ==jp->GetPDGcode()  &&
			(int)(ip->GetMomentum().Energy()*1000.)==(int)(jp->GetMomentum().Energy()*1000.)) {
		  intermediate.push_back(forward[j]);
		}
	 }
  }
  intermediate.push_back(forward[ipart]);
  
  /// Sort by energy
  double etmp=0;
  for(unsigned int i=0; i<intermediate.size()-1; i++) {
	 for(unsigned int j=i+1; j<intermediate.size(); j++) {
		if(intermediate[j]->GetMomentum().E()>
			intermediate[i]->GetMomentum().E()) {
		  Forward* tmp=intermediate[j];
		  intermediate[j]=intermediate[i];
		  intermediate[i]=tmp;
		}
	 }
  }
  
  return intermediate;
}

TVector3 GetHitPosition(vector<Forward*> forward, int ipart, int flag=0)
/// 0: Projection to RHICf from intermediate particle/ 1: Recorded position
{
  if(flag==0 && forward[ipart]->GetIntermediate()!=NULL) {
	 Forward* ip=forward[ipart]->GetIntermediate();
	 TVector3 proj=GetProjection(ip->GetPosition(), ip->GetMomentum(), rhicf_posz);
	 return proj;
  }else{
	 return forward[ipart]->GetPosition();
  }
}

vector<Forward*> Intermediates(vector<Forward*> forward)
{
  vector<Forward*> intermediates;
  intermediates.clear();
  
  vector<int> tmp_pdg;
  tmp_pdg.clear();
  vector<TVector3> tmp_pos;
  tmp_pos.clear();
  vector<TLorentzVector> tmp_mom;
  tmp_mom.clear();
  for(unsigned int i=0; i<forward.size(); i++) {
	 if(forward[i]->GetIntermediate()==NULL) {
		intermediates.push_back(forward[i]);
		tmp_pdg.push_back(forward[i]->GetPDGcode());
		tmp_pos.push_back(forward[i]->GetPosition());
		tmp_mom.push_back(forward[i]->GetMomentum());
		
		//cout << i << "  NULL" << endl; 
	 }else if(tmp_pdg.size()==0) {
		tmp_pdg.push_back(forward[i]->GetIntermediate()->GetPDGcode());
		tmp_pos.push_back(forward[i]->GetIntermediate()->GetPosition());
		tmp_mom.push_back(forward[i]->GetIntermediate()->GetMomentum());
		
		intermediates.push_back(forward[i]->GetIntermediate());
		//cout << i << "   size 0 "  << endl;
	 }else{
		bool newp=true;
		for(unsigned int j=0; j<tmp_pdg.size(); j++) {
		  /*
			 cout << i << " " << j << " " 
			 << setprecision(5) 
			 << tmp_mom[j].Energy() << " " 
			 << forward[i]->GetIntermediate()->GetMomentum().Energy() << "   "
			 << tmp_pos[j].X() << "  " 
			 << forward[i]->GetIntermediate()->GetPosition().X() << "  "
			 << tmp_pos[j].Z() << "  "
			 << forward[i]->GetIntermediate()->GetPosition().Z() << "  "
			 << endl;
		  */
		  //if(tmp_pdg[j]==forward[i]->GetIntermediate()->GetPDGcode() &&
		  //   (int)(tmp_pos[j].X()*1000)==(int)(forward[i]->GetIntermediate()->GetPosition().X()*1000) &&
		  //   (int)(tmp_mom[j].Energy()*1000)==(int)(forward[i]->GetIntermediate()->GetMomentum().Energy()*1000)) {
		  if(tmp_pdg[j]==forward[i]->GetIntermediate()->GetPDGcode() &&
		     (int)(tmp_mom[j].Energy()*1000)==(int)(forward[i]->GetIntermediate()->GetMomentum().Energy()*1000)) {
			 newp=false;
		    //cout << "false" << endl;
			 break;
		  }
		}
		if(newp) {
		  tmp_pdg.push_back(forward[i]->GetIntermediate()->GetPDGcode());
		  tmp_pos.push_back(forward[i]->GetIntermediate()->GetPosition());
		  tmp_mom.push_back(forward[i]->GetIntermediate()->GetMomentum());
		  
		  forward[i]->SetPosition(GetHitPosition(forward,i,0));
		  intermediates.push_back(forward[i]->GetIntermediate());
		}
	 }
  }
  
  for(unsigned int i=0; i<intermediates.size(); i++) {
	 intermediates[i]
		->SetPosition(GetProjection(intermediates[i]->GetPosition(),
											 intermediates[i]->GetMomentum(),
											 rhicf_posz));
  }

  return intermediates;
}

void FormatForward(vector<Forward*> forward, vector<Forward*> &Mother, vector< vector<Forward*> > &Daughters)
{
  /// Clear
  for(unsigned int i=0; i<Mother.size(); i++) 
	 Daughters[i].clear();
  
  Mother.clear();
  
  if(forward.size()==0) return;
  
  Mother=Intermediates(forward);
  int fsize=Mother.size();
  Daughters.resize(fsize);
  
  int j=0;
  for(unsigned int i=0; i<forward.size(); i++) {
	 if(j==fsize) break;
	 if((Mother[j]->GetPDGcode()==forward[i]->GetPDGcode() &&
		  Mother[j]->GetMomentum()==forward[i]->GetMomentum()) ||
		 (Mother[j]->GetPDGcode()==forward[i]->GetIntermediate()->GetPDGcode() &&
		  Mother[j]->GetMomentum()==forward[i]->GetIntermediate()->GetMomentum())) {
		
		Daughters[j]=SameIntermediates(forward,i);
		j++;
	 }
  }
  
  if(Mother.size()>1) {
	 for(unsigned int i=0; i<Mother.size()-1; i++) {
		for(unsigned int j=i+1; j<Mother.size(); j++) {
		  if(Mother[i]->GetMomentum().E()<Mother[j]->GetMomentum().E()) {
			 Forward* tmp=Mother[i];
		    //cout << " Position " << Mother[i]->GetPosition().z() << endl;
          
		    Mother[i]=Mother[j];
			 Mother[j]=tmp;
			 vector<Forward*> tmp2=Daughters[i];
			 Daughters[i]=Daughters[j];
			 Daughters[j]=tmp2;
		  }
		}
	 }
  }
  

  if(0) {
	 for(unsigned int i=0; i<Mother.size(); i++) {
		//cout << ">>> " << i << "/" << Mother.size()  << endl;
		for(unsigned int j=0; j<Daughters[i].size(); j++) {  
		  /*
			 cout << " " << j << "/"
			 << Daughters[i].size()  << " "
			 << Daughters[i][j]->GetPosition().Z()  << " "
			 << endl;
		  */
		}
	 }
  }
}




int main(int argc, char** argv)
{
  
  cout << "begin convertor" <<endl;
  
  
  // Variables
  TString InputFileName;
  TString OutputFileName;
  Int_t Run = 0;
  
  for(int i=1;i<argc;i++){
	 string ss = argv[i];
	 if(ss == "-i"){
		InputFileName = argv[++i];
	 }
	 if(ss == "-o"){
		OutputFileName =argv[++i];
	 }
	 if(ss == "--run"){
		Run = atoi(argv[++i]);
	 }
  }
  
  
  TString tmpString;
  TChain* ChainForInput;
  
  // IO files
  TFile* OutputFile;
  TTree* TreeInOutputFile;
  
  // ++++++ OPEN DATA FILE ++++++++++++++++++++++++++
  ChainForInput = new TChain("EventInfo");
  //InputFileName     = Form("%s", argv[2]);
  //OutputFileName    = Form("%s", argv[4]);
  cout << "InputFileName " << InputFileName  << endl;
  cerr << "InputFileName " << InputFileName  << endl;
  
  // Containers from Suzuki
  RHICfSimEvent *SimEvent = new RHICfSimEvent();
  //RunInfo *SimRunInfo = new RunInfo();
  MCDataContainer *RHICfContainer = new MCDataContainer();
  BBCContainer *fBBCContainer = new BBCContainer();
  ZDCContainer *fZDCContainer = new ZDCContainer();
  ForwardContainer* forwardCont=new ForwardContainer();
  
  // New format
  RHICfEvent *RHICfEvents=  new RHICfEvent();
  
  // Setting for Input root file
  ChainForInput -> AddFile(InputFileName);
  ChainForInput -> SetMakeClass(1);
  ChainForInput -> SetBranchAddress("mc", &RHICfContainer);
  ChainForInput -> SetBranchAddress("bbc", &fBBCContainer);
  //ChainForInput -> SetBranchAddress("zdc", &fZDCContainer);
  
  //ChainForInput -> SetBranchAddress("RunInfo", &SimRunInfo);
  
  
  
  // ++++++ OUTPUT DATA FILE ++++++++++++++++++++++++++
  OutputFile = new TFile(OutputFileName, "RECREATE");
  TreeInOutputFile = new TTree("LHCfEvents","Collision Events");
  TreeInOutputFile  ->  Branch("ev.","LHCfEvent",&RHICfEvents);
  
  A1Cal2* Cal2M = new A1Cal2("a1cal2", "RHICf Trigger Event");
  RHICfBBC* fBBC = new RHICfBBC("bbc","RHICf Trigger Event"); 
  RHICfZDC* fZDC = new RHICfZDC("zdc","RHICf Trigger Event"); 
  //RHICfSimIncidents* a1simin = new RHICfSimIncidents("a1simin","RHICf particle Info");
  
  
  // TMP vectors for copying detector response
  // ARM1
  vector<vector<double> > DepEInPlate;//2D vector for saving deposit energy in GSO plate
  vector<vector<vector<vector<double> > > > DepEInGSOBar;//4D vector for saving deposit energy in GSO bar
  // ZDC
  //vector<int> NopInZDC;
  //vector<vector<double> > DepEInSMD;
  // BBC
  vector<vector<BBC*> > DepEInBBC;
  
  int TotalNEvent = ChainForInput -> GetEntries();
  
  int run = 0;
  int gnumber=0;
  ChainForInput -> SetBranchAddress("forward", &forwardCont);
  vector<Forward*> forward;
  
  RHICfSimP p[1000];
  RHICfFlag *Flag = new RHICfFlag();
  // Loop for Conversion Process =========================================================
  for(int iEvent=0; iEvent<TotalNEvent; iEvent++)
	 {
		ChainForInput -> GetEntry(iEvent);
		RHICfEvents->Clear();
		//RHICfEvents->run = SimRunInfo->GetRunNumber();
		//RHICfEvents->gnumber = gnumber+1; 
		
		RHICfEvents->run = Run;
		RHICfEvents->gnumber = iEvent;
		
		// Copy responses to temp vectors
		DepEInPlate   = RHICfContainer->GetPlate();
		DepEInGSOBar  = RHICfContainer->GetBar();
		DepEInBBC   = fBBCContainer->GetContainer();
		//NopInZDC  = fZDCContainer->GetNphoton();
		//DepEInSMD  = fZDCContainer->GetSMD();
		
		// Header of A1Cal2 ---------------------------------
		Cal2M->run = Run;
		Cal2M->number = iEvent;
		Cal2M->flag[0] = 0x1013;
		
		// Conversion ARM1 response ------------------------
		for(int iTower=0; iTower<2; iTower++) {
		  // GSO plate
		  for(int iPlate=0; iPlate<16; iPlate++) {
			 // Insert deposit energy for GSO plate into A1Cal2M
			 (Cal2M->cal)[iTower][iPlate] = DepEInPlate[iTower][iPlate]/1000.;
			 //if ( iTower ==0 && iPlate ==0) cout << "de " <<  (Cal2M->cal)[iTower][iPlate] << endl; 
			 //Junsang****cout << (Cal2M->cal)[iTower][iPlate] << endl;
		  }

		  // GSO bar
		  for(int iGSOBarDepth=0; iGSOBarDepth<4; iGSOBarDepth++) {
			 for(int GSOBarXY=0; GSOBarXY<2; GSOBarXY++){
				if(iTower==0){
				  for(int iCH=0; iCH<20; iCH++){
					 (Cal2M->scifi0)[iGSOBarDepth][GSOBarXY][iCH] = DepEInGSOBar[iTower][iGSOBarDepth][GSOBarXY][iCH];
					 //Junsang****cout << (Cal2M->scifi0)[iGSOBarDepth][GSOBarXY][iCH] << endl;
				  }
				} 
				else {
				  for(int iCH=0; iCH<40; iCH++) {
					 (Cal2M->scifi1)[iGSOBarDepth][GSOBarXY][iCH] = DepEInGSOBar[iTower][iGSOBarDepth][GSOBarXY][iCH];
					 //Junsang****cout << (Cal2M->scifi1)[iTower][iGSOBarDepth][GSOBarXY][iCH] << endl;
				  }
				}
			 }
		  }
		} // end of conversion Arm1 responce --
		
        // Conversion ZDC response
		/*
        for (int iZDC = 0; iZDC < 3; iZDC++) 
        {
		  (fZDC->ZDCNOP)[iZDC] = NopInZDC[iZDC];
		  //Junsang****cout << (fZDC->ZDCNop)[iZDC] << endl;
        }
		*/
		// Conversion SMD response
		/*
        for (int iXY = 0; iXY < 2; iXY++) 
        {
		  if (iXY==0) 
		  {
		  for (int j = 0; j < 7; j++) 
		  {
		  (fZDC->SMDHdE)[j] = DepEInSMD[iXY][j];
		  //Junsang****cout <<(fZDC->SMDHdE)[j]<< endl;
		  }
		  }
		  for (int j = 0; j < 8; j++) 
		  {
		  (fZDC->SMDVdE)[j] = DepEInSMD[iXY][j];
		  //Junsang****cout << (fZDC->SMDVdE)[j] << endl;
		  }
        }
		*/

		// Conversion BBC response --------------------		
		for (int iEW = 0; iEW < 2; iEW++) {
		  for (int iBBC = 0; iBBC < 32; iBBC++) {
			 (fBBC->dE)[iEW][iBBC] = DepEInBBC[iEW][iBBC]->GetEdep();
			 //Junsang****cout << (fBBC->dE)[iEW][iBBC] << endl;
		  }
		}
		
		/// Add SimIncidents --------------------------
		
		forward=forwardCont->GetContainer();
		vector<Forward*> fMother;
		vector< vector<Forward*> > fDaughters;
		FormatForward(forward, fMother, fDaughters);
		
		RHICfSimIncidents* a1simin = new RHICfSimIncidents("a1simin","RHICf particle Info");
		a1simin->clear();
		a1simin->run = Run;
		a1simin->number = iEvent;
		
		// SimIncidents For RHICf
		RHICfSimP tmp;
		int np=0;
		for(unsigned int i=0; i<fMother.size(); i++) {
// 		  tmp.pdgcode=fMother[i]->GetPDGcode();
// 		  tmp.pos[0]=fMother[i]->GetPosition().x();
// 		  tmp.pos[1]=fMother[i]->GetPosition().y();
// 		  tmp.pos[2]=fMother[i]->GetPosition().z();
// 		  tmp.energy=fMother[i]->GetMomentum().E();
// 		  tmp.mom[0]=fMother[i]->GetMomentum().Px();
// 		  tmp.mom[1]=fMother[i]->GetMomentum().Py();
// 		  tmp.mom[2]=fMother[i]->GetMomentum().Pz();
// 		  int mother=fMother[i]->GetMotherID();
// 		  if(fMother[i]->IsBackground()) mother=-mother;
// 		  tmp.user=mother;
// 		  p[np].copydata(&tmp);

		  tmp.fPdgcode  = fMother[i]->GetPDGcode();
		  tmp.fFMomentum = fMother[i]->GetMomentum();
		  tmp.fPosition = fMother[i]->GetPosition();
		  int mother=fMother[i]->GetMotherID();
		  if(fMother[i]->IsBackground()) mother=-mother;
		  tmp.fTrackID  = mother;
		  p[np] = tmp;

		  np++;
		}
		
	
		RHICfSimP *pp;
		for(int i=0;i<np;i++){
		  pp = new RHICfSimP();
		  (*pp) = p[i];
		  a1simin->Add(pp);  
		}
		
		Flag->SetFlag(Cal2M);
		
		RHICfEvents->Add(a1simin);
		RHICfEvents->Add(Cal2M);
		//RHICfEvents -> Add(fZDC);
		RHICfEvents->Add(fBBC);
		//a1simin->Show();
		
		TreeInOutputFile -> Fill();
		delete a1simin;

    } // end of event looop
  
  OutputFile -> Write();
  OutputFile -> Close();
  return 0;
}

