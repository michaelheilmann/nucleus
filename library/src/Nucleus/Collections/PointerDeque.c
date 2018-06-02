// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerDeque.h"

#include "Nucleus/Memory.h"
#include "Nucleus/Types/Size.h"

Nucleus_NoError() static Nucleus_Size
MOD
    (
        Nucleus_Size index,
        Nucleus_Size capacity
    );

Nucleus_NonNull() static Nucleus_Size
MOD
    (
        Nucleus_Size index,
        Nucleus_Size capacity
    )
{ return index % capacity; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_initialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockFunction,
        Nucleus_UnlockFunction *unlockFunction
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    initialCapacity = initialCapacity > 0 ? initialCapacity : 1;
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&dynamicPointerDeque->elements,
                                                        initialCapacity,
                                                        sizeof(void *));
    dynamicPointerDeque->read = 0;
    dynamicPointerDeque->size = 0;
    dynamicPointerDeque->capacity = initialCapacity;
    dynamicPointerDeque->lockFunction = lockFunction;
    dynamicPointerDeque->unlockFunction = unlockFunction;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_uninitialize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    )
{
    Nucleus_Collections_PointerDeque_clear(dynamicPointerDeque);
    Nucleus_deallocateMemory(dynamicPointerDeque->elements);
    dynamicPointerDeque->elements = NULL;
    dynamicPointerDeque->capacity = 0;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_increaseCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size requiredAdditionalCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredAdditionalCapacity)) return Nucleus_Status_Success;
    // Compute the maximum additional capacity.
    Nucleus_Size maximumAdditionalCapacity = (Nucleus_Size_Greatest - dynamicPointerDeque->capacity) / sizeof(void *);
    // If the required additional capacity is greater than the maximum additional capacity ...
    if (maximumAdditionalCapacity < requiredAdditionalCapacity)
    {
        // ... fail.
        return Nucleus_Status_Overflow;
    }
    // Compute the desired additional capacity.
    // Note that if capacity * 2 overflows, then we have a wrap around. This does not cause any harm.
    Nucleus_Size desiredAdditionalCapacity = dynamicPointerDeque->capacity > 0 ? dynamicPointerDeque->capacity * 2 : 8;
    // The desired additional capacity might be smaller, equal, or greater than the required additional capacity.
    // Take the maximum of both.
#pragma push_macro("MAX")
#pragma push_macro("MIN")
#define MAX(x,y) x > y ? x : y
#define MIN(x,y) x < y ? x : y
    Nucleus_Size additionalCapacity = MAX(desiredAdditionalCapacity, requiredAdditionalCapacity);
    // The additional capacity may not exceed the maximum additional capacity.
    additionalCapacity = MIN(maximumAdditionalCapacity, additionalCapacity);
#pragma pop_macro("MIN")
#pragma pop_macro("MAX")
    // Compute the new capacity.
    Nucleus_Size newCapacity = dynamicPointerDeque->capacity + additionalCapacity;

    void **newElements;
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&newElements, newCapacity, sizeof(void *));
    if (status) return status;
    for (Nucleus_Size i = 0, n = dynamicPointerDeque->size; i < n; ++i)
    {
        newElements[i] = dynamicPointerDeque->elements[(dynamicPointerDeque->read + i) % (dynamicPointerDeque->capacity)];
    }
    Nucleus_deallocateMemory(dynamicPointerDeque->elements);
    dynamicPointerDeque->elements = newElements;
    dynamicPointerDeque->capacity = newCapacity;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_ensureFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size requiredFreeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(!requiredFreeCapacity)) return Nucleus_Status_Success;
    Nucleus_Size actualFreeCapacity = dynamicPointerDeque->capacity - dynamicPointerDeque->size;
    if (actualFreeCapacity < requiredFreeCapacity)
    {
        return Nucleus_Collections_PointerDeque_increaseCapacity(dynamicPointerDeque,
                                                                 requiredFreeCapacity - actualFreeCapacity);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getSize
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *size
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicPointerDeque->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicPointerDeque->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_getFreeCapacity
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size *freeCapacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque || !freeCapacity)) return Nucleus_Status_InvalidArgument;
    *freeCapacity = dynamicPointerDeque->capacity - dynamicPointerDeque->size;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_clear
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque
    )
{
    if (dynamicPointerDeque->unlockFunction)
    {
        Nucleus_UnlockFunction *unlockFunction = dynamicPointerDeque->unlockFunction;
        const Nucleus_Size capacity = dynamicPointerDeque->capacity;
        while (dynamicPointerDeque->size > 0)
        {
            void *element = dynamicPointerDeque->elements[MOD(dynamicPointerDeque->read +
                                                              dynamicPointerDeque->size - 1,
                                                              capacity)];
            unlockFunction(element);
            dynamicPointerDeque->size--;
        }

    }
    else
    {
        dynamicPointerDeque->size = 0;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_append
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerDeque_insert(dynamicPointerDeque, pointer, dynamicPointerDeque->size);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_prepend
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerDeque_insert(dynamicPointerDeque, pointer, 0);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_insert
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        void *pointer,
        Nucleus_Size index
    )
{
    // The pointer to the deque must not be a null pointer.
    if (Nucleus_Unlikely(!dynamicPointerDeque)) return Nucleus_Status_InvalidArgument;
    // "index" must be smaller than or equal to the size of the deque.
    if (index > dynamicPointerDeque->size) return Nucleus_Status_InvalidArgument;
    // Ensure there is room for one more element.
    Nucleus_Status status;
    status = Nucleus_Collections_PointerDeque_ensureFreeCapacity(dynamicPointerDeque, 1);
    if (Nucleus_Unlikely(status)) return status;

    const Nucleus_Size capacity = dynamicPointerDeque->capacity; // The capacity does not change anymore for the rest of this
                                                                 // function but is frequently referenced, hence it is cached
                                                                 // here.

    // The goal of the following algorithm is to minimize the number of shift operations when inserting into an index
    // smaller than size.

    // Assume the deque is not empty.
    // Treating the deque as an infinite array,
    // ..., a[0],...,a[read],...,a[read+index], ..., a[read+size-1]
    // then
    // a) the index of the first element is "read" and
    // b) the index of the last element is "read + size - 1" and
    // c) "read <= index <= read + size".
    //
    // So to insert at index "index", one can either shift up the elements
    // "a[read + index],... a[read+size-1]" or
    // shift down the elements
    // "a[read] ... a[read + index-1]"
    // to make room for the new element.
    //
    // The choice made here is to minimize the number of shifts:
    // if "index < size / 2" then "a[read] ... a[read + index - 1]" is shifted down
    // and otherwise "a[read + index],... a[read+size-1]" is shifted up.
    if (index < dynamicPointerDeque->size / 2)
    {
        // If a' ist the new queue and a is the old queue, then the operation
        // can be described as follows:
        // - a'[read-1] = a[read], ..., a'[read - 1 + index] = a[read + index]
        // - a'[read+index] = newElement
        // - read' = read - 1
        // - size' = size + 1
        // As read' = read - 1, one can also write
        // - a'[read'] = a[read' + 1], ..., a'[read + index] = a[read' + index + 1]
        // which is the form used here.
        Nucleus_Size offset = MOD(dynamicPointerDeque->read - 1, capacity);
        for (Nucleus_Size j = 0; j < index; ++j)
        {
            dynamicPointerDeque->elements[MOD(offset + j, capacity)] =
                dynamicPointerDeque->elements[MOD(offset + j + 1, capacity)];
        }
        dynamicPointerDeque->read = MOD(dynamicPointerDeque->read - 1, capacity);
    }
    else
    {
        // If a' ist the new queue and a is the old queue, then the operation
        // can be described as follows:
        // - a'[read + size] = a[read + size - 1], ..., a'[read + index + 1] = a[read + index]
        // - a'[read + index] = newElement
        // - read' = read
        // - size' = size+1
        Nucleus_Size offset = dynamicPointerDeque->read;
        for (Nucleus_Size j = dynamicPointerDeque->size; j > index; --j)
        {
            dynamicPointerDeque->elements[MOD(offset + j, capacity)] =
                dynamicPointerDeque->elements[MOD(offset + j - 1, capacity)];
        }
    }
    dynamicPointerDeque->elements[MOD(dynamicPointerDeque->read + index, capacity)] = pointer;
    dynamicPointerDeque->size++;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerDeque_at
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size index,
        void **element
    )
{
    if (Nucleus_Unlikely(!dynamicPointerDeque || !element)) return Nucleus_Status_InvalidArgument;
    *element = dynamicPointerDeque->elements[MOD(dynamicPointerDeque->read + index, dynamicPointerDeque->capacity)];
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerDeque_remove
    (
        Nucleus_Collections_PointerDeque *dynamicPointerDeque,
        Nucleus_Size index
    )
{
    // The pointer to the dequeue must not be a null pointer.
    if (Nucleus_Unlikely(!dynamicPointerDeque))
    {
        return Nucleus_Status_InvalidArgument;
    }
    // "index" must be smaller than the size of the queue.
    if (index >= dynamicPointerDeque->size)
    {
        return Nucleus_Status_InvalidArgument;
    }
    const Nucleus_Size capacity = dynamicPointerDeque->capacity;
    if (index < dynamicPointerDeque->size / 2)
    {  
        // - a'[read] = a[read-1], ..., a'[read + index] = a[read + index - 1] 
        // - read' = read + 1
        // - size' = size - 1
        Nucleus_Size offset = dynamicPointerDeque->read;
        for (Nucleus_Size j = index; j > 0; --j)
        {
            dynamicPointerDeque->elements[MOD(offset + j, capacity)] =
                dynamicPointerDeque->elements[MOD(offset + j - 1, capacity)];
        }
        dynamicPointerDeque->read = MOD(dynamicPointerDeque->read + 1, capacity);
    }
    else
    {
        // - a'[read+index] = a[read+index+1], ..., a'[read+size-2] = a[read+size-1]
        // - read' = read
        // - size' = size - 1
        // shift a[i+1],..,a[n-1] left one position
        for (Nucleus_Size j = index; j < dynamicPointerDeque->size - 1; ++j)
        {
            dynamicPointerDeque->elements[MOD(dynamicPointerDeque->read + j, capacity)] =
                dynamicPointerDeque->elements[MOD(dynamicPointerDeque->read + j + 1, capacity)];
        }
    }
    dynamicPointerDeque->size--;
    return Nucleus_Status_Success;
}
