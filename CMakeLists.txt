cmake_minimum_required (VERSION 2.6)
project (lx-demo)

message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

# Get the sources in "src" relative to "src".
file(GLOB Sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
message(STATUS "Sources: " ${Sources})

# Get the sources in "src/os" relative to "src".
file(GLOB SourcesOs "${CMAKE_CURRENT_SOURCE_DIR}/src/os/*.c")
message(STATUS "SourcesOs: " ${SourcesOs})

# Add the includes "src".
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(lx-demo "${Sources}" "${SourcesOs}")
