# @author Michael Heilmann
# @copyright Copyright (c) Michael Heilmann 2017

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (nucleus-demo C)

if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/detect_compiler_and_platform.cmake)
  include(${NUCLEUS_PATH}/buildsystem/set_default_project_properties.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/buildsystem/detect_compiler_and_platform.cmake)
  include(${CMAKE_SOURCE_DIR}/buildsystem/set_default_project_properties.cmake)
endif()

set_project_default_properties()

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
file(GLOB Sources "${SourceDirectory}/*.c")
#message(STATUS "Nucleus.Demo.Sources:\n ${Sources}")
# Executable.
add_executable(nucleus-demo "${Sources}")

# "Nucleus.Demo" requires "Nucleus.Library"
target_link_libraries(nucleus-demo nucleus-library)
