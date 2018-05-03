// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/FileSystem/directoryEnumerator.h"

typedef struct Nucleus_DirectoryEnumeratorWindows Nucleus_DirectoryEnumeratorWindows;

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorWindows_construct
    (
        Nucleus_DirectoryEnumeratorWindows *directoryEnumerator
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_DirectoryEnumeratorWindows_create
    (
        Nucleus_DirectoryEnumeratorWindows **directoryEnumerator
    );

#endif
