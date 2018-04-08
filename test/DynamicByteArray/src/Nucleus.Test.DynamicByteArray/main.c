#include "Nucleus/DynamicByteArray.h"
#include <stdlib.h>
#include <string.h>

static Nucleus_Status
test1
    (
    );

static Nucleus_Status
test2
    (
    );

static Nucleus_Status
test3
    (
    );

// [] -> ['c'] -> ['a', 'c'] -> ['a', 'b', 'c'] -> ['a', 'b', 'c', 'd']
static Nucleus_Status
test1
    (
    )
{
    Nucleus_DynamicByteArray byteArray;
    Nucleus_Status status;
    status = Nucleus_DynamicByteArray_initialize(&byteArray, 0);
    if (status) return status;

    // [c]
    status = Nucleus_DynamicByteArray_insert(&byteArray, 'c', 0);
    if (status) goto Exit;

    // [a, c]
    status = Nucleus_DynamicByteArray_insert(&byteArray, 'a', 0);
    if (status) goto Exit;

    // [a, b, c]
    status = Nucleus_DynamicByteArray_insert(&byteArray, 'b', 1);
    if (status) goto Exit;

    // [a, b, c, d]
    status = Nucleus_DynamicByteArray_insert(&byteArray, 'd', 3);
    if (status) goto Exit;

    size_t numberOfBytes;
    status = Nucleus_DynamicByteArray_getSize(&byteArray, &numberOfBytes);
    if (status) goto Exit;

    static const char *STRING = "abcd";
    const size_t STRING_LENGTH = strlen(STRING);
    if (numberOfBytes != STRING_LENGTH)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (size_t i = 0, n = numberOfBytes; i < n; ++i)
    {
        char byte;
        status = Nucleus_DynamicByteArray_at(&byteArray, i, &byte);
        if (status) goto Exit;
        if (byte != STRING[i])
        {
            status = Nucleus_Status_InternalError;
            goto Exit;
        }
    }
Exit:
    Nucleus_DynamicByteArray_uninitialize(&byteArray);
    return status;
}

// [] -> ['c', 'c'] -> ['a', 'a', 'c', 'c'] -> ['a', 'a', 'b', 'b', 'c', 'c'] ->
// ['a', 'a', 'b', 'b', 'c', 'c', 'd', 'd']
static Nucleus_Status
test2
    (
    )
{
    Nucleus_DynamicByteArray byteArray;
    Nucleus_Status status;
    status = Nucleus_DynamicByteArray_initialize(&byteArray, 0);
    if (status)
    {
        return status;
    }

    // [] -> [c c]
    status = Nucleus_DynamicByteArray_insertMany(&byteArray, "cc", 2, 0);
    if (status) goto Exit;

    // [c c] -> [a a c c]
    status = Nucleus_DynamicByteArray_insertMany(&byteArray, "aa", 2, 0);
    if (status) goto Exit;

    // [a a c c] -> [a a b b c c]
    status = Nucleus_DynamicByteArray_insertMany(&byteArray, "bb", 2, 2);
    if (status) goto Exit;

    // [a a b b c c] -> [a a b b c c d d]
    status = Nucleus_DynamicByteArray_insertMany(&byteArray, "dd", 2, 6);
    if (status) goto Exit;

    size_t numberOfBytes;
    status = Nucleus_DynamicByteArray_getSize(&byteArray, &numberOfBytes);
    if (status) goto Exit;

    static const char *STRING = "aabbccdd";
    const size_t STRING_LENGTH = strlen(STRING);
    if (numberOfBytes != STRING_LENGTH)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (size_t i = 0, n = numberOfBytes; i < n; ++i)
    {
        char byte;
        status = Nucleus_DynamicByteArray_at(&byteArray, i, &byte);
        if (status) goto Exit;

        if (byte != STRING[i])
        {
            status = Nucleus_Status_InternalError;
            goto Exit;
        }
    }
Exit:
    Nucleus_DynamicByteArray_uninitialize(&byteArray);
    return status;
}

// [] -> ['W', 'o', 'r', 'l', 'd'] -> ['H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd'] ->
// ['H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd'] ->
// [a'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!']
static Nucleus_Status
test3
    (
    )
{
    Nucleus_DynamicByteArray byteArray;
    Nucleus_Status status;
    status = Nucleus_DynamicByteArray_initialize(&byteArray, 0);
    if (status)
    {
        return status;
    }
    status = Nucleus_DynamicByteArray_appendMany(&byteArray, "World", strlen("World"));
    if (status)
    {
        goto Exit;
    }
    status = Nucleus_DynamicByteArray_prependMany(&byteArray, "Hello", strlen("Hello"));
    if (status)
    {
        goto Exit;
    }
    status = Nucleus_DynamicByteArray_insertMany(&byteArray, ", ", strlen(", "), 5);
    if (status)
    {
        goto Exit;
    }
    status = Nucleus_DynamicByteArray_appendMany(&byteArray, "!", strlen("!"));
    if (status)
    {
        goto Exit;
    }
    size_t numberOfBytes;
    status = Nucleus_DynamicByteArray_getSize(&byteArray, &numberOfBytes);
    if (status)
    {
        goto Exit;
    }
    static const char *STRING = "Hello, World!";
    size_t STRING_LENGTH = strlen(STRING);
    if (numberOfBytes != STRING_LENGTH)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (size_t i = 0, n = numberOfBytes; i < n; ++i)
    {
        char byte;
        status = Nucleus_DynamicByteArray_at(&byteArray, i, &byte);
        if (status)
        {
            goto Exit;
        }
        if (byte != STRING[i])
        {
            status = Nucleus_Status_InternalError;
            goto Exit;
        }
    }
Exit:
    Nucleus_DynamicByteArray_uninitialize(&byteArray);
    return status;
}

int main(int argc, char **argv)
{
    if (test1() || test2() || test3()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
