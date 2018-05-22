// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/getPageSizeWindows.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/IncludesWindows.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeWindows
    (
        Nucleus_Size *pageSize
    )
{
    if (Nucleus_Unlikely(!pageSize)) return Nucleus_Status_InvalidArgument;
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    *pageSize = systemInfo.dwPageSize;
    return Nucleus_Status_Success;
}

#endif
