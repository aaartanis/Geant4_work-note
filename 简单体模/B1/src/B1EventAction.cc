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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "B1Analysis.hh"
#include "G4UnitsTable.hh"
#include "G4PrimaryParticle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep1(0.),
  fEdep2(0.),
  fLength(0.),
  px(0.),py(0.),pz(0.),hx(0.),hy(0.),hz(0.),bx(0.),by(0.),bz(0.)
  
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event* event)
{    
  fEdep1 = 0.;
  fEdep2 = 0.;
  fLength = 0.;
  hx=0.,hy=0.,hz=0.,bx=0.,by=0.,bz=0.;
  px=event->GetPrimaryVertex()->GetPrimary()->GetPx();
  py=event->GetPrimaryVertex()->GetPrimary()->GetPy();
  pz=event->GetPrimaryVertex()->GetPrimary()->GetPz();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event* event)
{  
  G4int eventID= event->GetEventID();
  
  //get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  //G4cout<<"fEdep1:"<< std::setw(7)<<G4BestUnit(fEdep1,"Energy")<<G4endl;
  //G4cout<<"fEdep2:"<< std::setw(7)<<G4BestUnit(fEdep2,"Energy")<<G4endl;

  //fill ntuple
  analysisManager->FillNtupleIColumn(0,eventID);
  analysisManager->FillNtupleDColumn(1,fEdep1);
  analysisManager->FillNtupleDColumn(2,fEdep2);
  analysisManager->FillNtupleDColumn(3,px);
  analysisManager->FillNtupleDColumn(4,py);
  analysisManager->FillNtupleDColumn(5,pz);
  analysisManager->FillNtupleDColumn(6,hx);
  analysisManager->FillNtupleDColumn(7,hy);
  analysisManager->FillNtupleDColumn(8,hz);
  analysisManager->FillNtupleDColumn(9,bx);
  analysisManager->FillNtupleDColumn(10,by);
  analysisManager->FillNtupleDColumn(11,bz);
  analysisManager->AddNtupleRow();

  if((eventID)%10000==0) 
  {
    
    G4cout << "---> End of event: " << eventID << G4endl;     

    G4cout
       << "   head: deposit energy: " << std::setw(7)
                                        << G4BestUnit(fEdep1,"Energy")
       << G4endl
       << "   body: deposit energy: " << std::setw(7)
                                        << G4BestUnit(fEdep2,"Energy")
       << G4endl
       << "   primaryvector px:  " << std::setw(7)
                                        << px//G4BestUnit(px,"Vertex")
       << G4endl
              << "   py:  " << std::setw(7)
                                        << py//G4BestUnit(py,"Vertex")
       << G4endl
              << "   pz:  " << std::setw(7)
                                        << pz//G4BestUnit(pz,"Vertex")
       << G4endl
              << "   h_x: " << std::setw(7)
                                        << hx//G4BestUnit(hx,"position")
       << G4endl
              << "   b_x: " << std::setw(7)
                                        << bx//G4BestUnit(bx,"position")
       << G4endl;
  }


  // accumulate statistics in run action
  //fRunAction->AddEdep(fEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
