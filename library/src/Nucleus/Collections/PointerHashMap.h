// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Collections/Callbacks.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"

typedef struct Nucleus_Collections_PointerHashMap_Node Nucleus_Collections_PointerHashMap_Node;

typedef struct Nucleus_Collections_PointerHashMap Nucleus_Collections_PointerHashMap;
struct Nucleus_Collections_PointerHashMap
{
    Nucleus_Collections_PointerHashMap_Node **buckets;
    Nucleus_Size size, capacity;
    Nucleus_Collections_PointerHashMap_Node *unused;

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
