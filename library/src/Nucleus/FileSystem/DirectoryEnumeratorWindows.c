// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem/DirectoryEnumeratorWindows.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/IncludesWindows.h"
#include "Nucleus/Memory.h"

struct Nucleus_DirectoryEnumeratorWindows
{
    Nucleus_DirectoryEnumerator parent;
    HANDLE handle;
    WIN32_FIND_DATAA data;
}; // struct Nucleus_DirectoryEnumeratorWindows

// "pathname" must not be empty.
// "pathname" must not end with '/' or '\'.
// "pathname" must not contain the wildcards '?' or '*'.
Nucleus_NonNull() static Nucleus_Status
openImpl(Nucleus_DirectoryEnumeratorWindows *directoryEnumerator, const char *pathname)
{
    // Validate arguments.
    // directoryEnumerator and pathname must not be null.
    if (Nucleus_Unlikely(!directoryEnumerator || !pathname))
    { return Nucleus_Status_InvalidArgument; }
    // Validate arguments.
    // pathname must not be empty.
    Nucleus_Size size = strlen(pathname);
    if (!size) return Nucleus_Status_InvalidArgument;
    // Validate arguments.
    // pathname must not contain wildcards.
    for (Nucleus_Size i = 0, n = size; i < n; ++i)
    {
        if (pathname[i] == '?' || pathname[i] == '*')
        { return Nucleus_Status_InvalidArgument; }
    }
    // Ensure pathname ends with a reverse solidus followed by a star.
    // Create search string.
    char *searchString;
    if (pathname[size - 1] != '\\' && pathname[size - 1] != '/')
    {
        Nucleus_Status status = Nucleus_allocateMemory((void **)&searchString, size + 3);
        if (status) return status;
        strcpy(searchString, pathname);
        searchString[size + 0] = '/';
        searchString[size + 1] = '*';
        searchString[size + 2] = '\0';
    }
    else
    {
        Nucleus_Status status = Nucleus_allocateMemory((void **)&searchString, size + 2);
        if (status) return status;
        strcpy(searchString, pathname);
        searchString[size + 0] = '*';
        searchString[size + 1] = '\0';
    }
    // Begin iteration.
    SetLastError(0);
    directoryEnumerator->handle = FindFirstFileA(searchString, &directoryEnumerator->data);
    if (INVALID_HANDLE_VALUE == directoryEnumerator->handle)
    {
        Nucleus_deallocateMemory(searchString);
        DWORD dwLastError = GetLastError();
        SetLastError(0);
        if (dwLastError == ERROR_FILE_NOT_FOUND) return Nucleus_Status_FileDoesNotExist;
        else return Nucleus_Status_EnvironmentFailed;
    }
    Nucleus_deallocateMemory(searchString);
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->pathname = directoryEnumerator->data.cFileName;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state = Nucleus_DirectoryEnumerator_State_Open;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
closeImpl
    (
        Nucleus_DirectoryEnumeratorWindows *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    if (NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state == Nucleus_DirectoryEnumerator_State_Open)
    {
        FindClose(directoryEnumerator->handle);
        directoryEnumerator->handle = INVALID_HANDLE_VALUE;
        NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state = Nucleus_DirectoryEnumerator_State_Closed;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
nextValueImpl
    (
        Nucleus_DirectoryEnumeratorWindows *directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    if (NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->state == Nucleus_DirectoryEnumerator_State_Closed)
    {
        return Nucleus_Status_FileClosed;
    }
    //
    SetLastError(0);
    BOOL result = FindNextFileA(directoryEnumerator->handle, &directoryEnumerator->data);
    if (!result)
    {
        Nucleus_DirectoryEnumerator_close(NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator));
        if (GetLastError() == ERROR_NO_MORE_FILES)
        {
            SetLastError(0);
            return Nucleus_Status_Success;
        }
        else
        {
            SetLastError(0);
            return Nucleus_Status_EnvironmentFailed;
        }
    }
    //
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->pathname = directoryEnumerator->data.cFileName;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorWindows_construct
    (
        Nucleus_DirectoryEnumeratorWindows *directoryEnumerator
    )
{
    Nucleus_Status status;
    status = Nucleus_DirectoryEnumerator_construct(NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator));
    if (status) return status;
    directoryEnumerator->handle = INVALID_HANDLE_VALUE;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->openImpl = (Nucleus_Status(*)(Nucleus_DirectoryEnumerator *, const char *))&openImpl;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->closeImpl = (Nucleus_Status(*)(Nucleus_DirectoryEnumerator *))&closeImpl;
    NUCLEUS_DIRECTORYENUMERATOR(directoryEnumerator)->nextValueImpl = (Nucleus_Status(*)(Nucleus_DirectoryEnumerator *))&nextValueImpl;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorWindows_create
    (
        Nucleus_DirectoryEnumeratorWindows **directoryEnumerator
    )
{
    if (Nucleus_Unlikely(!directoryEnumerator)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_DirectoryEnumeratorWindows *directoryEnumeratorWindows;
    status = Nucleus_allocateMemory((void **)&directoryEnumeratorWindows, sizeof(Nucleus_DirectoryEnumeratorWindows));
    if (status) return status;
    status = Nucleus_DirectoryEnumeratorWindows_construct(directoryEnumeratorWindows);
    if (status)
    {
        Nucleus_deallocateMemory(directoryEnumeratorWindows);
        return status;
    }
    *directoryEnumerator = directoryEnumeratorWindows;
    return Nucleus_Status_Success;
}

#endif
