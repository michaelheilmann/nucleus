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
# 2) ${PROJECT_NAME}_SOURCE_FILES contains the source files.
# 3) ${PROJECT_NAME}_HEADER_FILES contains the header files.
# 4) ${PROJECT_NAME}_LIBRARIES contains the libraries.
# 5) ${PROJECT_NAME}_INLAY_FILES contains the inlay files.
#
# You can add additional source, header, and inlay files by prepopulating the lists
# ${PROJECT_NAME}_SOURCE_FILES, ${PROJECT_NAME}_HEADER_FILES, and ${PROJECT_NAME}_INLAY_FILES.
include(${CMAKE_CURRENT_LIST_FILE}/../set_default_project_properties.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_operating_system.cmake)
include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

macro(define_target_base parent_project_name project_name language)
  # (1) ${project_name}_OPERATING_SYSTEM is defined.
  detect_operating_system(${project_name})
  detect_compiler(${parent_project_name} ${project_name} ${language})
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

  if (NOT DEFINED ${project_name}-With-Debug-Information)
    set(${project_name}-With-Debug-Information ${${parent_project_name}-With-Debug-Information})
  endif()

  if (NOT DEFINED ${project_name}-With-Optimizations)
    set(${project_name}-With-Optimizations ${${parent_project_name}-With-Optimizations})
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
  set(CTEST_OUTPUT_ON_FAILURE ON)

  # If with optimizations is not specified ...
  if (NOT DEFINED ${module_name}-With-Optimizations)
    # ... use defaults.
	message("${module_name}-With-Optimizations not defined - defaulting to ON")
	set(${module_name}-With-Optimizations ON)
  endif()
  # If with debug information is not specified ...
  if (NOT DEFINED ${module_name}-With-Debug-Information)
    # ... use defaults.
	message("${module_name}-With-Debug-Information not defined - defaulting to OFF")
    set(${module_name}-With-Debug-Information OFF)
  endif()
  
  # Set default module properties.
  set_default_module_properties(${module_name})
endmacro()

# Defines the CMake project of a "test".
macro(define_test parent_project_name project_name libraries language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_executable(${project_name} ${${PROJECT_NAME}_SOURCE_FILES}
                                 ${${PROJECT_NAME}_HEADER_FILES}
                                 ${${PROJECT_NAME}_INLAY_FILES})

  set(${project_name}_LIBRARIES ${libraries})
  foreach(library ${${PROJECT_NAME}_LIBRARIES})
    target_link_libraries(${project_name} ${library})
  endforeach()

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})

  add_test(NAME ${project_name} COMMAND $<TARGET_FILE:${project_name}>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

# Defines the CMake project of a "static library".
macro(define_static_library parent_project_name project_name libraries language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_library(${project_name} STATIC ${${project_name}_SOURCE_FILES}
                                     ${${project_name}_HEADER_FILES}
									 ${${project_name}_INLAY_FILES})


  set(${project_name}_LIBRARIES ${libraries})
  foreach(library ${${project_name}_LIBRARIES})
    target_link_libraries(${project_name} ${library})
  endforeach()

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_include_directories(${project_name} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")


  set_project_default_properties(${parent_project_name} ${project_name})


  IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(${project_name}.Documentation ${DOXYGEN_EXECUTABLE} COMMENT "Building documentation")
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
  ENDIF(DOXYGEN_FOUND)
endmacro()

# Defines the CMake project of an "executable".
macro(define_executable parent_project_name project_name libraries language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_executable(${project_name} ${${project_name}_SOURCE_FILES}
                                 ${${project_name}_HEADER_FILES}
								 ${${project_name}_INLAY_FILES})


  set(${project_name}_LIBRARIES ${libraries})
  foreach(library ${${project_name}_LIBRARIES})
    target_link_libraries(${project_name} ${library})
  endforeach()

  target_include_directories(${project_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  set_project_default_properties(${parent_project_name} ${project_name})
endmacro()

# Defines the CMake project of a "dynamic library".
# A "dynamic library" can exclusively used with dlopen/GetModuleHandle/....
# Unlike other libraries, they are put in the "bin" folder and not in the "lib" folder.
macro(define_dynamic_library parent_project_name project_name libraries language)
  define_target_base(${parent_project_name} ${project_name} ${language})

  add_library(${project_name} MODULE ${${project_name}_SOURCE_FILES}
                                     ${${project_name}_HEADER_FILES}
			                         ${${project_name}_INLAY_FILES})


  set(${project_name}_LIBRARIES ${libraries})
  foreach(library ${${project_name}_LIBRARIES})
    target_link_libraries(${project_name} ${library})
  endforeach()

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
endmacro()