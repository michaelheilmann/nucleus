#include "Nucleus/FileSystem/DirectoryEnumerator.h"

#include "Nucleus/Memory.h"
#include <string.h>

Nucleus_NonNull() static Nucleus_Status
dotOrDotDotPredicate
    (
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Boolean *accept
    );

Nucleus_NonNull() static Nucleus_Status
dotOrDotDotPredicate
    (
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Boolean *accept
    )
{
    if (Nucleus_Unlikely(!bytes || !accept)) return Nucleus_Status_InvalidArgument;
    if (numberOfBytes == 1 && '.' == bytes[0])
    { *accept = false; return Nucleus_Status_Success; }
    if (numberOfBytes == 2 && '.' == bytes[0] && '.' == bytes[1])
    { *accept = false; return Nucleus_Status_Success; }
    *accept = true;
    return Nucleus_Status_Success;
}


Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_construct
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator))
    { return Nucleus_Status_InvalidArgument; }

    directoryEnumerator->state = Nucleus_DirectoryEnumerator_State_Closed;

    directoryEnumerator->openImpl = NULL;
    directoryEnumerator->closeImpl = NULL;
    directoryEnumerator->nextValueImpl = NULL;

    directoryEnumerator->pathname = NULL;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_DirectoryEnumerator_destroy
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    )
{
    directoryEnumerator->closeImpl(directoryEnumerator);
    Nucleus_deallocateMemory(directoryEnumerator);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_hasValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        Nucleus_Boolean *hasValue
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator || !hasValue)) return Nucleus_Status_InvalidArgument;
    *hasValue = Nucleus_DirectoryEnumerator_State_Closed != directoryEnumerator->state;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_getValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        const char **pathnameBytes,
        Nucleus_Size *pathnameNumberOfBytes
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator || !pathnameBytes || !pathnameNumberOfBytes)) return Nucleus_Status_InvalidArgument;
    if (directoryEnumerator->state == Nucleus_DirectoryEnumerator_State_Closed)
    {
        return Nucleus_Status_FileClosed;
    }
    *pathnameBytes = directoryEnumerator->pathname;
    *pathnameNumberOfBytes = strlen(directoryEnumerator->pathname) + 1;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_nextValue
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;

    Nucleus_Status status;

    // Increment.
    status = directoryEnumerator->nextValueImpl(directoryEnumerator);
    if (status) return status;
    // If the end was reached, stop here.
    if (directoryEnumerator->state == Nucleus_DirectoryEnumerator_State_Closed) return Nucleus_Status_Success;
    // Skip '.' and '..'.
    while (1)
    {
        Nucleus_Boolean accept;
        status = dotOrDotDotPredicate(directoryEnumerator->pathname,
                                      strlen(directoryEnumerator->pathname),
                                      &accept);
        if (status)
        {
            Nucleus_DirectoryEnumerator_close(directoryEnumerator);
            return status;
        }
        if (!accept)
        {
            status = directoryEnumerator->nextValueImpl(directoryEnumerator);
            if (status) return status;
            // If the end was reached, stop here.
            if (directoryEnumerator->state == Nucleus_DirectoryEnumerator_State_Closed) return Nucleus_Status_Success;
        }
        else
        {
            break;
        }
    }
    // Return successfully.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_open
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator,
        const char *pathname
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    Nucleus_DirectoryEnumerator_close(directoryEnumerator);
    Nucleus_Status status = directoryEnumerator->openImpl(directoryEnumerator, pathname);
    if (status) return status;
    // Skip '.' and '..'.
    while (1)
    {
        Nucleus_Boolean accept;
        Nucleus_Status status = dotOrDotDotPredicate(directoryEnumerator->pathname,
                                                     strlen(directoryEnumerator->pathname),
                                                     &accept);
        if (status)
        {
            Nucleus_DirectoryEnumerator_close(directoryEnumerator);
            return status;
        }
        if (!accept)
        {
            status = Nucleus_DirectoryEnumerator_nextValue(directoryEnumerator);
            if (status) return status;
        }
        else
        {
            break;
        }
    }
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumerator_close
    (
        Nucleus_DirectoryEnumerator *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    directoryEnumerator->closeImpl(directoryEnumerator);
    return Nucleus_Status_Success;
}
