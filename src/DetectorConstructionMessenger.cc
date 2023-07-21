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

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4RunManager.hh"

#include "G4ios.hh"

DetectorConstructionMessenger::
DetectorConstructionMessenger(
															DetectorConstruction* mpga)
:fTarget(mpga){
	fMyXtalDirectory = new G4UIdirectory("/xtal/");
	fMyXtalDirectory->SetGuidance("Crystal setup control commands.");
	
	fXtalMaterialCmd = new G4UIcmdWithAString("/xtal/setMaterial",
																						this);
	fXtalMaterialCmd->SetGuidance("Set crystal material.");
	fXtalMaterialCmd->SetParameterName("xMat",true);
	fXtalMaterialCmd->SetDefaultValue("G4_Si");
	
	fXtalSizeCmd = new G4UIcmdWith3VectorAndUnit("/xtal/setSize",this);
	fXtalSizeCmd->SetGuidance("Set crystal size.");
	fXtalSizeCmd->SetParameterName("xtalSizeX",
																 "xtalSizeY",
																 "xtalSizeZ",
																 true);
	fXtalSizeCmd->SetDefaultValue(G4ThreeVector(6.,2.,6.));
	fXtalSizeCmd->SetDefaultUnit("mm");
	
	fXtalBRCmd = new G4UIcmdWith3VectorAndUnit("/xtal/setBR",this);
	fXtalBRCmd->SetGuidance("Set crystal bending radius.");
	fXtalBRCmd->SetParameterName("xtalBRX",
															 "xtalBRY",
															 "xtalBRZ",
															 true);
	fXtalBRCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtalBRCmd->SetDefaultUnit("m");
	
	fXtalAngleCmd = new G4UIcmdWith3VectorAndUnit("/xtal/setAngle",this);
	fXtalAngleCmd->SetGuidance("Set crystal angles.");
	fXtalAngleCmd->SetParameterName("xtalAngleX",
																	"xtalAngleY",
																	"xtalAngleZ",
																	true);
	fXtalAngleCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtalAngleCmd->SetDefaultUnit("rad");
	
	fXtalECCmd = new G4UIcmdWithAString("/xtal/setEC",
																			this);
	fXtalECCmd->SetGuidance("Set crystal EC.");
	fXtalECCmd->SetParameterName("xEC",true);
	fXtalECCmd->SetDefaultValue("data/Si220pl");
    
    
    fXtalZ = new G4UIcmdWithADoubleAndUnit("/xtal/setZ",this);
    fXtalZ->SetGuidance("Set crystal Z.");
    fXtalZ->SetParameterName("X1Z",true);
    fXtalZ->SetDefaultValue(-8);
    fXtalZ->SetDefaultUnit("m");
    
    
    fXtalThetaBending = new G4UIcmdWithADoubleAndUnit("/xtal/setThetaBending",this);
    fXtalThetaBending->SetGuidance("Set crystal Theta Bending.");
    fXtalThetaBending->SetParameterName("XThetaB",true);
    fXtalThetaBending->SetDefaultValue(2e-3);
    fXtalThetaBending->SetDefaultUnit("rad");
    
    fXtalThetaBending2 = new G4UIcmdWithADoubleAndUnit("/xtal2/setThetaBending",this);
    fXtalThetaBending2->SetGuidance("Set crystal2 Theta Bending.");
    fXtalThetaBending2->SetParameterName("XThetaB",true);
    fXtalThetaBending2->SetDefaultValue(2e-3);
    fXtalThetaBending2->SetDefaultUnit("rad");
	
	fSiDetThickCmd = new G4UIcmdWithADoubleAndUnit("/sidet/thick",this);
	fSiDetThickCmd->SetGuidance("Set Silicon Detector thickness");
	fSiDetThickCmd->SetParameterName("siDetThick",true);
	fSiDetThickCmd->SetDefaultValue(0.300);
	fSiDetThickCmd->SetDefaultUnit("mm");
	
	fSiDetSizeCmd = new G4UIcmdWith3VectorAndUnit("/sidet/setSize",this);
	fSiDetSizeCmd->SetGuidance("Set Silicon Detector Sizes - x,y,z");
	fSiDetSizeCmd->SetParameterName("sidetSizeX",
																	"sidetSizeY",
																	"sidetSizeX",
																	true);
	fSiDetSizeCmd->SetDefaultValue(G4ThreeVector(38.,38.,0.64));
	fSiDetSizeCmd->SetDefaultUnit("mm");
    
    
    fXtalCutFocalDistance = new G4UIcmdWithADoubleAndUnit("/xtal/setCutFocalDistance",this);
    fXtalCutFocalDistance->SetGuidance("Set crystal cut focal distance.");
    fXtalCutFocalDistance->SetParameterName("CutF",true);
    fXtalCutFocalDistance->SetDefaultValue(5);
    fXtalCutFocalDistance->SetDefaultUnit("m");
	
	fXtal2SizeCmd = new G4UIcmdWith3VectorAndUnit("/xtal2/setSize",this);
	fXtal2SizeCmd->SetGuidance("Set crystal2 size.");
	fXtal2SizeCmd->SetParameterName("xtal2SizeX",
																 "xtal2SizeY",
																 "xtal2SizeZ",
																 true);
	fXtal2SizeCmd->SetDefaultValue(G4ThreeVector(6.,2.,6.));
	fXtal2SizeCmd->SetDefaultUnit("mm");
	
	fXtal2BRCmd = new G4UIcmdWith3VectorAndUnit("/xtal2/setBR",this);
	fXtal2BRCmd->SetGuidance("Set crystal2 bending radius.");
	fXtal2BRCmd->SetParameterName("xtal2BRX",
															 "xtal2BRY",
															 "xtal2BRZ",
															 true);
	fXtal2BRCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtal2BRCmd->SetDefaultUnit("m");
	
	fXtal2AngleCmd = new G4UIcmdWith3VectorAndUnit("/xtal2/setAngle",this);
	fXtal2AngleCmd->SetGuidance("Set crystal2 angles.");
	fXtal2AngleCmd->SetParameterName("xtal2AngleX",
																	"xtal2AngleY",
																	"xtal2AngleZ",
																	true);
	fXtal2AngleCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtal2AngleCmd->SetDefaultUnit("rad");
	
	
    
    fXtal2Z = new G4UIcmdWithADoubleAndUnit("/xtal2/setZ",this);
    fXtal2Z->SetGuidance("Set crystal2 Z.");
    fXtal2Z->SetParameterName("X2Z",true);
    fXtal2Z->SetDefaultValue(0);
    fXtal2Z->SetDefaultUnit("m");
    
    
    fXtal2XOffset = new G4UIcmdWithADoubleAndUnit("/xtal2/setXOffset",this);
    fXtal2XOffset->SetGuidance("Set crystal2 XOffset.");
    fXtal2XOffset->SetParameterName("X2XOffset",true);
    fXtal2XOffset->SetDefaultValue(0);
    fXtal2XOffset->SetDefaultUnit("mm");
    
	fXtal3SizeCmd = new G4UIcmdWith3VectorAndUnit("/xtal3/setSize",this);
	fXtal3SizeCmd->SetGuidance("Set crystal3 size.");
	fXtal3SizeCmd->SetParameterName("xtal3SizeX",
																 "xtal3SizeY",
																 "xtal3SizeZ",
																 true);
	fXtal3SizeCmd->SetDefaultValue(G4ThreeVector(6.,2.,6.));
	fXtal3SizeCmd->SetDefaultUnit("mm");
	
	fXtal3BRCmd = new G4UIcmdWith3VectorAndUnit("/xtal3/setBR",this);
	fXtal3BRCmd->SetGuidance("Set crystal3 bending radius.");
	fXtal3BRCmd->SetParameterName("xtal3BRX",
															 "xtal3BRY",
															 "xtal3BRZ",
															 true);
	fXtal3BRCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtal3BRCmd->SetDefaultUnit("m");
	
	fXtal3AngleCmd = new G4UIcmdWith3VectorAndUnit("/xtal3/setAngle",this);
	fXtal3AngleCmd->SetGuidance("Set crystal3 angles.");
	fXtal3AngleCmd->SetParameterName("xtal3AngleX",
																	"xtal3AngleY",
																	"xtal3AngleZ",
																	true);
	fXtal3AngleCmd->SetDefaultValue(G4ThreeVector(0.,0.,0.));
	fXtal3AngleCmd->SetDefaultUnit("rad");
	
    
    fXtal3Z = new G4UIcmdWithADoubleAndUnit("/xtal3/setZ",this);
    fXtal3Z->SetGuidance("Set crystal3 Z.");
    fXtal3Z->SetParameterName("X3Z",true);
    fXtal3Z->SetDefaultValue(10);
    fXtal3Z->SetDefaultUnit("m");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstructionMessenger::
~DetectorConstructionMessenger(){
	delete fXtalMaterialCmd;
	delete fXtalSizeCmd;
	delete fXtalAngleCmd;
    delete fXtalECCmd;
    delete fXtalZ;
    delete fXtalThetaBending;
    delete fXtalThetaBending2;
	delete fXtalBRCmd;
	delete fSiDetThickCmd;
	delete fSiDetSizeCmd;
	
	delete fXtal2SizeCmd;
	delete fXtal2AngleCmd;
	delete fXtal2BRCmd;
    delete fXtal2Z;

	delete fXtal3SizeCmd;
	delete fXtal3AngleCmd;
	delete fXtal3BRCmd;
    delete fXtal3Z;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstructionMessenger::SetNewValue(
																								G4UIcommand *command,
																								G4String newValue){
	if(command==fXtalMaterialCmd ){
		fTarget->SetMaterial(newValue);
	}
	if(command==fXtalSizeCmd ){
		fTarget->SetSizes(fXtalSizeCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtalBRCmd ){
		fTarget->SetBR(fXtalBRCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtalAngleCmd ){
		fTarget->SetAngles(fXtalAngleCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtalECCmd ){
		fTarget->SetEC(newValue);
	}
    if(command==fXtalZ ){
        fTarget->SetZ(fXtalZ->GetNewDoubleValue(newValue));
    }
    if(command==fXtalThetaBending ){
        fTarget->SetThetaBending(fXtalThetaBending->GetNewDoubleValue(newValue));
    }
    if(command==fXtalThetaBending2 ){
        fTarget->SetThetaBending2(fXtalThetaBending2->GetNewDoubleValue(newValue));
    }
    if(command==fSiDetThickCmd ){
		fTarget->SetSiDetThickness(fSiDetThickCmd->GetNewDoubleValue(newValue));
	}
    if(command==fXtalCutFocalDistance ){
        fTarget->SetCutFocalDistance(fXtalCutFocalDistance->GetNewDoubleValue(newValue));
    }
	if(command==fSiDetSizeCmd ){
		fTarget->SetSiDetSizes(fSiDetSizeCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtal2SizeCmd ){
		fTarget->SetSizes2(fXtal2SizeCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtal2BRCmd ){
		fTarget->SetBR2(fXtal2BRCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtal2AngleCmd ){
		fTarget->SetAngles2(fXtal2AngleCmd->GetNew3VectorValue(newValue));
	}
    if(command==fXtal2Z ){
        fTarget->SetZ2(fXtal2Z->GetNewDoubleValue(newValue));
    }
    if(command==fXtal2XOffset ){
        fTarget->SetX2Offset(fXtal2XOffset->GetNewDoubleValue(newValue));
    }
    if(command==fXtal3SizeCmd ){
		fTarget->SetSizes3(fXtal3SizeCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtal3BRCmd ){
		fTarget->SetBR3(fXtal3BRCmd->GetNew3VectorValue(newValue));
	}
	if(command==fXtal3AngleCmd ){
		fTarget->SetAngles3(fXtal3AngleCmd->GetNew3VectorValue(newValue));
	}
    if(command==fXtal3Z ){
        fTarget->SetZ3(fXtal3Z->GetNewDoubleValue(newValue));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4String DetectorConstructionMessenger::GetCurrentValue(
																												G4UIcommand * command){
	G4String cv;
	
	if( command==fXtalMaterialCmd ){
		cv = fTarget->GetMaterial();
	}
	if( command==fXtalSizeCmd ){
		cv = fXtalSizeCmd->ConvertToString(fTarget->GetSizes(),"mm");
	}
	if( command==fXtalBRCmd ){
		cv = fXtalBRCmd->ConvertToString(fTarget->GetBR(),"m");
	}
	if( command==fXtalAngleCmd ){
		cv = fXtalAngleCmd->ConvertToString(fTarget->GetAngles(),"rad");
	}
	if( command==fXtalECCmd ){
		cv = fTarget->GetEC();
	}
	if ( command==fSiDetThickCmd ){
		cv = fTarget->GetSiDetThickness();
	}
	if ( command==fSiDetSizeCmd ){
		cv = fSiDetSizeCmd->ConvertToString(fTarget->GetSiDetSizes(),"mm");
	}
	return cv;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
