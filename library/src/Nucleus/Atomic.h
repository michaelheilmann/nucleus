// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Integer.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_increment
    (
        volatile Nucleus_Integer *v
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_decrement
    (
        volatile Nucleus_Integer *v
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_decrementAndTest
    (
        volatile Nucleus_Integer *v,
        Nucleus_Boolean *r
    );
