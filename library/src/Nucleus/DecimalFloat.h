// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/FloatingPoint.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Sign.h"

typedef uint8_t Nucleus_DecimalFloat_Digit;

typedef struct Nucleus_DecimalFloat Nucleus_DecimalFloat;

struct Nucleus_DecimalFloat
{
    Nucleus_Sign sign;
    Nucleus_Integer64 exponent;
    Nucleus_Size numberOfDigits;
    Nucleus_DecimalFloat_Digit *digits;
}; // struct Nucleus_DecimalFloat

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_createNaN
    (
        Nucleus_DecimalFloat **decimalFloat
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_createInf
    (
        Nucleus_DecimalFloat **decimalFloat,
        Nucleus_Sign sign
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_create_fromString
    (
        Nucleus_DecimalFloat **decimalFloat,
        const char *bytes,
        Nucleus_Size numberOfBytes
    );

Nucleus_NonNull() void
Nucleus_DecimalFloat_destroy
    (
        Nucleus_DecimalFloat *decimalFloat
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isNaN
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isNaN
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isPositiveInfinity
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isPositiveInfinity
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isNegativeInfinity
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isNegativeInfinity
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_getNumberOfDigits
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Size *numberOfDigits
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_getDigit
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Size indexOfDigit,
        Nucleus_DecimalFloat_Digit *digit
    );
