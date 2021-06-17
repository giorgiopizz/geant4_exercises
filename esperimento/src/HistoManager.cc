//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/AnaEx02/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HistoManager* HistoManager::singleton = 0;


#include "G4AutoLock.hh"
namespace {
  G4Mutex singletonMutex = G4MUTEX_INITIALIZER;
}




HistoManager::HistoManager()
// :fRootFile(0),
:decays(0),
fFactoryOn(false)
 // fNtuple1(0), fNtuple2(0),
 // fEabs(0.), fEgap(0.) ,fLabs(0.), fLgap(0.)
{

  // histograms
  G4cout << "creo nuovo histo manager" << G4endl;
  // for (G4int k=0; k<kMaxHisto; k++) fHisto[k] = 0;

  // ntuple
  // fNtuple1 = 0;
  // fNtuple2 = 0;
}

 HistoManager*  HistoManager::GetInstance() {
  G4AutoLock l(&singletonMutex);
  if ( HistoManager::singleton == NULL ) HistoManager::singleton = new HistoManager();
  return HistoManager::singleton;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  // if (fRootFile) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //



//   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//   analysisManager->SetVerboseLevel(1);
//   // Only merge in MT mode to avoid warning when running in Sequential mode
// #ifdef G4MULTITHREADED
//   analysisManager->SetNtupleMerging(true);
// #endif
//
//   // Create directories
//   analysisManager->SetHistoDirectoryName("histo");
//   analysisManager->SetNtupleDirectoryName("ntuple");
//
//   // Open an output file
//   //
//   G4bool fileOpen = analysisManager->OpenFile("AnaEx02");
//   if (! fileOpen) {
//     G4cerr << "\n---> HistoManager::Book(): cannot open "
//            << analysisManager->GetFileName() << G4endl;
//     return;
//   }
//
//   // Create histograms.
//   // Histogram ids are generated automatically starting from 0.
//   // The start value can be changed by:
//   // analysisManager->SetFirstHistoId(1);
//
//
//   // id = 0
//   analysisManager->CreateH1("histo_tot","Time of Decay",200,0,11 );
//   // id = 1
//   analysisManager->CreateH1("histo_up","Time of Decay [Up]",30,0,11);
//   // id = 2
//   analysisManager->CreateH1("histo_down","Time of Decay [Down]",30,0,11);
//
//   // G4cout << "\n\n Histo creati!!!\n\n" << G4endl;
//   // Create ntuples.
//   // Ntuples ids are generated automatically starting from 0.
//   // The start value can be changed by:
//   // analysisManager->SetFirstMtupleId(1);
//
//   // Create 1st ntuple (id = 0)
//   analysisManager->CreateNtuple("ntuple_tot", "decays");
//   analysisManager->CreateNtupleDColumn("decay"); // column Id = 0
//   analysisManager->FinishNtuple();
//
//   // Create 2nd ntuple (id = 1)
//   //
//   analysisManager->CreateNtuple("ntuple_up", "decays up");
//   analysisManager->CreateNtupleDColumn("up"); // column Id = 0
//   analysisManager->FinishNtuple();
//
//   analysisManager->CreateNtuple("ntuple_down", "decays down");
//   analysisManager->CreateNtupleDColumn("down"); // column Id = 0
//   analysisManager->FinishNtuple();
//
//
//   fFactoryOn = true;
//
//   G4cout << "\n----> Output file is open in "
//          << analysisManager->GetFileName() << "."
//          << analysisManager->GetFileType() << G4endl;
//
//





  G4String fileName = "AnaEx02.root";
  fRootFile = new TFile(fileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " HistoManager::Book :"
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }


  TH1D *h=0;
  // create Histograms
  // histos.push_back(h=new TH1D("decayPos","Z Position of Decay",100,0.8*m,(0.8+2.24)*m) );
  // h->GetYaxis()->SetTitle("events");
  // h->GetXaxis()->SetTitle("t_{decay} #mus");
  // h->StatOverflows();
  histos.push_back(h=new TH1D("histo_tot","Time of Decay",200,0,11 ) ); //microsecond
  h->GetYaxis()->SetTitle("events");
  h->GetXaxis()->SetTitle("t_{decay} #mus");
  h->StatOverflows();
  histos.push_back(h=new TH1D("histo_up","Time of Decay [Up]",30,0,11) ); // microsecond
  h->GetYaxis()->SetTitle("up events");
  h->GetXaxis()->SetTitle("t_{decay} #mus");
  h->StatOverflows();
  histos.push_back(h=new TH1D("histo_down","Time of Decay [Down]",30,0,11) ); // microsecond
  h->GetYaxis()->SetTitle("down events");
  h->GetXaxis()->SetTitle("t_{decay} #mus");
  h->StatOverflows();

  // TTree * tree = new TTree("T", "decays");
  // tree->Branch()

  // ntuple_tot = new TNtuple("decay ntuple_tot", "decays", "decay");
  // ntuple_up = new TNtuple("decay ntuple_up", "decay up", "decay up");
  // ntuple_down = new TNtuple("decay ntuple_down", "decay down ", "decay down");
  // TTree * ntuple = 0;
  // ntuples.push_back(ntuple = new TTree("ntuple_tot", "decays"));
  // ntuple->Branch( "decay", &fTot, "decay/D");
  // ntuples.push_back(ntuple = new TTree("ntuple_up", "decay up"));
  // ntuple->Branch( "up", &fUp, "up/D");
  // ntuples.push_back(ntuple = new TTree("ntuple_down", "decay down "));
  // ntuple->Branch( "down", &fDown, "down/D");

  // id = 0
  // fHisto[0] = new TH1D("EAbs", "Edep in absorber (MeV)", 100, 0., 800*CLHEP::MeV);
  // // id = 1
  // fHisto[1] = new TH1D("EGap", "Edep in gap (MeV)", 100, 0., 100*CLHEP::MeV);
  // // id = 2
  // fHisto[2] = new TH1D("LAbs", "trackL in absorber (mm)", 100, 0., 1*CLHEP::m);
  // // id = 3
  // fHisto[3] = new TH1D("LGap", "trackL in gap (mm)", 100, 0., 50*CLHEP::cm);
  //
  // for ( G4int i=0; i<kMaxHisto; ++i ) {
  //   if (! fHisto[i]) G4cout << "\n can't create histo " << i << G4endl;
  // }
  //
  // // create 1st ntuple
  // fNtuple1 = new TTree("Ntuple1", "Edep");
  // fNtuple1->Branch("Eabs", &fEabs, "Eabs/D");
  // fNtuple1->Branch("Egap", &fEgap, "Egap/D");
  //
  // // create 2nd ntuple
  // fNtuple2 = new TTree("Ntuple2", "TrackL");
  // fNtuple2->Branch("Labs", &fLabs, "Labs/D");
  // fNtuple2->Branch("Lgap", &fLgap, "Lgap/D");

  G4cout << "\n----> Output file is open in " << fileName << G4endl;
}

void HistoManager::Fill(double x, G4int i){

    // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // if (i>0){
    //     analysisManager->FillH1(0, x);
    //     analysisManager->FillH1(1, x);
    //     analysisManager->FillNtupleDColumn(0, 0, x);
    //     analysisManager->AddNtupleRow(0);
    //     analysisManager->FillNtupleDColumn(1, 0, x);
    //     analysisManager->AddNtupleRow(1);
    // }
    // else{
    //     analysisManager->FillH1(0, x);
    //     analysisManager->FillH1(2, x);
    //     analysisManager->FillNtupleDColumn(0, 0, x);
    //     analysisManager->AddNtupleRow(0);
    //     analysisManager->FillNtupleDColumn(2, 0, x);
    //     analysisManager->AddNtupleRow(2);
    // }

    if (i>0){
        // fTot = x;
        // if (ntuples[0]) ntuples[0]->Fill();
        // fUp = x;
        // if (ntuples[1]) ntuples[1]->Fill();

        histos[0]->Fill(x);
        histos[1]->Fill(x);
    }
    else{
        // fTot = x;
        // if (ntuples[0]) ntuples[0]->Fill();
        // fDown = x;
        // if (ntuples[2]) ntuples[2]->Fill();

        histos[0]->Fill(x);
        histos[2]->Fill(x);
    }

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{

//     if (! fFactoryOn) return;
//
// G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
// analysisManager->Write();
// analysisManager->CloseFile();
//
// G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
//
// delete G4AnalysisManager::Instance();
// fFactoryOn = false;
  if (! fRootFile) return;

  fRootFile->Write();       // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)

  G4cout << "\n----> Histograms are saved\n" << G4endl;
  G4cout << "\nTot decays: " << decays <<"\n\n" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



// void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
// {
//   if (ih >= kMaxHisto) {
//     G4cerr << "---> warning from HistoManager::FillHisto() : histo " << ih
//            << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
//            << G4endl;
//     return;
//   }
//   if  (fHisto[ih]) { fHisto[ih]->Fill(xbin, weight); }
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HistoManager::Normalize(G4int ih, G4double fac)
// {
//   if (ih >= kMaxHisto) {
//     G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
//            << " does not exist. (fac=" << fac << ")" << G4endl;
//     return;
//   }
//   if (fHisto[ih]) fHisto[ih]->Scale(fac);
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HistoManager::FillNtuple(G4double energyAbs, G4double energyGap,
//                               G4double trackLAbs , G4double trackLGap )
// {
//   fEabs = energyAbs;
//   fEgap = energyGap;
//   fLabs = trackLAbs;
//   fLgap = trackLGap;
//
//   if (fNtuple1) fNtuple1->Fill();
//   if (fNtuple2) fNtuple2->Fill();
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HistoManager::PrintStatistic()
// {
//   G4cout << "\n ----> print histograms statistic \n" << G4endl;
//   for ( G4int i=0; i<kMaxHisto; ++i ) {
//     TH1D* h1 = fHisto[i];
//     const G4String name = h1->GetName();
//
//     G4String unitCategory;
//     if (name[0] == 'E' ) unitCategory = "Energy";
//     if (name[0] == 'L' ) unitCategory = "Length";
//
//     G4cout << name
//            << ": mean = " << G4BestUnit(h1->GetMean(), unitCategory)
//            << " rms = " << G4BestUnit(h1->GetRMS(), unitCategory )
//            << G4endl;
//   }
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
