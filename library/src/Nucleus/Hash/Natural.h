// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Natural.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural8
    (
        const Nucleus_Natural8 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural16
    (
        const Nucleus_Natural16 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural32
    (
        const Nucleus_Natural32 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural64
    (
        const Nucleus_Natural64 value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterNatural
    (
        const Nucleus_QuarterNatural value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfNatural
    (
        const Nucleus_HalfNatural value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural
    (
        const Nucleus_Natural value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleNatural
    (
        const Nucleus_DoubleNatural value,
        Nucleus_HashValue *hashValue
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleNatural
    (
        const Nucleus_QuadrupleNatural value,
        Nucleus_HashValue *hashValue
    );
