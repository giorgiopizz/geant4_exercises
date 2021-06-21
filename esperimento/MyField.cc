#include "MyField.hh"
#include "G4SystemOfUnits.hh"

MyField::MyField()
{
  // messenger = new MyFieldMessenger(this);
  SetFieldValue(G4ThreeVector(0.,0.,21*gauss));
}

// ~MyField::MyField()
// {  }

void MyField::GetFieldValue(const double*, double* BF)
{ BF[0]=fieldVal.x(); BF[1]=fieldVal.y(); BF[2]=fieldVal.z(); }

void MyField::SetFieldValue(G4ThreeVector fVal)
{
  fieldVal = fVal;
  G4FieldManager* fMan
    = G4TransportationManager::GetTransportationManager()
        ->GetFieldManager();

G4Mag_EqRhs* fEquation = new G4Mag_SpinEqRhs(this);

G4MagIntegratorStepper* fStepper = new G4DormandPrinceRK78( fEquation , 12); // spin needs 12 dof

G4ChordFinder* fChordFinder = new G4ChordFinder( this, 1*mm,fStepper);


  fMan->SetDetectorField(this);
  // fMan->CreateChordFinder(this);



  fMan->SetChordFinder( fChordFinder );
}
