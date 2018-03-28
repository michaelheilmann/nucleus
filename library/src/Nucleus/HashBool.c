/// @file Nucleus/HashBool.h
/// @brief Hash function for bool values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "Nucleus/HashBool.h"

Nucleus_NoError() Nucleus_Status
Nucleus_hash_bool_to_signedLongLongInt
    (
        const bool v,
        signed long long int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = v ? 1231 : 1237; // These are arbitrary prime number as e.g. used in Boolean.getHashCode in Java.
    return Nucleus_Status_Success;
}
