//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  3 02:46:14 2018 by ROOT version 5.34/36
// from TTree LHCfEvents/Tree of RHICfEvent
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "/home/hoosiki/Downloads/src/root/root/core/base/inc/TObject.h"
#include "/home/hoosiki/Downloads/src/root/root/core/base/inc/TNamed.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //LHCfEvent       *Events;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   TString         fName;
   TString         fTitle;
   Int_t           run;
   Int_t           gnumber;
   Int_t           a1number;
   Int_t           a2number;
   UInt_t          a1flag[2];
   UInt_t          a2flag[2];
   Int_t           ifile;
   Int_t           tnumber;
   UInt_t          tag;
   Int_t           tmp;
   TObjArray       objarray;

   // List of branches
   TBranch        *b_Events_fUniqueID;   //!
   TBranch        *b_Events_fBits;   //!
   TBranch        *b_Events_fName;   //!
   TBranch        *b_Events_fTitle;   //!
   TBranch        *b_Events_run;   //!
   TBranch        *b_Events_gnumber;   //!
   TBranch        *b_Events_a1number;   //!
   TBranch        *b_Events_a2number;   //!
   TBranch        *b_Events_a1flag;   //!
   TBranch        *b_Events_a2flag;   //!
   TBranch        *b_Events_ifile;   //!
   TBranch        *b_Events_tnumber;   //!
   TBranch        *b_Events_tag;   //!
   TBranch        *b_Events_tmp;   //!
   TBranch        *b_Events_objarray;   //!

   MyClass(TTree *tree=0);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test.root");
      }
      f->GetObject("LHCfEvents",tree);

   }
   Init(tree);
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_Events_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_Events_fBits);
   fChain->SetBranchAddress("fName", &fName, &b_Events_fName);
   fChain->SetBranchAddress("fTitle", &fTitle, &b_Events_fTitle);
   fChain->SetBranchAddress("run", &run, &b_Events_run);
   fChain->SetBranchAddress("gnumber", &gnumber, &b_Events_gnumber);
   fChain->SetBranchAddress("a1number", &a1number, &b_Events_a1number);
   fChain->SetBranchAddress("a2number", &a2number, &b_Events_a2number);
   fChain->SetBranchAddress("a1flag[2]", a1flag, &b_Events_a1flag);
   fChain->SetBranchAddress("a2flag[2]", a2flag, &b_Events_a2flag);
   fChain->SetBranchAddress("ifile", &ifile, &b_Events_ifile);
   fChain->SetBranchAddress("tnumber", &tnumber, &b_Events_tnumber);
   fChain->SetBranchAddress("tag", &tag, &b_Events_tag);
   fChain->SetBranchAddress("tmp", &tmp, &b_Events_tmp);
   fChain->SetBranchAddress("objarray", &objarray, &b_Events_objarray);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_cxx
