#include "Nucleus/DynamicByteArray.h"

#include "Nucleus/Memory.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_initialize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t initialCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&dynamicByteArray->array,
                                                        initialCapacity,
                                                        sizeof(char));
    if (Nucleus_Unlikely(status)) return status;
    dynamicByteArray->size = 0;
    dynamicByteArray->capacity = initialCapacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_DynamicByteArray_uninitialize
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    )
{
    Nucleus_deallocateMemory(dynamicByteArray->array);
    dynamicByteArray->array = NULL;
}

// TODO: Use Nucleus_reallocate(Array)Memory.
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_ensureFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t requiredFreeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    size_t availableFreeCapacity = dynamicByteArray->capacity - dynamicByteArray->size;
    if (availableFreeCapacity < requiredFreeCapacity)
    {
        size_t additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
        size_t oldCapacity = dynamicByteArray->capacity;
        size_t newCapacity = oldCapacity + additionalCapacity;
        char *oldArray = dynamicByteArray->array;
        char *newArray;
        Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&newArray,
                                                            newCapacity,
                                                            sizeof(char));
        if (Nucleus_Unlikely(status)) return status;
        Nucleus_copyArrayMemory(newArray, oldArray, oldCapacity, sizeof(char));
        dynamicByteArray->array = newArray;
        Nucleus_deallocateMemory(oldArray);
        dynamicByteArray->capacity = newCapacity;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_append
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte
    )
{ return Nucleus_DynamicByteArray_appendMany(dynamicByteArray, &byte, 1); }


Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_appendMany
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_DynamicByteArray_insertMany(dynamicByteArray, bytes, numberOfBytes, dynamicByteArray->size);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_prepend
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte
    )
{ return Nucleus_DynamicByteArray_prependMany(dynamicByteArray, &byte, 1); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_prependMany
    (
        
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_DynamicByteArray_insertMany(dynamicByteArray, bytes, numberOfBytes, 0);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_insert
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        char byte,
        size_t index
    )
{ return Nucleus_DynamicByteArray_insertMany(dynamicByteArray, &byte, 1, index); }

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_insertMany
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !bytes)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index > dynamicByteArray->size)) return Nucleus_Status_IndexOutOfBounds;
    if (Nucleus_Unlikely(0 == numberOfBytes)) return Nucleus_Status_Success;
    Nucleus_Status status;
    status = Nucleus_DynamicByteArray_ensureFreeCapacity(dynamicByteArray, numberOfBytes);
    if (Nucleus_Unlikely(status)) return status;
    Nucleus_copyMemory(dynamicByteArray->array + index + numberOfBytes, dynamicByteArray->array + index,
                       dynamicByteArray->size - index);
    Nucleus_copyMemory(dynamicByteArray->array + index, bytes, numberOfBytes);
    dynamicByteArray->size += numberOfBytes;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_at
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t index,
        char *byte
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !byte)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index >= dynamicByteArray->size)) return Nucleus_Status_IndexOutOfBounds;
    *byte = dynamicByteArray->array[index];
    return Nucleus_Status_Success;
}

Nucleus_NonNull() const char *
Nucleus_DynamicByteArray_getBytes
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    )
{ return dynamicByteArray->array; }

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getSize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *size
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicByteArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicByteArray->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_getFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *freeCapacity
    )
{ 
    if (Nucleus_Unlikely(!dynamicByteArray || !freeCapacity)) return Nucleus_Status_InvalidArgument;
    *freeCapacity = dynamicByteArray->capacity - dynamicByteArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicByteArray_clear
    (
        
        Nucleus_DynamicByteArray *dynamicByteArray
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    dynamicByteArray->size = 0;
    return Nucleus_Status_Success;
}
