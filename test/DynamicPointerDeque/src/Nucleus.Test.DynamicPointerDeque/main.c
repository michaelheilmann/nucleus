// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerDeque.h"
#include "Nucleus.Test.DynamicPointerDeque/testCollection.h"
#include <stdlib.h>

static Nucleus_Status
test2
    (
    );

static Nucleus_Status
test3
    (
    );

static Nucleus_Status
test2
    (
    )
{
    static const char *pointers[] = 
    {
        "0",
        "1",
        "2",
        "3",
    };
    Nucleus_Collections_PointerDeque pointerDequeue;
    Nucleus_Status status;

    status = Nucleus_Collections_PointerDeque_initialize(&pointerDequeue, 0, NULL, NULL);
    if (status) return status;

    status = Nucleus_Collections_PointerDeque_prepend(&pointerDequeue, (void *)pointers[0]);   if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_insert(&pointerDequeue, (void *)pointers[1], 1); if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_insert(&pointerDequeue, (void *)pointers[2], 2); if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_append(&pointerDequeue, (void *)pointers[3]);    if (status) goto Exit;
    size_t size;
    status = Nucleus_Collections_PointerDeque_getSize(&pointerDequeue, &size);
    if (status) goto Exit;
    if (size != 4)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (size_t i = 0, n = size; i < n; ++i)
    {
        char *pointer;
        status = Nucleus_Collections_PointerDeque_at(&pointerDequeue, i, (void **)&pointer);
        if (status)
        {
            goto Exit;
        }
        if (pointer != pointers[i])
        {
            status = Nucleus_Status_InternalError;
            goto Exit;
        }
    }
Exit:
    Nucleus_Collections_PointerDeque_uninitialize(&pointerDequeue);
    return status;
}

static Nucleus_Status
test3
    (
    )
{
    static const char *pointers[] =
    {
        "0",
        "1",
        "2",
        "3",
    };
    Nucleus_Collections_PointerDeque pointerDequeue;
    Nucleus_Status status;

    status = Nucleus_Collections_PointerDeque_initialize(&pointerDequeue, 0, NULL, NULL);
    if (status) return status;

    status = Nucleus_Collections_PointerDeque_prepend(&pointerDequeue, (void *)pointers[0]);   if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_insert(&pointerDequeue, (void *)pointers[1], 1); if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_insert(&pointerDequeue, (void *)pointers[2], 2); if (status) goto Exit;
    status = Nucleus_Collections_PointerDeque_append(&pointerDequeue, (void *)pointers[3]);    if (status) goto Exit;
    Nucleus_Size size;
    status = Nucleus_Collections_PointerDeque_getSize(&pointerDequeue, &size);
    if (status) goto Exit;
    if (size != 4)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (Nucleus_Size i = 0, n = size; i < n; ++i)
    {
        char *pointer;
        status = Nucleus_Collections_PointerDeque_at(&pointerDequeue, i, (void **)&pointer);
        if (status)
        {
            goto Exit;
        }
        if (pointer != pointers[i])
        {
            status = Nucleus_Status_InternalError;
            goto Exit;
        }
    }
Exit:
    Nucleus_Collections_PointerDeque_uninitialize(&pointerDequeue);
    return status;
}

int main(int argc, char **argv)
{
    if (testCollection() || test2() || test3()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
