// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getPageSizeLinux.h"

#if defined(Nucleus_Platform_Linux)

#include <unistd.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeLinux
    (
        Nucleus_Size *pageSize
    )
{
    if (!pageSize) return Nucleus_Status_InvalidArgument;
    long sz = sysconf(_SC_PAGESIZE);
    *pageSize = sz;
    return Nucleus_Status_Success;
}

#endif
