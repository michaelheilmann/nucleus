/// @file nucleus-hash-signedlonglongint.c
/// @brief Hash function for signed long long int values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-hash-signedlonglongint.h"

Nucleus_NoError() Nucleus_Status
Nucleus_hash_signedLongLongInt_to_signedLongLongInt
    (
        const signed long long int v,
        signed long long int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    *hv = v;
    return Nucleus_Status_Success;
}
