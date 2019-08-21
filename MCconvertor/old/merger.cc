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

    TString list(argv[1]);

    ifstream myReadFile;
    string tmpstring;
    myReadFile.open(list);
    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile, tmpstring)) 
        {
            //Junsang****cout << "start while" << endl;
            //Junsang****cout << tmpstring << endl;
            tmpfile = TFile::Open(tmpstring.c_str());
            for (int i = 0; i < 15; i++) 
            {
                if(i!=2)
                {
                TTree* buffer = tmptotaltree[i];
                tmpfile->GetObject(treename[i], tmptree[i]);
                gDirectory->cd(OutputFileName+":/");
                //Junsang****cout << "before delete" << endl;
                //Junsang****gDirectory->pwd();
                if(tmptree[i]->GetEntries())
                {
                    if(tmptotaltree[i]!=NULL)
                        tmplist[i]->Add(tmptotaltree[i]);
                    if(tmptree[i]!=NULL)
                        tmplist[i]->Add(tmptree[i]);
                    tmptotaltree[i] = TTree::MergeTrees(tmplist[i]);
                    //Junsang****cout << treename[i] << ": " <<  tmptotaltree[i]->GetEntries() << endl;
                    tmplist[i]->Clear();
                    if(buffer!=NULL)
                        delete buffer;
                    if(tmptree[i]!=NULL)
                        delete tmptree[i];
                }
                }
            }
            delete tmpfile;
        }
    }

    //Junsang****for (int i = 0; i < 15; i++) 
    //Junsang****{
        //Junsang****tmptotaltree[i]->SetName(treename[i]);
        //Junsang****tmptotaltree[i]->Write();
    //Junsang****}



    myReadFile.close();






    OutputFile -> Write();
    OutputFile -> Close();


    cout << "END" << endl;
    system("date");
    return 0;
}

