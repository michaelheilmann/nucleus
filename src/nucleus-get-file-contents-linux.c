/// @file nucleus-get-file-contents-linux.c
/// @author Michael Heilmann
/// @brief Get the contents of a file (Linux).

#if defined(__linux__)

#include "nucleus-get-file-contents-linux.h"

/// @internal
/// @brief Get the size of a file.
/// @param fileDescriptor a file descriptor
/// @param fileSize a pointer to a @a (size_t) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
static Nucleus_NonNull(1,2) Nucleus_Status
Nucleus_getFileSize
	(
		int fileDescriptor,
		size_t *fileSize
	)
{
	if (fileDescriptor < 0)
	{
        return Nucleus_Status_InvalidArgument;
	}
	// Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
	struct stat stat_buf;
	int status = fstat(file_descriptor, &temporary);
	if (status < 0 || temporary.st_size < 0 || temporary.st_size > SIZE_MAX)
	{
		return Nucleus_Status_EnvironmentFailed;
	}
	*fileSize = (size_t)temporary.st_size;
	return Nucleus_Status_Success;
}

/// @brief Helper to store the objects related to a file mapping.
typedef struct Nucleus_FileMapping
{
	char *bytes;
	size_t numberOfBytes;
	int fileDescriptor;
} Nucleus_FileMapping;

static const char DUMMY = 0;

static Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileMapping_initialize
	(
		Nucleus_FileMapping *fileMapping,
		const char *pathname
	)
{
	// Validate arguments.
    if (!pathname)
	{
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Open file for reading.
    fileMapping->fileDescriptor = open(pathname, O_RDONLY);
	if (fileMapping->fileDescriptor < 0)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        return Nucleus_Status_EnvironmentFailed;
	}
	// Get the size of the file.
	Nucleus_Status status = Nucleus_getFileSizeLinux(fileDescriptor, &fileMapping->fileSize);
	// If the file size is 0, use a dummy buffer. Reason is that mmap fails if file size is 0.
	if (0 == fileMapping->fileSize)
	{
		fileMapping->bytes = &DUMMY;
		return Nucleus_Status_Success;
	}
	// Open the mapping.
	char *mapping = mmap(NULL, fileMapping->fileSize, PROT_READ, MAP_PRIVATE, fileMapping->fileDescriptor, 0);
	if (MAP_FAILED == mapping)
	{
		fprintf(stderr, "unable to open file '%s'\n", pathname);
		// Close the file.
		close(fileMapping->fileDescriptor);
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
	if (fileMapping->bytes != DUMMY)
	{
		munmap(fileMapping->bytes, fileMapping->numberOfBytes);
	}
	// Close the file.
	close(fileMapping->fileDescriptor);
}

Nucleus_NonNull(1, 2, 3) Nucleus_Status
Nucleus_getFileContentsLinux
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_OutputParameter(char **bytes),
		Nucleus_OutputParameter(size_t *numberOfBytes)
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
	size_t temporaryNumberOfBytes = fileMapping->numberOfBytes;
	char *temporaryBytes = malloc(temporaryNumberOfBytes > 0 ? temporaryNumberOfBytes : 1);
	if (!temporaryBytes)
	{
		// Close file mapping.
		Nucleus_FileMapping_uninitialize(&fileMapping);
		// Return the result.
		return Nucleus_Status_AllocationFailed;
	}
	// Copy from source bytes to target bytes.
	memcpy(temporaryBytes, fileMapping->bytes, temporaryNumberOfBytes);
	// Close file mapping.
	Nucleus_FileMapping_uninitialize(&fileMapping);
	// Return the result.
	*numberOfBytes = temporaryNumberOfBytes;
	*bytes = temporaryBytes;
	return Spine_Status_Success;
}

typedef
Nucleus_NonNull(1,2,3) Nucleus_Status
Nucleus_getFileContentsExtendedLinux
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
	status = (*callback)(object, fileMapping->bytes, fileMapping->numberOfBytes);
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
	return Spine_Status_Success;
}

#endif
