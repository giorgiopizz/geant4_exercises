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

#ifndef TRIGGER_HH
#define TRIGGER_HH 1

#include "G4Event.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include <map>
// ROOT
class TH1;
class G4Track;


class Trigger {
public:
  static Trigger* GetInstance() {
    // if (  );
    singletonMap_t::iterator it = Trigger::singleton.find(G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());
    // G4MTRunManager::GetMasterRunManager
    if (it!=Trigger::singleton.end()){
        return it->second;
    }
    else{
         Trigger::singleton.insert( std::make_pair( G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() , new Trigger() ) );
         return Trigger::singleton.find(G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID())->second;
    }
    G4cout <<"rotto" <<G4endl;
    // for(it=Analysis::singleton.begin(); it!=Analysis::singleton.end(); ++it){
    //     if (it->first == G4Threading::G4GetThreadId())  return it->second;
    // }
  }
  ~Trigger();

  void PrepareNewEvent(const G4Event*);
  void EndOfEvent(const G4Event*);
  void AddEDepEM( G4double edep, G4int volCopyNum, G4double time);
  void AddTrack( const G4Track * aTrack );

private:

  // HistoManager * histoManager;

  Trigger();
  typedef std::map<G4int, Trigger*> singletonMap_t;
  static singletonMap_t singleton;

  G4double thisEventTotEM[3];

  G4double activationTimeFirst;
  G4double start;
  enum {
    fDecayPosZ=0,
    fDecayTime=1,
    fDecayTimeForward=2,
    fDecayTimeBackward=3
  };
};
#endif
