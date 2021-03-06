// $Id: task2.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief Main program.
 */

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4Version.hh"

#include "G4VisExecutive.hh"
#if  G4VERSION_NUMBER>=930
#include "G4UIExecutive.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"
#include "QGSP_BERT.hh"
//#include "EventAction.hh"
//#include "RunAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


/*!
\brief Main program

\callgraph

*/
int main(int argc,char** argv)
{
  // Run manager
  G4RunManager * runManager = new G4RunManager();

  // mandatory Initialization classes
  G4VUserDetectorConstruction* detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* physics = new PhysicsList();
  runManager->SetUserInitialization(physics);

  // mandatory User Action classes
  G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);

  //Optional User Action classes
  //Event action (handles for beginning / end of event)
  //EventAction* event_action = new EventAction();
  //Run action (handles for beginning / end of event)
  //This particular class needs a pointer to the event action
  //RunAction* run_action = new RunAction(event_action);
  //runManager->SetUserAction( event_action );
  //runManager->SetUserAction( run_action );

  // Initialize G4 kernel
  runManager->Initialize();

  //Initilize the visualization manager
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager * UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {  // batch mode
	  //command line contains name of the macro to execute
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
  }
  else {           // interactive mode : define UI session

      // The following works starting with Geant4 9.3.
      //  ( Older versions of G4: see solution in other exercises.
      //  Set up UI executive depending on env variables.
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      //If UI has graphics execute special macro: opens OpenGL Qt driver
      if (ui->IsGUI())
	      UImanager->ApplyCommand("/control/execute visQt.mac");
      else
	      UImanager->ApplyCommand("/control/execute vis.mac");

      ui->SessionStart();
      delete ui;
  }

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;

  return 0;
}
