// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap-private.h.i"

Nucleus_NonNull() static Nucleus_Status
getExtendedPosition
	(
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        ExtendedPosition *position
	)
{
    pointerHashMap->hashKeyFunction(key, &position->hashValue);
    position->hashIndex = position->hashValue % pointerHashMap->capacity;
    position->current = NULL;
	position->previous = NULL;
	Node **previous = &pointerHashMap->buckets[position->hashIndex];
	Node *current = *previous;
    while (current)
    {
        Nucleus_Boolean equalTo;
        pointerHashMap->keyEqualToKeyFunction(key, current->key, &equalTo);
        if (equalTo)
        {
			position->previous = previous;
            position->current = current;
            break;
        }
		else
		{
			previous = &current->next;
			current = current->next;
		}
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status 
getPosition
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap,
        void *key,
        Position *position
    )
{
    if (!pointerHashMap) return Nucleus_Status_InvalidArgument;
    pointerHashMap->hashKeyFunction(key, &position->hashValue);
    position->hashIndex = position->hashValue % pointerHashMap->capacity;
    position->current = NULL;
    for (Node *node = pointerHashMap->buckets[position->hashIndex];
         NULL != node; node = node->next)
    {
        Nucleus_Boolean equalTo;
        pointerHashMap->keyEqualToKeyFunction(key, node->key, &equalTo);
        if (equalTo)
        {
            position->current = node;
            break;
        }
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static void
clear
    (
        Nucleus_Collections_PointerHashMap *pointerHashMap
    )
{
    for (Nucleus_Size i = 0, n = pointerHashMap->capacity; i < n; ++i)
    {
        Node **bucket = &(pointerHashMap->buckets[i]);
        while (*bucket)
        {
            Node *node = *bucket; *bucket = node->next;
            if (pointerHashMap->unlockKeyFunction)
                pointerHashMap->unlockKeyFunction(node->key);
            if (pointerHashMap->unlockValueFunction)
                pointerHashMap->unlockValueFunction(node->value);
            pointerHashMap->size--;
            node->next = pointerHashMap->unused;
            pointerHashMap->unused = node;
        }
    }
}
