// Copyright (c) Michael Heilmann 2018
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "Nucleus/Annotations.h"

Nucleus_NonNull(3) bool
Nucleus_safeAdd
    (
        size_t x,
        size_t y,
        size_t *z
    );

Nucleus_NonNull(3) bool
Nucleus_safeMul
    (
        size_t x,
        size_t y,
        size_t *z
    );
