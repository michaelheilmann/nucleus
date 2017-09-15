/// @file nucleus-get-file-contents-windows.h
/// @author Michael Heilmann
/// @brief Get the contents of a file (Windows).

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

#endif
