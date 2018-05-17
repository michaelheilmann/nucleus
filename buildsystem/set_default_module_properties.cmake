include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

# Defines the global options
# - With-Static-Runtime
# - With-Pthreads
# - With-Optimizations
# - With-Debug-Information
macro(set_default_module_options)
	if (MSVC OR MINGW)
	  if (NOT DEFINED With-Static-Runtime)
		string(CONCAT description
			   "enable/disable compilation with static runtime.\n"
			   "ON enables compilation with static runtime, OFF disables compilation with static runtime.\n"
			   "Initial value is ON.\n"
			   "Only available under MSVC and MINGW")
		set(With-Static-Runtime ON CACHE BOOL ${description} FORCE)
	  endif()
	  if (NOT DEFINED Nucleus-With-Pthreads)
		string(CONCAT description
			   "enable/disable compilation with pthreads under Windows.\n"
			   "ON enables compilation with pthreads under windows, OFF disables compilation with pthreads under Windows.\n"
			   "Initial value is OFF.\n"
			   "Only available under MSVC and MINGW")
		set(Nucleus-With-Pthreads OFF CACHE BOOL ${description} FORCE)
	  endif()
	endif()

	if (NOT DEFINED With-Optimizations)
	  string(CONCAT description
			 "enable/disable compilation with optimizations.\n"
			 "ON enables compilation with optimizations, OFF disables compilation with optimizations.\n"
			 "Initial value is ON.") 
	  set(With-Optimizations ON CACHE BOOL ${description} FORCE)
	endif()

	if (NOT DEFINED With-Debug-Information)
	  string(CONCAT description
			 "enable/disable compilation with debug information.\n"
			 "ON enables compilation with debug information, OFF disables compilation with debug information.\n"
			 "Initial value is OFF.")
	  set(With-Debug-Information OFF CACHE BOOL ${description} FORCE)
	endif()
endmacro()
