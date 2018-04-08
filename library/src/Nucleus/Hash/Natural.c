// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Hash/Natural.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural8
    (
        const Nucleus_Natural8 v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (Nucleus_HashValue)v;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural16
    (
        const Nucleus_Natural16 v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (Nucleus_HashValue)v;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural32
    (
        const Nucleus_Natural32 v,
        Nucleus_HashValue *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (Nucleus_HashValue)v;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural64
    (
        const Nucleus_Natural64 v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Natural64), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterNatural
    (
        const Nucleus_QuarterNatural v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_QuarterNatural), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfNatural
    (
        const Nucleus_HalfNatural v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_HalfNatural), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural
    (
        const Nucleus_Natural v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Natural), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleNatural
    (
        const Nucleus_DoubleNatural v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_DoubleNatural), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleNatural
    (
        const Nucleus_QuadrupleNatural v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_QuadrupleNatural), hv); }
