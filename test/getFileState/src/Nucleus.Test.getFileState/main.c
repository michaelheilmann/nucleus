// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/FileSystem.h"

static Nucleus_Status
test
    (
    )
{
    Nucleus_Status status;
    Nucleus_FileState fileState;
    //
    status = Nucleus_getFileState("data/directory", &fileState);
    if (status) return status;
    if (fileState != Nucleus_FileState_IsDirectory) return Nucleus_Status_InternalError;
    //
    status = Nucleus_getFileState("data/regular", &fileState);
    if (status) return status;
    if (fileState != Nucleus_FileState_IsRegular) return Nucleus_Status_InternalError;
    //
    status = Nucleus_getFileState("data/notFound", &fileState);
    if (status) return status;
    if (fileState != Nucleus_FileState_NotFound) return Nucleus_Status_InternalError;
    //
    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (test())
    { return EXIT_FAILURE; }
    else
    { return EXIT_SUCCESS; }
}
