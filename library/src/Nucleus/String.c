// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/String.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/Memory.h"
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
