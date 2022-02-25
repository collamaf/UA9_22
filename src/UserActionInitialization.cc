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

#include "G4Types.hh"
#include <map>
#ifdef G4MULTITHREADED
#include "UserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "B1SteppingAction.hh"
#include <map>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UserActionInitialization::UserActionInitialization(std::map<G4String,G4double> & ParameterMap, G4String OutputFilename):G4VUserActionInitialization(), fParameterMap(ParameterMap), OutputFilename(OutputFilename)
//UserActionInitialization::UserActionInitialization():G4VUserActionInitialization()
{
	G4cout<<"PROVA MAPPA UserInit: "<<fParameterMap["KeepSec"]<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UserActionInitialization::~UserActionInitialization(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserActionInitialization::Build() const {
	PrimaryGeneratorAction* primGenAction=new PrimaryGeneratorAction(fParameterMap);
	SetUserAction(primGenAction);
	
	StackingAction* stackAct=new StackingAction(fParameterMap);
	SetUserAction(stackAct);
	
	RunAction* runAction = new RunAction(fParameterMap, OutputFilename);
	SetUserAction(runAction);
	
	EventAction* eventAction=new EventAction(runAction, fParameterMap);
	SetUserAction(eventAction);
	
	SetUserAction(new B1SteppingAction(eventAction, runAction));
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#endif
