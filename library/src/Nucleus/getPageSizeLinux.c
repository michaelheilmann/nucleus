// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getPageSizeLinux.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)

#include <unistd.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeLinux
    (
        Nucleus_Size *pageSize
    )
{
    if (Nucleus_Unlikely(!pageSize)) return Nucleus_Status_InvalidArgument;
    long sz = sysconf(_SC_PAGESIZE);
    *pageSize = sz;
    return Nucleus_Status_Success;
}

#endif
