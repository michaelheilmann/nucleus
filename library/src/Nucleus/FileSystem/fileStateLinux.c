// Copyright (c) Michael Heilmann 2018
#include "Nucleus/FileSystem/fileStateLinux.h"

#if defined(Nucleus_Platform_Linux)

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getFileState
    (
        const char *pathname,
        Nucleus_FileState *fileState
    )
{
    if (Nucleus_Unlikely(!pathname || !fileState))
    { return Nucleus_Status_InvalidArgument; }

    struct stat t;
    int result = stat(pathname, &t);
    if (0 == result)
    {
        if (0 != S_ISDIR(t.st_mode))
            *fileState = Nucleus_FileState_IsDirectory;
        else if (0 != S_ISREG(t.st_mode))
            *fileState = Nucleus_FileState_IsRegular;
        else
            *fileState = Nucleus_FileState_Unknown;
    }
    else
    {
        if (errno == ENOTDIR || errno == ENOENT || errno == ENAMETOOLONG || errno == EACCES)
            // ENOTDIR, ENOENT, ENAMETOOLONG, and EACCES all imply that the file does not exist or is not accessible due to permission constraints
            *fileState = Nucleus_FileState_NotFound;
        else if (errno == EOVERFLOW) // EOVERFLOW indicates that some file exists but is not accessible due to technical constraints
            *fileState = Nucleus_FileState_Unknown;
        else /*if (errno == ELOOP || errno == ENOMEN || errno == EFAULT || errno == EBADF)*/
            return Nucleus_Status_EnvironmentFailed;
    }
    return Nucleus_Status_Success;
}

#endif
