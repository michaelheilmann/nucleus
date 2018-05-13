// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Concurrency/Mutex.h"

#include "Nucleus/Configuration.h"

#include <stdlib.h>
#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Pthreads/Mutex.h"
#elif defined(Nucleus_Platform_Windows) && !defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Winapi/Mutex.h"
#else
    #error("platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_initialize
    (
        Nucleus_Concurrency_Mutex *mutex
    )
{
    if (Nucleus_Unlikely(!mutex)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    status = Nucleus_Concurrency_MutexImpl_create(&(mutex->impl));
    if (Nucleus_Unlikely(status)) return status;
    return status;
}

Nucleus_NonNull() void
Nucleus_Concurrency_Mutex_uninitialize
    (
        Nucleus_Concurrency_Mutex *mutex
    )
{
    Nucleus_Concurrency_MutexImpl_destroy(mutex->impl);
    mutex->impl = NULL;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_lock
    (
        Nucleus_Concurrency_Mutex *mutex
    )
{
    if (Nucleus_Unlikely(!mutex)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_MutexImpl_lock(mutex->impl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Mutex_unlock
    (
        Nucleus_Concurrency_Mutex *mutex
    )
{
    if (Nucleus_Unlikely(!mutex)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_MutexImpl_unlock(mutex->impl);
}
