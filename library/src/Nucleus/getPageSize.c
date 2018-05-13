// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getPageSize.h"

#if defined(Nucleus_Platform_Windows)
    #include "Nucleus/getPageSizeWindows.h"
#elif defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
    #include "Nucleus/getPageSizeLinux.h"
#else
    #error("target platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSize
    (
        Nucleus_Size *pageSize
    )
{
#if defined(Nucleus_Platform_Windows)
    return Nucleus_getPageSizeWindows(pageSize);
#elif defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
    return Nucleus_getPageSizeLinux(pageSize);
#else
    #error("target platform not supported")
#endif
}
