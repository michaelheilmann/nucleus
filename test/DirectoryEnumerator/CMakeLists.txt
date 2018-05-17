# Copyright (c) 2017, 2018 Michael Heilmann

# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project.
project (Nucleus.Test.DirectoryEnumerator C)
message("building Nucleus.Test.DirectoryEnumerator")

# Find and configure source files.
file(GLOB_RECURSE  SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
# Find and configure header files.
file(GLOB_RECURSE  HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# Add and configure executable.
add_executable(Nucleus.Test.DirectoryEnumerator ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Nucleus.Test.DirectoryEnumerator Nucleus.Library)
# Set its properties.
set_project_default_properties(Nucleus.Test.DirectoryEnumerator)

# Test.
add_test(NAME Nucleus.Test.DirectoryEnumerator COMMAND $<TARGET_FILE:Nucleus.Test.DirectoryEnumerator>
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
