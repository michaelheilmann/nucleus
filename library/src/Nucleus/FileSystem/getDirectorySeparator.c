// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem/getDirectorySeparator.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    static const char directorySeparatorBytes[] = { '\\', '\0' };
#else
    static const char directorySeparatorBytes[] = { '/', '\0' };
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getDirectorySeparator
    (
        const char **directorySeparator
    )
{
    if (Nucleus_Unlikely(!directorySeparator)) return Nucleus_Status_InvalidArgument;
    *directorySeparator = directorySeparatorBytes;
    return Nucleus_Status_Success;
}
