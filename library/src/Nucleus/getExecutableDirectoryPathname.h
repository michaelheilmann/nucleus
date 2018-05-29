// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_getExecutableDirectoryPathname.md
Nucleus_NonNull() Nucleus_Status
Nucleus_getExecutableDirectoryPathname
    (
        char **executableDirectoryPathname
    );
