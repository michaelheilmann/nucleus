// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_getDirectorySeparator.md
Nucleus_NonNull() Nucleus_Status
Nucleus_getDirectorySeparator
    (
        const char **directorySeparator
    );
