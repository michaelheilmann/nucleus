// Copyright (c) Michael Heilmann 2018
#include "Nucleus/getNumberOfProcessorsLinux.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)

#include <unistd.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessorsLinux
    (
        Nucleus_Size *numberOfProcessors
    )
{
    if (Nucleus_Unlikely(!numberOfProcessors)) return Nucleus_Status_InvalidArgument;
    int n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 0) return Nucleus_Status_EnvironmentFailed;
    *numberOfProcessors = (Nucleus_Size)n;
    return Nucleus_Status_Success;
}

#endif
