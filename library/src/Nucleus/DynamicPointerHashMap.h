// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include <stddef.h> // For size_t.
#include "Nucleus/Collections.h"

typedef struct Nucleus_DynamicPointerHashMap_Node Nucleus_DynamicPointerHashMap_Node;

typedef struct Nucleus_DynamicPointerHashMap Nucleus_DynamicPointerHashMap;
struct Nucleus_DynamicPointerHashMap
{
    Nucleus_DynamicPointerHashMap_Node **buckets;
    size_t size, capacity;
    Nucleus_DynamicPointerHashMap_Node *unused;

    Nucleus_LockFunction *lockKeyFunction;
    Nucleus_UnlockFunction *unlockKeyFunction;
    Nucleus_HashFunction *hashKeyFunction;
    Nucleus_EqualToFunction *keyEqualToKeyFunction;

    Nucleus_LockFunction *lockValueFunction;
    Nucleus_UnlockFunction *unlockValueFunction;

}; // struct Nucleus_DynamicPointerHashMap

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerHashMap_initialize.md
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerHashMap_initialize
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap,
        size_t initialCapacity,
        Nucleus_LockFunction *lockKeyFunction,
        Nucleus_UnlockFunction *unlockKeyFunction,
        Nucleus_HashFunction *hashKeyFunction,
        Nucleus_EqualToFunction *keyEqualToKeyFunction,
        Nucleus_LockFunction *lockValueFunction,
        Nucleus_UnlockFunction *unlockValueFunction
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_DynamicPointerHashMap_uninitialize.md
Nucleus_NonNull() void
Nucleus_DynamicPointerHashMap_uninitialize
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerHashMap_set
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap,
        void *key,
        void *value,
        bool replace
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerHashMap_get
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap,
        void *key,
        void **value
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerHashMap_clear
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap
    );
