// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddSize
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeMulSize
    (
        Nucleus_Size x,
        Nucleus_Size y,
        Nucleus_Size *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger8
    (
        Nucleus_Integer8 x,
        Nucleus_Integer8 y,
        Nucleus_Integer8 *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger16
    (
        Nucleus_Integer16 x,
        Nucleus_Integer16 y,
        Nucleus_Integer16 *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger32
    (
        Nucleus_Integer32 x,
        Nucleus_Integer32 y,
        Nucleus_Integer32 *z
    );

Nucleus_NonNull(3) Nucleus_Status
Nucleus_safeAddInteger64
    (
        Nucleus_Integer64 x,
        Nucleus_Integer64 y,
        Nucleus_Integer64 *z
    );
