#include <vector>
#include <list>
#include <algorithm>
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
#include <TH2D.h>
#include <TStyle.h>
#include <TString.h>
#include <cstdlib>
#include "FileManager.hh"
#include "A1Cal2.h"
#include "RHICfFlag.h"
#include "A1Cal2M.h"
#include "RHICfBBC.h"
#include "RHICfZDC.h"
#include "LHCfEvent.h"
#include "RunInfo.hpp"
#include "RHICfSimP.h"
#include "ParticlesInfo.h"
#include "RHICfFC.h"

typedef LHCfEvent RHICfEvent;

void ReadList(TString list, TChain* chain)
{
    ifstream myReadFile;
    string tmpstring;
    myReadFile.open(list);
    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile, tmpstring)) 
        {
            chain->Add(tmpstring.c_str());
        }
    }
    myReadFile.close();
}


void BuildIndex(TChain* chain, Int_t &eventnumber)
{
    eventnumber = chain->GetEntries(); 
    cout << "Entry Number in " << chain->GetName() << ": " << eventnumber << endl;
    cout << chain->GetEntries() << endl;

    //Junsang****if(eventnumber)
    //Junsang****{
        //Junsang****chain->BuildIndex("RunNumber", "EventNumber");
    //Junsang****}
}


int main(int argc, char** argv)
{

    FileManager::GetInstance()->PrepareSavingDirectory();



    // Variables
    TString OutputFileName;
    TString tmpString;
    TChain* ChainForInput[15];
    TString BrName[15] = 
    {
        "ARM1PL" , 
        "ARM1BAR" , 
        "FrontCounterInfo" , 
        "WPlate" , 
        "ZDCPMMA" , 
        "ZDCSMD" , 
        "ZDCGhost" , 
        "IP" , 
        "Ghost" , 
        "Circle" , 
        "GhostWhenPion" , 
        "GhostWhenNeutron" , 
        "PionSignal" , 
        "NeutronSignal" , 
        "SPINInfo"
    };





    for (int i = 0; i < 15; i++) 
    {
        ChainForInput[i] = new TChain(BrName[i]);
    }



    // Related input
    tmpString = argv[1];

    for (int i = 0; i < 15; i++) 
    {
        ReadList(tmpString, ChainForInput[i]);
    }


    FileManager::GetInstance()->SetFileName(argv[2]);

    // Related output
    OutputFileName = FileManager::GetInstance()->GetPathForANALYSIS()+"/"+FileManager::GetInstance()->GetFileName()+".root";


    RHICfEvent *RHICfEvents = new RHICfEvent();

    A1Cal2 *Cal2 = new A1Cal2("a1cal2", "RHICf NOP&DE");
    RHICfBBC *fBBC = new RHICfBBC("bbc","BBC NOP&DE"); 
    RHICfZDC *fZDC = new RHICfZDC("zdc","ZDC NOP&DE ");
    RHICfFC  *fFC = new RHICfFC("fc", "FC NOP&DE");
    //Junsang****RHICfFlag *Flag = new RHICfFlag();
    ParticlesInfo *fParticles = new ParticlesInfo("particles", "Particle info at each region");

    Int_t RUN, EVENT;
    Double_t TSGSOPLE[16], TLGSOPLE[16], TSGSOBR[4][20], TLGSOBR[4][40], TSGSOBL[4][20], TLGSOBL[4][40], TOTALE;

    // IO files
    TFile* OutputFile;
    TTree* TreeInOutputFile;








    //Junsang****std::cout << "TotalNumber: " << TotalNEvent << std::endl;



    // SetBranchAddress to store deposit energy for ARM1
    // GSOPlate
    for (int ilayer = 0; ilayer < 16; ilayer++) 
    {
        TString tmpstring;
        tmpstring ="TSGSOPLDE" + to_string(ilayer);
        ChainForInput[0]->SetBranchAddress(tmpstring, &TSGSOPLE[ilayer]);
        tmpstring ="TLGSOPLDE" + to_string(ilayer);
        ChainForInput[0]->SetBranchAddress(tmpstring, &TLGSOPLE[ilayer]);

    }
    ChainForInput[0]->SetBranchAddress("TotalEnergy", &TOTALE);
    // GSOBar
    for (int ilayer = 0; ilayer < 4; ilayer++) 
    {
        // 
        for (int iSmall = 0; iSmall < 20; iSmall++) 
        {
            TString tmpstring;
            tmpstring ="TSGSOBRDE" + to_string(ilayer) + to_string(iSmall);
            ChainForInput[1]->SetBranchAddress(tmpstring, &TSGSOBR[ilayer][iSmall]);
            tmpstring ="TSGSOBLDE" + to_string(ilayer) + to_string(iSmall);
            ChainForInput[1]->SetBranchAddress(tmpstring, &TSGSOBL[ilayer][iSmall]);
        }
        for (int iLarge = 0; iLarge < 40; iLarge++) 
        {
            TString  tmpstring;
            tmpstring ="TLGSOBRDE" + to_string(ilayer) + to_string(iLarge);
            ChainForInput[1]->SetBranchAddress(tmpstring, &TLGSOBR[ilayer][iLarge]);
            tmpstring ="TLGSOBLDE" + to_string(ilayer) + to_string(iLarge);
            ChainForInput[1]->SetBranchAddress(tmpstring, &TLGSOBL[ilayer][iLarge]);
        }
    }

    ChainForInput[0]->SetBranchAddress("RunNumber", &RUN);
    ChainForInput[0]->SetBranchAddress("EventNumber", &EVENT);


    Double_t TSFCDE, TLFCDE;
    Int_t TSFCNOP, TLFCNOP;

    // SetBranchAddress to store deposit energy for FrontCounter
    // Scintillator
    ChainForInput[2]->SetBranchAddress("TSFCDE", &TSFCDE);
    ChainForInput[2]->SetBranchAddress("TLFCDE", &TLFCDE);
    ChainForInput[2]->SetBranchAddress("TSFCNOP", &TSFCNOP);
    ChainForInput[2]->SetBranchAddress("TLFCNOP", &TLFCNOP);


    Double_t WPositionX, WPositionY, WPositionZ, WMomentumX, WMomentumY, WMomentumZ, WEnergy, WOEnergy;
    Char_t WName[10], WOName[10];
    Int_t WRunNumber, WEventNumber;


    // SetBranchAddress to store information about particles gothrough WPlate
    // Particle Info
    ChainForInput[3]->SetBranchAddress("POSITIONX[mm]", &WPositionX);
    ChainForInput[3]->SetBranchAddress("POSITIONY[mm]", &WPositionY);
    ChainForInput[3]->SetBranchAddress("POSITIONZ[mm]", &WPositionZ);
    ChainForInput[3]->SetBranchAddress("MOMENTUMX[GeV/c]", &WMomentumX);
    ChainForInput[3]->SetBranchAddress("MOMENTUMY[GeV/c]", &WMomentumY);
    ChainForInput[3]->SetBranchAddress("MOMENTUMZ[GeV/c]", &WMomentumZ);
    ChainForInput[3]->SetBranchAddress("ENERGY[GeV]", &WEnergy);
    ChainForInput[3]->SetBranchAddress("OPENERGY[GeV]", &WOEnergy);
    ChainForInput[3]->SetBranchAddress("NAME", &WName);
    ChainForInput[3]->SetBranchAddress("ORIGINALPARTICLE", &WOName);
    ChainForInput[3]->SetBranchAddress("RunNumber", &WRunNumber);
    ChainForInput[3]->SetBranchAddress("EventNumber", &WEventNumber);


    Double_t ZDCPMMA[3], SMDV[7], SMDH[8];
    Int_t   ZDCNOP[3], SMDVNOP[7], SMDHNOP[8];

    // SetBranchAddress to store deposit energy for ZDC
    // PMMA
    ChainForInput[4]->SetBranchAddress("1stPMMADE[MeV]", &ZDCPMMA[0]);
    ChainForInput[4]->SetBranchAddress("2ndPMMADE[MeV]", &ZDCPMMA[1]);
    ChainForInput[4]->SetBranchAddress("3rdPMMADE[MeV]", &ZDCPMMA[2]);
    ChainForInput[4]->SetBranchAddress("1stPMMANOP", &ZDCNOP[0]);
    ChainForInput[4]->SetBranchAddress("2ndPMMANOP", &ZDCNOP[1]);
    ChainForInput[4]->SetBranchAddress("3rdPMMANOP", &ZDCNOP[2]);
    // SMD
    for (int ivertical = 0; ivertical < 7; ivertical++) 
    {
        TString tmpstring;
        tmpstring ="SMDVDE" + to_string(ivertical+1) + "[MeV]";
        ChainForInput[5]->SetBranchAddress(tmpstring, &SMDV[ivertical]);
        tmpstring ="SMDVNOP" + to_string(ivertical+1);
        ChainForInput[5]->SetBranchAddress(tmpstring, &SMDVNOP[ivertical]);
    }
    for (int ihorizon = 0; ihorizon < 8; ihorizon++) 
    {
        TString tmpstring;
        tmpstring ="SMDHDE" + to_string(ihorizon+1) + "[MeV]";
        ChainForInput[5]->SetBranchAddress(tmpstring, &SMDH[ihorizon]);
        tmpstring ="SMDHNOP" + to_string(ihorizon+1);
        ChainForInput[5]->SetBranchAddress(tmpstring, &SMDHNOP[ihorizon]);
    }


    Double_t ZDCGhostPositionX, ZDCGhostPositionY,  ZDCGhostMomentumX, ZDCGhostMomentumY, ZDCGhostMomentumZ, ZDCGhostEnergy, ZDCGhostOEnergy;
    Char_t ZDCGhostName[10], ZDCGhostOName[10];
    Int_t ZDCGhostRunNumber, ZDCGhostEventNumber;

    // SetBranchAddress to store information about particles gothrough ZDCGhostPlate
    // Particle Info
    ChainForInput[6]->SetBranchAddress("POSITIONX[mm]", &ZDCGhostPositionX);
    ChainForInput[6]->SetBranchAddress("POSITIONY[mm]", &ZDCGhostPositionY);
    ChainForInput[6]->SetBranchAddress("MOMENTUMX[GeV/c]", &ZDCGhostMomentumX);
    ChainForInput[6]->SetBranchAddress("MOMENTUMY[GeV/c]", &ZDCGhostMomentumY);
    ChainForInput[6]->SetBranchAddress("MOMENTUMZ[GeV/c]", &ZDCGhostMomentumZ);
    ChainForInput[6]->SetBranchAddress("ENERGY[GeV]", &ZDCGhostEnergy);
    ChainForInput[6]->SetBranchAddress("OPENERGY[GeV]", &ZDCGhostOEnergy);
    ChainForInput[6]->SetBranchAddress("NAME", &ZDCGhostName);
    ChainForInput[6]->SetBranchAddress("ORIGINALPARTICLE", &ZDCGhostOName);
    ChainForInput[6]->SetBranchAddress("RunNumber", &ZDCGhostRunNumber);
    ChainForInput[6]->SetBranchAddress("EventNumber", &ZDCGhostEventNumber);


    Double_t IPPositionX, IPPositionY, IPPositionZ, IPMomentumX, IPMomentumY, IPMomentumZ, IPEnergy;
    Char_t IPName[10];
    Int_t IPRunNumber, IPEventNumber;

    // SetBranchAddress to store information about initial particles 
    // Particle Info
    ChainForInput[7]->SetBranchAddress("POSITIONX[mm]", &IPPositionX);
    ChainForInput[7]->SetBranchAddress("POSITIONY[mm]", &IPPositionY);
    ChainForInput[7]->SetBranchAddress("POSITIONZ[mm]", &IPPositionZ);
    ChainForInput[7]->SetBranchAddress("MOMENTUMX[GeV/c]", &IPMomentumX);
    ChainForInput[7]->SetBranchAddress("MOMENTUMY[GeV/c]", &IPMomentumY);
    ChainForInput[7]->SetBranchAddress("MOMENTUMZ[GeV/c]", &IPMomentumZ);
    ChainForInput[7]->SetBranchAddress("ENERGY[GeV]", &IPEnergy);
    ChainForInput[7]->SetBranchAddress("NAME", &IPName);
    ChainForInput[7]->SetBranchAddress("RunNumber", &IPRunNumber);
    ChainForInput[7]->SetBranchAddress("EventNumber", &IPEventNumber);


    Double_t GhostPositionX, GhostPositionY, GhostMomentumX, GhostMomentumY, GhostMomentumZ, GhostEnergy, GhostOEnergy;
    Char_t GhostName[10], GhostOName[10];
    Int_t GhostRunNumber, GhostEventNumber;

    // SetBranchAddress to store information about particles gothrough Ghost
    // Particle Info
    ChainForInput[8]->SetBranchAddress("POSITIONX[mm]", &GhostPositionX);
    ChainForInput[8]->SetBranchAddress("POSITIONY[mm]", &GhostPositionY);
    ChainForInput[8]->SetBranchAddress("MOMENTUMX[GeV/c]", &GhostMomentumX);
    ChainForInput[8]->SetBranchAddress("MOMENTUMY[GeV/c]", &GhostMomentumY);
    ChainForInput[8]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GhostMomentumZ);
    ChainForInput[8]->SetBranchAddress("ENERGY[GeV]", &GhostEnergy);
    ChainForInput[8]->SetBranchAddress("OPENERGY[GeV]", &GhostOEnergy);
    ChainForInput[8]->SetBranchAddress("NAME", &GhostName);
    ChainForInput[8]->SetBranchAddress("ORIGINALPARTICLE", &GhostOName);
    ChainForInput[8]->SetBranchAddress("RunNumber", &GhostRunNumber);
    ChainForInput[8]->SetBranchAddress("EventNumber", &GhostEventNumber);


    Double_t CirclePositionX, CirclePositionY, CircleMomentumX, CircleMomentumY, CircleMomentumZ, CircleEnergy, CircleOEnergy;
    Char_t CircleName[10], CircleOName[10];
    Int_t CircleRunNumber, CircleEventNumber;

    // SetBranchAddress to store information about particles gothrough Circle
    // Particle Info
    ChainForInput[9]->SetBranchAddress("POSITIONX[mm]", &CirclePositionX);
    ChainForInput[9]->SetBranchAddress("POSITIONY[mm]", &CirclePositionY);
    ChainForInput[9]->SetBranchAddress("MOMENTUMX[GeV/c]", &CircleMomentumX);
    ChainForInput[9]->SetBranchAddress("MOMENTUMY[GeV/c]", &CircleMomentumY);
    ChainForInput[9]->SetBranchAddress("MOMENTUMZ[GeV/c]", &CircleMomentumZ);
    ChainForInput[9]->SetBranchAddress("ENERGY[GeV]", &CircleEnergy);
    ChainForInput[9]->SetBranchAddress("OPENERGY[GeV]", &CircleOEnergy);
    ChainForInput[9]->SetBranchAddress("NAME", &CircleName);
    ChainForInput[9]->SetBranchAddress("ORIGINALPARTICLE", &CircleOName);
    ChainForInput[9]->SetBranchAddress("RunNumber", &CircleRunNumber);
    ChainForInput[9]->SetBranchAddress("EventNumber", &CircleEventNumber);


    Double_t GPionPositionX, GPionPositionY, GPionP0MomentumX, GPionP0MomentumY, GPionP0MomentumZ, GPionMomentumX, GPionMomentumY, GPionMomentumZ, GPionP0Energy, GPionEnergy, GPionOEnergy;
    Int_t GPionTrackID, GPionTower;
    Int_t GPionRunNumber, GPionEventNumber;


    // SetBranchAddress to store information about particles gothrough GPion
    // Particle Info
    ChainForInput[10]->SetBranchAddress("POSITIONX[mm]", &GPionPositionX);
    ChainForInput[10]->SetBranchAddress("POSITIONY[mm]", &GPionPositionY);
    ChainForInput[10]->SetBranchAddress("MOMENTUMX[GeV/c]", &GPionMomentumX);
    ChainForInput[10]->SetBranchAddress("MOMENTUMY[GeV/c]", &GPionMomentumY);
    ChainForInput[10]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GPionMomentumZ);
    ChainForInput[10]->SetBranchAddress("ENERGY[GeV]", &GPionEnergy);
    ChainForInput[10]->SetBranchAddress("PIONMOMENTUMX", &GPionP0MomentumX);
    ChainForInput[10]->SetBranchAddress("PIONMOMENTUMY", &GPionP0MomentumY);
    ChainForInput[10]->SetBranchAddress("PIONMOMENTUMZ", &GPionP0MomentumZ);
    ChainForInput[10]->SetBranchAddress("PIONENERGY[GeV]", &GPionP0Energy);
    ChainForInput[10]->SetBranchAddress("TOWERID", &GPionTower);
    ChainForInput[10]->SetBranchAddress("TrackID", &GPionTrackID);
    ChainForInput[10]->SetBranchAddress("RunNumber", &GPionRunNumber);
    ChainForInput[10]->SetBranchAddress("EventNumber", &GPionEventNumber);


    Double_t GNeutronPositionX, GNeutronPositionY, GNeutronMomentumX, GNeutronMomentumY, GNeutronMomentumZ, GNeutronEnergy;
    Int_t GNeutronTrackID, GNeutronTower;
    Int_t GNeutronRunNumber, GNeutronEventNumber;

    // SetBranchAddress to store information about particles gothrough GNeutron
    // Particle Info
    ChainForInput[11]->SetBranchAddress("POSITIONX[mm]", &GNeutronPositionX);
    ChainForInput[11]->SetBranchAddress("POSITIONY[mm]", &GNeutronPositionY);
    ChainForInput[11]->SetBranchAddress("MOMENTUMX[GeV/c]", &GNeutronMomentumX);
    ChainForInput[11]->SetBranchAddress("MOMENTUMY[GeV/c]", &GNeutronMomentumY);
    ChainForInput[11]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GNeutronMomentumZ);
    ChainForInput[11]->SetBranchAddress("ENERGY[GeV]", &GNeutronEnergy);
    ChainForInput[11]->SetBranchAddress("TrackID", &GNeutronTrackID);
    ChainForInput[11]->SetBranchAddress("RunNumber", &GNeutronRunNumber);
    ChainForInput[11]->SetBranchAddress("EventNumber", &GNeutronEventNumber);


    Double_t SPionPositionX, SPionPositionY, SPionVertexX, SPionVertexY, SPionVertexZ, SPionMomentumX, SPionMomentumY, SPionMomentumZ, SPionP0MomentumX, SPionP0MomentumY, SPionP0MomentumZ, SPionP0Energy, SPionEnergy, SPionOEnergy;
    Int_t SPionTrackID, SPionTower;
    Int_t SPionRunNumber, SPionEventNumber;

    // SetBranchAddress to store information about particles gothrough SPion
    // Particle Info
    ChainForInput[12]->SetBranchAddress("POSITIONX[mm]", &SPionPositionX);
    ChainForInput[12]->SetBranchAddress("POSITIONY[mm]", &SPionPositionY);
    ChainForInput[12]->SetBranchAddress("MOMENTUMX[GeV/c]", &SPionMomentumX);
    ChainForInput[12]->SetBranchAddress("MOMENTUMY[GeV/c]", &SPionMomentumY);
    ChainForInput[12]->SetBranchAddress("MOMENTUMZ[GeV/c]", &SPionMomentumZ);
    ChainForInput[12]->SetBranchAddress("ENERGY[GeV]", &SPionEnergy);
    ChainForInput[12]->SetBranchAddress("VPOSITIONX[mm]", &SPionVertexX);
    ChainForInput[12]->SetBranchAddress("VPOSITIONY[mm]", &SPionVertexY);
    ChainForInput[12]->SetBranchAddress("VPOSITIONZ[mm]", &SPionVertexZ);
    ChainForInput[12]->SetBranchAddress("PIONMOMENTUMX", &SPionP0MomentumX);
    ChainForInput[12]->SetBranchAddress("PIONMOMENTUMY", &SPionP0MomentumY);
    ChainForInput[12]->SetBranchAddress("PIONMOMENTUMZ", &SPionP0MomentumZ);
    ChainForInput[12]->SetBranchAddress("PIONENERGY[GeV]", &SPionP0Energy);
    ChainForInput[12]->SetBranchAddress("TOWERID", &SPionTower);
    ChainForInput[12]->SetBranchAddress("TrackID", &SPionTrackID);
    ChainForInput[12]->SetBranchAddress("RunNumber", &SPionRunNumber);
    ChainForInput[12]->SetBranchAddress("EventNumber", &SPionEventNumber);


    Double_t SNeutronPositionX, SNeutronPositionY, SNeutronMomentumX, SNeutronMomentumY, SNeutronMomentumZ, SNeutronNEnergy, SNeutronEnergy;
    Int_t SNeutronTrackID, SNeutronTower;
    Int_t SNeutronRunNumber, SNeutronEventNumber;

    // SetBranchAddress to store information about particles gothrough SNeutron
    // Particle Info
    ChainForInput[13]->SetBranchAddress("POSITIONX[mm]", &SNeutronPositionX);
    ChainForInput[13]->SetBranchAddress("POSITIONY[mm]", &SNeutronPositionY);
    ChainForInput[13]->SetBranchAddress("MOMENTUMX[GeV/c]", &SNeutronMomentumX);
    ChainForInput[13]->SetBranchAddress("MOMENTUMY[GeV/c]", &SNeutronMomentumY);
    ChainForInput[13]->SetBranchAddress("MOMENTUMZ[GeV/c]", &SNeutronMomentumZ);
    ChainForInput[13]->SetBranchAddress("ENERGY[GeV]", &SNeutronEnergy);
    ChainForInput[13]->SetBranchAddress("NEUTRONENERGY[GeV]", &SNeutronNEnergy);
    ChainForInput[13]->SetBranchAddress("TrackID", &SNeutronTrackID);
    ChainForInput[13]->SetBranchAddress("RunNumber", &SNeutronRunNumber);
    ChainForInput[13]->SetBranchAddress("EventNumber", &SNeutronEventNumber);




    Int_t spin, RunNumberSpin, EventNumberSpin;

    // SetBranchAddress to store information about spinpattern
    // 
    ChainForInput[14]->SetBranchAddress("SpinPattern", &spin);
    ChainForInput[14]->SetBranchAddress("RunNumber", &RunNumberSpin);
    ChainForInput[14]->SetBranchAddress("EventNumber", &EventNumberSpin);


    Int_t TotalNEvent[15];

    for (int i = 0; i < 15; i++) 
    {
        BuildIndex(ChainForInput[i], TotalNEvent[i]);
    }

    Int_t index, loopRunNumber, loopEventNumber;
    Int_t iTreeEntry=0;
    Int_t offsetEntry[15] = {0};

    OutputFile = new TFile(OutputFileName, "RECREATE");
    TreeInOutputFile = new TTree("LHCfEvents","Tree of RHICfEvent");
    TreeInOutputFile    ->  SetMaxTreeSize(100000000);
    TreeInOutputFile  ->  Branch("Events","LHCfEvent",&RHICfEvents);

    TH2D *arm1hitmap[2][4];
    TH2D *smdhitmap;
    TH2D *zdcghosthitmap;
    for (int j = 0; j < 2; j++) 
    {
        for (int i = 0; i < 4; i++) 
        {
            TString tmpst="hitmap"+to_string(j)+to_string(i);
            arm1hitmap[j][i] = new TH2D(tmpst,"a", 200, -15, 15, 200, -15, 15);
        }
    }

    smdhitmap = new TH2D("smdhitmap","a", 200, -15, 15, 200, -15, 15);
    zdcghosthitmap = new TH2D("zdcghosthitmap","a", 200, -15, 15, 200, -15, 15);

    for (Int_t iEntry = 0; iEntry < TotalNEvent[0]; iEntry++) 
    //Junsang****for (Int_t iEntry = 0; iEntry < 1000; iEntry++) 
    {
        if(iEntry%5000 == 0) 
        {
            cout << iEntry << endl;
            system("date");
        }
        
        ChainForInput[0]->GetEntry(iEntry);
        ChainForInput[1]->GetEntry(iEntry);
        ChainForInput[2]->GetEntry(iEntry);
        ChainForInput[4]->GetEntry(iEntry);
        ChainForInput[5]->GetEntry(iEntry);
        RHICfEvents->Clear();
        fParticles->Clear();
        fFC->Clear();
        fZDC->Clear();
        //Junsang****fBBC->Clear();




        loopRunNumber = RUN;
        loopEventNumber = EVENT;

        //Junsang****cout << RUN << ":" << EVENT << endl;
        Cal2->run = RUN;
        Cal2->gnumber = EVENT;
        fZDC->run = RUN;
        fZDC->number = EVENT;
        fFC->run = RUN;
        fFC->number = EVENT;
        fParticles->SetRunNumber(RUN);
        fParticles->SetEventNumber(EVENT);



        // Conversion ARM1 response
        for (int i = 0; i < 16; i++) 
        {
            (Cal2->cal)[0][i] = TSGSOPLE[i];
            (Cal2->cal)[1][i] = TLGSOPLE[i];
        }
        //Junsang****if(Cal2->calsum(1)>=135 || Cal2->calsum(0)>=135)
        //Junsang****{
        //Junsang****TreeInOutputFile->GetEntry(iTreeEntry);
        for (int iDepth = 0; iDepth < 4; iDepth++) 
        {
            Double_t tmpx, tmpy, tmptotalx, tmptotaly, tmppartx, tmpparty;
            // Small tower & arm1hitmap
            tmppartx = 0;
            tmpparty = 0;
            tmptotalx = 0;
            tmptotaly = 0;
            tmpx=0;
            tmpy=0;
            for (int iCH = 0; iCH < 20; iCH++) 
            {
                tmptotalx += TSGSOBL[iDepth][iCH];
                tmptotaly += TSGSOBR[iDepth][iCH];
                tmppartx += (iCH-9.5)*TLGSOBL[iDepth][iCH];
                tmpparty += (iCH-9.5)*TLGSOBR[iDepth][iCH];
                (Cal2->scifi0)[iDepth][0][iCH] = (Double_t)TLGSOBL[iDepth][iCH];
                (Cal2->scifi0)[iDepth][1][iCH] = (Double_t)TLGSOBR[iDepth][iCH];
            }
            tmpx  = tmppartx/tmptotalx;
            tmpy  = tmpparty/tmptotaly;
            if(Cal2->calsum(1)>=135 || Cal2->calsum(0)>=135) arm1hitmap[0][iDepth]->Fill(tmpx,tmpy);
            // Large tower & arm1hitmap
            tmppartx = 0;
            tmpparty = 0;
            tmptotalx = 0;
            tmptotaly = 0;
            tmpx=0;
            tmpy=0;
            for (int iCH = 0; iCH < 40; iCH++) 
            {
                tmptotalx += TLGSOBL[iDepth][iCH];
                tmptotaly += TLGSOBR[iDepth][iCH];
                tmppartx += (iCH-19.5)*TLGSOBL[iDepth][iCH];
                tmpparty += (iCH-19.5)*TLGSOBR[iDepth][iCH];
                (Cal2->scifi1)[iDepth][0][iCH] = TLGSOBL[iDepth][iCH];
                (Cal2->scifi1)[iDepth][1][iCH] = TLGSOBR[iDepth][iCH];
            }
            tmpx  = tmppartx/tmptotalx;
            tmpy  = tmpparty/tmptotaly;
            if(Cal2->calsum(1)>=135 || Cal2->calsum(0)>=135) arm1hitmap[1][iDepth]->Fill(tmpx,tmpy);
        }
        //Junsang****Flag->SetFlag(Cal2);

        // Conversion ZDC response
        for (int iZDC = 0; iZDC < 3; iZDC++)
        {
            (fZDC->ZDCdE)[iZDC] = ZDCPMMA[iZDC];
            (fZDC->ZDCNOP)[iZDC] = ZDCNOP[iZDC];
        }
        // Conversion SMD response
        Double_t tmpx, tmpy, tmptotalx, tmptotaly, tmppartx, tmpparty;
        tmppartx = 0;
        tmptotalx = 0;
        tmpx=0;
        for (int j = 0; j < 7; j++)
        {

            (fZDC->SMDHdE)[j] = SMDH[j];
            (fZDC->SMDHNOP)[j] = SMDHNOP[j];
            tmptotalx += (fZDC->SMDHdE)[j];
            tmppartx += (fZDC->SMDHdE)[j]*(1.5*j-4.5);
            //Junsang****tmptotalx += (fZDC->SMDHNOP)[j];
            //Junsang****tmppartx += (fZDC->SMDNOP)[j]*(1.5*j-4.5)
        }
        tmpparty = 0;
        tmptotaly = 0;
        tmpy=0;
        for (int j = 0; j < 8; j++)
        {
            (fZDC->SMDVdE)[j] = SMDV[j];
            (fZDC->SMDVNOP)[j] = SMDVNOP[j];
            tmptotaly += (fZDC->SMDVdE)[j];
            tmpparty += (fZDC->SMDVdE)[j]*(2.0*j-7);
        }
        tmpx    =   tmppartx/tmptotalx;
        tmpy    =   tmpparty/tmptotaly;
        if(tmptotaly>10 && tmptotalx>10) smdhitmap->Fill(tmpx,tmpy);


        // Frontcounter information 
        fFC->FCdE[0] = TSFCDE;
        fFC->FCdE[1] = TLFCDE;
        fFC->FCNOP[0] = TSFCNOP;
        fFC->FCNOP[1] = TLFCNOP;




        // Storing particle information
        // Particle information at first WPlate
        TString tmpstring;
        tmpstring = "RunNumber==" + to_string(loopRunNumber) + " && EventNumber==" + to_string(loopEventNumber);
        Int_t keyNum = 0;
        if(ChainForInput[3]->GetEntries(tmpstring))
        {
            for (Int_t iWPlate = offsetEntry[3]; iWPlate < offsetEntry[3]+(ChainForInput[3]->GetEntries(tmpstring)); iWPlate++) 
            {
                ChainForInput[3]->GetEntry(iWPlate);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToWPlate(keyNum);
                TVector3 tmpvec(WPositionX, WPositionY, WPositionZ);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(WMomentumX, WMomentumY, WMomentumZ, WEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec=TLorentzVector(0, 0, 0, WOEnergy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring(WName);
                fSimP->SetName(tmpstring);
                tmpstring = WOName;
                fSimP->SetOriginalPName(tmpstring);
                keyNum++;
            }
            //Junsang****(fParticles->GetWPlate())->Clear("C");
        }
        offsetEntry[3] = offsetEntry[3] + (ChainForInput[3]->GetEntries(tmpstring));

        // Particle information at ZDC ghost
        keyNum = 0;
        if(ChainForInput[6]->GetEntries(tmpstring))
        {
            for (Int_t iZDCGhost = offsetEntry[6]; iZDCGhost < offsetEntry[6]+(ChainForInput[6]->GetEntries(tmpstring)); iZDCGhost++) 
            {
                ChainForInput[6]->GetEntry(iZDCGhost);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToZDCGhost(keyNum);
                TVector3 tmpvec(ZDCGhostPositionX, ZDCGhostPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(ZDCGhostMomentumX, ZDCGhostMomentumY, ZDCGhostMomentumZ, ZDCGhostEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec=TLorentzVector(0, 0, 0, ZDCGhostOEnergy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring(ZDCGhostName);
                fSimP->SetName(tmpstring);
                tmpstring = ZDCGhostOName;
                fSimP->SetOriginalPName(tmpstring);
                keyNum++;
            }
            //Junsang****(fParticles->GetZDCGhost())->Clear("C");
        }
        offsetEntry[6] = offsetEntry[6] + (ChainForInput[6]->GetEntries(tmpstring));

        // Particle information at IP
        keyNum = 0;
        if(ChainForInput[7]->GetEntries(tmpstring))
        {
            for (Int_t iIP = offsetEntry[7]; iIP < offsetEntry[7]+(ChainForInput[7]->GetEntries(tmpstring)); iIP++) 
            {
                ChainForInput[7]->GetEntry(iIP);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToIP(keyNum);
                TVector3 tmpvec(IPPositionX, IPPositionY, IPPositionZ);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(IPMomentumX, IPMomentumY, IPMomentumZ, IPEnergy);
                fSimP->Set4Momentum(tmp4vec);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring(IPName);
                fSimP->SetName(tmpstring);
                fSimP->SetOriginalPName(tmpstring);
                keyNum++;
            }
            //Junsang****(fParticles->GetIP()).Clear("C");
        }
        offsetEntry[7] = offsetEntry[7] + (ChainForInput[7]->GetEntries(tmpstring));

        // Particle information at Ghost
        keyNum = 0;
        if(ChainForInput[8]->GetEntries(tmpstring))
        {
            for (Int_t iGhost = offsetEntry[8]; iGhost < offsetEntry[8]+(ChainForInput[8]->GetEntries(tmpstring)); iGhost++) 
            {
                ChainForInput[8]->GetEntry(iGhost);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToGhost(keyNum);
                TVector3 tmpvec(GhostPositionX, GhostPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(GhostMomentumX, GhostMomentumY, GhostMomentumZ, GhostEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec=TLorentzVector(0, 0, 0, GhostOEnergy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring(GhostName);
                fSimP->SetName(tmpstring);
                tmpstring = GhostOName;
                fSimP->SetOriginalPName(tmpstring);
                keyNum++;
            }
            //Junsang****(fParticles->GetGhost())->Clear("C");
        }
        offsetEntry[8] = offsetEntry[8] + (ChainForInput[8]->GetEntries(tmpstring));

        // Particle information at Circle
        keyNum = 0;
        if(ChainForInput[9]->GetEntries(tmpstring))
        {
            for (Int_t iCircle = offsetEntry[9]; iCircle < offsetEntry[9]+(ChainForInput[9]->GetEntries(tmpstring)); iCircle++) 
            {
                ChainForInput[9]->GetEntry(iCircle);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToCircle(keyNum);
                TVector3 tmpvec(CirclePositionX, CirclePositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(CircleMomentumX, CircleMomentumY, CircleMomentumZ, CircleEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec=TLorentzVector(0, 0, 0, CircleOEnergy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring(CircleName);
                fSimP->SetName(tmpstring);
                tmpstring = CircleOName;
                fSimP->SetOriginalPName(tmpstring);
                keyNum++;
            }
            //Junsang****(fParticles->GetCircle())->Clear("C");
        }
        offsetEntry[9] = offsetEntry[9] + (ChainForInput[9]->GetEntries(tmpstring));

        // Particle information at Ghost when Pion produced
        keyNum = 0;
        if(ChainForInput[10]->GetEntries(tmpstring))
        {
            for (Int_t iGPion = offsetEntry[10]; iGPion < offsetEntry[10]+(ChainForInput[10]->GetEntries(tmpstring)); iGPion++) 
            {
                ChainForInput[10]->GetEntry(iGPion);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToP0Ghost(keyNum);
                TVector3 tmpvec(GPionPositionX, GPionPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(GPionMomentumX, GPionMomentumY, GPionMomentumZ, GPionEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec = TLorentzVector(GPionP0MomentumX, GPionP0MomentumY, GPionP0MomentumZ, GPionP0Energy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring("gamma");
                fSimP->SetName(tmpstring);
                fSimP->SetOriginalPName("pi0");
                fSimP->SetTower(GPionTower);
                fSimP->SetTrackID(GPionTrackID);
                keyNum++;
            }
            //Junsang****(fParticles->GetP0Ghost())->Clear("C");
        }
        offsetEntry[10] = offsetEntry[10] + (ChainForInput[10]->GetEntries(tmpstring));

        // Particle informaiton at Ghost when neutron produced
        keyNum = 0;
        if(ChainForInput[11]->GetEntries(tmpstring))
        {
            for (Int_t iGNeutron = offsetEntry[11]; iGNeutron < offsetEntry[11]+(ChainForInput[11]->GetEntries(tmpstring)); iGNeutron++) 
            {
                ChainForInput[11]->GetEntry(iGNeutron);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToNGhost(keyNum);
                TVector3 tmpvec(GNeutronPositionX, GNeutronPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(GNeutronMomentumX, GNeutronMomentumY, GNeutronMomentumZ, GNeutronEnergy);
                fSimP->Set4Momentum(tmp4vec);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring("neutron");
                fSimP->SetName(tmpstring);
                fSimP->SetOriginalPName(tmpstring);
                fSimP->SetTrackID(GNeutronTrackID);
            }
            //Junsang****(fParticles->GetNGhost())->Clear("C");
        }
        offsetEntry[11] = offsetEntry[11] + (ChainForInput[11]->GetEntries(tmpstring));

        // Gamma information at WPlate when pion produced
        keyNum = 0;
        if(ChainForInput[12]->GetEntries(tmpstring))
        {
            for (Int_t iSPion = offsetEntry[12]; iSPion < offsetEntry[12]+(ChainForInput[12]->GetEntries(tmpstring)); iSPion++) 
            {
                ChainForInput[12]->GetEntry(iSPion);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToP0Signal(keyNum);
                TVector3 tmpvec(SPionPositionX, SPionPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(SPionMomentumX, SPionMomentumY, SPionMomentumZ, SPionEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec = TLorentzVector(SPionP0MomentumX, SPionP0MomentumY, SPionP0MomentumZ, SPionP0Energy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring("gamma");
                fSimP->SetName(tmpstring);
                fSimP->SetOriginalPName("pi0");
                fSimP->SetTower(SPionTower);
                fSimP->SetTrackID(SPionTrackID);
                keyNum++;
            }
            //Junsang****(fParticles->GetP0Signal())->Clear("C");
        }
        offsetEntry[12] = offsetEntry[12] + (ChainForInput[12]->GetEntries(tmpstring));

        // Neutron information at WPlate when neutron produced
        keyNum = 0;
        if(ChainForInput[13]->GetEntries(tmpstring))
        {
            for (Int_t iSNeutron = offsetEntry[13]; iSNeutron < offsetEntry[13]+(ChainForInput[13]->GetEntries(tmpstring)); iSNeutron++) 
            {
                ChainForInput[13]->GetEntry(iSNeutron);
                RHICfSimP *fSimP = (RHICfSimP*)fParticles->AddToNSignal(keyNum);
                TVector3 tmpvec(SNeutronPositionX, SNeutronPositionY, 0);
                fSimP->SetPosition(tmpvec);
                TLorentzVector tmp4vec(SNeutronMomentumX, SNeutronMomentumY, SNeutronMomentumZ, SNeutronEnergy);
                fSimP->Set4Momentum(tmp4vec);
                tmp4vec = TLorentzVector(0, 0, 0, SNeutronNEnergy);
                fSimP->SetOriginalP4Momentum(tmp4vec);
                TString tmpstring("neutron");
                fSimP->SetName(tmpstring);
                fSimP->SetOriginalPName(tmpstring);
                fSimP->SetTrackID(SNeutronTrackID);
                keyNum++;
            }
            //Junsang****(fParticles->GetNSignal())->Clear("C");
        }
        offsetEntry[13] = offsetEntry[13] + (ChainForInput[13]->GetEntries(tmpstring));



        if(ChainForInput[14]->GetEntries(tmpstring))
        {
            // Spin information 
            ChainForInput[14]->GetEntry(iEntry);
            fParticles->SetSpin(spin);
        }

        RHICfEvents->Add(Cal2);
        RHICfEvents->Add(fZDC);
        RHICfEvents->Add(fFC);
        RHICfEvents->Add(fParticles);
        TreeInOutputFile->Fill();
        iTreeEntry++;
        //Junsang****}// if(Cal2->calsum(1) || Cal2->calsum(0))

    }

    OutputFile -> Write();
    OutputFile -> Close();

    for (int i = 0; i < 15; i++) 
    {
        delete ChainForInput[i];
    }
    cout << "END" << endl;
    return 0;
}

