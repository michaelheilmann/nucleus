// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getNumberOfProcessorsWindows.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessorsWindows
    (
        Nucleus_Size *numberOfProcessors
    )
{
    if (Nucleus_Unlikely(!numberOfProcessors)) return Nucleus_Status_InvalidArgument;
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    *numberOfProcessors = sysinfo.dwNumberOfProcessors;
    return Nucleus_Status_Success;
}

#endif
