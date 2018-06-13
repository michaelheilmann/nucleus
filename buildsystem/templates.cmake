# This file provides template for "modules", "targets".
# "targets" are "tests", "tools", and "static libraries".
# A "target" always belongs a "module".

# A template is a macro which is invoked with the module name, followed by the target name,
# followed by the list of static libraries against which the project is linked. The template
# will define the test executable/static library with the target name PROJECT_NAME which is
# equal to the specified target name.
#
# The macros will define several variables:
# 1) PROJECT_NAME contains the project name.
# 2) ${PROJECT_NAME}_LANGUAGE contains the language.
# 3) ${PROJECT_NAME}_SOURCE_FILES contains the source files.
# 4) ${PROJECT_NAME}_HEADER_FILES contains the header files.
# 5) ${PROJECT_NAME}_INLAY_FILES contains the inlay files.
# 6) ${PROJECT_NAME}_OPERATING_SYSTEM_ID contains the (target) operating system ID.
#
# You can add additional source, header, and inlay files by prepopulating the lists
# ${PROJECT_NAME}_SOURCE_FILES, ${PROJECT_NAME}_HEADER_FILES, and ${PROJECT_NAME}_INLAY_FILES.
include(${CMAKE_CURRENT_LIST_FILE}/../set_default_project_properties.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_operating_system.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

macro(define_target_base parent_project_name project_name language)
  detect_operating_system(${project_name})
  if (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
    project (${project_name} C)
	message("building C ${project_name}")
  elseif (${language} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
     project (${project_name} CXX)
	message("building C++ ${project_name}")
  else()
    message(FATAL "unknown language")
  endif()
  set(${project_name}_LANGUAGE ${language})
  detect_compiler(${parent_project_name} ${project_name} ${language})

  if (NOT DEFINED ${project_name}-With-Debug-Information)
    set(${project_name}-With-Debug-Information ${${parent_project_name}-With-Debug-Information})
  endif()

  if (NOT DEFINED ${project_name}-With-Optimizations)
    set(${project_name}-With-Optimizations ${${parent_project_name}-With-Optimizations})
  endif()

  if (NOT DEFINED ${project_name}-With-Static-Runtime)
    set(${project_name}-With-Static-Runtime ${${parent_project_name}-With-Static-Runtime})
  endif()

  if (NOT DEFINED ${project_name}-With-Pthreads)
    set(${project_name}-With-Pthreads ${${parent_project_name}-With-Pthreads})
  endif()
  
  set(temporary)

  if (${${project_name}_LANGUAGE} EQUAL ${NUCLEUS_LANGUAGE_ID_C})
    file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c")
    list(APPEND ${project_name}_SOURCE_FILES ${temporary})
    
	file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
    set_source_files_properties(${temporary} PROPERTIES HEADER_FILE_ONLY TRUE)
    list(APPEND ${project_name}_HEADER_FILES ${temporary})
  elseif (${${project_name}_LANGUAGE} EQUAL ${NUCLEUS_LANGUAGE_ID_CPP})
    file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
    list(APPEND ${project_name}_SOURCE_FILES ${temporary})
    
	file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.hpp")
    set_source_files_properties(${temporary} PROPERTIES HEADER_FILE_ONLY TRUE)
    list(APPEND ${project_name}_HEADER_FILES ${temporary}) 
  endif()

  file(GLOB_RECURSE temporary "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.i")
  set_source_files_properties(${${project_name}_INLAY_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
  list(APPEND ${project_name}_INLAY_FILES ${temporary})
endmacro()

# Defines the CMake project of a "module".
macro(define_module module_name)
  project (${module_name} C)
  message("building ${PROJECT_NAME}")

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
macro(define_test parent_project_name project_name language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_executable(${project_name} ${${PROJECT_NAME}_SOURCE_FILES}
                                 ${${PROJECT_NAME}_HEADER_FILES}
                                 ${${PROJECT_NAME}_INLAY_FILES})

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})

  add_test(NAME ${project_name} COMMAND $<TARGET_FILE:${project_name}>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

# Defines the CMake project of a "shared library".
macro(define_shared_library parent_project_name project_name language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  
  add_library(${project_name} SHARED ${${project_name}_SOURCE_FILES}
                                     ${${project_name}_HEADER_FILES}
									 ${${project_name}_INLAY_FILES})

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_include_directories(${project_name} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})
  
  # Add the -fPIC flag to static libraries under Linux.
  # This allows for linking dynamically loadable libraries to these static libraries.
  # This hurts performance.
  if (${${project_name}_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
    set_target_properties(${project_name} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
  endif()
endmacro()

# Defines the CMake project of a "static library".
macro(define_static_library parent_project_name project_name language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_library(${project_name} STATIC ${${project_name}_SOURCE_FILES}
                                     ${${project_name}_HEADER_FILES}
									 ${${project_name}_INLAY_FILES})

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_include_directories(${project_name} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})
  
  # Add the -fPIC flag to static libraries under Linux.
  # This allows for linking dynamically loadable libraries to these static libraries.
  # This hurts performance.
  if (${${project_name}_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
    set_target_properties(${project_name} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
  endif()
endmacro()

# Defines the CMake project of an "executable".
macro(define_executable parent_project_name project_name language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_executable(${project_name} ${${project_name}_SOURCE_FILES}
                                 ${${project_name}_HEADER_FILES}
								 ${${project_name}_INLAY_FILES})

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})
endmacro()

# Defines the CMake project of a "dynamic library".
# A "dynamic library" can exclusively used with dlopen/GetModuleHandle/....
# Unlike other libraries, they are put in the "bin" folder and not in the "lib" folder.
macro(define_dynamic_library parent_project_name project_name language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_library(${project_name} MODULE ${${project_name}_SOURCE_FILES}
                                     ${${project_name}_HEADER_FILES}
			                         ${${project_name}_INLAY_FILES})

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})

  # Put "dynamic libraries" in the same folder as "executables".
  if (NUCLEUS_IS_MULTI_TARGET_GENERATOR)
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
      string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
      set_target_properties(${project_name} PROPERTIES
                            LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG}
							${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG}})
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
  else()
    set_target_properties(${project_name} PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY
						  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  endif()
  set_target_properties(${project_name} PROPERTIES PREFIX "")
endmacro()
