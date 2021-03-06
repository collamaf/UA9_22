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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(EventAction* eventAction, RunAction* runAction)
: G4UserSteppingAction(),
fEventAction(eventAction),
fRunAction(runAction),
fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
	
	G4VPhysicalVolume* ThisVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
	G4VPhysicalVolume* NextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
	
	if (fEventAction->GetHitX()==0 && NextVol && NextVol->GetName()=="crystal.physic") {
		fEventAction->AddHitX();
//		G4cout<<"ENTRATO IN X1"<<G4endl;
	}
	if (fEventAction->GetHitX()==1 && NextVol && NextVol->GetName()=="crystal2.physic") {
		fEventAction->AddHitX();
//		G4cout<<"ENTRATO IN X2"<<G4endl;
	}
	if (fEventAction->GetHitX()==2 && NextVol && NextVol->GetName()=="crystal3.physic") {
		fEventAction->AddHitX();
//		G4cout<<"ENTRATO IN X3"<<G4endl;
	}
	
	if (NextVol && NextVol->GetName()=="physDummyPlane") {
		//G4cout<<"ENTRO NEL PIANO "<<NextVol->GetCopyNo()<<G4endl;
		fRunAction->GetPlaneX().push_back(step->GetPostStepPoint()->GetPosition().x()/mm);
		fRunAction->GetPlaneY().push_back(step->GetPostStepPoint()->GetPosition().y()/mm);
		fRunAction->GetPlaneZ().push_back(step->GetPostStepPoint()->GetPosition().z()/mm);
		fRunAction->GetPlaneCosX().push_back(step->GetPostStepPoint()->GetMomentumDirection().x());
		fRunAction->GetPlaneCosY().push_back(step->GetPostStepPoint()->GetMomentumDirection().y());
		fRunAction->GetPlaneCosZ().push_back(step->GetPostStepPoint()->GetMomentumDirection().z());
		fRunAction->GetPlaneP().push_back(step->GetPostStepPoint()->GetMomentum().mag()/GeV);
		fRunAction->GetPlaneEne().push_back(step->GetPostStepPoint()->GetKineticEnergy()/GeV);
		fRunAction->GetPlaneTime().push_back(step->GetTrack()->GetGlobalTime()/ns);
		fRunAction->GetPlanePart().push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
		//		fRunAction->GetCrystAng().push_back(((fEventAction->GetParameterMap())["CrystAng"]) * 1.E6 * CLHEP::rad );
		fRunAction->GetPlanePlaneId().push_back(NextVol->GetCopyNo());
	}
	if (ThisVol->GetName()!="ssd.physic" && NextVol && NextVol->GetName()=="ssd.physic") {
		//G4cout<<"ENTRO NEL SiDet "<<NextVol->GetCopyNo()<<G4endl;
		fRunAction->GetSdAngX().push_back(step->GetPostStepPoint()->GetMomentumDirection().x());
		fRunAction->GetSdAngY().push_back(step->GetPostStepPoint()->GetMomentumDirection().y());
		fRunAction->GetSdAngId().push_back(NextVol->GetCopyNo());
	}
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

