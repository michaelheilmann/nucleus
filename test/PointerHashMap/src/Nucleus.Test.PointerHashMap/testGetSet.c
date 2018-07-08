#include "Nucleus.Test.PointerHashMap/testGetSet.h"

#include "Nucleus/Memory.h"
#include "Nucleus/C/strdup.h"
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
        const char *p,
        Nucleus_HashValue *hashValue
    )
{ 
    if (Nucleus_Unlikely(!p)) return Nucleus_Status_InvalidArgument;
    return Nucleus_hashMemory(p, strlen(p), hashValue);
}

Nucleus_NonNull() static Nucleus_Status
equalToKeyFunction
    (
        const char *p,
        const char *q,
        Nucleus_Boolean *equalTo
    )
{
    if (Nucleus_Unlikely(!p || !q || !equalTo)) return Nucleus_Status_InvalidArgument;
    *equalTo = !strcmp(p, q);
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
test0
    (
        const Entry *entries,
        Nucleus_Size numberOfEntries
    )
{
    if (Nucleus_Unlikely(!entries)) return Nucleus_Status_InvalidArgument;
    Nucleus_Collections_PointerHashMap pointerHashMap;
    Nucleus_Status status;

    status = Nucleus_Collections_PointerHashMap_initialize(&pointerHashMap,
                                                           0,
                                                           NUCLEUS_LOCKFUNCTION(NULL),
                                                           NUCLEUS_UNLOCKFUNCTION(&unlockKeyFunction),
                                                           NUCLEUS_HASHFUNCTION(&hashKeyFunction),
                                                           NUCLEUS_EQUALTOFUNCTION(&equalToKeyFunction),
                                                           NUCLEUS_LOCKFUNCTION(NULL),
                                                           NUCLEUS_UNLOCKFUNCTION(&unlockValueFunction));
    if (Nucleus_Unlikely(status)) return status;

    for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
    {
        char *k = C_strdup(entries[i].key);
        char *v = C_strdup(entries[i].value);
        if (!k || !v)
        {
            Nucleus_deallocateMemory(v);
            Nucleus_deallocateMemory(k);
            status = Nucleus_Status_InternalError;
            goto Exit; 
        }
        status = Nucleus_Collections_PointerHashMap_set(&pointerHashMap, (void *)k,
                                                                         (void *)v,
                                                                         false);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_deallocateMemory(v);
            Nucleus_deallocateMemory(k);
            goto Exit;     
        }
    }
    Nucleus_Size size;
    status = Nucleus_Collections_PointerHashMap_getSize(&pointerHashMap, &size);
    if (Nucleus_Unlikely(status))
    {
        goto Exit;
    }
    if (size != numberOfEntries)
    {
        status = Nucleus_Status_InternalError;
        goto Exit;
    }
    for (Nucleus_Size i = 0, n = numberOfEntries; i < n; ++i)
    {
        char *v;
        status = Nucleus_Collections_PointerHashMap_get(&pointerHashMap, (void *)entries[i].key,
                                                                         (void **)&v);
        if (Nucleus_Unlikely(status))
        {
            goto Exit;     
        }
        if (!v || strcmp(v, entries[i].value))
        {
            status = Nucleus_Status_InternalError;
            goto Exit;   
        }
    }
    
Exit:
    Nucleus_Collections_PointerHashMap_uninitialize(&pointerHashMap);
    return Nucleus_Status_Success;
}

Nucleus_Status
testGetSet
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
