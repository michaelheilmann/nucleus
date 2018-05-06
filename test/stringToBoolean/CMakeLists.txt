# Copyright (c) Michael Heilmann 2017, 2018

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus.Test.stringToBoolean C)
message("building Nucleus.Test.stringToBoolean")

if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/detect_compiler_and_platform.cmake)
  include(${NUCLEUS_PATH}/buildsystem/set_default_project_properties.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/buildsystem/detect_compiler_and_platform.cmake)
  include(${CMAKE_SOURCE_DIR}/buildsystem/set_default_project_properties.cmake)
endif()

# Find and configure source files.
file(GLOB_RECURSE  SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
# Find and configure header files.
file(GLOB_RECURSE  HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Add and configure executable.
add_executable(Nucleus.Test.stringToBoolean ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Nucleus.Test.stringToBoolean Nucleus.Library)
# Set its properties.
set_project_default_properties(Nucleus.Test.stringToBoolean)

# Test.
add_test(NAME Nucleus.Test.stringToBoolean COMMAND $<TARGET_FILE:Nucleus.Test.stringToBoolean>
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
