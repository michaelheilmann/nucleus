// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

// Forward declaration.
typedef struct Nucleus_Concurrency_ThreadImpl Nucleus_Concurrency_ThreadImpl;


typedef void Nucleus_Concurrency_Thread_CallbackContext;

typedef Nucleus_Status (Nucleus_Concurrency_Thread_CallbackFunction)(Nucleus_Concurrency_Thread_CallbackContext *context);


typedef struct Nucleus_Concurrency_Thread Nucleus_Concurrency_Thread;

struct Nucleus_Concurrency_Thread
{
    Nucleus_Concurrency_ThreadImpl *impl;
}; // struct Nucleus_Concurrency_Thread

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_initialize
    (
        Nucleus_Concurrency_Thread *thread,
        Nucleus_Concurrency_Thread_CallbackContext *callbackContext,
        Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction
    );

Nucleus_NonNull() void
Nucleus_Concurrency_Thread_uninitialize
    (
        Nucleus_Concurrency_Thread *thread
    );

/*
 * This function returns immediatly if the thread is not started yet or terminated already.
 */
Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_join
    (
        Nucleus_Concurrency_Thread *thread
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_getStatus
    (
        Nucleus_Concurrency_Thread *thread,
        Nucleus_Status *status
    );

/*
 * The function returns immediatly if the thread started already or terminated already.
 * In the first case `Nucleus_Status_AlreadyStarted` is returned, in the second case `Nucleus_Status_AlreadyStopped` is returned.
 * This function is thread-safe.
 */
Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_start
    (
        Nucleus_Concurrency_Thread *thread
    );
