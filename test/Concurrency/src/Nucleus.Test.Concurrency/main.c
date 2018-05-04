// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Collections/ByteArray.h"
#include "Nucleus/Concurrency/Thread.h"
#include <stdlib.h>
#include <string.h>

static Nucleus_Status
print
    (
        const char *text
    )
{ return Nucleus_Status_Success; }

// - initialize a thread,
// - uninitialize the thread
static Nucleus_Status
test1
    (
    )
{
    static const char *STRING = "Hello, World!\n";
    Nucleus_Status status;

    Nucleus_Concurrency_Thread thread;
    status = Nucleus_Concurrency_Thread_initialize(&thread,
                                                   (Nucleus_Concurrency_Thread_CallbackContext *)STRING,
                                                   (Nucleus_Concurrency_Thread_CallbackFunction *)&print);
    if (status) return status;
    Nucleus_Concurrency_Thread_uninitialize(&thread);
    return status;
}

// - initialize a thread,
// - assert that joining the unstarted thread returns Nucleus_Status_NotStarted,
// - uninitialize the thread
static Nucleus_Status
test2
    (
    )
{
    static const char *STRING = "Hello, World!\n";
    Nucleus_Status status;

    Nucleus_Concurrency_Thread thread;
    status = Nucleus_Concurrency_Thread_initialize(&thread,
                                                   (Nucleus_Concurrency_Thread_CallbackContext *)STRING,
                                                   (Nucleus_Concurrency_Thread_CallbackFunction *)&print);
    if (status) return status;
    status = Nucleus_Concurrency_Thread_join(&thread);
    if (status)
    {
        if (status == Nucleus_Status_NotStarted)
        {
            Nucleus_Concurrency_Thread_uninitialize(&thread);
            return Nucleus_Status_Success;
        }
        else
        {
            Nucleus_Concurrency_Thread_uninitialize(&thread);
            return Nucleus_Status_InternalError;
        }
    }
    Nucleus_Concurrency_Thread_uninitialize(&thread);
    return status;
}

// - initialize a thread,
// - start the thread,
// - uninitialize the thread
static Nucleus_Status
test3
    (
    )
{
    static const char *STRING = "Hello, World!\n";
    Nucleus_Status status;

    Nucleus_Concurrency_Thread thread;
    // initialize the thread
    status = Nucleus_Concurrency_Thread_initialize(&thread,
                                                   (Nucleus_Concurrency_Thread_CallbackContext *)STRING,
                                                   (Nucleus_Concurrency_Thread_CallbackFunction *)&print);
    if (status) return status;
    // start the thread
    status = Nucleus_Concurrency_Thread_start(&thread);
    if (status)
    {
        Nucleus_Concurrency_Thread_uninitialize(&thread);
        return status;
    }
    // uninitialize the thread
    Nucleus_Concurrency_Thread_uninitialize(&thread);
    return status;
}


int main(int argc, char **argv)
{
    if (test1() || test2() || test3()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
