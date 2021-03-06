// $Id: DetectorConstruction.hh Geometry to study np production from polyethylene gcroci$
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

/**
 * @file
 * @brief Defines mandatory user class DetectorConstruction.
 */

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*!
\brief This mandatory user class defines the geometry.

It is responsible for
 - Definition of material, and
 - Construction of geometry

\sa Construct()
 */
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  //! Constructor
  DetectorConstruction();
  //! Destructor
  ~DetectorConstruction();
public:
  //! Construct geometry of the setup
  G4VPhysicalVolume* Construct();

  //! Update geometry
  void UpdateGeometry();
  
private:
  //! define needed materials
  void DefineMaterials();
  //! initialize geometry parameters
  void ComputeParameters();
  //! Construct the full geometry
  // Cu block representing the beam dump and a high density Ge Detector 
  G4VPhysicalVolume* Construct_PEConv_ArDet();
  
  

  
  

private:

  //! \name Materials
  //@{

  G4Material* vacuum;
  G4Material* PE_Mat;
  G4Material* Ar_Mat;


  //@}

  //! \name Geometry
  //@{

  ////DECLARE LOGICAL VOLUMES!!!!

  //! global mother volume
  G4LogicalVolume * logicWorld;

  //! PE Converter
  G4LogicalVolume * logicPEConv;

  //!High Density Ge Detector
  G4LogicalVolume * logicArDet;

  
  ///DECLARE PHYSICAL VOLUMES

  //!!Beam Dump physical volume 
  G4VPhysicalVolume* physiPEConv;
  
  //!! High Density Ge Detector
  G4VPhysicalVolume* physiArDet;

  //@{

  //DECLARE GEOMETRICAL PARAMETERS
  
  // ** World **
  G4double halfWorldLength;
  
  // ** PE Converter **
  G4double halfPEConv_x;
  G4double halfPEConv_y;
  G4double halfPEConv_z;

  // ** High Density Ge Detector **

  G4double halfArDet_x;
  G4double halfArDet_y;
  G4double halfArDet_z;

  G4double ArDet_z_displacement;

  //@}

  //! \name UI Messenger 
  //@{
  DetectorMessenger * messenger;
  //@}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
