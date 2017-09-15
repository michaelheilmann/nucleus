/// @file nucleus-get-file-contents-linux.h
/// @author Michael Heilmann
/// @brief Get the contents of a file (Linux).
#pragma once

#if defined(__linux__)

#include "nucleus-get-file-contents.h"

/// @brief Implementation of the @a Nucleus_getFileContentsFunction function for Windows.
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

#endif
