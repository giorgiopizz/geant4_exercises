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
/// \file analysis/AnaEx02/include/HistoManager.hh
/// \brief Definition of the HistoManager class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
// class TH1D;
// #include "TH1D.h"
#include <TH1D.h>
const G4int kMaxHisto = 4;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
      static HistoManager* GetInstance();

   ~HistoManager();

    void Book();
    void Save();
private:
    HistoManager();
    static HistoManager* singleton;
    std::vector<TH1*> histos;
    int decays;
public:
    void HistoFill(double x, int i) {histos[i]->Fill(x);}
    void AddDecay() {decays++;}
    int numDecays() { return decays;}
  private:
    TFile*   fRootFile;
    // TH1D*    fHisto[kMaxHisto];
    // TTree*   fNtuple1;
    // TTree*   fNtuple2;
    //
    // G4double fEabs;
    // G4double fEgap;
    // G4double fLabs;
    // G4double fLgap;




    enum {
      fDecayPosZ=0,
      fDecayTime=1,
      fDecayTimeForward=2,
      fDecayTimeBackward=3
    };
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
