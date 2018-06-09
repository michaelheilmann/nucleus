// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"

typedef struct Node Node;

typedef struct Nucleus_Collections_PointerHashMap Nucleus_Collections_PointerHashMap;
struct Nucleus_Collections_PointerHashMap
{
    Node **buckets;
    Nucleus_Size size, capacity;
    Node *unused;

    Nucleus_LockFunction *lockKeyFunction;
    Nucleus_UnlockFunction *unlockKeyFunction;
    Nucleus_HashFunction *hashKeyFunction;
    Nucleus_EqualToFunction *keyEqualToKeyFunction;

    Nucleus_LockFunction *lockValueFunction;
    Nucleus_UnlockFunction *unlockValueFunction;

}; // struct Nucleus_Collections_PointerHashMap

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerHashMap_initialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_initialize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockKeyFunction,
        Nucleus_UnlockFunction *unlockKeyFunction,
        Nucleus_HashFunction *hashKeyFunction,
        Nucleus_EqualToFunction *keyEqualToKeyFunction,
        Nucleus_LockFunction *lockValueFunction,
        Nucleus_UnlockFunction *unlockValueFunction
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_PointerHashMap_uninitialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_uninitialize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerHashMap_set
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        void *value,
        Nucleus_Boolean replace
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_get
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        void **value
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_clear
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Collection-Type]_getSize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getSize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size *size
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getCapacity
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size *capacity
    );

typedef struct Nucleus_Collections_PointerHashMap_Enumerator Nucleus_Collections_PointerHashMap_Enumerator;

struct Nucleus_Collections_PointerHashMap_Enumerator
{
    Nucleus_Collections_PointerHashMap *source;
    Nucleus_Size bucketIndex;
    Node *node;
}; // struct Nucleus_Collections_PointerHashMap_Enumerator

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_initialize
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        Nucleus_Collections_PointerHashMap *source
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_uninitialize
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_next
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_hasValue
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        Nucleus_Boolean *hasValue
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_getValue
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        void **key,
        void **value
    );
