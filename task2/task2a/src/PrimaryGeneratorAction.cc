/*!
  \file
  \brief implements mandatory user class PrimaryGeneratorAction
*/

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4UnitsTable.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{

  gun  = new G4ParticleGun();
  // Exercise 2a.1
  // complete particle name and energy here below (do not forget the energy unit)
  // if you don't update here, the default will be created, namely: 1 GeV
  // geantino
  // --> from here
  particle = G4ParticleTable::GetParticleTable()->FindParticle("pi-");
  gun->SetParticleDefinition(particle);
  gun->SetParticleEnergy(1*GeV);
  // <-- to here

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete gun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called to generate each G4 event

  // Ex 2a.2 : generate only one particle
  // --> from here
  G4double x0 = 0.*cm, y0 = 0.*cm, z0= 0.0*cm;
  G4cout<<"GeneratePrimaries : new event "<<G4BestUnit(G4ThreeVector(x0,y0,z0),"Length")<<G4endl;
  gun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  gun->GeneratePrimaryVertex(anEvent);
  // <-- to here



  // Ex 2a.3 : to generate a set of particles uniformly distributed
  // --> from here
  G4double a, b;
  a = 2*mm;
  b = 4*mm;

  G4double z0 = 0;
  G4double x0 = 2*a*(G4UniformRand()-0.5);
  G4double y0 = 2*b*(G4UniformRand()-0.5);

  gun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  gun->GeneratePrimaryVertex(anEvent);
  // <-- to here


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
