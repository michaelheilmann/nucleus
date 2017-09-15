/// @file nucleus-get-file-contents.h
/// @brief Function prototype for getting the contents of a file.
/// @author Michael Heilmann

#pragma once

#include "nucleus.h"
#include "nucleus-status.h"
#include "nucleus-annotations.h"

/// @brief The type of a Nucleus_getFileContents function.
/// @detail Get the contents of a file.
/// @param pathname a pointer to the pathname of the file
/// @param bytes a pointer to a @a (char *) variable
/// @param numberOfBytes a pointer to a @a (size_t) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post 
/// - On success: @a *numberOfBytes was assigned the size of the file which may be @a 0.
/// @a *bytes was assigned a pointer to an array of at least @a *numberOfBytes Bytes such that the first @a *numberOfBytes
/// represent the content of the file. That array must be deallocated using free if no longer required.
/// - On failure: Neither @a *numberOfBytes nor @a *bytes were dereferened.
typedef
Nucleus_NonNull(1,2,3) Nucleus_Status
Nucleus_getFileContentsFunction
	(
		Nucleus_InputParameter(const char *pathname),
		Nucleus_OutputParameter(char **bytes),
		Nucleus_OutputParameter(size_t *numberOfBytes)
	);
