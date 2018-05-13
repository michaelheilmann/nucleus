// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Integer.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger8
    (
        const Nucleus_Integer8 v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Integer8), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger16
    (
        const Nucleus_Integer16 v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Integer16), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger32
    (
        const Nucleus_Integer32 v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Integer32), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger64
    (
        const Nucleus_Integer64 v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Integer64), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterInteger
    (
        const Nucleus_QuarterInteger v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_QuarterInteger), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfInteger
    (
        const Nucleus_HalfInteger v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_HalfInteger), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger
    (
        const Nucleus_Integer v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Integer), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleInteger
    (
        const Nucleus_DoubleInteger v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_DoubleInteger), hv); }

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleInteger
    (
        const Nucleus_QuadrupleInteger v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_QuadrupleInteger), hv); }
