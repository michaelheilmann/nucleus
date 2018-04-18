// Copyright (c) Michael Heilmann 2018
#include "Nucleus/SafeArithmeticOperations.h"
#include "Nucleus/Configuration.h"

#if defined(Nucleus_Compiler_MSVC)
#include <intrin.h>
#include <stdint.h>
#endif

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAdd
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
Nucleus_safeMul
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
