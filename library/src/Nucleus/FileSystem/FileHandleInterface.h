/// @file Nucleus/FileSystem/FileHandle.h
/// @brief A file handle.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/FileSystem/NonExistingFilePolicy.h"
#include "Nucleus/FileSystem/ExistingFilePolicy.h"
#include "Nucleus/FileSystem/FileAccessMode.h"
#include "Nucleus/Types/Size.h"

/// @ingroup filesystem
/// @brief The opaque type of a file handle.
typedef struct Nucleus_FileHandle Nucleus_FileHandle;

/// @ingroup filesystem
/// @brief Create a file handle.
/// @param [out] fileHandle a pointer to a @a (Nucleus_FileHandle *) variable
/// @param pathname a pointer to the pathname of the file
/// @success @a (*fileHandle) was assigned a pointer to the created @a (Nucleus_FileHandle) object.
/// @failure @a (*fileHandle) was not dereferenced.
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileHandle_create
    (
        Nucleus_FileHandle **fileHandle,
        const char *pathname,
        Nucleus_FileAccessMode fileAccessMode,
        Nucleus_ExistingFilePolicy existingFilePolicy,
        Nucleus_NonExistingFilePolicy nonExistingFilePolicy
    );

/// @ingroup filesystem
/// @brief Destroy a @a (Nucleus_FileHandle_Prototype) object.
/// @param fileHandle a pointer to the @a (Nucleus_FileHandle_Prototype) object
/// @post The @a (Nucleus_FileHandle_Prototype) object pointed by @a (*fileHandle) was destroyed.
Nucleus_NonNull(1) void
Nucleus_FileHandle_destroy
    (
        Nucleus_FileHandle *fileHandle
    );

/// @ingroup filesystem
/// @brief Get the size of thefi
/// @param fileHandle a pointer to a @a (Nucleus_FileHandle) object
/// @param fileSize a pointer to a @a (Nucleus_Size) variable
/// @defaultReturn
/// @success The size of the file represented by the @a (Nucleu_FileHandle) object pointed to by @a (fileHandle) was assigned to @a (*fileSize).
/// @failure @a (*fileSize) was not dereferenced.
Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_FileHandle_getFileSize
    (
        Nucleus_FileHandle *fileHandle,
        Nucleus_Size *fileSize
    );
