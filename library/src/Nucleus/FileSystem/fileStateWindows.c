// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem/fileStateWindows.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getFileState
    (
        const char *pathname,
        Nucleus_FileState *fileState
    )
{
    if (Nucleus_Unlikely(!pathname || !fileState))
    { return Nucleus_Status_InvalidArgument; }

    DWORD t = GetFileAttributesA(pathname);
    if (t == INVALID_FILE_ATTRIBUTES)
    {
        // error or not found
        t = GetLastError();
        SetLastError(0);
        if (t == ERROR_FILE_NOT_FOUND    ||
            t == ERROR_PATH_NOT_FOUND    ||
            t == ERROR_INVALID_NAME      ||
            t == ERROR_INVALID_DRIVE     ||
            t == ERROR_NOT_READY         ||
            t == ERROR_INVALID_PARAMETER ||
            t == ERROR_BAD_PATHNAME      ||
            t == ERROR_BAD_NETPATH)
        {
            *fileState = Nucleus_FileState_NotFound;
            return Nucleus_Status_Success;
        }
        else
        {
            return Nucleus_Status_EnvironmentFailed;
        }
    }
    if (FILE_ATTRIBUTE_DIRECTORY == (FILE_ATTRIBUTE_DIRECTORY & t))
    {
        *fileState = Nucleus_FileState_IsDirectory;
        return Nucleus_Status_Success;
    }
    else
    {
        *fileState = Nucleus_FileState_IsRegular;
        return Nucleus_Status_Success;
    }
}

#endif
