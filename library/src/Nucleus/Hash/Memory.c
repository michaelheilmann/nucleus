// Copyright (c) 2017, 2018 Michael Heilmann
#include "Nucleus/Hash/Memory.h"

Nucleus_NoError() Nucleus_NonNull(1) static unsigned int 
hash1
    (
        const char *p,
        Nucleus_Size l
    );

Nucleus_NoError() Nucleus_NonNull(1) static unsigned int 
hash1
    (
        const char *p,
        Nucleus_Size l
    )
{
    unsigned int h = (unsigned int)l;
    size_t step = (l >> 5) + 1;
    for (; l >= step; l -= step)
        h ^= (h << 5) + (h >> 2) + ((unsigned char)(p[l - 1]));
    return h;
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashMemory
    (
        const void *p,
        Nucleus_Size n,
        Nucleus_HashValue *hv
    )
{
    if (!p || !hv) return Nucleus_Status_InvalidArgument;
    *hv = hash1(p, n);    
    return Nucleus_Status_Success;
}
