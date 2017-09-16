/// @file nucleus-get-file-contents-windows.h
/// @brief Get the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(_WIN32)

#pragma once

#include "nucleus-get-file-contents.h"

/// @brief Implementation of the @a Nucleus_getFileContentsFunction function for Windows.
/// @param pathname, bytes, numberOfBytes see the documentation of @a Nucleus_getFileContentsFunction for more information
/// @return see the documentation of @a Nucleus_getFileContentsFunction for more information
/// @post see the documentation of @a Nucleus_getFileContentsFunction for more information
Nucleus_NonNull(1, 2, 3) Nucleus_Status
Nucleus_getFileContentsWindows
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_OutputParameter(char **bytes),
        Nucleus_OutputParameter(size_t *numberOfBytes)
    );
	
/// @brief Implementation of the @a Nucleus_getFileContentsExtendedFunction function for Windows.
/// @param pathname, bytes, numberOfBytes see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
/// @return see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
/// @post see the documentation of @a Nucleus_getFileContentsExtendedFunction for more information
Nucleus_NonNull(1,2,3) Nucleus_Status
Nucleus_getFileContentsExtendedWindows
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_InputOutputParameter(void *object),
		Nucleus_InputOutputParameter(Nucleus_getFileContentsExtendedCallbackFunction *callback)
	);

#endif
