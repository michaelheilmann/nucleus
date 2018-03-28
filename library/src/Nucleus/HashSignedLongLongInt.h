/// @file Nucleus/HashSignedLongLongInt.h
/// @brief Hash function for signed long long int values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup Hash
/// @brief Compute the hash value of a @a (signed long long int) value.
/// @param v a pointer which can also be a null pointer
/// @param [out] hv a pointer to an @a (signed long long int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a v value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hash_signedLongLongInt_to_signedLongLongInt
    (
        const signed long long int v,
        signed long long int *hv
    );
