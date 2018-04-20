// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

/// @brief A dynamic array of Bytes.
typedef struct Nucleus_Collections_ByteArray Nucleus_Collections_ByteArray;

struct Nucleus_Collections_ByteArray
{
    /// @brief A pointer to an array of @a capacity @a (char) elements.
    char *array;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    Nucleus_Size capacity;
    /// @brief The number of elements in this array.
    Nucleus_Size size;
}; // struct Nucleus_Collections_ByteArray

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_ByteArray_initialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_initialize
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size initialCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_ByteArray_uninitialize.md
Nucleus_NonNull() void
Nucleus_Collections_ByteArray_uninitialize
    (
        Nucleus_Collections_ByteArray *byteArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_increaseCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_increaseCapacity
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size requiredAdditionalCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_ensureFreeCapacity
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_append.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_append
    (
        Nucleus_Collections_ByteArray *byteArray,
        char byte
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_ByteArray_appendMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_appendMany
    (
        Nucleus_Collections_ByteArray *byteArray,
        const char *bytes,
        size_t numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_prepend
    (
        Nucleus_Collections_ByteArray *byteArray,
        char byte
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_ByteArray_prependMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_prependMany
    (
        Nucleus_Collections_ByteArray *byteArray,
        const char *bytes,
        Nucleus_Size numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_insert
    (
        Nucleus_Collections_ByteArray *byteArray,
        char byte,
        Nucleus_Size index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_ByteArray_insertMany.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_insertMany
    (
        Nucleus_Collections_ByteArray *byteArray,
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Size index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_at
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size index,
        char *byte
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_lock
    (
        Nucleus_Collections_ByteArray *byteArray,
        void **bytes,
        Nucleus_Size *numberOfBytes
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_unlock
    (
        Nucleus_Collections_ByteArray *byteArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getSize
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getCapacity
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getFreeCapacity
    (
        Nucleus_Collections_ByteArray *byteArray,
        Nucleus_Size *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_clear
    (
        Nucleus_Collections_ByteArray *byteArray
    );
