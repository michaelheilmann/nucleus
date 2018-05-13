// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/ByteArray.h"
#include "Nucleus/FileSystem.h"
#include "Nucleus/Memory.h"
#include <string.h>

Nucleus_NonNull(2) Nucleus_Status
callback
    (
        Nucleus_Collections_ByteArray *byteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    return Nucleus_Collections_ByteArray_appendMany(byteArray, bytes, numberOfBytes);
}

Nucleus_NonNull() static Nucleus_Status
test
    (
        const char *pathname,
        const char *content,
        size_t contentSize
    )
{
    if (!pathname || !content) return Nucleus_Status_InvalidArgument;

    Nucleus_Status status;

    status = Nucleus_setFileContents(pathname, content, contentSize);
    if (status) return status;

    Nucleus_Collections_ByteArray buffer;
    status = Nucleus_Collections_ByteArray_initialize(&buffer, 0);
    if (status) return status;

    status = Nucleus_getFileContentsExtended(pathname, &buffer,
                                             (Nucleus_getFileContentsExtendedCallbackFunction *)(&callback));
    if (status)
    {
        Nucleus_Collections_ByteArray_uninitialize(&buffer);
        return status;
    }

    void *readContent = NULL;
    size_t readContentSize = 0;

    // TODO: API violates the API conventions of Nucleus.
    status = Nucleus_Collections_ByteArray_lock(&buffer, &readContent, &readContentSize);
    if (status)
    {
        Nucleus_Collections_ByteArray_uninitialize(&buffer);
        return status;
    }

    if (contentSize != readContentSize)
    {
        Nucleus_Collections_ByteArray_unlock(&buffer);
        Nucleus_Collections_ByteArray_uninitialize(&buffer);
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    bool result;
    status = Nucleus_compareMemory(content, readContent, contentSize, &result);
    if (status)
    {
        Nucleus_Collections_ByteArray_unlock(&buffer);
        Nucleus_Collections_ByteArray_uninitialize(&buffer);
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    Nucleus_Collections_ByteArray_unlock(&buffer);
    Nucleus_Collections_ByteArray_uninitialize(&buffer);

    if (!result)
    {
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (test("data/helloworld.txt", "Hello, World!\n", strlen("Hello, World!\n")) || 
        test("data/empty.txt", "", strlen("")))
    { return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}
