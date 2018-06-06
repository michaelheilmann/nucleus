/// @file Nucleus/FileSystem/setFileContentsInterface.h
/// @brief Function prototype for setting the contents of a file.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

#include <stdlib.h>
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_setFileContents.md
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(Nucleus_Size numberOfBytes)
    );
