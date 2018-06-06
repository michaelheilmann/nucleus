// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include "Nucleus/Types/Size.h"

/// @brief A dynamic array of pointers.
typedef struct Nucleus_Collections_PointerDeque Nucleus_Collections_PointerDeque;

struct Nucleus_Collections_PointerDeque
{
    /// @brief A pointer to an array of @a capacity @a (void *) elements.
    void **elements;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    Nucleus_Size capacity;
    /// @brief The position to read from.
    Nucleus_Size read;
    /// @brief The number of elements in this array.
    Nucleus_Size size;
    /// @brief A pointer to the @a Nucleus_LockFunction function or a null pointer.
    Nucleus_LockFunction *lockFunction;
    /// @brief A pointer to the @a Nucleus_UnlockFunction function or  a null pointer.
    Nucleus_UnlockFunction *unlockFunction;
}; // struct Nucleus_Collections_PointerDeque

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerDeque_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_initialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerDeque_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_uninitialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    );

// TODO: Nucleus_Collections_ByteArray and Nucleus_Collections_PointerArray shall provide this function as well.
// TODO: This function shall be documented in
// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_increaseCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_increaseCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size requiredAdditionalCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_ensureFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size requiredFreeCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getSize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *size
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *capacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *freeCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_clear
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_append
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_prepend
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_insert
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer,
        Nucleus_Size index
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_at
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size index,
        void **element
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_remove
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size index
    );
