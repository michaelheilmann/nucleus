#include "nucleus-safe-arithmetic-operations.h"
#include "nucleus-config.h"

#if defined(Nucleus_Compiler_MSVC)
#include <intrin.h>
#include <stdint.h>
#endif

Nucleus_NonNull(3) bool
Nucleus_safeAdd
    (
        size_t x,
        size_t y,
        size_t *z
    )
{
#if defined(Nucleus_Compiler_Clang) || defined(Nucleus_Compiler_GCC)
    // __builti_add_overflow returns false on success.
    size_t u;
    if (!__builtin_add_overflow(x, y, &u))
    {
        *z = u;
        return true;
    }
    return false;
#elif defined(Nucleus_Compiler_MSVC)
    if (SIZE_MAX - x > y)
    {
        *z = x + y;
        return true;
    }
    return false;
#else
    if (!Nucleus_Unlikely((y > 0) && x > (SIZE_MAX / y)))
    {
        *z = x * y;
        return true;
    }
    return false;
#endif
}

Nucleus_NonNull(3) bool
Nucleus_safeMul
    (
        size_t x,
        size_t y,
        size_t *z
    )
{
#if defined(Nucleus_Compiler_Clang) || defined(Nucleus_Compiler_GCC)
    // __builti_mul_overflow returns false on success.
    size_t u;
    if (!__builtin_mul_overflow(x, y, &u))
    {
        *z = u;
        return true;
    }
    return false;
#elif defined(Nucleus_Compiler_MSVC)
#if defined(_WIN64)
    size_t l, h;
    l = _umul128(x, y, &h);
    if (!h)
    {
        *z = l;
        return true;
    }
    return false;
#else
    static const uint64_t mask = 0xffffffff00000000Ui64; // Mask for the high 32 high Bits.
    uint64_t w = x *y;
    if (0Ui64 == (w & mask)) // If the high 32 bits are non-zero, then an overflow occurred.
    {
        *z = (uint32_t)w;
        return true;
    }
    return false;
#endif
#else
    if (!Nucleus_Unlikely((y > 0) && x > (SIZE_MAX / y)))
    {
        *z = x * y;
        return true;
    }
    return false;
#endif
}
