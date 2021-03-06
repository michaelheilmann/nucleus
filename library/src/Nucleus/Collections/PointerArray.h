// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include "Nucleus/Types/Size.h"

/// @brief A dynamic array of pointers.
typedef struct Nucleus_Collections_PointerArray Nucleus_Collections_PointerArray;

struct Nucleus_Collections_PointerArray
{
    /// @brief A pointer to an array of @a capacity @a (void *) elements.
    void **elements;
    /// @brief The capacity, in elements, of the array pointed to by @a array.
    Nucleus_Size capacity;
    /// @brief The number of elements in this array.
    Nucleus_Size size;
    /// @brief A pointer to the @a Nucleus_LockFunction function or a null pointer.
    Nucleus_LockFunction *lockFunction;
    /// @brief A pointer to the @a Nucleus_UnlockFunction function or  a null pointer.
    Nucleus_UnlockFunction *unlockFunction;
}; // struct Nucleus_Collections_PointerArray

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerArray_initialize.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_initialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerArray_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_uninitialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_increaseCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_increaseCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size requiredAdditionalCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_ensureFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size requiredFreeCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_append.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_append
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_prepend
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_insert
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer,
        Nucleus_Size index
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_at.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_at
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size index,
        void **pointer
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getSize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *size
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *capacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *freeCapacity
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Collection-Type]_clear.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_clear
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    );

typedef struct Nucleus_Collections_PointerArray_Enumerator Nucleus_Collections_PointerArray_Enumerator;

struct Nucleus_Collections_PointerArray_Enumerator
{
    Nucleus_Collections_PointerArray *source;
    Nucleus_Size index;
}; // struct Nucleus_Collections_PointerArray_Enumerator

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_initialize
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        Nucleus_Collections_PointerArray *source
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_uninitialize
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_nextValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_hasValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        Nucleus_Boolean *hasValue
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_getValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        void **value
    );
