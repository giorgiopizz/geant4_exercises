
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 23 09:12:42 2010 by ROOT version 5.24/00
// from TChain Gas_Tree/Gas_Tree
//////////////////////////////////////////////////////////

#ifndef chrunmap_h
#define chrunmap_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <TH1F.h>



using namespace std;

class chrunmap : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
//Int_t maxtracks = 1000; 

   Int_t           ntracks;
   Int_t           id[1000];   //[ntracks]
   Int_t           type[1000];   //[ntracks]
   Int_t           mum[1000];   //[ntracks]
   Float_t         edep[1000];   //[ntracks]

   // List of branches
   TBranch        *b_ntracks;   //!
   TBranch        *b_id;   //!
   TBranch        *b_type;   //!
   TBranch        *b_mum;   //!
   TBranch        *b_edep;   //!

   chrunmap(TTree * /*tree*/ =0) { }
   virtual ~chrunmap() { }
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

   //Declaration of std map<> used to recognize a 
   //process starting direcly from a primary neutron (mumID==1)
   //Eg n->A+B or n->A+B+C, 
   //I use a string taken from the convesion of the PDG_encoding to recognize a 
   //process Int_t PGDEncA_PGD_EncB
   //the second entry of the map is histogram that will 
   //keep th energy of the process
   //involving also all the successive created particles 

   string convertInt(Int_t number);
     

   typedef std::map<std::string,TH1F*> ProcessMap_t;
   ProcessMap_t processmap;

   ClassDef(chrunmap,0);
};

#endif

#ifdef chrunmap_cxx
void chrunmap::Init(TTree *tree)
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

Bool_t chrunmap::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

string chrunmap::convertInt(Int_t number)
     
{
  //Create the table in order to covert the PDGEconding 
  // to the symbol of the particle
  
  string tmps;

  //gamma
  if(number == 22) 
    {
      tmps = "g";
    }
  //proton
  else if(number == 2212) 
    {
      tmps = "p";
    }
  //neutron
  else if(number == 2112) 
    {
      tmps = "n";
    }
  //ArgonIon40
  else if(number == 1000180400) 
    {
      tmps = "Ar40";
    }
  //ArgonIon36
  else if(number == 1000180360) 
    {
      tmps = "Ar36";
    }
  //ArgonIon37
  else if(number == 1000180370) 
    {
      tmps = "Ar37";
    }
  //ArgonIon38
  else if(number == 1000180380) 
    {
      tmps = "Ar38";
    }
  //ArgonIon41
  else if(number == 1000180410)
    {
      tmps = "Ar41";
    }
  //CarbonIon12
  else if(number == 1000060120) 
    { 
      tmps = "C12";
    }
  //CarbonIon13
  else if(number == 1000060130) 
    { 
      tmps = "C13";
    }
  //OxygenIon16
  else if(number == 1000080160) 
    {
      tmps = "O16";
    }
  //OxygenIon17
  else if(number == 1000080170) 
    {
      tmps = "O17";
    }
  //OxygenIon18
  else if(number == 1000080180) 
    {
      tmps = "O18";
    }
  //CopperIon63
  else if(number == 1000290630) 
    {
      tmps = "Cu63";
    }
  //CopperIon65
  else if(number == 1000290650) 
    { 
      tmps = "Cu65";
    }
  //HeliumIon4
  else if(number == 1000020040)
    {
      tmps = "He4";
    }
  //SulfurIon33
  else if(number == 1000160330)
    {
      tmps = "S33";
    }
  //SulfurIon37
  else if(number == 1000160370)
    {
      tmps = "S37";
    }
  //NichelIon63
  else if(number == 1000280630)
    {
      tmps = "Ni63";
    }
  //ClorumIon36
  else if(number == 1000170360)
    {
      tmps = "Cl36";
    }
  //DeuteriumIon
  else if(number == 1000010020)
    {
      tmps = "H2";
    }
  

  
  
  


  else
    {
      
      stringstream ss;//create a stringstream
      ss << number;//add number to the stream
      tmps = ss.str();
    }
  
  return tmps;//return a string with the contents of the stream
  

}


#endif // #ifdef chrunmap_cxx
