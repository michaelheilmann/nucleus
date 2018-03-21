include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

# == Doxygen ==================================================================================== #

# Find Doxygen.
# Remark: CMake 3.10 fails under Cygwin for no reason on FIND_PACKAGE(Doxygen).
FIND_PACKAGE(Doxygen)
IF(NOT DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF()

# == Default project settings =================================================================== #

# Macro adjusting (mostly compiler-specific) properties of a project.
macro(set_project_default_properties)
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR ${NUCLEUS_CXX_COMPILER_ID} EQUAL ${NUCLEUS_CXX_COMPILER_ID_MSVC})
    message("case of MSVC C or C++: add_definitions(-DUNICODE -D_UNICODE)")
    add_definitions(-DUNICODE -D_UNICODE)
  endif()

  # Set the C++ standard to C++ 17.
  if (NOT (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR ${NUCLEUS_CXX_COMPILER_ID} EQUAL ${NUCLEUS_CXX_COMPILER_ID_MSVC}))
    #message("case of neither MSVC C nor MSVC C++: set(CMAKE_CXX_STANDARD 17)")
    set(CMAKE_CXX_STANDARD 17)
  endif()

  # GNU GCC (C/C++) settings
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C/C++)")
    # Set standard to C++ 17, enable -Wall and -Wextra
    add_definitions("-Wall -Wextra -D_GNU_SOURCE")
    add_definitions("-Werror=implicit-function-declaration")
    add_definitions("-Werror=incompatible-pointer-types")
  endif()

  # GNU GCC (C/C++) settings
  if (${NUCLEUS_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C/C++)")
    if (With-Optimizations AND With-Debug-Information)
        message("  - enabling optimizations and debug information")
        # Enable optimizations that do not interfere with debug experience.
        add_definitions("-Og")
        # Enable extra debug information.
        add_definitions("-ggdb3")
    elseif (NOT With-Optimizations AND With-Debug-Information)
        message("  - enabling debug information")
        # Disable optimizations.
        add_definitions("-O0")
        # Enable extra debug information.
        add_definitions("-ggdb3")
    elseif(With-Optimizations AND NOT With-Debug-Information)
        message("  - enabling optimizations")
        # Enable optimizations.
        add_definitions("-O3")
    else()
        message(WARNING "  - unspecified optimization and debug information settings")
    endif()
  endif()

  # GNU GCC (C++) specific settings
  if (${NUCLEUS_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_GCC})
    #message("case of GCC (C++)")
    # Set standard to C++ 17, enable -Wall and -Wextra
    add_definitions("-std=gnu++17")
    # Disable some warnings
    # TODO: IdLib can have these warnings enabled.
    add_definitions("-Wno-reorder -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter")
  endif()

  # (2) MSVC C++ settings
  # TODO: Raise an error if the MSVC version is too low.
  if (${NUCLEUS_CXX_COMPILER_ID} EQUAL ${NUCLEUS_CXX_COMPILER_ID_MSVC})
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
    if(${variable} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
    endif()
    endforeach()
    set(MSVC_RUNTIME "static")
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
    message("  - Nucleus Platform Id: x86")
    message("  - path for CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin")
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin )
    message("  - path for CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib )
    message("  - path for CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
    message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
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
