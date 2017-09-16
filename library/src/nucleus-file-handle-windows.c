/// @file nucleus-file-handle-windows.c
/// @brief A file handle (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017


#if defined (_WIN32)

#include "nucleus-file-handle-windows.h"

#include <stdio.h>
#include <malloc.h>

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
	// Translate desired access and (non) existing file policies.
	DWORD dwDesiredAccess = 0;
	if (!(fileAccessMode & (Nucleus_FileAccessMode_ReadWrite)))
	{
		fprintf(stderr, "%s:%d: invalid argument\n", __FILE__, __LINE__);
		return Nucleus_Status_InvalidArgument;
	}
	if (fileAccessMode & Nucleus_FileAccessMode_Read)
	{
		dwDesiredAccess |= GENERIC_READ;
	}
	if (fileAccessMode & Nucleus_FileAccessMode_Write)
	{
		dwDesiredAccess |= GENERIC_WRITE;
	}
	DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
	DWORD dwCreationDisposition = 0;
	typedef struct PolicyMapping
	{
		Nucleus_ExistingFilePolicy existingFilePolicy;
		Nucleus_NonExistingFilePolicy nonExistingFilePolicy;
		DWORD dwCreationDisposition;
		DWORD dwDesiredAccessModifier;
	} PolicyMapping;
	static const PolicyMapping policyMappings[] =
	{
		// CREATE_NEW is a conditional flag which fails
		// if the file exists and succeeds if the file
		// does not exist and is successfully created.
		// It is not used.
		{ Nucleus_ExistingFilePolicy_Truncate,
		  Nucleus_NonExistingFilePolicy_Create,
		  CREATE_ALWAYS,
		  0 },
		{ Nucleus_ExistingFilePolicy_Retain,
		  Nucleus_NonExistingFilePolicy_Create,
		  OPEN_ALWAYS,
		  0 },
		{ Nucleus_ExistingFilePolicy_Truncate,
		  Nucleus_NonExistingFilePolicy_Fail,
		  TRUNCATE_EXISTING,
		  GENERIC_WRITE },
		{ Nucleus_ExistingFilePolicy_Retain,
		  Nucleus_NonExistingFilePolicy_Fail,
		  OPEN_EXISTING,
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
	dwDesiredAccess |= policyMapping->dwDesiredAccessModifier;
	Nucleus_FileHandle *temporaryFileHandle = malloc(sizeof(Nucleus_FileHandle));
	if (!temporaryFileHandle)
	{
		return Nucleus_Status_AllocationFailed;
	}
	temporaryFileHandle->hFileHandle = CreateFileA(pathname, dwDesiredAccess, dwShareMode, 0, policyMapping->dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, 0);
	if (INVALID_HANDLE_VALUE == temporaryFileHandle->hFileHandle)
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
	if (INVALID_HANDLE_VALUE != fileHandle->hFileHandle)
	{
		CloseHandle(fileHandle->hFileHandle);
		fileHandle->hFileHandle = INVALID_HANDLE_VALUE;
	}
	// Deallocate file handle.
	free(fileHandle);
}

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileHandle_getFileSize
	(
		Nucleus_FileHandle *fileHandle,
		size_t *fileSize
	)
{
	if (!fileHandle || !fileSize || INVALID_HANDLE_VALUE == fileHandle->hFileHandle)
	{
		return Nucleus_Status_InvalidArgument;
	}
	// Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
	DWORD temporaryFileSize = GetFileSize(fileHandle->hFileHandle, NULL);
	if (INVALID_FILE_SIZE == temporaryFileSize || temporaryFileSize > SIZE_MAX)
	{
		return Nucleus_Status_EnvironmentFailed;
	}
	*fileSize = temporaryFileSize;
	return Nucleus_Status_Success;
}

#endif
