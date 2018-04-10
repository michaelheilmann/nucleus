// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include <stddef.h> // For size_t.

/// @brief A dynamic array of pointers.
typedef struct Nucleus_Collections_PointerArray Nucleus_Collections_PointerArray;

struct Nucleus_Collections_PointerArray
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
}; // struct Nucleus_Collections_PointerArray

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerArray_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_initialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerArray_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_uninitialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_ensureFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_append
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_prepend
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_insert
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer,
        size_t index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_at
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t index,
        void **pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getSize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_clear
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    );
