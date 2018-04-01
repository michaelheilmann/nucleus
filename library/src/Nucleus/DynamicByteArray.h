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

/// @brief Ensure the free capacity of a @a (Nucleus_DynamicByteArray) is greater than or equal a required free capacity.
/// @param dynamicByteArray a pointer to an initialized @a (Nucleus_DynamicByteArray) object
/// @param requiredFreeCapacity the required free capacity
/// @details The free capacity of the @a (Nucleus_DynamicByteArray) object pointed to by @a (dynamicByteArray) is greater than or
/// equal to the required free capacity @a requiredFreeCapacity on success and #Nucleus_Status_Success is returned.
/// On error, one of the non-zero status codes below is returned:
/// - `Nucleus_Status_InvalidArgument`: `dynamicByteArray` is a null pointer
/// - `Nucleus_Status_AllocationFailed`: an allocation failed
/// - `Nucleus_Status_Overflow`: the required free capacity `requiredFreeCapacity` is too big
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_ensureFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_append.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_append
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_prepend.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_prepend
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_insert.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_insert
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    );

/// @ingroup dl
Nucleus_NonNull() const char *
Nucleus_DynamicByteArray_getBytes
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getSize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicByteArray_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_clear
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );
