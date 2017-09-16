/// @file nucleus-get-file-contents-linux.h
/// @brief Get the contents of a file (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#if defined(__linux__)

#include "nucleus-get-file-contents.h"

/// @brief Implementation of the @a Nucleus_getFileContentsExtendedFunction function for Linux.
/// @param pathname, bytes, numberOfBytes see the documentation of @a Nucleus_getFileContentsFunction for more information
/// @return see the documentation of @a Nucleus_getFileContentsFunction for more information
/// @post see the documentation of @a Nucleus_getFileContentsFunction for more information
Nucleus_NonNull(1, 2, 3) Nucleus_Status
Nucleus_getFileContentsLinux
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_OutputParameter(char **bytes),
		Nucleus_OutputParameter(size_t *numberOfBytes)
	);
	
/// @brief Implementation of the @a Nucleus_getFileContentsExtendedFunction function for Linux.
/// @param pathname, bytes, numberOfBytes see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
/// @return see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
/// @post see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
Nucleus_NonNull(1,2,3) Nucleus_Status
Nucleus_getFileContentsExtendedLinux
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_InputOutputParameter(void *object),
		Nucleus_InputOutputParameter(Nucleus_getFileContentsExtendedCallbackFunction *callback)
	);

#endif
