// $Id: Analysis.hh 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief Analysis of calorimeter application.
 */
/*
 * Analysis.hh
 *
 *  Created on: 9 Feb 2010
 *      Author: adotti
 */

#ifndef ANALYSIS_HH
#define ANALYSIS_HH 1

#include "G4Event.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
// ROOT
class TH1;
class G4Track;

class Analysis {
public:
  static Analysis* GetInstance() {
    if ( Analysis::singleton == NULL ) Analysis::singleton = new Analysis();
    return Analysis::singleton;
  }
  ~Analysis();

  void PrepareNewEvent(const G4Event* anEvent);
  void EndOfEvent(const G4Event* anEvent);
  void PrepareNewRun(const G4Run* aRun);
  void EndOfRun(const G4Run* aRun);
  void AddEDepEM( G4double edep, G4int volCopyNum, G4double time);
  void AddSecondary( G4int num ) { thisEventSecondaries += num; }
  void AddTrack( const G4Track * aTrack );
  // int numDecays() { return decays;}
private:
  Analysis();
  static Analysis* singleton;
  G4double thisEventTotEM[3];
  G4int thisEventSecondaries;
  G4double thisRunTotEM[3];
  G4int thisRunTotSecondaries;

  // G4double activationTimeFirst;
  // G4double start;
  // std::vector<TH1*> histos;
  // int decays =0;
  G4double activation_times[3]; // the three times of activation of each scintillator
  G4double doppie, triple;

  enum {
    fDecayPosZ=0,
    fDecayTime=1,
    fDecayTimeForward=2,
    fDecayTimeBackward=3
  };
};

#endif /* ANALYSIS_HH */
