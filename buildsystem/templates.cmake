# This file provides template for "modules", "targets".
# "targets" are "tests", "tools", and "static libraries".
# A "target" always belongs a "module".

# A template is a macro which is invoked with the module name, followed by the target name,
# followed by the list of static libraries against which the project is linked. The template
# will define the test executable/static library with the target name target_name which is
# equal to the specified target name.
#
# The macros will define several variables:
# 1) target_name contains the project name.
# 2) ${target_name}_LANGUAGE_ID contains the language.
# 3) ${target_name}_C_COMPILER_ID and ${target_name}_CPP_COMPILER_ID
# 4) ${target_name}_SOURCE_FILES contains the source files.
# 5) ${target_name}_HEADER_FILES contains the header files.
# 6) ${target_name}_INLAY_FILES contains the inlay files.
# 7) ${target_name}_OPERATING_SYSTEM_ID contains the (target) operating system ID.
#
# You can add additional source, header, and inlay files by prepopulating the lists
# ${target_name}_SOURCE_FILES, ${target_name}_HEADER_FILES, and ${target_name}_INLAY_FILES.
include(${CMAKE_CURRENT_LIST_FILE}/../set_default_project_properties.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_operating_system.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_void_pointer_size.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_isa.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_multi_target_generator.cmake)

macro(define_target_base parent_target_name target_name language)
  detect_operating_system(${target_name})
  if (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
    project (${target_name} C)
	message("building C ${target_name}")
  elseif (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
     project (${target_name} CXX)
	message("building C++ ${target_name}")
  else()
    message(FATAL "unknown language")
  endif()
  set(${target_name}_LANGUAGE_ID ${language})
  detect_compiler(${parent_target_name} ${target_name} ${language})
  detect_multi_target_generator(${parent_target_name} ${target_name} ${language})
  detect_void_pointer_size(${parent_target_name} ${target_name} ${language})
  detect_isa(${parent_target_name} ${target_name} ${language})

  if (NOT DEFINED ${target_name}-With-Debug-Information)
    set(${target_name}-With-Debug-Information ${${parent_target_name}-With-Debug-Information})
  endif()

  if (NOT DEFINED ${target_name}-With-Optimizations)
    set(${target_name}-With-Optimizations ${${parent_target_name}-With-Optimizations})
  endif()

  if (NOT DEFINED ${target_name}-With-Static-Runtime)
    set(${target_name}-With-Static-Runtime ${${parent_target_name}-With-Static-Runtime})
  endif()

  if (NOT DEFINED ${target_name}-With-Pthreads)
    set(${target_name}-With-Pthreads ${${parent_target_name}-With-Pthreads})
  endif()
  
  set(temporary)

  if (${${target_name}_LANGUAGE_ID} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
    file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
    list(APPEND ${target_name}_SOURCE_FILES ${temporary})
    
	file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
    set_source_files_properties(${temporary} PROPERTIES HEADER_FILE_ONLY TRUE)
    list(APPEND ${target_name}_HEADER_FILES ${temporary})
  elseif (${${target_name}_LANGUAGE_ID} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
    file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
    list(APPEND ${target_name}_SOURCE_FILES ${temporary})
    
	file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.hpp")
    set_source_files_properties(${temporary} PROPERTIES HEADER_FILE_ONLY TRUE)
    list(APPEND ${target_name}_HEADER_FILES ${temporary}) 
  endif()

  file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.i")
  set_source_files_properties(${${target_name}_INLAY_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
  list(APPEND ${target_name}_INLAY_FILES ${temporary})
endmacro()

# Defines the CMake project of a "module".
macro(define_module module_name)
  project (${module_name} C)
  message("building ${target_name}")

  # Enable testing.
  include(CTest)
  enable_testing()

  # If with option is not specified ...
  if (NOT DEFINED ${module_name}-With-Static-Runtime)
    # ... use defaults.
	message("${module_name}-With-Static-Runtime not defined - defaulting to OFF")
    set(${module_name}-With-Static-Runtime OFF)
  endif()
  # If option is not specified ...
  if (NOT DEFINED ${module_name}-With-Optimizations)
    # ... use defaults.
	message("${module_name}-With-Optimizations not defined - defaulting to ON")
	set(${module_name}-With-Optimizations ON)
  endif()
  # If option is not specified ...
  if (NOT DEFINED ${module_name}-With-Debug-Information)
    # ... use defaults.
	message("${module_name}-With-Debug-Information not defined - defaulting to OFF")
    set(${module_name}-With-Debug-Information OFF)
  endif()
  # If option is not specified ...
  if (NOT DEFINED ${module_name}-With-Pthreads)
    # ... use defaults.
	message("${module_name}-With-Pthreads not defined - defaulting to OFF")
    set(${module_name}-With-Pthreads OFF)
  endif()
  
  # Set default module properties.
  set_default_module_properties(${module_name})
endmacro()

# Defines the CMake project of a "test".
macro(define_test parent_target_name target_name language)
  define_target_base(${parent_target_name} ${target_name} ${language})

  add_executable(${target_name} ${${target_name}_SOURCE_FILES}
                                 ${${target_name}_HEADER_FILES}
                                 ${${target_name}_INLAY_FILES})

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_target_name} ${target_name})

  add_test(NAME ${target_name} COMMAND $<TARGET_FILE:${target_name}>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

# Defines the CMake project of a "shared library".
macro(define_shared_library parent_target_name target_name language)
  define_target_base(${parent_target_name} ${target_name} ${language})

  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  
  add_library(${target_name} SHARED ${${target_name}_SOURCE_FILES}
                                     ${${target_name}_HEADER_FILES}
									 ${${target_name}_INLAY_FILES})

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_include_directories(${target_name} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_target_name} ${target_name})
  
  # Add the -fPIC flag to static libraries under Linux.
  # This allows for linking dynamically loadable libraries to these static libraries.
  # This hurts performance.
  if (${${target_name}_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
    set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
  endif()
endmacro()

# Defines the CMake project of a "static library".
macro(define_static_library parent_target_name target_name language)
  define_target_base(${parent_target_name} ${target_name} ${language})

  add_library(${target_name} STATIC ${${target_name}_SOURCE_FILES}
                                     ${${target_name}_HEADER_FILES}
									 ${${target_name}_INLAY_FILES})

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_include_directories(${target_name} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_target_name} ${target_name})
  
  # Add the -fPIC flag to static libraries under Linux.
  # This allows for linking dynamically loadable libraries to these static libraries.
  # This hurts performance.
  if (${${target_name}_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
    set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
  endif()
endmacro()

# Defines the CMake project of an "executable".
macro(define_executable parent_target_name target_name language)
  define_target_base(${parent_target_name} ${target_name} ${language})

  add_executable(${target_name} ${${target_name}_SOURCE_FILES}
                                 ${${target_name}_HEADER_FILES}
								 ${${target_name}_INLAY_FILES})

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_target_name} ${target_name})
endmacro()

# Defines the CMake project of a "dynamic library".
# A "dynamic library" can exclusively used with dlopen/GetModuleHandle/....
# Unlike other libraries, they are put in the "bin" folder and not in the "lib" folder.
macro(define_dynamic_library parent_target_name target_name language)
  define_target_base(${parent_target_name} ${target_name} ${language})

  add_library(${target_name} MODULE ${${target_name}_SOURCE_FILES}
                                    ${${target_name}_HEADER_FILES}
			                        ${${target_name}_INLAY_FILES})

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_target_name} ${target_name})

  # Put "dynamic libraries" in the same folder as "executables".
  get_target_property(temporary ${target_name} RUNTIME_OUTPUT_DIRECTORY)
  if (${target_name}_IS_MULTI_TARGET_GENERATOR)
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
      string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	  get_target_property(temporary ${target_name} RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG})
      set_target_properties(${target_name} PROPERTIES
                            LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG}
							${temporary})
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
  else()
    get_target_property(temporary ${target_name} RUNTIME_OUTPUT_DIRECTORY)
    set_target_properties(${target_name} PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY
						  ${temporary})
  endif()
  # Remove any prefix from the file name of the "dynamic library".
  set_target_properties(${target_name} PROPERTIES PREFIX "")
endmacro()
