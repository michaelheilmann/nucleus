/// @file nucleus-file-handle-linux.h
/// @brief A file handle (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(unix)

#pragma once

#include "nucleus-includes-windows.h"
#include "nucleus-annotations.h"
#include "nucleus-status.h"
#include "nucleus-non-existing-file-policy.h"
#include "nucleus-existing-file-policy.h"
#include "nucleus-file-access-mode.h"

#include <stdlib.h>

/// @internal
/// @brief A file handle.
typedef struct Nucleus_FileHandle Nucleus_FileHandle;
struct Nucleus_FileHandle
{
	/// @brief The file handle.
	/// @default @a -1
	int fileDescriptor;
};

/// @internal
/// @brief Create a file handle.
/// @param [out] fileHandle a pointer to a @a (Nucleus_FileHandle *) variable
/// @param pathname a pointer to the pathname of the file
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileHandle_create
	(
		Nucleus_FileHandle **fileHandle,
		const char *pathname,
		Nucleus_FileAccessMode fileAccessMode,
		Nucleus_ExistingFilePolicy existingFilePolicy,
		Nucleus_NonExistingFilePolicy nonExistingFilePolicy
	);

/// @internal
/// @brief Destroy a file handle.
/// @param fileHandle a pointer to the file handle
Nucleus_NonNull(1) void
Nucleus_FileHandle_destroy
	(
		Nucleus_FileHandle *fileHandle
	);
	
/// @internal
/// @brief Get the size of a file.
/// @param fileDescriptor a file descriptor
/// @param fileSize a pointer to a @a (size_t) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_NonNull(1,2) Nucleus_Status
Nucleus_FileHandle_getFileSize
	(
		Nucleus_FileHandle *fileHandle,
		size_t *fileSize
	);

#endif
