// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Concurrency/Winapi/Thread.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Memory.h"

static DWORD WINAPI
callback
    (
        void *thread
    );

static DWORD WINAPI
callback
    (
        void *p
    )
{
    Nucleus_Concurrency_ThreadImpl *impl = (Nucleus_Concurrency_ThreadImpl *)p;
    impl->started = true;
    impl->status = impl->callbackFunction(impl->callbackContext);
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
    threadImpl->status = Nucleus_Status_Success;
    threadImpl->started = false;
    //
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
    //
    if (!thread->started)
    {
        return Nucleus_Status_NotStarted;
    }
    //
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
    DWORD dwResult = ResumeThread(thread->thread);
    if ((DWORD)-1 == dwResult)
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    return Nucleus_Status_Success;
}

#endif
