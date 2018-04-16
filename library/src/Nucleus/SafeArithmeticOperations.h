// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Types/Size.h"
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAdd
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeMul
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    );
