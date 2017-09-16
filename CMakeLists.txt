# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required (VERSION 2.6)

project (nucleus)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The directory all modules are residing in.
#set(Nucleus.ModulesDirectory "${CMAKE_CURRENT_SOURCE_DIR}")

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "demo".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")
