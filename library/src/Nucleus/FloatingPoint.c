/// @file Nucleus/FloatingPoint.h
/// @brief Support for single, double, and quad precision floating-point numbers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "Nucleus/FloatingPoint.h"




#include <math.h>
#include "Nucleus/Memory.h"




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isSubnormal
    (
        Nucleus_Single x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isSubnormal
    (
        Nucleus_Double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Quadruple_isSubnormal
    (
        Nucleus_Quadruple x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isNaN
    (
        Nucleus_Single x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isNaN
    (
        Nucleus_Double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Quadruple_isNaN
    (
        Nucleus_Quadruple x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}
