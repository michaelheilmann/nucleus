// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Integer.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger8
    (
        const Nucleus_Integer8 value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Integer8), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger16
    (
        const Nucleus_Integer16 value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Integer16), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger32
    (
        const Nucleus_Integer32 value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Integer32), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger64
    (
        const Nucleus_Integer64 value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Integer64), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterInteger
    (
        const Nucleus_QuarterInteger value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_QuarterInteger), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfInteger
    (
        const Nucleus_HalfInteger value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_HalfInteger), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger
    (
        const Nucleus_Integer value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_Integer), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleInteger
    (
        const Nucleus_DoubleInteger value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_DoubleInteger), hashValue); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleInteger
    (
        const Nucleus_QuadrupleInteger value,
        Nucleus_HashValue *hashValue
    )
{ return Nucleus_hashMemory((void *)&value, sizeof(Nucleus_QuadrupleInteger), hashValue); }
