// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux)

#include "Nucleus/Concurrency/Condition.h"
#include <pthread.h>

// Forward declaration.
typedef struct Nucleus_Concurrency_MutexImpl Nucleus_Concurrency_MutexImpl;

typedef struct Nucleus_Concurrency_ConditionImpl Nucleus_Concurrency_ConditionImpl;

struct Nucleus_Concurrency_ConditionImpl
{
    pthread_cond_t condition;
}; // Nucleus_Concurrency_ConditionImpl

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ConditionImpl_create
    (
        Nucleus_Concurrency_ConditionImpl **condition
    );

Nucleus_NonNull() void
Nucleus_Concurrency_ConditionImpl_destroy
    (
        Nucleus_Concurrency_ConditionImpl *condition
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ConditionImpl_wait
    (
        Nucleus_Concurrency_ConditionImpl *condition,
        Nucleus_Concurrency_MutexImpl *mutex
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ConditionImpl_signalOne
    (
        Nucleus_Concurrency_ConditionImpl *condition
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ConditionImpl_signalAll
    (
        Nucleus_Concurrency_ConditionImpl *condition
    );

#endif
