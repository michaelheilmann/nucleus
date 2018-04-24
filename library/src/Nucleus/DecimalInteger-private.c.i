#include "Nucleus/DecimalInteger-private.h.i"

Nucleus_NonNull() static Nucleus_Status
addSameSigns
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{
    if (Nucleus_Unlikely(!x || !y)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(x->sign != y->sign)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    // Determine which of "x" and "y" has more digits. "small" points to the number with the least amount of digits,
    // "big" points to the number with the greatest amount of digits. If "x" and "y" have the same number of digits,
    // then "small" points to "x" and "big" points to "y".
    const Nucleus_DecimalInteger *small = x, *big = y;
    if (small->numberOfDigits > big->numberOfDigits)
    {
        const Nucleus_DecimalInteger *t = (const Nucleus_DecimalInteger *)small;
        small = big;
        big = t;
    }
    // Make room for "big.numberOfDigits" plus one digits.
    Nucleus_DecimalInteger_Digit *digits;
    Nucleus_Size numberOfDigits = big->numberOfDigits;
    status = Nucleus_allocateArrayMemory((void **)&digits, big->numberOfDigits + 1,
                                         sizeof(Nucleus_DecimalInteger_Digit));
    if (status) return status;
    // Iterate over "[0, small.numberOfDigits)]".
    Nucleus_Size i;
    Nucleus_Size c;
    for (i = 0, c = 0; i < small->numberOfDigits; ++i)
    {
        Nucleus_DecimalInteger_Digit t = small->digits[i] - big->digits[i] + c;
        t /= BASE;
        c %= BASE;
        digits[i] = t;
    }
    // Iterate over "[small.numberOfDigits, big.numberOfDigits)".
    for(; i < big->numberOfDigits; ++i)
    {
        // sum of carry (0 + 1) and one digit (0 to 9) yields a maximal value of 10.
        Nucleus_DecimalInteger_Digit t = big->digits[i] + c;
        if (t > 9)
        {
            t = t - 10;
            c = 1;
        }
        digits[i] = t;
    }

    if (c)
    {
        digits[i] = 1;
        numberOfDigits += 1;
    }

    Nucleus_deallocateMemory(x->digits);

    x->digits = digits;
    x->numberOfDigits = numberOfDigits;
    x->capacityInDigits = numberOfDigits;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
subtractSameSigns
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{
    if (Nucleus_Unlikely(!x || !y)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(x->sign != y->sign)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    // Determine the sign of the operands.
    Nucleus_DecimalInteger_Sign sign = x->sign;
    // The least number of digits.
    Nucleus_Size leastNumberOfDigits, greatestNumberOfDigits;
    if (x->numberOfDigits < y->numberOfDigits)
    {
        leastNumberOfDigits = x->numberOfDigits;
        greatestNumberOfDigits = y->numberOfDigits;
    }
    else
    {
        leastNumberOfDigits = x->numberOfDigits;
        greatestNumberOfDigits = y->numberOfDigits;
    }
    // Make room for "greatestNumberOfDigits + 1".
    Nucleus_DecimalInteger_Digit *digits;
    Nucleus_Size numberOfDigits = greatestNumberOfDigits + 1;
    status = Nucleus_allocateArrayMemory((void **)&digits, numberOfDigits, sizeof(Nucleus_DecimalInteger_Digit));
    if (status) return status;
    // Iterate over "[0, leastNumberOfDigits)]".
    Nucleus_Size i;
    Nucleus_Size c = 0;
    for (i = 0, c = 0; i < leastNumberOfDigits; ++i)
    {
        Nucleus_DecimalInteger_Digit t = x->digits[i] - y->digits[i] + c;
        t /= BASE;
        c %= BASE;
        digits[i] = t;
    }
    // Iterate over "[leastNumberOfDigits, greatestNumberOfDigits)".
    Nucleus_DecimalInteger *big = x;
    if (x->numberOfDigits < y->numberOfDigits)
    {
        big = (Nucleus_DecimalInteger *)y;
    }
    for(; i < greatestNumberOfDigits; ++i)
    {
        Nucleus_DecimalInteger_Digit t = big->digits[i] + c;
        t /= BASE;
        c %= BASE;
        digits[i] = t;
    }

    // A non-0 value of c (i.e. -1) indicates that the sign needs to be swapped.
    if (c)
    {
        digits[i] = 1; // As carry is 0 or -1.
        numberOfDigits += 1;
        switch (sign)
        {
        case Nucleus_DecimalInteger_Sign_Plus:
            sign = Nucleus_DecimalInteger_Sign_Minus;
            break;
        case Nucleus_DecimalInteger_Sign_Minus:
            sign = Nucleus_DecimalInteger_Sign_Plus;
            break;
        };
    }

    Nucleus_deallocateMemory(x->digits);

    x->sign = sign;
    x->digits = digits;
    x->numberOfDigits = numberOfDigits;
    x->capacityInDigits = numberOfDigits;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
add
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{
    if (Nucleus_Unlikely(!x || !y)) return Nucleus_Status_InvalidArgument;
    if (x->sign == y->sign)
    {
        return addSameSigns(x, y);
    }
    else
    {
        Nucleus_Status status;
        Nucleus_DecimalInteger *z;
        //
        status = Nucleus_DecimalInteger_clone(&z, y);
        if (status) return status;
        status = Nucleus_DecimalInteger_negate(z);
        if (status) return status;
        //
        status = subtractSameSigns(x, z);
        Nucleus_DecimalInteger_destroy(z);
        //
        return status;
    }
}

Nucleus_NonNull() static Nucleus_Status
subtract
    (
        Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y
    )
{
    if (Nucleus_Unlikely(!x || !y)) return Nucleus_Status_InvalidArgument;
    if (x->sign == y->sign)
    {
        return subtractSameSigns(x, y);
    }
    else
    {
        Nucleus_Status status;
        Nucleus_DecimalInteger *z;
        //
        status = Nucleus_DecimalInteger_clone(&z, y);
        if (status) return status;
        //
        status = Nucleus_DecimalInteger_negate(z);
        if (status) return status;
        //
        status = addSameSigns(x, z);
        Nucleus_DecimalInteger_destroy(z);
        //
        return status;
    }
}

Nucleus_NonNull() static Nucleus_Status
compare
    (
        const Nucleus_DecimalInteger *x,
        const Nucleus_DecimalInteger *y,
        int *r
    )
{
    if (Nucleus_Unlikely(!x || !y || !r)) return Nucleus_Status_InvalidArgument;

    Nucleus_Boolean isZeroX = x->digits[0] == 0 && x->numberOfDigits == 1,
                    isZeroY = y->digits[0] == 0 && y->numberOfDigits == 1;
    
    // If x and y are both 0 then they are equal.
    if (isZeroX && isZeroY)
    {
        *r = 0;
        return Nucleus_Status_Success;
    }

    Nucleus_DecimalInteger_Sign signX = x->sign,
                                signY = y->sign;
    // If an operand is zero, force its sign to 
    if (isZeroX) signX = Nucleus_DecimalInteger_Sign_Plus;
    if (isZeroY) signY = Nucleus_DecimalInteger_Sign_Plus;

    // INV1: At this point x or y are non-zero.
    // At this point INV1 holds.

    // If x has a minus sign and y has a plus sign ...
    if (signX == Nucleus_DecimalInteger_Sign_Minus && signY == Nucleus_DecimalInteger_Sign_Plus)
    {
        // ... then x is negative and y is non-negative.
        // Hence x is smaller than y.
        *r = -1;
        return Nucleus_Status_Success;
    }
    // If x has plus sign and y has a minus sign ...
    if (signX == Nucleus_DecimalInteger_Sign_Plus && signY == Nucleus_DecimalInteger_Sign_Minus)
    {
        // ... then x is non-negative and y is negative.
        // Hence x is greater than y.
        *r = +1;
        return Nucleus_Status_Success;
    }

    // INV2: At this point x and y have the same sign.
    // At this point INV1 and INV2 hold.

    if (x->numberOfDigits > y->numberOfDigits)
    {
        (*r) = +1;
        return Nucleus_Status_Success;
    }
    else if (x->numberOfDigits < y->numberOfDigits)
    {
        (*r) = -1;
        return Nucleus_Status_Success;
    }

    // INV3: The numbe of digits of x and y is equal.
    // At this point INV1, INV2, and INV3 hold.
    for (Nucleus_Size i = x->numberOfDigits; i > 0; --i)
    {
        if (x->digits[i-1] < y->digits[i-1])
        {
            (*r) = -1;
            return Nucleus_Status_Success;
        }
        else if (x->digits[i-1] > y->digits[i-1])
        {
            (*r) = +1;
            return Nucleus_Status_Success;
        }
    }

    (*r) = 0;
    return Nucleus_Status_Success;
}
