// Copyright (c) Michael Heilmann 2018
#include "Nucleus/DynamicPointerArray.h"

#include "Nucleus/Memory.h"

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_initialize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&dynamicPointerArray->elements,
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
Nucleus_DynamicPointerArray_uninitialize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray
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

// TODO: Use Nucleus_reallocate(Array)Memory.
Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_ensureFreeCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t requiredFreeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    size_t availableFreeCapacity = dynamicPointerArray->capacity - dynamicPointerArray->size;
    if (availableFreeCapacity < requiredFreeCapacity)
    {
        size_t additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
        size_t oldCapacity = dynamicPointerArray->capacity;
        size_t newCapacity = oldCapacity + additionalCapacity;
        void **oldElements = dynamicPointerArray->elements;
        void **newElements;
        Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&newElements,
                                                            newCapacity,
                                                            sizeof(void *));
        if (Nucleus_Unlikely(status)) return status;
        Nucleus_copyArrayMemory(newElements, oldElements, oldCapacity, sizeof(void *));
        dynamicPointerArray->elements = newElements;
        Nucleus_deallocateMemory(oldElements);
        dynamicPointerArray->capacity = newCapacity;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_append
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_DynamicPointerArray_insert(dynamicPointerArray, pointer, dynamicPointerArray->size);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_prepend
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    return Nucleus_DynamicPointerArray_insert(dynamicPointerArray, pointer, 0);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_DynamicPointerArray_insert
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        void *pointer,
        size_t index
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index > dynamicPointerArray->size)) return Nucleus_Status_IndexOutOfBounds;
    Nucleus_Status status;
    status = Nucleus_DynamicPointerArray_ensureFreeCapacity(dynamicPointerArray, 1);
    if (Nucleus_Unlikely(status)) return status;
    if (dynamicPointerArray->lockFunction)
    {
        dynamicPointerArray->lockFunction(pointer);
    }
    Nucleus_copyMemory(dynamicPointerArray->elements + index + 1, dynamicPointerArray->elements + index,
                       sizeof(void *));

    dynamicPointerArray->elements[index] = pointer;
    dynamicPointerArray->size++;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_at
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t index,
        void **pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !pointer)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(index >= dynamicPointerArray->size)) return Nucleus_Status_IndexOutOfBounds;
    *pointer = dynamicPointerArray->elements[index];
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getSize
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *size
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicPointerArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicPointerArray->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_getFreeCapacity
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray,
        size_t *freeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerArray || !freeCapacity)) return Nucleus_Status_InvalidArgument;
    *freeCapacity = dynamicPointerArray->capacity - dynamicPointerArray->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DynamicPointerArray_clear
    (
        Nucleus_DynamicPointerArray *dynamicPointerArray
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
