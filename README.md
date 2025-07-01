# About
A Geant4 simulation package that simulates the detector (a time-of-flight detector) responses of electron beam on liquid hydrogen target.

## Breif introduction of the code structure
All the initializations are done in the `doSimu.cc`

- `DetConstruction.cc/hh`
Reconstruction of detectors

- `PrimaryGenerator.cc/hh`
Set particles, for example Beam particles (Energy, momentum etc.)
Updates of particles for next event can be only performed here

- `EventAction.cc/hh`
Hits information can be processed/stored here 

- `TOFSD.cc/hh`
This is the main codes that process the response of the detector (a time-of-flight detector).
We can get all the hit information here and calculate the probability of accepting this event. This can be performed in the function `void TOFSD::EndOfEvent(G4HCofThisEvent *HCE)`. 
It can also be done in the `void EventAction::EndOfEventAction(const G4Event *event)` from `EventAction.cc/hh`

If McMule need to control the event loop, we need to find a way to pass information at `EndOfEvent` functions and go back to `PrimaryGenerator.cc/hh` after we generated the next event.

## Compilation
[ROOT](https://root.cern.ch) and [Geant4](https://geant4.web.cern.ch) should be installed firstly.
One simple way to install them is to use [anaconda](https://www.anaconda.com/installation-success?source=installer)
After installation of anaconda, ROOT and Geant4 can be installed with the following commands
```bash
conda config --set channel_priority strict
conda create -c conda-forge --name <my-environment> root geant4 cmake
conda activate <my-environment>
```
### Compilation of the Geant4 simulation package
1. change to the directory where `src` and `include` located.
2. `mkdir -p build`
3. `cd build`
4. `cmake ..`
5. `make`

You will get a executable file `doSimu` and a shared library in the current directory.

## Running the codes
1. `cd build`
2. `./doSimu number_of_events runnumber`. 

    The `doSimu` accepts two arguements, the first is the number of events and the second is the runnumber that you can set freely.
    
    You will get a root file `runnumber.BOT.root` in the current directory, in which a tree is stored and also a histogram storing number of generated enents

## Running the codes with external macro
Please modify the following lines in the CMakeLists.txt:
```cmake
set(G4_Simu_Pack_Path "/Users/Yi/Documents/vscode/PRad/EvtGen_Dev/external_calling/simple_geant4_package")
set(G4_Simu_Lib_Path "${G4_Simu_Pack_Path}/build")
```
1. `cd external_macros`
2. `mkdir -p <folder>`
3. `cd <folder>`
4. `cmake ..` and `make`
5. `./run_geant4 number_of_events output_root_file_name`



## Read tree
Some root macros of reading simulation trees can be found in `readTree`.
### How to run
1. `compile processVirtual.cc`
2. `./processVritual input_root_file output_root_file`

To draw plots, please modify the `draw.zsh`. There are some variables defined in this script.
```bash
# POW and MULT are used to calculate the number of generated events 
# nevent = MULT * pow(10, POW)
export POW="10" 
export MULT="1"
## directory where plots are stored
export OUTDIR="./output/0915-0916.Virtual" 
## input root files obtained with `processVirtual`
export INPUT="./input/0915-0916.Virtual.root" 
```

