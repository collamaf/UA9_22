//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4CrystalExtension.hh"
#include "G4ExtendedMaterial.hh"
#include "G4LogicalCrystalVolume.hh"

#include "G4ChannelingMaterialData.hh"
#include "G4ChannelingOptrMultiParticleChangeCrossSection.hh"

#include "SensitiveDetector.hh"

#include "G4SDManager.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(const std::map<G4String,G4double> & ParameterMap):
fECfileName("Si220pl"),
fMaterialName("G4_Si"),
fSizes(G4ThreeVector(1.*CLHEP::mm,
										 70.*CLHEP::mm,
										 1.94 * CLHEP::mm)),
fBR(G4ThreeVector(0.,0.,0.)),
fAngles(G4ThreeVector(0.,0.,0.)),
fSiDetSizes(G4ThreeVector(38.*mm,38.*mm,0.3*mm)),
fParameterMap(ParameterMap),
fSizes2(G4ThreeVector(1.*CLHEP::mm,
										 70.*CLHEP::mm,
										 1.94 * CLHEP::mm)),
fBR2(G4ThreeVector(0.,0.,0.)),
fAngles2(G4ThreeVector(0.,0.,0.)),
fSizes3(G4ThreeVector(1.*CLHEP::mm,
										 70.*CLHEP::mm,
										 1.94 * CLHEP::mm)),
fBR3(G4ThreeVector(0.,0.,0.)),
fAngles3(G4ThreeVector(0.,0.,0.)){
	fMessenger = new DetectorConstructionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void DetectorConstruction::DefineMaterials(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct(){
	
	//#####################################
	//** World **//
	G4Material* worldMaterial =
	G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
	
	G4Material* matPb =
	G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
	
	G4double worldSizeXY =  1. * CLHEP::meter;
	G4double worldSizeZ  = 45. * CLHEP::meter;
	
	G4Box* worldSolid = new G4Box("world.solid",
																worldSizeXY/2.,
																worldSizeXY/2.,
																worldSizeZ/2.);
	
	G4LogicalVolume* worldLogic = new G4LogicalVolume(worldSolid,
																										worldMaterial,
																										"world.logic");
	
	G4PVPlacement* worldPhysical = new G4PVPlacement(0,
																									 G4ThreeVector(),
																									 worldLogic,
																									 "world.physic",
																									 0,
																									 false,
																									 0);
	//#####################################

	//#####################################
	//** Detectors instantiation **//
	G4ThreeVector fDetectorSizes = fSiDetSizes;
	//  G4ThreeVector fDetectorSizes(G4ThreeVector(38.0 * CLHEP::mm,
	//					     38.0 * CLHEP::mm,
	//					     fSiDetThickness)); // was 0.64 mm
//	G4double fDetectorDistance[4] = {
//		-1.320 * CLHEP::m,
//		-0.320 * CLHEP::m,
//		+0.320 * CLHEP::m,
//		+10.32 * CLHEP::m};
	std::vector<G4double> fDetectorDistance = {
//	G4double fDetectorDistance[4] = {
		fParameterMap["Det0Z"]?fParameterMap["Det0Z"] * CLHEP::m : -1.320 * CLHEP::m,
		fParameterMap["Det1Z"]?fParameterMap["Det1Z"] * CLHEP::m : -0.320 * CLHEP::m,
		fParameterMap["Det2Z"]?fParameterMap["Det2Z"] * CLHEP::m : +0.320 * CLHEP::m,
		fParameterMap["Det3Z"]?fParameterMap["Det3Z"] * CLHEP::m : +10.32 * CLHEP::m
		
	};
	
	if (fParameterMap["Setup"]==2){ //MUonE case - Sept.22
		fDetectorDistance[0]= -4*CLHEP::m;
		fDetectorDistance[1]= -0.3*CLHEP::m;
		fDetectorDistance[2]= 0.3*CLHEP::m;
		fDetectorDistance[3]= 0.5*CLHEP::m;
		fDetectorDistance.push_back(4*CLHEP::m);
		fDetectorSizes.setZ(0.7*CLHEP::mm);
	}else if (fParameterMap["Setup"]==2.5){
		fDetectorDistance[0]= -3*CLHEP::m;
		fDetectorDistance[1]= -0.32*CLHEP::m;
		fDetectorDistance[2]= 0.3*CLHEP::m;
		fDetectorDistance[3]= 0.5*CLHEP::m;
		fDetectorDistance.push_back(5*CLHEP::m);
	}else if (fParameterMap["Setup"]==3){
		fDetectorDistance[0]= -9.5*CLHEP::m;
		fDetectorDistance[1]= -0.32*CLHEP::m;
		fDetectorDistance[2]= 0.32*CLHEP::m;
		fDetectorDistance[3]= 1.5*CLHEP::m;
		fDetectorDistance.push_back(11*CLHEP::m);
		fDetectorSizes.setZ(0.7*CLHEP::mm);
	}
	
	G4cout<<"POS DET " <<fDetectorDistance[0] / CLHEP::m<<G4endl;
	G4cout<<"POS DET " <<fDetectorDistance[1] / CLHEP::m<<G4endl;
	G4cout<<"POS DET " <<fDetectorDistance[2] / CLHEP::m<<G4endl;
	G4cout<<"POS DET " <<fDetectorDistance[3] / CLHEP::m<<G4endl;
	if (fParameterMap["Setup"]==2 || fParameterMap["Setup"]==3) G4cout<<"POS DET " <<fDetectorDistance[4] / CLHEP::m<<G4endl;
	
	if (fParameterMap["Telescope"]) {
		fDetectorDistance.clear();
		fDetectorDistance.push_back(10.4*CLHEP::m);
		fDetectorDistance.push_back(19.9*CLHEP::m);
	}
	
	G4Box* ssdSolid = new G4Box("ssd.solid",
															fDetectorSizes.x()/2.,
															fDetectorSizes.y()/2.,
															fDetectorSizes.z()/2.);
	
	G4Material* detectorMaterial =
	G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
	if (fParameterMap["NoDet"]) detectorMaterial=worldMaterial; //If requested remove detectors (make them void)
	G4LogicalVolume* ssdLogic =
	new G4LogicalVolume(ssdSolid,
											detectorMaterial,
											"ssd.logic");
	
	for(size_t i1=0;i1<fDetectorDistance.size();i1++){
		new G4PVPlacement(0,
											G4ThreeVector(0.,0.,fDetectorDistance[i1]),
											ssdLogic,
											"ssd.physic",
											worldLogic,
											false,
											i1);
	}
	
	G4ThreeVector posX=G4ThreeVector(fParameterMap["CrystDX"]?fParameterMap["CrystDX"]*CLHEP::mm:0,0,0);
	G4ThreeVector posX2=G4ThreeVector(20*CLHEP::mm,0,0);
	G4ThreeVector posX3=G4ThreeVector(0,0,10*CLHEP::m);
	
	if (fParameterMap["Setup"]==3){
		posX=G4ThreeVector(0,0,-10*CLHEP::m);
	}
	
	//#####################################
//	G4cout << "MYDEBUG " << __FILE__<< " " << __LINE__<< " " << __FUNCTION__<<G4endl;
	//#####################################
	//** Crystal **//
	//	if (fParameterMap["CrystX"]) SetSizes(G4ThreeVector(fParameterMap["CrystX"]*CLHEP::mm,fParameterMap["CrystY"]*CLHEP::mm,fParameterMap["CrystZ"]*CLHEP::mm));
	if (fParameterMap["CrystX"]) SetSizeX(fParameterMap["CrystX"]*CLHEP::mm);
	if (fParameterMap["CrystY"]) SetSizeY(fParameterMap["CrystY"]*CLHEP::mm);
	if (fParameterMap["CrystZ"]) SetSizeZ(fParameterMap["CrystZ"]*CLHEP::mm);
	
	G4Box* crystalSolid = new G4Box("crystal.solid",
																	fSizes.x()/2.,
																	fSizes.y()/2.,
																	fSizes.z()/2.);
	
	G4Box* crystalSolid2;
	G4Box* crystalSolid3;

	if (fParameterMap["Setup"]==3) {
		crystalSolid2 = new G4Box("crystal2.solid",
																		fSizes2.x()/2.,
																		fSizes2.y()/2.,
																		fSizes2.z()/2.);
		crystalSolid3 = new G4Box("crystal3.solid",
																		fSizes3.x()/2.,
																		fSizes3.y()/2.,
																		fSizes3.z()/2.);
	}
	
	G4Material* mat =
	G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
	
	G4CrystalUnitCell* uCell=new G4CrystalUnitCell(5.43 * CLHEP::angstrom,
																											5.43 * CLHEP::angstrom,
																											5.43 * CLHEP::angstrom,
																											CLHEP::halfpi,
																											CLHEP::halfpi,
																											CLHEP::halfpi,
																											227);

#if 1
	G4ExtendedMaterial* Crystal = new G4ExtendedMaterial("crystal.material",mat);
	G4ExtendedMaterial* Crystal2 = new G4ExtendedMaterial("crystal2.material",mat);
	G4ExtendedMaterial* Crystal3 = new G4ExtendedMaterial("crystal3.material",mat);


	// Dichiariamo che crystal è un materiale di tipo cristallo (condizione necessaria affinchè vi avvenga il channeling)
	Crystal ->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal )));
	Crystal2->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal2)));
	Crystal3->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal3)));
	
	G4CrystalExtension* crystalExtension  = 	(G4CrystalExtension*)Crystal ->RetrieveExtension("crystal");
	G4CrystalExtension* crystalExtension2 = 	(G4CrystalExtension*)Crystal2->RetrieveExtension("crystal");
	G4CrystalExtension* crystalExtension3 = 	(G4CrystalExtension*)Crystal3->RetrieveExtension("crystal");
	
	// Ne definiamo le caratteritiche del reticolo cristallino
	crystalExtension ->SetUnitCell(uCell);
	crystalExtension2->SetUnitCell(uCell);
	crystalExtension3->SetUnitCell(uCell);
	
	// Dichiariamo che in questo materiale esteso avviene il channeling
	Crystal ->RegisterExtension(std::unique_ptr<G4ChannelingMaterialData>(new G4ChannelingMaterialData("channeling")));
	Crystal2->RegisterExtension(std::unique_ptr<G4ChannelingMaterialData>(new G4ChannelingMaterialData("channeling")));
	Crystal3->RegisterExtension(std::unique_ptr<G4ChannelingMaterialData>(new G4ChannelingMaterialData("channeling")));
	G4ChannelingMaterialData* crystalChannelingData =	(G4ChannelingMaterialData*)Crystal->RetrieveExtension("channeling");
	G4ChannelingMaterialData* crystalChannelingData2 =	(G4ChannelingMaterialData*)Crystal2->RetrieveExtension("channeling");
	G4ChannelingMaterialData* crystalChannelingData3 =	(G4ChannelingMaterialData*)Crystal3->RetrieveExtension("channeling");
	
	// Definiamo le caratteristiche di questo channeling: file con i potenziali dei piani e BR
	crystalChannelingData ->SetFilename(fECfileName);
	crystalChannelingData2->SetFilename(fECfileName);
	crystalChannelingData3->SetFilename(fECfileName);
	
	
	if(fBR!=G4ThreeVector()){
		if (fParameterMap["BR"]) {
			G4cout<<"DetConst modifica BR "<< fParameterMap["BR"]<<G4endl;
			crystalChannelingData->SetBR(fParameterMap["BR"]*CLHEP::m);
			//			crystalChannelingData2->SetBR(-fParameterMap["BR"]*CLHEP::m);
		} else  {
			crystalChannelingData->SetBR(fBR.x());
			//			crystalChannelingData2->SetBR(-fBR.x());
		}
	}
	
	if(fBR2!=G4ThreeVector()){
		if (fParameterMap["BR2"]) {
			G4cout<<"DetConst modifica BR2 "<< fParameterMap["BR2"]<<G4endl;
			crystalChannelingData2->SetBR(fParameterMap["BR2"]*CLHEP::m);
		} else  {
			crystalChannelingData2->SetBR(fBR2.x());
		}
	}
	
	if(fBR3!=G4ThreeVector()){
		if (fParameterMap["BR3"]) {
			G4cout<<"DetConst modifica BR3 "<< fParameterMap["BR3"]<<G4endl;
			crystalChannelingData3->SetBR(fParameterMap["BR3"]*CLHEP::m);
		} else  {
			crystalChannelingData3->SetBR(fBR3.x());
		}
	}
	
	
	G4ThreeVector temp;
	G4cout<<"DetConst BendingRadius= "<< crystalChannelingData->GetBR(temp)/CLHEP::m<<" "<<temp.x()/CLHEP::m<<G4endl;
	if (fParameterMap["Setup"]==3) {
		G4cout<<"DetConst BendingRadius2= "<< crystalChannelingData2->GetBR(temp)/CLHEP::m<<" "<<temp.x()/CLHEP::m<<G4endl;
		G4cout<<"DetConst BendingRadius3= "<< crystalChannelingData3->GetBR(temp)/CLHEP::m<<" "<<temp.x()/CLHEP::m<<G4endl;
	}

#endif
	G4LogicalVolume* dummyCrystalLogic = //Fake crystal (made of void) to be placed when a no-crystal run is needed
	new G4LogicalVolume(crystalSolid,
											worldMaterial,
											"crystal.dummy");
	
	G4LogicalVolume* noChCrystalLogic = //Fake crystal (made of not channeling Si) to be placed when a no-ch run is needed
	new G4LogicalVolume(crystalSolid,
											mat,
											"crystal.noCh");
	
	G4LogicalCrystalVolume* crystalLogic = new G4LogicalCrystalVolume(crystalSolid,
														 Crystal, // creiamo il cristallo con il materiale "esteso"
														 "crystal.logic");
	crystalLogic->SetVerbose(1);
	
//	G4LogicalCrystalVolume* crystalLogic =
//	new G4LogicalCrystalVolume(crystalSolid,
//														 Crystal, // creiamo il cristallo con il materiale "esteso"
//														 "crystal.logic");
	G4LogicalCrystalVolume* crystalLogic2;
	G4LogicalCrystalVolume* crystalLogic3;

	if (fParameterMap["Setup"]==3) {
		crystalLogic2 =
		new G4LogicalCrystalVolume(crystalSolid2,
															 Crystal2, // creiamo il cristallo con il materiale "esteso"
															 "crystal2.logic");
		crystalLogic2->SetVerbose(1);
		
		crystalLogic3 =
		new G4LogicalCrystalVolume(crystalSolid3,
															 Crystal3, // creiamo il cristallo con il materiale "esteso"
															 "crystal3.logic");
		crystalLogic3->SetVerbose(1);
		
	}
	
	
	//** Crystal Definition End **//
	//#####################################

	G4RotationMatrix* rot = new G4RotationMatrix;
	if(fAngles.x()!=0.){
		rot->rotateX(fAngles.x());
	}
	if(fAngles.y()!=0.){
		rot->rotateY(fAngles.y());
	}
	if (fParameterMap["CrystAng"]){ //if I asked a particular angle rotation along Y..
		rot->rotateY(fParameterMap["CrystAng"]*CLHEP::rad);
	} else
	if(fAngles.z()!=0.){
		rot->rotateZ(fAngles.z());
	}
	G4cout<<"Matrice rotazione x1:"<<G4endl;
	rot->print(G4cout);

	G4RotationMatrix* rot2 = new G4RotationMatrix;
	if(fAngles2.x()!=0.){
		rot2->rotateX(fAngles2.x());
	}
	if(fAngles2.y()!=0.){
		rot2->rotateY(fAngles2.y());
	}
	if (fParameterMap["CrystAng2"]){ //if I asked a particular angle rotation along Y..
		rot2->rotateY(fParameterMap["CrystAng2"]*CLHEP::rad);
	} else
	if(fAngles2.z()!=0.){
		rot2->rotateZ(fAngles2.z());
	}
	G4cout<<"Matrice rotazione x2:"<<G4endl;
	rot2->print(G4cout);
	
	G4RotationMatrix* rot3 = new G4RotationMatrix;
	if(fAngles3.x()!=0.){
		rot3->rotateX(fAngles3.x());
	}
	if(fAngles3.y()!=0.){
		rot3->rotateY(fAngles3.y());
	}
	if (fParameterMap["CrystAng3"]){ //if I asked a particular angle rotation along Y..
		rot3->rotateY(fParameterMap["CrystAng3"]*CLHEP::rad);
	} else
	if(fAngles3.z()!=0.){
		rot3->rotateZ(fAngles3.z());
	}
	G4cout<<"Matrice rotazione x3:"<<G4endl;
	rot3->print(G4cout);
//	if(fAngles.y()!=0.){
////		rot2->rotateY(-fAngles.y());
//		rot2->rotateY(CLHEP::pi*CLHEP::rad-fAngles.y());
//		G4cout<<"AAAA ruoto di "<<CLHEP::pi*CLHEP::rad+fAngles.y()<<G4endl;
//		rot2->print(G4cout);
//	}
//	if (fParameterMap["CrystAng"]){ //if I asked a particular angle rotation along Y..
//		rot2->rotateY(-fParameterMap["CrystAng"]*CLHEP::rad);
////		rot2->rotateY(CLHEP::halfpi*CLHEP::rad-fParameterMap["CrystAng"]);
//		G4cout<<"AAAA ruoto di "<<CLHEP::halfpi*CLHEP::rad-fParameterMap["CrystAng"]<<G4endl;
//	}

	
	
	G4VPhysicalVolume* physCrystal;
	if(fParameterMap["NoCryst"]){
		physCrystal= new G4PVPlacement(rot,
																	 posX,
																	 dummyCrystalLogic, /***/
																	 "crystal.physic",
																	 worldLogic,
																	 false,
																	 0);
	} if(fParameterMap["NoCh"]){
		physCrystal= new G4PVPlacement(rot,
																	 posX,
																	 noChCrystalLogic, /***/
																	 "crystal.physic",
																	 worldLogic,
																	 false,
																	 0);
	} else {
		physCrystal= new G4PVPlacement(rot,
																	 posX,
																	 crystalLogic,
																	 "crystal.physic",
																	 worldLogic,
																	 false,
																	 0);
	}
	
	if(fParameterMap["Setup"]==3){
		
		if(fParameterMap["NoCryst2"]){
			new G4PVPlacement(rot2,
												posX2,
												dummyCrystalLogic, /***/
												"crystal2.physic",
												worldLogic,
												false,
												0);
		} else {
			new G4PVPlacement(rot2,
												//											G4ThreeVector(-fSizes.z()*sin(fAngles.y()),0,fSizes.z()+0*CLHEP::mm),
												posX2,
												crystalLogic2, /***/
												"crystal2.physic",
												worldLogic,
												false,
												0);
		}
		new G4PVPlacement(rot3,
//											G4ThreeVector(-fSizes.z()*sin(fAngles.y()),0,fSizes.z()+0*CLHEP::mm),
											posX3,
											crystalLogic3, /***/
											"crystal3.physic",
											worldLogic,
											false,
											0);
	}
	
	
	
#ifndef G4MULTITHREADED
	G4ChannelingOptrMultiParticleChangeCrossSection* testMany =
	new G4ChannelingOptrMultiParticleChangeCrossSection();
	testMany->AttachTo(crystalLogic);
	G4cout << " Attaching biasing operator " << testMany->GetName()
	<< " to logical volume " << crystalLogic->GetName()
	<< G4endl;
	
	if(fParameterMap["Setup"]==3){
		testMany->AttachTo(crystalLogic2);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic2->GetName()
		<< G4endl;
		
		testMany->AttachTo(crystalLogic3);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic2->GetName()
		<< G4endl;
	}
	
	G4VSensitiveDetector* telescope = new SensitiveDetector("/telescope");
	G4SDManager::GetSDMpointer()->AddNewDetector(telescope);
	for(unsigned int i1=0;i1<3;i1++){
		ssdLogic->SetSensitiveDetector(telescope);
	}
#endif
	
	
	//-- Dummy planes to score particles
	G4double dummyPlane_DX=1*m;
	G4double dummyPlane_DY=1*m;
	G4double dummyPlane_DZ=.1*mm;
	G4double delta=0.00*mm;
	G4bool checkOverlaps=true;
	
	G4double dummyPlane0_Z=fParameterMap["Plane0Z"] ?fParameterMap["Plane0Z"] *m : -10.4999*m; // at beam orogin
	G4double dummyPlane1_Z=fParameterMap["Plane1Z"] ?fParameterMap["Plane1Z"] *m :posX.z()-fSizes.z()/2.-delta-dummyPlane_DZ/2.; // right before crystal
	G4double dummyPlane2_Z=fParameterMap["Plane2Z"] ?fParameterMap["Plane2Z"] *m :posX.z()+fSizes.z()/2.+delta+dummyPlane_DZ/2.; // right after crystal
	G4double dummyPlane3_Z=fParameterMap["Plane3Z"] ?fParameterMap["Plane3Z"] *m :-dummyPlane0_Z; // symmetrical
	G4double dummyPlane4_Z=posX2.z()-fSizes2.z()/2.-delta-dummyPlane_DZ/2.; // right before crystal2
	G4double dummyPlane5_Z=posX2.z()+fSizes2.z()/2.+delta+dummyPlane_DZ/2.; // right after crystal2
	G4double dummyPlane6_Z=posX3.z()-fSizes3.z()/2.-delta-dummyPlane_DZ/2.; // right before crystal3
	G4double dummyPlane7_Z=20*m; // at the very end
	
	if (fParameterMap["Telescope"]) {
		dummyPlane3_Z=fDetectorDistance[0]+fDetectorSizes.z()/2.+100*um;
		dummyPlane7_Z=fDetectorDistance[1]+fDetectorSizes.z()/2.+100*um;
	}

	if (fParameterMap["Setup"]==2){ //MUonE case - Sept.22
		dummyPlane0_Z= -4*CLHEP::m+fDetectorSizes.z();
		dummyPlane1_Z= -0.3*CLHEP::m+fDetectorSizes.z();
		dummyPlane2_Z= 0.3*CLHEP::m+fDetectorSizes.z();
		dummyPlane3_Z= 0.5*CLHEP::m+fDetectorSizes.z();
		dummyPlane4_Z= 4*CLHEP::m+fDetectorSizes.z();
	} else if (fParameterMap["Setup"]==2.5){ //MUonE case - Sept.22
		dummyPlane0_Z= -3*CLHEP::m+fDetectorSizes.z();
		dummyPlane1_Z= -0.32*CLHEP::m+fDetectorSizes.z();
		dummyPlane2_Z= 0.3*CLHEP::m+fDetectorSizes.z();
		dummyPlane3_Z= 0.5*CLHEP::m+fDetectorSizes.z();
		dummyPlane4_Z= 5*CLHEP::m+fDetectorSizes.z();
	}
	G4ThreeVector posDummyPlane0= G4ThreeVector(0, 0, dummyPlane0_Z);
	G4ThreeVector posDummyPlane1= G4ThreeVector(0, 0, dummyPlane1_Z);
	G4ThreeVector posDummyPlane2= G4ThreeVector(0, 0, dummyPlane2_Z);
	G4ThreeVector posDummyPlane3= G4ThreeVector(0, 0, dummyPlane3_Z);
	G4ThreeVector posDummyPlane4= G4ThreeVector(0, 0, dummyPlane4_Z);
	G4ThreeVector posDummyPlane5= G4ThreeVector(0, 0, dummyPlane5_Z);
	G4ThreeVector posDummyPlane6= G4ThreeVector(0, 0, dummyPlane6_Z);
	G4ThreeVector posDummyPlane7= G4ThreeVector(0, 0, dummyPlane7_Z);

	G4cout<<"POS PIANI 0 " <<posDummyPlane0.z()/m <<G4endl;
	G4cout<<"POS PIANI 1 " <<posDummyPlane1.z()/m <<G4endl;
	G4cout<<"POS PIANI 2 " <<posDummyPlane2.z()/m <<G4endl;
	G4cout<<"POS PIANI 3 " <<posDummyPlane3.z()/m <<G4endl;
	G4cout<<"POS PIANI 4 " <<posDummyPlane4.z()/m <<G4endl;
	G4cout<<"POS PIANI 5 " <<posDummyPlane5.z()/m <<G4endl;
	G4cout<<"POS PIANI 6 " <<posDummyPlane6.z()/m <<G4endl;
	G4cout<<"POS PIANI 7 " <<posDummyPlane7.z()/m <<G4endl;

	G4Box* geoDummyPlane = new G4Box("geoDummyPlane", dummyPlane_DX/2, dummyPlane_DY/2, dummyPlane_DZ/2);
	G4LogicalVolume* logicDummyPlane = new G4LogicalVolume(geoDummyPlane, worldMaterial, "logicDummyPlane");
	
	new G4PVPlacement(0,posDummyPlane0,logicDummyPlane,"physDummyPlane",worldLogic,false,0,checkOverlaps);
	new G4PVPlacement(0,posDummyPlane1,logicDummyPlane,"physDummyPlane",worldLogic,false,1,checkOverlaps);
	new G4PVPlacement(0,posDummyPlane2,logicDummyPlane,"physDummyPlane",worldLogic,false,2,checkOverlaps);
	new G4PVPlacement(0,posDummyPlane3,logicDummyPlane,"physDummyPlane",worldLogic,false,3,checkOverlaps);
	if(fParameterMap["Setup"]==3){
		new G4PVPlacement(0,posDummyPlane4,logicDummyPlane,"physDummyPlane",worldLogic,false,4,checkOverlaps);
		new G4PVPlacement(0,posDummyPlane5,logicDummyPlane,"physDummyPlane",worldLogic,false,5,checkOverlaps);
		new G4PVPlacement(0,posDummyPlane6,logicDummyPlane,"physDummyPlane",worldLogic,false,6,checkOverlaps);
		new G4PVPlacement(0,posDummyPlane7,logicDummyPlane,"physDummyPlane",worldLogic,false,7,checkOverlaps);

	}
	if(fParameterMap["Setup"]==2||fParameterMap["Setup"]==2.5){
		new G4PVPlacement(0,posDummyPlane4,logicDummyPlane,"physDummyPlane",worldLogic,false,4,checkOverlaps);
	}
	// ################## MAGNET VOLUME #####################
	//Bending Magnet
	G4double Mag_R = 100.*cm;
	G4double Mag_sizeY = 40.*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	G4ThreeVector posMag  = G4ThreeVector(0,0,3*m); // Subdet
	
	G4Tubs* geoMag = new G4Tubs("Mag",0*cm,Mag_R,Mag_sizeY/2.,startAngle,spanningAngle);
	G4RotationMatrix *MagRot = new G4RotationMatrix;
	MagRot->rotateX(90.*deg);
	G4LogicalVolume* logicMag = new G4LogicalVolume(geoMag,worldMaterial,"Mag");
	new G4PVPlacement(MagRot,posMag,logicMag,"Mag",worldLogic,false,0,checkOverlaps);
	// ######################################################
	
	return worldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
void DetectorConstruction::ConstructSDandField(){
	G4LogicalVolume* crystalLogic =
	G4LogicalVolumeStore::GetInstance()->GetVolume("crystal.logic");
	G4ChannelingOptrMultiParticleChangeCrossSection* testMany =
	new G4ChannelingOptrMultiParticleChangeCrossSection();
	testMany->AttachTo(crystalLogic);
	G4cout << " Attaching biasing operator " << testMany->GetName()
	<< " to logical volume " << crystalLogic->GetName()
	<< G4endl;
	
	if(fParameterMap["Setup"]==3){
		G4LogicalVolume* crystalLogic2 =
		G4LogicalVolumeStore::GetInstance()->GetVolume("crystal2.logic");
		testMany->AttachTo(crystalLogic2);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic2->GetName()
		<< G4endl;
		
		G4LogicalVolume* crystalLogic3 =
		G4LogicalVolumeStore::GetInstance()->GetVolume("crystal3.logic");
		testMany->AttachTo(crystalLogic3);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic2->GetName()
		<< G4endl;
		
	}
	G4LogicalVolume* ssdLogic =
	G4LogicalVolumeStore::GetInstance()->GetVolume("ssd.logic");
	G4VSensitiveDetector* telescope = new SensitiveDetector("/telescope");
	G4SDManager::GetSDMpointer()->AddNewDetector(telescope);
	for(unsigned int i1=0;i1<3;i1++){
		ssdLogic->SetSensitiveDetector(telescope);
	}
	
	G4UniformMagField* myField = new G4UniformMagField(G4ThreeVector(0., fParameterMap["Mag"]*tesla, 0.));
	G4LogicalVolume* logicBend = G4LogicalVolumeStore::GetInstance()->GetVolume("Mag");
	G4FieldManager* localfieldMgr = new G4FieldManager(myField);
	logicBend->SetFieldManager(localfieldMgr,true);
	localfieldMgr->CreateChordFinder(myField);
	
	
}
#else
void DetectorConstruction::ConstructSDandField(){;}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
