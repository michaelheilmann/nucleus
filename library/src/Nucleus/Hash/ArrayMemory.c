// Copyright (c) Michael Heilmann 2017, 2018
#include "Nucleus/Hash/ArrayMemory.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/SafeArithmeticOperations.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashArrayMemory
    (
        const void *p,
        size_t n,
        size_t m,
        Nucleus_HashValue *hv
    )
{
    size_t k;
    Nucleus_Status status = Nucleus_safeMul(n, m, &k);
    if (status) return status;
    return Nucleus_hashMemory(p, k, hv);
}
