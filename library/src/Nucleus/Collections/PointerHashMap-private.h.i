// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Types/HashValue.h"

struct Nucleus_Collections_PointerHashMap_Node
{
    Nucleus_Collections_PointerHashMap_Node *next;
    void *key;
    Nucleus_HashValue hashValue;
    void *value;
}; // struct Nucleus_Collections_PointerHashMap_Node

typedef struct Position
{
    Nucleus_Collections_PointerHashMap_Node *node; // Pointer to the colliding node or a null pointer.
    Nucleus_HashValue hashValue; // The hash value.
    Nucleus_Size hashIndex; // The hash index.
} Position;

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        Position *position
    );

Nucleus_NonNull() static void
clear
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    );
