// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_subString
    (
        char **result,
        const char *string,
        Nucleus_Size index,
        Nucleus_Size length
    );
