/// @file filesystem/get-file-contents-linux.c
/// @author Michael Heilmann
/// @brief Get the contents of a file (Linux).

#if defined(unix)

#include "Nucleus/FileSystem/getFileContentsLinux.h"
#include "Nucleus/FileSystem/FileHandleLinux.h"

// For fprintf.
#include <stdio.h>

// For memcpy.
#include <string.h>

// For mmap.
#include <sys/mman.h>

/// @brief Helper to store the objects related to a file mapping.
typedef struct Nucleus_FileMapping
{
    char *bytes;
    size_t numberOfBytes;
    Nucleus_FileHandle *fileHandle;
} Nucleus_FileMapping;

static const char DUMMY = 0;

static Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileMapping_initialize
    (
        Nucleus_FileMapping *fileMapping,
        const char *pathname
    )
{
    Nucleus_Status status;
    
    // Open the file handle.
    status = Nucleus_FileHandle_create(&fileMapping->fileHandle,
                                       pathname,
                                       Nucleus_FileAccessMode_Read,
                                       Nucleus_ExistingFilePolicy_Retain,
                                       Nucleus_NonExistingFilePolicy_Fail);
    if (status)
    {
        // Return the result.
        return status;
    }
    // Get the size of the file.
    status = Nucleus_FileHandle_getFileSize(fileMapping->fileHandle, &fileMapping->numberOfBytes);
    if (status)
    {
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
        // Return the result.
        return status;
    }
    // If the file size is 0, use a dummy buffer. Reason is that mmap fails if file size is 0.
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
    // Open the mapping.
    fileMapping->bytes = mmap(NULL, fileMapping->numberOfBytes, PROT_READ, MAP_PRIVATE, fileMapping->fileHandle->fileDescriptor, 0);
    if (MAP_FAILED == fileMapping->bytes)
    {
        fprintf(stderr, "unable to open file '%s'\n", pathname);
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
    // Close the mapping.
    if (&DUMMY != fileMapping->bytes)
    {
        munmap(fileMapping->bytes, fileMapping->numberOfBytes);
    }
    if (fileMapping->fileHandle)
    {
        // Close file handle.
        Nucleus_FileHandle_destroy(fileMapping->fileHandle);
        fileMapping->fileHandle = NULL;
    }
}

Nucleus_NonNull(1, 2, 3) Nucleus_Status
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
    // Open file mapping.
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
    // Return the result.
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1,2,3) Nucleus_Status
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
    // Open file mapping.
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
