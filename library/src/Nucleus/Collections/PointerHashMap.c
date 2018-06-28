// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap-private.c.i"

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerHashMap_initialize
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockKeyFunction,
        Nucleus_UnlockFunction *unlockKeyFunction,
        Nucleus_HashFunction *hashKeyFunction,
        Nucleus_EqualToFunction *keyEqualToKeyFunction,
        Nucleus_LockFunction *lockValueFunction,
        Nucleus_UnlockFunction *unlockValueFunction
    )
{
    if (Nucleus_Unlikely(!pointerHashMap)) return Nucleus_Status_InvalidArgument;
    
    initialCapacity = initialCapacity > 0 ? initialCapacity : 1;
    
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&pointerHashMap->buckets,
                                                        initialCapacity,
                                                        sizeof(Node *));
    if (Nucleus_Unlikely(status)) return status;
    for (Nucleus_Size i = 0, n = initialCapacity; i < n; ++i)
    {
        pointerHashMap->buckets[i] = NULL;
    }

    pointerHashMap->size = 0;
    pointerHashMap->capacity = initialCapacity;

    pointerHashMap->unused = NULL;

    pointerHashMap->lockKeyFunction = lockKeyFunction;
    pointerHashMap->unlockKeyFunction = unlockKeyFunction;
    pointerHashMap->hashKeyFunction = hashKeyFunction;
    pointerHashMap->keyEqualToKeyFunction = keyEqualToKeyFunction;
    pointerHashMap->lockValueFunction = lockValueFunction;
    pointerHashMap->unlockValueFunction = unlockValueFunction;
    
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_uninitialize
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap
    )
{
    clear(pointerHashMap);

    Nucleus_deallocateMemory(pointerHashMap->buckets);
    pointerHashMap->buckets = NULL;
    pointerHashMap->capacity = 0;

    while(pointerHashMap->unused)
    {
        Node *node = pointerHashMap->unused;
        pointerHashMap->unused = node->next;
        Nucleus_deallocateMemory(node);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerHashMap_set
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        void *value,
        Nucleus_Boolean replace
    )
{
    Position position;
    Nucleus_Status status = getPosition(pointerHashMap, key, &position);
    if (status) return status;
    if (position.current)
    {
        if (replace)
        {
            if (pointerHashMap->lockKeyFunction)
                pointerHashMap->lockKeyFunction(key);
            if (pointerHashMap->lockValueFunction)
                pointerHashMap->lockValueFunction(value);
            if (pointerHashMap->unlockKeyFunction)
                pointerHashMap->unlockKeyFunction(position.current->key);
            if (pointerHashMap->unlockValueFunction)
                pointerHashMap->unlockValueFunction(position.current->value);
            position.current->key = key;
            position.current->value = value;
            return Nucleus_Status_Success;
        }
        else
        {
            return Nucleus_Status_Exists;
        }
    }
    Node *node = NULL;
    if (pointerHashMap->unused)
    {
        node = pointerHashMap->unused; pointerHashMap->unused = node->next;
    }
    else
    {
        status = Nucleus_allocateMemory((void **)&node, sizeof(Node));
        if (status) return status;
    }
    if (pointerHashMap->lockKeyFunction)
        pointerHashMap->lockKeyFunction(key);
    if (pointerHashMap->lockValueFunction)
        pointerHashMap->lockValueFunction(value);
    node->key = key;
    node->value = value;
    node->next = pointerHashMap->buckets[position.hashIndex];
    pointerHashMap->buckets[position.hashIndex] = node;
    pointerHashMap->size++;
    /// TODO: Invoke Optimize which resizes the hash map. If resizing fails, there is no error.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_get
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        void **value
    )
{
    Position position;
    Nucleus_Status status = getPosition(pointerHashMap, key, &position);
    if (status) return status;
    if (position.current)
    {
        *value = position.current->value;
        return Nucleus_Status_Success;
    }
    else
    {
        return Nucleus_Status_NotExists;
    }
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_clear
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap
    )
{
    clear(pointerHashMap);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getSize
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        Nucleus_Size *size
    )
 {
    if (Nucleus_Unlikely(!pointerHashMap || !size)) return Nucleus_Status_InvalidArgument;
    *size = pointerHashMap->size;
    return Nucleus_Status_Success;
 }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getCapacity
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        Nucleus_Size *capacity
    )
{
    if (Nucleus_Unlikely(!pointerHashMap || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = pointerHashMap->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_removeExtended
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        void **storedKey,
        void **storedValue,
        Nucleus_Boolean invokeUnlockKey,
        Nucleus_Boolean invokeUnlockValue
    )
{
    ExtendedPosition position;
    Nucleus_Status status = getExtendedPosition(pointerHashMap, key, &position);
    if (status) return status;
    if (position.current)
    {
        *storedKey = position.current->key;
        *storedValue = position.current->value;
        if (invokeUnlockKey && pointerHashMap->unlockKeyFunction)
        {
            pointerHashMap->unlockKeyFunction(*storedKey);
        }
        if (invokeUnlockValue && pointerHashMap->unlockValueFunction)
        {
            pointerHashMap->unlockValueFunction(*storedValue);
        }
        *position.previous = position.current->next;
        pointerHashMap->size--;
        position.current->key = NULL;
        position.current->value = NULL;
        position.current->next = pointerHashMap->unused;
        pointerHashMap->unused = position.current;
        return Nucleus_Status_Success;
    }
    else return Nucleus_Status_NotExists;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_remove
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key
    )
{
    ExtendedPosition position;
    Nucleus_Status status = getExtendedPosition(pointerHashMap, key, &position);
    if (status) return status;
    if (position.current)
    {
		void *storedKey = position.current->key,
		     *storedValue = position.current->value;
        if (pointerHashMap->unlockKeyFunction)
        {
            pointerHashMap->unlockKeyFunction(storedKey);
        }
        if (pointerHashMap->unlockValueFunction)
        {
            pointerHashMap->unlockValueFunction(storedValue);
        }
        *position.previous = position.current->next;
        pointerHashMap->size--;
        position.current->key = NULL;
        position.current->value = NULL;
        position.current->next = pointerHashMap->unused;
        pointerHashMap->unused = position.current;
        return Nucleus_Status_Success;
    }
    else return Nucleus_Status_NotExists;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined (Nucleus_Collections_PointerHashMap_WithConstantEnumerator) && 1 == Nucleus_Collections_PointerHashMap_WithConstantEnumerator

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_ConstantEnumerator_initialize
    (
        Nucleus_Collections_PointerHashMap_ConstantEnumerator *enumerator,
        Nucleus_Collections_PointerHashMap *source
    )
{
    enumerator->source = source;
    enumerator->bucketIndex = 0;
    enumerator->current = source->buckets[0];
    while (NULL == enumerator->current && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
        enumerator->current = enumerator->source->buckets[enumerator->bucketIndex];
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize
    (
        Nucleus_Collections_PointerHashMap_ConstantEnumerator *enumerator
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status 
Nucleus_Collections_PointerHashMap_ConstantEnumerator_next
    (
        Nucleus_Collections_PointerHashMap_ConstantEnumerator *enumerator
    )
{
    if (enumerator->current)
    {
        enumerator->current = enumerator->current->next;
    }
    while (NULL == enumerator->current && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
        enumerator->current = enumerator->source->buckets[enumerator->bucketIndex];
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_ConstantEnumerator_hasValue
    (
        Nucleus_Collections_PointerHashMap_ConstantEnumerator *enumerator,
        Nucleus_Boolean *hasValue
    )
{
    if (Nucleus_Unlikely(!enumerator || !hasValue)) return Nucleus_Status_InvalidArgument;
    *hasValue = NULL != enumerator->current;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_ConstantEnumerator_getValue
    (
        Nucleus_Collections_PointerHashMap_ConstantEnumerator *enumerator,
        void **key,
        void **value
    )
{
    if (Nucleus_Unlikely(!enumerator || !key || !value)) return Nucleus_Status_InvalidArgument;
    if (!enumerator->current) return Nucleus_Status_InvalidArgument;
    *key = enumerator->current->key;
    *value = enumerator->current->value;
    return Nucleus_Status_Success;
}

#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined (Nucleus_Collections_PointerHashMap_WithEnumerator) && 1 == Nucleus_Collections_PointerHashMap_WithEnumerator

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_initialize
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        Nucleus_Collections_PointerHashMap *source
    )
{
    enumerator->source = source;
    enumerator->bucketIndex = 0;
	enumerator->previous = &source->buckets[0];
    enumerator->current = source->buckets[0];
    while (NULL == enumerator->current && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
		enumerator->previous = &(enumerator->source->buckets[enumerator->bucketIndex]);
        enumerator->current = *(enumerator->previous);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_uninitialize
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status 
Nucleus_Collections_PointerHashMap_Enumerator_next
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator
    )
{
    if (enumerator->current)
    {
		enumerator->previous = &enumerator->current->next;
        enumerator->current = *(enumerator->previous);
    }
    while (NULL == enumerator->current && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
		enumerator->previous = &(enumerator->source->buckets[enumerator->bucketIndex]);
        enumerator->current = *(enumerator->previous);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_hasValue
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        Nucleus_Boolean *hasValue
    )
{
    if (Nucleus_Unlikely(!enumerator || !hasValue)) return Nucleus_Status_InvalidArgument;
    *hasValue = NULL != enumerator->current;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_getValue
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        void **key,
        void **value
    )
{
    if (Nucleus_Unlikely(!enumerator || !key || !value)) return Nucleus_Status_InvalidArgument;
    if (!enumerator->current) return Nucleus_Status_InvalidArgument;
    *key = enumerator->current->key;
    *value = enumerator->current->value;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_remove
	(
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator
	)
{
	Node **previous = enumerator->previous;
	Node *current = enumerator->current;
	// Predecessor points to successor.
	*previous = current->next;
	// Decrement size by 1.
	enumerator->source->size--;
	// Relinquish node.
	current->key = NULL;
    current->value = NULL;
    current->next = enumerator->source->unused;
    enumerator->source->unused = current;
	// Advance iterator.
	enumerator->previous = previous;
	enumerator->current = *previous;
	Nucleus_Collections_PointerHashMap_Enumerator_next(enumerator);
	// Return success.
	return Nucleus_Status_Success;
}

#endif
