// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Integer.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger8
    (
        const Nucleus_Integer8 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger16
    (
        const Nucleus_Integer16 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger32
    (
        const Nucleus_Integer32 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger64
    (
        const Nucleus_Integer64 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterInteger
    (
        const Nucleus_QuarterInteger v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfInteger
    (
        const Nucleus_HalfInteger v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger
    (
        const Nucleus_Integer v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleInteger
    (
        const Nucleus_DoubleInteger v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleInteger
    (
        const Nucleus_QuadrupleInteger v,
        Nucleus_HashValue *hv
    );