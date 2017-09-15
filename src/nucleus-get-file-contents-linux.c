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

Nucleus_NonNull(1, 2, 3) Nucleus_Status
Nucleus_getFileContentsLinux
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_OutputParameter(char **bytes),
		Nucleus_OutputParameter(size_t *numberOfBytes)
{
    if (!pathname || !bytes || !numberOfBytes)
	{
        fprintf(stderr, "invalid arguments\n");
        return Nucleus_Status_InvalidArgument;
    }
    // Open the file for reading.
    int fileDescriptor = open(pathname, O_RDONLY);
	if (fileDescriptor < 0)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        return Nucleus_Status_EnvironmentFailed;
	}
	// Get the size of the file.
	size_t fileSize;
	Nucleus_Status status = Nucleus_getFileSizeLinux(fileDescriptor, &fileSize);
	// If the file size is 0, mmap will fail.
	// Hence a special treatment is required.
	if (0 == fileSize)
	{
		// Close the file.
		close(fileDescriptor);
		// Return an array of length 1 and return 0 Bytes read.
		char *bytes0 = malloc(1);
        if (!bytes0)
		{
            return Nucleus_Status_AllocationFailed;
        }
		*bytes = bytes0;
		*numberOfBytes = fileSize;
		return Nucleus_Status_Success;
	}
	// Open the mapping.
	char *mapping = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);
	if (MAP_FAILED == mapping)
	{
		// Close the file.
		close(fileDescriptor);
		// Return the result.
		return Nucleus_Status_EnvironmentFailed;
	}
	// Allocate the Bytes.
	char *bytes0 = malloc(fileSize);
	if (!bytes0)
	{
		// Destroy the mapping.
		munmap(mapping, fileSize);
		// Close the file.
		close(fileDescriptor);
		// Return the result.
		return Nucleus_Status_AllocationFailed;
	}
	memcpy(bytes0, mapping, fileSize);
	// Destroy the mapping.
	munmap(mapping, fileSize);
	// Close the file.
	close(fileDescriptor);
	// Return the result.
	*numberOfBytes = fileSize;
	*bytes = bytes0;
	// Return the result.
	return tagged_return_value;
}

#endif
