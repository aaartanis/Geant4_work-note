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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume1(0),
  fScoringVolume2(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
    
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 4*m;
  G4double world_sizeZ  = 4*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //     
  // Shape 1 head 
  //  
  G4double head_d=18*cm;

  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 43.*cm);     
 
  G4Orb* solidShape1=new G4Orb("Shape1", 0.5*head_d);         
                 
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
  G4VPhysicalVolume* physShape1 =             
    new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //
  // Shape 5 neck
  //
  G4double neck_innerR=0.*cm;
  G4double neck_outerR=5.*cm;
  G4double neck_high=9.*cm;
  G4double neck_startAngle=0.*deg;
  G4double neck_spanningAngle=360.*deg;

  G4Material *shape5_mat =nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos5=G4ThreeVector(0,0,29.5*cm);

  G4Tubs* solidShape5=new G4Tubs("Shape5",
                                  neck_innerR,
                                  neck_outerR,
                                  0.5*neck_high,
                                  neck_startAngle,
                                  neck_spanningAngle);

      
  G4LogicalVolume* logicShape5 =                         
    new G4LogicalVolume(solidShape5,shape5_mat,"Shape5");             
                        
                     
  G4VPhysicalVolume* physShape5 =              
    new G4PVPlacement(0,                       //no rotation
                    pos5,                    //at (0,0,0)
                    logicShape5,                //its logical volume
                    "Shape5",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking   

  //     
  // Shape 2 body
  //
  G4double body_X=26*cm;
  G4double body_Y=12*cm;
  G4double body_Z=50*cm;
  G4Material *shape2_mat =nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos2=G4ThreeVector(0,0,0);

  G4Box* solidShape2 =    
    new G4Box("Shape2",                    //its name
        0.5*body_X, 0.5*body_Y, 0.5*body_Z);              //its size
      
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,            //its solid
                        shape2_mat,             //its material
                        "Shape2");         //its name
  G4VPhysicalVolume* physShape2 =              
    new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at (0,0,0)
                    logicShape2,                //its logical volume
                    "Shape2",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking   

  //     
  // Shape 3 legs1
  //
  G4double leg_innerR=0.*cm;
  G4double leg_outerR=5.5*cm;
  G4double leg_high=41.*cm;
  G4double leg_startAngle=0.*deg;
  G4double leg_spanningAngle=360.*deg;

  G4Material *shape3_mat =nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos3=G4ThreeVector(7.5*cm,0,-66.*cm);

  G4Tubs* solidShape3=new G4Tubs("Shape3",
                                  leg_innerR,
                                  leg_outerR,
                                  leg_high,
                                  leg_startAngle,
                                  leg_spanningAngle);

      
  G4LogicalVolume* logicShape3 =                         
    new G4LogicalVolume(solidShape3,shape3_mat,"Shape3");             
                        
                     
  G4VPhysicalVolume* physShape3 =              
    new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at (0,0,0)
                    logicShape3,                //its logical volume
                    "Shape3",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking   

  //     
  // Shape 4 legs2
  //
  G4Material *shape4_mat =nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos4=G4ThreeVector(-7.5*cm,0,-66.*cm);

  G4Tubs* solidShape4=new G4Tubs("Shape4",
                                  leg_innerR,
                                  leg_outerR,
                                  leg_high,
                                  leg_startAngle,
                                  leg_spanningAngle);

      
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,shape4_mat,"Shape4");             
                        
                     
  G4VPhysicalVolume* physShape4 =              
    new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at (0,0,0)
                    logicShape4,                //its logical volume
                    "Shape4",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking      
  // Set Shape1(head+neck) and Shape2(body) as scoring volume
  //
  fScoringVolume1 = logicShape1;
  fScoringVolume2 = logicShape2;
/*
  //Set head(+neck) and body as SensitiveDetector
  //
  G4VSensitiveDetector* mySensitive=new MySensitiveDetector(SDname="/MyDetector");
  G4SDManager* sdMan=G4SDManager::GetSDMpointer();
  sdMan->AddNewDetector(mySensitive);
  SetSensitiveDetector("logicShape1",mySensitive);
*/
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
