// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/HashValue.h"

Nucleus_NoError() Nucleus_Status
Nucleus_hashHashValue
    (
        const Nucleus_HashValue v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = v;
    return Nucleus_Status_Success;
}
