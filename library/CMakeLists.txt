# Copyright (c) 2017, 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the static library.
define_static_library(Nucleus Nucleus.Library ${NUCLEUS_LANGUAGE_ID_C})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/buildsystem/Configuration.h.i
               ${CMAKE_CURRENT_SOURCE_DIR}/src/Nucleus/Configuration.h.i)

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
