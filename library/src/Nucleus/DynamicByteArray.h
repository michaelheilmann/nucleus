// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include <stddef.h> // For size_t.

/// @brief A dynamic array of Bytes.
typedef struct Nucleus_DynamicByteArray Nucleus_DynamicByteArray;

struct Nucleus_DynamicByteArray
{
    /// @brief A pointer to an array of @a capacity @a (char) elements.
    char *array;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    size_t capacity;
    /// @brief The number of elements in this array.
    size_t size;
}; // struct Nucleus_DynamicByteArray

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_initialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_initialize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t initialCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_uninitialize.md
Nucleus_NonNull() void
Nucleus_DynamicByteArray_uninitialize
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_ensureFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_append.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_append
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_appendMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_appendMany
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_prepend.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_prepend
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_prependMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_prependMany
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_insert.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_insert
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte,
        size_t index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_insertMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_insertMany
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_at
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t index,
        char *byte
    );

/// @ingroup dl
Nucleus_NonNull() const char *
Nucleus_DynamicByteArray_getBytes
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getSize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_clear
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );
