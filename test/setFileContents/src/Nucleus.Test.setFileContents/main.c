// Copyright (c) Michael Heilmann 2018
#include "Nucleus/DynamicByteArray.h"
#include "Nucleus/FileSystem.h"
#include "Nucleus/Memory.h"
#include <string.h>

Nucleus_NonNull(2) Nucleus_Status
callback
    (
        Nucleus_DynamicByteArray *byteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    return Nucleus_DynamicByteArray_append(byteArray, bytes, numberOfBytes);
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

    Nucleus_DynamicByteArray buffer;
    status = Nucleus_DynamicByteArray_initialize(&buffer, 0);
    if (status) return status;

    status = Nucleus_getFileContentsExtended(pathname, &buffer,
                                             (Nucleus_getFileContentsExtendedCallbackFunction *)(&callback));
    if (status)
    {
        Nucleus_DynamicByteArray_uninitialize(&buffer);
        return status;
    }

    const char *readContent = NULL;
    size_t readContentSize = 0;

    // TODO: API violates the API conventions of Nucleus.
    readContent = Nucleus_DynamicByteArray_getBytes(&buffer);

    status = Nucleus_DynamicByteArray_getSize(&buffer, &readContentSize);
    if (status)
    {
        Nucleus_DynamicByteArray_uninitialize(&buffer);
        return status;
    }

    if (contentSize != readContentSize)
    {
        Nucleus_DynamicByteArray_uninitialize(&buffer);
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    bool result;
    status = Nucleus_compareMemory(content, readContent, contentSize, &result);
    if (status)
    {
        Nucleus_DynamicByteArray_uninitialize(&buffer);
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    Nucleus_DynamicByteArray_uninitialize(&buffer);

    if (!result)
    {
        return Nucleus_Status_InternalError; // TODO: Add and use Nucleus_Status_TestFailed.
    }

    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (test("data/helloworld.txt", "Hello, World!\n", sizeof("Hello, World!\n") - 1) || 
        test("data/empty.txt", "", sizeof("") - 1))
    { return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}
