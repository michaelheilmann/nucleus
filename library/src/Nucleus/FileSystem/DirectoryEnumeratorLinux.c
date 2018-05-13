// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem/DirectoryEnumeratorLinux.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)

#include "Nucleus/Memory.h"
#include <errno.h>
#if defined(Nucleus_Platform_Osx)
	#include <sys/types.h>
	#include <sys/dir.h>
#else
	#include <dirent.h>
#endif
#include <string.h> // For strlen().

struct Nucleus_DirectoryEnumeratorLinux
{
    Nucleus_DirectoryEnumerator parent;
    DIR *dir;
    struct dirent *dirent;
}; // struct Nucleus_DirectoryEnumeratorLinux

Nucleus_NonNull() static Nucleus_Status
openImpl
    (
        Nucleus_DirectoryEnumeratorLinux *directoryEnumerator,
        const char *pathname
    )
{
    // Clear errno.
    errno = 0;
    // Open directory.
    directoryEnumerator->dir = opendir(pathname);
    if (!directoryEnumerator->dir)
    {
        errno = 0;
        return Nucleus_Status_EnvironmentFailed; // TODO: Be more specific here what exactly is the cause of the error.
    }
    // Read first directory entry.
    directoryEnumerator->dirent = readdir(directoryEnumerator->dir);
    if (!directoryEnumerator->dirent)
    {
        closedir(directoryEnumerator->dir);
        directoryEnumerator->dir = NULL;
        if (errno)
        {
            errno = 0;
            return Nucleus_Status_EnvironmentFailed; // TODO: Be more specific here what exactly is the cause of the error.
        }
        return Nucleus_Status_Success;
    }
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->pathname = directoryEnumerator->dirent->d_name;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state = Nucleus_DirectoryEnumerator_State_Open;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
closeImpl
    (
        Nucleus_DirectoryEnumeratorLinux *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    if (NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state == Nucleus_DirectoryEnumerator_State_Open)
    {
        directoryEnumerator->dirent = NULL;
        closedir(directoryEnumerator->dir);
        directoryEnumerator->dir = NULL;
        NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state = Nucleus_DirectoryEnumerator_State_Closed;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
nextValueImpl
    (
        Nucleus_DirectoryEnumeratorLinux *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    if (NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state == Nucleus_DirectoryEnumerator_State_Closed)
    {
        return Nucleus_Status_FileClosed;
    }
    //
    errno = 0;
    directoryEnumerator->dirent = readdir(directoryEnumerator->dir);
    if (!directoryEnumerator->dirent)
    {
        Nucleus_DirectoryEnumerator_close(NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator));
        if (errno)
        {
            errno = 0;
            return Nucleus_Status_EnvironmentFailed;
        }
    }
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->pathname = directoryEnumerator->dirent->d_name;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorLinux_construct
    (
        Nucleus_DirectoryEnumeratorLinux *directoryEnumerator
    )
{
    Nucleus_Status status;
    status = Nucleus_DirectoryEnumerator_construct(NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator));
    if (status) return status;
    directoryEnumerator->dir = NULL;
    directoryEnumerator->dirent = NULL;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->openImpl = (Nucleus_Status (*)(Nucleus_DirectoryEnumerator *, const char *))&openImpl;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->closeImpl = (Nucleus_Status (*)(Nucleus_DirectoryEnumerator *))&closeImpl;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->nextValueImpl = (Nucleus_Status (*)(Nucleus_DirectoryEnumerator *))&nextValueImpl;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorLinux_create
    (
        Nucleus_DirectoryEnumeratorLinux **directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator))
    { return Nucleus_Status_InvalidArgument; }
    //
    Nucleus_Status status;
    Nucleus_DirectoryEnumeratorLinux *self;
    //
    status = Nucleus_allocateMemory((void **)&self, sizeof(Nucleus_DirectoryEnumeratorLinux));
    if (status)
    { return status; }
    //
    status = Nucleus_DirectoryEnumeratorLinux_construct(self);
    if (status)
    {
        Nucleus_deallocateMemory(self);
        return status;
    }
    //
    *directoryEnumerator = self;
    //
    return Nucleus_Status_Success;
}

#endif
