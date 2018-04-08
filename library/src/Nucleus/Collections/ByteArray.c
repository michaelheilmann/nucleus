#include "Nucleus/Collections/ByteArray.h"

#include "Nucleus/Memory.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_initialize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
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
Nucleus_Collections_ByteArray_uninitialize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray
    )
{
    Nucleus_deallocateMemory(dynamicByteArray->array);
    dynamicByteArray->array = NULL;
}

// TODO: Use Nucleus_reallocate(Array)Memory.
Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_ensureFreeCapacity
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
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
Nucleus_Collections_ByteArray_append
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        char byte
    )
{ return Nucleus_Collections_ByteArray_appendMany(dynamicByteArray, &byte, 1); }


Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_appendMany
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_ByteArray_insertMany(dynamicByteArray, bytes, numberOfBytes, dynamicByteArray->size);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_prepend
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        char byte
    )
{ return Nucleus_Collections_ByteArray_prependMany(dynamicByteArray, &byte, 1); }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_prependMany
    (
        
        Nucleus_Collections_ByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_ByteArray_insertMany(dynamicByteArray, bytes, numberOfBytes, 0);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_insert
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        char byte,
        size_t index
    )
{ return Nucleus_Collections_ByteArray_insertMany(dynamicByteArray, &byte, 1, index); }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_insertMany
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !bytes)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index > dynamicByteArray->size)) return Nucleus_Status_IndexOutOfBounds;
    if (Nucleus_Unlikely(0 == numberOfBytes)) return Nucleus_Status_Success;
    Nucleus_Status status;
    status = Nucleus_Collections_ByteArray_ensureFreeCapacity(dynamicByteArray, numberOfBytes);
    if (Nucleus_Unlikely(status)) return status;
    Nucleus_copyMemory(dynamicByteArray->array + index + numberOfBytes, dynamicByteArray->array + index,
                       dynamicByteArray->size - index);
    Nucleus_copyMemory(dynamicByteArray->array + index, bytes, numberOfBytes);
    dynamicByteArray->size += numberOfBytes;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_at
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
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
Nucleus_Collections_ByteArray_getBytes
    (
        Nucleus_Collections_ByteArray *dynamicByteArray
    )
{ return dynamicByteArray->array; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getSize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        size_t *size
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicByteArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getCapacity
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        size_t *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicByteArray->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getFreeCapacity
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        size_t *freeCapacity
    )
{ 
    if (Nucleus_Unlikely(!dynamicByteArray || !freeCapacity)) return Nucleus_Status_InvalidArgument;
    *freeCapacity = dynamicByteArray->capacity - dynamicByteArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_clear
    (
        
        Nucleus_Collections_ByteArray *dynamicByteArray
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    dynamicByteArray->size = 0;
    return Nucleus_Status_Success;
}
