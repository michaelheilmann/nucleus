// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Windows)

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessorsWindows
    (
        Nucleus_Size *numberOfProcessors
    );

#endif
