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
#include "TH2D.h"
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

    ChainForInput1 = new TChain("ARM1PL");
    //Junsang****ChainForInput2 = new TChain("ARM1BAR");
    //Junsang****ChainForInput3 = new TChain("FrontCounterInfo");
    //Junsang****ChainForInput4 = new TChain("WPlate");
    //Junsang****ChainForInput5 = new TChain("ZDCPMMA");
    //Junsang****ChainForInput6 = new TChain("ZDCSMD");
    //Junsang****ChainForInput7 = new TChain("ZDCGhost");
    ChainForInput8 = new TChain("IP");
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
        ReadList(tmpString, ChainForInput1);
        //Junsang****ReadList(tmpString, ChainForInput2);
        //Junsang****ReadList(tmpString, ChainForInput3);
        //Junsang****ReadList(tmpString, ChainForInput4);
        //Junsang****ReadList(tmpString, ChainForInput5);
        //Junsang****ReadList(tmpString, ChainForInput6);
        //Junsang****ReadList(tmpString, ChainForInput7);
        ReadList(tmpString, ChainForInput8);
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

    int TotalNEvent1 = ChainForInput1 -> GetEntries();
    int TotalNEvent8 = ChainForInput8 -> GetEntries();
    int TotalNEvent11 = ChainForInput11 -> GetEntries();
    int TotalNEvent12 = ChainForInput12 -> GetEntries();
    int TotalNEvent13 = ChainForInput13 -> GetEntries();
    int TotalNEvent14 = ChainForInput14 -> GetEntries();

    std::cout << "TotalNumber1: " << TotalNEvent1 << std::endl;
    std::cout << "TotalNumber8: " << TotalNEvent8 << std::endl;
    std::cout << "TotalNumber11: " << TotalNEvent11 << std::endl;
    std::cout << "TotalNumber12: " << TotalNEvent12 << std::endl;
    std::cout << "TotalNumber13: " << TotalNEvent13 << std::endl;
    std::cout << "TotalNumber14: " << TotalNEvent14 << std::endl;



    //------------------------------------------------------------------



    Double_t ENERGY8, MOMENTUMY8, MOMENTUMZ8, MOMENTUMX8, X8, Y8;
    Char_t NAME[10];

    ChainForInput8->SetBranchAddress("ENERGY[GeV]", &ENERGY8);

    ChainForInput8->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX8);
    ChainForInput8->SetBranchAddress("MOMENTUMY[GeV/c]", &MOMENTUMY8);
    ChainForInput8->SetBranchAddress("MOMENTUMZ[GeV/c]", &MOMENTUMZ8);
    ChainForInput8->SetBranchAddress("NAME", &NAME);



    Int_t RunNumber11;

    Double_t pT11, ENERGY11, MOMENTUMY11, MOMENTUMX11, X11, Y11;

    ChainForInput11->SetBranchAddress("RunNumber", &RunNumber11);
    ChainForInput11->SetBranchAddress("ENERGY[GeV]", &ENERGY11);

    ChainForInput11->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX11);
    ChainForInput11->SetBranchAddress("MOMENTUMY[GeV/c]", &MOMENTUMY11);

    ChainForInput11->SetBranchAddress("POSITIONX[mm]", &X11);

    ChainForInput11->SetBranchAddress("POSITIONY[mm]", &Y11);



    Int_t RunNumber12;

    Double_t pT12, ENERGY12, MOMENTUMY12, MOMENTUMX12, X12, Y12;

    ChainForInput12->SetBranchAddress("RunNumber", &RunNumber12);
    ChainForInput12->SetBranchAddress("ENERGY[GeV]", &ENERGY12);

    ChainForInput12->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX12);
    ChainForInput12->SetBranchAddress("MOMENTUMY[GeV/c]", &MOMENTUMY12);

    ChainForInput12->SetBranchAddress("POSITIONX[mm]", &X12);

    ChainForInput12->SetBranchAddress("POSITIONY[mm]", &Y12);



    Int_t RunNumber13;

    Double_t pT13, ENERGY13, MOMENTUMY13, MOMENTUMX13, X13, Y13;

    ChainForInput13->SetBranchAddress("RunNumber", &RunNumber13);
    ChainForInput13->SetBranchAddress("ENERGY[GeV]", &ENERGY13);

    ChainForInput13->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX13);
    ChainForInput13->SetBranchAddress("MOMENTUMY[GeV/c]", &MOMENTUMY13);

    ChainForInput13->SetBranchAddress("POSITIONX[mm]", &X13);

    ChainForInput13->SetBranchAddress("POSITIONY[mm]", &Y13);



    Int_t RunNumber14;
    Double_t pT14, ENERGY14, MOMENTUMY14, MOMENTUMX14, X14, Y14;

    ChainForInput14->SetBranchAddress("RunNumber", &RunNumber14);
    ChainForInput14->SetBranchAddress("ENERGY[GeV]", &ENERGY14);

    ChainForInput14->SetBranchAddress("MOMENTUMX[GeV/c]", &MOMENTUMX14);
    ChainForInput14->SetBranchAddress("MOMENTUMY[GeV/c]", &MOMENTUMY14);

    ChainForInput14->SetBranchAddress("POSITIONX[mm]", &X14);

    ChainForInput14->SetBranchAddress("POSITIONY[mm]", &Y14);


    delete gROOT->FindObject("rawspectrum");


    TString tmpstring = FileManager::GetInstance()->GetFileName()+"nrawspectrum";
    TH1D* nrawspectrum   = new TH1D(tmpstring,"Energy spectrum[raw];Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"nsignalspectrum";
    TH1D* nsignalspectrum   = new TH1D(tmpstring,"Energy spectrum[signal];Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"prawspectrum";
    TH1D* prawspectrum   = new TH1D(tmpstring,"Energy spectrum[raw];Gamma Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"psignalspectrum";
    TH1D* psignalspectrum   = new TH1D(tmpstring,"Energy spectrum[signal];Gamma Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"nrawpTdis";
    TH1D* nrawpTdis   = new TH1D(tmpstring,"pT distribution;pT[GeV/C];Event#",30,0.,1.2);
    tmpstring = FileManager::GetInstance()->GetFileName()+"nsignalpTdistribution";
    TH1D* nsignalpTdis   = new TH1D(tmpstring,"pT distribution[signal];pT[GeV/C];Event#",30,0.,1.2);
    tmpstring = FileManager::GetInstance()->GetFileName()+"prawpTdis";
    TH1D* prawpTdis   = new TH1D(tmpstring,"pT distribution;pT[GeV/C];Event#",30,0.,1.2);
    tmpstring = FileManager::GetInstance()->GetFileName()+"psignalpTdistribution";
    TH1D* psignalpTdis   = new TH1D(tmpstring,"pT distribution[signal];pT[GeV/C];Event#",30,0.,1.2);



    tmpstring = FileManager::GetInstance()->GetFileName()+"lowpt";
    TH1D* lowEspec   = new TH1D(tmpstring,"spectrum in low range;Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"highpt";
    TH1D* highEspec   = new TH1D(tmpstring,"spectrum in high range;Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"signallowpt";
    TH1D* signallowEspec   = new TH1D(tmpstring,"spectrum in low range;Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"signalhighpt";
    TH1D* signalhighEspec   = new TH1D(tmpstring, "spectrum in high range;Neutron Energy[GeV];Event#",255,0.,255.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"hitmap";
    TH2D* hitmap    = new TH2D(tmpstring, "Hitmap;X[mm];Y[mm]", 160, -40, 40, 460, -100., 130.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"hitmap2";
    TH2D* hitmap2    = new TH2D(tmpstring, "Hitmap;X[mm];Y[mm]", 160, -40, 40, 460, -100., 130.);
    TH2D* hitmapplus = new TH2D("plus", "Hitmap[neutron];X[mm];Y[mm]", 300, -150., 150., 400, -200., 200.); 
    TH2D* hitmapminus = new TH2D("minus", "Hitmap[pion];X[mm];Y[mm]", 300, -150., 150., 400, -200., 200.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"highhitmap";
    TH2D* highhitmap    = new TH2D(tmpstring, "Hitmap;X[mm];Y[mm]", 160, -40, 40, 460, -100., 130.);
    tmpstring = FileManager::GetInstance()->GetFileName()+"lowhitmap";
    TH2D* lowhitmap    = new TH2D(tmpstring, "Hitmap;X[mm];Y[mm]", 160, -40, 40, 460, -100., 130.);


    for (int i = 0; i < TotalNEvent11; i++) 
    {
        ChainForInput11->GetEntry(i);
        //Junsang****cout << RunNumber << endl;
        //Junsang****cout << ENERGY << endl;
        //Junsang****cout << MOMENTUMX << endl;
        //Junsang****cout << MOMENTUMY << endl;
        nrawspectrum->Fill(ENERGY11);
        Double_t pT = sqrt(MOMENTUMX11*MOMENTUMX11+MOMENTUMY11*MOMENTUMY11);
        nrawpTdis->Fill(pT);
        hitmap->Fill(X11,Y11);

        if(pT<=0.1)
        {
            lowEspec->Fill(ENERGY11);
        }

        if(pT>=0.4)
        {
            highEspec->Fill(ENERGY11);
        }
    }

    for (int i = 0; i < TotalNEvent12; i++) 
    {
        ChainForInput12->GetEntry(i);
        //Junsang****cout << RunNumber << endl;
        //Junsang****cout << ENERGY << endl;
        //Junsang****cout << MOMENTUMX << endl;
        //Junsang****cout << MOMENTUMY << endl;
        nrawspectrum->Fill(ENERGY12);
        Double_t pT = sqrt(MOMENTUMX12*MOMENTUMX12+MOMENTUMY12*MOMENTUMY12);
        nrawpTdis->Fill(pT);
        hitmap2->Fill(X12,Y12);

        if(pT<=0.1)
        {
            lowEspec->Fill(ENERGY12);
        }

        if(pT>=0.4)
        {
            highEspec->Fill(ENERGY12);
        }
    }

    for (int i = 0; i < TotalNEvent14; i++) 
    {
        ChainForInput14->GetEntry(i);
        //Junsang****cout << RunNumber << endl;
        //Junsang****cout << ENERGY << endl;
        //Junsang****cout << MOMENTUMX << endl;
        //Junsang****cout << MOMENTUMY << endl;
        nsignalspectrum->Fill(ENERGY14);
        Double_t pT = sqrt(MOMENTUMX14*MOMENTUMX14+MOMENTUMY14*MOMENTUMY14);
        nsignalpTdis->Fill(pT);
        //Junsang****hitmap->Fill(X14,Y14);
        if(pT<=0.1)
        {
            signallowEspec->Fill(ENERGY14);
            lowhitmap->Fill(X14, Y14);
        }

        if(pT>=0.4)
        {
            signalhighEspec->Fill(ENERGY14);
            highhitmap->Fill(X14, Y14);
        }
    }



    for (int i = 0; i < TotalNEvent8; i++) 
    {

        ChainForInput8->GetEntry(i);
        TString tmps = NAME;
        if(tmps == "neutron")
        {
            //Junsang****cout << RunNumber << endl;
            //Junsang****cout << ENERGY << endl;
            //Junsang****cout << MOMENTUMX << endl;
            //Junsang****cout << MOMENTUMY << endl;
            //Junsang****rawspectrum->Fill(ENERGY8);
            X8 = MOMENTUMX8/MOMENTUMZ8*17770;
            Y8 = MOMENTUMY8/MOMENTUMZ8*17770;
            if(MOMENTUMZ8>=0) hitmapplus->Fill(X8, Y8);
            //Junsang****if(MOMENTUMZ8>=0){
            //Junsang****hitmapminus->Fill(X8, Y8);
            //Junsang****}else
            //Junsang****{
            //Junsang****hitmapplus->Fill(X8, Y8);
            //Junsang****}

        }else if(tmps == "pi0")
        {
            X8 = MOMENTUMX8/MOMENTUMZ8*17770;
            Y8 = MOMENTUMY8/MOMENTUMZ8*17770;
            if(MOMENTUMZ8>=0) hitmapminus->Fill(X8, Y8);
            //Junsang****if(MOMENTUMZ8>=0){ if(tmps == "pion")
            //Junsang****hitmapminus->Fill(X8, Y8);
            //Junsang****}

        }
    }

    OutputFile -> Write();
    OutputFile -> Close();
    cout << "End" << endl;
    return 0;
}

