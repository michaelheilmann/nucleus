// Copyright (c) Michael Heilmann 2018
#include "Nucleus/getNumberOfProcessors.h"

#if defined(Nucleus_Platform_Windows)
    #include "Nucleus/getNumberOfProcessorsWindows.h"
#elif defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
    #include "Nucleus/getNumberOfProcessorsLinux.h"
#else
    #error("platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessors
    (
        Nucleus_Size *numberOfProcessors
    )
{
#if defined(Nucleus_Platform_Windows)
    return Nucleus_getNumberOfProcessorsWindows(numberOfProcessors);
#elif defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
    return Nucleus_getNumberOfProcessorsLinux(numberOfProcessors);
#else
    #error("platform not supported")
#endif
}
