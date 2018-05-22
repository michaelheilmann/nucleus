/// @file Nucleus/Configuration.h
/// @brief The configuration file of Nucleus.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

#include "Nucleus/Configuration.h.i"

// The only reliable way to detect which Apple operating system is running, is to include the
// "TargetConditionals.h" header and analyze the symbolic constants defined in it. Either we
// find a way to handle this from within CMake or some CMake plugin needs to be written to
// distinguish between the various Appl operating system.
#if Nucleus_OperatingSystem == Nucleus_Operating_System_MACOS
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define Nucleus_OperatingSystem Nucleus_OperatingSystem_IOSSIMULATOR
		#error("IOSSIMULATOR not yet supported")
	#elif TARGET_OS_IPHONE == 1
		#define Nucleus_OperatingSystem Nucleus_OperatingSystem_IOS
		#error("IOS not yet supported")
	#elif TARGET_OS_MAC == 1
		#define Nucleus_OperatingSystem Nucleus_OperatingSystem_MACOS /* Nothing changed. */
	#endif
#endif
