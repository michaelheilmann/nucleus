// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_getNumberOfProcessors
    (
        Nucleus_Size *numberOfProcessors
    );
