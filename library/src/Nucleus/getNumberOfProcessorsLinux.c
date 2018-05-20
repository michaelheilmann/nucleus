// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getNumberOfProcessorsLinux.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)

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
