// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Natural.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural8
    (
        const Nucleus_Natural8 value,
        Nucleus_HashValue *hashValue
    )
{
    if (Nucleus_Unlikely(!hashValue)) return Nucleus_Status_InvalidArgument;
    *hashValue = (Nucleus_HashValue)value;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural16
    (
        const Nucleus_Natural16 value,
        Nucleus_HashValue *hashValue
    )
{
    if (Nucleus_Unlikely(!hashValue)) return Nucleus_Status_InvalidArgument;
    *hashValue = (Nucleus_HashValue)value;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural32
    (
        const Nucleus_Natural32 value,
        Nucleus_HashValue *hashValue
    )
{
    if (Nucleus_Unlikely(!hashValue)) return Nucleus_Status_InvalidArgument;
    *hashValue = (Nucleus_HashValue)value;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural64
    (
        const Nucleus_Natural64 value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Natural64), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterNatural
    (
        const Nucleus_QuarterNatural value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_QuarterNatural), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfNatural
    (
        const Nucleus_HalfNatural value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_HalfNatural), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural
    (
        const Nucleus_Natural value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Natural), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleNatural
    (
        const Nucleus_DoubleNatural value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_DoubleNatural), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleNatural
    (
        const Nucleus_QuadrupleNatural value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_QuadrupleNatural), hashValue); }
