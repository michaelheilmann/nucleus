// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getExecutablePathnameLinux.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include "Nucleus/Memory.h"
#include <string.h>

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    #include <limits.h>
#else
    #include <linux/limits.h>
#endif
#include <unistd.h>
    
// If defined to (1), print diagnostics on errors.
#define Diagnostics (1)
    
#if defined(Diagnostics) && 1 == Diagnostics
    #include <stdio.h>
    #define ERROR(...) fprintf(stderr, __VA_ARGS__);
#else
    #define ERROR(...)
#endif
    
Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutablePathnameLinux
    (
        char **pathname
    )
{ 
    if (Nucleus_Unlikely(!pathname))
    {
        ERROR("%s:%d: %s failed \n", __FILE__, __LINE__, "assertion `NULL != pathname`");
        return Nucleus_Status_InvalidArgument;
    }
    char buffer[PATH_MAX + 1];
    if (Nucleus_Unlikely(-1 == readlink("/proc/self/exe", buffer, sizeof(buffer) - 1)))
    {
        ERROR("%s:%d: %s failed\n", __FILE__, __LINE__, "readlink");
        return Nucleus_Status_EnvironmentFailed; 
    }
    // TODO: `readlink` returns a string in some unknown encoding. There is an article stating
    // PRECISELY the problem I have suspected (https://lwn.net/Articles/71472/). An interesting
    // Wiki entry of the Mercurial project sheds a light on the findings regarding these unknown
    // encoding and how to deal with them (https://www.mercurial-scm.org/wiki/EncodingStrategy).
    char *temporary = strdup(buffer);
    if (Nucleus_Unlikely(!temporary))
    {
        ERROR("%s:%d: %s failed\n", __FILE__, __LINE__, "strdup");
        return Nucleus_Status_AllocationFailed;
    }
    *pathname = temporary;
    return Nucleus_Status_Success;
}

#endif
