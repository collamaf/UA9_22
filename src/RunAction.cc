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
using namespace std;
RunAction::RunAction(const std::map<G4String,G4double> & ParameterMap, G4String fileName): G4UserRunAction(), fParameterMap(ParameterMap), OutputFilename(fileName),numKilledTracks(0){
	G4RunManager::GetRunManager()->SetPrintProgress(fParameterMap["NPrim"]/100);
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;
	
	//** Create directories **//
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstHistoId(1);
	
	//** Creating ntuple **//
	analysisManager->CreateNtuple("ExpTree", "Info from Exp. Setup");
	analysisManager->CreateNtupleDColumn("angXin", fAngXin);//0
	analysisManager->CreateNtupleDColumn("angYin", fAngYin);//1
	analysisManager->CreateNtupleDColumn("posXin", fPosXin);//2
	analysisManager->CreateNtupleDColumn("posYin", fPosYin);//3
	analysisManager->CreateNtupleDColumn("angXout", fAngXout);//4
	analysisManager->CreateNtupleDColumn("angYout", fAngYout);//5
	analysisManager->CreateNtupleDColumn("crystAngX", fCrystAng);//6
	analysisManager->CreateNtupleDColumn("sdHitId", fSdHitId);//7
	analysisManager->CreateNtupleDColumn("sdHitX", fSdHitX);//8
	analysisManager->CreateNtupleDColumn("sdHitY", fSdHitY);//9
	analysisManager->CreateNtupleDColumn("sdHitZ", fSdHitZ);//10
	analysisManager->CreateNtupleDColumn("sdAngX", fSdAngX);
	analysisManager->CreateNtupleDColumn("sdAngY", fSdAngY);
	analysisManager->CreateNtupleDColumn("sdAngId", fSdAngId);
	analysisManager->FinishNtuple();
	
	analysisManager->CreateNtuple("Beam", "Primary Beam");
	analysisManager->CreateNtupleDColumn(1,"X");
	analysisManager->CreateNtupleDColumn(1,"Y");
	analysisManager->CreateNtupleDColumn(1,"Z");
	analysisManager->CreateNtupleDColumn(1,"CosX");
	analysisManager->CreateNtupleDColumn(1,"CosY");
	analysisManager->CreateNtupleDColumn(1,"CosZ");
	analysisManager->CreateNtupleDColumn(1,"P");
	analysisManager->CreateNtupleDColumn(1,"Ene");
	analysisManager->CreateNtupleDColumn(1,"Part");
	analysisManager->FinishNtuple();
	
	analysisManager->CreateNtuple("Planes", "Dummy planes scoring");
	analysisManager->CreateNtupleDColumn(2, "X", fPlaneX);
	analysisManager->CreateNtupleDColumn(2, "Y", fPlaneY);
	analysisManager->CreateNtupleDColumn(2, "Z", fPlaneZ);
	analysisManager->CreateNtupleDColumn(2, "CosX", fPlaneCosX);
	analysisManager->CreateNtupleDColumn(2, "CosY", fPlaneCosY);
	analysisManager->CreateNtupleDColumn(2, "CosZ", fPlaneCosZ);
	analysisManager->CreateNtupleDColumn(2, "P", fPlaneP);
	analysisManager->CreateNtupleDColumn(2, "Ene", fPlaneEne);
	analysisManager->CreateNtupleDColumn(2, "Part", fPlanePart);
	analysisManager->CreateNtupleDColumn(2, "Time", fPlaneTime);
	analysisManager->CreateNtupleDColumn(2, "PlaneId", fPlanePlaneId);
	analysisManager->CreateNtupleDColumn(2, "crystAngX", fCrystAng);
	analysisManager->FinishNtuple();
	
	numKilledTracks=0;
	//	G4cout<<"PROVA MAPPA RunAct: "<<fParameterMap["Ene"]<<G4endl;
	
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction(){
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*){
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	//	G4String fileName = "ExExCh";
	
	std::map<G4int,G4String> ParticleName;
	ParticleName[11]="e-";
	ParticleName[-11]="e+";
	ParticleName[-13]="mu+";
	ParticleName[13]="mu-";
	ParticleName[22]="gamma";
	ParticleName[2212]="proton";
	ParticleName[211]="pi+";
	
	if (fParameterMap["Label"]) OutputFilename.append("_" + to_string(int(fParameterMap["Label"])));
	if (fParameterMap["Part"]) OutputFilename.append("_Part" + (ParticleName[(G4int)fParameterMap["Part"]]));
	if (fParameterMap["Ene"]) OutputFilename.append("_Ene" + to_string((G4int)fParameterMap["Ene"]));
	if (fParameterMap["CrystX"]) OutputFilename.append("_CrystX" + to_string((G4int)fParameterMap["CrystX"])+ "Y"+ to_string((G4int)fParameterMap["CrystY"])+ "Z" +to_string((G4int)fParameterMap["CrystZ"]));
	if (fParameterMap["SigmaX"]) OutputFilename.append("_SigmaX" + to_string((G4int)(fParameterMap["SigmaX"]*1.E6))+ "Y"+ to_string((G4int)(fParameterMap["SigmaY"]*1.E6))+ "Z" +to_string((G4int)(fParameterMap["SigmaZ"]*1.E6)));
	//if (fParameterMap["CrystAng"]) OutputFilename.append("_CrystAng" + to_string((G4int)(fParameterMap["CrystAng"]*1.E6)));
	if (fParameterMap["CrystDX"]) OutputFilename.append("_CrystDX" + to_string((G4int)fParameterMap["CrystDX"]));
	if (fParameterMap.find("CrystAng") != fParameterMap.end() ) OutputFilename.append("_CrystAng" + to_string((G4int)(fParameterMap["CrystAng"]*1.E6)));
	if (fParameterMap["BR"]) OutputFilename.append("_BR" + to_string((G4int)(fParameterMap["BR"])));
	if (fParameterMap["Mag"]) OutputFilename.append("_Mag" + to_string((G4int)(fParameterMap["Mag"])));
	if (fParameterMap["NoCryst"]) OutputFilename.append("_NoCryst");
	if (fParameterMap["NoCryst2"]) OutputFilename.append("_NoCryst2");
	if (fParameterMap["Telescope"]) OutputFilename.append("_Tel");
	if (fParameterMap["NoDet"]) OutputFilename.append("_NoDet");
	if (fParameterMap["SecondX"]) OutputFilename.append("_SecondX");

	if (fParameterMap["Det0Z"])	OutputFilename.append("_Det0Z" + to_string((G4int)fParameterMap["Det0Z"]*100));
	if (fParameterMap["Det1Z"]) OutputFilename.append("_Det1Z" + to_string((G4int)fParameterMap["Det1Z"]*100));
	if (fParameterMap["Det2Z"]) OutputFilename.append("_Det2Z" + to_string((G4int)fParameterMap["Det2Z"]*100));
	if (fParameterMap["Det3Z"]) OutputFilename.append("_Det3Z" + to_string((G4int)fParameterMap["Det3Z"]*100));
	
	if (fParameterMap["KeepSec"]) OutputFilename.append("_Sec");
	if (fParameterMap["CutChan"]==-1) OutputFilename.append("_OnlyChPost");
	if (fParameterMap["CutChan"]==1) OutputFilename.append("_OnlyNotChPost");
	if (fParameterMap["CutChan"]==-10) OutputFilename.append("_OnlyChPre");
	if (fParameterMap["CutChan"]==10) OutputFilename.append("_OnlyNotChPre");

	OutputFilename.append("_N" + to_string((G4int)fParameterMap["NPrim"]));
	
	analysisManager->OpenFile(OutputFilename + ".root");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
	G4cout<<G4endl<<G4endl<<
	"hadd -f "<< OutputFilename<<".root ";
	for (int ii=0; ii<G4Threading::G4GetNumberOfCores() - 2; ii++) G4cout<<OutputFilename<<"_t"<<ii<<".root ";
	G4cout<<"; rm ";
	for (int ii=0; ii<G4Threading::G4GetNumberOfCores() - 2; ii++) G4cout<<OutputFilename<<"_t"<<ii<<".root ";
	
	G4cout<<G4endl<<G4endl<<G4endl;
	G4cout<<"NUMBER OF KILLED TRACKS: "<<numKilledTracks<<G4endl;
	
	
#if 0
	// Manually merge root files at the end (and delete temporary root files) since the automatic G4 way fails to merge vectors
	if (G4Threading::G4GetThreadId()==0) {
	G4cout<<"hadd -f "<< OutputFilename<<".root ";
	G4String tempFileList="";
	for (int iThread=0; iThread<G4Threading::G4GetNumberOfCores() - 2; iThread++) {
		tempFileList.append(OutputFilename+ "_t"+to_string(iThread) + ".root ");
	}
	G4String comandoHadd="hadd -f  " + OutputFilename + ".root " + tempFileList;
	G4String comandoRm="rm " + tempFileList;

	system(comandoHadd);
	system(comandoRm);
	}
#endif
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
