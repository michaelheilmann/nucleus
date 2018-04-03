// Copyright (c) Michael Heilmann 2018
#include "Nucleus/getPageSizeLinux.h"

#if defined(Nucleus_Platform_Linux)

#include <unistd.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeLinux
    (
        size_t *pageSize
    )
{
    if (!pageSize) return Nucleus_Status_InvalidArgument;
    long sz = sysconf(_SC_PAGESIZE);
    *pageSize = sz;
    return Nucleus_Status_Success;
}

#endif
