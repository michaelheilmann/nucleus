/// @file Nucleus/FileSystem/FileHandleLinux.h
/// @brief A file handle (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)

#include "Nucleus/FileSystem/FileHandleInterface.h"

/// @ingroup filesystem
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
