// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Hash/combineHashValues.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_combineHashValues
    (
        Nucleus_HashValue x,
        Nucleus_HashValue y,
        Nucleus_HashValue *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
    // This is just another black-magic formula used by boost and glib.
    *z = x + 0x9e3779b9 + (y << 6) + (y >> 2);
    return Nucleus_Status_Success;
}
