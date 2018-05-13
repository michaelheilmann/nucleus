// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include <stddef.h> // For size_t.

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSizeWindows
    (
        size_t *pageSize
    );

#endif
