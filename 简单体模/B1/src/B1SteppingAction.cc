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
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume1(0),
  fScoringVolume2(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  //G4ThreeVector fMom=step->GetMomentumDirection();
  //fEventAction->emitvector(fMom.getX(),fMom.getY(),fMom.getZ());

  if (!fScoringVolume1) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();   
  }

  if (!fScoringVolume2) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume == fScoringVolume1)
  {
    //collect energy deposited in this step (fScoringVolume1)
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep1(edepStep);
    auto pos = step->GetPostStepPoint()->GetPosition();
    auto posx=(pos.getX());
    auto posy=(pos.getY());
    auto posz=(pos.getZ());
    fEventAction->Addweight1(posx*edepStep,posy*edepStep,posz*edepStep);
  }
  
  if (volume == fScoringVolume2)
  {
    //collect energy deposited in this step (fScoringVolume1)
    G4double edepStep = step->GetTotalEnergyDeposit();
    //G4cout<< "edepStep:" <<edepStep<<G4endl;
    fEventAction->AddEdep2(edepStep);
    auto pos = step->GetPostStepPoint()->GetPosition();
    auto posx=(pos.getX());
    auto posy=(pos.getY());
    auto posz=(pos.getZ());
    fEventAction->Addweight2(posx*edepStep,posy*edepStep,posz*edepStep);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

