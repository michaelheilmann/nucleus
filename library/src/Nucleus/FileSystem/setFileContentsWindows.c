/// @file Nucleus/FileSystem/setFileContentsWindows.c
/// @brief Set the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#include "Nucleus/FileSystem/setFileContentsWindows.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/IncludesWindows.h"
#include "Nucleus/FileSystem/FileHandleWindows.h"

// For fprintf.
#include <stdio.h>

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(size_t numberOfBytes)
    )
{
    if (!pathname || !bytes)
    {
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    Nucleus_FileHandle *fileHandle;
    Nucleus_Status status;
    // Create file descriptor.
    // Windows memory mapping require read access as well.
    status = Nucleus_FileHandle_create(&fileHandle, pathname, Nucleus_FileAccessMode_ReadWrite,
                                       Nucleus_ExistingFilePolicy_Truncate, Nucleus_NonExistingFilePolicy_Create);
    if (status)
    {
        // Return the result.
        return status;
    }
    // If the size is zero, this function succeeded.
    if (numberOfBytes == 0)
    {
        // Destroy file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_Success;
    }
    // Create file mapping.
    HANDLE hFileMapping = CreateFileMapping(fileHandle->hFileHandle, 0, PAGE_READWRITE, 0, numberOfBytes, NULL);
    if (NULL == hFileMapping)
    {
        fprintf(stderr, "unable to create file mapping of file '%s'\n", pathname);
        // Destroy file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Create view of file mapping.
    char *pData = (char *)MapViewOfFile(hFileMapping, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, 0);
    if (!pData)
    {
        fprintf(stderr, "unable to create view of file '%s'\n", pathname);
        // Close file mapping.
        CloseHandle(hFileMapping);
        hFileMapping = NULL;
        // Destroy file handle.
        Nucleus_FileHandle_destroy(fileHandle);
        fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }

    // Write the Bytes.
    memcpy(pData, bytes, numberOfBytes);

    // Destroy view of file.
    UnmapViewOfFile(pData);
    pData = NULL;
    // Close file mapping.
    CloseHandle(hFileMapping);
    hFileMapping = NULL;
    // Destroy file handle.
    Nucleus_FileHandle_destroy(fileHandle);
    fileHandle = NULL;
    // Return the result.
    return Nucleus_Status_Success;
}

#endif
