// Copyright (c) Michael Heilmann 2018
#include "Nucleus/booleanToString.h"

#include "Nucleus/Memory.h"

Nucleus_NonNull(2, 3, 5, 6) Nucleus_Status
Nucleus_booleanToString
    (
        Nucleus_Boolean value,
        char **bytes,
        Nucleus_Size *numberOfBytes,
        Nucleus_MemoryManager_State *state,
        Nucleus_MemoryManager_Allocate *allocate,
        Nucleus_MemoryManager_Deallocate *deallocate
    )
{
    if (!bytes || !numberOfBytes || !allocate || !deallocate)
    {
        return Nucleus_Status_InvalidArgument;
    }

    // Holds a static strings and its length without zero terminator.
    typedef struct StaticString
    {
        const char *bytes;
        size_t numberOfBytes;
    } StaticString;

    static const StaticString strings[] =
    {
        { "true", sizeof("true") - sizeof(char) },
        { "false", sizeof("false") - sizeof(char) },
    };

    const StaticString *q = value ? &(strings[0])
                                  : &(strings[1]);
    char *p;
    Nucleus_Status status = allocate(state, NULL, (void **)&p, q->numberOfBytes);
    if (status)
    {
        return status;
    }
    Nucleus_copyMemory(p, q->bytes, q->numberOfBytes);
    *bytes = p;
    *numberOfBytes = q->numberOfBytes;
    return Nucleus_Status_Success;
}
