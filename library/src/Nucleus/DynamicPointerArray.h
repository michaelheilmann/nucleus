// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections.h"
#include <stddef.h> // For size_t.

/// @brief A dynamic array of pointers.
typedef struct Nucleus_DynamicPointerArray Nucleus_DynamicPointerArray;

struct Nucleus_DynamicPointerArray
{
    /// @brief A pointer to an array of @a capacity @a (void *) elements.
    void **elements;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    size_t capacity;
    /// @brief The number of elements in this array. 
    size_t size;
    /// @brief A pointer to the @a Nucleus_LockFunction function or a null pointer.
    Nucleus_LockFunction *lockFunction;
    /// @brief A pointer to the @a Nucleus_UnlockFunction function or  a null pointer.
    Nucleus_UnlockFunction *unlockFunction;
}; // struct Nucleus_DynamicPointerArray

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_initialize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_uninitialize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray
    );

/// @brief Ensure the free capacity of a @a (Nucleus_DynamicPointerArray) is greater than or equal a required free capacity.
/// @param dynamicPointerArray a pointer to an initialized @a (Nucleus_DynamicPointerArray) object
/// @param requiredFreeCapacity the required free capacity
/// @details The free capacity of the @a (Nucleus_DynamicPointerArray) object pointed to by @a (dynamicPointerArray) is greater than or
/// equal to the required free capacity @a requiredFreeCapacity on success and #Nucleus_Status_Success is returned.
/// On error, one of the non-zero status codes below is returned:
/// - `Nucleus_Status_InvalidArgument`: ``dynamicPointerArray` is a null pointer
/// - `Nucleus_Status_AllocationFailed`: an allocation failed
/// - `Nucleus_Status_Overflow`: the required free capacity `requiredFreeCapacity` is too big
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_ensureFreeCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_append
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_prepend
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_insert
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer,
        size_t index
    );

/// @ingroup dl
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_at
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t index,
        void **pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getSize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getFreeCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerArray_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_clear
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray
    );