// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include <stddef.h> // For size_t.

typedef struct Nucleus_Collections_PointerHashMap_Node Nucleus_Collections_PointerHashMap_Node;

typedef struct Nucleus_Collections_PointerHashMap Nucleus_Collections_PointerHashMap;
struct Nucleus_Collections_PointerHashMap
{
    Nucleus_Collections_PointerHashMap_Node **buckets;
    size_t size, capacity;
    Nucleus_Collections_PointerHashMap_Node *unused;

    Nucleus_LockFunction *lockKeyFunction;
    Nucleus_UnlockFunction *unlockKeyFunction;
    Nucleus_HashFunction *hashKeyFunction;
    Nucleus_EqualToFunction *keyEqualToKeyFunction;

    Nucleus_LockFunction *lockValueFunction;
    Nucleus_UnlockFunction *unlockValueFunction;

}; // struct Nucleus_Collections_PointerHashMap

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerHashMap_initialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_initialize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        size_t initialCapacity,
        Nucleus_LockFunction *lockKeyFunction,
        Nucleus_UnlockFunction *unlockKeyFunction,
        Nucleus_HashFunction *hashKeyFunction,
        Nucleus_EqualToFunction *keyEqualToKeyFunction,
        Nucleus_LockFunction *lockValueFunction,
        Nucleus_UnlockFunction *unlockValueFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_Collections_PointerHashMap_uninitialize.md
Nucleus_NonNull() void
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
        bool replace
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
