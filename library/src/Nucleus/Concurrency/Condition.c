// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Concurrency/Condition.h"

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Pthreads/Condition.h"
    #include "Nucleus/Concurrency/Pthreads/Mutex.h"
#elif defined(Nucleus_Platform_Windows) && !defined(Nucleus_Threads_Pthreads)
    #include "Nucleus/Concurrency/Winapi/Condition.h"
    #include "Nucleus/Concurrency/Winapi/Mutex.h"
#else
    #error("platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Condition_initialize
    (
        Nucleus_Concurrency_Condition *condition
    )
{
    if (Nucleus_Unlikely(!condition)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    status = Nucleus_Concurrency_ConditionImpl_create(&(condition->impl));
    if (Nucleus_Unlikely(status)) return status;
    return status;
}

Nucleus_NonNull() void
Nucleus_Concurrency_Condition_uninitialize
    (
        Nucleus_Concurrency_Condition *condition
    )
{
    Nucleus_Concurrency_ConditionImpl_destroy(condition->impl);
    condition->impl = NULL;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Condition_wait
    (
        Nucleus_Concurrency_Condition *condition,
        Nucleus_Concurrency_Mutex *mutex
    )
{
    if (Nucleus_Unlikely(!condition || !mutex)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ConditionImpl_wait(condition->impl, mutex->impl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Condition_signalOne
    (
        Nucleus_Concurrency_Condition *condition
    )
{
    if (Nucleus_Unlikely(!condition)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ConditionImpl_signalOne(condition->impl);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Concurrency_Condition_signalAll
    (
        Nucleus_Concurrency_Condition *condition
    )
{
    if (Nucleus_Unlikely(!condition)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Concurrency_ConditionImpl_signalAll(condition->impl);
}
