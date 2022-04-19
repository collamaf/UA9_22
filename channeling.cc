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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4ScoringManager.hh"
#include "G4UImanager.hh"

#ifdef G4MULTITHREADED
#include "UserActionInitialization.hh"
#else
#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#endif

#include "DetectorConstruction.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "FTFP_BERT.hh"

#include "G4EmStandardPhysics_option4_channeling.hh"
#include "G4ChannelingPhysics.hh"
#include "G4GenericBiasingPhysics.hh"
#include "B1SteppingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using namespace std;
int main(int argc,char** argv)
{
	// Detect interactive mode (if no arguments) and define UI session
	//
	G4UIExecutive* ui = 0;
	
	std::map<G4String,G4double> ParameterMap;
	//	ParameterMap["BR"]=0.17;
	//	ParameterMap["Div"]=0.0017;
	//	ParameterMap["Ene"]=17;
	ParameterMap["NPrim"]=100;
	ParameterMap["KeepSec"]=0;
	
	G4bool VisFlag=false;
	G4String MacroName="";
	G4String OutputFilename = "mUA9";
	G4cout<<"Filename: "<<OutputFilename<<G4endl;
	G4int ExpSetup=-1;
	
	for(int i=1;i<argc;i++)
		if(argv[i][0] =='-')
		{
			G4String option(argv[i]);
			G4cout<<"option: "<<i<<" "<<option<<G4endl;
			if(option.compare("-Ene")==0)
			{
				ParameterMap["Ene"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Part")==0)
			{
				ParameterMap["Part"]=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-NPrim")==0)
			{
				ParameterMap["NPrim"]=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-SigmaX")==0)
			{
				ParameterMap["SigmaX"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-SigmaY")==0)
			{
				ParameterMap["SigmaY"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-BR")==0)
			{
				ParameterMap["BR"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-CrystX")==0)
			{
				ParameterMap["CrystX"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-CrystY")==0)
			{
				ParameterMap["CrystY"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-CrystZ")==0)
			{
				ParameterMap["CrystZ"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-CrystAng")==0)
			{
				ParameterMap["CrystAng"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-KeepSec")==0)
			{
				ParameterMap["KeepSec"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-NoDet")==0)
			{
				ParameterMap["NoDet"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-NoCryst")==0)
			{
				ParameterMap["NoCryst"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Mag")==0)
			{
				ParameterMap["Mag"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Plane0Z")==0)
			{
				ParameterMap["Plane0Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Plane1Z")==0)
			{
				ParameterMap["Plane1Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Plane2Z")==0)
			{
				ParameterMap["Plane2Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Plane3Z")==0)
			{
				ParameterMap["Plane3Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Det0Z")==0)
			{
				ParameterMap["Det0Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Det1Z")==0)
			{
				ParameterMap["Det1Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Det2Z")==0)
			{
				ParameterMap["Det2Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Det3Z")==0)
			{
				ParameterMap["Det3Z"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Vis")==0)
			{
				VisFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Setup")==0)
			{
//				ExpSetup=stoi (argv[++i], NULL);;
				ParameterMap["Setup"]=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-SecondX")==0)
			{
				ParameterMap["SecondX"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-NoCh")==0)
			{
				ParameterMap["NoCh"]=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Label")==0)
			{
				OutputFilename.append(argv[++i]);
				G4cout<<"Filename: "<<OutputFilename<<G4endl;
			}
		}
		else
		{
			MacroName = argv[i]; //If I found a macro (without trailing "-") it means that I do NOT want visualization
			VisFlag=false;
		}
	
	if (ParameterMap["Setup"]==1) {
		MacroName="mua922_conf1.mac";
		OutputFilename.append("_Conf1");

	}else if (ParameterMap["Setup"]==3) {
		MacroName="mua922_conf3.mac";
		OutputFilename.append("_Conf3");
	}
	
	
	// Construct the default run manager
#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores() - 2);
#else
	G4RunManager* runManager = new G4RunManager;
#endif
	
	// Activate UI-command base scorer
	G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
	scManager->SetVerboseLevel(0);
	
	// Set mandatory initialization classes
	G4VModularPhysicsList* physlist= new FTFP_BERT();
	G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
	physlist->RegisterPhysics(new G4ChannelingPhysics());
	physlist->ReplacePhysics(new G4EmStandardPhysics_option4_channeling());
	//physlist->ReplacePhysics(new G4EmStandardPhysicsSS_channeling());
	biasingPhysics->PhysicsBiasAllCharged();
	physlist->RegisterPhysics(biasingPhysics);
	runManager->SetUserInitialization(physlist);
	
#ifndef G4MULTITHREADED
	// Set user action classes
	runManager->SetUserAction(new PrimaryGeneratorAction());
	runManager->SetUserAction(new StackingAction());
	//	runManager->SetUserAction(new RunAction());
	RunAction* runAction = new RunAction();
	runManager->SetUserAction(runAction);
	
	EventAction* eventAction = new EventAction(runAction);
	
	runManager->SetUserAction(eventAction);
	runManager->SetUserAction(new B1SteppingAction(eventAction, runAction));
#else
	//	runManager->SetUserInitialization(new UserActionInitialization(ParameterMap));
	UserActionInitialization* actionInit = new UserActionInitialization(ParameterMap,OutputFilename);
	runManager->SetUserInitialization(actionInit);
#endif
	DetectorConstruction* detConst=new DetectorConstruction(ParameterMap);
	runManager->SetUserInitialization(detConst);
	
	
	std::map<G4int,G4String> ParticleName;
	
	ParticleName[11]="e-";
	ParticleName[-11]="e+";
	ParticleName[-13]="mu+";
	ParticleName[13]="mu-";
	ParticleName[22]="gamma";
	ParticleName[2212]="proton";
	ParticleName[211]="pi+";
	
	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	
	if ( VisFlag ) { //Prepare for vis
		ui = new G4UIExecutive(argc, argv);
	}
	
	// Process macro or start UI session
	if (MacroName!="") { //se ho passato una macro
		UImanager->ApplyCommand("/control/execute "+MacroName);
	} else { //se non ho passato una macro carica quella di default
		UImanager->ApplyCommand("/control/execute default.mac");
	}
	// modifico i vari parametri secondo quanto passato da linea di comando
	G4cout<<"CIAONNN "<<"/gps/particle "+(ParticleName[ParameterMap["Part"]]) <<G4endl;
	if (ParameterMap["Part"]) UImanager->ApplyCommand("/gps/particle "+(ParticleName[ParameterMap["Part"]]) );
	if (ParameterMap["Ene"]) UImanager->ApplyCommand("/gps/ene/mono "+std::to_string(ParameterMap["Ene"]) + " GeV");
	if (ParameterMap["SigmaX"]) UImanager->ApplyCommand("/gps/ang/sigma_x "+std::to_string(ParameterMap["SigmaX"]) + " rad");
	if (ParameterMap["SigmaY"]) UImanager->ApplyCommand("/gps/ang/sigma_y "+std::to_string(ParameterMap["SigmaY"]) + " rad");
	if (ParameterMap["CrystX"]) UImanager->ApplyCommand("/xtal/setSize "+std::to_string(ParameterMap["CrystX"]) +" "+ std::to_string(ParameterMap["CrystY"]) + " " +std::to_string(ParameterMap["CrystZ"]) + " rad");
	
	// Ora che ho caricato tutti i parametri necessari, decido se lanciare in batch o in interattivo
	if (!ui) { //se batch mode mando NPrim
		if (ParameterMap["NPrim"]) UImanager->ApplyCommand("/run/beamOn "+std::to_string(G4int(ParameterMap["NPrim"])));
	}
	else { //altrimenti mando interattivo
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted
	// in the main() program !
	//	runAction->PrintRunHadd(G4Threading::G4GetNumberOfCores() - 2);
	
	if (VisFlag) delete visManager;
	delete runManager;
	
	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
