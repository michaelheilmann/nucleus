# Detect compiler and platform detection.
#
# Provides the following numeric constants for identifying C++ compilers:
# - NUCLEUS_CPP_COMPILER_ID_UNKNOWN
# - NUCLEUS_CPP_COMPILER_ID_CLANG
# - NUCLEUS_CPP_COMPILER_ID_GCC
# - NUCLEUS_CPP_COMPILER_ID_MSVC
# - NUCLEUS_CPP_COMPILER_ID_MINGW
#
# If compiler detection succeeds,
# define ${target}_CPP_COMPILER_ID to one of the constants listed above except for ${target}_CPP_COMPILER_ID_UNKNOWN.
# If compiler detection fails,
# define ${target}_CPP_COMPILER_ID to NUCLEUS_CPP_COMPILER_ID_UNKNOWN.
#
# Provides the following numeric constants for identifying C compilers:
# - NUCLEUS_C_COMPILER_ID_UNKNOWN
# - NUCLEUS_C_COMPILER_ID_CLANG
# - NUCLEUS_C_COMPILER_ID_GCC
# - NUCLEUS_C_COMPILER_ID_MSVC
# - NUCLEUS_C_COMPILER_ID_MINGW
#
# If compiler detection succeeds,
# define ${target}_C_COMPILER_ID to one of the constants listed above except for NUCLEUS_C_COMPILER_ID_UNKNOWN.
# If compiler detection fails,
# define ${target}_C_COMPILER_ID to NUCLEUS_C_COMPILER_ID_UNKNOWN otherwise.

include(${CMAKE_CURRENT_LIST_FILE}/../languages.cmake)

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

macro(detect_compiler parent_target_name target_name language)
  set(${target_name}_C_COMPILER_ID ${NUCLEUS_C_COMPILER_ID_UNKNOWN})
  set(${target_name}_C_COMPILER_STRING ${NUCLEUS_C_COMPILER_STRING_UNKNOWN})
  set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_UNKNOWN})
  set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_CPP_COMPILER_STRING_UNKNOWN})
  if (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
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
	message("  - ${target_name} C compiler: ${${target_name}_C_COMPILER_STRING}")
  elseif (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
    if (CMAKE_CPP_COMPILER_ID)
      if (CMAKE_CPP_COMPILER MATCHES ".*clang")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_CPP_COMPILER_STRING_CLANG})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_CLANG})
      endif()
      if (CMAKE_CPP_COMPILER_ID STREQUAL "GNU")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_CPP_COMPILER_STRING_GCC})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_GCC})
      endif()
      if (CMAKE_CPP_COMPILER_ID STREQUAL "MSVC")
        set(${target_name}_CPP_COMPILER_STRING ${NUCLEUS_CPP_COMPILER_STRING_MSVC})
        set(${target_name}_CPP_COMPILER_ID ${NUCLEUS_CPP_COMPILER_ID_MSVC})
      endif()
    endif()
	message("  - ${target_name} C++ compiler: ${${target_name}_CPP_COMPILER_STRING}")
  endif()
endmacro()
