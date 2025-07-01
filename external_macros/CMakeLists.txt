cmake_minimum_required(VERSION 3.10)
project(run_geant4_external)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(G4_Simu_Pack_Path "/Users/Yi/Documents/vscode/PRad/EvtGen_Dev/external_calling/simple_geant4_package")
set(G4_Simu_Include_Path "${G4_Simu_Pack_Path}/include")
set(G4_Simu_Lib_Path "${G4_Simu_Pack_Path}/build")

# Find Geant4
find_package(Geant4 REQUIRED)

# Find ROOT
find_package(ROOT REQUIRED)

# Include Geant4 and ROOT headers
include(${Geant4_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})       # For local headers (if any)
include_directories(${G4_Simu_Include_Path})     # Replace with actual path to A/include

# Macro source
add_executable(run_geant4 run_geant4.cc)

# Link the Geant4 simulation library from your package
# You may need to link multiple libs if A/lib contains more than one relevant .so/.dylib
target_link_directories(run_geant4 PRIVATE ${G4_Simu_Lib_Path})

# If your simulation library is named libSimulationLib.dylib (or .so), link it:
target_link_libraries(run_geant4
    Simple_geant4       # omit "lib" and ".so"/".dylib"
    ${Geant4_LIBRARIES}
    ${ROOT_LIBRARIES}
)

# Optionally, show library paths
# message(STATUS "Linking against A/lib and libdoSimuLib")