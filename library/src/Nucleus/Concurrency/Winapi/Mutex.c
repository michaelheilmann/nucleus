// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Concurrency/Pthreads/Mutex.h"

#if defined(Nucleus_Platform_Winapi)

#include "Nucleus/Memory.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_create
    (
        Nucleus_Concurrency_MutexImpl **mutex
    )
{
    if (Nucleus_Unlikely(!mutex))
    { return Nucleus_Status_InvalidArgument; }
    //
    Nucleus_Status status;
    //
    Nucleus_Concurrency_MutexImpl *mutexImpl;
    status = Nucleus_allocateMemory((void **)&(mutexImpl), (sizeof (Nucleus_Concurrency_MutexImpl)));
    if (status)
    { return status; }
    //
    InitializeSRWLock(&(mutexImpl->srwLock));
    //
    *mutex = mutexImpl;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_Concurrency_MutexImpl_destroy
    (
        Nucleus_Concurrency_MutexImpl *mutex
    )
{
    Nucleus_Concurrency_MutexImpl *mutexImpl = mutex;
    Nucleus_deallocateMemory(mutexImpl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_lock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    )
{
    Nucleus_Concurrency_MutexImpl *mutexImpl = mutex;
    AcquireSRWLockExclusive(&(mutexImpl->srwLock));
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_unlock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    )
{
    Nucleus_Concurrency_MutexImpl *mutexImpl = mutex;
    ReleaseSRWLockExclusive(&(mutexImpl->srwLock));
    return Nucleus_Status_Success;
}

#endif
