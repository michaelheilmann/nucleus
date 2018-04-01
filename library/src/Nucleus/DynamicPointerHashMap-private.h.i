// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/DynamicPointerHashMap.h"
#include "Nucleus/Memory.h"

struct Nucleus_DynamicPointerHashMap_Node
{
    Nucleus_DynamicPointerHashMap_Node *next;
    void *key;
    size_t hashValue;
    void *value;
}; // struct Nucleus_DynamicPointerHashMap_Node

typedef struct Position
{
    Nucleus_DynamicPointerHashMap_Node *node; // Pointer to the colliding node or a null pointer.
    unsigned int hashValue; // The hash value.
    unsigned int hashIndex; // The hash index.
} Position;

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap,
        void *key,
        Position *position
    );

Nucleus_NonNull() static void
clear
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap
    );
