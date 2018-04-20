#include "Nucleus/Collections/ByteArray.h"

#include "Nucleus/Memory.h"

static const Nucleus_Size greatestCapacity = Nucleus_Size_Greatest / sizeof(char);

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_initialize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        Nucleus_Size initialCapacity
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

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_increaseCapacity
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        Nucleus_Size requiredAdditionalCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredAdditionalCapacity)) return Nucleus_Status_Success;
    Nucleus_Size oldCapacity = dynamicByteArray->capacity;
    if (greatestCapacity - oldCapacity < requiredAdditionalCapacity) return Nucleus_Status_Overflow;
    Nucleus_Size newCapacity = oldCapacity + requiredAdditionalCapacity;
    Nucleus_Status status = Nucleus_reallocateArrayMemory((void **)&dynamicByteArray->array,
                                                          newCapacity,
                                                          sizeof(char));
    if (Nucleus_Unlikely(status)) return status;
    dynamicByteArray->capacity = newCapacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_ensureFreeCapacity
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        Nucleus_Size requiredFreeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicByteArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredFreeCapacity)) return Nucleus_Status_Success;
    Nucleus_Size availableFreeCapacity = dynamicByteArray->capacity - dynamicByteArray->size;
    if (availableFreeCapacity < requiredFreeCapacity)
    {
        Nucleus_Size requiredAdditionalCapacity = requiredFreeCapacity - availableFreeCapacity;
        return Nucleus_Collections_ByteArray_increaseCapacity(dynamicByteArray, requiredAdditionalCapacity);
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
        Nucleus_Size numberOfBytes
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
        Nucleus_Size index
    )
{ return Nucleus_Collections_ByteArray_insertMany(dynamicByteArray, &byte, 1, index); }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_insertMany
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Size index
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
        Nucleus_Size index,
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
Nucleus_Collections_ByteArray_lock
    (
        Nucleus_Collections_ByteArray *byteArray,
        void **bytes,
        size_t *numberOfBytes
    )
{
    *bytes = byteArray->array;
    *numberOfBytes = byteArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_unlock
    (
        Nucleus_Collections_ByteArray *byteArray
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_ByteArray_getSize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray,
        Nucleus_Size *size
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
        Nucleus_Size *capacity
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
        Nucleus_Size *freeCapacity
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
