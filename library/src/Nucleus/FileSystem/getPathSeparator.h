// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_getPathSeparator.md
Nucleus_NonNull() Nucleus_Status
Nucleus_getPathSeparator
    (
        const char **bytes,
        Nucleus_Size *numberOfBytes
    );
