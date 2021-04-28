// ***********************************************
// ***  ConTree Class                          ***
// ***           edited by H.Menjo , 12.Sep.06 ***
// ***                                         ***
// *** this class is base one for tree file    ***
// ***********************************************

#ifndef __CONTREE__
#define __CONTREE__

#include "TChain.h"

#define CONTREE_MAXNFILE  200

#define FORMAT_NUMBER_NO_FORMAT 0
#define FORMAT_NUMBER_RAW       1
#define FORMAT_NUMBER_CAL01     2
#define FORMAT_NUMBER_CAL02     3
#define FORMAT_NUMBER_SIM      10
#define FORMAT_NUMBER_CALFSIL2 33

#define CONTREE_OK            0
#define CONTREE_ERROR        -1
#define CONTREE_END_EVENT    -2
#define CONTREE_SELECTED      1
#define CONTREE_NOSELECTED    0

class ConTree
{
  protected:
  int         iformat;
  char        formatname[100];
  char        chainname[100];
  int         nfile;
  char        file[CONTREE_MAXNFILE][200];
  TChain*     chain;
  TTree*      tree;
  TFile*      tfile;

  int         ievent;     // now event number on ifile.
  int         nevent;     // number of events on ifile.
  int         cevent;     // now event number made selection

public:
  ConTree();
  virtual ~ConTree();
  
  int         InitConTree();
  char*       GetChainName(){return chainname;}
  int         SetFormat(char form[]);
  char*       GetFormatName();
  int         GetFormatNumber();
  // for Read Mode
  int         CreateChain(char name[],char title[]="");
  int         DeleteChain();
  int         AddFile(char fname[],char form[]="");
  virtual int Open(){return CONTREE_OK;}
  virtual int Close(){return CONTREE_OK;}
  virtual int Cut(){return CONTREE_SELECTED;}
  int         Incriment();
  int         GetEntry(int ie);
  TChain*     GetChain(){return chain;}
  int         GetEntries(){return chain->GetEntries();}
  int         GetIEvent(){return ievent;}
  int         GetSelectedNumber(){return cevent;}
  // for Write Mode
  int         OpenTFile(char fname[],char opt[]="");
  int         CloseTFile(); 
  virtual int CreateTree(char name[],char title[]="");
  virtual int CreateBranch(){return CONTREE_OK;}
  int         Write(char name[]="",Int_t opt=0);
  int         Fill();
  // others
  char*       FormatInt2Char(int a);
  int         FormatChar2int(char* a); 
  TFile*      GetFilePointer(){return tfile;}
};

ConTree::ConTree(){
  InitConTree();
}

ConTree::~ConTree(){;}

int ConTree::InitConTree(){
  iformat = CONTREE_ERROR;
  strcpy(formatname,"EMPTY");
  strcpy(chainname,"NONAME");
  nfile = 0;
  chain = 0;
  ievent = 0;
  nevent = 0;
  cevent = 0;
  return CONTREE_OK;
}

int ConTree::CreateChain(char name[],char title[]){
  chain  = new TChain(name,title);
  return CONTREE_OK;
}

int ConTree::DeleteChain(){
  if(chain!=0){
    delete chain;
  }
  return CONTREE_OK;
}

int ConTree::SetFormat(char form[]){
  int itmp;
  itmp = FormatChar2int(form);
  iformat = itmp;
  strcpy(formatname,FormatInt2Char(itmp));
  return itmp;
}

char* ConTree::GetFormatName(){
  return formatname;
}

int  ConTree::GetFormatNumber(){
  return iformat;
}

int  ConTree::AddFile(char fname[],char form[]){
  if(iformat!=CONTREE_ERROR && strcmp(form,"")!=0){
    if(iformat!=FormatChar2int(form)){
      cerr << "[ConTree::AddFile] differ the setting file format ." 
	   << endl;
      return CONTREE_ERROR;
    }
  }
  strcpy(file[nfile],fname);
  chain->Add(file[nfile]);
  nevent = chain->GetEntries();
  nfile++;
  return CONTREE_OK;
}

int ConTree::Incriment(){
  if(ievent>=nevent){return CONTREE_END_EVENT;}
  
  while(1){
    ievent++;
    if(chain->GetEntry(ievent)==0){ return CONTREE_END_EVENT;}
    if(Cut()==CONTREE_SELECTED){break;}
  }
  
  cevent++;
  return ievent;
}

int ConTree::GetEntry(int ie){
  if(chain->GetEntry(ie)==0){ 
    ievent = ie;
    return CONTREE_END_EVENT;
  }
  ievent = ie;
  return CONTREE_OK;
}

int ConTree::OpenTFile(char fname[],char opt[]){
  if(nfile!=0){
    cerr << "[ConTree::OpenTFile] TFile have already opend." << endl;
    return CONTREE_ERROR;
  }
  
  tfile = new TFile(fname,opt);
  nfile++;
  strcpy(file[0],fname);
  return CONTREE_OK;
}

int ConTree::CloseTFile(){
  tfile->Close();
  return CONTREE_OK;
}

int ConTree::CreateTree(char name[],char title[]){
  tree = new TTree(name,title);
  chain = (TChain*)tree;
  return CONTREE_OK;
}

int ConTree::Write(char name[],Int_t opt){
  tfile->cd();
  chain->Write(name,opt);
  gROOT->cd();
  return CONTREE_OK;
}

int ConTree::Fill(){
  chain->Fill();
  ievent++;
  nevent++;
  return CONTREE_OK;
}

char* ConTree::FormatInt2Char(int a){
  if(a==FORMAT_NUMBER_RAW){ return "RAW";}
  else if(a==FORMAT_NUMBER_CAL01){ return "CAL01";}
  else if(a==FORMAT_NUMBER_CAL02){ return "CAL02";}
  else if(a==FORMAT_NUMBER_SIM){ return "SIM";}
  else if(a==FORMAT_NUMBER_CALFSIL2){ return "CALFSIL2";}
  else {return "NO_FORMAT";}
}

int ConTree::FormatChar2int(char* a){
  if(strcmp(a,"RAW")==0){return FORMAT_NUMBER_RAW;}
  else if(strcmp(a,"CAL01")==0){return FORMAT_NUMBER_CAL01;}
  else if(strcmp(a,"CAL02")==0){return FORMAT_NUMBER_CAL02;}
  else if(strcmp(a,"SIM")==0){return FORMAT_NUMBER_SIM;}
  else if(strcmp(a,"CALFSIL2")==0){return FORMAT_NUMBER_CALFSIL2;}
  else{return FORMAT_NUMBER_NO_FORMAT;}
}

#endif
