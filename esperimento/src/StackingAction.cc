// $Id:$
/**
 * @file
 * @brief implements user class StackingAction
 */
#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "Analysis.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4ProcessType.hh"

#include "Analysis.hh"

StackingAction::StackingAction()
  : analysis(0)
{
  analysis= Analysis::GetInstance();
}


StackingAction::~StackingAction() {
}


G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack( const G4Track * aTrack ) {

  G4ClassificationOfNewTrack result( fUrgent );
  if ( aTrack->GetParentID() > 0 )//This is a secondary
  {
    Analysis::GetInstance()->AddSecondary(1);
    const G4VTouchable* touchable = aTrack->GetTouchable();
	G4int volCopyNum = touchable->GetVolume()->GetCopyNo();
    // if (aTrack->GetParentID() == 1 && aTrack->GetCreatorProcess()->GetProcessType()== fElectromagnetic &&aTrack->GetDefinition()->GetPDGEncoding()==22){
    //     //gamma di brehmstrahlung emesso da mu
    //     if(volCopyNum ==0 || volCopyNum == 1){
    //         G4cout << "  START Event     " << G4endl;
    //     }
    // }

    if ( aTrack->GetCreatorProcess()->GetProcessType()==fDecay && (volCopyNum==0 || volCopyNum==2)) {
        // if ( aTrack->GetCreatorProcess()->GetProcessType()==fDecay) {
      // G4cout << "va aggiunta " << volCopyNum << G4endl;
      // G4cout << "pos. mome" << aTrack->GetPosition() << " " << aTrack->GetGlobalTime() << G4endl;
      analysis->AddTrack(aTrack);
    }
  }
  // else if ( aTrack->GetParentID() == 0 ){
  //     const G4VTouchable* touchable = aTrack->GetTouchable();
  // 	   G4int volCopyNum = touchable->GetVolume()->GetCopyNo();
  //      if(volCopyNum ==0 || volCopyNum ==1){
  //          G4cout << "  START Event     " << G4endl;
  //      }
  // }

  return result;







}
