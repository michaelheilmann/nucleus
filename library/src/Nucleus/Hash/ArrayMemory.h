// Copyright (c) 2017, 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hashArrayMemory.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashArrayMemory
    (
        const void *p,
        Nucleus_Size n,
        Nucleus_Size m,
        Nucleus_HashValue *hv
    );