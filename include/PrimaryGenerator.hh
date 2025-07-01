#ifndef _PRIMARYGENERATOR_HH_
#define _PRIMARYGENERATOR_HH_
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "TLorentzVector.h"
class PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
        PrimaryGenerator();
        ~PrimaryGenerator();
        virtual void GeneratePrimaries(G4Event *);
        void SetPxPyPzE(const double &px, const double &py, const double &pz, const double &e);
        double GetPx() const { return fP4.Px(); };
        double GetPy() const { return fP4.Py(); };
        double GetPz() const { return fP4.Pz(); };
        double GetE() const { return fP4.E(); };

    private:
        G4ParticleGun *fParticleGun;
        TLorentzVector fP4;
};
#endif