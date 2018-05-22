// Copyright (c) 2018 Michael Heilmann
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
// - assert that joining the unstarted thread returns Nucleus_Status_NotStarted,
// - uninitialize the thread
static Nucleus_Status
test
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

int main(int argc, char **argv)
{
    if (test()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
