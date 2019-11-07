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

#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(const std::map<G4String,G4double> & ParameterMap): G4UserRunAction(), fParameterMap(ParameterMap){
	G4RunManager::GetRunManager()->SetPrintProgress(1);
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;
	
	//** Create directories **//
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstHistoId(1);
	
	//** Creating ntuple **//
	analysisManager->CreateNtuple("ExExChTree", "Angles and Positions");
	analysisManager->CreateNtupleDColumn("angXin");
	analysisManager->CreateNtupleDColumn("angYin");
	analysisManager->CreateNtupleDColumn("posXin");
	analysisManager->CreateNtupleDColumn("posYin");
	analysisManager->CreateNtupleDColumn("angXout");
	analysisManager->CreateNtupleDColumn("angYout");
	analysisManager->FinishNtuple();
	
	analysisManager->CreateNtuple("Beam", "Primary Beam");
	analysisManager->CreateNtupleDColumn(1,"X");
	analysisManager->CreateNtupleDColumn(1,"Y");
	analysisManager->CreateNtupleDColumn(1,"Z");
	analysisManager->CreateNtupleDColumn(1,"PX");
	analysisManager->CreateNtupleDColumn(1,"PY");
	analysisManager->CreateNtupleDColumn(1,"PZ");
	analysisManager->CreateNtupleDColumn(1,"Ene");
	analysisManager->CreateNtupleDColumn(1,"Part");
	analysisManager->FinishNtuple();

	analysisManager->CreateNtuple("Planes", "Dummy planes scoring");
	analysisManager->CreateNtupleDColumn(2, "X", fPlaneX);
	analysisManager->CreateNtupleDColumn(2, "Y", fPlaneY);
	analysisManager->CreateNtupleDColumn(2, "Z", fPlaneZ);
	analysisManager->CreateNtupleDColumn(2, "PX", fPlanePX);
	analysisManager->CreateNtupleDColumn(2, "PY", fPlanePY);
	analysisManager->CreateNtupleDColumn(2, "PZ", fPlanePZ);
	analysisManager->CreateNtupleDColumn(2, "Ene", fPlaneEne);
	analysisManager->CreateNtupleDColumn(2, "Part", fPlanePart);
	analysisManager->CreateNtupleDColumn(2, "PlaneId", fPlanePlaneId);
	analysisManager->FinishNtuple();

	G4cout<<"PROVA MAPPA RunAct: "<<fParameterMap["Ene"]<<G4endl;

	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction(){
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*){
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4String fileName = "ExExCh";
	analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
