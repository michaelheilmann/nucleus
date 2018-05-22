# Detect compiler and platform detection.
#
# Provides the following numeric constants for identifying C++ compilers:
# - NUCLEUS_CPP_COMPILER_ID_UNKNOWN
# - NUCLEUS_CPP_COMPILER_ID_CLANG
# - NUCLEUS_CPP_COMPILER_ID_GCC
# - NUCLEUS_CPP_COMPILER_ID_MSVC
# - NUCLEUS_CPP_COMPILER_ID_MINGW
#
# If compiler detection succeeds, define NUCLEUS_CPP_COMPILER_ID to one of the constants listed above except for
# NUCLEUS_CPP_COMPILER_ID_UNKNOWN. If compiler detection fails, define NUCLEUS_CPP_COMPILER_ID to
# NUCLEUS_CPP_COMPILER_ID_UNKNOWN. Defines the macro nucleus_report_cpp_compiler_id to report the value of NUCLEUS_CPP_COMPILER_ID.

# Provides the following numeric constants for identifying C compilers:
# - NUCLEUS_C_COMPILER_ID_UNKNOWN
# - NUCLEUS_C_COMPILER_ID_CLANG
# - NUCLEUS_C_COMPILER_ID_GCC
# - NUCLEUS_C_COMPILER_ID_MSVC
# - NUCLEUS_C_COMPILER_ID_MINGW
#
# If compiler detection succeeds, define NUCLEUS_C_COMPILER_ID to one of the constants listed above except for
# NUCLEUS_C_COMPILER_ID_UNKNOWN. If compiler detection fails, define NUCLEUS_C_COMPILER_ID to
# NUCLEUS_C_COMPILER_ID_UNKNOWN otherwise. Defines the macro nucleus_report_c_compiler_id to report the value of NUCLEUS_C_COMPILER_ID.
#
#
# Provides the following numeric constants:
# - NUCLEUS_PLATFORM_ID_UNKNOWN
# - NUCLEUS_PLATFORM_ID_X64
# - NUCLEUS_PLATFORM_ID_X86
#
# If platform detection succeeds, define NUCLEUS_PLATFORM_ID to NUCLEUS_PLATFORM_ID_X64 or NUCLEUS_PLATFORM_ID_X86.
# Define NUCLEUS_PLATFORM_ID to NUCLEUS_PLATFORM_ID_UNKNOWN otherwise.
# Define macro idlib_report_platform_id to report the value of NUCLEUS_PLATFORM_ID.
#
# If multi target detection succeeds, define NUCLEUS_IS_MULTI_TARGET_GENERATOR to YES.
# Define NUCLEUS_IS_MULTI_TARGET_GENERATOR to NO otherwise.
# Define macro idlib_report_is_multi_target_generator to report the value of NUCLEUS_IS_MULTI_TARGET_GENERATOR.
include(${CMAKE_CURRENT_LIST_FILE}/../languages.cmake)

# Compiler detection (C).

set(NUCLEUS_C_COMPILER_STRING_UNKNOWN "<unknown>")
set(NUCLEUS_C_COMPILER_ID_UNKNOWN 0)

set(NUCLEUS_C_COMPILER_STRING_CLANG "CLANG")
set(NUCLEUS_C_COMPILER_ID_CLANG 1)

set(NUCLEUS_C_COMPILER_STRING_MSVC "MSVC")
set(NUCLEUS_C_COMPILER_ID_MSVC 2)

set(NUCLEUS_C_COMPILER_STRING_GCC "GCC")
set(NUCLEUS_C_COMPILER_ID_GCC 3)

set(NUCLEUS_CPP_COMPILER_STRING_UNKNOWN "<unknown>")
set(NUCLEUS_CPP_COMPILER_ID_UNKNOWN 0)

set(NUCLEUS_CPP_COMPILER_STRING_CLANG "CLANG")
set(NUCLEUS_CPP_COMPILER_ID_CLANG 1)

set(NUCLEUS_CPP_COMPILER_STRING_MSVC "MSVC")
set(NUCLEUS_CPP_COMPILER_ID_MSVC 2)

set(NUCLEUS_CPP_COMPILER_STRING_GCC "GCC")
set(NUCLEUS_CPP_COMPILER_ID_GCC 3)

set(NUCLEUS_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_UNKNOWN})

macro(detect_compiler parent_target_name target_name language)
  if (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
    set(${target_name}_C_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_UNKNOWN})
    set(${target_name}_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_UNKNOWN})
    if (CMAKE_C_COMPILER_ID)
      if (CMAKE_C_COMPILER MATCHES ".*clang")
        set(${target_name}_C_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_CLANG})
        set(${target_name}_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_CLANG})
      endif()
      if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(${target_name}_C_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_GCC})
        set(${target_name}_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_GCC})
      endif()
      if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set(${target_name}_C_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_MSVC})
        set(${target_name}_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_MSVC})
      endif()
    endif()
  elseif (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
    set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_UNKNOWN})
    set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_UNKNOWN})
    if (CMAKE_CPP_COMPILER_ID)
      if (CMAKE_CPP_COMPILER MATCHES ".*clang")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_CLANG})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_CLANG})
      endif()
      if (CMAKE_CPP_COMPILER_ID STREQUAL "GNU")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_GCC})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_GCC})
      endif()
      if (CMAKE_CPP_COMPILER_ID STREQUAL "MSVC")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_MSVC})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_MSVC})
      endif()
    endif()
  endif()
  message("${${target_name}_C_COMPILER_STRING} C compiler detected for target ${target_name}")
endmacro()

if (CMAKE_C_COMPILER_ID)
    if (CMAKE_C_COMPILER MATCHES ".*clang")
      message("compiler CLANG detected")
      set(NUCLEUS_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_CLANG})
    endif()

    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      message("compiler GCC detected")
      set(NUCLEUS_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_GCC})
    endif()

    if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
      message("compiler MSVC detected")
      set(NUCLEUS_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_MSVC})
    endif()
endif()

macro(nucleus_report_c_compiler_id)
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_CLANG})
    message("  - Nucleus C Compiler Id: CLANG")
  elseif (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC})
    message("  - Nucleus C Compiler Id: GCC")
  elseif (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC})
    message("  - Nucleus C Compiler Id: MSVC")
  elseif (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_UNKNOWN})
    message("  - Nucleus C Compiler Id: Unknown")
  else()
    message(FATAL_ERROR "unhandled enumeration element")
  endif()
endmacro()

# Compiler detection (C++).


set(NUCLEUS_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_UNKNOWN})

if (CMAKE_CXX_COMPILER_ID)
    if (CMAKE_CXX_COMPILER MATCHES ".*clang")
      message("compiler CLANG detected")
      set(NUCLEUS_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_CLANG})
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      message("compiler GCC detected")
      set(NUCLEUS_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_GCC})
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      message("compiler MSVC detected")
      set(NUCLEUS_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    endif()
endif()

macro(nucleus_report_cpp_compiler_id)
  if (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_CLANG})
    message("  - Nucleus C++ Compiler Id: CLANG")
  elseif (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    message("  - Nucleus C++ Compiler Id: GCC")
  elseif (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    message("  - Nucleus C++ Compiler Id: MSVC")
  elseif (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_UNKNOWN})
    message("  - Nucleus C++ Compiler Id: Unknown")
  else()
    message(FATAL_ERROR "unhandled enumeration element")
  endif()
endmacro()

# Platform detection.

set(NUCLEUS_PLATFORM_ID_UNKNOWN 0)
set(NUCLEUS_PLATFORM_ID_X64 1)
set(NUCLEUS_PLATFORM_ID_X86 2)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    #message("platform `x64` detected")
    set(NUCLEUS_PLATFORM_ID ${NUCLEUS_PLATFORM_ID_X64})
elseif ( CMAKE_SIZEOF_VOID_P EQUAL 4)
    #message("platform `x86` detected" )
    set(NUCLEUS_PLATFORM_ID ${NUCLEUS_PLATFORM_ID_X86})
endif()

macro(nucleus_report_platform_id)
  if (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X64})
    message("  - Nucleus Platform Id: x64")
  elseif (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X86})
    message("  - Nucleus Platform Id: x86")
  elseif (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_UNKNOWN})
    message("  - Nucleus Platform Id: Unknown")
  else()
    message(FATAL_ERROR "unhandled enumeration element")
  endif()
endmacro()

# Multi target generator detection.

if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC}))
    set(NUCLEUS_IS_MULTI_TARGET_GENERATOR YES)
else()
    set(NUCLEUS_IS_MULTI_TARGET_GENERATOR NO)
endif()

macro(nucleus_report_is_multi_target_generator)
    if (NUCLEUS_IS_MULTI_TARGET_GENERATOR)
      message("  - Nucleus Is Multi Target Generator: Yes")
    else()
      message("  - Nucleus Is Multi Target Generator: NO")
    endif()
endmacro()

#nucleus_report_c_compiler_id()
#nucleus_report_cpp_compiler_id()
#nucleus_report_platform_id()
#nucleus_report_is_multi_target_generator()
