/// @file nucleus-get-file-contents-windows.c
/// @author Michael Heilmann
/// @brief Get the contents of a file (Windows).

#if defined(_WIN32)

#include "nucleus-get-file-contents-windows.h"

#if defined(_WIN32)
#include <Windows.h>
#else
#error("_WIN32 not defined")
#endif

#include <stdio.h>

/// @internal
/// @brief Get the size of a file.
/// @param fileDescriptor a file descriptor
/// @param fileSize a pointer to a @a (size_t) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
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

/// @brief Helper to store the objects related to a file mapping.
typedef struct Nucleus_FileMapping Nucleus_FileMapping;
struct Nucleus_FileMapping
{
	HANDLE hFile;
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
    // Open file.
	fileMapping->hFile = CreateFileA(pathname, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (INVALID_HANDLE_VALUE == fileMapping->hFile)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
		// Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Determine file size.
	Nucleus_Status status = Nucleus_getFileSize(fileMapping->hFile, &fileMapping->numberOfBytes);
	if (status)
	{
		fprintf(stderr, "unable to open file '%s'\n", pathname);
		// Return the result.
		return status;
	}
	// If the file is empty, use a dummy buffer.
	if (0 == fileMapping->numberOfBytes)
	{
		fileMapping->bytes = &DUMMY;
		// Return the result.
        return Nucleus_Status_Success;
    }
    // Create file mapping.
    fileMapping->hFileMapping = CreateFileMapping(fileMapping->hFile, 0, PAGE_READONLY, 0, 0, 0);
    if (NULL == fileMapping->hFileMapping)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        // Close file.
        CloseHandle(fileMapping->hFile);
        fileMapping->hFile = NULL;
		// Return the result.
        return Nucleus_Status_EnvironmentFailed;
    }
    // Create view of file mapping.
	fileMapping->bytes = (const char*)MapViewOfFile(fileMapping->hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (NULL == fileMapping->bytes)
	{
        fprintf(stderr, "unable to create view of file '%s'\n", pathname);
        // Close file mapping.
        CloseHandle(fileMapping->hFileMapping);
        fileMapping->hFileMapping = NULL;
        // Close file.
        CloseHandle(fileMapping->hFile);
        fileMapping->hFile = NULL;
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
    UnmapViewOfFile(fileMapping->bytes);
    fileMapping->bytes = NULL;
    // Close file mapping.
    CloseHandle(fileMapping->hFileMapping);
    fileMapping->hFileMapping = NULL;
    // Close file.
    CloseHandle(fileMapping->hFile);
    fileMapping->hFile = NULL;
}

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_getFileContentsWindows
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

Nucleus_NonNull(1,2,3) Nucleus_Status
Nucleus_getFileContentsExtendedWindows
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
