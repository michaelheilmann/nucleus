// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/FloatingPoint.h"

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumericType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashSingle
    (
        Nucleus_Single x,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumericType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashDouble
    (
        Nucleus_Double x,
        Nucleus_HashValue *hv
    );

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_hash[NumericType].md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashQuadruple
    (
        Nucleus_Quadruple x,
        Nucleus_HashValue *hv
    );
