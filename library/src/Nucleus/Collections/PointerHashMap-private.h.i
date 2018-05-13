// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus/Memory.h"

struct Nucleus_Collections_PointerHashMap_Node
{
    Nucleus_Collections_PointerHashMap_Node *next;
    void *key;
    size_t hashValue;
    void *value;
}; // struct Nucleus_Collections_PointerHashMap_Node

typedef struct Position
{
    Nucleus_Collections_PointerHashMap_Node *node; // Pointer to the colliding node or a null pointer.
    unsigned int hashValue; // The hash value.
    unsigned int hashIndex; // The hash index.
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
