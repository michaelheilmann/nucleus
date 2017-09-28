# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required (VERSION 2.6)

# Project.
project (Nucleus.Test)

# Add Google test subdirectory and enable testing.
enable_testing()
include_directories(${googletest_dir}/googletest/include ${googletest_dir}/src)

# == GCC specific settings ====================================================================== #
if (CMAKE_COMPILER_IS_GNUCC)
  message("compiler is GCC")
  # Enable all warnings and extra warnings.
  add_definitions("-Wall -Wextra")
  # Disable some warnings. Deactivated: Nucleus library can have these warnings enabled.
  # add_definitions("-Wno-reorder -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter")
  # Enable optimizations that do not interfere with debug experience.
  add_definitions("-Og")
  # Enable extra debug information.
  add_definitions("-ggdb3")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# == MSVC specific settings ====================================================================== #
if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  message("compiler is MSVC")
  set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO)
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
    endif()
  endforeach()
  set(MSVC_RUNTIME "static")
ENDIF()

# == Executable ================================================================================= #

# Module directory.
set(ModuleDirectory "${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "Nucleus.Demo.ModuleDirectory:\n ${ModuleDirectory}")
# Include directory.
set(IncludeDirectory "${ModuleDirectory}/rc")
#message(STATUS "Nucleus.Demo.IncludeDirectory:\n ${IncludeDirectory}")
# Source directory.
set(SourceDirectory "${ModuleDirectory}/src")
#message(STATUS "Nucleus.Demo.SourceDirectory:\n ${SourceDirectory}")
# Sources.
file(GLOB Sources "${SourceDirectory}/*.cpp")
#message(STATUS "Nucleus.Demo.Sources:\n ${Sources}")
# Executable.
add_executable(nucleus-test "${Sources}")

# == x86 / x64 detection ======================================================================== #

# This way it can be detected wether the target is x86 or x64.
# TODO: Isn't there a more semantic way to do this.
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
    SET( EX_PLATFORM_NAME "x64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
    MESSAGE( "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
    SET( EX_PLATFORM_NAME "x86" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

# "Nucleus.Test" requires "Nucleus.Library"
include_directories("${ModuleDirectory}/../library/src")
target_link_libraries(nucleus-test nucleus-library)
target_link_libraries(nucleus-test gtest gtest_main)
