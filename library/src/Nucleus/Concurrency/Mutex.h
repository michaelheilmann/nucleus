// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

// Forward declaration.
typedef struct Nucleus_Concurrency_MutexImpl Nucleus_Concurrency_MutexImpl;

typedef struct Nucleus_Concurrency_Mutex Nucleus_Concurrency_Mutex;
struct Nucleus_Concurrency_Mutex
{
    Nucleus_Concurrency_MutexImpl *impl;
}; // struct Nucleus_Concurrency_Mutex

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_initialize
    (
        Nucleus_Concurrency_Mutex *mutex
    );

Nucleus_NonNull() void
Nucleus_Concurrency_Mutex_uninitialize
    (
        Nucleus_Concurrency_Mutex *mutex
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_lock
    (
        Nucleus_Concurrency_Mutex *mutex
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_unlock
    (
        Nucleus_Concurrency_Mutex *mutex
    );
