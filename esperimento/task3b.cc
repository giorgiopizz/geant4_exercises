// $Id: task2.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief Main program.
 */

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"

#include "G4Version.hh"

#include "G4VisExecutive.hh"
#if  G4VERSION_NUMBER>=930
#include "G4UIExecutive.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"

#include "MyActionInitialization.hh"


#include "PhysicsList.hh"
#include "QGSP_BERT.hh"

#include "G4RadioactiveDecayPhysics.hh"


// #include "G4PhysListFactory.hh"
// #include "G4VModularPhysicsList.hh"
// #include "G4GenericPhysicsList.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


/*!
\brief Main program

\callgraph

*/
int main(int argc,char** argv)
{
  // Run manager
  // G4RunManager * runManager = new G4RunManager();
  #ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(2*(G4Threading::G4GetNumberOfCores()));
  G4cout << "Multithreaded" << G4endl;
  #else
  G4RunManager* runManager = new G4RunManager;
  G4cout << "Single threaded" << G4endl;
  #endif
  // mandatory Initialization classes
  G4VUserDetectorConstruction* detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* physics = new PhysicsList();
  runManager->SetUserInitialization(physics);

  // G4PhysListFactory factory;
  // G4VModularPhysicsList* phys = nullptr;
  // phys = factory.GetReferencePhysList("FTFP_BERT");

// G4VModularPhysicsList* physList = nullptr;
//   std::vector<G4String>* myConstructors = new std::vector<G4String>;
//
//     myConstructors->push_back("G4EmStandardPhysics");
//     myConstructors->push_back("G4EmExtraPhysics");
//     myConstructors->push_back("G4DecayPhysics");
//     myConstructors->push_back("G4HadronElasticPhysics");
//     myConstructors->push_back("G4HadronPhysicsFTFP_BERT");
//     myConstructors->push_back("G4StoppingPhysics");
//     myConstructors->push_back("G4IonPhysics");
//     myConstructors->push_back("G4NeutronTrackingCut");
//
//     physList = new G4GenericPhysicsList(myConstructors);
//
//   runManager->SetUserInitialization(physList);


  // run->SetPhysicsList(phys);

  // mandatory User Action classes
  // G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
  // runManager->SetUserAction(gen_action);


  // //Optional User Action classes
  // //Stacking Action
  // StackingAction* aStackingAction = new StackingAction();
  // runManager->SetUserAction(aStackingAction);
  // //Stepping Action
  // SteppingAction* aSteppingAction = new SteppingAction();
  // runManager->SetUserAction(aSteppingAction);
  // //Event action (handles for beginning / end of event)
  // EventAction* anEventAction = new EventAction();
  // runManager->SetUserAction( anEventAction );
  //
  // //Run action (handles for beginning / end of event)
  // RunAction* aRunAction = new RunAction();
  // runManager->SetUserAction( aRunAction );

  runManager->SetUserInitialization(new MyActionInitialization());

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

#if  G4VERSION_NUMBER>=930
	  //New since G4 9.3: UI executive setups up
	  //correct UI depending on env variables
	  G4UIExecutive * ui = new G4UIExecutive(argc,argv);
	  //If UI has graphics execute special macro: opens OpenGL Qt driver
	  if (ui->IsGUI())
		  UImanager->ApplyCommand("/control/execute visQt.mac");
	  else
		  UImanager->ApplyCommand("/control/execute vis.mac");
#else
	  //Older versions of G4: UI selected by user
  #ifdef G4UI_USE_TCSH
	  G4UIsession * ui = new G4UIterminal(new G4UItcsh);
  #else
	  G4UIsession * ui = new G4UIterminal();
  #endif
	  UImanager->ApplyCommand("/control/execute vis.mac");
#endif
	  ui->SessionStart();
	  delete ui;
  }

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;

  return 0;
}
