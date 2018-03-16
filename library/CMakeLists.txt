# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus.Library C)

include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/detect_compiler_and_platform.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/set_default_project_properties.cmake)

# Module directory.
set(ModuleDirectory "${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "Nucleus.Library.ModuleDirectory:\n ${ModuleDirectory}")
# Include directory.
set(IncludeDirectory "${ModuleDirectory}/src")
#message(STATUS "Nucleus.Library.IncludeDirectory:\n ${IncludeDirectory}")
# Source directory.
set(SourceDirectory "${ModuleDirectory}/src")
#message(STATUS "Nucleus.Library.SourceDirectory:\n ${SourceDirectory}")
# Sources.
file(GLOB Sources "${SourceDirectory}/*.c")
#message(STATUS "Nucleus.Library.Sources:\n ${Sources}")
# Define the library.
add_library(nucleus-library STATIC "${Sources}")
target_include_directories(nucleus-library INTERFACE ${SourceDirectory})

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(nucleus-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "Building documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
