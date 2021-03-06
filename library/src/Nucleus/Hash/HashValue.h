// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_Status
Nucleus_hashHashValue
    (
        const Nucleus_HashValue v,
        Nucleus_HashValue *hv
    );
