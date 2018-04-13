// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Concurrency/Pthreads/Thread.h"

#if defined(Nucleus_Platform_Linux)

#include "Nucleus/Memory.h"

static void *
callback
    (
        void *thread
    );

static void *
callback
    (
        void *p
    )
{
    Nucleus_Concurrency_ThreadImpl *impl = (Nucleus_Concurrency_ThreadImpl *)p;
    Nucleus_Status status;

    status = Nucleus_Concurrency_Mutex_lock(&impl->mutex);
    if (status)
    {
        impl->status = status;
        impl->terminated = true;
        return p;
    }

    // Protection from spurious wakeups.
    while (!impl->startRequested)
    {
        status = Nucleus_Concurrency_Condition_wait(&impl->condition, &impl->mutex);
        if (status)
        {
            impl->status = status;
            impl->terminated = true;
            Nucleus_Concurrency_Mutex_unlock(&impl->mutex);
            return p;
        }
    }

    impl->started = true;

    status = Nucleus_Concurrency_Mutex_unlock(&impl->mutex);
    if (status)
    {
        impl->status = status;
        return p;
    }

    // if the thread is not requested to terminate, invoke the function
    if (!impl->terminationRequested)
    {
        impl->status = impl->callbackFunction(impl->callbackContext);
    }

    impl->terminated = true;

    return impl;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_create
    (
        Nucleus_Concurrency_ThreadImpl **thread,
        Nucleus_Concurrency_Thread_CallbackContext *callbackContext,
        Nucleus_Concurrency_Thread_CallbackFunction *callbackFunction
    )
{
    if (Nucleus_Unlikely(!thread || !callbackFunction)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    //
    Nucleus_Concurrency_ThreadImpl *threadImpl;
    status = Nucleus_allocateMemory((void **)&(threadImpl), sizeof (Nucleus_Concurrency_ThreadImpl));
    if (status)
    { return status; }
    //
    threadImpl->callbackContext = callbackContext;
    threadImpl->callbackFunction = callbackFunction;
    threadImpl->startRequested = false;
    threadImpl->started = false;
    threadImpl->terminationRequested = false;
    threadImpl->terminated = false;
    threadImpl->status = Nucleus_Status_Success;
    //
    status = Nucleus_Concurrency_Mutex_initialize(&threadImpl->mutex);
    if (status)
    {
        Nucleus_deallocateMemory(threadImpl);
        return status;
    }
    //
    status = Nucleus_Concurrency_Condition_initialize(&threadImpl->condition);
    if (status)
    {
        Nucleus_Concurrency_Condition_uninitialize(&threadImpl->condition);
        Nucleus_deallocateMemory(threadImpl);
        return status;
    }
    //
    if (Nucleus_Unlikely(0 != pthread_create(&(threadImpl->thread), NULL, &callback, (void *)threadImpl)))
    {
        Nucleus_Concurrency_Condition_uninitialize(&threadImpl->condition);
        Nucleus_Concurrency_Mutex_uninitialize(&threadImpl->mutex);
        Nucleus_deallocateMemory(threadImpl);
        return Nucleus_Status_EnvironmentFailed;
    }
    //
    *thread = threadImpl;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_Concurrency_ThreadImpl_destroy
    (
        Nucleus_Concurrency_ThreadImpl *thread
    )
{
    Nucleus_Concurrency_ThreadImpl *threadImpl = thread;
    // If the thread was not started yet, unblock the callback.
    if (!threadImpl->started)
    {
        threadImpl->terminationRequested = true;
        threadImpl->startRequested = true;
        Nucleus_Concurrency_Condition_signalAll(&threadImpl->condition);
    }
    // Join the thread.
    Nucleus_Concurrency_ThreadImpl_join(threadImpl);
    Nucleus_Concurrency_Condition_uninitialize(&threadImpl->condition);
    Nucleus_Concurrency_Mutex_uninitialize(&threadImpl->mutex);
    Nucleus_deallocateMemory(threadImpl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_join
    (
        Nucleus_Concurrency_ThreadImpl *thread
    )
{
    void *result;
    // TODO: The thread's mutex needs to be locked.
    //       If locking fails, then the thread has not started yet.

    // if the thread was not started yet ...
    if (!thread->started)
    {
        // ... return Nucleus_Status_NotStarted;
        return Nucleus_Status_NotStarted;
    }
    // if the thread was terminated already ...
    if (thread->terminated)
    {
        // ... return Nucleus_Status_AlreadyStopped.
        return Nucleus_Status_AlreadyStopped;
    }
    else
    {
        pthread_join(thread->thread, &result);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_getStatus
    (
        Nucleus_Concurrency_ThreadImpl *thread,
        Nucleus_Status *status
    )
{
    if (Nucleus_Unlikely(!thread || !status)) return Nucleus_Status_InvalidArgument;
    *status = thread->status;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_start
    (
        Nucleus_Concurrency_ThreadImpl *thread
    )
{
    if (!thread->startRequested)
    {
        thread->startRequested = true;
        Nucleus_Concurrency_Condition_signalAll(&thread->condition);
    }
    return Nucleus_Status_Success;
}

#endif
