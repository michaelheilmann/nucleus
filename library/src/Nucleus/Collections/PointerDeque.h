// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include <stddef.h> // For size_t.

/// @brief A dynamic array of pointers.
typedef struct Nucleus_Collections_PointerDeque Nucleus_Collections_PointerDeque;

struct Nucleus_Collections_PointerDeque
{
    /// @brief A pointer to an array of @a capacity @a (void *) elements.
    void **elements;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    size_t capacity;
    /// @brief The position to read from.
    size_t read;
    /// @brief The number of elements in this array.
    size_t size;
    /// @brief A pointer to the @a Nucleus_LockFunction function or a null pointer.
    Nucleus_LockFunction *lockFunction;
    /// @brief A pointer to the @a Nucleus_UnlockFunction function or  a null pointer.
    Nucleus_UnlockFunction *unlockFunction;
}; // struct Nucleus_Collections_PointerDeque

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerDeque_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_initialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerDeque_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_uninitialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    );

// TODO: Nucleus_Collections_ByteArray and Nucleus_Collections_PointerArray shall provide this function as well.
// TODO: This function shall be documented in
// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_increaseCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_increaseCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t requiredAdditionalCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_ensureFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getSize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_clear
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_append
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_prepend
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_insert
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer,
        size_t index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_at
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t index,
        void **element
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_remove
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        size_t index
    );
