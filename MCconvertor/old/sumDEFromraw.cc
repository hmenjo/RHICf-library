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

bool IsAboveThreshold(Double_t kDE[])
{
    for (int i = 1; i < 15; i++)
    {
        if (kDE[i-1]>=45 && kDE[i]>=45 && kDE[i+1]>=45)
        {
            return true;
        }
    }
    return false;
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

    ChainForInput[13]->BuildIndex("RunNumber", "EventNumber");

    FileManager::GetInstance()->SetFileName(argv[2]);

    // Related output
    OutputFileName = FileManager::GetInstance()->GetPathForANALYSIS()+"/"+FileManager::GetInstance()->GetFileName()+".root";


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


    //Junsang****Double_t TSFCDE, TLFCDE;
    //Junsang****Int_t TSFCNOP, TLFCNOP;
//Junsang****
    //Junsang****// SetBranchAddress to store deposit energy for FrontCounter
    //Junsang****// Scintillator
    //Junsang****ChainForInput[2]->SetBranchAddress("TSFCDE", &TSFCDE);
    //Junsang****ChainForInput[2]->SetBranchAddress("TLFCDE", &TLFCDE);
    //Junsang****ChainForInput[2]->SetBranchAddress("TSFCNOP", &TSFCNOP);
    //Junsang****ChainForInput[2]->SetBranchAddress("TLFCNOP", &TLFCNOP);
//Junsang****
//Junsang****
    //Junsang****Double_t WPositionX, WPositionY, WPositionZ, WMomentumX, WMomentumY, WMomentumZ, WEnergy, WOEnergy;
    //Junsang****Char_t WName[10], WOName[10];
    //Junsang****Int_t WRunNumber, WEventNumber;
//Junsang****
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough WPlate
    //Junsang****// Particle Info
    //Junsang****ChainForInput[3]->SetBranchAddress("POSITIONX[mm]", &WPositionX);
    //Junsang****ChainForInput[3]->SetBranchAddress("POSITIONY[mm]", &WPositionY);
    //Junsang****ChainForInput[3]->SetBranchAddress("POSITIONZ[mm]", &WPositionZ);
    //Junsang****ChainForInput[3]->SetBranchAddress("MOMENTUMX[GeV/c]", &WMomentumX);
    //Junsang****ChainForInput[3]->SetBranchAddress("MOMENTUMY[GeV/c]", &WMomentumY);
    //Junsang****ChainForInput[3]->SetBranchAddress("MOMENTUMZ[GeV/c]", &WMomentumZ);
    //Junsang****ChainForInput[3]->SetBranchAddress("ENERGY[GeV]", &WEnergy);
    //Junsang****ChainForInput[3]->SetBranchAddress("OPENERGY[GeV]", &WOEnergy);
    //Junsang****ChainForInput[3]->SetBranchAddress("NAME", &WName);
    //Junsang****ChainForInput[3]->SetBranchAddress("ORIGINALPARTICLE", &WOName);
    //Junsang****ChainForInput[3]->SetBranchAddress("RunNumber", &WRunNumber);
    //Junsang****ChainForInput[3]->SetBranchAddress("EventNumber", &WEventNumber);
//Junsang****
//Junsang****
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


    //Junsang****Double_t ZDCGhostPositionX, ZDCGhostPositionY,  ZDCGhostMomentumX, ZDCGhostMomentumY, ZDCGhostMomentumZ, ZDCGhostEnergy, ZDCGhostOEnergy;
    //Junsang****Char_t ZDCGhostName[10], ZDCGhostOName[10];
    //Junsang****Int_t ZDCGhostRunNumber, ZDCGhostEventNumber;
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough ZDCGhostPlate
    //Junsang****// Particle Info
    //Junsang****ChainForInput[6]->SetBranchAddress("POSITIONX[mm]", &ZDCGhostPositionX);
    //Junsang****ChainForInput[6]->SetBranchAddress("POSITIONY[mm]", &ZDCGhostPositionY);
    //Junsang****ChainForInput[6]->SetBranchAddress("MOMENTUMX[GeV/c]", &ZDCGhostMomentumX);
    //Junsang****ChainForInput[6]->SetBranchAddress("MOMENTUMY[GeV/c]", &ZDCGhostMomentumY);
    //Junsang****ChainForInput[6]->SetBranchAddress("MOMENTUMZ[GeV/c]", &ZDCGhostMomentumZ);
    //Junsang****ChainForInput[6]->SetBranchAddress("ENERGY[GeV]", &ZDCGhostEnergy);
    //Junsang****ChainForInput[6]->SetBranchAddress("OPENERGY[GeV]", &ZDCGhostOEnergy);
    //Junsang****ChainForInput[6]->SetBranchAddress("NAME", &ZDCGhostName);
    //Junsang****ChainForInput[6]->SetBranchAddress("ORIGINALPARTICLE", &ZDCGhostOName);
    //Junsang****ChainForInput[6]->SetBranchAddress("RunNumber", &ZDCGhostRunNumber);
    //Junsang****ChainForInput[6]->SetBranchAddress("EventNumber", &ZDCGhostEventNumber);
//Junsang****
//Junsang****
    //Junsang****Double_t IPPositionX, IPPositionY, IPPositionZ, IPMomentumX, IPMomentumY, IPMomentumZ, IPEnergy;
    //Junsang****Char_t IPName[10];
    //Junsang****Int_t IPRunNumber, IPEventNumber;
//Junsang****
    //Junsang****// SetBranchAddress to store information about initial particles 
    //Junsang****// Particle Info
    //Junsang****ChainForInput[7]->SetBranchAddress("POSITIONX[mm]", &IPPositionX);
    //Junsang****ChainForInput[7]->SetBranchAddress("POSITIONY[mm]", &IPPositionY);
    //Junsang****ChainForInput[7]->SetBranchAddress("POSITIONZ[mm]", &IPPositionZ);
    //Junsang****ChainForInput[7]->SetBranchAddress("MOMENTUMX[GeV/c]", &IPMomentumX);
    //Junsang****ChainForInput[7]->SetBranchAddress("MOMENTUMY[GeV/c]", &IPMomentumY);
    //Junsang****ChainForInput[7]->SetBranchAddress("MOMENTUMZ[GeV/c]", &IPMomentumZ);
    //Junsang****ChainForInput[7]->SetBranchAddress("ENERGY[GeV]", &IPEnergy);
    //Junsang****ChainForInput[7]->SetBranchAddress("NAME", &IPName);
    //Junsang****ChainForInput[7]->SetBranchAddress("RunNumber", &IPRunNumber);
    //Junsang****ChainForInput[7]->SetBranchAddress("EventNumber", &IPEventNumber);
//Junsang****
//Junsang****
    //Junsang****Double_t GhostPositionX, GhostPositionY, GhostMomentumX, GhostMomentumY, GhostMomentumZ, GhostEnergy, GhostOEnergy;
    //Junsang****Char_t GhostName[10], GhostOName[10];
    //Junsang****Int_t GhostRunNumber, GhostEventNumber;
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough Ghost
    //Junsang****// Particle Info
    //Junsang****ChainForInput[8]->SetBranchAddress("POSITIONX[mm]", &GhostPositionX);
    //Junsang****ChainForInput[8]->SetBranchAddress("POSITIONY[mm]", &GhostPositionY);
    //Junsang****ChainForInput[8]->SetBranchAddress("MOMENTUMX[GeV/c]", &GhostMomentumX);
    //Junsang****ChainForInput[8]->SetBranchAddress("MOMENTUMY[GeV/c]", &GhostMomentumY);
    //Junsang****ChainForInput[8]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GhostMomentumZ);
    //Junsang****ChainForInput[8]->SetBranchAddress("ENERGY[GeV]", &GhostEnergy);
    //Junsang****ChainForInput[8]->SetBranchAddress("OPENERGY[GeV]", &GhostOEnergy);
    //Junsang****ChainForInput[8]->SetBranchAddress("NAME", &GhostName);
    //Junsang****ChainForInput[8]->SetBranchAddress("ORIGINALPARTICLE", &GhostOName);
    //Junsang****ChainForInput[8]->SetBranchAddress("RunNumber", &GhostRunNumber);
    //Junsang****ChainForInput[8]->SetBranchAddress("EventNumber", &GhostEventNumber);
//Junsang****
//Junsang****
    //Junsang****Double_t CirclePositionX, CirclePositionY, CircleMomentumX, CircleMomentumY, CircleMomentumZ, CircleEnergy, CircleOEnergy;
    //Junsang****Char_t CircleName[10], CircleOName[10];
    //Junsang****Int_t CircleRunNumber, CircleEventNumber;
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough Circle
    //Junsang****// Particle Info
    //Junsang****ChainForInput[9]->SetBranchAddress("POSITIONX[mm]", &CirclePositionX);
    //Junsang****ChainForInput[9]->SetBranchAddress("POSITIONY[mm]", &CirclePositionY);
    //Junsang****ChainForInput[9]->SetBranchAddress("MOMENTUMX[GeV/c]", &CircleMomentumX);
    //Junsang****ChainForInput[9]->SetBranchAddress("MOMENTUMY[GeV/c]", &CircleMomentumY);
    //Junsang****ChainForInput[9]->SetBranchAddress("MOMENTUMZ[GeV/c]", &CircleMomentumZ);
    //Junsang****ChainForInput[9]->SetBranchAddress("ENERGY[GeV]", &CircleEnergy);
    //Junsang****ChainForInput[9]->SetBranchAddress("OPENERGY[GeV]", &CircleOEnergy);
    //Junsang****ChainForInput[9]->SetBranchAddress("NAME", &CircleName);
    //Junsang****ChainForInput[9]->SetBranchAddress("ORIGINALPARTICLE", &CircleOName);
    //Junsang****ChainForInput[9]->SetBranchAddress("RunNumber", &CircleRunNumber);
    //Junsang****ChainForInput[9]->SetBranchAddress("EventNumber", &CircleEventNumber);
//Junsang****
//Junsang****
    //Junsang****Double_t GPionPositionX, GPionPositionY, GPionP0MomentumX, GPionP0MomentumY, GPionP0MomentumZ, GPionMomentumX, GPionMomentumY, GPionMomentumZ, GPionP0Energy, GPionEnergy, GPionOEnergy;
    //Junsang****Int_t GPionTrackID, GPionTower;
    //Junsang****Int_t GPionRunNumber, GPionEventNumber;
//Junsang****
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough GPion
    //Junsang****// Particle Info
    //Junsang****ChainForInput[10]->SetBranchAddress("POSITIONX[mm]", &GPionPositionX);
    //Junsang****ChainForInput[10]->SetBranchAddress("POSITIONY[mm]", &GPionPositionY);
    //Junsang****ChainForInput[10]->SetBranchAddress("MOMENTUMX[GeV/c]", &GPionMomentumX);
    //Junsang****ChainForInput[10]->SetBranchAddress("MOMENTUMY[GeV/c]", &GPionMomentumY);
    //Junsang****ChainForInput[10]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GPionMomentumZ);
    //Junsang****ChainForInput[10]->SetBranchAddress("ENERGY[GeV]", &GPionEnergy);
    //Junsang****ChainForInput[10]->SetBranchAddress("PIONMOMENTUMX", &GPionP0MomentumX);
    //Junsang****ChainForInput[10]->SetBranchAddress("PIONMOMENTUMY", &GPionP0MomentumY);
    //Junsang****ChainForInput[10]->SetBranchAddress("PIONMOMENTUMZ", &GPionP0MomentumZ);
    //Junsang****ChainForInput[10]->SetBranchAddress("PIONENERGY[GeV]", &GPionP0Energy);
    //Junsang****ChainForInput[10]->SetBranchAddress("TOWERID", &GPionTower);
    //Junsang****ChainForInput[10]->SetBranchAddress("TrackID", &GPionTrackID);
    //Junsang****ChainForInput[10]->SetBranchAddress("RunNumber", &GPionRunNumber);
    //Junsang****ChainForInput[10]->SetBranchAddress("EventNumber", &GPionEventNumber);
//Junsang****
//Junsang****
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
//Junsang****
//Junsang****
    //Junsang****Double_t SPionPositionX, SPionPositionY, SPionVertexX, SPionVertexY, SPionVertexZ, SPionMomentumX, SPionMomentumY, SPionMomentumZ, SPionP0MomentumX, SPionP0MomentumY, SPionP0MomentumZ, SPionP0Energy, SPionEnergy, SPionOEnergy;
    //Junsang****Int_t SPionTrackID, SPionTower;
    //Junsang****Int_t SPionRunNumber, SPionEventNumber;
//Junsang****
    //Junsang****// SetBranchAddress to store information about particles gothrough SPion
    //Junsang****// Particle Info
    //Junsang****ChainForInput[12]->SetBranchAddress("POSITIONX[mm]", &SPionPositionX);
    //Junsang****ChainForInput[12]->SetBranchAddress("POSITIONY[mm]", &SPionPositionY);
    //Junsang****ChainForInput[12]->SetBranchAddress("MOMENTUMX[GeV/c]", &SPionMomentumX);
    //Junsang****ChainForInput[12]->SetBranchAddress("MOMENTUMY[GeV/c]", &SPionMomentumY);
    //Junsang****ChainForInput[12]->SetBranchAddress("MOMENTUMZ[GeV/c]", &SPionMomentumZ);
    //Junsang****ChainForInput[12]->SetBranchAddress("ENERGY[GeV]", &SPionEnergy);
    //Junsang****ChainForInput[12]->SetBranchAddress("VPOSITIONX[mm]", &SPionVertexX);
    //Junsang****ChainForInput[12]->SetBranchAddress("VPOSITIONY[mm]", &SPionVertexY);
    //Junsang****ChainForInput[12]->SetBranchAddress("VPOSITIONZ[mm]", &SPionVertexZ);
    //Junsang****ChainForInput[12]->SetBranchAddress("PIONMOMENTUMX", &SPionP0MomentumX);
    //Junsang****ChainForInput[12]->SetBranchAddress("PIONMOMENTUMY", &SPionP0MomentumY);
    //Junsang****ChainForInput[12]->SetBranchAddress("PIONMOMENTUMZ", &SPionP0MomentumZ);
    //Junsang****ChainForInput[12]->SetBranchAddress("PIONENERGY[GeV]", &SPionP0Energy);
    //Junsang****ChainForInput[12]->SetBranchAddress("TOWERID", &SPionTower);
    //Junsang****ChainForInput[12]->SetBranchAddress("TrackID", &SPionTrackID);
    //Junsang****ChainForInput[12]->SetBranchAddress("RunNumber", &SPionRunNumber);
    //Junsang****ChainForInput[12]->SetBranchAddress("EventNumber", &SPionEventNumber);


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




    //Junsang****Int_t spin, RunNumberSpin, EventNumberSpin;
//Junsang****
    //Junsang****// SetBranchAddress to store information about spinpattern
    //Junsang****// 
    //Junsang****ChainForInput[14]->SetBranchAddress("SpinPattern", &spin);
    //Junsang****ChainForInput[14]->SetBranchAddress("RunNumber", &RunNumberSpin);
    //Junsang****ChainForInput[14]->SetBranchAddress("EventNumber", &EventNumberSpin);


    Int_t TotalNEvent[15];

    //Junsang****for (int i = 0; i < 15; i++) 
    //Junsang****{
        //Junsang****BuildIndex(ChainForInput[i], TotalNEvent[i]);
    //Junsang****}


    TotalNEvent[0] = ChainForInput[0]->GetEntries();


    Int_t index, loopRunNumber, loopEventNumber;
    Int_t iTreeEntry=0;
    Int_t offsetEntry[15] = {0};

    OutputFile = new TFile(OutputFileName, "RECREATE");

    TH1D* hist[5];
    TH1D* zdchist[4];
    TH2D* rawhitmap[2];
    TH2D *arm1hitmap[2][4];
    TH2D *smdhitmap;
    hist[0] = new TH1D("TSDE","DEInGSOPLOfTS;DE[MeV];Events#",1000,0.,10000.);
    hist[1] = new TH1D("TLDE","DEInGSOPLOfTL;DE[MeV];Events#",1000,0.,10000.);
    hist[2] = new TH1D("TOTALDE","DEInGSOPL;DE[MeV];Events#",1000,0.,10000.);
    hist[3] = new TH1D("SIGH1D","DEInGSOPL[SIG];DE[MeV];Events#",1000,0.,10000.);
    hist[4] = new TH1D("NOSIG","DEInGSOPL[NOSIG];DE[MeV];Events#",1000,0.,10000.);


    zdchist[0] = new TH1D("ZDC0","DEInZDC0;DE[MeV];Events#",1500,0.,15000.);
    zdchist[1] = new TH1D("ZDC1","DEInZDC1;DE[MeV];Events#",1500,0.,15000.);
    zdchist[2] = new TH1D("ZDC2","DEInZDC2;DE[MeV];Events#",1500,0.,15000.);
    zdchist[3] = new TH1D("ZDCSUM","DEInZDCSUM;DE[MeV];Events#",1500,0.,15000.);


    for (int i = 0; i < 4; i++) 
    {
        TString tmpst1=FileManager::GetInstance()->GetFileName()+"TS"+to_string(i);
        TString tmpst2 = "TS" + to_string(i) + ";X[mm];Y[mm]"; 
        arm1hitmap[0][i] = new TH2D(tmpst1,tmpst2, 200, -10, 10, 200, -10, 10);
    }
    for (int i = 0; i < 4; i++) 
    {
        TString tmpst1=FileManager::GetInstance()->GetFileName()+"TL"+to_string(i);
        TString tmpst2 = "TL" + to_string(i) + ";X[mm];Y[mm]"; 
        arm1hitmap[1][i] = new TH2D(tmpst1,tmpst2, 200, -20, 20, 200, -20, 20);
    }

    rawhitmap[0] = new TH2D("RAWHIT", "RAWHitmap;X[mm];Y[mm]", 200, -40, 40, 460, -100., 130.);
    rawhitmap[1] = new TH2D("SIGHIT", "SIGHitmap;X[mm];Y[mm]", 200, -40, 40, 460, -100., 130.);

    smdhitmap = new TH2D("smdhitmap","a", 200, -5, 5, 200, -15, 15);


    Double_t weight[16] = {0., 0., 1., 1., 1., 1., 1., 1.,
        1., 1., 1., 2., 2., 2., 2., 2.};

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
        ChainForInput[4]->GetEntry(iEntry);
        ChainForInput[5]->GetEntry(iEntry);
        ChainForInput[11]->GetEntry(iEntry);
        ChainForInput[13]->GetEntry(iEntry);



        loopRunNumber = RUN;
        loopEventNumber = EVENT;

        Double_t TotalETS1, TotalETL1;
        TotalETS1 = 0;
        TotalETL1 = 0;
        // Conversion ARM1 response
        for (int i = 0; i < 16; i++) 
        {
            TotalETS1 += weight[i]*TSGSOPLE[i];
            TotalETL1 += weight[i]*TLGSOPLE[i];
        }
        if(IsAboveThreshold(TSGSOPLE) || IsAboveThreshold(TLGSOPLE))
        {
            if(IsAboveThreshold(TSGSOPLE)) hist[0]->Fill(TotalETS1);
            if(IsAboveThreshold(TLGSOPLE)) hist[1]->Fill(TotalETL1);
            hist[2]->Fill(TotalETS1+TotalETL1);
            if(ChainForInput[13]->GetEntryNumberWithIndex(RUN,EVENT) != -1)
            {
                hist[3]->Fill(TotalETS1+TotalETL1);
                rawhitmap[1]->Fill(SNeutronPositionX, SNeutronPositionY);
            }else
            {
                hist[4]->Fill(TotalETS1+TotalETL1);
            }
        }

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
            }
            tmpx  = tmppartx/tmptotalx;
            tmpy  = tmpparty/tmptotaly;
            arm1hitmap[0][iDepth]->Fill(tmpx,tmpy);
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
            }
            tmpx  = tmppartx/tmptotalx;
            tmpy  = tmpparty/tmptotaly;
            arm1hitmap[1][iDepth]->Fill(tmpx,tmpy);
        }

        // Conversion ZDC response
        for (int iZDC = 0; iZDC < 3; iZDC++)
        {
            zdchist[iZDC]->Fill(ZDCPMMA[iZDC]);
        }
        zdchist[3]->Fill(ZDCPMMA[0]+ZDCPMMA[1]+ZDCPMMA[2]);

        // Conversion SMD response
        Double_t tmpx, tmpy, tmptotalx, tmptotaly, tmppartx, tmpparty;
        tmppartx = 0;
        tmptotalx = 0;
        tmpx=0;
        for (int j = 0; j < 7; j++)
        {
            tmptotalx += SMDH[j];
            tmppartx += SMDH[j]*(1.5*(double)j-4.5);
        }

        tmpparty = 0;
        tmptotaly = 0;
        tmpy=0;
        for (int j = 0; j < 8; j++)
        {
            tmptotaly += SMDV[j];
            tmpparty += SMDV[j]*(2.0*(double)j-7);
        }
        tmpx    =   tmppartx/tmptotalx;
        tmpy    =   tmpparty/tmptotaly;
        smdhitmap->Fill(tmpx,tmpy);


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

