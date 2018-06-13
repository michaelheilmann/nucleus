// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/subString.h"

#include <string.h> // For "strlen".
#include "Nucleus/Memory.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_subString
    (
        char **result,
        const char *string,
        Nucleus_Size index,
        Nucleus_Size length
    )
{
    if (Nucleus_Unlikely(!result || !string || length == SIZE_MAX)) return Nucleus_Status_InvalidArgument;

    size_t l = strlen(string);
    if (l == SIZE_MAX || l < index + length)
    { return Nucleus_Status_InvalidArgument; }

    Nucleus_Status status;
    char *temporary;

    status = Nucleus_allocateMemory((void **)&temporary, length + 1);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }

    status = Nucleus_copyMemory(temporary, string + index, length);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(temporary);
        return status;
    }

    temporary[length] = '\0';

    *result = temporary;

    return Nucleus_Status_Success;
}
