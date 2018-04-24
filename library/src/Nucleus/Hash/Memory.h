// Copyright (c) Michael Heilmann 2017, 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hashMemory.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashMemory
    (
        const void *p,
        Nucleus_Size n,
        Nucleus_HashValue *hv
    );
