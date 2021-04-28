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

int main(int argc, char** argv)
{
    system("date");
    FileManager::GetInstance()->PrepareSavingDirectory();
    // Variables

    TFile* tmpfile;


    TString treename[15] = 
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


    TTree* tmptotaltree[15];
    TTree* tmptree[15];

    TList* tmplist[15];

    for (int i = 0; i < 15; i++) 
    {
        tmplist[i] = new TList;
        tmptotaltree[i] = NULL;
        tmptree[i] = NULL;
    }


    TString OutputFileName;


    FileManager::GetInstance()->SetFileName(argv[2]);

    // Related output
    OutputFileName = FileManager::GetInstance()->GetPathForANALYSIS()+"/"+FileManager::GetInstance()->GetFileName()+".root";




    // IO files
    TFile* OutputFile;

    OutputFile = new TFile(OutputFileName, "RECREATE");
    gDirectory -> pwd();
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

    TString list(argv[1]);

    ifstream myReadFile;
    string tmpstring;
    myReadFile.open(list);
    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile, tmpstring)) 
        {
            //Junsang****array<make_shared<TTree>, 15> tmptree;
            //Junsang****auto tmptree = make_shared<TTree>;
            //Junsang****cout << "start while" << endl;
            //Junsang****cout << tmpstring << endl;
            tmpfile = TFile::Open(tmpstring.c_str());
            for (int i = 0; i < 15; i++) 
            {
                if(i!=2)
                {
                    tmpfile->GetObject(treename[i], tmptree[i]);
                    //Junsang****gDirectory->cd(OutputFileName+":/");
                    //Junsang****cout << "before delete" << endl;
                    //Junsang****gDirectory->pwd();
                    if(tmptree[i]->GetEntries())
                    {
                        if(tmptree[i]!=NULL)
                        {
                            tmplist[i]->Add(tmptree[i]);
                            tmptree[i]->BuildIndex("RunNumber", "EventNumber");
                        }

                        //Junsang****cout << treename[i] << ": " <<  tmptotaltree[i]->GetEntries() << endl;
                        //Junsang****tmplist[i]->Clear();
                        //Junsang****if(buffer!=NULL)
                            //Junsang****delete buffer;
                        //Junsang****if(tmptree[i]!=NULL)
                            //Junsang****delete tmptree[i];
                    }
                }
            }



            Int_t RUN, EVENT;
            Double_t TSGSOPLE[16], TLGSOPLE[16], TSGSOBR[4][20], TLGSOBR[4][40], TSGSOBL[4][20], TLGSOBL[4][40], TOTALE;

            // SetBranchAddress to store deposit energy for ARM1
            // GSOPlate
            for (int ilayer = 0; ilayer < 16; ilayer++) 
            {
                TString tmpstring;
                tmpstring ="TSGSOPLDE" + to_string(ilayer);
                tmptree[0]->SetBranchAddress(tmpstring, &TSGSOPLE[ilayer]);
                tmpstring ="TLGSOPLDE" + to_string(ilayer);
                tmptree[0]->SetBranchAddress(tmpstring, &TLGSOPLE[ilayer]);
            }
            tmptree[0]->SetBranchAddress("TotalEnergy", &TOTALE);
            // GSOBar
            for (int ilayer = 0; ilayer < 4; ilayer++) 
            {
            // 
            for (int iSmall = 0; iSmall < 20; iSmall++) 
            {
            TString tmpstring;
            tmpstring ="TSGSOBRDE" + to_string(ilayer) + to_string(iSmall);
            tmptree[1]->SetBranchAddress(tmpstring, &TSGSOBR[ilayer][iSmall]);
            tmpstring ="TSGSOBLDE" + to_string(ilayer) + to_string(iSmall);
            tmptree[1]->SetBranchAddress(tmpstring, &TSGSOBL[ilayer][iSmall]);
            }
            for (int iLarge = 0; iLarge < 40; iLarge++) 
            {
            TString  tmpstring;
            tmpstring ="TLGSOBRDE" + to_string(ilayer) + to_string(iLarge);
            tmptree[1]->SetBranchAddress(tmpstring, &TLGSOBR[ilayer][iLarge]);
            tmpstring ="TLGSOBLDE" + to_string(ilayer) + to_string(iLarge);
            tmptree[1]->SetBranchAddress(tmpstring, &TLGSOBL[ilayer][iLarge]);
            }
            }

            tmptree[0]->SetBranchAddress("RunNumber", &RUN);
            tmptree[0]->SetBranchAddress("EventNumber", &EVENT);


            Double_t ZDCPMMA[3], SMDV[7], SMDH[8];
            Int_t   ZDCNOP[3], SMDVNOP[7], SMDHNOP[8];

            // SetBranchAddress to store deposit energy for ZDC
            // PMMA
            tmptree[4]->SetBranchAddress("1stPMMADE[MeV]", &ZDCPMMA[0]);
            tmptree[4]->SetBranchAddress("2ndPMMADE[MeV]", &ZDCPMMA[1]);
            tmptree[4]->SetBranchAddress("3rdPMMADE[MeV]", &ZDCPMMA[2]);
            tmptree[4]->SetBranchAddress("1stPMMANOP", &ZDCNOP[0]);
            tmptree[4]->SetBranchAddress("2ndPMMANOP", &ZDCNOP[1]);
            tmptree[4]->SetBranchAddress("3rdPMMANOP", &ZDCNOP[2]);
            // SMD
            for (int ivertical = 0; ivertical < 7; ivertical++) 
            {
                TString tmpstring;
                tmpstring ="SMDVDE" + to_string(ivertical+1) + "[MeV]";
                tmptree[5]->SetBranchAddress(tmpstring, &SMDV[ivertical]);
                tmpstring ="SMDVNOP" + to_string(ivertical+1);
                tmptree[5]->SetBranchAddress(tmpstring, &SMDVNOP[ivertical]);
            }
            for (int ihorizon = 0; ihorizon < 8; ihorizon++) 
            {
                TString tmpstring;
                tmpstring ="SMDHDE" + to_string(ihorizon+1) + "[MeV]";
                tmptree[5]->SetBranchAddress(tmpstring, &SMDH[ihorizon]);
                tmpstring ="SMDHNOP" + to_string(ihorizon+1);
                tmptree[5]->SetBranchAddress(tmpstring, &SMDHNOP[ihorizon]);
            }


            Double_t GhostPositionX, GhostPositionY, GhostMomentumX, GhostMomentumY, GhostMomentumZ, GhostEnergy, GhostOEnergy;
            Char_t GhostName[10], GhostOName[10];
            Int_t GhostRunNumber, GhostEventNumber;

            // SetBranchAddress to store information about particles gothrough Ghost
            // Particle Info
            tmptree[8]->SetBranchAddress("POSITIONX[mm]", &GhostPositionX);
            tmptree[8]->SetBranchAddress("POSITIONY[mm]", &GhostPositionY);
            tmptree[8]->SetBranchAddress("MOMENTUMX[GeV/c]", &GhostMomentumX);
            tmptree[8]->SetBranchAddress("MOMENTUMY[GeV/c]", &GhostMomentumY);
            tmptree[8]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GhostMomentumZ);
            tmptree[8]->SetBranchAddress("ENERGY[GeV]", &GhostEnergy);
            tmptree[8]->SetBranchAddress("OPENERGY[GeV]", &GhostOEnergy);
            tmptree[8]->SetBranchAddress("NAME", &GhostName);
            tmptree[8]->SetBranchAddress("ORIGINALPARTICLE", &GhostOName);
            tmptree[8]->SetBranchAddress("RunNumber", &GhostRunNumber);
            tmptree[8]->SetBranchAddress("EventNumber", &GhostEventNumber);


            Double_t GNeutronPositionX, GNeutronPositionY, GNeutronMomentumX, GNeutronMomentumY, GNeutronMomentumZ, GNeutronEnergy;
            Int_t GNeutronTrackID, GNeutronTower;
            Int_t GNeutronRunNumber, GNeutronEventNumber;

            // SetBranchAddress to store information about particles gothrough GNeutron
            // Particle Info
            tmptree[11]->SetBranchAddress("POSITIONX[mm]", &GNeutronPositionX);
            tmptree[11]->SetBranchAddress("POSITIONY[mm]", &GNeutronPositionY);
            tmptree[11]->SetBranchAddress("MOMENTUMX[GeV/c]", &GNeutronMomentumX);
            tmptree[11]->SetBranchAddress("MOMENTUMY[GeV/c]", &GNeutronMomentumY);
            tmptree[11]->SetBranchAddress("MOMENTUMZ[GeV/c]", &GNeutronMomentumZ);
            tmptree[11]->SetBranchAddress("ENERGY[GeV]", &GNeutronEnergy);
            tmptree[11]->SetBranchAddress("TrackID", &GNeutronTrackID);
            tmptree[11]->SetBranchAddress("RunNumber", &GNeutronRunNumber);
            tmptree[11]->SetBranchAddress("EventNumber", &GNeutronEventNumber);


            Double_t SNeutronPositionX, SNeutronPositionY, SNeutronMomentumX, SNeutronMomentumY, SNeutronMomentumZ, SNeutronNEnergy, SNeutronEnergy;
            Int_t SNeutronTrackID, SNeutronTower;
            Int_t SNeutronRunNumber, SNeutronEventNumber;

            // SetBranchAddress to store information about particles gothrough SNeutron
            // Particle Info
            tmptree[13]->SetBranchAddress("POSITIONX[mm]", &SNeutronPositionX);
            tmptree[13]->SetBranchAddress("POSITIONY[mm]", &SNeutronPositionY);
            tmptree[13]->SetBranchAddress("MOMENTUMX[GeV/c]", &SNeutronMomentumX);
            tmptree[13]->SetBranchAddress("MOMENTUMY[GeV/c]", &SNeutronMomentumY);
            tmptree[13]->SetBranchAddress("MOMENTUMZ[GeV/c]", &SNeutronMomentumZ);
            tmptree[13]->SetBranchAddress("ENERGY[GeV]", &SNeutronEnergy);
            tmptree[13]->SetBranchAddress("NEUTRONENERGY[GeV]", &SNeutronNEnergy);
            tmptree[13]->SetBranchAddress("TrackID", &SNeutronTrackID);
            tmptree[13]->SetBranchAddress("RunNumber", &SNeutronRunNumber);
            tmptree[13]->SetBranchAddress("EventNumber", &SNeutronEventNumber);
            //Junsang****delete tmpfile;
            
            Int_t TotalEnetries = tmptree[0]->GetEntries();
            //Junsang****for (Int_t iEntry = 0; iEntry < TotalNEvent[0]; iEntry++) 
            for (Int_t iEntry = 0; iEntry < 1000; iEntry++) 
            {
                if(iEntry%5000 == 0) 
                {
                    cout << iEntry << endl;
                    system("date");
                }
                Double_t TotalETS1, TotalETL1;
                TotalETS1 = 0;
                TotalETL1 = 0;
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
                    if(tmptree[13]->GetEntryNumberWithIndex(RUN,EVENT) != -1)
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
            }
        }
    }
    gDirectory->cd(OutputFileName+":/");
    //Junsang****for (int i = 0; i < 15; i++) 
    //Junsang****{
    //Junsang****if(i!=2)
    //Junsang****tmptotaltree[i] = TTree::MergeTrees(tmplist[i]);
    //Junsang****}

    //Junsang****for (int i = 0; i < 15; i++) 
    //Junsang****{
    //Junsang****if(i!=2)
    //Junsang****{
    //Junsang****tmptotaltree[i]->SetName(treename[i]);
    //Junsang****tmptotaltree[i]->Write();
    //Junsang****}
    //Junsang****}



    myReadFile.close();






    OutputFile -> Write();
    OutputFile -> Close();


    cout << "END" << endl;
    system("date");
    return 0;
}

