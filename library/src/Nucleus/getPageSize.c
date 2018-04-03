// Copyright (c) Michael Heilmann 2018
#include "Nucleus/getPageSize.h"

#if defined(Nucleus_Platform_Windows)
    #include "Nucleus/getPageSizeWindows.h"
#elif defined(Nucleus_Platform_Linux)
    #include "Nucleus/getPageSizeLinux.h"
#else
    #error("target platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSize
    (
        size_t *pageSize
    )
{
#if defined(Nucleus_Platform_Windows)
    return Nucleus_getPageSizeWindows(pageSize);
#elif defined(Nucleus_Platform_Linux)
    return Nucleus_getPageSizeLinux(pageSize);
#else
    #error("target platform not supported")
#endif
}
