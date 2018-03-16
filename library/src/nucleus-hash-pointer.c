/// @file nucleus-hash-pointer.c
/// @brief Hash functions for pointer values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-hash-pointer.h"

#include <stdint.h>

Nucleus_NoError() Nucleus_Status
Nucleus_hash_pointer_to_unsignedInt
    (
        const void *v,
        unsigned int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (unsigned int)(uintptr_t)v;
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_Status
Nucleus_hash_pointer_to_signedLongLongInt
    (
        const void *v,
        signed long long int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = (signed long long int)(intptr_t)v;
    return Nucleus_Status_Success;
}
