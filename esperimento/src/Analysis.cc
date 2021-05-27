/*
 * Analysis.cc
 *
 *  Created on: 9 Feb 2010
 *      Author: adotti
 */
/**
 * @file
 * @brief implements singleton class Analysis
 */

#include "Analysis.hh"
#include "G4UnitsTable.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ProcessType.hh"
#include "TH1D.h"
#include "TFile.h"

Analysis* Analysis::singleton = 0;

Analysis::Analysis() :
	thisEventSecondaries(0),
	thisRunTotSecondaries(0),
	activationTimeFirst(-1),
	start(-1)
{

}

Analysis::~Analysis()
{}

void Analysis::AddTrack( const G4Track * aTrack )
{
  if (histos.size()>3) {
	const G4VTouchable* touchable = aTrack->GetTouchable();
  	G4int volCopyNum = touchable->GetVolume()->GetCopyNo();

	// if (thisEventTotEM[volCopyNum-1]>3*MeV){
		// if (volCopyNum==1 && activationTimeFirst==-1){
		// 	activationTimeFirst = aTrack->GetGlobalTime();
		// 	G4cout << " attivazione primo detector " << G4endl;
		// }
		// else if (volCopyNum==2 && start==-1 && activationTimeFirst!=-1 && (aTrack->GetGlobalTime()-activationTimeFirst)<60*ns){
		// 	G4cout << " segnale start " << G4endl;
		// 	start = aTrack->GetGlobalTime();
		// }
		// else if (start!=-1 && (volCopyNum==1 || volCopyNum==3)){
		if (start!=-1 && (aTrack->GetGlobalTime()-start)>100*ns){
			// G4cout << " segnale stop " << G4endl;
			// if (abs(aTrack->GetDefinition()->GetPDGEncoding())!=11 && aTrack->GetDefinition()->GetPDGEncoding()!=22) return; // electrons
			const G4ThreeVector & pos = aTrack->GetPosition();
		    const G4ThreeVector & mom = aTrack->GetMomentumDirection();
		    G4double time = aTrack->GetGlobalTime();

			decays++;
		    histos[fDecayPosZ]->Fill(pos.y()/m);
		    histos[fDecayTime]->Fill((time-start)/microsecond);
		    if (mom.y()>0) histos[fDecayTimeForward]->Fill(time/microsecond);
		    else histos[fDecayTimeBackward]->Fill(time/microsecond);
		}
	// }


    // if (aTrack->GetDefinition()->GetPDGEncoding()!=11) return; // electrons
	//
    // const G4ThreeVector & pos = aTrack->GetPosition();
    // const G4ThreeVector & mom = aTrack->GetMomentumDirection();
    // G4double time = aTrack->GetGlobalTime();
	//
	//
    // histos[fDecayPosZ]->Fill(pos.z()/m);
    // histos[fDecayTime]->Fill(time/microsecond);
    // if (mom.y()>0) histos[fDecayTimeForward]->Fill(time/microsecond);
    // else histos[fDecayTimeBackward]->Fill(time/microsecond);
  }
}

void Analysis::AddEDepEM( G4double edep, G4int volCopyNum, G4double time)
{
	thisEventTotEM[volCopyNum-1] += edep;
	if (thisEventTotEM[volCopyNum-1]>3*MeV){
		if (volCopyNum==1 && activationTimeFirst==-1){
			activationTimeFirst = time;
			// G4cout << " attivazione primo detector " << G4endl;
		}
		else if (volCopyNum==2 && start==-1 && activationTimeFirst!=-1 && (time-activationTimeFirst)<60*ns){
			// G4cout << " segnale start " << G4endl;
			start = time;
		}
		else if (volCopyNum==3 && start!=-1 && (time-start)<60*ns){
			// G4cout << " false start " << G4endl;
			start = -1;
		}
	}
}

void Analysis::PrepareNewEvent(const G4Event* /*anEvent*/)
{
	//Reset variables relative to this event
	thisEventSecondaries = 0;
	for (int i=0;i<3;i++) thisEventTotEM[i]=0;
	activationTimeFirst = -1;
	start = -1;
}

void Analysis::PrepareNewRun(const G4Run* /*aRun*/ )
{
	//Reset variables relative to the run
	for (int i=0;i<3;i++) thisRunTotEM[i]=0;
	thisRunTotSecondaries = 0;

	TH1D *h=0;
	// create Histograms
	histos.push_back(h=new TH1D("decayPos","Z Position of Decay",100,0.8*m,(0.8+2.24)*m) );
	h->GetYaxis()->SetTitle("events");
	h->GetXaxis()->SetTitle("t_{decay} #mus");
	h->StatOverflows();
	histos.push_back(h=new TH1D("decayTime","Time of Decay",200,0,11 ) ); //microsecond
	h->GetYaxis()->SetTitle("events");
	h->GetXaxis()->SetTitle("t_{decay} #mus");
	h->StatOverflows();
	histos.push_back(h=new TH1D("decayTimeForward","Time of Decay [Forward electron]",25,0,11) ); // microsecond
	h->GetYaxis()->SetTitle("forward events");
	h->GetXaxis()->SetTitle("t_{decay} #mus");
	h->StatOverflows();
	histos.push_back(h=new TH1D("decayTimeBackward","Time of Decay [Backward electron]",25,0,11) ); // microsecond
	h->GetYaxis()->SetTitle("backward events");
	h->GetXaxis()->SetTitle("t_{decay} #mus");
	h->StatOverflows();
}

void Analysis::EndOfEvent(const G4Event* /*anEvent*/)
{
	//Accumulate over the run
	for (int i=0;i<3;i++) thisRunTotEM[i]+=thisEventTotEM[i];
	thisRunTotSecondaries += thisEventSecondaries;
	//Uncomment this line for more verbosity:
	//	G4cout<<"Event: "<<anEvent->GetEventID() <<" Energy in EM calo: "<<G4BestUnit(thisEventTotEM,"Energy")<<" Secondaries: "<<thisEventSecondaries<<G4endl;
}

void Analysis::EndOfRun(const G4Run* aRun)
{
	//Some print outs
	G4int numEvents = aRun->GetNumberOfEvent();

	G4cout<<"================="<<G4endl;
	G4cout<<"Summary for run: "<<aRun->GetRunID()<<G4endl;
	G4cout << "  secondari:  " << thisEventSecondaries << G4endl;
	G4cout<<"\t Event processed: "<<numEvents<<G4endl;
	G4cout<<"\t Average number of secondaries: "<<thisRunTotSecondaries/numEvents<<G4endl;
	// G4cout<<"\t Average energy in EM calo: "<<G4BestUnit(thisRunTotEM/numEvents,"Energy")<<G4endl;
	G4cout<<"================="<<G4endl;

	//At the end of the run we can now save a ROOT file containing the histogram
	char filename[256];
	sprintf(filename,"run_%d.root",aRun->GetRunID() );
	TFile* outfile = TFile::Open(filename,"recreate");
	for (size_t i=0; i<histos.size();++i)
	  histos[i]->Write();
	outfile->Close();
	// delete histos
	for (size_t i=0; i<histos.size();++i)
	  delete histos[i];
	histos.clear();
}
