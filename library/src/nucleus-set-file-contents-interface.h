/// @file nucleus-set-file-contents-inteface.h
/// @brief Function prototype for setting the contents of a file.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#include "nucleus.h"
#include "nucleus-status.h"
#include "nucleus-annotations.h"

/// @brief Set the contents of a file.
/// @details The file is overwritten if it exists. The file is created if it does not exist.
/// @param pathname a pointer to the pathname of the file
/// @param bytes a pointer to a @a (char *) variable
/// @param numberOfBytes a pointer to a @a (size_t) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(size_t numberOfBytes)
    );
