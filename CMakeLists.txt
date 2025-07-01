cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(AVFFs-BOT-Simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Geant4
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Find ROOT
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/cmake)
find_package(ROOT REQUIRED)

# Include directories
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

# Shared library from your simulation code
add_library(Simple_geant4 SHARED ${sources})
target_link_libraries(Simple_geant4 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# Optional: keep your standalone executable
add_executable(doSimu doSimu.cc)
target_link_libraries(doSimu Simple_geant4)
# target_link_libraries(doSimu ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# Install rules (optional)
install(TARGETS Simple_geant4 DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/*.hh DESTINATION include)