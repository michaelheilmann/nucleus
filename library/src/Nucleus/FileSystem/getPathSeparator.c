// Copyright (c) Michael Heilmann 2018
#include "Nucleus/FileSystem/getDirectorySeparator.h"

static const char pathSeparatorBytes[] = { ';', '\0' };

static const Nucleus_Size pathSeparatorNumberOfBytes = sizeof(pathSeparatorBytes);

Nucleus_NonNull() Nucleus_Status
Nucleus_getPathSeparator
    (
        const char **bytes,
        Nucleus_Size *numberOfBytes
    )
{
    if (Nucleus_Unlikely(!bytes || !numberOfBytes)) return Nucleus_Status_InvalidArgument;
    *bytes = pathSeparatorBytes;
    *numberOfBytes = pathSeparatorNumberOfBytes;
    return Nucleus_Status_Success;
}
