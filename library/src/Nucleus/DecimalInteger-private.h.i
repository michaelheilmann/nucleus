#pragma once

#include "Nucleus/DecimalInteger.h"

#include "Nucleus/Memory.h"
#include <math.h>

/* The base. */
static const Nucleus_DecimalInteger_Digit BASE = 10;

struct Nucleus_DecimalInteger
{
    /// @brief A pointer to an array of @a numberOfDigits @a (Nucleus_DecimalDigit) values.
    /// @a (digit[0]) is the least significant digit.
    Nucleus_DecimalInteger_Digit *digits;
    /// @brief The number of used elements in the array pointed to by @a digits.
    /// This number is at least @a 1.
    Nucleus_Size numberOfDigits;
    /// @brief The number of elements in the array pointed to by @a digits.
    /// This number of at least @a 1.
    Nucleus_Size capacityInDigits;
    /// @brief The sign of the decimal integer.
    Nucleus_DecimalInteger_Sign sign;
}; // struct Nucleus_DecimalInteger

/* Addition of two decimal integers with same signs. */
Nucleus_NonNull() static Nucleus_Status
addSameSigns
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

/* Subtraction of two decimal integers with same signs. */
Nucleus_NonNull() static Nucleus_Status
subtractSameSigns
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

/*
 * X + Y
 * if X.sign = Y.sign then call addSameSigns(X, Y)
 * if X.sign != Y.sign then call subtractSameSigns(X, -Y)
 * The latter formula is proper as X + Y ~ X - (Y-)
 */
Nucleus_NonNull() static Nucleus_Status
add
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

/* 
 * X - Y
 * if X.sign = Y.sign then call subtractSameSigns(X, Y)
 * if X.sign != Y.sign then call addSameSigns(X, -Y)
 * The latter formula is proper as X - Y ~ X + (-Y)
 */
Nucleus_NonNull() static Nucleus_Status
subtract
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

Nucleus_NonNull() static Nucleus_Status
compare
    (
        const Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y,
        int *r
    );
