#include "globals.hh"
#include "G4UserStackingAction.hh"

class G4Track;
class StackingAction: public G4UserStackingAction{
    StackingAction();
    ~StackingAction();

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track * aTrack);

    G4int old_TrackID;

};
