/// @file nucleus-hash-bool.h
/// @brief Hash function for bool values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once

#include <stdbool.h>

#include "nucleus-annotations.h"
#include "nucleus-status.h"

/// @ingroup Hash
/// @brief Compute the hash value of a @a (bool) value.
/// @param v a @a (bool) value
/// @param [out] hv a pointer to an @a (signed long long int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a v value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hash_bool_to_signedLongLongInt
    (
        const bool v,
        signed long long int *hv
    );