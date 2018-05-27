# Copyright (c) 2017, 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

if (NOT NUCLEUS_PATH)
  set(NUCLEUS_PATH ${CMAKE_CURRENT_SOURCE_DIR})
endif()
if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/buildsystem.cmake)
endif()

# Define module.
define_module(Nucleus)
detect_operating_system(Nucleus)

# Link library with the platform's threading libraries.
# We allow for overriding the platform's threading libraries with pthreads for some platforms:
# If
# - the operating system is without built-in pthreads support and
# - the use of pthreads is requested,
# use the packaged implementation.
if (NOT DEFINED Nucleus-With-Pthreads)
  set(Nucleus-With-Pthreads OFF)
endif()
if (((${Nucleus_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS}) OR
     (${Nucleus_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_MINGW})) AND
     ${Nucleus-With-Pthreads})
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/pthreads-win32)
  set(CMAKE_THREAD_LIBS_INIT pthreadsVC2)
  set(CMAKE_USE_PTHREADS_INIT TRUE)
else()
  find_package (Threads)
endif()

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "demo".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")

# Add module "test".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
