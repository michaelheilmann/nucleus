/// @file nucleus-get-file-contents-windows.c
/// @author Michael Heilmann
/// @brief Get the contents of a file (Windows/WinAPI/file mappings).

#if defined(_WIN32)

#include "nucleus-get-file-contents-windows.h"

#if defined(_WIN32)
#include <Windows.h>
#else
#error("_WIN32 not defined")
#endif

#include <stdio.h>

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_getFileContentsWindows
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_OutputParameter(char **bytes),
        Nucleus_OutputParameter(size_t *numberOfBytes)
    )
{
    if (!pathname || !bytes || !numberOfBytes)
	{
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Open file.
    HANDLE hFile = CreateFileA(pathname, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        return Nucleus_Status_EnvironmentFailed;
    }
    // Determine file size.
    DWORD fileSize = GetFileSize(hFile, 0);
    if (0 == fileSize)
	{
        // Close file.
        CloseHandle(hFile);
        hFile = NULL;
        // The file is empty.
        char *outBytes = malloc(1);
        if (!outBytes)
		{
            return Nucleus_Status_AllocationFailed;
        }
        size_t outSize = fileSize;
        *numberOfBytes = outSize;
        *bytes = outBytes;
        return Nucleus_Status_Success;
    }

    // Create file mapping.
    HANDLE hFileMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
    if (NULL == hFileMapping)
	{
        fprintf(stderr, "unable to create file mapping of file '%s'\n", pathname);
        // Close file.
        CloseHandle(hFile);
        hFile = NULL;
        return Nucleus_Status_EnvironmentFailed;
    }
    // Create view of file mapping.
    const char* pData = (const char*)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (!pData)
	{
        fprintf(stderr, "unable to create view of file '%s'\n", pathname);
        // Close file mapping.
        CloseHandle(hFileMapping);
        hFileMapping = NULL;
        // Close file.
        CloseHandle(hFile);
        hFile = NULL;
        return Nucleus_Status_EnvironmentFailed;
    }

    char *outBytes = malloc(fileSize > 0 ? fileSize : 1);
    if (!outBytes)
	{
        fprintf(stderr, "unable to allocate memory for contents of file '%s'\n", pathname);
        // Destroy view of file.
        UnmapViewOfFile(pData);
        pData = NULL;
        // Close file mapping.
        CloseHandle(hFileMapping);
        hFileMapping = NULL;
        // Close file.
        CloseHandle(hFile);
        hFile = NULL;
        return Nucleus_Status_AllocationFailed;
    }
    memcpy(outBytes, pData, fileSize);
    size_t outSize = fileSize;
    *numberOfBytes = outSize;
    *bytes = outBytes;

    // Destroy view of file.
    UnmapViewOfFile(pData);
    pData = NULL;
    // Close file mapping.
    CloseHandle(hFileMapping);
    hFileMapping = NULL;
    // Close file.
    CloseHandle(hFile);
    hFile = NULL;
    return Nucleus_Status_Success;
}

#endif
