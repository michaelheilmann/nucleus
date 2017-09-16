# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required (VERSION 2.6)

# Project.
project (Nucleus.Demo)

# Module directory.
set(ModuleDirectory "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Nucleus.Demo.ModuleDirectory:\n ${ModuleDirectory}")
# Include directory.
set(IncludeDirectory "${ModuleDirectory}/rc")
message(STATUS "Nucleus.Demo.IncludeDirectory:\n ${IncludeDirectory}")
# Source directory.
set(SourceDirectory "${ModuleDirectory}/src")
message(STATUS "Nucleus.Demo.SourceDirectory:\n ${SourceDirectory}")
# Sources.
file(GLOB Sources "${SourceDirectory}/*.c")
message(STATUS "Nucleus.Demo.Sources:\n ${Sources}")
# Executable.
add_executable(nucleus-demo "${Sources}")

# "Nucleus.Demo" requires "Nucleus.Library"
include_directories("${ModuleDirectory}/../library/src")
target_link_libraries(nucleus-demo nucleus-library)
