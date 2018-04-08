// Copyright (c) Michael Heilmann 2017, 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include <stddef.h>
#include <stdbool.h>

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_allocateMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
    (
        void **p,
        size_t n
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_reallocateMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateMemory
    (
        void **p,
        size_t n
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_allocateArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
    (
        void **p,
        size_t n,
        size_t m
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_reallocateArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateArrayMemory
    (
        void **p,
        size_t n,
        size_t m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_deallocateMemory.md
Nucleus_NoError() void
Nucleus_deallocateMemory
    (
        void *p
    );

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillMemory
    (
        void *p,
        int v,
        size_t n
    );

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillArrayMemory
    (
        void *p,
        int v,
        size_t n,
        size_t m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_copyMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        size_t n
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_copyArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
    (
        void *p,
        const void *q,
        size_t n,
        size_t m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_compareMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
    (
        const void *p,
        const void *q,
        size_t n,
        bool *r
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_compareArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
    (
        const void *p,
        const void *q,
        size_t n,
        size_t m,
        bool *r
    );
