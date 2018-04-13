// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Concurrency/Condition.h"
#include "Nucleus/Concurrency/Mutex.h"
#include "Nucleus/Concurrency/Thread.h"
#include "Nucleus/IncludesWindows.h"
#include <stdbool.h>

typedef struct Nucleus_Concurrency_ThreadImpl Nucleus_Concurrency_ThreadImpl;

struct Nucleus_Concurrency_ThreadImpl
{
    Nucleus_Concurrency_Thread_CallbackContext *callbackContext;
    Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction;
    Nucleus_Status status;
    HANDLE thread;
    bool started;
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
