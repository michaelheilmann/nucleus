// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Concurrency/Pthreads/Mutex.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)  || \
    defined(Nucleus_Threads_Pthreads)

#include "Nucleus/Memory.h"
#include <stdio.h>

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_create
    (
        Nucleus_Concurrency_MutexImpl **mutex,
        Nucleus_Boolean recursive
    )
{
    //
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
    if (recursive)
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        if (Nucleus_Unlikely(0 != pthread_mutex_init(&mutexImpl->mutex, &attr)))
        {
            pthread_mutexattr_destroy(&attr);
            Nucleus_deallocateMemory(mutexImpl);
            return Nucleus_Status_EnvironmentFailed;
        }
        pthread_mutexattr_destroy(&attr);
    }
    else
    {
        if (Nucleus_Unlikely(0 != pthread_mutex_init(&mutexImpl->mutex, NULL)))
        {
            Nucleus_deallocateMemory(mutexImpl);
            return Nucleus_Status_EnvironmentFailed;
        }
    }
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
    pthread_mutex_destroy(&(mutex->mutex));
    Nucleus_deallocateMemory(mutex);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_lock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    )
{
    int error = pthread_mutex_lock(&(mutex->mutex));
    if (error) fprintf(stderr, "%s:%d: warning: pthread_mutex_lock failed\n", __FILE__, __LINE__);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_MutexImpl_unlock
    (
        Nucleus_Concurrency_MutexImpl *mutex
    )
{
    int error = pthread_mutex_unlock(&(mutex->mutex));
    if (error) fprintf(stderr, "%s:%d: warning: pthread_mutex_unlock failed\n", __FILE__, __LINE__);
    return Nucleus_Status_Success;
}

#endif
