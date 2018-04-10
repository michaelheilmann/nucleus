// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Natural.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural8
    (
        const Nucleus_Natural8 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural16
    (
        const Nucleus_Natural16 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural32
    (
        const Nucleus_Natural32 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural64
    (
        const Nucleus_Natural64 v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuarterNatural
    (
        const Nucleus_QuarterNatural v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashHalfNatural
    (
        const Nucleus_HalfNatural v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashNatural
    (
        const Nucleus_Natural v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDoubleNatural
    (
        const Nucleus_DoubleNatural v,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadrupleNatural
    (
        const Nucleus_QuadrupleNatural v,
        Nucleus_HashValue *hv
    );
