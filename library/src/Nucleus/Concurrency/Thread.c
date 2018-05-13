// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Concurrency/Thread.h"

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Pthreads/Thread.h"
#elif defined(Nucleus_Platform_Windows) && !defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Winapi/Thread.h"
#else
    #error("platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_initialize
    (
        Nucleus_Concurrency_Thread *thread,
        Nucleus_Concurrency_Thread_CallbackContext *callbackContext,
        Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction
    )
{
    if (Nucleus_Unlikely(!thread || !callbackFunction)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    status = Nucleus_Concurrency_ThreadImpl_create(&(thread->impl), callbackContext, callbackFunction);
    if (Nucleus_Unlikely(status)) return status;
    return status;
}

Nucleus_NonNull() void
Nucleus_Concurrency_Thread_uninitialize
    (
        Nucleus_Concurrency_Thread *thread
    )
{
    Nucleus_Concurrency_ThreadImpl_destroy(thread->impl);
    thread->impl = NULL;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_join
    (
        Nucleus_Concurrency_Thread *thread
    )
{
    if (Nucleus_Unlikely(!thread)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ThreadImpl_join(thread->impl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_getStatus
    (
        Nucleus_Concurrency_Thread *thread,
        Nucleus_Status *status
    )
{
    if (Nucleus_Unlikely(!thread)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ThreadImpl_getStatus(thread->impl, status);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Thread_start
    (
        Nucleus_Concurrency_Thread *thread
    )
{
    if (Nucleus_Unlikely(!thread)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ThreadImpl_start(thread->impl);
}
