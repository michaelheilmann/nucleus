// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"

typedef enum Nucleus_DirectoryEnumerator_State Nucleus_DirectoryEnumerator_State;

enum Nucleus_DirectoryEnumerator_State
{

    Nucleus_DirectoryEnumerator_State_Open,

    Nucleus_DirectoryEnumerator_State_Closed,

}; // enum Nucleus_DirectoryEnumerator_State

#define NUCLEUS_DIRECTORYENUMERATOR(pointer) ((Nucleus_DirectoryEnumerator *)(pointer))
typedef struct Nucleus_DirectoryEnumerator Nucleus_DirectoryEnumerator;

struct Nucleus_DirectoryEnumerator
{
    Nucleus_DirectoryEnumerator_State state;

    Nucleus_Status (*openImpl)(Nucleus_DirectoryEnumerator *self, const char *pathname);

    Nucleus_Status (*closeImpl)(Nucleus_DirectoryEnumerator *self);

    Nucleus_Status (*nextValueImpl)(Nucleus_DirectoryEnumerator *self);

    char *pathname;

}; // struct Nucleus_DirectoryEnumerator

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_construct
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    );

Nucleus_NonNull() void
Nucleus_DirectoryEnumerator_destroy
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_open
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        const char *pathname
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_close
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_hasValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        Nucleus_Boolean *hasValue
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_getValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        const char **bytesOfPathname,
        Nucleus_Size *numberOfBytesInPathname
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_nextValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    );
