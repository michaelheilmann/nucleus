# Copyright (c) 2017, 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Default to "static" (as opposed to "shared") variant.
if (DEFINED Nucleus-Shared)
  set(Nucleus.Library-Shared ${Nucleus-Shared})
else()
  set(Nucleus.Library-Shared OFF)
endif()

# Define the library.
if (Nucleus.Library-Shared)
  # Define the shared library.
  define_shared_library(Nucleus Nucleus.Library ${NUCLEUS_LANGUAGE_ID_C})
else()
  # Define the static library.
  define_static_library(Nucleus Nucleus.Library ${NUCLEUS_LANGUAGE_ID_C})
endif()

# Write configuration header file into binary directory.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/buildsystem/Configuration.h.i
               ${CMAKE_CURRENT_BINARY_DIR}/src/Nucleus/Configuration.h.i)
target_include_directories(Nucleus.Library PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src)

# Link library with the platform's threading libraries.
if (CMAKE_USE_PTHREADS_INIT)
    target_compile_options(Nucleus.Library PRIVATE -DNucleus_Threads_Pthreads=1)
    if (MSVC)
      target_compile_options(Nucleus.Library PRIVATE -D_TIMESPEC_DEFINED)
    endif()
endif()
if (CMAKE_USE_WIN32_THREADS_INIT)
    target_compile_options(Nucleus.Library PRIVATE -DNucleus_Threads_Winapi=1)
endif()

# GCC or Clang: Link library with the platform's math libraries (-lm).
if (${Nucleus.Library_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${Nucleus.Library_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_CLANG})
  target_link_libraries(Nucleus.Library PRIVATE m)
endif()

# Link to the selected threading libraries.
target_link_libraries(Nucleus.Library PRIVATE ${CMAKE_THREAD_LIBS_INIT})

# Writ export header file into binary directory.
include(GenerateExportHeader)
generate_export_header(
    Nucleus.Library
    EXPORT_MACRO_NAME Nucleus_Library_Export
    NO_EXPORT_MACRO_NAME Nucleus_Library_NoExport
    DEPRECATED_MACRO_NAME Nucleus_Library_Deprecated  
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/src/Nucleus/Exports.h)
target_include_directories(Nucleus.Library PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src)
if (NOT Nucleus.Library-Shared)
  set_target_properties(Nucleus.Library PROPERTIES
                        COMPILE_FLAGS -DNUCLEUS_LIBRARY_STATIC_DEFINE)
endif()
