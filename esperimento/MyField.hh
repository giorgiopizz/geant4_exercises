#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4Mag_SpinEqRhs.hh"
#include "G4ClassicalRK4.hh"
#include "G4SimpleRunge.hh"
#include "G4ChordFinder.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4DormandPrince745.hh"
#include "G4DormandPrinceRK78.hh"

#include "G4EqEMFieldWithSpin.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"


#ifndef MYFIELD_hh
#define MYFIELD_hh 1



class MyField : public G4MagneticField
{
 public:
   MyField();
   virtual ~MyField();

   virtual void GetFieldValue(const double*, double* ) ;
   void SetFieldValue(G4ThreeVector);

 private:
   // MyFieldMessenger* messenger;
   G4ThreeVector fieldVal;
};
#endif
