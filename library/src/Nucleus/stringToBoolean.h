#pragma once

#include "Nucleus/Status.h"
#include "Nucleus/Annotations.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_stringToBoolean
    (
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Boolean *value
    );
