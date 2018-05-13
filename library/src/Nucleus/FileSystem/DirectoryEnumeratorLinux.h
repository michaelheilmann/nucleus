// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)

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
