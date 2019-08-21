#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include "FileManager.hh"
#include "A1Cal2.h"
#include "A1Cal2M.h"
#include "RHICfBBC.h"
#include "RHICfZDC.h"
#include "LHCfEvent.h"
#include "RunInfo.hpp"
#include "RHICfSimP.h"
#include "ParticlesInfo.h"

void ReadList(TString list, TChain* chain)
{
    ifstream myReadFile;
    string tmpstring;
    myReadFile.open(list);
    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile, tmpstring)) 
        {
            chain->AddFile(tmpstring.c_str());
        }
    }
    myReadFile.close();
}

int main(int argc, char** argv)
{

    FileManager::GetInstance()->PrepareSavingDirectory();
    


    // Variables
    TString OutputFileName;
    TString tmpString;
    TChain* ChainForInput1;
    TChain* ChainForInput2;
    TChain* ChainForInput3;
    TChain* ChainForInput4;
    TChain* ChainForInput5;
    TChain* ChainForInput6;
    TChain* ChainForInput7;
    TChain* ChainForInput8;
    TChain* ChainForInput9;
    TChain* ChainForInput10;
    TChain* ChainForInput11;
    TChain* ChainForInput12;
    TChain* ChainForInput13;
    TChain* ChainForInput14;
    TChain* ChainForInput15;
    
    //Junsang****ChainForInput1 = new TChain("ARM1PL");
    //Junsang****ChainForInput2 = new TChain("ARM1BAR");
    //Junsang****ChainForInput3 = new TChain("FrontCounterInfo");
    //Junsang****ChainForInput4 = new TChain("WPlate");
    //Junsang****ChainForInput5 = new TChain("ZDCPMMA");
    //Junsang****ChainForInput6 = new TChain("ZDCSMD");
    //Junsang****ChainForInput7 = new TChain("ZDCGhost");
    //Junsang****ChainForInput8 = new TChain("IP");
    //Junsang****ChainForInput9 = new TChain("Ghost");
    //Junsang****ChainForInput10 = new TChain("Circle");
    ChainForInput11 = new TChain("GhostWhenPion");
    ChainForInput12 = new TChain("GhostWhenNeutron");
    ChainForInput13 = new TChain("PionSignal");
    ChainForInput14 = new TChain("NeutronSignal");
    //Junsang****ChainForInput15 = new TChain("SPINInfo");

    //Junsang****ChainForInput11->AddFile("/home/hoosiki/Documents/ANA/neutronstatistics/DATA/P_TOP/P_TOP010132266.root");
    //Junsang****ChainForInput11->AddFile("/home/hoosiki/Documents/ANA/neutronstatistics/DATA/P_TOP/P_TOP01035673.root");
    //Junsang****ChainForInput11->AddFile("/home/hoosiki/Documents/ANA/neutronstatistics/DATA/P_TOP/P_TOP010111456.root");

    // Related input
    tmpString = argv[1];
    if(argc>=1) 
    {
        //Junsang****ReadList(tmpString, ChainForInput1);
        //Junsang****ReadList(tmpString, ChainForInput2);
        //Junsang****ReadList(tmpString, ChainForInput3);
        //Junsang****ReadList(tmpString, ChainForInput4);
        //Junsang****ReadList(tmpString, ChainForInput5);
        //Junsang****ReadList(tmpString, ChainForInput6);
        //Junsang****ReadList(tmpString, ChainForInput7);
        //Junsang****ReadList(tmpString, ChainForInput8);
        //Junsang****ReadList(tmpString, ChainForInput9);
        //Junsang****ReadList(tmpString, ChainForInput10);
        ReadList(tmpString, ChainForInput11);
        ReadList(tmpString, ChainForInput12);
        ReadList(tmpString, ChainForInput13);
        ReadList(tmpString, ChainForInput14);
        //Junsang****ReadList(tmpString, ChainForInput15);
    }else 
    {
        ChainForInput1 -> AddFile(tmpString);
    }
    
    FileManager::GetInstance()->SetFileName(argv[2]);

    // Related output
    OutputFileName = FileManager::GetInstance()->GetPathForANALYSIS()+"/"+FileManager::GetInstance()->GetFileName()+".root";





    // IO files
    TFile* OutputFile;
    TTree* TreeInOutputFile;

    OutputFile = new TFile(OutputFileName, "RECREATE");
    //Junsang****TreeInOutputFile = new TTree("LHCfEvents","Tree of RHICfEvent");
    //Junsang****TreeInOutputFile  ->  Branch("Events","LHCfEvent",&RHICfEvents);

    //Junsang****A1Cal2 *Cal2M = new A1Cal2("a1cal2", "RHICf Event");
    //Junsang****RHICfBBC *fBBC = new RHICfBBC("bbc","RHICf Event"); 
    //Junsang****RHICfZDC *fZDC = new RHICfZDC("zdc","RHICf Event");
    //Junsang****ParticlesInfo *fParticles = new ParticlesInfo("particles", "RHICf Event");







    int TotalNEvent14 = ChainForInput14 -> GetEntries();
    //Junsang****int TotalNEvent12 = ChainForInput12 -> GetEntries();
    //Junsang****int TotalNEvent13 = ChainForInput13 -> GetEntries();
    //Junsang****int TotalNEvent14 = ChainForInput14 -> GetEntries();

    std::cout << "TotalNumberN: " << TotalNEvent14 << std::endl;
    //Junsang****std::cout << "TotalNumberN: " << TotalNEvent12 << std::endl;
    //Junsang****std::cout << "TotalNumberSP0: " << TotalNEvent13 << std::endl;
    //Junsang****std::cout << "TotalNumberSN: " << TotalNEvent14 << std::endl;


    Int_t RunNumber;
    Double_t pT, ENERGY, MOMENTUMY, MOMENTUMX;
    
    ChainForInput14->SetBranchAddress("RunNumber", &RunNumber);
    ChainForInput14->SetBranchAddress("ENERGY[GeV]", &ENERGY);

    ChainForInput14->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX);
    ChainForInput14->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX);

    TH1D* spectrum   = new TH1D("spectrum","Espectrum;Neutron Energy[GeV];Event#",255,0.,255.);
    TH1D* pTdis   = new TH1D("pTdistribution","pT distribution;pT[GeV/C];Event#",30,0.,1.8);
    TH1D* lowEspec   = new TH1D("lowpt","Spectrum in low range;Neutron Energy[GeV];Event#",255,0.,255.);
    TH1D* highEspec   = new TH1D("highpt","Spectrum in high range;Neutron Energy[GeV];Event#",255,0.,255.);



    for (int i = 0; i < TotalNEvent14; i++) 
    {
        ChainForInput14->GetEntry(i);
        //Junsang****cout << RunNumber << endl;
        //Junsang****cout << ENERGY << endl;
        //Junsang****cout << MOMENTUMX << endl;
        //Junsang****cout << MOMENTUMY << endl;
        spectrum->Fill(ENERGY);
        pT = sqrt(MOMENTUMX*MOMENTUMX+MOMENTUMY*MOMENTUMY);
        pTdis->Fill(pT);

        if(pT<=0.3)
        {
            lowEspec->Fill(ENERGY);
        }

        if(pT>=0.9)
        {
            highEspec->Fill(ENERGY);
        }
    }

    //Junsang****RHICfSimP p[1000];
    //Junsang****RHICfFlag *Flag = new RHICfFlag();
    // Loop for Conversion Process 
    //Junsang****for(int iEvent=0; iEvent<TotalNEvent; iEvent++)
    //Junsang****{
        //Junsang****ChainForInput -> GetEntry(iEvent);
        //Junsang****RHICfEvents->Clear();
        //Junsang****RHICfEvents->run = SimRunInfo->GetRunNumber();
        //Junsang****RHICfEvents->gnumber = gnumber+1; 
//Junsang****
        //Junsang****// Copy responses to temp vectors
        //Junsang****DepEInPlate   = RHICfContainer->GetPlate();
        //Junsang****DepEInGSOBar  = RHICfContainer->GetBar();
        //Junsang****DepEInBBC   = fBBCContainer->GetContainer();
        //Junsang****NopInZDC  = fZDCContainer->GetNphoton();
        //Junsang****DepEInSMD  = fZDCContainer->GetSMD();
//Junsang****
        //Junsang****Cal2M->number = iEvent;
        //Junsang****Cal2M->flag[0] = 0x1013;
        //Junsang****// Conversion ARM1 response
        //Junsang****for(int iTower=0; iTower<2; iTower++)
        //Junsang****{
            //Junsang****// GSO plate
            //Junsang****for(int iPlate=0; iPlate<16; iPlate++)
            //Junsang****{
                //Junsang****// Insert deposit energy for GSO plate into A1Cal2M
                //Junsang****(Cal2M->cal)[iTower][iPlate] = DepEInPlate[iTower][iPlate];
                //Junsang****//Junsang****cout << (Cal2M->cal)[iTower][iPlate] << endl;
            //Junsang****}
            //Junsang****// GSO bar
            //Junsang****for(int iGSOBarDepth=0; iGSOBarDepth<4; iGSOBarDepth++)
            //Junsang****{
                //Junsang****for(int GSOBarXY=0; GSOBarXY<2; GSOBarXY++)
                //Junsang****{
                    //Junsang****if(iTower==0)
                    //Junsang****{
                        //Junsang****for(int iCH=0; iCH<20; iCH++)
                        //Junsang****{
                            //Junsang****(Cal2M->scifi0)[iGSOBarDepth][GSOBarXY][iCH] = DepEInGSOBar[iTower][iGSOBarDepth][GSOBarXY][iCH];
                            //Junsang****//Junsang****cout << (Cal2M->scifi0)[iGSOBarDepth][GSOBarXY][iCH] << endl;
                        //Junsang****}
                    //Junsang****}else
                    //Junsang****{
                        //Junsang****for(int iCH=0; iCH<40; iCH++)
                        //Junsang****{
                            //Junsang****(Cal2M->scifi1)[iGSOBarDepth][GSOBarXY][iCH] = DepEInGSOBar[iTower][iGSOBarDepth][GSOBarXY][iCH];
                            //Junsang****//Junsang****cout << (Cal2M->scifi1)[iTower][iGSOBarDepth][GSOBarXY][iCH] << endl;
                        //Junsang****}
                    //Junsang****}
                //Junsang****}
            //Junsang****}
        //Junsang****}
        //Junsang****// Conversion ZDC response
        //Junsang****for (int iZDC = 0; iZDC < 3; iZDC++) 
        //Junsang****{
            //Junsang****(fZDC->ZDCNOP)[iZDC] = NopInZDC[iZDC];
            //Junsang****//Junsang****cout << (fZDC->ZDCNop)[iZDC] << endl;
        //Junsang****}
        //Junsang****// Conversion SMD response
        //Junsang****for (int iXY = 0; iXY < 2; iXY++) 
        //Junsang****{
            //Junsang****if (iXY==0) 
            //Junsang****{
                //Junsang****for (int j = 0; j < 7; j++) 
                //Junsang****{
                    //Junsang****(fZDC->SMDHdE)[j] = DepEInSMD[iXY][j];
                    //Junsang****//Junsang****cout <<(fZDC->SMDHdE)[j]<< endl;
                //Junsang****}
            //Junsang****}
            //Junsang****for (int j = 0; j < 8; j++) 
            //Junsang****{
                //Junsang****(fZDC->SMDVdE)[j] = DepEInSMD[iXY][j];
                //Junsang****//Junsang****cout << (fZDC->SMDVdE)[j] << endl;
            //Junsang****}
        //Junsang****}
        //Junsang****// Conversion BBC response
        //Junsang****for (int iEW = 0; iEW < 2; iEW++) 
        //Junsang****{
            //Junsang****for (int iBBC = 0; iBBC < 32; iBBC++) 
            //Junsang****{
                //Junsang****(fBBC->dE)[iEW][iBBC] = DepEInBBC[iEW][iBBC]->GetEdep();
                //Junsang****//Junsang****cout << (fBBC->dE)[iEW][iBBC] << endl;
            //Junsang****}
        //Junsang****}
        //Junsang****/// Add SimIncidents
        //Junsang****forward=forwardCont->GetContainer();
        //Junsang****vector<Forward*> fMother;
        //Junsang****vector< vector<Forward*> > fDaughters;
        //Junsang****FormatForward(forward, fMother, fDaughters);
//Junsang****
        //Junsang****a1simin->clear();
//Junsang****
        //Junsang****/// SimIncidents For RHICf
        //Junsang****RHICfSimP tmp;
        //Junsang****int np=0;
        //Junsang****for(unsigned int i=0; i<fMother.size(); i++) {
            //Junsang****tmp.pdgcode=fMother[i]->GetPDGcode();
            //Junsang****tmp.pos[0]=fMother[i]->GetPosition().x();
            //Junsang****tmp.pos[1]=fMother[i]->GetPosition().y();
            //Junsang****tmp.pos[2]=fMother[i]->GetPosition().z();
            //Junsang****tmp.energy=fMother[i]->GetMomentum().E();
            //Junsang****tmp.mom[0]=fMother[i]->GetMomentum().Px();
            //Junsang****tmp.mom[1]=fMother[i]->GetMomentum().Py();
            //Junsang****tmp.mom[2]=fMother[i]->GetMomentum().Pz();
            //Junsang****int mother=fMother[i]->GetMotherID();
            //Junsang****if(fMother[i]->IsBackground()) mother=-mother;
            //Junsang****tmp.user=mother;
//Junsang****
            //Junsang****p[np].copydata(&tmp);
            //Junsang****np++;
        //Junsang****}
//Junsang****
        //Junsang****RHICfSimP *pp;
        //Junsang****for(int i=0;i<np;i++){
            //Junsang****pp = new RHICfSimP();
            //Junsang****pp->copydata(&(p[i]));
            //Junsang****a1simin->Add(pp);
        //Junsang****}
//Junsang****
        //Junsang****//Junsang****Flag->SetFlag(Cal2M);
//Junsang****
        //Junsang****RHICfEvents->Add(a1simin);
        //Junsang****RHICfEvents -> Add(Cal2M);
        //Junsang****RHICfEvents -> Add(fZDC);
        //Junsang****RHICfEvents -> Add(fBBC);
        //Junsang****TreeInOutputFile -> Fill();
    //Junsang****}

    OutputFile -> Write();
    OutputFile -> Close();
    cout << "End" << endl;
    return 0;
}

