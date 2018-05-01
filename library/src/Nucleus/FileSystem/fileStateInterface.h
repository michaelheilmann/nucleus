#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

typedef enum Nucleus_FileState
{
    Nucleus_FileState_IsDirectory,
    Nucleus_FileState_IsRegular,
    Nucleus_FileState_NotFound,
    Nucleus_FileState_Unknown,
} Nucleus_FileState;

Nucleus_NonNull() Nucleus_Status
Nucleus_getFileState
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_OutputParameter(Nucleus_FileState *fileState)
    );
