// $Id: DetectorConstruction.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief Implements mandatory user class DetectorConstruction.
 */

#include "DetectorConstruction.hh"
//#include "DetectorMessenger.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//#include "SensitiveDetector.hh"
// #include "G4SDManager.hh"

#define CERBERO_SOPRA

DetectorConstruction::DetectorConstruction()
{
	fieldInitialized=false;
	//--------- Material definition ---------
	DefineMaterials();

	//--------- Sizes of the principal geometrical components (solids)  ---------
	ComputeParameters();
}

DetectorConstruction::~DetectorConstruction()
{
}

void DetectorConstruction::DefineMaterials()
{
	//Get Materials from NIST database
	G4NistManager* man = G4NistManager::Instance();
	man->SetVerbose(0);

	// define NIST materials
	// Scintillator
	// (PolyVinylToluene, C_9H_10)
    plastic = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	G4Element * elNa = new G4Element("Sodium", "Na", 11, 22.98977*g/mole);
	G4Element * elCl = new G4Element("Chlorine", "Cl", 17, 35.446*g/mole);
	NaCl = new G4Material("NaCl", 2.16*g/cm3, 2);
	NaCl->AddElement(elNa, 1);
	NaCl->AddElement(elCl, 1);

 	alluminium = man->FindOrBuildMaterial("G4_Al");

	// vacuum  = man->FindOrBuildMaterial("G4_Galactic");

	//Tracker
	air     = man->FindOrBuildMaterial("G4_AIR");
	// silicon = man->FindOrBuildMaterial("G4_Si");
	// //Em calo
	// pbw04   = man->FindOrBuildMaterial("G4_PbWO4");
	//Had calo
	// Liquid Argon has a  X0 = 10.971 cm  and  lambda_I = 65.769 cm.
	//G4double density = 1.4*g/cm3;
	//G4double  a = 39.95*g/mole;
	//G4int z = 18;
	//lar = new G4Material( "LiquidArgon", z, a, density );

	// lar = man->FindOrBuildMaterial("G4_lAr");
	// fe = man->FindOrBuildMaterial("G4_Fe");

}

void DetectorConstruction::ComputeParameters()
{
	//This function defines the defaults
	//of the geometry construction

	// ** world **
	halfWorldLength = 1* m;


	// Scintillators

	#ifdef CERBERO_SOPRA

		// // Cerbero sopra
		// scintLength = 80.*cm;
		// scintWidth = 30.*cm;
		// scintHeight = 4.*cm;
		// G4double scintSeparation23 = 2.*cm; //separation between lower scintillators
		// G4double scintSeparation12 = 2*cm;//separation between upper scintillators
		// // look at note for explanation of posFirstScint y compontent
		// posFirstScint  = G4ThreeVector(0., scintHeight/2 + scintSeparation23 + scintHeight + scintSeparation12 + scintHeight/4, 0.);
		// posSecondScint = G4ThreeVector(0., scintHeight/2 + scintSeparation23 + scintHeight/2, 0.);
		// posThirdScint  = G4ThreeVector(0., 0., 0.);



		scintLength = 80.*cm;
		scintWidth = 30.*cm;
		scintHeight = 4.*cm;
		G4double scintSeparation23 = 0.5*cm; //separation between lower scintillators
		G4double scintSeparation12 = 0.5*cm;//separation between upper scintillators
		// 0.08,0.265,0.01
		scintPiccoloLenght = 8*cm;
		// scintPiccoloWidth = 26.5*cm;
		scintPiccoloWidth = 31*cm;
		scintPiccoloHeight = 1*cm;
		// look at note for explanation of posFirstScint y compontent
		posFirstScint  = G4ThreeVector(0., scintPiccoloHeight/2 + scintSeparation23 + scintHeight + scintSeparation12 + scintPiccoloHeight/2, 1.5*cm);
		posSecondScint = G4ThreeVector(0, scintPiccoloHeight/2 + scintSeparation23 + scintHeight/2, 0);
		posThirdScint  = G4ThreeVector(0.*cm, 0., 1.5*cm);

	#else



		// Cerbero in mezzo

		scintLength = 80.*cm;
		scintWidth = 30.*cm;
		scintHeight = 4.*cm;
		G4double scintSeparation23 = 3.*cm; //separation between lower scintillators
		G4double scintSeparation12 = 4*cm;//separation between upper scintillators
		posFirstScint  = G4ThreeVector(0., scintHeight/2 + scintSeparation23 + scintHeight/2 + scintSeparation12 + scintHeight/2, 0.);
		posSecondScint = G4ThreeVector(0., scintHeight/2 + scintSeparation23 + scintHeight/4, 0.);
		posThirdScint  = G4ThreeVector(0., 0., 0.);

		materialLenght = scintLength;
		materialWidth = scintWidth;
		materialHeight = scintSeparation23;
		posMaterial    = G4ThreeVector(0., scintHeight/2 + scintSeparation23/2, 0.);
	#endif

	// // ** em calo **
	// emCaloCentralCrystalWidth = 22*mm;
	// emCaloWidth               = 110*mm;
	// emCaloLength              = 230*mm;
	// posEmCalo = -G4ThreeVector(0,0,emCaloLength/2);
	//
	// // ** Si tracker **
	// noOfSensorStrips = 600;//48;
	// sensorStripLength = 10.*mm;
	// sensorThickness = 300.*um;
	// teleStripPitch  = 80*um;//20. * um;
	// posFirstSensor  = G4ThreeVector(0., 0., -190*mm - emCaloLength);
	// posSecondSensor = G4ThreeVector(0., 0., -100*mm - emCaloLength);
	// posThirdSensor  = G4ThreeVector(0., 0., -10.*mm - emCaloLength);
	//
	// // ** Had Calorimeter **
	// hadCaloLArThickness = 8*mm;
	// hadCaloFeThickness = 20*mm;
	// hadCaloRadius = 800*mm;
	// hadCaloNumLayers = 80;
	// posHadCalo = G4ThreeVector(0,0,(hadCaloLArThickness+hadCaloFeThickness)*hadCaloNumLayers/2);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	//This function is called by G4 when the detector has to be created
	//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------


	//------------------------------
	// World
	//------------------------------

	G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2.*halfWorldLength);
	G4cout << "Computed tolerance = "
			<< G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
			<< " mm" << G4endl;


	G4Box * solidWorld= new G4Box("world",halfWorldLength,halfWorldLength,halfWorldLength);
	logicWorld= new G4LogicalVolume( solidWorld, air, "World", 0, 0, 0);

	//  Must place the World Physical volume unrotated at (0,0,0).
	//
	G4VPhysicalVolume * physiWorld = new G4PVPlacement(0,               // no rotation
			G4ThreeVector(), // at (0,0,0)
			logicWorld,      // its logical volume
			"World",         // its name
			0,               // its mother  volume
			false,           // no boolean operations
			0);              // copy number



	//Construction of the three si plane is actually done here
	//	ConstructTelescope();

	//Construction of the EM calorimeter
	//	ConstructEMCalo();

	//Construction of the Had calorimeter
	ConstructScintillator();

	//--------- Visualization attributes -------------------------------

	G4Color
		green(0.0,1.0,0.0),
		blue(0.0,0.0,1.0),
		brown(0.4,0.4,0.1),
		white(1.0,1.0,1.0);

	logicWorld -> SetVisAttributes(new G4VisAttributes(white));
	logicWorld -> SetVisAttributes(G4VisAttributes::Invisible);

	//always return the physical World
	//
	return physiWorld;
}

// G4VPhysicalVolume* DetectorConstruction::ConstructTelescope()
// {
// 	//
// 	// 1st Plane of Si tracker
// 	//
// 	G4double halfSensorSizeX = noOfSensorStrips*teleStripPitch/2.;
// 	G4double halfSensorSizeY = sensorStripLength/2.;
// 	G4double halfSensorSizeZ = sensorThickness/2.;
//
// 	G4Box * solidSensor = new G4Box("Sensor",
// 				   halfSensorSizeX,halfSensorSizeY,halfSensorSizeZ);
//
// 	G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor, // its solid
// 			silicon,	//its material
// 			"SensorPlane");	//its name
//
// 	physiFirstSensor = new G4PVPlacement(0,	//no rotation
// 				  posFirstSensor,
// 				  logicSensorPlane,		//its logical volume
// 				  "FirstSensor",		//its name
// 				  logicWorld,		//its mother  volume
// 				  false,			//no boolean operation
// 				  0);			//copy number
//
//
// 	// 2nd Plane of Si tracker
//
// 	physiSecondSensor = new G4PVPlacement(0,//rm,
// 						  posSecondSensor,
// 						  logicSensorPlane,
// 						  "SecondSensor",
// 						  logicWorld,
// 						  false,
// 						  1);			//copy number
//
// 	// 3rd Plane of Si tracker
// 	physiThirdSensor = new G4PVPlacement(0,
// 				  posThirdSensor,
// 				  logicSensorPlane,
// 				  "ThirdSensor",
// 				  logicWorld,
// 				  false,
// 				  2);			//copy number
//
// 	//
// 	// Strips
// 	//
// 	//Note that we use G4VReplica giving as logical volume
// 	//the logicSensorPlane as mother. This ensures that three
// 	//replicas will exists, one for each physical volume where
// 	//logicSensorPlane is used: the Si planes
// 	//In case of using DUT the thing is a bit different.
// 	G4double halfSensorStripSizeX = teleStripPitch/2.;
// 	G4double halfSensorStripSizeY = sensorStripLength/2.;
// 	G4double halfSensorStripSizeZ = sensorThickness/2.;
//
// 	G4Box * solidSensorStrip =
// 			new G4Box("SensorStrip",
// 					halfSensorStripSizeX,halfSensorStripSizeY,halfSensorStripSizeZ);
//
// 	G4LogicalVolume * logicSensorStrip =
// 			new G4LogicalVolume(solidSensorStrip,silicon,"SensorStrip");
//
// 	physiSensorStrip = new G4PVReplica("SensorStrip",		//its name
// 				logicSensorStrip,		//its logical volume
// 				logicSensorPlane,		//its mother
// 				kXAxis,		        //axis of replication
// 				noOfSensorStrips,		//number of replica
// 				teleStripPitch);	        //witdth of replica
//
//   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0);
//   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
//   logicSensorStrip -> SetVisAttributes(new G4VisAttributes(red));
//
//   return physiSecondSensor;
// }
//
//
// G4VPhysicalVolume* DetectorConstruction::ConstructEMCalo()
// {
// 	G4double halfEmCaloSizeX = emCaloWidth/2;
// 	G4double halfEmCaloSizeY = emCaloWidth/2;
// 	G4double halfEmCaloSizeZ = emCaloLength/2;
// 	G4double halfEmCentralSizeX = emCaloCentralCrystalWidth/2;
// 	G4double halfEmCentralSizeY = emCaloCentralCrystalWidth/2;
//
//
// 	G4Box* emSolid = new G4Box("emCaloSolid",halfEmCaloSizeX,halfEmCaloSizeY,halfEmCaloSizeZ);
//
// 	G4LogicalVolume* emLogic = new G4LogicalVolume( emSolid,//its solid
// 													pbw04, //its material
// 													"emCaloLogic");//its name
// 	emCalo = new G4PVPlacement(0, //no rotation
// 							   posEmCalo,//translation
// 							   emLogic, //its logical volume
// 							   "EmCalo",//its name
// 							   logicWorld,//its mother volume
// 							   false, //no boolean operation
// 							   10); //copy number
//
// 	G4Box* emCentralSolid=new G4Box("emCentralSolid",halfEmCentralSizeX,halfEmCentralSizeY,halfEmCaloSizeZ);
// 	G4LogicalVolume* emCentralLogic = new G4LogicalVolume( emCentralSolid,pbw04,"emCentralLogic");
// 	emCaloCentralCrystal = new G4PVPlacement( 0 , G4ThreeVector(0,0,0), emCentralLogic , "EmCentral", emLogic ,false, 11);
//
// 	G4Color yellow(1,1,0);
// 	emLogic->SetVisAttributes(new G4VisAttributes(yellow));
// 	G4Color red(1,0,0);
// 	emCentralLogic->SetVisAttributes(new G4VisAttributes(red));
// 	return emCalo;
// }


G4VPhysicalVolume* DetectorConstruction::ConstructScintillator()
{

	// G4double halfHadCaloHalfZ = (hadCaloFeThickness+hadCaloLArThickness)*hadCaloNumLayers/2;
	G4Box* scintPiccoloSolid = new G4Box( "scintSmallSolid",//its name
										scintPiccoloLenght/2, //halfX
										scintPiccoloHeight/4,//halfY
										scintPiccoloWidth/2); //halfZ
	// G4Box* scintSmallSolid = new G4Box( "scintSmallSolid",//its name
	// 									scintLength/2, //halfX
	// 									scintHeight/4,//halfY
	// 									scintWidth/2); //halfZ
	G4Box* scintBigSolid= new G4Box( "scintBigSolid",//its name
										scintLength/2, //halfX
										scintHeight/2,//halfY
										scintWidth/2); //halfZ
	#ifdef CERBERO_SOPRA

		G4LogicalVolume* scintLogicFirst = new G4LogicalVolume( scintPiccoloSolid,//its solid
															 plastic,//its material
															 "scintLogicFirst");//its name


		G4LogicalVolume* scintLogicSecond = new G4LogicalVolume( scintBigSolid,//its solid
															 plastic,//its material
															 "scintLogicSecond");//its name

		 G4LogicalVolume* scintLogicThird = new G4LogicalVolume( scintPiccoloSolid,//its solid
		 													 plastic,//its material
		 													 "scintLogicThird");//its name

	#else
		G4LogicalVolume* scintLogicFirst = new G4LogicalVolume( scintBigSolid,//its solid
															 plastic,//its material
															 "scintLogicFirst");//its name

		G4LogicalVolume* scintLogicSecond = new G4LogicalVolume( scintSmallSolid,//its solid
															 plastic,//its material
															 "scintLogicSecond");//its name

		 G4LogicalVolume* scintLogicThird = new G4LogicalVolume( scintBigSolid,//its solid
															 plastic,//its material
															 "scintLogicThird");//its name
		 G4Box* materialSolid= new G4Box( "material",//its name
												materialLenght/2, //halfX
												materialHeight/2,//halfY
												materialWidth/2); //halfZ
		G4LogicalVolume* materialLogic = new G4LogicalVolume( materialSolid,//its solid
															NaCl,//its material
															"material_for_decay");//its name
		Material = new G4PVPlacement(0,//rm,
							  posMaterial,
							  materialLogic,
							  "physical_material_for_decay",
							  logicWorld,
							  false,
							  4);			//copy number
		materialLogic->SetVisAttributes(new G4VisAttributes(G4Colour(0,0,1)));

	#endif

	G4Color
		green(0.0,1.0,0.0),
		blue(0.0,0.0,1.0),
		red	(1,0,0),
		white(1.0,1.0,1.0);

	scintLogicFirst-> SetVisAttributes(new G4VisAttributes(green));
	scintLogicSecond-> SetVisAttributes(new G4VisAttributes(white));
	scintLogicThird-> SetVisAttributes(new G4VisAttributes(red));

	physiFirstScint = new G4PVPlacement(0,	//no rotation
				  posFirstScint,
				  scintLogicFirst,		//its logical volume
				  "FirstSensor",		//its name
				  logicWorld,		//its mother  volume
				  false,			//no boolean operation
				  1);			//copy number


	// 2nd Plane of Si tracker

	// physiSecondScint = new G4PVPlacement(0,//rm,
	// 					  posSecondScint,
	// 					  scintLogicSecond,
	// 					  "SecondSensor",
	// 					  logicWorld,
	// 					  false,
	// 					  2);			//copy number


	//secondo scintillatore ruotato con campo magnetico
	// G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
	//   rotationMatrix->rotateY(90.*deg);
	//   physiSecondScint = new G4PVPlacement(rotationMatrix,//rm,
	  physiSecondScint = new G4PVPlacement(0,
							  posSecondScint,
							  scintLogicSecond,
							  "SecondSensor",
							  logicWorld,
							  false,
							  2);			//copy number
	// scintLogicSecond->SetFieldManager(GetLocalFieldManager(),false);

	// 3rd Plane of Si tracker
	physiThirdScint = new G4PVPlacement(0,
				  posThirdScint,
				  scintLogicThird,
				  "ThirdSensor",
				  logicWorld,
				  false,
				  3);			//copy number
	// for ( int layerIdx = 0 ; layerIdx < hadCaloNumLayers ; ++layerIdx )
	// {
	// 	G4ThreeVector position = (layerIdx+1)*absorberLayer + (layerIdx+0.5)*activeLayer;
	// 	position -= G4ThreeVector(0,0,halfHadCaloHalfZ);//Position is w.r.t. center of mother volume: the hadCaloLogic
	// 	new G4PVPlacement(0,position,hadLayerLogic,"HadCaloLayer",hadCaloLogic,false,++layerCopyNum);
	// }
	// hadCalo = new G4PVPlacement( 0, //no rotation
	// 						     posHadCalo, //translation
	// 						     hadCaloLogic,//its logical volume
	// 						     "HadCalo",//its name
	// 						     logicWorld,//its mother volume
	// 						     false,
	// 						     hadCaloCopyNum);//copy number



	// G4Colour green(0,1,0);
	// G4Colour white(1,1,1);
	// scintLogicFirst->SetVisAttributes(new G4VisAttributes(green));
	// scintLogicSecond->SetVisAttributes(new G4VisAttributes(green));
	// scintLogicThird->SetVisAttributes(new G4VisAttributes(green));
	// hadLayerLogic->SetVisAttributes(new G4VisAttributes(white));
	//hadLayerLogic->SetVisAttributes(G4VisAttributes::Invisible);
	return physiFirstScint;
}

#include "G4RunManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

void DetectorConstruction::UpdateGeometry()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());


}
//
// #include "G4FieldManager.hh"
// #include "G4UniformMagField.hh"
// #include "G4Mag_SpinEqRhs.hh"
// #include "G4ClassicalRK4.hh"
// #include "G4SimpleRunge.hh"
// #include "G4ChordFinder.hh"
// #include "G4MagIntegratorDriver.hh"
// #include "G4DormandPrince745.hh"
// #include "G4DormandPrinceRK78.hh"
//
// #include "G4EqEMFieldWithSpin.hh"
// #include "G4TransportationManager.hh"
// #include "G4PropagatorInField.hh"
// G4FieldManager* DetectorConstruction::GetLocalFieldManager()
// {
//   // pure magnetic field
//   G4ElectroMagneticField* fMagneticField =
//     new G4UniformMagField(G4ThreeVector(0, 0., 21*gauss));
//
//   // equation of motion with spin
//   // G4Mag_EqRhs* fEquation = new G4Mag_SpinEqRhs(fMagneticField);
//   //
//   // // local field manager
//   // G4FieldManager* fFieldManager = new G4FieldManager(fMagneticField);
//
//   G4EqEMFieldWithSpin* equation = new G4EqEMFieldWithSpin(fMagneticField);
//   G4FieldManager* fFieldManager
//       = G4TransportationManager::GetTransportationManager()->GetFieldManager();
//   fFieldManager->SetDetectorField(fMagneticField );
//
//   // default stepper Runge Kutta 4th order
//   // G4MagIntegratorStepper* fStepper = new G4ClassicalRK4( fEquation , 12); // spin needs 12 dof
//    // G4MagIntegratorStepper* fStepper = new G4SimpleRunge( fEquation , 12); // spin needs 12 dof
// G4MagIntegratorStepper* fStepper = new G4DormandPrinceRK78( equation , 12); // spin needs 12 dof
//   // add chord finder
//   G4double minStep           = 0.01*mm;
//
//    G4ChordFinder* chordFinder =
// 				  new G4ChordFinder((G4MagneticField*)fMagneticField,minStep,fStepper);
//   G4double deltaChord        = 3.0*mm;
//        chordFinder->SetDeltaChord( deltaChord );
//
//        G4double deltaOneStep      = 0.01*mm;
//        fFieldManager->SetAccuraciesWithDeltaOneStep(deltaOneStep);
//
//        G4double deltaIntersection = 0.1*mm;
//        fFieldManager->SetDeltaIntersection(deltaIntersection);
//
//        G4TransportationManager* transportManager =
//                              G4TransportationManager::GetTransportationManager();
//
//        G4PropagatorInField* fieldPropagator =
//                                         transportManager->GetPropagatorInField();
//
//        G4double epsMin            = 2.5e-7*mm;
//        G4double epsMax            = 0.05*mm;
//
//        fieldPropagator->SetMinimumEpsilonStep(epsMin);
//        fieldPropagator->SetMaximumEpsilonStep(epsMax);
//
//
//
//
//
//
// //   G4MagInt_Driver* driver = new G4MagInt_Driver
// // (10*mm, fStepper, fStepper->GetNumberOfVariables());
// // G4ChordFinder* fChordFinder = new G4ChordFinder(driver);
// // fFieldManager->SetDeltaOneStep(1e-2); // improved tracking precision
// // fFieldManager->SetMinimumEpsilonStep(1e-2);
// // fFieldManager->SetMaximumEpsilonStep(1e-2);
//   // G4double fMinStep=1*mm;
//   // G4ChordFinder* fChordFinder = new G4ChordFinder( fMagneticField, fMinStep,fStepper);
//   fFieldManager->SetChordFinder( chordFinder );
//   return fFieldManager;
// }
