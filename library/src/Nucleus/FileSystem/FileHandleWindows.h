/// @file Nucleus/FileSystem/FileHandleWindows.h
/// @brief A file handle (Windows).
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"
#include "Nucleus/FileSystem/FileHandleInterface.h"

/// @ingroup filesystem
/// @internal
/// @brief Implementation of @a (Nucleus_FileHandle) for Windows.
struct Nucleus_FileHandle
{
    /// @brief The file handle.
    /// @default INVALID_FILE_HANDLE
    HANDLE hFileHandle;
};

#endif
