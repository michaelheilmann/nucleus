#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Natural.h"
#include "Nucleus/Types/Size.h"

typedef enum Nucleus_DecimalInteger_Sign Nucleus_DecimalInteger_Sign;
enum Nucleus_DecimalInteger_Sign
{
    Nucleus_DecimalInteger_Sign_Plus,
    Nucleus_DecimalInteger_Sign_Minus,
}; // enum Nucleus_DecimalInteger_Sign

typedef Nucleus_Natural8 Nucleus_DecimalInteger_Digit;

typedef struct Nucleus_DecimalInteger Nucleus_DecimalInteger;

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

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger8
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer8 integer
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger16
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer16 integer
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger32
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer32 integer
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger64
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer64 integer
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_create
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_DecimalInteger_Sign sign,
        const Nucleus_DecimalInteger_Digit *digits,
        Nucleus_Size numberOfDigits
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_clone
    (
        Nucleus_DecimalInteger **y,
        const Nucleus_DecimalInteger *x
    );

Nucleus_NonNull() void
Nucleus_DecimalInteger_destroy
    (
        Nucleus_DecimalInteger *decimalInteger
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_trimLeadingZeroes
    (
        Nucleus_DecimalInteger *x
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_getNumberOfDigits
    (
        Nucleus_DecimalInteger *decimalInteger,
        Nucleus_Size *numberOfDigits
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_getDigit
    (
        Nucleus_DecimalInteger *decimalInteger,
        Nucleus_Size indexOfDigit,
        Nucleus_DecimalInteger_Digit *digit
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_negate
    (
        Nucleus_DecimalInteger *x
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_add
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_subtract
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_compare
    (
        const Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y,
        int *r
    );
