#include "PrimaryGenerator.hh"
#include "Constants.hh"
#include "G4Event.hh"
PrimaryGenerator::PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); // 1 primary vertex created

    // G4cout << "End of Particle Gen." << G4endl;
}
PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}
void PrimaryGenerator::GeneratePrimaries(G4Event *myEvt)
{
    G4ParticleTable *partTable = G4ParticleTable::GetParticleTable();
    // G4cout << partTable->size() << G4endl;
    /*for (int i = 0; i < partTable->size(); ++i)
    {
        G4cout << partTable->GetParticleName(i) << "\t" << partTable->GetParticle(i)->GetPDGEncoding() << G4endl;
    }*/
    // G4String partName = "proton";
    // G4String partName = "neutron";
    G4String partName = "e-";
    G4ParticleDefinition *part = partTable->FindParticle(partName);
    
    G4double mass = part->GetPDGMass();
    // G4cout << "mass: " << mass << G4endl;
    G4ThreeVector pos(MyParticleGun::kPosX, MyParticleGun::kPosY, MyParticleGun::kPosZ);
    G4ThreeVector p3(fP4.Px(), fP4.Py(), fP4.Pz());


    // G4ThreeVector pos(0, 0.5 * m, 0.3 * m);
    G4ThreeVector direction(MyParticleGun::kDirectionX, MyParticleGun::kDirectionY, MyParticleGun::kDirectionZ);
    
    G4double KineticE = sqrt(p3.mag2() + mass * mass) - mass / MeV;
    // G4cout << "KineticE: " << KineticE << G4endl;
    // KineticE = 80 * MeV;
    // KineticE = 1.6 * GeV;    
    fParticleGun->SetParticleDefinition(part);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(direction);
    fParticleGun->SetParticleEnergy(KineticE);
    fParticleGun->GeneratePrimaryVertex(myEvt); 
    // if (myEvt->GetEventID() % 1000 == 0)
    // {
    //     G4cout << "KineticE: " << KineticE << G4endl;
    // }
}
void PrimaryGenerator::SetPxPyPzE(const double &px, const double &py, const double &pz, const double &e)
{
    fP4.SetPxPyPzE(px, py, pz, e);
}
