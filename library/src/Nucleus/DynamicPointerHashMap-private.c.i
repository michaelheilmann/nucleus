// Copyright (c) Michael Heilmann 2018
#include "Nucleus/DynamicPointerHashMap-private.h.i"

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap,
        void *key,
        Position *position
    )
{
    if (!dynamicPointerHashMap) return Nucleus_Status_InvalidArgument;
    dynamicPointerHashMap->hashKeyFunction(key, &position->hashValue);
    position->hashIndex = position->hashValue % dynamicPointerHashMap->capacity;
    position->node = NULL;
    for (Nucleus_DynamicPointerHashMap_Node *node = dynamicPointerHashMap->buckets[position->hashIndex];
         NULL != node; node = node->next)
    {
        bool equalTo;
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
        Nucleus_DynamicPointerHashMap *dynamicPointerHashMap
    )
{
    for (size_t i = 0, n = dynamicPointerHashMap->capacity; i < n; ++i)
    {
        Nucleus_DynamicPointerHashMap_Node **bucket = &(dynamicPointerHashMap->buckets[i]);
        while (*bucket)
        {
            Nucleus_DynamicPointerHashMap_Node *node = *bucket; *bucket = node->next;
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