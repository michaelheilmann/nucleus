// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap-private.c.i"

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_initialize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size initialCapacity,
        Nucleus_LockFunction *lockKeyFunction,
        Nucleus_UnlockFunction *unlockKeyFunction,
        Nucleus_HashFunction *hashKeyFunction,
        Nucleus_EqualToFunction *keyEqualToKeyFunction,
        Nucleus_LockFunction *lockValueFunction,
        Nucleus_UnlockFunction *unlockValueFunction
    )
{
    if (Nucleus_Unlikely(!dynamicPointerHashMap)) return Nucleus_Status_InvalidArgument;
    
    initialCapacity = initialCapacity > 0 ? initialCapacity : 1;
    
    Nucleus_Status status = Nucleus_allocateArrayMemory((void **)&dynamicPointerHashMap->buckets,
                                                        initialCapacity,
                                                        sizeof(Node *));
    if (Nucleus_Unlikely(status)) return status;
    for (Nucleus_Size i = 0, n = initialCapacity; i < n; ++i)
    {
        dynamicPointerHashMap->buckets[i] = NULL;
    }

    dynamicPointerHashMap->size = 0;
    dynamicPointerHashMap->capacity = initialCapacity;

    dynamicPointerHashMap->unused = NULL;

    dynamicPointerHashMap->lockKeyFunction = lockKeyFunction;
    dynamicPointerHashMap->unlockKeyFunction = unlockKeyFunction;
    dynamicPointerHashMap->hashKeyFunction = hashKeyFunction;
    dynamicPointerHashMap->keyEqualToKeyFunction = keyEqualToKeyFunction;
    dynamicPointerHashMap->lockValueFunction = lockValueFunction;
    dynamicPointerHashMap->unlockValueFunction = unlockValueFunction;
    
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_uninitialize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    )
{
    clear(dynamicPointerHashMap);

    Nucleus_deallocateMemory(dynamicPointerHashMap->buckets);
    dynamicPointerHashMap->buckets = NULL;
    dynamicPointerHashMap->capacity = 0;

    while(dynamicPointerHashMap->unused)
    {
        Node *node = dynamicPointerHashMap->unused;
        dynamicPointerHashMap->unused = node->next;
        Nucleus_deallocateMemory(node);
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Collections_PointerHashMap_set
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        void *value,
        Nucleus_Boolean replace
    )
{
    Position position;
    Nucleus_Status status = getPosition(dynamicPointerHashMap, key, &position);
    if (status) return status;
    if (position.node)
    {
        if (replace)
        {
            if (dynamicPointerHashMap->lockKeyFunction)
                dynamicPointerHashMap->lockKeyFunction(key);
            if (dynamicPointerHashMap->lockValueFunction)
                dynamicPointerHashMap->lockValueFunction(value);
            if (dynamicPointerHashMap->unlockKeyFunction)
                dynamicPointerHashMap->unlockKeyFunction(position.node->key);
            if (dynamicPointerHashMap->unlockValueFunction)
                dynamicPointerHashMap->unlockValueFunction(position.node->value);
            position.node->key = key;
            position.node->value = value;
            return Nucleus_Status_Success;
        }
        else
        {
            return Nucleus_Status_Exists;
        }
    }
    Node *node = NULL;
    if (dynamicPointerHashMap->unused)
    {
        node = dynamicPointerHashMap->unused; dynamicPointerHashMap->unused = node->next;
    }
    else
    {
        status = Nucleus_allocateMemory((void **)&node, sizeof(Node));
        if (status) return status;
    }
    if (dynamicPointerHashMap->lockKeyFunction)
        dynamicPointerHashMap->lockKeyFunction(key);
    if (dynamicPointerHashMap->lockValueFunction)
        dynamicPointerHashMap->lockValueFunction(value);
    node->key = key;
    node->value = value;
    node->next = dynamicPointerHashMap->buckets[position.hashIndex];
    dynamicPointerHashMap->buckets[position.hashIndex] = node;
    dynamicPointerHashMap->size++;
    /// TODO: Invoke Optimize which resizes the hash map. If resizing fails, there is no error.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_get
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        void **value
    )
{
    Position position;
    Nucleus_Status status = getPosition(dynamicPointerHashMap, key, &position);
    if (status) return status;
    if (position.node) { *value = position.node->value; return Nucleus_Status_Success; }
    else return Nucleus_Status_NotExists;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_clear
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    )
{
    clear(dynamicPointerHashMap);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getSize
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size *size
    )
 {
    if (Nucleus_Unlikely(!dynamicPointerHashMap || !size)) return Nucleus_Status_InvalidArgument;
    *size = dynamicPointerHashMap->size;
    return Nucleus_Status_Success;
 }

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_getCapacity
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        Nucleus_Size *capacity
    )
{
    if (Nucleus_Unlikely(!dynamicPointerHashMap || !capacity)) return Nucleus_Status_InvalidArgument;
    *capacity = dynamicPointerHashMap->capacity;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Collections_PointerHashMap_Enumerator_initialize
    (
        Nucleus_Collections_PointerHashMap_Enumerator *enumerator,
        Nucleus_Collections_PointerHashMap *source
    )
{
    enumerator->source = source;
    enumerator->bucketIndex = 0;
    enumerator->node = source->buckets[0];
    while (NULL == enumerator->node && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
        enumerator->node = enumerator->source->buckets[enumerator->bucketIndex];
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
    if (enumerator->node)
    {
        enumerator->node = enumerator->node->next;
    }
    while (NULL == enumerator->node && enumerator->bucketIndex < enumerator->source->capacity - 1) // Secure as capacity is always positive.
    {
        enumerator->bucketIndex++;
        enumerator->node = enumerator->source->buckets[enumerator->bucketIndex];
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
    *hasValue = NULL != enumerator->node;
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
    if (!enumerator->node) return Nucleus_Status_InvalidArgument;
    *key = enumerator->node->key;
    *value = enumerator->node->value;
    return Nucleus_Status_Success;
}
