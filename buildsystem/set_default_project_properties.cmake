include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../languages.cmake)

# == Doxygen ==================================================================================== #

# Find Doxygen.
# Remark: CMake 3.10 fails under Cygwin for no reason on FIND_PACKAGE(Doxygen).
FIND_PACKAGE(Doxygen)
IF(NOT DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF()

# == Default project settings =================================================================== #

# Macro adjusting (mostly compiler-specific) properties of a project.
macro(set_project_default_properties module target)
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    #message("case of MSVC C or C++: add_definitions(-DUNICODE -D_UNICODE)")
    target_compile_options(${target} PRIVATE -DUNICODE -D_UNICODE)
  endif()

  # Set the C++ standard to C++ 17.
  if (${${target}_LANGUAGE} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
    if (NOT (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC}))
      #message("case of neither MSVC C nor MSVC C++: set(CMAKE_CXX_STANDARD 17)")
      set(CMAKE_CXX_STANDARD 17)
    endif()
  endif()

  # GNU GCC (C/C++) settings
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C/C++)")
    # Set standard to C++ 17, enable -Wall and -Wextra
    target_compile_options(${target} PRIVATE -Wall -Wextra -D_GNU_SOURCE)
    target_compile_options(${target} PRIVATE -Werror=implicit-function-declaration)
    target_compile_options(${target} PRIVATE -Werror=incompatible-pointer-types)
    target_compile_options(${target} PRIVATE -Werror=unused-function)
    target_compile_options(${target} PRIVATE -Werror=format-extra-args)
    target_compile_options(${target} PRIVATE -Werror=int-conversion)
    target_compile_options(${target} PRIVATE -Werror=return-type)
    target_compile_options(${target} PRIVATE -Werror=discarded-qualifiers)
  endif()

  # GNU GCC (C/C++) settings
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C/C++)")
    if (${target}-With-Optimizations AND ${target}-With-Debug-Information)
        message("  - enabling optimizations and debug information")
        # Enable optimizations that do not interfere with debug experience.
        target_compile_options(${target} PRIVATE -Og)
        # Enable extra debug information.
        target_compile_options(${target} PRIVATE -ggdb3)
    elseif (NOT ${target}-With-Optimizations AND ${target}-With-Debug-Information)
        message("  - enabling debug information")
        # Disable optimizations.
        target_compile_options(${target} PRIVATE -O0)
        # Enable extra debug information.
        target_compile_options(${target} PRIVATE -ggdb3)
    elseif(${target}-With-Optimizations AND NOT ${target}-With-Debug-Information)
        message("  - enabling optimizations")
        # Enable optimizations.
        target_compile_options(${target} PRIVATE -O3)
    else()
        message(WARNING "  - unspecified optimization and debug information settings")
    endif()
  endif()

  # GNU GCC (C++) specific settings
  if (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C++)")
    # If language is C++, then the GNU C++ 17 shall be used.
	if (${${target}_LANGUAGE} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
      target_compile_options(${target} PRIVATE -std=gnu++17)
	endif()
    # If language is C++, then disable some warnings.
    # TODO: Idlib can have these warnings enabled.
    if (${${target}_LANGUAGE} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
      target_compile_options(${target} PRIVATE -Wno-reorder)
	endif()
    target_compile_options(${target} PRIVATE -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter)
  endif()

  # (2) MSVC C++ settings
  # TODO: Raise an error if the MSVC version is too low.
  if (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    #message("case of MSVC (C++)")
    if (MSVC_VERSION GREATER_EQUAL "1900")
      include(CheckCXXCompilerFlag)
      CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
      if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
      endif()
    endif()
  endif()

  # (2) MSVC (C/C++) settings
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    #message("case of MSVC (C/C++)")
    set(variables
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    foreach(variable ${variables})
      string(REGEX REPLACE "/MTd" "" ${variable} "${${variable}}")
      string(REGEX REPLACE "/MT" "" ${variable} "${${variable}}")
      string(REGEX REPLACE "/MDd" "" ${variable} "${${variable}}")
      string(REGEX REPLACE "/MD" "" ${variable} "${${variable}}")
    endforeach()
    if (${${target}-With-Static-Runtime})
      # Enable static runtime.
      message("  - enabling static runtime")
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:/MTd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/MTd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:RELEASE>>:/MT>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:MINSIZEREL>>:/MT>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:/MTd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/MTd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELEASE>>:/MT>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MINSIZEREL>>:/MT>)
      set(MSVC_RUNTIME "static")
    else()
      # Enable dynamic runtime.
      message("  - enabling dynamic runtime")
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:/MDd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/MDd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:RELEASE>>:/MD>)
      target_compile_options(${target} PRIVATE $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:MINSIZEREL>>:/MD>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:/MDd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/MDd>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELEASE>>:/MD>)
      target_compile_options(${target} PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MINSIZEREL>>:/MD>)
      set(MSVC_RUNTIME "dynamic")
    endif()
  endif()

  # (3) MSVC C++ settings
  if (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    #message("case of MSVC (C++)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
  endif()
endmacro(set_project_default_properties)

# For configuring the output paths, we distinguish between single- and multi-target generators.
if (NUCLEUS_IS_MULTI_TARGET_GENERATOR)
  #message("multi-target generator")
  # For multi-target generators like MSVC, we specify disjoint output paths for targets.
  foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    # Suffix for CMake's configuration type specific output path variables.
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    # The name of the output configuration as used in the pathnames.
    string( TOLOWER ${OUTPUTCONFIG} OUTPUTCONFIG_FOLDER_NAME)
    # The name of the output platform as used in the pathnames.
    if (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X64})
       set(OUTPUTPLATFORM_FOLDER_NAME "x64")
    elseif (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X86})
       set(OUTPUTPLATFORM_FOLDER_NAME "x86")
    else()
        message(FATAL_ERROR "unhandled enumeration element")    
    endif()
    #message("  - Nucleus Platform Id: x86")
    #message("  - path for CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    #message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin")
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin )
    #message("  - path for CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    #message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib )
    #message("  - path for CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    #message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib )
  endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
else()
    #message("single-target generator")
  
  # The name of the output platform as used in the pathnames.
  if (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X64})
     set(OUTPUTPLATFORM_FOLDER_NAME "x64")
  elseif (${NUCLEUS_PLATFORM_ID} EQUAL ${NUCLEUS_PLATFORM_ID_X86})
     set(OUTPUTPLATFORM_FOLDER_NAME "x86")
  else()
    message(FATAL_ERROR "unhandled enumeration element")    
  endif()
  
  # Adjust the archive output directory.
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/lib)

  # Adjust the library output directory.
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/lib)

  # Adjust the runtime output directory.
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/bin)
endif()
