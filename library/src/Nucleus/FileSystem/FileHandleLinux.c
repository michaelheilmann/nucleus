/// @file Nucleus/FileSystem/FileHandleLinux.c
/// @brief A file handle (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(unix)

#include "Nucleus/FileSystem/FileHandleLinux.h"

// For fprintf.
#include <stdio.h>

// For malloc.
#include <malloc.h>

// For open.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// For close.
#include <unistd.h>

// For SIZE_MAX.
#include <stdint.h>

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileHandle_create
(
    Nucleus_FileHandle **fileHandle,
    const char *pathname,
    Nucleus_FileAccessMode fileAccessMode,
    Nucleus_ExistingFilePolicy existingFilePolicy,
    Nucleus_NonExistingFilePolicy nonExistingFilePolicy
)
{
    // Validate arguments.
    if (!fileHandle || !pathname)
    {
        fprintf(stderr, "%s:%d: invalid argument\n", __FILE__, __LINE__);
        return Nucleus_Status_InvalidArgument;
    }    
    // Translate file access and policies for existing and non-existing files.
    int flags = 0;
    if (Nucleus_FileAccessMode_ReadWrite == (fileAccessMode & (Nucleus_FileAccessMode_ReadWrite)))
    {
        flags |= O_RDWR;
    }
    else if (fileAccessMode & Nucleus_FileAccessMode_Read)
    {
        flags |= O_RDONLY;
    }
    else if (fileAccessMode & Nucleus_FileAccessMode_Write)
    {
        flags |= O_WRONLY;
    }
    else
    {
        fprintf(stderr, "%s:%d: invalid argument\n", __FILE__, __LINE__);
        return Nucleus_Status_InvalidArgument;
    }
    typedef struct PolicyMapping
    {
        Nucleus_ExistingFilePolicy existingFilePolicy;
        Nucleus_NonExistingFilePolicy nonExistingFilePolicy;
        int flagsModifier;
    } PolicyMapping;
    static const PolicyMapping policyMappings[] =
    {
        { Nucleus_ExistingFilePolicy_Truncate,
          Nucleus_NonExistingFilePolicy_Create,
          O_CREAT | O_TRUNC },
        { Nucleus_ExistingFilePolicy_Retain,
          Nucleus_NonExistingFilePolicy_Create,
          O_CREAT },
        { Nucleus_ExistingFilePolicy_Truncate,
          Nucleus_NonExistingFilePolicy_Fail,
          O_TRUNC },
        { Nucleus_ExistingFilePolicy_Retain,
          Nucleus_NonExistingFilePolicy_Fail,
          0 },
        };
    const PolicyMapping *policyMapping = NULL;
    for (size_t i = 0, n = sizeof(policyMappings) / sizeof(PolicyMapping); i < n; ++i)
    {
        policyMapping = policyMappings + i;
        if (policyMapping->existingFilePolicy == existingFilePolicy &&
            policyMapping->nonExistingFilePolicy == nonExistingFilePolicy)
        {
            break;
        }
    }
    if (policyMapping == NULL)
    {
        fprintf(stderr, "%s:%d: invalid argument\n", __FILE__, __LINE__);
        return Nucleus_Status_InvalidArgument;
    }
    flags |= policyMapping->flagsModifier;
    Nucleus_FileHandle *temporaryFileHandle = malloc(sizeof(Nucleus_FileHandle));
    if (!temporaryFileHandle)
    {
        return Nucleus_Status_AllocationFailed;
    }
    if (nonExistingFilePolicy == Nucleus_NonExistingFilePolicy_Create)
    {
        temporaryFileHandle->fileDescriptor = open(pathname, flags, S_IRWXU);
    }
    else
    {
        temporaryFileHandle->fileDescriptor = open(pathname, flags);
    }
    if (temporaryFileHandle->fileDescriptor < 0)
    {
        free(temporaryFileHandle);
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    *fileHandle = temporaryFileHandle;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) void
Nucleus_FileHandle_destroy
    (
        Nucleus_FileHandle *fileHandle
    )
{
    // Close file handle.
    if (fileHandle->fileDescriptor > 0)
    {
        close(fileHandle->fileDescriptor);
        fileHandle->fileDescriptor = -1;
    }
    // Deallocate file handle.
    free(fileHandle);
}

Nucleus_NonNull(1,2) Nucleus_Status
Nucleus_FileHandle_getFileSize
    (
        Nucleus_FileHandle *fileHandle,
        size_t *fileSize
    )
{
    if (!fileHandle || !fileSize || fileHandle->fileDescriptor < 0)
    {
        return Nucleus_Status_InvalidArgument;
    }
    // Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
    struct stat stat_buf;
    int status = fstat(fileHandle->fileDescriptor, &stat_buf);
    if (status < 0 || stat_buf.st_size < 0 || stat_buf.st_size > SIZE_MAX)
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    *fileSize = (size_t)stat_buf.st_size;
    return Nucleus_Status_Success;
}

#endif
