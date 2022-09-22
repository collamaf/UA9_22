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

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
#include "G4PhysicsFreeVector.hh"

class RunAction;


class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction* , const std::map<G4String,G4double> &);
	virtual ~EventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	std::map<G4String,G4double> GetParameterMap() { return fParameterMap; };
	virtual void AddHitX(void) {numHitX++;};
	virtual G4int  GetHitX(void) {return numHitX;};
	virtual void SetEntranceAngleInX(G4double angle) {entranceAngleInX=angle;};
	virtual G4double GetEntranceAngleInX(void) {return entranceAngleInX;};

private:
	G4int fSDHT_ID;
	RunAction* fRunAction;
	std::map<G4String,G4double>  fParameterMap;
	G4int numHitX;
	G4double entranceAngleInX;
};

#endif
