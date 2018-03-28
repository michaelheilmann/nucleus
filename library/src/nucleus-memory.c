/// @file nucleus-memory.c
/// @brief Allocation and deallocation or memory blocks, valuation and manipulation of memory blocks and their contents
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-memory.h"

#include "nucleus-config.h"
#include "nucleus-safe-arithmetic-operations.h"
#include <malloc.h>
#include <memory.h>

/// @brief Get if two memory blocks overlap.
/// @param a pointers to the first Byte of the first memory block
/// @param b pointer to the first Byte of the second memory block
/// @param n the size of the memory block prefixes
Nucleus_NoError() Nucleus_NonNull(1, 2) static bool
overlapping
    (
        const void *a,
        const void *b,
        size_t n
    )
{
    const char *x = a, *y =  b;
    return (x <= y && x + n > y) || (y <= x && y + n > x);
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
    (
        void **p,
        size_t n
    )
{
    if (!p) return Nucleus_Status_InvalidArgument;
    void *q = malloc(n > 0 ? n : 1);
    if (!q) return Nucleus_Status_AllocationFailed;
    *p = q;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
    (
        void **p,
        size_t n,
        size_t m
    )
{
    size_t k;
    if (!Nucleus_safeMul(n, m, &k)) return Nucleus_Status_Overflow;
    return Nucleus_allocateMemory(p, k);
}

Nucleus_NoError() void
Nucleus_deallocateMemory
    (
        void *p
    )
{
    free(p);
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillMemory
    (
        void *p,
        int v,
        size_t n
    )
{
    if (!p) return Nucleus_Status_InvalidArgument;
    memset(p, v, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillArrayMemory
    (
        void *p,
        int v,
        size_t n,
        size_t m
    )
{
    size_t k;
    if (!Nucleus_safeMul(n, m, &k)) return Nucleus_Status_Overflow;
    return Nucleus_fillMemory(p, v, k);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        size_t n
    )
{
    if (!p || !q) return Nucleus_Status_InvalidArgument;
    if (overlapping(p, q, n)) memmove(p, q, n);
    else memcpy(p, q, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
    (
        void *p,
        const void *q,
        size_t n,
        size_t m
    )
{
    size_t k;
    if (!Nucleus_safeMul(n, m, &k)) return Nucleus_Status_Overflow;
    return Nucleus_copyMemory(p, q, k);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
    (
        const void *p,
        const void *q,
        size_t n,
        bool *r
    )
{
    if (!p || !q || !r) return Nucleus_Status_InvalidArgument;
    *r = !memcmp(p, q, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
    (
        const void *p,
        const void *q,
        size_t n,
        size_t m,
        bool *r
    )
{
    size_t k;
    if (!Nucleus_safeMul(n, m, &k)) return Nucleus_Status_Overflow;
    return Nucleus_compareMemory(p, q, k, r);
}

Nucleus_NoError() Nucleus_NonNull(1) static unsigned int 
hash1(const char *p, size_t l)
{
    unsigned int h = (unsigned int)l;
    size_t step = (l >> 5) + 1;
    for (; l >= step; l -= step)
        h ^= (h << 5) + (h >> 2) + ((unsigned char)(p[l - 1]));
    return h;
}

/// @todo Make a qualified decision when selecting the hash function.
///       Nothing is known about the current hash function.
Nucleus_NoError() Nucleus_NonNull(1, 3) Nucleus_Status
Nucleus_hashMemory
    (
        const void *p,
        size_t n,
        unsigned int *hv
    )
{
    if (!p || !hv) return Nucleus_Status_InvalidArgument;
    *hv = hash1(p, n);    
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 4) Nucleus_Status
Nucleus_hashArrayMemory
    (
        const void *p,
        size_t n,
        size_t m,
        unsigned int *hv
    )
{
    size_t k;
    if (!Nucleus_safeMul(n, m, &k)) return Nucleus_Status_Overflow;
    return Nucleus_hashMemory(p, k, hv);
}
