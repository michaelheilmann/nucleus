// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getExecutablePathname.h"

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #include "Nucleus/getExecutablePathnameWindows.h"
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    #include "Nucleus/getExecutablePathnameLinux.h"
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    #include "Nucleus/getExecutablePathnameMacOS.h"
#else
    #error("environment not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutablePathname
    (
        char **pathname
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    return Nucleus_getExecutablePathnameWindows(pathname);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    return Nucleus_getExecutablePathnameLinux(pathname);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    return Nucleus_getExecutablePathnameMacOS(pathname);
#else
    #error("environment not supported")
#endif
}
