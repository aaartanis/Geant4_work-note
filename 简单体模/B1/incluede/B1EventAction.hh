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
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class B1RunAction;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep1(G4double edep) { fEdep1 += edep; }
    void AddEdep2(G4double edep) { fEdep2 += edep; }
    void AddLength(G4double length) {fLength +=length;}
    void Addweight1(G4double posx,G4double posy,G4double posz) 
    {
      hx +=posx;
      hy +=posy;
      hz +=posz;
    }
    void Addweight2(G4double posx,G4double posy,G4double posz) 
    {
      bx +=posx;
      by +=posy;
      bz +=posz;
    }
    void emitvector(G4double v_x,G4double v_y,G4double v_z)
    {
      px=v_x;
      py=v_y;
      pz=v_z;
    }
    
  private:
    B1RunAction* fRunAction;
    G4double     fEdep1;
    G4double     fEdep2;
    G4double fLength;
    G4double px,py,pz,hx,hy,hz,bx,by,bz;
    

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
