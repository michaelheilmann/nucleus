// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_hash[NumberType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashSize
    (
        const Nucleus_Size v,
        Nucleus_HashValue *hv
    );
