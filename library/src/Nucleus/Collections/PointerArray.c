// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerArray.h"

#include "Nucleus/Memory.h"

static const Nucleus_Size greatestCapacity = Nucleus_Size_Greatest / sizeof(void *);

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_initialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&(dynamicPointerArray->elements),
                                                        initialCapacity,
                                                        sizeof(void *));
    if (Nucleus_Unlikely(status)) return status;
    dynamicPointerArray->size = 0;
    dynamicPointerArray->capacity = initialCapacity;
    dynamicPointerArray->lockFunction = lockFunction;
    dynamicPointerArray->unlockFunction = unlockFunction;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_uninitialize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    )
{
    if (dynamicPointerArray->unlockFunction)
    {
        Nucleus_UnlockFunction *unlockFunction = dynamicPointerArray->unlockFunction;
        while (dynamicPointerArray->size > 0)
        {
            unlockFunction(dynamicPointerArray->elements[dynamicPointerArray->size - 1]);
            dynamicPointerArray->size--;
        }

    }
    else
    {
        dynamicPointerArray->size = 0;
    }
    Nucleus_deallocateMemory(dynamicPointerArray->elements);
    dynamicPointerArray->elements = NULL;
    dynamicPointerArray->capacity = 0;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_increaseCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size requiredAdditionalCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredAdditionalCapacity)) return Nucleus_Status_Success;
    Nucleus_Size oldCapacity = dynamicPointerArray->capacity;
    if (greatestCapacity - oldCapacity < requiredAdditionalCapacity) return Nucleus_Status_Overflow;
    Nucleus_Size newCapacity = oldCapacity + requiredAdditionalCapacity;
    Nucleus_Status status = Nucleus_reallocateArrayMemory((void **)&(dynamicPointerArray->elements),
                                                          newCapacity,
                                                          sizeof(void *));
    if (Nucleus_Unlikely(status)) return status;
    dynamicPointerArray->capacity = newCapacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_ensureFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size requiredFreeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredFreeCapacity)) return Nucleus_Status_Success;
    Nucleus_Size availableFreeCapacity = dynamicPointerArray->capacity - dynamicPointerArray->size;
    if (availableFreeCapacity < requiredFreeCapacity)
    {
        Nucleus_Size requiredAdditionalCapacity = requiredFreeCapacity - availableFreeCapacity;
        return Nucleus_Collections_PointerArray_increaseCapacity(dynamicPointerArray, requiredAdditionalCapacity);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_append
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_insert(dynamicPointerArray, pointer, dynamicPointerArray->size);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_prepend
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_insert(dynamicPointerArray, pointer, 0);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerArray_insert
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        void *pointer,
        Nucleus_Size index
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index > dynamicPointerArray->size)) return Nucleus_Status_IndexOutOfBounds;
    Nucleus_Status status;
    status = Nucleus_Collections_PointerArray_ensureFreeCapacity(dynamicPointerArray, 1);
    if (Nucleus_Unlikely(status)) return status;
    if (dynamicPointerArray->lockFunction)
    {
        dynamicPointerArray->lockFunction(pointer);
    }
    if (index != dynamicPointerArray->size)
    {
        Nucleus_copyArrayMemory(dynamicPointerArray->elements + index + 1,
                                dynamicPointerArray->elements + index,
                                dynamicPointerArray->size - index,
                                sizeof(void *));
    }
    dynamicPointerArray->elements[index] = pointer;
    dynamicPointerArray->size++;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_at
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size index,
        void **pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !pointer)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index >= dynamicPointerArray->size)) return Nucleus_Status_IndexOutOfBounds;
    *pointer = dynamicPointerArray->elements[index];
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getSize
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *size
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicPointerArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicPointerArray->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_getFreeCapacity
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray,
        Nucleus_Size *freeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !freeCapacity)) return Nucleus_Status_InvalidArgument;
    *freeCapacity = dynamicPointerArray->capacity - dynamicPointerArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_clear
    (
        Nucleus_Collections_PointerArray *dynamicPointerArray
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray))
    {
        return Nucleus_Status_InvalidArgument;
    }
    if (dynamicPointerArray->unlockFunction)
    {
        Nucleus_UnlockFunction *unlockFunction = dynamicPointerArray->unlockFunction;
        while (dynamicPointerArray->size > 0)
        {
            unlockFunction(dynamicPointerArray->elements[dynamicPointerArray->size - 1]);
            dynamicPointerArray->size--;
        }

    }
    else
    {
        dynamicPointerArray->size = 0;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_initialize
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        Nucleus_Collections_PointerArray *source
    )
{
    enumerator->source = source;
    enumerator->index = 0;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_uninitialize
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status 
Nucleus_Collections_PointerArray_Enumerator_nextValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator
    )
{
    if (enumerator->index == enumerator->source->size)
    {
        return Nucleus_Status_Success;
    }
    enumerator->index++;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_hasValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        Nucleus_Boolean *hasValue
    )
{
    if (Nucleus_Unlikely(!enumerator || !hasValue)) return Nucleus_Status_InvalidArgument;
    *hasValue = enumerator->index < enumerator->source->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerArray_Enumerator_getValue
    (
        Nucleus_Collections_PointerArray_Enumerator *enumerator,
        void **value
    )
{
    if (Nucleus_Unlikely(!enumerator || !value)) return Nucleus_Status_InvalidArgument;
    *value = enumerator->source->elements[enumerator->index];
    return Nucleus_Status_Success;
}
