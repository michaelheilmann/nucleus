// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Pointer.h"

#include <stdint.h>

Nucleus_NoError() Nucleus_Status
Nucleus_hashPointer
    (
        const void *v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (Nucleus_HashValue)(uintptr_t)v;
    return Nucleus_Status_Success;
}
