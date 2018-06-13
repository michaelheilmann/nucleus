// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/formatString.h"

#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "Nucleus/Memory.h"

Nucleus_NonNull() static Nucleus_Status
formatString
    (
        char **result,
        const char *format,
        va_list arguments
    );

Nucleus_NonNull() static Nucleus_Status
formatString
    (
        char **result,
        const char *format,
        va_list arguments
    )
{
    #define CAPACITY 8
    
    // Compute the size of the result.
    char buffer[CAPACITY + 1];
    int count = vsnprintf(buffer, CAPACITY + 1, format, arguments);
    if (-1 == count)
    { return Nucleus_Status_InvalidArgument; }
    if (INT_MAX == count)
    { return Nucleus_Status_TooLong; }
    
    // Allocate memory for the result.
    Nucleus_Status status;
    char *temporary;
    status = Nucleus_allocateArrayMemory((void **)&temporary, count + 1, sizeof(char));
    if (status)
    { return status; }

    // Write the result.
    if (count != vsnprintf(temporary, count + 1, format, arguments))
    { Nucleus_deallocateMemory(temporary); return Nucleus_Status_EnvironmentFailed; }
    
    // Return the result.
    *result = temporary;

    // Return success.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_formatString
    (
        char **result,
        const char *format,
        ...
    )
{
    if (Nucleus_Unlikely(!result || !format))
    { return Nucleus_Status_InvalidArgument; }

    va_list arguments;

    va_start(arguments, format);
    Nucleus_Status status = formatString(result, format, arguments);
    va_end(arguments);

    return status;
}
