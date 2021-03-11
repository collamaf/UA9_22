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

#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"

#include "G4Event.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(const std::map<G4String,G4double> & ParameterMap):G4VUserPrimaryGeneratorAction() , fParameterMap(ParameterMap) {
    fGPS = new G4GeneralParticleSource();
	G4cout<<"PROVA MAPPA PrimGen: "<<fParameterMap["Ene"]<<G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    fGPS->GeneratePrimaryVertex(anEvent);
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	//G4cout<<"Genero primario con E= "<<fGPS->GetParticleEnergy()/GeV<<G4endl;
	analysisManager->FillNtupleDColumn(1, 0, fGPS->GetParticlePosition().x()/mm);
	analysisManager->FillNtupleDColumn(1, 1, fGPS->GetParticlePosition().y()/mm);
	analysisManager->FillNtupleDColumn(1, 2, fGPS->GetParticlePosition().z()/mm);
	analysisManager->FillNtupleDColumn(1, 3, fGPS->GetParticleMomentumDirection().x());
	analysisManager->FillNtupleDColumn(1, 4, fGPS->GetParticleMomentumDirection().y());
	analysisManager->FillNtupleDColumn(1, 5, fGPS->GetParticleMomentumDirection().z());
	analysisManager->FillNtupleDColumn(1, 6, fGPS->GetParticleEnergy()/GeV);
	analysisManager->FillNtupleDColumn(1, 7, fGPS->GetParticleEnergy()/GeV);
	analysisManager->FillNtupleDColumn(1, 8, fGPS->GetParticleDefinition()->GetPDGEncoding());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
