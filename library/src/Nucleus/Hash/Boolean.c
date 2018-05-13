// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Boolean.h"

Nucleus_NoError() Nucleus_Status
Nucleus_hashBoolean
    (
        const Nucleus_Boolean v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = v ? 1231 : 1237; // These are arbitrary prime number as e.g. used in Boolean.getHashCode in Java.
    return Nucleus_Status_Success;
}
