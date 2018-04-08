// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"

/// @ingroup Hash
/// @brief Compute the hash value of a pointer value.
/// @param v a pointer value which can also be a null pointer value
/// @param [out] hv a pointer to an @a (Nucleus_HashValue) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a v value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hashPointer
    (
        const void *v,
        Nucleus_HashValue *hv
    );
