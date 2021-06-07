#include "MyActionInitialization.hh"


#include "StackingAction.hh"
#include "SteppingAction.hh"
// #include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
    // HistoManager * histoManager = new HistoManager();
    // RunAction* aRunAction = new RunAction(histoManager);
    RunAction* aRunAction = new RunAction();
    SetUserAction( aRunAction );
}
void MyActionInitialization::Build() const
{
    RunAction* aRunAction = new RunAction();
    SetUserAction( aRunAction );
    G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
    SetUserAction(gen_action);
    //Optional User Action classes
    //Stacking Action
    // StackingAction* aStackingAction = new StackingAction();
    // SetUserAction(aStackingAction);
    // //Stepping Action
    // SteppingAction* aSteppingAction = new SteppingAction();
    // SetUserAction(aSteppingAction);
    //Event action (handles for beginning / end of event)
    // HistoManager * histoManager = new HistoManager();
    // EventAction* anEventAction = new EventAction(histoManager);
    // EventAction* anEventAction = new EventAction();
    // SetUserAction( anEventAction );
}
