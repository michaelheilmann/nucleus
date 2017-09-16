/// @file nucleus-set-file-contents-windows.h
/// @brief Set the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(_WIN32)

#pragma once

#include "nucleus-set-file-contents.h"

/// @brief Implementation of the @a Nucleus_setFileContentsFunction function for Windows.
/// @param pathname, bytes, numberOfBytes see the documentation of @a Nucleus_setFileContentsFunction for more information
/// @return see the documentation of @a Nucleus_setFileContentsFunction for more information
/// @post see the documentation of @a Nucleus_setFileContentsFunction for more information.
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContentsWindows
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(size_t numberOfBytes)
    );

#endif
