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

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class G4Run;

class RunAction : public G4UserRunAction
{
public:
	RunAction(const std::map<G4String,G4double> &, G4String );
	virtual ~RunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void   EndOfRunAction(const G4Run*);
	
	std::vector<G4double>& GetPlaneX() {return fPlaneX; }
	std::vector<G4double>& GetPlaneY() {return fPlaneY; }
	std::vector<G4double>& GetPlaneZ() {return fPlaneZ; }
	std::vector<G4double>& GetPlaneCosX() {return fPlaneCosX; }
	std::vector<G4double>& GetPlaneCosY() {return fPlaneCosY; }
	std::vector<G4double>& GetPlaneCosZ() {return fPlaneCosZ; }
	std::vector<G4double>& GetPlaneP() {return fPlaneP; }
	std::vector<G4double>& GetPlaneEne() {return fPlaneEne; }
	std::vector<G4double>& GetPlanePart() {return fPlanePart; }
	std::vector<G4double>& GetPlaneTime() {return fPlaneTime; }
	std::vector<G4double>& GetPlanePlaneId() {return fPlanePlaneId; }
	std::vector<G4double>& GetCrystAng() {return fCrystAng; }
	
	std::vector<G4double>& GetPosXin() {return fPosXin; }
	std::vector<G4double>& GetPosYin() {return fPosYin; }
	std::vector<G4double>& GetPosXout() {return fPosXout; }
	std::vector<G4double>& GetPosYout() {return fPosYout; }
	std::vector<G4double>& GetAngXin() {return fAngXin; }
	std::vector<G4double>& GetAngYin() {return fAngYin; }
	std::vector<G4double>& GetAngXout() {return fAngXout; }
	std::vector<G4double>& GetAngYout() {return fAngYout; }
	std::vector<G4double>& GetSdHitId() {return fSdHitId; }
	std::vector<G4double>& GetSdHitX() {return fSdHitX; }
	std::vector<G4double>& GetSdHitY() {return fSdHitY; }
	std::vector<G4double>& GetSdHitZ() {return fSdHitZ; }
	std::vector<G4double>& GetSdAngX() {return fSdAngX; }
	std::vector<G4double>& GetSdAngY() {return fSdAngY; }
	std::vector<G4double>& GetSdAngId() {return fSdAngId; }
	
	virtual void   AddKilledTrack(void){numKilledTracks++;};

private:
	std::vector<G4double> fPlaneX;
	std::vector<G4double> fPlaneY;
	std::vector<G4double> fPlaneZ;
	std::vector<G4double> fPlaneCosX;
	std::vector<G4double> fPlaneCosY;
	std::vector<G4double> fPlaneCosZ;
	std::vector<G4double> fPlaneP;
	std::vector<G4double> fPlaneEne;
	std::vector<G4double> fPlanePart;
	std::vector<G4double> fPlaneTime;
	std::vector<G4double> fPlanePlaneId;
	std::vector<G4double> fCrystAng;
	
	std::vector<G4double> fPosXin;
	std::vector<G4double> fPosYin;
	std::vector<G4double> fPosXout;
	std::vector<G4double> fPosYout;
	std::vector<G4double> fAngXin;
	std::vector<G4double> fAngYin;
	std::vector<G4double> fAngXout;
	std::vector<G4double> fAngYout;
	std::vector<G4double> fSdHitId;
	std::vector<G4double> fSdHitX;
	std::vector<G4double> fSdHitY;
	std::vector<G4double> fSdHitZ;
	std::vector<G4double> fSdAngX;
	std::vector<G4double> fSdAngY;
	std::vector<G4double> fSdAngId;
	
	std::map<G4String,G4double>  fParameterMap;
	
	G4String OutputFilename;
	G4int numKilledTracks;
	
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
