// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux)

#include "Nucleus/FileSystem/DirectoryEnumerator.h"

typedef struct Nucleus_DirectoryEnumeratorLinux Nucleus_DirectoryEnumeratorLinux;

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorLinux_construct
    (
        Nucleus_DirectoryEnumeratorLinux *directoryEnumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorLinux_create
    (
        Nucleus_DirectoryEnumeratorLinux **directoryEnumerator
    );

#endif
