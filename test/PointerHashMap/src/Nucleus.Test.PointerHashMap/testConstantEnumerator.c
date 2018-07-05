#include "Nucleus.Test.PointerHashMap/testConstantEnumerator.h"

#include "Nucleus/Memory.h"
#include "Nucleus/Hash/Memory.h"
#include <string.h>

typedef struct Entry
{
    const char *key;
    const char *value;
} Entry;

Nucleus_NonNull() static Nucleus_Status
hashKeyFunction
    (
        const char *key,
        Nucleus_HashValue *hashValue
    )
{ 
    if (Nucleus_Unlikely(!key || !hashValue)) return Nucleus_Status_InvalidArgument;
    return Nucleus_hashMemory(key, strlen(key), hashValue);
}

Nucleus_NonNull() static Nucleus_Status
equalToKeyFunction
    (
        const char *leftKey,
        const char *rightKey,
        Nucleus_Boolean *equalTo
    )
{
    if (Nucleus_Unlikely(!leftKey || !rightKey || !equalTo)) return Nucleus_Status_InvalidArgument;
    *equalTo = !strcmp(leftKey, rightKey);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
unlockKeyFunction
    (
        char *key
    )
{
    if (Nucleus_Unlikely(!key)) return Nucleus_Status_InvalidArgument;
    Nucleus_deallocateMemory(key);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
unlockValueFunction
    (
        char *value
    )
{
    if (Nucleus_Unlikely(!value)) return Nucleus_Status_InvalidArgument;
    Nucleus_deallocateMemory(value);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
test1
    (
        Nucleus_Collections_PointerHashMap *collection,
        const Entry *entries,
        Nucleus_Size numberOfEntries,
        Nucleus_Size *arities
    )
{
    Nucleus_Status status;
    for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
    {
        char *k = strdup(entries[i].key);
        char *v = strdup(entries[i].value);
        if (!k || !v)
        {
            Nucleus_deallocateMemory(v);
            Nucleus_deallocateMemory(k);
            status = Nucleus_Status_InternalError;
            return status; 
        }
        status = Nucleus_Collections_PointerHashMap_set(collection, (void *)k,
                                                                    (void *)v,
                                                                    false);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_deallocateMemory(v);
            Nucleus_deallocateMemory(k);
            return status;     
        }
    }

    Nucleus_Collections_PointerHashMap_ConstantEnumerator enumerator;
    status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_initialize(&enumerator, collection);
    if (Nucleus_Unlikely(status)) return status;
    while (true)
    {
        Nucleus_Boolean hasValue;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_hasValue(&enumerator, &hasValue);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&enumerator);
            return status;
        }
        if (!hasValue)
        {
            break;
        }
        void *key, *value;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_getValue(&enumerator, &key, &value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&enumerator);
            return status;
        }
        Nucleus_Boolean found = Nucleus_Boolean_False;
        for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
        {
            if (!strcmp(key, entries[i].key) && !strcmp(value, entries[i].value))
            {
                found = Nucleus_Boolean_True;
                arities[i]++;
                break;
            }
        }
        if (!found)
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&enumerator);
            status = Nucleus_Status_InternalError;
            return status;
        }
        Nucleus_Collections_PointerHashMap_ConstantEnumerator_next(&enumerator);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&enumerator);
            return status;
        }
    }
    Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&enumerator);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
test0
    (
        const Entry *entries,
        Nucleus_Size numberOfEntries
    )
{
    if (Nucleus_Unlikely(!entries)) return Nucleus_Status_InvalidArgument;
    Nucleus_Collections_PointerHashMap pointerHashMap;
    Nucleus_Status status;
    
    Nucleus_Size *arities;
    status = Nucleus_allocateArrayMemory((void **)&arities, numberOfEntries, sizeof(Nucleus_Size));
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
    {
        arities[i] = 0;
    }   
    status = Nucleus_Collections_PointerHashMap_initialize(&pointerHashMap,
                                                           0,
                                                           NUCLEUS_LOCKFUNCTION(NULL),
                                                           NUCLEUS_UNLOCKFUNCTION(&unlockKeyFunction),
                                                           NUCLEUS_HASHFUNCTION(&hashKeyFunction),
                                                           NUCLEUS_EQUALTOFUNCTION(&equalToKeyFunction),
                                                           NUCLEUS_LOCKFUNCTION(NULL),
                                                           NUCLEUS_UNLOCKFUNCTION(&unlockValueFunction));
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(arities);
        arities = NULL;
        return status;
    }
    status = test1(&pointerHashMap, entries, numberOfEntries, arities);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(arities);
        arities = NULL;
        Nucleus_Collections_PointerHashMap_uninitialize(&pointerHashMap);
        return status;
    }
    for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
    {
        if (arities[i] != 1)
        {
            status = Nucleus_Status_InternalError;
            Nucleus_deallocateMemory(arities);
            arities = NULL;
            Nucleus_Collections_PointerHashMap_uninitialize(&pointerHashMap);
            return status;
        }
    }
    Nucleus_deallocateMemory(arities);
    arities = NULL;
    Nucleus_Collections_PointerHashMap_uninitialize(&pointerHashMap);
    return Nucleus_Status_Success;
}

Nucleus_Status
testConstantEnumerator
    (
    )
{
    Nucleus_Status status;
    {
        static const Entry entries[] = 
        {
            { "0", "a" },
            { "1", "b" },
            { "2", "c" },
            { "3", "d" },
        };
        status = test0(entries, sizeof(entries) / sizeof(Entry));
        if (Nucleus_Unlikely(status)) return status;
    }
    {
    }
    return Nucleus_Status_Success;
}
