// Copyright (c) Michael Heilmann 2018
#include "Nucleus/FileSystem/getDirectorySeparator.h"

#if defined(Nucleus_Platform_Windows)
    static const char directorySeparatorBytes[] = { '\\', '\0' };
#else
    static const char directorySeparatorBytes[] = { '/', '\0' };
#endif

static const Nucleus_Size directorySeparatorNumberOfBytes = sizeof(directorySeparatorBytes);

Nucleus_NonNull() Nucleus_Status
Nucleus_getDirectorySeparator
    (
        const char **bytes,
        Nucleus_Size *numberOfBytes
    )
{
    if (Nucleus_Unlikely(!bytes || !numberOfBytes)) return Nucleus_Status_InvalidArgument;
    *bytes = directorySeparatorBytes;
    *numberOfBytes = directorySeparatorNumberOfBytes;
    return Nucleus_Status_Success;
}
