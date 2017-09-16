/// @file nucleus-file-handle-linux.h
/// @brief A file handle (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(unix)

#pragma once

#include "nucleus-file-handle.h"

/// @internal
/// @brief Implementation of @a (Nucleus_FileHandle) for Windows.
typedef struct Nucleus_FileHandle_Linux Nucleus_FileHandle_Linux;
struct Nucleus_FileHandle_Linux
{
	/// @brief The file handle.
	/// @default @a -1
	int fileDescriptor;
};

#endif
