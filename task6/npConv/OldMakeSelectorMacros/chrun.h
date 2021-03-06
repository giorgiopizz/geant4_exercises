
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 19 15:44:06 2010 by ROOT version 5.24/00
// from TChain Gas_Tree/Gas_Tree
//////////////////////////////////////////////////////////

#ifndef chrun_h
#define chrun_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1F.h>
#include <TCanvas.h>

class chrun : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           ntracks;
   Int_t           id[300];   //[ntracks]
   Int_t           type[300];   //[ntracks]
   Int_t           mum[300];   //[ntracks]
   Float_t         edep[300];   //[ntracks]

   // List of branches
   TBranch        *b_ntracks;   //!
   TBranch        *b_id;   //!
   TBranch        *b_type;   //!
   TBranch        *b_mum;   //!
   TBranch        *b_edep;   //!

   chrun(TTree * /*tree*/ =0) { }
   virtual ~chrun() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   TH1F* hele;
   TH1F* hprot;
   TH1F* hgamma;
   TH1F* hneutr;
   TH1F* harg;
   TH1F* hcarb;
   TH1F* hoxy;
   TH1F* hcopper;
   TH1F* htot;
   TH1F* hbump;
   TH1F* heleprot;
   TH1F* helearg;
   TH1F* hprotarg;


   //
   TCanvas* cele;
   TCanvas* cprot;
   TCanvas* cgamma;
   TCanvas* cneutr;
   TCanvas* carg;
   TCanvas* ccarb;
   TCanvas* coxy;
   TCanvas* ccopper;
   TCanvas* ctot;
   TCanvas* cbump;
   TCanvas* celeprot;
   TCanvas* celearg;
   TCanvas* cprotarg;


   ClassDef(chrun,0);
};

#endif

#ifdef chrun_cxx
void chrun::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ntracks", &ntracks, &b_ntracks);
   fChain->SetBranchAddress("id", id, &b_id);
   fChain->SetBranchAddress("type", type, &b_type);
   fChain->SetBranchAddress("mum", mum, &b_mum);
   fChain->SetBranchAddress("edep", edep, &b_edep);
}

Bool_t chrun::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef chrun_cxx
