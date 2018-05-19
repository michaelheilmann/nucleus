include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

# Defines the global options
# - ${module}-With-Static-Runtime
# - ${module}-With-Pthreads
# - ${module}-With-Optimizations
# - ${module}-With-Debug-Information
macro(set_default_module_properties module)
	if (MSVC OR MINGW)
	  if (NOT DEFINED ${module}-With-Static-Runtime)
		string(CONCAT description
			   "enable/disable compilation with static runtime for module ${module}.\n"
			   "ON enables compilation with static runtime, OFF disables compilation with static runtime.\n"
			   "Initial value is ON.\n"
			   "Only available under MSVC and MINGW")
		set(${module}-With-Static-Runtime ON CACHE BOOL ${description} FORCE)
	  endif()
      if (NOT DEFINED ${module}-With-Pthreads)
        string(CONCAT description
               "enable/disable compilation with pthreads under Windows for module ${module}."
               "ON enables compilation with pthreads under windows, OFF disables compilation with pthreads under windows."
               "Initial value is OFF."
               "Only available under MSVC and MINGW")
		set(${module}-With-Pthreads OFF CACHE BOOL ${description} FORCE)
      endif()
	endif()

	if (NOT DEFINED ${module}-With-Optimizations)
	  string(CONCAT description
			 "enable/disable compilation with optimizations for ${module}.\n"
			 "ON enables compilation with optimizations, OFF disables compilation with optimizations.\n"
			 "Initial value is ON.") 
	  set(${module}-With-Optimizations ON CACHE BOOL ${description} FORCE)
	endif()

	if (NOT DEFINED ${module}-With-Debug-Information)
	  string(CONCAT description
			 "enable/disable compilation with debug information for module ${module}.\n"
			 "ON enables compilation with debug information, OFF disables compilation with debug information.\n"
			 "Initial value is OFF.")
	  set(${module}-With-Debug-Information OFF CACHE BOOL ${description} FORCE)
	endif()

	# Enable/disable compilation and execution of unit tests.
	# The value of this option can be set from the command-line by -D{module}-with-tests=(ON|OFF).
	string(CONCAT description
		   "enable/disable compilation and execution of unit tests for module ${module}."
		   "ON enables compilation and execution of unit tests, OFF disables compilation and execution of unit tests."
		   "Initial value is ON.")
	option(${module}-With-Tests ${description} ON)
endmacro()
