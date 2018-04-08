// Copyright (c) Michael Heilmann 2018
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_Status
Nucleus_hashHashValue
    (
        const Nucleus_HashValue v,
        Nucleus_HashValue *hv
    );
