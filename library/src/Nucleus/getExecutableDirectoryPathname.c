// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getExecutableDirectoryPathname.h"

#include "Nucleus/Configuration.h"
#include "Nucleus/Memory.h"
#include "Nucleus/getExecutablePathname.h"
#include "Nucleus/FileSystem/getDirectorySeparator.h"
#include "Nucleus/C/strrstr.h"
#include <string.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutableDirectoryPathname
    (
        char **executableDirectoryPathname
    )
{
    // (1) Validate arguments.
    if (Nucleus_Unlikely(!executableDirectoryPathname))
    {
        return Nucleus_Status_InvalidArgument;
    }
    Nucleus_Status status;
    // (2) Get executable pathname.
    char *temporary;
    status = Nucleus_getExecutablePathname(&temporary);
    if (Nucleus_Unlikely(status)) return status;
    // (3) Remove everything from (inclusive) the last directory separator.
    const char *directorySeparator;
    status = Nucleus_getDirectorySeparator(&directorySeparator);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(temporary);
        return status;
    }
    char *p = strrstr(temporary, directorySeparator);
    if (Nucleus_Unlikely(!p))
    {
        Nucleus_deallocateMemory(temporary);
        return Nucleus_Status_InternalError;
    }
    p++;
    *p = '\0';
    Nucleus_Size l = strlen(temporary);
    // (4) Shrink the buffer.
    status = Nucleus_reallocateArrayMemory((void **)&temporary, l + 1, sizeof(char));
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(temporary);
        return status;
    }
    // (5) Return result.
    *executableDirectoryPathname = temporary;
    // (6) Return success.
    return Nucleus_Status_Success;
}
