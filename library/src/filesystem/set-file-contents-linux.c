/// @file filesystem/set-file-contents-windows.c
/// @brief Set the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(unix)

#include "filesystem/set-file-contents-linux.h"
#include "filesystem/file-handle-linux.h"

// For fprintf.
#include <stdio.h>

// For lseek.
#include <sys/types.h>
#include <unistd.h>

// For memcpy.
#include <string.h>

// For mmap.
#include <sys/mman.h>

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(size_t numberOfBytes)
    )
{
    Nucleus_Status status;
    Nucleus_FileHandle *fileHandle;
    if (!pathname || !bytes)
    {
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Create the file handle.
    status = Nucleus_FileHandle_create(&fileHandle, pathname, Nucleus_FileAccessMode_ReadWrite, Nucleus_ExistingFilePolicy_Truncate, Nucleus_NonExistingFilePolicy_Create);
    if (status)
    {
        // Return the result.
        return status;
    }
    // If the contents are empty, then we are done.
    if (0 == numberOfBytes)
    {
        // Destroy the file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_Success;
    }
    // Extend the file to the size of the contents if necessary.
    if (-1 == lseek(fileHandle->fileDescriptor, numberOfBytes - 1, SEEK_SET))
    {
        // Destroy the file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    if (-1 == write(fileHandle->fileDescriptor, "", 1))
    {
        // Destroy the file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Now the file is ready to be mmapped.
    char *mapping = mmap(0, numberOfBytes, PROT_READ | PROT_WRITE, MAP_SHARED, fileHandle->fileDescriptor, 0);
    if (mapping == MAP_FAILED)
    {
        // Destroy the file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Copy the contents into the mappping and write them to disk.
    memcpy(mapping, bytes, numberOfBytes);
    if (-1 == msync(mapping, numberOfBytes, MS_SYNC) == -1)
    {
        // Close the mapping.
        munmap(mapping, numberOfBytes);
        // Destroy the file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Close the mapping.
    munmap(mapping, numberOfBytes);
    // Destroy the file handle.
    Nucleus_FileHandle_destroy(fileHandle);
    fileHandle = NULL;
    // Return the result.
    return Nucleus_Status_Success;
}

#endif
