# Copyright (c) Michael Heilmann 2017, 2018

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus.Library C)
message("building Nucleus.Library")

if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/detect_compiler_and_platform.cmake)
  include(${NUCLEUS_PATH}/buildsystem/set_default_project_properties.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/buildsystem/detect_compiler_and_platform.cmake)
  include(${CMAKE_SOURCE_DIR}/buildsystem/set_default_project_properties.cmake)
endif()

# Find and configure source files.
file(GLOB_RECURSE SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
# Find and configure header files.
file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Find and configure inlay files.
file(GLOB_RECURSE INLAY_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.i")
set_source_files_properties(${INLAY_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Define and configure the library.
add_library(Nucleus.Library STATIC ${SOURCE_FILES} ${HEADER_FILES} ${INLAY_FILES})
target_include_directories(Nucleus.Library PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Nucleus.Library INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
# Set its properties.
set_project_default_properties(Nucleus.Library)

# GCC: Link library with the platform's math libraries.
if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
  target_link_libraries(Nucleus.Library m)
endif()

# Link library with the platform's threading libraries.
find_package (Threads)
target_link_libraries (Nucleus.Library ${CMAKE_THREAD_LIBS_INIT})

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(Nucleus.Library.Documentation ${DOXYGEN_EXECUTABLE} COMMENT "Building documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
