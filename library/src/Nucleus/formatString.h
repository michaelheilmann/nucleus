// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_formatString
    (
        char **result,
        const char *format,
        ...
    );
