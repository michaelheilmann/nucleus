// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Types/HashValue.h"

struct Node
{
    Node *next;
    void *key;
    Nucleus_HashValue hashValue;
    void *value;
}; // struct Node

typedef struct ExtendedPosition
{
	Node **previous; // Pointr to the predecessor of the colliding node or a null pointer.
    Node *current; // Pointer to the colliding node or a null pointer.
    Nucleus_HashValue hashValue; // The hash value.
    Nucleus_Size hashIndex; // The hash index.
} ExtendedPosition;

typedef struct Position
{
    Node *current; // Pointer to the colliding node or a null pointer.
    Nucleus_HashValue hashValue; // The hash value.
    Nucleus_Size hashIndex; // The hash index.
} Position;

Nucleus_NonNull() static Nucleus_Status
getExtendedPosition
	(
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        ExtendedPosition *position
	);

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        Position *position
    );

Nucleus_NonNull() static void
clear
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap
    );
    

