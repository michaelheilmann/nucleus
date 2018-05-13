// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem.h"
#include "Nucleus/Memory.h"
#include <string.h>

typedef enum ExpectedFileType
{
    ExpectedFileType_Directory,
    ExpectedFileType_Regular,
} ExpectedFileType;

typedef struct ExpectedFile
{
    const char *expectedFilename;
    ExpectedFileType expectedFileType;
} ExpectedFile;

static const ExpectedFile g_expectedFiles1[] = 
{
    { "regular", ExpectedFileType_Regular },
    { "directory", ExpectedFileType_Directory },
};

static const Nucleus_Size g_numberOfExpectedFiles1 = sizeof(g_expectedFiles1) / sizeof(ExpectedFile);

Nucleus_NonNull() static Nucleus_Status
test
    (
        const char *pathname,
        const ExpectedFile *expectedFiles,
        Nucleus_Size numberOfExpectedFiles
    )
{
    if (!pathname) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_Status_Success;

    int *count = NULL;
    status = Nucleus_allocateArrayMemory((void **)&count, numberOfExpectedFiles, sizeof(int));
    if (status) return status;

    for (Nucleus_Size i = 0, n = numberOfExpectedFiles; i < n; ++i)
    {
        count[i] = 0;
    }

    Nucleus_DirectoryEnumerator *directoryEnumerator = NULL;
    status = Nucleus_createDirectoryEnumerator(&directoryEnumerator);
    if (status)
    {
        Nucleus_deallocateMemory(count);
        return status;
    }

    status = Nucleus_DirectoryEnumerator_open(directoryEnumerator, pathname);
    if (status) goto End;

    while (1)
    {
        Nucleus_Boolean hasValue;
        status = Nucleus_DirectoryEnumerator_hasValue(directoryEnumerator, &hasValue);
        if (status) goto End;
        
        if (hasValue)
        {
            const char *bytesOfFilename;
            Nucleus_Size numberOfBytesInFilename;
            status = Nucleus_DirectoryEnumerator_getValue(directoryEnumerator, &bytesOfFilename, &numberOfBytesInFilename);
            if (status) goto End;

            Nucleus_Boolean expected = false;
            for (Nucleus_Size i = 0, n = numberOfExpectedFiles; i < n; ++i)
            {
                const char *expectedBytesOfFilename = expectedFiles[i].expectedFilename;
                Nucleus_Size expectedNumberOfBytesInFilename = strlen(expectedBytesOfFilename) + 1;
                if (expectedNumberOfBytesInFilename == numberOfBytesInFilename &&
                    !memcmp(expectedBytesOfFilename, bytesOfFilename, numberOfBytesInFilename))
                {
                    count[i]++;
                    expected = true;
                    break;
                }
            }
            if (!expected)
            { status = Nucleus_Status_InternalError; goto End; }

            status = Nucleus_DirectoryEnumerator_nextValue(directoryEnumerator);
            if (status) goto End;
        }
        else
        {
            break;
        }
    }
End:
    for (Nucleus_Size i = 0, n = numberOfExpectedFiles; i < n; ++i)
    {
        if (count[i] != 1)
        {
            status = Nucleus_Status_InternalError;
            break;
        }
    }
    Nucleus_DirectoryEnumerator_destroy(directoryEnumerator);
    Nucleus_deallocateMemory(count);
    return status;
}

int main(int argc, char **argv)
{
    if (test("data", g_expectedFiles1, g_numberOfExpectedFiles1) ||
        test("data/", g_expectedFiles1, g_numberOfExpectedFiles1))
    { return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}
