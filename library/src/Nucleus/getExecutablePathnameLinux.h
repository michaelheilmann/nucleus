// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_getExecutablePathname.md
Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutablePathnameLinux
    (
        char **pathname
    );

#endif
