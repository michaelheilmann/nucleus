// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getExecutablePathnameWindows.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/String.h"

// If defined to (1), print diagnostics on errors.
#define Diagnostics (1)

#if defined(Diagnostics) && 1 == Diagnostics
    #include <stdio.h>
    #define ERROR(...) fprintf(stderr, __VA_ARGS__);
#else
    #define ERROR(...)
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutablePathnameWindows
    (
        char **pathname
    )
{
    if (Nucleus_Unlikely(!pathname)) return Nucleus_Status_InvalidArgument;
    HMODULE hModule = GetModuleHandleW(NULL); // TODO: Use GetModuleHandleW.
    WCHAR *buffer = NULL;
    Nucleus_Size capacity = MAX_PATH;
    Nucleus_Status status;
    // Allocate buffer.
    status = Nucleus_allocateArrayMemory((void **)&buffer, capacity, sizeof(WCHAR));
    if (Nucleus_Unlikely(status)) return status;
    do
    {
        // Try to get the module filename.
        DWORD dwResult = GetModuleFileNameW(hModule, buffer, capacity);
        if (dwResult == 0)
        {
            // Failure.
            Nucleus_deallocateMemory(buffer);
            return Nucleus_Status_EnvironmentFailed;
        }
        else if (dwResult == capacity)
        {
            // Buffer is too small. Increase its size.
            Nucleus_Size newCapacity = capacity + MAX_PATH; // TODO: Use safe and saturating arithmetic.
            status = Nucleus_reallocateMemory((void **)&buffer, newCapacity);
            if (status)
            {
                Nucleus_deallocateMemory(buffer);
                return status;
            }
            capacity = newCapacity;
            // Keep going.
        }
        else
        {
            // Optimize the buffer.
            status = Nucleus_reallocateArrayMemory((void **)&buffer, dwResult + 1, sizeof(WCHAR));
            if (status)
            {
                Nucleus_deallocateMemory(buffer);
                return status;
            }
            break;
        }
    } while (1);
    char *temporary;
    status = Nucleus_UCS16_to_UTF8(&temporary, buffer);
    Nucleus_deallocateMemory(buffer);
    if (status)
    {
        return status;
    }
    *pathname = temporary;
    return Nucleus_Status_Success;
}

#endif
