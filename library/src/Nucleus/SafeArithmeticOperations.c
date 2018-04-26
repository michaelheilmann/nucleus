// Copyright (c) Michael Heilmann 2018
#include "Nucleus/SafeArithmeticOperations.h"
#include "Nucleus/Configuration.h"

#if defined(Nucleus_Compiler_MSVC)
#include <intrin.h>
#include <stdint.h>
#endif

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddSize
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
#if defined(Nucleus_Compiler_Clang) || defined(Nucleus_Compiler_GCC)
    // __builti_add_overflow returns false on success.
    Nucleus_Size u;
    if (!__builtin_add_overflow(x, y, &u))
    {
        *z = u;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#elif defined(Nucleus_Compiler_MSVC)
    if (SIZE_MAX - x > y)
    {
        *z = x + y;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#else
    if (!Nucleus_Unlikely((y > 0) && x > (SIZE_MAX / y)))
    {
        *z = x * y;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#endif
}

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeMulSize
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
#if defined(Nucleus_Compiler_Clang) || defined(Nucleus_Compiler_GCC)
    // __builti_mul_overflow returns false on success.
    Nucleus_Size u;
    if (!__builtin_mul_overflow(x, y, &u))
    {
        *z = u;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#elif defined(Nucleus_Compiler_MSVC)
#if defined(_WIN64)
    Nucleus_Size l, h;
    l = _umul128(x, y, &h);
    if (!h)
    {
        *z = l;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#else
    static const uint64_t mask = 0xffffffff00000000Ui64; // Mask for the high 32 high Bits.
    uint64_t w = x *y;
    if (0Ui64 == (w & mask)) // If the high 32 bits are non-zero, then an overflow occurred.
    {
        *z = (uint32_t)w;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#endif
#else
    if (!Nucleus_Unlikely((y > 0) && x > (SIZE_MAX / y)))
    {
        *z = x * y;
        return Nucleus_Status_Success;
    }
    return Nucleus_Status_Overflow;
#endif
}

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger8
    (
        Nucleus_Integer8 x,
        Nucleus_Integer8 y,
        Nucleus_Integer8 *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
    Nucleus_Integer16 w = x + y;
    if (w < Nucleus_Integer8_Least || w > Nucleus_Integer8_Greatest)
    { return Nucleus_Status_Overflow; }
    *z = (Nucleus_Integer8)w;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger16
    (
        Nucleus_Integer16 x,
        Nucleus_Integer16 y,
        Nucleus_Integer16 *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
    Nucleus_Integer32 w = x + y;
    if (w < Nucleus_Integer16_Least || w > Nucleus_Integer16_Greatest)
    { return Nucleus_Status_Overflow; }
    *z = (Nucleus_Integer16)w;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger32
    (
        Nucleus_Integer32 x,
        Nucleus_Integer32 y,
        Nucleus_Integer32 *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
    Nucleus_Integer64 w = x + y;
    if (w < Nucleus_Integer32_Least || w > Nucleus_Integer32_Greatest)
    { return Nucleus_Status_Overflow; }
    *z = (Nucleus_Integer32)w;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger64
    (
        Nucleus_Integer64 x,
        Nucleus_Integer64 y,
        Nucleus_Integer64 *z
    )
{
    if (Nucleus_Unlikely(!z)) return Nucleus_Status_InvalidArgument;
    // x + y can not overflow/underflow if one of the statements below is true:
    // - x and/or y are 0
    // - x and y are both not 0 and have different signs
    if ((x == 0 || y == 0) || (x < 0 && y > 0) || (x > 0 && y < 0))
    {
        *z = x + y;
        return Nucleus_Status_Success;
    }
    // Invariant: x != 0, y != 0, sgn(x) == sgn(y)
    // If x and y are both not 0 and have the same sign, then they might overflow.
    if (x < 0 /*&& y < 0*/)
    {
        // An underflow occurs iff x + y < LEAST iff x < LEAST - y.
        // LEAST - y can not overflow/underflow as 0 > y >= LEAST.
        if (x < Nucleus_Integer64_Least - y)
        {
            return Nucleus_Status_Overflow;
        }
        *z = x + y;
        return Nucleus_Status_Success;
    }
    else /*if (x > 0 && y > 0)*/
    {
        // An overflow occurs iff x + y < GREATEST iff x > GREATEST - y.
        // GREATEST - y can not overflow/underflow as GREATEST >= y > 0.
        if (x > Nucleus_Integer64_Greatest - y)
        {
            return Nucleus_Status_Overflow;
        }
        *z = x + y;
        return Nucleus_Status_Success;
    }
}
