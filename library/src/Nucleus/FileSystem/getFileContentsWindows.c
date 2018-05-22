/// @file Nucleus/FileSystem/getFileContentsWindows.c
/// @author Michael Heilmann
/// @brief Get the contents of a file (Windows).

#include "Nucleus/FileSystem/getFileContentsWindows.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"
#include "Nucleus/FileSystem/FileHandleWindows.h"

// For fprintf.
#include <stdio.h>

/// @ingroup filesystem
/// @internal
/// @brief Get the size of a file.
/// @param fileDescriptor a file descriptor
/// @param fileSize a pointer to a @a (size_t) variable
/// @defaultReturn
static Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_getFileSize
    (
        HANDLE hFile,
        size_t *fileSize
    )
{
    if (INVALID_HANDLE_VALUE == hFile)
    {
        return Nucleus_Status_InvalidArgument;
    }
    // Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
    DWORD temporaryFileSize = GetFileSize(hFile, NULL);
    if (INVALID_FILE_SIZE == temporaryFileSize || temporaryFileSize > SIZE_MAX)
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    *fileSize = temporaryFileSize;
    return Nucleus_Status_Success;
}

/// @ingroup filesystem
/// @brief Helper to store the objects related to a file mapping.
typedef struct Nucleus_FileMapping Nucleus_FileMapping;
struct Nucleus_FileMapping
{
    Nucleus_FileHandle *fileHandle;
    HANDLE hFileMapping;
    char *bytes;
    size_t numberOfBytes;
}; // struct Nucleus_FileMapping

static const char DUMMY = 0;

static Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileMapping_initialize
    (
        Nucleus_FileMapping *fileMapping,
        const char *pathname
    )
{
    if (!pathname)
    {
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Initialize members that might not be initialized later on with safe defaults.
    fileMapping->hFileMapping = NULL;
    fileMapping->fileHandle = NULL;
    Nucleus_Status status;
    
    // Open the file handle.
    status = Nucleus_FileHandle_create(&fileMapping->fileHandle,
                                       pathname,
                                       Nucleus_FileAccessMode_Read,
                                       Nucleus_ExistingFilePolicy_Retain,
                                       Nucleus_NonExistingFilePolicy_Fail);
    if (status)
    {
        return status;
    }
    // Determine file size.
    status = Nucleus_FileHandle_getFileSize(fileMapping->fileHandle, &fileMapping->numberOfBytes);
    if (status)
    {
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
        // Return the result.
        return status;
    }
    // If the file is empty, use a dummy buffer.
    if (0 == fileMapping->numberOfBytes)
    {
        // Use a dummy buffer.
        fileMapping->bytes = (char *)&DUMMY;
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_Success;
    }
    // Create file mapping.
    fileMapping->hFileMapping = CreateFileMapping(fileMapping->fileHandle->hFileHandle, 0, PAGE_READONLY, 0, 0, 0);
    if (NULL == fileMapping->hFileMapping)
    {
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Create view of file mapping.
    fileMapping->bytes = (char *)MapViewOfFile(fileMapping->hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (NULL == fileMapping->bytes)
    {
        fprintf(stderr, "unable to create view of file '%s'\n", pathname);
        // Close file mapping.
        CloseHandle(fileMapping->hFileMapping);
        fileMapping->hFileMapping = NULL;
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
        // Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Return the result.
    return Nucleus_Status_Success;
}

static Nucleus_NonNull(1) void
Nucleus_FileMapping_uninitialize
    (
        Nucleus_FileMapping *fileMapping
    )
{
    // Close view of file.
    if (&DUMMY != fileMapping->bytes)
    {
        UnmapViewOfFile(fileMapping->bytes);
        fileMapping->bytes = NULL;
    }
    // Close file mapping.
    if (NULL != fileMapping->hFileMapping)
    {
        CloseHandle(fileMapping->hFileMapping);
        fileMapping->hFileMapping = NULL;
    }
    // Close file.
    if (fileMapping->fileHandle)
    {
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
    }
}

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_getFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_OutputParameter(char **bytes),
        Nucleus_OutputParameter(size_t *numberOfBytes)
    )
{
    // Validate arguments.
    if (!bytes || !numberOfBytes)
    {
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Open the file mapping.
    Nucleus_FileMapping fileMapping;
    Nucleus_Status status = Nucleus_FileMapping_initialize(&fileMapping, pathname);
    if (status)
    {
        return status;
    }
    // Allocate target bytes.
    size_t temporaryNumberOfBytes = fileMapping.numberOfBytes;
    char *temporaryBytes = malloc(temporaryNumberOfBytes > 0 ? temporaryNumberOfBytes : 1);
    if (!temporaryBytes)
    {
        fprintf(stderr, "unable to allocate memory for contents of file '%s'\n", pathname);
        // Close file mapping.
        Nucleus_FileMapping_uninitialize(&fileMapping);
        // Return the result.
        return Nucleus_Status_AllocationFailed;
    }
    // Copy from source bytes to target bytes.
    memcpy(temporaryBytes, fileMapping.bytes, temporaryNumberOfBytes);
    // Close file mapping.
    Nucleus_FileMapping_uninitialize(&fileMapping);
    // Return the result.
    *numberOfBytes = temporaryNumberOfBytes;
    *bytes = temporaryBytes;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1, 3) Nucleus_Status
Nucleus_getFileContentsExtended
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputOutputParameter(void *object),
        Nucleus_InputOutputParameter(Nucleus_getFileContentsExtendedCallbackFunction *callback)
    )
{
    // Validate arguments.
    if (!callback)
    {
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Open the file mapping.
    Nucleus_FileMapping fileMapping;
    Nucleus_Status status = Nucleus_FileMapping_initialize(&fileMapping, pathname);
    if (status)
    {
        return status;
    }
    // Invoke callback.
    status = (*callback)(object, fileMapping.bytes, fileMapping.numberOfBytes);
    if (status)
    {
        // Close file mapping.
        Nucleus_FileMapping_uninitialize(&fileMapping);
        // Return the result.
        return status;
    }
    // Close file mapping.
    Nucleus_FileMapping_uninitialize(&fileMapping);
    // Return the result.
    return Nucleus_Status_Success;
}

#endif
