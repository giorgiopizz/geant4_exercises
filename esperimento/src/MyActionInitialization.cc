#include "MyActionInitialization.hh"


#include "StackingAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"


MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
    RunAction* aRunAction = new RunAction();
    SetUserAction( aRunAction );
}
void MyActionInitialization::Build() const
{
    G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
    SetUserAction(gen_action);
    //Optional User Action classes
    //Stacking Action
    StackingAction* aStackingAction = new StackingAction();
    SetUserAction(aStackingAction);
    //Stepping Action
    SteppingAction* aSteppingAction = new SteppingAction();
    SetUserAction(aSteppingAction);
    //Event action (handles for beginning / end of event)
    EventAction* anEventAction = new EventAction();
    SetUserAction( anEventAction );
}
