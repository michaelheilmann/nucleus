/// @file Nucleus/FileSystem/getFileContentsInterface.h
/// @brief Function prototype for getting the contents of a file.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

#include <stdlib.h>
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

/// @ingroup filesystem
/// @brief The type of a callback invoked by Nucleus_getFileContentsExtended function.
/// @param object the object to invoke the callback on
/// @param bytes a pointer to an array of @a numberOfBytes Bytes, the contents of the file
/// @param numberOfBytes the number of Bytes in the array pointed to by @a bytes
/// @defaultReturn
/// @warning Writing to the array pointed to by @a bytes is in general undefined behavior.
typedef
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_getFileContentsExtendedCallbackFunction
    (
        Nucleus_InputOutputParameter(void *object),
        Nucleus_InputParameter(const char *bytes),
        Nucleus_InputParameter(Nucleus_Size numberOfBytes)
    );

/// @ingroup filesystem
/// @brief Get the contents of a file.
/// @param pathname a pointer to the pathname of the file
/// @param bytes a pointer to a @a (char *) variable
/// @param numberOfBytes a pointer to a @a (Nucleus_Size) variable
/// @defaultReturn
/// @success @a *numberOfBytes was assigned the size of the file which may be @a 0.
///          @a *bytes was assigned a pointer to an array of at least @a *numberOfBytes Bytes such that the first @a *numberOfBytes
///          represent the content of the file. That array must be deallocated using free if no longer required.
/// @failure Neither @a numberOfBytes nor @a bytes were dereferenced.
/// @remark The memory returned is allocated using <code>malloc</code>. If it is no longer referenced then it must be deallocated using <code>free</code>.
Nucleus_NonNull(1, 2, 3) Nucleus_Status
Nucleus_getFileContents
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_OutputParameter(char **bytes),
        Nucleus_OutputParameter(Nucleus_Size *numberOfBytes)
    );

/// @ingroup filesystem
/// @brief Get the contents of a file.
/// @param pathname a pointer to the pathname of the file
/// @param object the object to invoke the callback pointed to by @a (callback) on
/// @param callback a pointer to a @a (Nucleus_getFileContentsCallbackFunction) function
/// @defaultReturn
Nucleus_NonNull(1, 3) Nucleus_Status
Nucleus_getFileContentsExtended
    (
        Nucleus_InputParameter(const char *pathname),
        Nucleus_InputOutputParameter(void *object),
        Nucleus_InputOutputParameter(Nucleus_getFileContentsExtendedCallbackFunction *callback)
    );
