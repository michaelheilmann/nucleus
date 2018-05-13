// Copyright (c) 2017, 2018 Michael Heilmann
#include "Nucleus/Hash/ArrayMemory.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/SafeArithmeticOperations.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashArrayMemory
    (
        const void *p,
        Nucleus_Size n,
        Nucleus_Size m,
        Nucleus_HashValue *hv
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (status) return status;
    return Nucleus_hashMemory(p, k, hv);
}
