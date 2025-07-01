#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "DetConstruction.hh"
#include "PrimaryGenerator.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4GeometryManager.hh"
#include "ActionInit.hh"
#include "EventAction.hh"

#include "G4SDManager.hh"
#include "TOFSD.hh"
#include "StandardHit.hh"
#include "RootTree.hh"
#include "GlobalVars.hh"

#include "TRandom3.h"

#include <iostream>
#include <random>
using namespace std;

int main(int argc, char **argv)
{
    int nEvent = atoi(argv[1]);
    if (nEvent < 0)
    {
        nEvent = 1000;
    }
    char *ofilename = argv[2];
    if (argc < 3)
    {
        ofilename = "test.BOT.root";
    }
    gRootTree = new RootTree(ofilename);
    G4Random::setTheEngine(new CLHEP::Ranlux64Engine);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long randseed = ts.tv_sec * 1000000000L + ts.tv_nsec;
    std::cout << "Using random seed " << randseed << std::endl;
    // randseed = 19302;
    G4Random::setTheSeed(randseed);
    // == == == == Initialization of Geant4 == == == == //
    //                                                  //
    auto runManager = new G4RunManager();
    runManager->SetUserInitialization(new DetConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new ActionInit());
    runManager->Initialize();
    if (nEvent < 1000)
    {
        runManager->SetPrintProgress(0);
    }

    // Get the SDManager and Sensitive detectors
    // variables required by McMule can be obtained with MySD
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    auto MySD = (TOFSD *)sdManager->FindSensitiveDetector("TOF");

    // == == == == Initialization of McMule == == == == //
    //                                                  //
    // call possible functions here

    auto primaryGen = (PrimaryGenerator *)runManager->GetUserPrimaryGeneratorAction();
    primaryGen->SetPxPyPzE(0, 0, 1000, 1000);
    // runManager->BeamOn(100000);
    // Loop over events manually
    for (int i = 0; i < nEvent; ++i)
    {
        long seed = static_cast<long>(std::time(nullptr)) + i * 783782;
        CLHEP::HepRandom::setTheSeed(seed);
        // G4cout << "seed: " << seed << G4endl;
        runManager->BeamOn(1);

        // == == == ==  We can retrieve detector info here == == == == //
        //                                                             //
        // get the total energy depositions on TOF
        G4cout << "Total Energy depositions on TOF: " << MySD->GetTotalEdep() << G4endl;

        // Note: the following 3 functions haven't been implemented
        // double theta = MySD->GetTheta();
        // double Q2 = MySD->GetQ2();
        // double prob = MySD->GetEventAcceptProbability();

        // == == == == Call McMule here == == == == //
        //                                          //
        // McMule exposes some functions here
        // McMule_Gen(theta, Q2, prob); // a possible function

        // Setup the next event.
        // McMule exposes 4-momentum variables of particles
        // Not limited to 1 particle. Here is just an example
        primaryGen->SetPxPyPzE(0, 0, 1000, 1000);
    }
    // Finalization

    // == == == == return cross section == == == == //
    // get cross section from McMule
    // getXS();

    delete runManager;
    delete gRootTree;
    return 0;
}