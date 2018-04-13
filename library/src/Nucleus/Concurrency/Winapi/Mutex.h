// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Concurrency/Mutex.h"
#include "Nucleus/IncludesWindows.h"

typedef struct Nucleus_Concurrency_MutexImpl Nucleus_Concurrency_MutexImpl;

struct Nucleus_Concurrency_MutexImpl
{
    Nucleus_Concurrency_Mutex parent;
    SRWLOCK srwLock;
}; // struct Nucleus_Concurrency_MutexImpl

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_create
    (
        Nucleus_Concurrency_MutexImpl **mutex
    );

Nucleus_NonNull() void
Nucleus_Concurrency_MutexImpl_destroy
    (
        Nucleus_Concurrency_MutexImpl *mutex
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_lock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_unlock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    );

#endif
