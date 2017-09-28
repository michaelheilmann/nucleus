# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required (VERSION 2.6)

# Project.
project (Nucleus.Library C)

# == GCC specific settings ====================================================================== #
if (CMAKE_COMPILER_IS_GNUCC)
  # Enable all warnings and extra warnings.
  add_definitions("-Wall -Wextra")
  # Disable some warnings. Deactivated: Nucleus library can have these warnings enabled.
  # add_definitions("-Wno-reorder -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter")
  # Enable optimizations that do not interfere with debug experience.
  add_definitions("-Og")
  # Enable extra debug information.
  add_definitions("-ggdb3")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# == static library ============================================================================ #

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

# == Doxygen ==================================================================================== #

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(nucleus-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "Building documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)

# @TODO: The MSVC generator adds an install target to the solution if we add that.
#        However, we do not want that install target.
#install(TARGETS nucleus-library ARCHIVE DESTINATION lib/static)

# Configure the source distribution.
#SET(CPACK_SOURCE_GENERATOR "ZIP")
#SET(CPACK_SOURCE_PACKAGE_FILE_NAME "nucleus-library-src")
