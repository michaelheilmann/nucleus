// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Test.ByteArray/testCollection.h"

// Create a collection (1),
// Assert the size is 0 (2).
// Assert the capacity is greater than or equal to the size (3).
// Destroy the collection (4).
Nucleus_Status
testCollection
    (
    )
{
    Nucleus_Collections_ByteArray collection;
    Nucleus_Status status;
    
    // (1)
    status = Nucleus_Collections_ByteArray_initialize(&collection,
                                                      8);
    if (Nucleus_Unlikely(status)) return status;
    
    // (2)
    Nucleus_Size size;
    status = Nucleus_Collections_ByteArray_getSize(&collection, &size);
    if (Nucleus_Unlikely(status)) goto Exit;  
    if (size != 0)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }

    // (3)
    Nucleus_Size capacity;
    status = Nucleus_Collections_ByteArray_getCapacity(&collection, &capacity);
    if (Nucleus_Unlikely(status)) goto Exit;
    if (capacity < size)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }

    // (4)
Exit:
    Nucleus_Collections_ByteArray_uninitialize(&collection);
    return status;
}
