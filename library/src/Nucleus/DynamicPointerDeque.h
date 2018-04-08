// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections.h"
#include <stddef.h> // For size_t.

/// @brief A dynamic array of pointers.
typedef struct Nucleus_DynamicPointerDeque Nucleus_DynamicPointerDeque;

struct Nucleus_DynamicPointerDeque
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
}; // struct Nucleus_DynamicPointerDeque

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerDeque_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerDeque_initialize
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerDeque_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_uninitialize
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque
    );

// TODO: Nucleus_DynamicByteArray and Nucleus_DynamicPointerArray shall provide this function as well.
// TODO: This function shall be documented in
// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_increaseCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_increaseCapacity
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t requiredAdditionalCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_ensureFreeCapacity
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t requiredFreeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_getSize
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t *size
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_getCapacity
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t *capacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_getFreeCapacity
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t *freeCapacity
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_clear
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerDeque_append
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerDeque_prepend
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerDeque_insert
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        void *pointer,
        size_t index
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Dynamic[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerDeque_at
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t index,
        void **element
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerDeque_remove
    (
        Nucleus_DynamicPointerDeque *dynamicPointerDeque,
        size_t index
    );
