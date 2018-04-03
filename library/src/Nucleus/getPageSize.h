// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include <stddef.h> // For size_t.

Nucleus_NonNull() Nucleus_Status
Nucleus_getPageSize
    (
        size_t *pageSize
    );
