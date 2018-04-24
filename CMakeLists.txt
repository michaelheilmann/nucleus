# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus C)
message("building Nucleus")

include(CTest)
enable_testing()

if (MSVC OR MINGW)
  if (NOT DEFINED With-Static-Runtime)
    set(With-Static-Runtime ON CACHE BOOL
        "enable/disable compilation with static runtime. \
         ON enables compilation with static runtime, OFF disables compilation with static runtime. \
         Initial value is ON. \
         Only available under MSVC and MINGW" FORCE)
  endif()
endif()

if (NOT DEFINED With-Optimizations)
  set(With-Optimizations ON CACHE BOOL
      "enable/disable compilation with optimizations. \
       ON enables compilation with optimizations, OFF disables compilation with optimizations. \
       Initial value is ON." FORCE)
endif()

if (NOT DEFINED With-Debug-Information)
  set(With-Debug-Information OFF CACHE BOOL
      "enable/disable compilation with debug information. \
       ON enables compilation with debug information, OFF disables compilation with debug information. \
       Initial value is OFF." FORCE)
endif()

# Enable/disable compilation and execution of unit tests.
# The value of this option can be set from the command-line by -Didlib-with-tests=(ON|OFF).
option(Nucleus-With-Tests
       "enable/disable compilation and execution of unit tests. \
        ON enables compilation and execution of unit tests, OFF disables compilation and execution of unit tests. \
        Initial value is ON."
       ON)

# The output directories.
# TODO: Change to "products".
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "demo".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")

# Add module "test".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
