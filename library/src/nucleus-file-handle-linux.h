/// @file nucleus-file-handle-linux.h
/// @brief A file handle (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(unix)

#pragma once

#include "nucleus-file-handle.h"

/// @internal
/// @brief Implementation of @a (Nucleus_FileHandle) for Linux.
typedef struct Nucleus_FileHandle Nucleus_FileHandle;
struct Nucleus_FileHandle
{
	/// @brief The file handle.
	/// @default @a -1
	int fileDescriptor;
};

#endif
