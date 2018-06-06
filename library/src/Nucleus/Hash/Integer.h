// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Integer.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger8
    (
        const Nucleus_Integer8 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger16
    (
        const Nucleus_Integer16 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger32
    (
        const Nucleus_Integer32 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger64
    (
        const Nucleus_Integer64 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterInteger
    (
        const Nucleus_QuarterInteger value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfInteger
    (
        const Nucleus_HalfInteger value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashInteger
    (
        const Nucleus_Integer value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleInteger
    (
        const Nucleus_DoubleInteger value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleInteger
    (
        const Nucleus_QuadrupleInteger value,
        Nucleus_HashValue *hashValue
    );
