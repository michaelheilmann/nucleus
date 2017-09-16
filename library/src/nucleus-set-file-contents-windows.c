/// @file nucleus-set-file-contents-windows.c
/// @brief Set the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(_WIN32)

#include "nucleus-set-file-contents-windows.h"
#include "nucleus-includes-windows.h"
#include "nucleus-file-handle-windows.h"

// For fprintf.
#include <stdio.h>

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContentsWindows
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
#if 0
	// Open file.
    HANDLE hFile = CreateFileA(pathname, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        return Nucleus_Status_EnvironmentFailed;
    }
#endif
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
