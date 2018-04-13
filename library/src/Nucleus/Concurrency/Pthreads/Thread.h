// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux)

#include "Nucleus/Concurrency/Condition.h"
#include "Nucleus/Concurrency/Mutex.h"
#include "Nucleus/Concurrency/Thread.h"
#include <pthread.h>
#include <stdbool.h>

typedef struct Nucleus_Concurrency_ThreadImpl Nucleus_Concurrency_ThreadImpl;

struct Nucleus_Concurrency_ThreadImpl
{
    bool started; ///< @a true if the thread was started, @a false otherwise.
    bool startRequested; ///< @a true if the thread was requested to start, @a false otherwise.
    bool terminationRequested;
    bool terminated;
    Nucleus_Concurrency_Thread_CallbackContext *callbackContext;
    Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction;
    Nucleus_Status status;
    Nucleus_Concurrency_Mutex mutex;
    Nucleus_Concurrency_Condition condition;
    pthread_t thread;
}; // struct Nucleus_Concurrency_ThreadImpl

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_create
    (
        Nucleus_Concurrency_ThreadImpl **thread,
        Nucleus_Concurrency_Thread_CallbackContext *callbackContext,
        Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction
    );

Nucleus_NonNull() void
Nucleus_Concurrency_ThreadImpl_destroy
    (
        Nucleus_Concurrency_ThreadImpl *thread
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_join
    (
        Nucleus_Concurrency_ThreadImpl *thread
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_getStatus
    (
        Nucleus_Concurrency_ThreadImpl *thread,
        Nucleus_Status *status
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_start
    (
        Nucleus_Concurrency_ThreadImpl *thread
    );

#endif
