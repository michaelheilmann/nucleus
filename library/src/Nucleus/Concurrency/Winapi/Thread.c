// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Concurrency/Winapi/Thread.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Memory.h"

static DWORD WINAPI
callback
    (
        void *thread
    );

static void lock(Nucleus_Concurrency_ThreadImpl *impl);

static void unlock(Nucleus_Concurrency_ThreadImpl *impl);

static int GetState(Nucleus_Concurrency_ThreadImpl *impl);

static void SetState(Nucleus_Concurrency_ThreadImpl *impl, int state);


static void lock(Nucleus_Concurrency_ThreadImpl *impl)
{ Nucleus_Concurrency_Mutex_lock(&impl->mutex); }

static void unlock(Nucleus_Concurrency_ThreadImpl *impl)
{ Nucleus_Concurrency_Mutex_unlock(&impl->mutex); }


static DWORD WINAPI
callback
    (
        void *p
    )
{
    Nucleus_Concurrency_ThreadImpl *impl = (Nucleus_Concurrency_ThreadImpl *)p;
    SetState(impl, Nucleus_Concurrency_ThreadImpl_Started);
    impl->status = impl->callbackFunction(impl->callbackContext);
    SetState(impl, Nucleus_Concurrency_ThreadImpl_Terminated);
    return impl;
}

static int GetState(Nucleus_Concurrency_ThreadImpl *impl)
{
    lock(impl);
    int state = impl->state;
    unlock(impl);
    return state;
}

static void SetState(Nucleus_Concurrency_ThreadImpl *impl, int state)
{
    lock(impl);
    impl->state = state;
    unlock(impl);
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
    // Initialize the fields.
    threadImpl->callbackContext = callbackContext;
    threadImpl->callbackFunction = callbackFunction;
    threadImpl->status = Nucleus_Status_Success;
    threadImpl->state = Nucleus_Concurrency_ThreadImpl_Initialized;
    // Initialize the mutex.
    status = Nucleus_Concurrency_Mutex_initialize(&threadImpl->mutex);
    if (status)
    {
        Nucleus_deallocateMemory(threadImpl);
        return status;
    }
    // Create the thread suspended.
    threadImpl->thread = CreateThread(NULL, 0, &callback, threadImpl, CREATE_SUSPENDED, NULL);
    if (Nucleus_Unlikely(!threadImpl->thread))
    {
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
    // Join the thread.
    Nucleus_Concurrency_ThreadImpl_join(thread);
    Nucleus_deallocateMemory(thread);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_ThreadImpl_join
    (
        Nucleus_Concurrency_ThreadImpl *thread
    )
{
    lock(thread);
    switch (thread->state)
    {
        case Nucleus_Concurrency_ThreadImpl_Initialized:
        {
            unlock(thread);
            return Nucleus_Status_NotStarted;
        }
        case Nucleus_Concurrency_ThreadImpl_Terminated:
        {
            unlock(thread);
            return Nucleus_Status_AlreadyStopped;
        }
    };
    unlock(thread);
    // We enter the waiting state here.
    // The thread is either running or has terminated.
    WaitForSingleObject(thread->thread, INFINITE);
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
    if (Nucleus_Unlikely(!thread)) return Nucleus_Status_InvalidArgument;
    lock(thread);
    switch (thread->state)
    {
        case Nucleus_Concurrency_ThreadImpl_Started:
            {
                unlock(thread);
                return Nucleus_Status_AlreadyStarted;
            }
        case Nucleus_Concurrency_ThreadImpl_Terminated:
            {
                unlock(thread);
                return Nucleus_Status_AlreadyStopped;
            }
    };
    DWORD dwResult = ResumeThread(thread->thread);
    if ((DWORD)-1 == dwResult)
    {
        unlock(thread);
        return Nucleus_Status_EnvironmentFailed;
    }
    unlock(thread);
    return Nucleus_Status_Success;
}

#endif
