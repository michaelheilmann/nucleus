// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getNumberOfProcessors.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #include "Nucleus/getNumberOfProcessorsWindows.h"
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    #include "Nucleus/getNumberOfProcessorsLinux.h"
#else
    #error("operating system not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessors
    (
        Nucleus_Size *numberOfProcessors
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    return Nucleus_getNumberOfProcessorsWindows(numberOfProcessors);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    return Nucleus_getNumberOfProcessorsLinux(numberOfProcessors);
#else
    #error("operating system not supported")
#endif
}
