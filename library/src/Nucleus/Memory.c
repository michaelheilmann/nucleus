/// @file Nucleus/Memory.c
/// @brief Allocation and deallocation or memory blocks, valuation and manipulation of memory blocks and their contents
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "Nucleus/Memory.h"

#include "Nucleus/Configuration.h"
#include "Nucleus/SafeArithmeticOperations.h"
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    #include <stdlib.h>
#else
    #include <malloc.h>
#endif
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
        Nucleus_Size n
    )
{
    const char *x = a, *y =  b;
    return (x <= y && x + n > y) || (y <= x && y + n > x);
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
    (
        void **p,
        Nucleus_Size n
    )
{
    if (Nucleus_Unlikely(!p)) return Nucleus_Status_InvalidArgument;
    void *q = malloc(n > 0 ? n : 1);
    if (!q) return Nucleus_Status_AllocationFailed;
    *p = q;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateMemory
    (
        void **p,
        Nucleus_Size n
    )
{
    if (Nucleus_Unlikely(!p || !*p)) return Nucleus_Status_InvalidArgument;
    void *q = realloc(*p, n > 0 ? n : 1);
    if (Nucleus_Unlikely(!q)) return Nucleus_Status_AllocationFailed;
    *p = q;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
    (
        void **p,
        Nucleus_Size n,
        Nucleus_Size m
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (Nucleus_Unlikely(status)) return status;
    return Nucleus_allocateMemory(p, k);
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateArrayMemory
    (
        void **p,
        Nucleus_Size n,
        Nucleus_Size m
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (Nucleus_Unlikely(status)) return status;
    return Nucleus_reallocateMemory(p, k);
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
        Nucleus_Size n
    )
{
    if (Nucleus_Unlikely(!p)) return Nucleus_Status_InvalidArgument;
    memset(p, v, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillArrayMemory
    (
        void *p,
        int v,
        Nucleus_Size n,
        Nucleus_Size m
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (Nucleus_Unlikely(status)) return status;
    return Nucleus_fillMemory(p, v, k);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n
    )
{
    if (Nucleus_Unlikely(!p || !q)) return Nucleus_Status_InvalidArgument;
    if (n == 0) return Nucleus_Status_Success;
    if (overlapping(p, q, n))
    {
        memmove(p, q, n);
    }
    else
    {
        memcpy(p, q, n);
    }
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    )
{
    if (Nucleus_Unlikely(!p || !q)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!n || !m)) return Nucleus_Status_Success;
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (status) status;
    return Nucleus_copyMemory(p, q, k);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
    (
        const void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Boolean *r
    )
{
    if (Nucleus_Unlikely(!p || !q || !r)) return Nucleus_Status_InvalidArgument;
    *r = !memcmp(p, q, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
    (
        const void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m,
        Nucleus_Boolean *r
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (Nucleus_Unlikely(status)) return status;
    return Nucleus_compareMemory(p, q, k, r);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_cloneMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n
     )
{
    if (Nucleus_Unlikely(!p || !q)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_allocateMemory(p, n);
    if (Nucleus_Unlikely(status)) return status;
    memcpy(*p, q, n);
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_cloneArrayMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    )
{
    Nucleus_Size k;
    Nucleus_Status status = Nucleus_safeMulSize(n, m, &k);
    if (Nucleus_Unlikely(status)) return status;
    return Nucleus_cloneMemory(p, q, k);
}
