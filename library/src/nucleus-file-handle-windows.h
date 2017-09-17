/// @file nucleus-file-handle-windows.h
/// @brief A file handle (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined (_WIN32)

#pragma once

#include "nucleus-includes-windows.h"
#include "nucleus-file-handle-interface.h"

/// @internal
/// @brief Implementation of @a (Nucleus_FileHandle) for Windows.
struct Nucleus_FileHandle
{
	/// @brief The file handle.
	/// @default INVALID_FILE_HANDLE
	HANDLE hFileHandle;
};

#endif
