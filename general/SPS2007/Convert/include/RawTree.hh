// ***********************************************************
// ***  RawTree Class                                      ***
// ***   this class is for controling SPS2006 raw data     ***
// ***  13 Sep. 06 : first edited                          ***
// ***  30 Oct. 06 : add CreateBranch                      ***
// ***  03 Apl. 07 : modified Raw::FSIL -> RawFSIL         ***
// ***********************************************************

#ifndef __RAWTREE__
#define __RAWTREE__

#include <iomanip>
#include <ctime>
#include "Raw.hh"
#include "RawFSIL.hh"
#include "ConTree.hh"

class RawTree : public ConTree 
{ 
protected:
  Raw            *rdata;
  RawFSIL        *rfsil;

  TBranch        *b_Number; //!
  TBranch        *b_TIME;   //!
  TBranch        *b_INP0;   //!
  TBranch        *b_SCL0;   //!
  TBranch        *b_ADC0;   //!
  TBranch        *b_ADC1;   //! 
  TBranch        *b_ADC2;   //!
  TBranch        *b_CAD0;   //!
  TBranch        *b_CAD1;   //! 
  TBranch        *b_CAD2;   //!
  TBranch        *b_SCIF;   //!
  TBranch        *b_FSIL;   //!
  TBranch        *b_TDC0;   //!
  TBranch        *b_SADC;   //!
  TBranch        *b_ARM2;   //!
  

  Int_t           status_Number;
  Int_t           status_TIME;
  Int_t           status_INP0;
  Int_t           status_SCL0;
  Int_t           status_ADC0;
  Int_t           status_ADC1;
  Int_t           status_ADC2;
  Int_t           status_CAD0;
  Int_t           status_CAD1;
  Int_t           status_CAD2; 
  Int_t           status_SCIF;
  Int_t           status_FSIL;
  Int_t           status_TDC0;
  Int_t           status_SADC;
  Int_t           status_ARM2;


public:
  RawTree();
  ~RawTree();

  int      InitTree();
  Raw*     GetData(){return rdata;}
  RawFSIL* GetFSIL(){return rfsil;}
  int      SetData(Raw* d){rdata = d; return CONTREE_OK; }  
  int      Open();
  int      Close();
  int      SetBranchStatus(char* bname,int stat);
  int      PrintStatus();
  int      CreateBranch();
};

RawTree::RawTree(){
  InitTree();
  return ;
}

RawTree::~RawTree() {
//   DeleteChain();
  return ;
}

int RawTree::InitTree(){
  SetFormat(RAW_DATAFORMAT);
  rdata = new Raw();
  rfsil = new RawFSIL();
  CreateChain("Trigger");

  status_Number = 1;
  status_TIME = 1;
  status_INP0 = 1;
  status_SCL0 = 1;
  status_ADC0 = 1;
  status_ADC1 = 1;
  status_ADC2 = 1;
  status_CAD0 = 1;
  status_CAD1 = 1;
  status_CAD2 = 1;
  status_SCIF = 1;
  status_FSIL = 1;
  status_TDC0 = 1;
  status_SADC = 1;
  status_ARM2 = 1;
  b_Number = 0;
  b_TIME = 0;
  b_INP0 = 0;
  b_SCL0 = 0;
  b_ADC0 = 0;
  b_ADC1 = 0;
  b_ADC2 = 0;
  b_CAD0 = 0;
  b_CAD1 = 0;
  b_CAD2 = 0;
  b_SCIF = 0;
  b_FSIL = 0;
  b_TDC0 = 0;
  b_SADC = 0;
  b_ARM2 = 0;
  
  return CONTREE_OK;
}

int RawTree::Open(){
  if(chain==0){
    cerr << "[RawTree::Open] No Chain." <<endl;
    return CONTREE_ERROR;
  }
  if(chain->FindBranch("Number")){
    chain->SetBranchAddress("Number",&(rdata->Number));
  }
  if(chain->FindBranch("TIME")){
    chain->SetBranchAddress("TIME",&(rdata->TIME));
  }
  if(chain->FindBranch("INP0")){
    chain->SetBranchAddress("INP0",&(rdata->INP0));
  }
  if(chain->FindBranch("SCL0")){
    chain->SetBranchAddress("SCL0",&(rdata->SCL0));
  }
  if(chain->FindBranch("ADC0")){
    chain->SetBranchAddress("ADC0",&(rdata->ADC0));
  }
  if(chain->FindBranch("ADC1")){
    chain->SetBranchAddress("ADC1",&(rdata->ADC1));
  }
  if(chain->FindBranch("ADC2")){
    chain->SetBranchAddress("ADC2",&(rdata->ADC2));
  }
  if(chain->FindBranch("CAD0")){
    chain->SetBranchAddress("CAD0",&(rdata->CAD0));
  }
  if(chain->FindBranch("CAD1")){
    chain->SetBranchAddress("CAD1",&(rdata->CAD1));
  }
  if(chain->FindBranch("CAD2")){
    chain->SetBranchAddress("CAD2",&(rdata->CAD2));
  }
  if(chain->FindBranch("SCIF")){
    chain->SetBranchAddress("SCIF",&(rdata->SCIF));
  }
  if(chain->FindBranch("FSIL")){
    chain->SetBranchAddress("FSIL",&(rfsil->FSIL));
  }
  if(chain->FindBranch("TDC0")){
    chain->SetBranchAddress("TDC0",&(rdata->TDC0));
  }
  if(chain->FindBranch("SADC")){
    chain->SetBranchAddress("SADC",&(rdata->SADC));
  }
//   if(chain->FindBranch("ARM2")){
//     chain->SetBranchAddress("ARM2",&(rdata->ARM2));
//   }
  return CONTREE_OK;
}

int RawTree::Close(){
  delete rdata;
  if(b_Number!=0){delete b_Number;}
  if(b_TIME!=0){delete b_TIME;}
  if(b_INP0!=0){delete b_INP0;}
  if(b_SCL0!=0){delete b_SCL0;}
  if(b_ADC0!=0){delete b_ADC0;}
  if(b_ADC1!=0){delete b_ADC1;}
  if(b_ADC2!=0){delete b_ADC2;}
  if(b_CAD0!=0){delete b_CAD0;}
  if(b_CAD1!=0){delete b_CAD1;}
  if(b_CAD2!=0){delete b_CAD2;}
  if(b_SCIF!=0){delete b_SCIF;}
  if(b_FSIL!=0){delete b_FSIL;}
  if(b_TDC0!=0){delete b_TDC0;}
  if(b_SADC!=0){delete b_SADC;}
//   if(b_ARM2!=0){delete b_ARM2;}

  return CONTREE_OK;
}

int RawTree::SetBranchStatus(char* bname,int stat){
   if(strcmp(bname,"Number")==0){
     status_Number= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"TIME")==0){
     status_TIME= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"INP0")==0){
     status_INP0= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"SCL0")==0){
     status_SCL0= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"ADC0")==0){
     status_ADC0= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"ADC1")==0){
     status_ADC1= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"ADC2")==0){
     status_ADC2= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"CAD0")==0){
     status_CAD0= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"CAD1")==0){
     status_CAD1= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"CAD2")==0){
     status_CAD2= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"SCIF")==0){
     status_SCIF= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"FSIL")==0){
     status_FSIL= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  } 
  if(strcmp(bname,"TDC0")==0){
     status_TDC0= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
  if(strcmp(bname,"SADC")==0){
     status_SADC= stat;
     chain->SetBranchStatus(bname,stat);
     return CONTREE_OK;
  }
//   if(strcmp(bname,"ARM2")==0){
//      status_ARM2= stat;
//      chain->SetBranchStatus(bname,stat);
//      return CONTREE_OK;
//   }


  return CONTREE_ERROR;
}

int RawTree::CreateBranch(){
  if(chain==0){
    cerr << "[RawTree::CreateBranch] chain is not defined." << endl;
    return CONTREE_ERROR;
  }

  chain->Branch("Number",&(rdata->Number),"Run/I:Number/I:Time/i");
  chain->Branch("TIME",&(rdata->TIME),"nTIME/I:TIME[1]/i");
  chain->Branch("INP0",&(rdata->INP0),"nINP0/I:INP0[8]/b");
  chain->Branch("SCL0",&(rdata->SCL0),"nSCL0/I:SCL0[8]/i");
  chain->Branch("ADC0",&(rdata->ADC0),"nADC0/I:ADC0[64]/s");
  chain->Branch("ADC1",&(rdata->ADC1),"nADC1/I:ADC1[64]/s");
  chain->Branch("ADC2",&(rdata->ADC2),"nADC2/I:ADC2[64]/s");
  chain->Branch("CAD0",&(rdata->CAD0),"nCAD0/I:CAD0[5]/i");
  chain->Branch("CAD1",&(rdata->CAD1),"nCAD1/I:CAD1[5]/i");
  chain->Branch("CAD1",&(rdata->CAD2),"nCAD2/I:CAD2[5]/i"); 
  chain->Branch("SCIF",&(rdata->SCIF),"nSCIF/I:SCIF[512]/i"); 
  chain->Branch("FSIL",&(rfsil->FSIL),"nFSIL/I:FSIL[15394]/s"); 
  chain->Branch("SADC",&(rdata->SADC),"nSADC/I:SADC[16]/s");
//   chain->Branch("ARM2",&(rdata->ARM2),"nARM2/I:ARM2[14228]/b");
  
  return CONTREE_OK;
}

int RawTree::PrintStatus(){
  cout << "RawTree" << endl;
  cout << " File: " << file[0] << endl;
  for(int ifile=1;ifile<nfile;ifile++){
    cout << "       " << file[ifile] << endl;
  }
  cout << " NEVENT: " <<  setw(7) << nevent << endl
       << " IEVENT: " <<  setw(7) << ievent << endl
       << " CEVENT: " <<  setw(7) << ievent << endl;
  return CONTREE_OK;
}

#endif
