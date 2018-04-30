#include "Nucleus/DecimalInteger-private.c.i"

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger8
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer8 integer
    )
{ return Nucleus_DecimalInteger_fromInteger64(decimalInteger, integer); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger16
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer16 integer
    )
{ return Nucleus_DecimalInteger_fromInteger64(decimalInteger, integer); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger32
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer32 integer
    )
{ return Nucleus_DecimalInteger_fromInteger64(decimalInteger, integer); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_fromInteger64
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_Integer64 integer
    )
{
    if (Nucleus_Unlikely(!decimalInteger)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    // Allocate DecimalInteger.
    Nucleus_DecimalInteger *temporary;
    status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_DecimalInteger));
    if (status) { return status; }
    // Special case of integer = 0.
    if (!integer)
    {
        temporary->sign = Nucleus_DecimalInteger_Sign_Plus;
        temporary->numberOfDigits = 1;
        temporary->capacityInDigits = 1;
        status = Nucleus_allocateMemory((void **)&temporary->digits, sizeof(Nucleus_DecimalInteger_Digit));
        if (status)
        {
            Nucleus_deallocateMemory(temporary);
            return status;
        }
        temporary->digits[0] = 0;
        *decimalInteger = temporary;
        return Nucleus_Status_Success;
    }
    // Estimate number of digits and capacity in digits and compute the sign.
    if (integer < 0) temporary->sign = Nucleus_DecimalInteger_Sign_Minus;
    else temporary->sign = Nucleus_DecimalInteger_Sign_Plus;
    // An integer in base 10 has a smaller or equal number of digits compared to an integer in base 2
    // if both represent the same value. So the number of binary digits is a conservative approximation
    // of the number of decimal digits.
    temporary->numberOfDigits = 0;
    temporary->capacityInDigits = sizeof(Nucleus_Integer64) * 8;
    // Allocate digits.
    status = Nucleus_allocateArrayMemory((void **)&temporary->digits, temporary->capacityInDigits,
                                         sizeof(Nucleus_DecimalInteger_Digit));
    if (status)
    {
        Nucleus_deallocateMemory(temporary);
        return status;
    }
    // Compute the digits.
    Nucleus_Integer64 v = integer;
    if (v < 0)
    {
        for (Nucleus_Size i = 0; v != 0; ++i)
        {
            temporary->digits[i] = -(v % 10);
            v /= 10;
            temporary->numberOfDigits++;
        }

    }
    else
    {
        for (Nucleus_Size i = 0; v != 0; ++i)
        {
            temporary->digits[i] = +(v % 10);
            v /= 10;
            temporary->numberOfDigits++;
        }
    }
    // Return the result
    *decimalInteger = temporary;
    // Return success.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_create
    (
        Nucleus_DecimalInteger **decimalInteger,
        Nucleus_DecimalInteger_Sign sign,
        const Nucleus_DecimalInteger_Digit *digits,
        Nucleus_Size numberOfDigits
    )
{
    if (Nucleus_Unlikely(!decimalInteger || !digits || !numberOfDigits)) return Nucleus_Status_InvalidArgument;
    Nucleus_DecimalInteger *temporary;
    Nucleus_Status status;
    status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_DecimalInteger));
    if (status) { return status; }
    status = Nucleus_cloneArrayMemory((void **)&temporary->digits, digits, numberOfDigits,
                                       sizeof(Nucleus_DecimalInteger_Digit));
    if (status) { Nucleus_deallocateMemory(temporary); return status; }

    temporary->sign = sign;
    temporary->numberOfDigits = numberOfDigits;
    temporary->capacityInDigits = numberOfDigits;

    *decimalInteger = temporary;
    return Nucleus_Status_Success;
}

#define OptimizeOnClone (1)

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_clone
    (
        Nucleus_DecimalInteger **y,
        const Nucleus_DecimalInteger *x
    )
{
    if (Nucleus_Unlikely(!y || !x)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_DecimalInteger *temporary;
    Nucleus_Status status;
    //
    status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_DecimalInteger));
    if (status) { return status; }
#if defined(OptimizeOnClone) && 1 == OptimizeOnClone
    //
    status = Nucleus_cloneArrayMemory((void **)&temporary->digits, x->digits, x->numberOfDigits,
                                      sizeof(Nucleus_DecimalInteger_Digit));
    if (status) { Nucleus_deallocateMemory(temporary); return status; }
    temporary->sign = x->sign;
    temporary->numberOfDigits = x->numberOfDigits;
    temporary->capacityInDigits = x->numberOfDigits;
#else
    //
    status = Nucleus_cloneArrayMemory((void **)&temporary->digits, x->digits, x->capacityInDigits,
                                      sizeof(Nucleus_DecimalInteger_Digit));
    if (status) { Nucleus_deallocateMemory(temporary); return status; }
    temporary->sign = x->sign;
    temporary->numberOfDigits = x->numberOfDigits;
    temporary->capacityInDigits = x->capacityInDigits;
#endif
    //
    *y = temporary;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_DecimalInteger_destroy
    (
        Nucleus_DecimalInteger *decimalInteger
    )
{
    decimalInteger->numberOfDigits = 0;
    Nucleus_deallocateMemory(decimalInteger->digits);
    decimalInteger->digits = NULL;
    decimalInteger->capacityInDigits = 0;
    Nucleus_deallocateMemory(decimalInteger);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_trimLeadingZeroes
    (
        Nucleus_DecimalInteger *x
    )
{
    if (Nucleus_Unlikely(!x)) return Nucleus_Status_InvalidArgument;
    Nucleus_Size i, j;
    for (i = x->numberOfDigits, j = 0; i > 1 && x->digits[i-1] == 0; --i, ++j)
    {}
    x->numberOfDigits -= j;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_getNumberOfDigits
    (
        Nucleus_DecimalInteger *decimalInteger,
        Nucleus_Size *numberOfDigits
    )
{
    if (Nucleus_Unlikely(!decimalInteger || !numberOfDigits)) return Nucleus_Status_InvalidArgument;
    *numberOfDigits = decimalInteger->numberOfDigits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_getDigit
    (
        Nucleus_DecimalInteger *decimalInteger,
        Nucleus_Size indexOfDigit,
        Nucleus_DecimalInteger_Digit *digit
    )
{
    if (Nucleus_Unlikely(!decimalInteger || !digit)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(indexOfDigit >= decimalInteger->numberOfDigits)) return Nucleus_Status_IndexOutOfBounds;
    *digit = decimalInteger->digits[indexOfDigit];
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_negate
    (
        Nucleus_DecimalInteger *x
    )
{
    if (Nucleus_Unlikely(!x)) return Nucleus_Status_InvalidArgument;
    switch (x->sign)
    {
        case Nucleus_DecimalInteger_Sign_Plus:
            x->sign = Nucleus_DecimalInteger_Sign_Minus;
            break;
        case Nucleus_DecimalInteger_Sign_Minus:
            x->sign = Nucleus_DecimalInteger_Sign_Plus;
            break;
        default:
            return Nucleus_Status_InternalError;
    };
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_add
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{ return add(x,y); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_subtract
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{ return subtract(x, y); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalInteger_compare
    (
        const Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y,
        int *r
    )
{ return compare(x, y, r); }
