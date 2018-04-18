// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_combineHashValues
    (
        Nucleus_HashValue x,
        Nucleus_HashValue y,
        Nucleus_HashValue *z
    );
