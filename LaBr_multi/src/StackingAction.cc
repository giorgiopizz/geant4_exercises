#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"



StackingAction::StackingAction():
old_TrackID(-1)
{
}

StackingAction::~StackingAction(){}


G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
    //at the beginning all the tracks are Urgent
    G4ClassificationOfNewTrack result(fUrgent);

    // i want to get the number of previous track
    old_TrackID = aTrack ->GetParentID();

    //if the prev track came "before" this track, the present track is put on waiting status
    //the waiting stack is processed after the urgent stack is emptied

    if (aTrack->GetTrackID() > old_TrackID) // is a secondary
    {
        result = fWaiting;
    }
    else
    {
        result = fUrgent;
    }
    return result;
}
