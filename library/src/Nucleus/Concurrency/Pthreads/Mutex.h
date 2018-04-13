// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux)

#include "Nucleus/Concurrency/Mutex.h"
#include <pthread.h>

typedef struct Nucleus_Concurrency_MutexImpl Nucleus_Concurrency_MutexImpl;

struct Nucleus_Concurrency_MutexImpl
{
    Nucleus_Concurrency_Mutex parent;
    pthread_mutex_t mutex;
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
