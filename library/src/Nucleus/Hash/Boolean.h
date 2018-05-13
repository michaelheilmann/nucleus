// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Boolean.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hashBoolean.md
Nucleus_NoError() Nucleus_Status
Nucleus_hashBoolean
    (
        const Nucleus_Boolean v,
        Nucleus_HashValue *hv
    );
