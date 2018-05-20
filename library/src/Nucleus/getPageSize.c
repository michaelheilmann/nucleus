// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getPageSize.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #include "Nucleus/getPageSizeWindows.h"
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    #include "Nucleus/getPageSizeLinux.h"
#else
    #error("operating system not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSize
    (
        Nucleus_Size *pageSize
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    return Nucleus_getPageSizeWindows(pageSize);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    return Nucleus_getPageSizeLinux(pageSize);
#else
    #error("operating system not supported")
#endif
}
