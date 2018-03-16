# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus.Test C)

include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/detect_compiler_and_platform.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../buildsystem/set_default_project_properties.cmake)

# Module directory.
set(ModuleDirectory "${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "Nucleus.Test.ModuleDirectory:\n ${ModuleDirectory}")
# Include directory.
set(IncludeDirectory "${ModuleDirectory}/src")
#message(STATUS "Nucleus.Test.IncludeDirectory:\n ${IncludeDirectory}")
# Source directory.
set(SourceDirectory "${ModuleDirectory}/src")
#message(STATUS "Nucleus.Test.SourceDirectory:\n ${SourceDirectory}")
# Sources.
file(GLOB Sources "${SourceDirectory}/*.c")
#message(STATUS "Nucleus.Test.Sources:\n ${Sources}")
# Executable.
add_executable(nucleus-test-executable "${Sources}")
target_link_libraries(nucleus-test-executable nucleus-library)

# "Nucleus.Test" requires "Nucleus.Library"
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY := ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
add_test(NAME nucleus-test-1 COMMAND $<TARGET_FILE:nucleus-test-executable>)
