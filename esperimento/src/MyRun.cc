#include "G4SDManager.hh"
#include "MyRun.hh"
#include "G4RunManager.hh"
#include "MyHit.hh"
#include "G4Event.hh"
#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include <algorithm>
#include <vector>

MyRun::MyRun()
:G4Run()
{
 collID = G4SDManager::GetSDMpointer()->GetCollectionID("ScintHitCollection");
}
MyRun::~MyRun(){

}

bool compare (MyHit * a, MyHit* b) {return (a->GetTime()<b->GetTime()); }

void MyRun::RecordEvent(const  G4Event* evt )
{
  // if (collID<0) collID = G4SDManager::GetSDMpointer()->GetCollectionID("ScintHitCollectionsda");
  // G4cout << "\n\n\n\njfewsfhjjkldsfhgjkdsfhgjkldfshgjkdfshgjkldsfhgjklsdhgkjls\n\n\n\n" << G4endl;
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(HCE) {
      // G4cout << " HCE" << G4endl;
   // This part of the code could be replaced to any kind of access
   // to hits collections and scores
   HitCollection *hc =(HitCollection *) HCE->GetHC(collID);
   if (hc->entries()!=0){

       // copy hc to a vector of hits
       std::vector <MyHit*> vh;
       for (G4int i=0;i < hc->entries() ;i++) vh.push_back((*hc)[i]);
       std::sort (vh.begin(), vh.end(), compare);
        // G4cout << hc->entries() << G4endl;
       // G4int max = hc->entries();

       G4double thisEventTotEM[3] = {0, 0, 0};
       G4double activationTimeFirst = -1;
       G4double start = -1;
       G4double lastTime = -1;


       for (G4int i=0; i < vh.size() ; i++){
           MyHit * hit = vh[i];
           // hit->PrintHit();
           thisEventTotEM[ hit->GetLayer() -1 ] += hit->GetEdep();
           G4double time = hit->GetTime();

           // if (time<lastTime) G4cout <<"\n\n ERROR \n\n" << G4endl;
           // else G4cout <<"\n\n tutto bene \n\n" << G4endl;
           lastTime = time;

           if ((start!=-1 && (time-start)<100*ns) || start==-1){

               if (thisEventTotEM[hit->GetLayer() -1]>1.5*MeV){
               		if (hit->GetLayer() ==1 && activationTimeFirst==-1){
               			activationTimeFirst = time;
               			// G4cout << " attivazione primo detector " << G4endl;
               		}
               		else if (hit->GetLayer() ==2 && start==-1 && activationTimeFirst!=-1 && (time-activationTimeFirst)<60*ns){
               			// G4cout << " segnale start " << G4endl;
               			start = time;
               		}
               		else if (hit->GetLayer() ==3 && start!=-1 && (time-start)<60*ns){
               			// G4cout << " false start " << G4endl;
               			start = -1;
               		}
           	    }
            }
            // if (start!=-1 && (time-start)>100*ns){
            else if (hit->GetProcess()>0){

                // stop event

    			// G4cout << "\n\nsegnale stop\n\n" << G4endl;
    			// if (abs(aTrack->GetDefinition()->GetPDGEncoding())!=11 && aTrack->GetDefinition()->GetPDGEncoding()!=22) return; // electrons
    			// const G4ThreeVector & pos = aTrack->GetPosition();
    		    // const G4ThreeVector & mom = aTrack->GetMomentumDirection();

                // G4cout << "decay" << G4endl;
    			HistoManager::GetInstance()->AddDecay();
    		    // histos[fDecayPosZ]->Fill(pos.y()/m);
    		    // histos[fDecayTime]->Fill((time-start)/microsecond);
    		    // if (mom.y()>0) histos[fDecayTimeForward]->Fill(time/microsecond);
    		    // else histos[fDecayTimeBackward]->Fill(time/microsecond);
    			// histoManager->HistoFill(fpos.y()/m);
    		    HistoManager::GetInstance()->HistoFill((time-start)/microsecond, 1);
    		    if (hit->GetDirection()>0)  HistoManager::GetInstance()->HistoFill(time/microsecond, 2);
    		    else HistoManager::GetInstance()->HistoFill(time/microsecond, 3);
    		}




           // HistoManager::GetInstance()->AddDecay();
           // // histos[fDecayPosZ]->Fill(pos.y()/m);
           // // histos[fDecayTime]->Fill((time-start)/microsecond);
           // // if (mom.y()>0) histos[fDecayTimeForward]->Fill(time/microsecond);
           // // else histos[fDecayTimeBackward]->Fill(time/microsecond);
           // // histoManager->HistoFill(fpos.y()/m);
           // HistoManager::GetInstance()->HistoFill(hit->GetTime(), 1);
           // G4cout << << G4endl;
       }
      }
   // }
  }


  if (evt->GetEventID()%10000==0) G4cout << "end of event " << evt->GetEventID() <<G4endl;

   // G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(collID));
   // std::map<G4int,G4double*>::iterator itr = evtMap->GetMap()->begin();
   // for(; itr != evtMap->GetMap()->end(); itr++) { fEDep += *(itr->second); }
  //
  G4Run::RecordEvent(evt);
}

void MyRun::Merge(const G4Run* aRun)
{
 // G4cout << "ciao" << G4endl;
  const MyRun* localRun = static_cast<const MyRun*>(aRun);
  // fEDep += localRun->fEDep;
  G4Run::Merge(aRun);
}
