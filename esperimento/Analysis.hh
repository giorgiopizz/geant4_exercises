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
#include "G4Threading.hh"
#include <map>
// ROOT
class TH1;
class G4Track;


class Analysis {
public:
  static Analysis* GetInstance() {
    // if (  );
    singletonMap_t::iterator it = Analysis::singleton.find(G4Threading::G4GetThreadId());
    if (it!=Analysis::singleton.end()){
        return it->second;
    }
    else{
         Analysis::singleton.insert( std::make_pair( G4Threading::G4GetThreadId() , new Analysis() ) );
         return Analysis::singleton.find(G4Threading::G4GetThreadId())->second;
    }
    // for(it=Analysis::singleton.begin(); it!=Analysis::singleton.end(); ++it){
    //     if (it->first == G4Threading::G4GetThreadId())  return it->second;
    // }
  }
  ~Analysis();

  void PrepareNewEvent(const G4Event* anEvent);
  void EndOfEvent(const G4Event* anEvent);
  void PrepareNewRun(const G4Run* aRun);
  void EndOfRun(const G4Run* aRun);
  void AddEDepEM( G4double edep, G4int volCopyNum, G4double time);
  void AddSecondary( G4int num ) { thisEventSecondaries += num; }
  void AddTrack( const G4Track * aTrack );
  int numDecays() { return decays;}

private:
  Analysis();
  // static std::vector<Analysis*> singleton;
  typedef std::map<G4int, Analysis*> singletonMap_t;
  static singletonMap_t singleton;
  G4double thisEventTotEM[3];
  G4int thisEventSecondaries;
  G4double thisRunTotEM[3];
  G4int thisRunTotSecondaries;

  G4double activationTimeFirst;
  G4double start;
  std::vector<TH1*> histos;
  int decays =0;

  enum {
    fDecayPosZ=0,
    fDecayTime=1,
    fDecayTimeForward=2,
    fDecayTimeBackward=3
  };
};

#endif /* ANALYSIS_HH */
