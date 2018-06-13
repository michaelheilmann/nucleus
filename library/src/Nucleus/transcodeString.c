// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/transcodeString.h"

#include "Nucleus/Memory.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"

// Convert a zero-terminated UCS-16 string into a zero-terminated UTF-8 string.
Nucleus_NonNull() Nucleus_Status
Nucleus_UCS16_to_UTF8
    (
        Nucleus_UTF8 **target,
        const Nucleus_UCS16 *source
    )
{
    if (Nucleus_Unlikely(!target || !source)) return Nucleus_Status_InvalidArgument;
    
    int result;
    
    result = WideCharToMultiByte(CP_UTF8, 0, source, -1, NULL, 0, NULL, NULL);
    if (Nucleus_Unlikely(0 == result))
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    
    Nucleus_UTF8 *temporary;
    Nucleus_Status status;
    status = Nucleus_allocateArrayMemory((void **)&temporary, result, sizeof(char));
    if (Nucleus_Unlikely(status)) return status;
    
    result = WideCharToMultiByte(CP_UTF8, 0, source,-1, temporary, result, NULL, NULL);
    if (Nucleus_Unlikely(0 == result))
    {
        Nucleus_deallocateMemory(temporary);
        return Nucleus_Status_EnvironmentFailed;
    }

    *target = temporary;
    
    return Nucleus_Status_Success;
}

// Convert a zero-terminated UTF-8 string into a zero-terminated UCS-16 string.
Nucleus_NonNull() Nucleus_Status
Nucleus_UTF8_to_UCS16
    (
        Nucleus_UCS16 **target,
        const Nucleus_UTF8 *source
    )
{
    if (Nucleus_Unlikely(!target || !source)) return Nucleus_Status_InvalidArgument;
    
    int result;
    
    result = MultiByteToWideChar(CP_UTF8, 0, source, -1, NULL, 0);
    if (Nucleus_Unlikely(0 == result))
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    
    Nucleus_UCS16 *temporary;
    Nucleus_Status status;
    status = Nucleus_allocateArrayMemory((void **)&temporary, result, sizeof(Nucleus_UCS16));
    if (Nucleus_Unlikely(status)) return status;
    
    result = MultiByteToWideChar(CP_UTF8, 0, source,-1, temporary, result);
    if (Nucleus_Unlikely(0 == result))
    {
        Nucleus_deallocateMemory(temporary);
        return Nucleus_Status_EnvironmentFailed;
    }

    *target = temporary;
    
    return Nucleus_Status_Success;
}

#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_UTF8_to_ASCII
    (
        Nucleus_ASCII **target,
        const Nucleus_UTF8 *source
    )
{
    if (Nucleus_Unlikely(!target || !source)) return Nucleus_Status_InvalidArgument;
    const Nucleus_UTF8 *p = source;
    Nucleus_Size length = 0;
    while (true)
    {
        // If and only if the leftmost bit is not set,
        // then the Byte is the beginning of a 1-Byte UTF-8 sequence.
        if (((*p) & 128) == 0)
        {
            // We hit the end of the string.
            if ((*p) == '\0')
            {
                break;
            }
            p++;
            length++;
        }
        else
        {
            return Nucleus_Status_InvalidArgument;
        }
    }
    Nucleus_ASCII *temporary;
    Nucleus_Status status;
    status = Nucleus_allocateArrayMemory((void **)&temporary, length+1, sizeof(Nucleus_ASCII));
    if (Nucleus_Unlikely(status)) return status;
    Nucleus_copyArrayMemory((void *)temporary, source, length+1, sizeof(char));
    *target = temporary;
    return Nucleus_Status_Success;
}
