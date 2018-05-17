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
define_module("Nucleus")

# Link library with the platform's threading libraries.
if (MSVC OR MINGW)
  # If under Windows and pthreads is required, then the path to pthreads directory must be specified.
  if (${PROJECT_NAME}-With-Pthreads)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/pthreads-win32)
    set(CMAKE_THREAD_LIBS_INIT pthreadsVC2)
    set(CMAKE_USE_PTHREADS_INIT TRUE)
  endif()
else()
  find_package (Threads)
endif()

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "demo".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")

# Add module "test".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
