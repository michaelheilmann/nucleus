# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required (VERSION 2.6)

# Project.
project (Nucleus.Library C)

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
# Library.
add_library(nucleus-library STATIC "${Sources}")
