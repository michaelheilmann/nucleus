// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Status.h"
#include "Nucleus/Annotations.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/MemoryManagerInterface.h"

Nucleus_NonNull(2, 3, 5, 6) Nucleus_Status
Nucleus_booleanToString
    (
        Nucleus_Boolean value,
        char **bytes,
        Nucleus_Size *numberOfBytes,
        Nucleus_MemoryManager_State *state,
        Nucleus_MemoryManager_Allocate *allocate,
        Nucleus_MemoryManager_Deallocate *deallocate
    );
