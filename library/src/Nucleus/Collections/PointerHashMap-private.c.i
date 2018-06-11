// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap-private.h.i"

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap,
        void *key,
        Position *position
    )
{
    if (!dynamicPointerHashMap) return Nucleus_Status_InvalidArgument;
    dynamicPointerHashMap->hashKeyFunction(key, &position->hashValue);
    position->hashIndex = position->hashValue % dynamicPointerHashMap->capacity;
    position->node = NULL;
    for (Node *node = dynamicPointerHashMap->buckets[position->hashIndex];
         NULL != node; node = node->next)
    {
        Nucleus_Boolean equalTo;
        dynamicPointerHashMap->keyEqualToKeyFunction(key, node->key, &equalTo);
        if (equalTo)
        {
            position->node = node;
            break;
        }
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static void
clear
    (
        Nucleus_Collections_PointerHashMap *dynamicPointerHashMap
    )
{
    for (Nucleus_Size i = 0, n = dynamicPointerHashMap->capacity; i < n; ++i)
    {
        Node **bucket = &(dynamicPointerHashMap->buckets[i]);
        while (*bucket)
        {
            Node *node = *bucket; *bucket = node->next;
            if (dynamicPointerHashMap->unlockKeyFunction)
                dynamicPointerHashMap->unlockKeyFunction(node->key);
            if (dynamicPointerHashMap->unlockValueFunction)
                dynamicPointerHashMap->unlockValueFunction(node->value);
            dynamicPointerHashMap->size--;
            node->next = dynamicPointerHashMap->unused;
            dynamicPointerHashMap->unused = node;
        }
    }
}
