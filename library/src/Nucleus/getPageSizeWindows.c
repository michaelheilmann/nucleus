// Copyright (c) Michael Heilmann 2018
#include "Nucleus/getPageSizeWindows.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/IncludesWindows.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeWindows
    (
        size_t *pageSize
    )
{
    if (!pageSize) return Nucleus_Status_InvalidArgument;
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    *pageSize = systemInfo.dwPageSize;
    return Nucleus_Status_Success;
}

#endif
