// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getExecutablePathnameMacOS.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)

#include "Nucleus/Memory.h"
#include <string.h>    
#include <mach-o/dyld.h>

// If defined to (1), print diagnostics on errors.
#define Diagnostics (1)

#if defined(Diagnostics) && 1 == Diagnostics
    #include <stdio.h>
    #define ERROR(...) fprintf(stderr, __VA_ARGS__);
#else
    #define ERROR(...)
#endif
    
Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutablePathnameMacOS
    (
        char **pathname
    )
{ 
    if (Nucleus_Unlikely(!pathname))
    {
        ERROR("%s:%d: %s failed \n", __FILE__, __LINE__, "assertion `NULL != pathname`");
        return Nucleus_Status_InvalidArgument;
    }
    uint32_t size = 1024;
    char *buffer = NULL;
    Nucleus_Status status;
    status = Nucleus_allocateMemory((void **)&buffer, size);
    if (Nucleus_Unlikely(status))
    { 
        ERROR("%s:%d: %s failed\n", __FILE__, __LINE__, "Nucleus_allocateMemory");
        return status;
    }
    do
    {
        if (_NSGetExecutablePath(buffer, &size) != -1)
        {
            break;
        }
        status = Nucleus_reallocateMemory((void **)&buffer, (size_t)size);
        if (Nucleus_Unlikely(status))
        {
            ERROR(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Nucleus_reallocateMemory");
            Nucleus_deallocateMemory(buffer);
            return status;
        }
    } while (1);
    char *temporary = strdup(buffer);
    Nucleus_deallocateMemory(buffer);
    if (Nucleus_Unlikely(!temporary))
    {
        ERROR(stderr, "%s:%d: %s: failed\n", __FILE__, __LINE__, "strdup");
        return Nucleus_Status_AllocationFailed;
    }
    *pathname = temporary;
    return Nucleus_Status_Success;
}

#endif
