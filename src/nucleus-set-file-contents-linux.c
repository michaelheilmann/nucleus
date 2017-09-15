/// @file nucleus-set-file-contents-windows.c
/// @brief Set the contents of a file (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(__linux__)

#include "nucleus-set-file-contents-linux.h"

Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_setFileContentsLinux
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
	// Return false by default.
	wb_tagged_union tagged_return_value;
	wb_tagged_union_set_boolean(&tagged_return_value, WB_FALSE);
	int file_descriptor;
	wb_integer file_size;
    // Open the file for writing.
    int fileDescriptor = open(file_name_c->bytes, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (fileDescriptor < 0)
	{
        fprintf(stderr, "unable to open file '%s'\n", pathname);
        return Nucleus_Status_EnvironmentFailed;
	}
	// If the contents are empty, then we are done.
	if (0 == numberOfBytes)
	{
		// Close the file.
		close(fileDescriptor);
		// Return the result.
		return Nucleus_Status_Success;
	}
	// Extend the file to the size of the contents if necessary.
    if (-1 == lseek(fileDescriptor, numberOfBytes - 1, SEEK_SET))
    {
		// Close the file.
        close(fileDescriptor);
		// Return the result.
		return Nucleus_Status_EnvironmentFailed;
	}
    if (-1 == write(fileDescriptor, "", 1))
    {
		// Close the file.
        close(fileDescriptor);
		// Return the result.
		return Nucleus_Status_EnvironmentFailed;
	}
    // Now the file is ready to be mmapped.
    char *mapping = mmap(0, numberOfBytes, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
    if (mapping == MAP_FAILED)
    {
		// Close the file.
        close(fileDescriptor);
		// Return the result.
		return Spine_Status_EnvironmentFailed;
	}
	// Copy the contents into the mappping and write them to disk.
	memcpy(mapping, numberOfBytes, numberOfBytes);
    if (-1 == msync(mapping, numberOfBytes, MS_SYNC) == -1)
    {
		// Close the mapping.
		munmap(mapping, numberOfBytes);
		// Close the file.
        close(fileDescriptor);
		// Return the result.
		return Spine_Status_EnvironmentFailed;
	}
	// Close the mapping.
	munmap(mapping, numberOfBytes);
	// Close the file.
    close(fileDescriptor);
	// Return the result.
	return Spine_Status_Success;
}

#endif
