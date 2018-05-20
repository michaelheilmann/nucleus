// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/FileSystem/DirectoryEnumerator.h"

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
