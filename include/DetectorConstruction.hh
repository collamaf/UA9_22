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
// --------------------------------------------------------------
//

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1
#endif

#include "G4VUserDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "DetectorConstructionMessenger.hh"

#include "globals.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	
	DetectorConstruction(const std::map<G4String,G4double> &);
	~DetectorConstruction();
	
	void DefineMaterials();
	G4VPhysicalVolume* Construct();
	
private:
	void ConstructSDandField();
	
private:
	DetectorConstructionMessenger* fMessenger;
	
public:
	G4String GetEC() {return fECfileName;}
	void SetEC(G4String aString) {fECfileName = aString;}
	
	G4String GetMaterial() {return fMaterialName;}
	void SetMaterial(G4String aString) {fMaterialName = aString;}
	
	G4ThreeVector GetSizes() {return fSizes;}
	void SetSizes(G4ThreeVector a3vec) {fSizes = a3vec;}
	
	G4double GetSizeX() {return fSizes.x();}
	void SetSizeX(G4double xsize) {G4ThreeVector a3vec = G4ThreeVector(xsize,fSizes.y(),fSizes.z()); fSizes = a3vec;}
	
	G4double GetSizeY() {return fSizes.y();}
	void SetSizeY(G4double ysize) {G4ThreeVector a3vec = G4ThreeVector(fSizes.x(),ysize,fSizes.z()); fSizes = a3vec;}
	
	G4double GetSizeZ() {return fSizes.z();}
	void SetSizeZ(G4double zsize) {G4ThreeVector a3vec = G4ThreeVector(fSizes.x(),fSizes.y(),zsize); fSizes = a3vec;}
	
	G4ThreeVector GetBR() {return fBR;}
	void SetBR(G4ThreeVector a3vec) {fBR = a3vec;}
	
	G4ThreeVector GetAngles() {return fAngles;}
	void SetAngles(G4ThreeVector a3vec) {fAngles = a3vec;}
    
    void SetZ(G4double z1) {fZ = z1;}
    void SetThetaBending(G4double _thetaBending) {thetaBending = _thetaBending;}

	
	G4double GetSiDetThickness() {return fSiDetThickness;}
	void SetSiDetThickness(G4double thick) {fSiDetThickness = thick;}
	
	G4ThreeVector GetSiDetSizes() {return fSiDetSizes;}
	void SetSiDetSizes(G4ThreeVector a3vec) {fSiDetSizes = a3vec;}
	
	void SetSizes2(G4ThreeVector a3vec) {fSizes2 = a3vec;}
	void SetBR2(G4ThreeVector a3vec) {fBR2 = a3vec;}
	void SetAngles2(G4ThreeVector a3vec) {fAngles2 = a3vec;}
    void SetZ2(G4double z2) {fZ2 = z2;}
    void SetX2Offset(G4double x2Offset) {fX2Offset = x2Offset;}

	void SetSizes3(G4ThreeVector a3vec) {fSizes3 = a3vec;}
	void SetBR3(G4ThreeVector a3vec) {fBR3 = a3vec;}
	void SetAngles3(G4ThreeVector a3vec) {fAngles3 = a3vec;}
    void SetZ3(G4double z3) {fZ3 = z3;}

	G4double GetThetaBending(void) const {return thetaBending;};
	
private:
	G4String fECfileName;
	G4String fECOfileName;
	G4String fMaterialName;
	G4ThreeVector fSizes;
	G4ThreeVector fBR;
	G4ThreeVector fAngles;
    G4double  fZ;
	G4double  fSiDetThickness;
	G4ThreeVector fSiDetSizes;
	std::map<G4String,G4double>  fParameterMap;
	
	G4ThreeVector fSizes2;
	G4ThreeVector fBR2;
	G4ThreeVector fAngles2;
    G4double  fZ2;
    G4double  fX2Offset;

	G4ThreeVector fSizes3;
	G4ThreeVector fBR3;
	G4ThreeVector fAngles3;
	G4double thetaBending;
    G4double  fZ3;
};
