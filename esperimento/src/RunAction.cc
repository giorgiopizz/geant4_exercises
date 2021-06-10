// $Id: RunAction.cc 102 2010-01-26 16:45:56Z adotti $
/**
 * @file   RunAction.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 *
 * @brief  Implements user class RunAction.
 */

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include "MyRun.hh"

RunAction::RunAction()
: G4UserRunAction()
{

	// G4RunManager::GetRunManager()->SetPrintProgress(1);
 //
 // // Create analysis manager
 // // The choice of analysis technology is done via selectin of a namespace
 // // in B4Analysis.hh
 // auto analysisManager = G4AnalysisManager::Instance();
 // G4cout << "Using " << analysisManager->GetType() << G4endl;
 //
 // // Create directories
 // //analysisManager->SetHistoDirectoryName("histograms");
 // //analysisManager->SetNtupleDirectoryName("ntuple");
 // analysisManager->SetVerboseLevel(1);
 // analysisManager->SetNtupleMerging(true);
 //   // Note: merging ntuples is available only with Root output
 //
 // // Book histograms, ntuple
 // //
 //
 // // Creating histograms
 // analysisManager->CreateH1("decayTime","Edep in absorber", 200, 0., 11);
 //  analysisManager->CreateH1("decayTimeForward","Edep in absorber", 25, 0., 11);
 //  analysisManager->CreateH1("decayTimeBackward","Edep in absorber", 25, 0., 11);

}


G4Run* RunAction::GenerateRun()
{ return (new MyRun()); }


// RunAction::~RunAction(){
// 	// delete G4AnalysisManager::Instance();
// }
void RunAction::BeginOfRunAction(const G4Run* aRun )
{
	// G4AnalysisManager * analysisManager = G4Analysis::ManagerInstance("root");
	// HistoManager::GetInstance()->Book();
	if (IsMaster()){
		G4cout << "### Run " << aRun->GetRunID() << " starts (master)." << G4endl;
		HistoManager::GetInstance()->Book();
	}

else
  G4cout << "### Run " << aRun->GetRunID() << " starts (worker)." << G4endl;
	// G4cout<<"Starting Run: "<<aRun->GetRunID()<<G4endl;
	// Analysis::GetInstance()->PrepareNewRun(aRun);
	// G4cout <<"ciaoiwfiorfhjeiorjfiorejfior" << G4endl;

}

void RunAction::EndOfRunAction( const G4Run* aRun )
{
	// Analysis::GetInstance()->EndOfRun(aRun);
	// std::cout << "\n\n Number of decays: " << Analysis::GetInstance()->numDecays() << std::endl;
	if (IsMaster()) HistoManager::GetInstance()->Save();
	// HistoManager::GetInstance()->Save();
    const MyRun* theRun = static_cast<const MyRun*> (aRun);
    // if(IsMaster())
    // {
    //   G4cout << "Global result with " << theRun->GetNumberOfEvent()
    //          << " events : " << theRun->GetTotalEDep()/GeV << " [GeV]" << G4endl;
    // } else {
    //   G4cout << "Local thread result with " << theRun->GetNumberOfEvent()
    //          << " events : " << theRun->GetTotalEDep()/GeV << " [GeV]" << G4endl;
    // }
}
