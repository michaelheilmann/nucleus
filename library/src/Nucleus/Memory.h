// Copyright (c) 2017, 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_allocateMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
    (
        void **p,
        Nucleus_Size n
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_reallocateMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateMemory
    (
        void **p,
        Nucleus_Size n
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_allocateArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
    (
        void **p,
        Nucleus_Size n,
        Nucleus_Size m
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_reallocateArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_reallocateArrayMemory
    (
        void **p,
        Nucleus_Size n,
        Nucleus_Size m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_deallocateMemory.md
Nucleus_NoError() void
Nucleus_deallocateMemory
    (
        void *p
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_fillMemory.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillMemory
    (
        void *p,
        int v,
        Nucleus_Size n
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_fillArrayMemory.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_fillArrayMemory
    (
        void *p,
        int v,
        Nucleus_Size n,
        Nucleus_Size m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_copyMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_copyArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_compareMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
    (
        const void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Boolean *r
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_compareArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
    (
        const void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m,
        Nucleus_Boolean *r
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_cloneMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_cloneMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n
     );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_cloneArrayMemory.md
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_cloneArrayMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    );
